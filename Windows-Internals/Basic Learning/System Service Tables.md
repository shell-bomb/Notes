SSDT (System Service Dispatch Table): Is a table that contains index point of a particular funtion, used to locate a function to execute. The table doesnt know what funcitons are, it only stores the functions 

  * 2 Built-in, up to 4 suported
    * Bits 13-13 select the table
    * Lower 12 bits select the service

* On intel/AMD CPUs, EAX serves as an index to the system service required
  * 32-bit Windows holds the actual addresses
  * 64-bit Windwos holds offsets (32 bit)
    * Lower 4 bits used as argument count
    * Must be masked of to get actual offset

2 Default System Tables

1* KeServiceDescriptorTable
   * Contains only kernel related entries
   * Value is KiServiceTable
2* KeServiceDescriptorTableShadow
      * Contains both kernel entries and USER and GDI entries

When a thread is create, it uses KeServiceDescriptorTable

• The first tiem it makes any GDI or USER call, it starts using KeServiceDescriptorTableShadow
![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130201.png)
Table of loaded kernel functions, offset from left to right indicates the index of the kernel funcion, for example ![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130211.png) is index 0 

To get address ![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130220.png)

To get one kernel Function ![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130230.png)

Don't use the last bit in the offset

The last digit of the offset is the number of parameters that the function can accedpt
For example

NtCreateFile function

![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130238.png)

In this case there is 11 parameters instead of 7.
The first x parameters are passed by the registry stack

If a offset has 0 parameters, this means that the syscall parameter could have 0,1,2,3 or 4 parameters, the function doesn't know how many parameters but the function accept up to 4 parameters.

PatchGuard: Responsible software to check if the core kernel components are not altered, by hashing the SSDT table PatchGuard when kernel is load, can check if has been modifications.

It's not reccomended to hook the SSDT because it can provoke a blue screen

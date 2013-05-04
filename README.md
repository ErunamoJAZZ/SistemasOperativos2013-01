#Pequeño juego para Sistemas Operativos 2013-01

La idea de esto, es que hay un demonio (un programa infinito que está bajo 
cuerda haciendo... alguna cosa...), es decir, un servicio, que está monitorizando
todo el tiempo un archivo llamado "juego_SO".

Este archivo está ubicado en la carpeta del usuario que lo haya llamado. 
En el archivo solo irá una cosa: un número del 0 al 9. 


##Funcionamiento

Tenemos un juego en Python, que escribirá en el archivo mencionado el número
que le digamos. Por el otro lado, el demonio estará revisando todo el tiempo 
dicho archivo, en caso que el número que esté allí, concuerde con el que él 
estaba escondiendo, dará una alarma, y cambiará su numero escondido.

##Compilando
Las dependencias en distribuciones basadas en Debian/Ubuntu sería algo como:
`sudo aptitude install build-essential zenity python python-wxgtk2.8`

Para compilar el demonio se necesita el GCC 4.7 o superior, y se usa el comando 
`g++ -std=c++11 demonio.c -o demon_SO`
cuidando de colocar la compatibilidad con el nuevo estándar de C++ 2011.

_El demonio fue probado en Debian Wheezy. Si se prueba con Ubuntu, hay que mirar 
primero qué versión del GCC tiene. En teoría, las versiones mayores a la 12.10 
deberían funcionar sin problemas._


#Tecnología usada (?)
##El Demonio
Este demonio está basado en el código básico explicado por Devin Watson en su 
documento _"Linux Daemon Writing HOWTO"_. A ese código se le hicieron algunas 
modificaciones, tales como la utilización de C++11 en vez de C puro, ya que 
tiene algunas comodidades respecto al manejo de Strings.
También se usó Zenity para generar los avisos de error y de victoria.

##El Juego
El otro programa está escrito en python, y la GUI está hecha con wxPython, 
usando wxGlade para el diseño.


#Licencia
¿WTFPL?, podría ser... xD

/* 
 *   Mayo de 2013, Universidad Nacional de Colombia, sede Medellín
 * 
 *              Trabajo Práctico 1, Sistemas Operativos:
 *                          Servicio Demonio
 * 
 * Integrantes:
 *   Vincent D. Restrepo T.
 *   Karen Y. Espinosa Z.
 *   C. Daniel Sanchez R.
 * 
 * Descripción del trabajo: 
 *   Crear un proceso demonio que vigile permanentemente la ocurrencia de 
 *   un evento, y una vez detectado este, se debe generar una acción. 
 *   Se debe crear un segundo programa que genere el evento.
 * 
 * 
 *  NOTA: Para compilar es INDISPENSABLE una versión del GCC 4.7 o superior, y
 *        debe compilarse usando la sentencia:
 *                     $ g++ -std=c++11 demonio.c -o demon_SO
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <string>
#include <pwd.h>
#include <time.h>


using namespace std;


int main(void) {
    
    pid_t pid, sid;
    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
    we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    /* Change the file mode mask */
    umask(0);
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    
    
    
    
    /*Recuperando el nombre del usuario para el path*/
    char *name; 
    char path_[] = "/home/";
    struct passwd *pass; 
    pass = getpwuid(getuid()); 
    name = pass->pw_name; 
    strcat(path_, name);
    //printf("This is the login name: %s y %s\n", name,path_);
    
    /* Cambiando el directorio de trabajo a /home/<usuarioActual> */
    if ((chdir(path_)) < 0) {
        exit(EXIT_FAILURE);
    }
    
    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    
    
    /* INICIALIZACIÓN DE VARIABLES IMPORTANTES */
    FILE *fichero;       //Archivo para leer
    int himitsu;         //numero secreto
    srand(time(NULL));   //Inicializa la semilla del numero aleatorio
    himitsu = rand()%10; //Numero aleatorio del 0 al 9
    
    char num_c[1]; //Numero leído
    int  num_i;    //Numero convertido a integer
    string mensaje;//Mensaje que sale cuando se gana.
    
    
    //Ciclo infinito
    while (1) { 
        
        //Se abre el fichero en solo lectura
        fichero = fopen("juego_SO", "r+");
        
        //En caso de no esté el archivo o algo así...
        if (fichero == NULL) {
            system("zenity --error --text='Hay un error. Abra el juego primero.'");
        }
        
        //En caso de que sí se haya abierto el fichero...
        else {
            //lee solo el primer carácter (que deberá ser un número del 0 al 9)
            fgets(num_c,2,fichero); 
            fclose( fichero );
            
            //lo convierte a entero.
            num_i = atoi (num_c); 
            
            //Si el número escrito sí es el número secreto...
            if (num_i == himitsu) {
                //Genera el mensaje y lo muestra
                mensaje = "zenity --info --text='¡Felicidades!, hallaste el número secreto... era "+to_string(himitsu)+". \n\n                            Ｏｏ｡｡(￣_￣*) \n\n\n ... generando un nuevo número...'";
                system(mensaje.c_str());
                
                //.. y genera uno nuevo.
                srand(time(NULL));  //nueva semilla del numero aleatorio
                himitsu = rand()%10; //nuevo número aleatorio del 0 al 9
            }
            else{
                //... y sino, pues no hace nada xD
            }
        }
        
        //Espera 1 segundo para volver a comprobar el estado del archivo.
        sleep(1);
    }
    
    exit(EXIT_SUCCESS);
}


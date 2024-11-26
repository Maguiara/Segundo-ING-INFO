
/**
 * PSEUDOCÓDIGO DE LA PRACTICA
 * parse_args(): Procesar los argumentos de la línea de comandos
    error-fatal if error al procesar los argumentos
    if las opciones contienen -h o --help
      Mostrar ayuda
      Terminar sin error
    end if
    error-fatal if NO se ha indicado un nombre de archivo en los argumentos
      read_all(): Leer archivo en memoria
      if error de permisos o archivo no encontrado
        send_response(): Mostrar mensaje de error leve
        (ver Sección 1.1.2)
        error
      elif otro error etectado
        error-fatal
      else
        send_response(): Mostrar el contenido del archivo en la salida estándar
        (ver Sección 1.1)
      end if
 * 
 */

#include <iostream>

int main (int argc, char *argv[]) {


}
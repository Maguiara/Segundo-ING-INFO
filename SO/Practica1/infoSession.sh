#!/bin/bash

# "Foto" del proceso ps sin los identificadores de sesion 0
# Para añadir los identificadores de sesion 0 se usa -eo sid,pgid,pid,euser,tty,%mem,cmd, si no los quiero pongo -o
PS_HEADER=$(ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser | awk 'NR==1 {print $0}')
PS_FOTO=$(ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser)

# Para imprimir respetando los saltos de linea
#printf "%s\n" "$PS_FOTO" 

# Para imprimir sin respetar los saltos de linea
#echo $PS_FOTO

############################################################################################################
##FUNCIONES USADAS EN EL SCRIPT##
# Funcion que muestra la ayuda del script
show_help() {
  echo "Uso: $0 [-h] [-z] [-u user] "
  echo  "Opciones: "
  echo "-h  Muestra la ayuda"
  echo "-z  Muestra los procesos con identificador de sesion 0"
  echo "-u user  Muestra los procesos del usuario indicado"
  exit 0
}

# Funcion que muestra los procesos con identificador de sesion 0
show_indentifier_0() {
  local indentifier_user=""
    if [[ -n "$1" ]]; then
      for indentifier_user in "${usuarios[@]}"; do
        if id "$indentifier_user" &>/dev/null; then
          echo "Procesos con identificador de sesion 0 del usuario $indentifier_user"
          echo
          printf "%s\n" "$PS_HEADER"
          #Si no es mostrar solo los procesos con identificador de sesion 0 del usuario se quita la comparacion de $1
          printf "%s\n" "$PS_FOTO" | awk -v user_awk="$indentifier_user" '$1 == 0 && $4 == user_awk {print $0}'
          echo
        else 
          error_exit "El usuario $indentifier_user no existe"
        fi
      done
    else
      echo "Procesos con identificador de sesion 0"
      echo
      printf "%s\n" "$PS_HEADER"
      #Si no es mostrar solo los procesos con identificador de sesion 0 se quita la comparacion de $1
      printf "%s\n" "$PS_FOTO" | awk '$1 == 0 {print $0}'
    fi
  #else 
    #error_exit "El usuario $1 no existe"
  #fi
}

# Funcion que muestra los procesos sin identidicador de sesion 0
show_process_without_identifier_0() {
  echo "Procesos sin identificador de sesion 0"
  echo
  printf "%s\n" "$PS_FOTO" | awk '$1 != 0 {print $0}'
}

# Funcion que muestra los procesos de un usuario
show_process_user() {
  local show_user=""
  #Print de las cabezeras
  printf "%s\n" "$PS_HEADER"
  #Bucle para recorrer los usuarios
  for show_user in "${usuarios[@]}"; do
    #Comprobacion de si el usuario existe
    if id "$show_user" &>/dev/null; then
      printf "%s\n" "$PS_FOTO" | awk -v user_awk="$show_user" '$4 == user_awk {print $0}'
    else
      #Mensaje de error si el usuario no existe
      error_exit "El usuario $show_user no existe"
    fi
  done
}

# Funcion que muestra los procesos con lsof
show_lsof() {
  local dir_lsof="$1"
  local show_lsof_user=""
  #Comprobacion de si el directorio existe
  if [ -d "$dir_lsof" ]; then
    #Bucle para recorrer los usuarios
    if [[ -n "$2" ]]; then
      for show_lsof_user in "${usuarios[@]}"; do
        #Comprobacion de si el usuario existe
        if id "$show_lsof_user" &>/dev/null; then
          #Print de los procesos con lsof
          lsof -u $show_lsof_user $dir_lsof | awk -v user_awk="$show_lsof_user" '$3 == user_awk {print $0}'
        else
          #Mensaje de error si el usuario no existe
          error_exit "El usuario $show_lsof_user no existe"
        fi
      done
    else 
      #Print de los procesos con lsof
      lsof $dir_lsof
    fi
  else
    #Mensaje de error si el directorio no existe
    error_exit "El directorio $dir_lsof no existe"
  fi
}

#Funcion para mostrar un mensaje de error y salir
error_exit() {
    echo "$1" 1>&2
    exit 1
}

############################################################################################################
##GESTION DE LAS FLAGS Y ARGUMENTOS DEL SCRIPT##

# Flags y variables para las opciones del script
show_help_flag=false
show_identifier_flag=false
show_user_flag=false
show_lsof_flag=false
user_arg=""
dir_lsof=""
# Array para almacenar los usuarios
usuarios=()

# Funcion para gestionar las opciones del script
while getopts ":hdzu:" option; do
  case $option in 
    h)
      # Activar el flag de mostrar la ayuda
      show_help_flag=true
      ;;
    z)
      # Activar el flag de mostrar los procesos con identificador de sesion 0
      show_identifier_flag=true
      ;;
    u)
     # Activar el flag de mostrar los procesos de un usuario
      show_user_flag=true
      # Desplazar a la siguiente posición
      shift 
      # Capturar todos los argumentos que siguen hasta que encuentres otro flag o se terminen los argumentos
      while [[ "$1" != -* && "$1" != "" ]]; do
          usuarios+=("$1")
          shift
      done
      ;;
    d)
      # Activar el flag de mostrar los procesos con lsof
      show_lsof_flag=true
      dir_lsof="$2"
      ;;
    \?)
    # Si se introduce una opcion no valida
      error_exit "Opcion invalida: $OPTARG"
      ;;
    :)
    # Si se introduce una opcion sin argumento
      error_exit "La opcion -$OPTARG requiere un argumento"
      ;;
  esac
done

############################################################################################################
##CUERPO DEL SCRIPT##

# Si se ha activado la bandera de ayuda, se muestra la ayuda
if $show_help_flag; then
  show_help
fi

if $show_identifier_flag && $show_user_flag; then
  show_indentifier_0 "${usuarios[@]}"

elif $show_lsof_flag && $show_user_flag; then
  show_lsof "$dir_lsof" "${usuarios[@]}"

elif $show_lsof_flag; then
  show_lsof "$dir_lsof"

elif $show_identifier_flag; then
  show_indentifier_0

elif $show_user_flag; then
  show_process_user "${usuarios[@]}"

else 
  show_process_without_identifier_0

fi


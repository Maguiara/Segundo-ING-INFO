#!/bin/bash

# Variables constantes usadas en el script
# Para añadir los identificadores de sesion 0 se usa -eo sid,pgid,pid,euser,tty,%mem,cmd, si no los quiero pongo -o
PS_HEADER=$(ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser | awk 'NR==1 {print $0}')
PS_FOTO=$(ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser)
ACTUAL_USER=$(whoami)

# Para imprimir respetando los saltos de linea
#printf "%s\n" "$PS_FOTO" 

# Para imprimir sin respetar los saltos de linea
#echo $PS_FOTO

############################################################################################################
##FUNCIONES USADAS EN EL SCRIPT##
# Funcion que muestra la ayuda del script
show_help() {
  cat << EOF
    =============================================================
    Uso: $0 [-h] [-z] [-u user1 ... userN] [-d dir]
    =============================================================
    Opciones: 
      -h                  Muestra la ayuda
      -z                  Muestra los procesos con identificador de sesion 0
      -u user1 ... userN  Muestra los procesos de la lista de usuarios indicados
      -d dir              Muestra los procesos que tienen archivos abiertos en un directorio especificado
EOF
    exit 0
}

# Funcion que muestra los procesos con identificador de sesion 0
show_indentifier_0() {
  local indentifier_user=""
    if [[ $show_user_flag == true ]]; then
      for indentifier_user in "${usuarios[@]}"; do
        if id "$indentifier_user" &>/dev/null; then
          echo "Todos los procesos (incluido sesion 0) del usuario $indentifier_user"
          echo
          printf "%s\n" "$PS_HEADER"
          #Si no es mostrar solo los procesos con identificador de sesion 0 del usuario se quita la comparacion de $1
          #awk '$1 == "0" { if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print }'
          printf "%s\n" "$PS_FOTO" | awk -v user_awk="$indentifier_user" '$4 == user_awk { if (length($0) > 100) $0 = substr($0, 1, 97) "..."; print $0}'
          if [[ $show_num_process_flag == true ]]; then
            printf "%s\n" "$PS_FOTO" | awk 'END {print "El numero de lineas es: " NR}'
          fi
        else 
          error_exit "El usuario $indentifier_user no existe"
        fi
      done
    else
      echo "Todos los procesos (incluido sesion 0)"
      echo
      #Si no es mostrar solo los procesos con identificador de sesion 0 se quita la comparacion de $1
      printf "%s\n" "$PS_FOTO" | awk -v actual_user="$ACTUAL_USER" ' $4 == actual_user {if (length($0) > 100) $0 = substr($0, 1, 97) "...";  print $0}'
      if [[ $show_num_process_flag == true ]]; then
      printf "%s\n" "$PS_FOTO" | awk -v actual_user="$ACTUAL_USER" ' $4 == actual_user {if (length($0) > 100) $0 = substr($0, 1, 97) "...";  print $0}' | awk 'END {print "El numero de lineas es: " NR}'
      fi
    fi
  exit 0
}

# Funcion que muestra los procesos sin identidicador de sesion 0
show_process_without_identifier_0() {
  echo "Procesos sin identificador de sesion 0"
  echo
  printf "%s\n" "$PS_HEADER"
  printf "%s\n" "$PS_FOTO" | awk -v actual_user="$ACTUAL_USER" '$1 != 0 && $4 == actual_user {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}'

  if [[ $show_num_process_flag == true ]]; then 
    printf "%s\n" "$PS_FOTO" | awk -v actual_user="$ACTUAL_USER" '$1 != 0 && $4 == actual_user {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}'| awk 'END {print "El numero de lineas es: " NR}'
  fi
  exit 0
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
      echo
      echo "Todos los procesos del usuario $show_user"
      echo
      printf "%s\n" "$PS_FOTO" | awk -v user_awk="$show_user" ' $1 != 0 && $4 == user_awk {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}'
      if [[ $show_num_process_flag == true ]]; then
        printf "%s\n" "$PS_FOTO" | awk -v user_awk="$show_user" '$1 != 0 && $4 == user_awk {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}' | awk 'END {print "El numero de lineas es: " NR}'
      fi
    else
      #Mensaje de error si el usuario no existe
      error_exit "El usuario $show_user no existe"
    fi
  done
  exit 0
}

# Funcion que muestra los procesos con lsof
show_lsof() {
  local dir_lsof="$1"
  local show_lsof_user=""
  #Comprobacion de si el directorio existe
  if [ ! -d "$dir_lsof" ]; then
    error_exit "El directorio $dir_lsof no existe"
  fi
  # Si se activo la bandera de mostrar los procesos de un usuario
  if [[ $show_user_flag == true ]]; then
    for show_lsof_user in "${usuarios[@]}"; do
      #Comprobacion de si el usuario existe
      if id "$show_lsof_user" &>/dev/null; then
        #Print de los procesos con lsof
        lsof +d "$dir_lsof" | awk -v user_awk="$show_lsof_user" '$3 == user_awk {print $0}'
        if [[ $show_num_process_flag == true ]]; then
          # Si se activa la bandera de procesos en la tabla
          lsof +d "$dir_lsof" | awk -v user_awk="$show_lsof_user" '$3 == user_awk {print $0}' | awk 'END {print "El numero de lineas es: " NR}'
        fi
      else
      #Mensaje de error si el usuario no existe
      error_exit "El usuario "$show_lsof_user" no existe"
    fi
    done
  else 
    #Print de los procesos con lsof
    lsof +d "$dir_lsof" | awk '{ if (length($0) > 100) $0 = substr($0, 1, 98) "..." ; print $0}'
    if $show_num_process_flag; then
    lsof +d "$dir_lsof" | awk '{ if (length($0) > 100) $0 = substr($0, 1, 98) "..." ; print $0}' | awk 'END {print "El numero de lineas es: " NR}'
    fi
  fi
  exit 0
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
show_num_process_flag=false
show_terminal_flag=false
user_arg=""
dir_lsof=""
# Array para almacenar los usuarios
usuarios=()

# Funcion para gestionar las opciones del script
# $# es el numero de argumentos
while [[ $# -gt 0 ]]; do
  # Capturar la opcion
  option=$1
  case $option in 
    -h)
      # Activar el flag de mostrar la ayuda
      show_help
      ;;
    -z)
      # Activar el flag de mostrar los procesos con identificador de sesion 0
      show_identifier_flag=true
      shift
      ;;
    -u)
     # Activar el flag de mostrar los procesos de un usuario
      show_user_flag=true
      shift
      # Guardar los usuarios en un array
      # =~ sirve para comparar una expresion regular
      while [[ $# -gt 0 && ! $1 =~ ^- ]]; do
        usuarios+=("$1")
        shift
      done
      ;;
    -d)
      # Activar el flag de mostrar los procesos con lsof
      show_lsof_flag=true
      shift
      # Guardar el directorio en la variable
      dir_lsof=$1
      shift
      ;;
    -n)
      #Activar el flag de procecos en la tabla
      show_num_process_flag=true
      shift
      ;;
    -t)
      show_terminal_flag=true
      shift
      ;;
    *)
      #Mensaje de error si falta un argumento
      error_exit "La opcion $option no es valida"
      ;;
  esac
done


############################################################################################################
##CUERPO DEL SCRIPT##

# Debug 
# Descomentar en caso de necesitar ver el valor de las variables

#echo "Bandera para mostrar la ayuda: $show_help_flag"
#echo "Bandera para el numero de procesos: $show_num_process_flag"
#echo "Bandera para los procesos 0: $show_identifier_flag"
#echo "Bandera para los usuarios: $show_user_flag"
#echo "Bandera para lsof: $show_lsof_flag"
#echo "Direcctorio para lsof: $dir_lsof"
#echo "Usuarios especificados: ${usuarios[@]}"

usuarios_prueba=( "root" "usuario" )
ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser | awk -v user_awk="${usuarios_prueba}" ' $4 == user_awk {if (length($0) > 100) $0 = substr($0, 1, 97) "..."; print $0}'

echo "usuarios_prueba: ${usuarios_prueba[@]}"
exit 0

# Estas opciones "son las mas importantes", por ello si se activan se ejecutaran en este orden
# utilizando en la funcion el resto de banderas en caso de necestiarlas

# Si se ha activado la bandera de mostrar los procesos con identificador de sesion 0
if $show_identifier_flag; then
    show_indentifier_0 
# Si se ha activado la bandera de mostrar los procesos con lsof
elif $show_lsof_flag; then
    show_lsof "$dir_lsof" 
# Si se ha activado la bandera de mostrar los procesos de un usuario
elif $show_user_flag; then
  show_process_user 
# Si no se ha activado ninguna bandera
else 
  show_process_without_identifier_0
fi


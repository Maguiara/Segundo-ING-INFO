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
      -t                  Muestra los procesos que tienen una terminal asociada
EOF
    exit 0
}

# Funcion que muestra los procesos sin identidicador de sesion 0
show_process_without_identifier_0() {
  # Filtra PS-FOTO para que se muestren solo los procesos que no tienen identificador 0
  PS_FOTO=$(echo "$PS_FOTO" | awk '$1 != 0 {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}' )
}

# Funcion que filtra los procesos por el que tenga una terminal asociada
filter_terminal() {
  PS_FOTO=$(echo "$PS_FOTO" | awk -v terminal_asociada="?" '$5 != terminal_asociada {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}')
}

# Funcion que muestra los procesos de un usuario
show_process_user() {
  local show_user=""
  local PS_FILTRADO=()
  #Print de las cabezeras
  printf "%s\n" "$PS_HEADER"
  #Bucle para recorrer los usuarios
  for show_user in "${usuarios[@]}"; do
    #Comprobacion de si el usuario existe
    if id "$show_user" &>/dev/null; then
      echo
      echo "Todos los procesos del usuario $show_user"
      echo
      if [[ $imprimir_archivo_flag == true ]]; then
        echo "$PS_FOTO" | awk -v user_awk="$show_user" '$4 == user_awk {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}' > "$user_file"
      else 
        printf "%s\n" "$PS_FOTO" | awk -v user_awk="$show_user" '$4 == user_awk {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}'
      fi

      if [[ $show_num_process_flag == true ]]; then
        printf "%s\n" "$PS_FOTO" | awk -v user_awk="$show_user" '$4 == user_awk {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}' | awk 'END {print "El numero de lineas es: " NR}'
      fi
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
modo_ps_flag=false
imprimir_archivo_flag=false
user_arg=""
dir_lsof=""
user_file=""
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
    -e)
      modo_ps_flag=true
      shift
      ;;
    -f)
      imprimir_archivo_flag=true
      shift
      user_file=$1
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

# DEBUG # 
# Descomentar en caso de necesitar ver el valor de las variables

#echo "Bandera para mostrar la ayuda: $show_help_flag"
#echo "Bandera para el numero de procesos: $show_num_process_flag"
#echo "Bandera para los procesos 0: $show_identifier_flag"
#echo "Bandera para los usuarios: $show_user_flag"
#echo "Bandera para lsof: $show_lsof_flag"
#echo "Direcctorio para lsof: $dir_lsof"
#echo "Usuarios especificados: ${usuarios[@]}"
#echo "Bandera de guaradar en archivo: $imprimir_archivo_flag"
#echo "Archivo= $user_file"
#exit 0


if $modo_ps_flag; then
  # Filtra PS_FOTO por los procesos con o sin identidicador 0
  if [[ $show_identifier_flag == false ]]; then
    show_process_without_identifier_0
  fi
  # Filtra PS_FOTO por los procesos que tienen una terminal asociada
  if $show_terminal_flag; then
    filter_terminal
  fi

  # Si se activa muestra todos los procesos del usuario especificado, si no muestra PS_FOTO filtrado sin mas
  if $show_user_flag; then
    show_process_user
  else
    if [[ $imprimir_archivo_flag == true ]]; then
      echo "$PS_FOTO" > "$user_file"
    else 
      echo "$PS_FOTO"
    fi
  fi



  # Si se activa busca los procesos de un directorio especificado
  if $show_lsof_flag; then
    show_lsof "$dir_lsof" 
  fi

else

  echo "$PS_FOTO" | awk ' BEGIN {
    # Imprimir los encabezados de las columnas
    print  "sid | total de pgid | total de %mem| pgid | user | tty | cmd";
  }

  {
    # Asignamos las variables de acuerdo a las columnas de entrada
    pid = $1;         
    sid = $2;         
    pgid = $3;         
    cmd = $7;         
    uid = $5;         
    mem = $4;          
    tty = $6;          

    # Procesar solo sesiones válidas (sid != 0)
    if (sid != 0) {
        # Si la sesión no ha sido registrada antes, la inicializamos
        if (!(sid in sesiones)) {
            sesiones[sid] = "";
            grupos[sid] = "";     
            memoria[sid] = 0;     
            lider[sid] = pid;     
            usuario[sid] = get_user(uid);  
            terminal[sid] = tty;  
            comando[sid] = cmd;   
        }

        # Sumar la memoria consumida por la sesión
        memoria[sid] += mem;

        # Si el proceso es el líder de la sesión, actualizamos la información
        if (pgid == pid) {
            lider[sid] = pid;
            comando[sid] = cmd;
        }

        # Registrar los grupos de procesos en la sesión (sin repetir)
        if (pgid != sid) {
            grupos[sid] = grupos[sid] (grupos[sid] ? " " : "") pgid;
        }
    }
}

END {
    # Al final, procesamos y mostramos la información recopilada
    for (sid in sesiones) {
        # Contar cuántos grupos de procesos diferentes hay en la sesión
        split(grupos[sid], grps, " ");
        total_grupos = length(grps);

        # Verificar los datos del líder de la sesión
        if (lider[sid] != "" && lider[sid] != sid) {
            lider_pid = lider[sid];
            lider_usuario = usuario[sid];
            lider_terminal = terminal[sid];
            lider_comando = comando[sid];
        } else {
            lider_pid = "?";
            lider_usuario = "?";
            lider_terminal = "?";
            lider_comando = "?";
        }

        # Imprimir la información de la sesión en formato tabulado
        print sid "\t" total_grupos "\t" memoria[sid] "\t" lider_pid "\t" lider_usuario "\t" lider_terminal "\t" lider_comando;
    }
}

# Función para obtener el nombre del usuario a partir del UID
function get_user(uid) {
    # Ejecutamos el comando `getent passwd` para obtener el nombre de usuario
    cmd = "getent passwd " uid " | cut -d: -f1";
    cmd | getline user;
    close(cmd);
    return user;
}
  '

fi
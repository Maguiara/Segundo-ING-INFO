#!/bin/bash

# Variables constantes usadas en el script
# Para añadir los identificadores de sesion 0 se usa -eo sid,pgid,pid,euser,tty,%mem,cmd, si no los quiero pongo -o
PS_HEADER=$(ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser | awk 'NR==1 {print $0}')
PS_FOTO=$(ps -eo sid,pgid,pid,euser,tty,%mem,cmd --sort=euser --no-headers)
ACTUAL_USER=$(whoami)
# En la practica: ACTUAL_USER=$(alu0101+)

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

      -e                  Muestra los procesos en formato tabla, si se activa:
        -h                  Muestra la ayuda
        -z                  Muestra los procesos con identificador de sesion 0
        -u user1 ... userN  Muestra los procesos de la lista de usuarios indicados
        -d dir              Muestra los procesos que tienen archivos abiertos en un directorio especificado
        -n                  Muestra el numero de procesos en la tabla
        -t                  Muestra los procesos que tienen una terminal asociada
        -f file             Guarda la salida en un archivo
        -sm                 Ordemaniento por porcentaje de memoria consumida por el proceso
        -r                  Revierte cualquier tipo de ordenamiento aplicado
      
      en caso de que no se utilice -e:
        -sg                 Ordenamiento por el numero de grupos de procesos en cada sesion (de menos a mas)
    ========================================================================================================

EOF
    exit 0
}

# Funcion que filtra los procesos con lsof
filter_lsof() {
  local dir_lsof=$1
  # Comprobamos que el directorio exista
  if [ ! -d "$dir_lsof" ]; then
    error_exit "El directorio $dir_lsof no existe"
  fi


  pids_lsof=$(lsof +d $dir_lsof | tail -n+2 | awk '{print $2}')
  # Filtramos PS por los pids obtenidos con lsof
  PS_FOTO=$(echo "$PS_FOTO" | awk -v pids_lsof="$pids_lsof" '
    BEGIN {
      #Tranformamos la lista de pids pasada por lsof en un array
      #Especificamos el delimitador de la lista es un newline
      split(pids_lsof, lista_pids, "\n");
    }

    {
      for (i = 0; i < length(lista_pids); i++) {
        if ($3 == lista_pids[i]) {
          if (length($0) > 100) $0 = substr($0, 1, 97) "..." ;
          print $0;
        }
      }
    }')
}

# Funcion que muestra los procesos sin identidicador de sesion 0
filter_identifier_0() {
  # Filtra PS-FOTO para que se muestren solo los procesos que no tienen identificador 0
  PS_FOTO=$(echo "$PS_FOTO" | awk '$1 != 0 {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}' )
}

# Funcion que filtra los procesos por el que tenga una terminal asociada
filter_terminal() {
  PS_FOTO=$(echo "$PS_FOTO" | awk -v terminal_asociada="?" '$5 != terminal_asociada {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}')
}

# Funcion que muestra los procesos de un usuario
filter_user() {
  # Comprobamos que se haya pasado al menos un usuario
  if [ ${#usuarios[@]} -eq 0 ]; then
    error_exit "La opcion -u requiere al menos un usuario"
  fi
  PS_FOTO=$(echo "$PS_FOTO" | awk -v usuarios="${usuarios[*]}" '
    BEGIN {
      #Tranformamos la lista de usuarios pasada por linea de comandos en un array
      split(usuarios, lista_usuarios, " ");
    }

    {
      for (i = 0; i < length(lista_usuarios); i++) {
        if ($4 == lista_usuarios[i]) {
          if (length($0) > 100) $0 = substr($0, 1, 97) "..." ;
          print $0;
        }
      }
    }')
}

# Funcion que muestra los procesos del usuario actual
filter_actual_user() {
  PS_FOTO=$(echo "$PS_FOTO" | awk -v usuario_actual="$ACTUAL_USER" '$4 == usuario_actual {if (length($0) > 100) $0 = substr($0, 1, 97) "..." ; print $0}')
}

#Funcion para mostrar un mensaje de error y salir
error_exit() {
    echo "$1" 1>&2
    exit 1
}

#Funcion para filtrar los procesos por modo de sesion
filtros_foto_ps() {
  # Filtra PS_FOTO por los procesos con o sin identidicador 0
  if ! $show_identifier_flag; then
    filter_identifier_0
  fi

  # Filtra PS_FOTO por los procesos que tienen una terminal asociada
  if $show_terminal_flag; then
    filter_terminal
  fi

  # Si se activa muestra todos los procesos del usuario especificado, si no muestra PS_FOTO filtrado sin mas
  if $show_user_flag; then
    filter_user
  else 
    filter_actual_user
  fi

  # Si se activa busca los procesos de un directorio especificado
  if $show_lsof_flag; then
    filter_lsof "$dir_lsof" 
  fi

}

# Si no se activa la opcion -e se muestra la tabla de sesiones
get_active_sessions() {
    local sids
    # Se guarda cada sid unico en la variable sids
    sids=$(echo "$PS_FOTO" | awk '{print $1}' | sort -u)

    # Se recorre cada sid y se obtiene la informacion de la sesion
    for sid in $sids; do
        process_leader_info="$(get_process_leader_info "$sid")"
        process_groups_count="$(get_process_groups_count "$sid")"
        memory_usage="$(get_memory_usage "$sid")"

        # Se imprime la informacion de la sesion
        printf "%-10s %-10s %-10s %s\n" "$sid" "$process_groups_count" "$memory_usage" "$process_leader_info"
    done
}

# Funcion para obtener la informacion del lider de un proceso
get_process_leader_info() {
    local sid="$1"
    local leader_info

    # Se intenta obtener la informacion del lider de la sesion, si no se obtiene se imprime ? ? ? ?
    leader_info=$(echo "$PS_FOTO" | awk -v sid="$sid" '$3 == sid' | head -n 1)
    if [[ -z "$leader_info" ]]; then
        printf "%-5s %-10s %-10s %s" "?" " ?" " ?" " ?"
    else
       echo "$leader_info" | awk '{printf "%-5s %-10s %-10s %s", $3, $4, $5, $7}'
    fi
}

# Funcion para obtener el numero de grupos de procesos de una sesion
get_process_groups_count() {
    local sid="$1"
    echo "$PS_FOTO" | awk -v sid="$sid" '$1 == sid {print $2}' | sort -u | wc -l
}

# Funcion para obtener el uso de memoria de una sesion
get_memory_usage() {
    local sid="$1"
    echo "$PS_FOTO" | awk -v sid="$sid" '$1 == sid {total += $6} END {printf "%.2f MB", total}' 
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
      # comprobacion de que exista el usuario
        if id "$1" &>/dev/null; then
          usuarios+=("$1")
        shift
        else
          error_exit "El usuario $1 no existe"
        fi
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
# Filtramos los procesos segun las opciones seleccionadas
filtros_foto_ps

# Comprobamos si se ha activado el modo de sesion
if $modo_ps_flag; then
  if $imprimir_archivo_flag; then
    echo "$PS_HEADER" > "$user_file"
    echo "$PS_FOTO" >> "$user_file"
    if $show_num_process_flag; then
      echo "Numero de procesos: $(echo "$PS_FOTO" | wc -l)" >> "$user_file"
    fi
  else
    echo "$PS_HEADER"
    echo "$PS_FOTO"
    if $show_num_process_flag; then
      echo "Numero de procesos: $(echo "$PS_FOTO" | wc -l)"
    fi
  fi
else
  if $imprimir_archivo_flag; then
    printf "%-10s %-10s %-10s %-5s %-10s %-10s %s\n" "SID" "PGroups" "MemUsage" "PID" "User" "TTY" "CMD" > "$user_file"
    get_active_sessions >> "$user_file"
    if $show_num_process_flag; then
      echo "Numero de sesiones: $(echo "$PS_FOTO" | awk '{print $1}' | sort -u | wc -l)" >> "$user_file"
    fi
  else
    printf "%-10s %-10s %-10s %-5s %-10s %-10s %s\n" "SID" "PGroups" "MemUsage" "PID" "User" "TTY" "CMD"
    get_active_sessions
    if $show_num_process_flag; then
      echo "Numero de sesiones: $(echo "$PS_FOTO" | awk '{print $1}' | sort -u | wc -l)"
    fi
  fi

fi 
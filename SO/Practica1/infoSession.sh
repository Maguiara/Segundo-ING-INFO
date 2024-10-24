#!/bin/bash



# "Foto" del proceso ps
PS_FOTO=$(ps -o sid,pgid,pid,euser,tty,%mem,cmd --no-header --sort=euser -u $USER)


# Funcion para mostrar la ayuda del script

show_help() {
  echo "Uso: &0 [-h] [-z] [-u user] "
  echo  "Opciones: "
  echo "-h  Muestra la ayuda"
  echo "-z  Muestra los procesos con identificador de sesion 0"
  echo "-u user  Muestra los procesos del usuario indicado"
}

# Funcion para mostrar los procesos con identificador de sesion 0
if [ "$1" == "-z" ]; then
  echo "Procesos con identificador de sesion 0"
  PS_FOTO=(echo $PS_FOTO | awk '$1 == 0')
fi

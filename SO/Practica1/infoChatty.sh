#!/bin/bash

# Function to display usage
usage() {
  echo "Usage: $0 [-z] [-u user1,user2,...] [-d directory]"
  exit 1
}

# Capture the snapshot of processes
process_snapshot=$(ps -eo pid,sess,user)

# Parse command line options
while getopts ":zu:d:" opt; do
  case ${opt} in
    z )
      # Include processes with PID 0
      process_snapshot=$(ps -eo pid,sess,user)
      ;;
    u )
      # Filter processes by users
      IFS=',' read -r -a users <<< "$OPTARG"
      user_filter=""
      for user in "${users[@]}"; do
        user_filter+=" -u $user"
      done
      process_snapshot=$(ps -eo pid,sess,user $user_filter)
      ;;
    d )
      # Use lsof in the specified directory
      directory=$OPTARG
      lsof $directory
      exit 0
      ;;
    \? )
      usage
      ;;
  esac
done

# If no options are specified, filter out processes with PID 0
if [ $OPTIND -eq 1 ]; then
  process_snapshot=$(ps -eo pid,sess,user | awk '$1 != 0')
fi

# Display the process snapshot
echo "$process_snapshot"
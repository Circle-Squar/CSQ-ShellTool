#!/bin/bash
user=$(env |grep USER | cut -d = -f 2)
sudouser=$(env|grep SUDO_USER|cut -d = -f 2)

isRoot=false
readPath=""
installPath="/usr/bin/"

if [ -n "$sudouser" ]
then
  isRoot=true
fi

if [ "$user" == "root" ]
then
  isRoot=true
fi


if [ $isRoot == true ]
then
# Root
###########################
  echo "
[INFO] ROOT!
"
  if [ -n "$1" ]
  then
    installPath="$1"
  else
   read -p "Please input Install path by absolute path [Default: /usr/bin/ ] : " readPath
   
   if [ -n "$readPath" ]
   then 
     installPath="$readPath"
    fi
  fi

# Is dir 
###########################
  if [ -e "$installPath" ]
  then 
    # Is dir?
    #########################
    if [ ! -d "$installPath" ]
    then 
      echo "[ERROR] Install Path is a File !"
      exit
    fi

  else
    # make Dir
    #########################
    echo "[WARNING] Install Path not exist! Makeing dir!"
    echo "[INFO] mkdir $installPath "
    mkdir $installPath/
  fi

# Format Path Name
###########################
  if [ "${installPath: -1}" != "/" ]
  then
    installPath="$installPath/"
  fi

# Install
###########################
  echo
  cd scripts
  for i in *
  do
    echo "[INFO] Copy $i to $installPath$i"
    cp $i $installPath -r
    echo "[INFO] Chmod +x $i"
    chmod +x $installPath$i
  done

  echo 
  echo "[INFO] Install done :) "


else
# Non Root
###########################
  echo "
[ERROR] NoN Root!
[INFO] Please run this script by root!
"


fi

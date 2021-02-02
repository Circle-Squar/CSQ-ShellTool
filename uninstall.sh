#!/bin/bash

user=$(env |grep USER |cut -d = -f 2)
sudouser=$(env|grep SUDO_USER|cut -d = -f 2)
isRoot=false

installPath="/usr/bin"
readPath=""


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

# Path
#######################
  if [ -n "$1" ]
  then
    installPath=$1
  else
    read -p "Please input install Path[Default /usr/bin ] : " readPath

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
    echo
    echo "[ERROR] Install Path not exist!"
    echo
    exit
  fi

# Format Path Name
###########################
  if [ "${installPath: -1}" == "/" ]
  then
    echo
  else
    echo 
    installPath="$installPath/"
  fi


# Read File Sheet & del
#######################
  cd scripts
  for i in *
  do
    echo "[INFO] rm $installPath$i"
    rm $installPath$i -r
  done

else
  echo
  echo "[ERROR] Non Root , please run it in root!"
  echo
fi

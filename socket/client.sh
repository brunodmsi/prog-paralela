#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supllied"
    exit
fi

CLIENT_QTY=$1

while :
do
  for i in $(seq 1 $CLIENT_QTY); do
    echo -en "INVASAO DO MACACO $i\0" | nc 127.0.0.1 5000
  done
done
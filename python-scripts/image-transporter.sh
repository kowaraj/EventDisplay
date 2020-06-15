#!/bin/bash

while [ True ] 
do
  for x in `find /home/common/ams-event-display-snapshots/ -type f -mmin 1 -printf '%P___%Cs\n'`
  do 
      a=(`echo ${x} | awk -F"___" '{print $1" "$2}'`)
      even_ts_half=$(( ${a[1]} /2 ))
      even_ts=$(( even_ts_half*2 ))
      echo "MOVE: File name: ${a[0]}, ts= ${a[1]} ---> ${even_ts} "
      mv /home/common/ams-event-display-snapshots/${a[0]} /eos/project-a/amstest/www/buffer/ss_${even_ts}.png
  done

  for x in `find /eos/project-a/amstest/www/buffer/ -type f -mmin +3 -printf '%P___%Cs\n'`
  do 
      a=(`echo ${x} | awk -F"___" '{print $1" "$2}'`)
      echo "DELETE: File name: ${a[0]} - modified @ ${a[1]}"
      rm -rf /eos/project-a/amstest/www/buffer/${a[0]}
  done

  sleep 30
  
done    


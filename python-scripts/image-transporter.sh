#!/bin/bash
path_src="/home/common/ams-event-display-snapshots"
path_dst="/eos/project/w/wwwams/www/buffer"
timeto_mv=1 #min
timeto_rm=3 #min

while [ True ] 
do
  # Clean up local buffer for older than X min files

  for x in `find ${path_src}/ -type f -mmin +${timeto_rm} -printf '%P___%Cs\n'`
  do 
      a=(`echo ${x} | awk -F"___" '{print $1" "$2}'`)
      echo "CLEAN UP: File name: ${a[0]}, ts= ${a[1]}"
      rm -rf ${path_src}/${a[0]}
  done

  # Move to remote buffer

  for x in `find ${path_src}/ -type f -mmin ${timeto_mv} -printf '%P___%Cs\n'`
  do 
      a=(`echo ${x} | awk -F"___" '{print $1" "$2}'`)
      even_ts_half=$(( ${a[1]} /2 ))
      even_ts=$(( even_ts_half*2 ))
      echo "MOVE: File name: ${a[0]}, ts= ${a[1]} ---> ${path_dst}/ss_${even_ts}.png "
      #mv /home/common/ams-event-display-snapshots/${a[0]} /eos/project-a/amstest/www/buffer/ss_${even_ts}.png
      mv ${path_src}/${a[0]} ${path_dst}/ss_${even_ts}.png
  done

  # Clean up remote buffer

  for x in `find ${path_dst}/ -type f -mmin +${timeto_rm} -printf '%P___%Cs\n'`
  do 
      a=(`echo ${x} | awk -F"___" '{print $1" "$2}'`)
      echo "DELETE: File name: ${path_dst}/${a[0]} - modified @ ${a[1]}"
      rm -rf ${path_dst}/${a[0]}
  done


  sleep 30
  
done    


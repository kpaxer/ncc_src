#!/usr/bin/ksh
chnnl=$1
cd /home/mbp/simpre/msg
#array="P0001M P0003M P0005M P0013M P0015M P0021M P0025M P0026M P0033M P0035M P0053M P0060M P0061M P0063M"
array="P0013M P0015M P0021M P0025M  P0060M P0061M P0063M"

dt=`date +%Y%m%d`
tm_h=`date +%H`
(( tm_h_next = tm_h +1 ))
chnnl_uper=` echo $chnnl| tr '[a-z]' '[A-Z]' `
log_name=${chnnl}_${dt}.${tm_h}-${tm_h_next}.log
#for fname in `ls x${chnnl}_*_succ.log`;do
for name in $array;do
    echo "start { "
    fname=xnbk_${name}_succ.log
    echo "    ${fname}"
    simpre $fname
    tran_code=`echo ${fname} |cut -d'_' -f1-2|cut -c 2-`;
    echo "    ${tran_code}" 
    echo "    ${fname}"
    echo "} end "
    echo
    sleep 2
done





mailSend()
{
    mailContent="xxxx Web response time over 5 seconds"
    echo $mailContent | mail -s "xxxxxx Web TimeOut" xxxxx@xxx.cion
}
timeout()
{
    waitfor=5
    command=$*
    $command &
    commandpid=$!
    ( sleep $waitfor ; kill -9 $commandpid  > /dev/null 2>&1 && mailSend ) &
    watchdog=$!
    sleeppid=$PPID
    wait $commandpid > /dev/null 2>&1
    kill $sleeppid > /dev/null 2>&1
}
#测试的函数
xtails()
{
    if [ ! -f "$fname" ]; then
    echo "${fname} is not found"
    fi

    if [ ! -f "$cs_fname" ]; then
        echo "${cs_fname} is not found"
    fi
    echo $tm 
    ret=`sed -n "/${tm}...======================TENPAY BEGIN/p" $cs_fname`
    echo "$ret"
    tm_log=`echo $ret|cut -d'|' -f3`
    tm_log=`echo $ret|cut -d']' -f1`
    echo $tm_log
    if [ -z "$ret" ]; then
    	(( tm = tm-1 ))
    	echo $tm
    	sed -n "/${tm}...=====/p" $cs_fname
    fi
}
tails()
{
    tail -f -0 cs_${chnnl_uper}.${dt}.log >err.log
    #cat err.log|cut -d'|' -f3 |cut -d']' -f1 >err
}

dt=`date +%Y%m%d`
cd ~/log/`date +%Y%m%d`;


#dt=`date +%Y%m%d%H%M`
tm=`date +%H%M`
tm_h=`date +%H`
(( tm_h_next = tm_h +1 ))

chnnl=`echo $1|cut -d'_' -f1|cut -c 2-`
chnnl_uper=` echo $chnnl| tr '[a-z]' '[A-Z]' `

fname=${chnnl}_${dt}.${tm_h}-${tm_h_next}.log
cs_fname=cs_${chnnl_uper}.${dt}.log

echo $cs_fname
echo $fname

timeout tails &
simpub $1 > /dev/null 2>&1
cat err

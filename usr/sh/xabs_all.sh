#!/usr/bin/bsh
#netstat -Aan|grep LISTEN|awk -F ' ' '{print $5}'|awk -F '.' '{print $NF}'|sort -n
cd /home/mbp/file/sim
for fname in `ls xabs*succ.log`;do
    echo $fname;
    simabs $fname;
done





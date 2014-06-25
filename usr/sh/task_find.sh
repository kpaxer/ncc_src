#!/usr/bin/ksh

while read line; do
    find ~/bin -name "$line"
done < /home/mbp/usr/sh/task.cfg

while read line; do
    find ~/tools -name "$line" >tmp.txt
    size=`wc -c tmp.txt |awk '{print $1}'`
    #echo $size
    #echo ====================
    if [ "$size" -eq 0 ];then
        echo "File $line is not find!"
    #else 
    #    echo `cat tmp.txt`
    fi
done < /home/mbp/usr/sh/task.cfg

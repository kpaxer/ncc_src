#!/usr/bin/ksh
#netstat -Aan|grep LISTEN|awk -F ' ' '{print $5}'|awk -F '.' '{print $NF}'|sort -n
#for fname in `ls`;do
#    if [[ $fname != tran_* ]]  ;then
#        continue;
#    fi
#    
#    if [ -f $fname ]  ;then
#        echo $fname;
#        echo x$fname;
#        mv $fname x$fname;
#    fi
#
#    #echo $dir
#done
#

for fname in `ls`;do
    if [[ $fname != xtran_* ]]  ;then
        continue;
    fi
    if [ -f $fname ]  ;then
        #new_fname=${fname:1};
        new_fname=`echo $fname|cut -c 2-`;
        #echo $fname:$new_fname
        line=`grep "^CronTaskRun" $fname`;
        #echo $line
        echo '#!/usr/bin/ksh' >$new_fname
        echo '. $HOME/tools/task_pub.sh' >$new_fname
        echo $line >> $new_fname;
    fi
done
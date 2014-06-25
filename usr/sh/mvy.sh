#!/usr/bin/ksh
cd ~/simpre/msg
for fname in `ls`;do
    if [[ $fname != ynbk* ]]  ;then
        continue;
    fi
    
    if [ -f $fname ]  ;then
        new_fname=`echo $fname|cut -c 2-`;
        new_fname=x$new_fname
        echo $new_fname;
        mv $fname $new_fname;
        #echo $fname;
        #echo $new_fname;
    fi

    #echo $dir
done



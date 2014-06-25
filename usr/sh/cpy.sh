#!/usr/bin/ksh
cd ~/simpre/msg
for fname in `ls`;do
    if [[ $fname != yabs* ]]  ;then
        continue;
    fi
    
    if [ -f $fname ]  ;then
        new_fname=`echo $fname|cut -c 2-`;
        new_fname=x$new_fname
        echo $new_fname;
        cp $fname $new_fname;
    fi

    #echo $dir
done



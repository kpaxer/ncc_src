#!/usr/bin/ksh
cd ~/file/sim
for fname in `ls`;do
    if [[ $fname != xabs* ]]  ;then
        continue;
    fi
    
    if [ -f $fname ]  ;then
        new_fname=`echo $fname|cut -c 5-`;
        new_fname=xabs_$new_fname
        echo $new_fname;
        mv $fname $new_fname;
        #echo $fname;
        #echo $new_fname;
    fi

    #echo $dir
done



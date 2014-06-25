#netstat -Aan|grep LISTEN|awk -F ' ' '{print $5}'|awk -F '.' '{print $NF}'|sort -n
array="111 222 33"
for port in $array; do
    echo $port
done

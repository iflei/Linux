#!/bin/bash

net='192.168.2.'  #当前局域网的网络号
i=1  #表示主机号

count=0
while [ $i -le 254 ] #主机号0-255，去掉0x00和0xff剩下254个
do
    if [ $count -eq 20 ];then   #每 ping 20个ip，sleep 1秒
	    count=0
		sleep 1
	fi
	ping -c1 $net$i & 
	let i++
	let count++
done

wait
echo '##################################################################################'
arp | grep -v 'incomplete' #打印所有不包含incomplete的IP地址和对应MAC地址
echo '##################################################################################'

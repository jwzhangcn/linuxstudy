#!/bin/bash

DIR=backup

touch num{1..10}.c

if [ ! -d $DIR ]
then
	mkdir $DIR
fi

for v in `ls`
do	
	if [ -f $v ]
	then
		chmod u+x $v
		echo "$v 赋予权限"
	fi
done

for v in `ls`
do	
	if [ -f $v ]
	then
		cp *.c $DIR
	fi
done

tar -zcvf backup.tar.gz ./$DIR



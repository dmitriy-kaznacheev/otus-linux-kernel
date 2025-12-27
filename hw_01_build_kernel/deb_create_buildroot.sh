#!/bin/bash

chr="/home/build_root_6.1.130"
sudo debootstrap \
     --include ncurses-term,mc,locales,nano,gawk,lsb-release,acl \
     --components=main,contrib,non-free 
     bookworm \
     ${chr} \
     http://mirror.mephi.ru/debian/

cp /etc/resolv.conf ${chr}/etc/resolv.conf
echo "cp /etc/resolv.conf ${chr}/etc/resolv.conf"

cd ${chr}
mount proc -t proc ./proc
echo "proc"
mount sys -t sysfs ./sys
echo "sys"
mount --bind /dev ./dev
echo "dev"

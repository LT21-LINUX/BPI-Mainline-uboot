#!/bin/bash
TOPDIR=`pwd`
TOOLCHAIN=gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu
export PATH=$TOPDIR/toolchains/$TOOLCHAIN/bin:$PATH
#cd linux-4.14
#cd linux-4.17.6
#cd linux-4.18-rc4
#cd linux-4.18
#cd linux-4.19-rc1
#cd linux-4.19

K=linux-5.16.17
L=/tmp/$K.log

cd $K
date >> $L
echo build $K >> $L
#
##
#

nproc=$(cat /proc/cpuinfo | grep processor | wc -l )
echo nproc=$nproc
export ARCH=arm64
export CROSS_COMPILE=aarch64-none-linux-gnu-
cp -a config .config
make -j$nproc dtbs
LOADADDR=0x40008000 make -j$nproc Image Image.gz
make -j$nproc modules
make -j$nproc INSTALL_MOD_PATH=out modules_install
#make headers_install

#
##
#
date >> $L

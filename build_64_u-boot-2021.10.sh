#!/bin/bash
TOPDIR=`pwd`
TOOLCHAIN=gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu
export PATH=$TOPDIR/toolchains/$TOOLCHAIN/bin:$PATH
#cd u-boot-sunxi
cd u-boot-2021.10
#./bpi-m2p-h5.sh
./bpi-m64.sh
#./opi3.sh

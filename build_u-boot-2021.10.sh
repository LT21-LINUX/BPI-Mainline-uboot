#!/bin/bash
TOPDIR=`pwd`
TOOLCHAIN=gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf
export PATH=$TOPDIR/toolchains/$TOOLCHAIN/bin:$PATH
#cd u-boot-sunxi
#cd u-boot-2019.04
#cd u-boot-2019.07
cd u-boot-2021.10
#./bpi-r2.sh
#./bpi-m2u.sh
#./bpi-m2b.sh
#./bpi-m2p.sh
#./bpi-m2p-480.sh
#./bpi-m3.sh
#./bpi-m2z.sh
#./bpi-p2z.sh
#./bpi-m2.sh
#./bpi-r1.sh
#./bpi-m1p.sh
#./bpi-m1.sh
exit
./bpi-r2.sh
./bpi-p2z.sh
./bpi-m2z.sh
./bpi-m2m.sh
./bpi-m2b.sh
./bpi-m2u.sh
./bpi-m2p.sh
./bpi-m3.sh
./bpi-m2.sh
./bpi-r1.sh
./bpi-m1p.sh
./bpi-m1.sh

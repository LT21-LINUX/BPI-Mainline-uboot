#!/bin/bash
TOPDIR=`pwd`
TOOLCHAIN=gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu
export PATH=$TOPDIR/toolchains/$TOOLCHAIN/bin:$PATH
cd arm-trusted-firmware-sunxi-mainline/v2.2
#
export CROSS_COMPILE=aarch64-none-linux-gnu-
make PLAT=sun50i_h6 DEBUG=1 bl31

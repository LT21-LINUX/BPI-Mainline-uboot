#!/bin/bash
TOPDIR=`pwd`
TOOLCHAIN=gcc-linaro-6.4.1-2017.11-x86_64_aarch64-linux-gnu
export PATH=$TOPDIR/$TOOLCHAIN/bin:$PATH
cd arm-trusted-firmware/sunxi
./bpi-sunxi64.sh

cd $TOPDIR
(./build_atf_a64.sh)
(./build_atf_a64_v2.2.sh)
(./build_atf_h616.sh)
(./build_atf_h6.sh)
(./build_atf_h6_v2.2.sh)

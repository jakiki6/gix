#!/bin/bash

TARGET="x86_64-elf"
GCC_VERSION="12.2.0"
BINUTILS_VERSION="2.39"
MPFR_VERSION="${MPFR_VERSION}"
GMP_VERSION="${GMP_VERSION}"
MPC_VERSION="${MPC_VERSION}"

cd $(dirname "$(readlink -f "$0")")

mkdir build
cd build

wget https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.xz && tar fx gcc-${GCC_VERSION}.tar.xz
wget https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.xz && tar fx binutils-${BINUTILS_VERSION}.tar.xz
wget https://ftp.gnu.org/gnu/mpfr/mpfr-${MPFR_VERSION}.tar.xz && tar fx mpfr-${MPFR_VERSION}.tar.xz
wget https://ftp.gnu.org/gnu/gmp/gmp-${GMP_VERSION}.tar.xz && tar fx gmp-${GMP_VERSION}.tar.xz
wget https://ftp.gnu.org/gnu/mpc/mpc-${MPC_VERSION}.tar.gz && tar fx mpc-${MPC_VERSION}.tar.gz

cd gcc-${GCC_VERSION}
ln -s ../mpfr-${MPFR_VERSION} mpfr
ln -s ../gmp-${GMP_VERSION} gmp
ln -s ../mpc-${MPC_VERSION} mpc
cd ..

mkdir ../cross
export PREFIX=$(pwd)/../cross
export PATH=$PEFIX/bin:$PATH

mkdir build-binutils
cd build-binutils
../binutils-${BINUTILS_VERSION}/configure --prefix=$PREFIX --target=$TARGET --disable-multilib
make -j $(nproc)
make install
cd ..

mkdir build-gcc
cd build-gcc
../gcc-${GCC_VERSION}/configure --prefix=$PREFIX --target=$TARGET --enable-languages=c --disable-multilib
make -j $(nproc) all-gcc
make install-gcc
make -j $(nproc) all-target-libgcc
make install-target-libgcc
cd ..


cd ../../thirdparty/limine
make
cp limine-deploy $PREFIX/bin/

PROJECT_DIR=`pwd`
PREFIX=$PROJECT_DIR/local/
BINUTILS_VERSION=2.26
GCC_VERSION=6.1.0

export PATH="$PREFIX/bin:$PATH"

mkdir -p build/cross/gcc/
cd build/cross/gcc/

wget ftp://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz
wget ftp://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz

tar zxf binutils-${BINUTILS_VERSION}.tar.gz
tar zxf gcc-${GCC_VERSION}.tar.gz

cd binutils-${BINUTILS_VERSION}/
mkdir build
cd build
../configure --prefix=$PREFIX --target=i686-elf --with-sysroot --disable-nls --disable-werror
make -j4
make install
cd ..

mkdir build-x64
cd build-x64
../configure --prefix=$PREFIX --target=x86_64-elf --with-sysroot --disable-nls --disable-werror
make -j4
make install
cd ..

cd ..
cd gcc-${GCC_VERSION}/

mkdir build
cd build
../configure --target=i686-elf --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers

make -j4 all-gcc
make -j4 all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..

mkdir build-x64
cd build-x64
../configure --target=x86_64-elf --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
make -j4 all-gcc
make -j4 all-target-libgcc
make install-gcc
make install-target-libgcc

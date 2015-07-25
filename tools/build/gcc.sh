PROJECT_DIR=`pwd`
PREFIX=$PROJECT_DIR/local/

export PATH="$PREFIX/bin:$PATH"

mkdir -p build/cross/gcc/
cd build/cross/gcc/

wget ftp://ftp.gnu.org/gnu/binutils/binutils-2.25.tar.gz
wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.9.3/gcc-4.9.3.tar.gz

tar zxf binutils-2.25.tar.gz
tar zxf gcc-4.9.3.tar.gz

cd binutils-2.25/
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
cd gcc-4.9.3/

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

PROJECT_DIR=`pwd`

mkdir -p build/cross/rustc
cd build/cross/rustc/

wget https://static.rust-lang.org/dist/rustc-nightly-src.tar.gz
tar zxf rustc-nightly-src.tar.gz
cd rustc-nightly
./configure --prefix=$PROJECT_DIR/local/
make
make install

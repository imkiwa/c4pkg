#!/system/bin/bash

source $(dirname $(readlink -f $0))/common.sh

mkdir -p build
cd build

cmake -DCMAKE_INSTALL_PREFIX=../pkgfiles/data ..
make -j4
make install

cd ..
tools/make-package.sh pkgfiles $PWD/c4pkg.zip

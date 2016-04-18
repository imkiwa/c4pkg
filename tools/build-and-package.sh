#!/system/bin/bash

source $(dirname $(readlink -f $0))/common.sh

tools/add-copyright.sh

mkdir -p build
cd build

cmake -DCMAKE_INSTALL_PREFIX=../pkgfiles/data ..
make -j4
make install

cd ..
tools/make-package.sh pkgfiles $PWD/pkgfiles/c4pkg.zip

#!/system/bin/bash

set -e

cd $(dirname $(readlink -f $0))
mkdir -p build
cd build

cmake -DCMAKE_INSTALL_PREFIX=../dist ..
make -j4
make install

cd ../dist
zip -r ../data.zip .
cd ..
zip c4pkg.zip data.zip manifest.json
rm -f data.zip

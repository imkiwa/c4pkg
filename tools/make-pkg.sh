#!/system/bin/bash

source $(dirname $(readlink -f $0))/common.sh

mkdir -p build
cd build

cmake -DCMAKE_INSTALL_PREFIX=../pkgfiles/data ..
make -j4
make install

cd ../pkgfiles/data
zip -r ../data.zip .
cd ..

checksum="$(sha1sum data.zip | awk '{print $1}')"
sed "s/<CHECKSUM>/$checksum/g" manifest.json.in > manifest.json
zip ../c4pkg.zip data.zip manifest.json
rm -f data.zip manifest.json

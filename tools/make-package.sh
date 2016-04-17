#!/system/bin/bash

MANIFEST_IN="manifest.json.in"
MANIFEST="manifest.json"
DATA="data"
DATAZIP="data.zip"

function usage()
{
  echo "Usage: $0 <DIR> <FILE>"
  echo "  Build FILE package from DIR"
}

function build-package()
{
  local root="$1"
  local name="$2"
  
  cd "$root" || return 1
  
  if [[ ! -f "$MANIFEST_IN" || ! -d "$DATA" ]];then
    echo "Neither $MANIFEST_IN nor $DATA was found in $root"
    return 1
  fi
  
  cd "$DATA"
  zip -r "../$DATAZIP" . || {
    echo "Failed to create $DATAZIP file"
    return 1
  }
  
  cd ..
  local hash="$(sha1sum $DATAZIP | awk '{print $1}')"
  sed "s/<CHECKSUM>/$hash/g" "$MANIFEST_IN" > "$MANIFEST"
  
  zip "$name" "$DATAZIP" "$MANIFEST" || {
    echo "Failed to create $name"
    return 1
  }
  
  rm "$MANIFEST" "$DATAZIP"
}

if [[ ! "$1" ]];then
  usage
  exit 1
fi

build-package "$1" "$2"

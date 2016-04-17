#!/system/bin/bash

source $(dirname $(readlink -f $0))/common.sh

COPYRIGHT='/**
 * Copyright (C) 2016  apollo-opensource
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
'

function process-file()
{
  local f="$1"
  
  local fl="$(head -n1 $f)"
  if [[ "$fl" == "/**" ]];then
    return
  fi
  
  echo "=> $f"
  echo -e "$COPYRIGHT\n" > "$f.tmp"
  cat "$f" >> "$f.tmp"
  mv "$f.tmp" "$f"
}

function add-copyright()
{
  while [[ "$1" ]];do
    local dir="$1"; shift
    for f in $(find "$dir" -name "*.c" -o -name "*.h");do
      process-file "$f"
    done
  done
}

add-copyright \
    deps/c4pkg* \
    src \
    include

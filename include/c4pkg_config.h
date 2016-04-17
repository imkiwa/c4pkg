/**
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


#pragma once

#include "c4pkg_version.h"

#define C4DROID_PKG_NAME "com.n0n3m4.droidc"
#define C4DROID_DATA "/data/data/" C4DROID_PKG_NAME

#define C4PKG_DATA C4DROID_DATA "/c4pkg"

#define C4PKG_LIST_PATH C4PKG_DATA "/lists"
#define C4PKG_PKG_PATH C4PKG_DATA "/packages"

#define C4PKG_PKG_INCLUDE_PATH C4PKG_PKG_PATH "/include"
#define C4PKG_PKG_LIB_PATH C4PKG_PKG_PATH "/lib"
#define C4PKG_PKG_BIN_PATH C4PKG_PKG_PATH "/bin"
#define C4PKG_PKG_DOCS_PATH C4PKG_PKG_PATH "/docs"

#define C4PKG_DATA_ZIP "data.zip"
#define C4PKG_MANIFEST "manifest.json"
#define C4PKG_LIST_FILE "files.list"

#define C4PKG_MANIFEST_NAME  "package"
#define C4PKG_MANIFEST_DESC  "description"
#define C4PKG_MANIFEST_MAJOR "major-version"
#define C4PKG_MANIFEST_MINOR "minor-version"
#define C4PKG_MANIFEST_PATCH "patch-version"
#define C4PKG_MANIFEST_DEPS  "dependencies"
#define C4PKG_MANIFEST_CHECKSUM "checksum"

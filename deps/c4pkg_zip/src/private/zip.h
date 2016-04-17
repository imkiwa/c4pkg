/**
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef PRIVATE_H
#define PRIVATE_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Zipentry {
    unsigned long fileNameLength;
    const unsigned char* fileName;
    unsigned short compressionMethod;
    unsigned int uncompressedSize;
    unsigned int compressedSize;
    const unsigned char* data;
    
    struct Zipentry* next;
} Zipentry;

typedef struct Zipfile
{
    const unsigned char *buf;
    ssize_t bufsize;

    // Central directory
    unsigned short  disknum;            //mDiskNumber;
    unsigned short  diskWithCentralDir; //mDiskWithCentralDir;
    unsigned short  entryCount;         //mNumEntries;
    unsigned short  totalEntryCount;    //mTotalNumEntries;
    unsigned int    centralDirSize;     //mCentralDirSize;
    unsigned int    centralDirOffest;  // offset from first disk  //mCentralDirOffset;
    unsigned short  commentLen;         //mCommentLen;
    const unsigned char*  comment;            //mComment;

    Zipentry* entries;
} Zipfile;

int read_central_dir(Zipfile* file);

unsigned int read_le_int(const unsigned char* buf);
unsigned int read_le_short(const unsigned char* buf);

#endif // PRIVATE_H


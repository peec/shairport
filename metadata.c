/*
 * Metadate structure and utility methods. This file is part of Shairport.
 * Copyright (c) Benjamin Maus 2013
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "metadata.h"

metadata player_meta;

void  metadata_set(char** field, const char* value) {
    if (*field)
      free(*field);
    *field = strdup(value);
}

FILE* metadata_open(const char* mode) {
  FILE* fh = NULL;
  if (config.cover_dir) {
    const char fn[] = "now_playing.txt";
    size_t pl = strlen(config.cover_dir) + 1 + strlen(fn);
    
    char* path = malloc(pl+1);
    snprintf(path, pl+1, "%s/%s", config.cover_dir, fn);
    
    fh = fopen(path, mode);
    free(path);
  }
  return fh;
}

void metadata_write(const char* dir) {
  FILE* fh = metadata_open("w");
  if (fh) {
    fprintf(fh, "%s\n", player_meta.artist);
    fprintf(fh, "%s\n", player_meta.title);
    fprintf(fh, "%s\n", player_meta.album);
    fprintf(fh, "%s\n", player_meta.artwork);
    fprintf(fh, "%s\n", player_meta.genre);
    fprintf(fh, "%s\n", (player_meta.comment == NULL) ? "" : player_meta.comment);
    fclose(fh);
  }
}

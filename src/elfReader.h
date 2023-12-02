/**
 * File              : elfReader.h
 * Author            : guochuliang <2797366715@qq.com>
 * Date              : 25.11.2023
 * Last Modified Date: 25.11.2023
 * Last Modified By  : guochuliang <2797366715@qq.com>
 */
#ifndef _ELF_PATCH_H
#define _ELF_PATCH_H

#include <elf.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "log.h"

int checkFile(char *elfPath);
int readElf(char *elfPath);
int read32elf(FILE *fp);
int read64elf(FILE *fp);

#endif

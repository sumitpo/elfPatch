/**
 * File              : main.c
 * Author            : guochuliang <2797366715@qq.com>
 * Date              : 24.11.2023
 * Last Modified Date: 24.11.2023
 * Last Modified By  : guochuliang <2797366715@qq.com>
 */
#include <stdio.h>

#include "elfReader.h"
#include "log.h"
int
usage(char *binFile) {
  printf("%s [stripped binary]\n", binFile);
  return 0;
}
int
main(int argc, char *argv[]) {
  log_set_level(LOG_DEBUG);
  if (argc < 2) {
    log_error("no binary file provided");
    usage(argv[0]);
    return 1;
  }
  log_info("welcome to the elf patcher");
  readElf(argv[1]);
  return 0;
}

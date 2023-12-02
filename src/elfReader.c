/**
 * File              : elfReader.c
 * Author            : guochuliang <2797366715@qq.com>
 * Date              : 15.11.2023
 * Last Modified Date: 25.11.2023
 * Last Modified By  : guochuliang <2797366715@qq.com>
 */
#include "elfReader.h"

char *
type2str(uint32_t sh_type) {
  char *ret = NULL;
  switch (sh_type) {
    case SHT_NULL: ret = "null"; break;
    case SHT_PROGBITS: ret = "progbits"; break;
    case SHT_SYMTAB: ret = "symtab"; break;
    case SHT_STRTAB: ret = "strtab"; break;
    case SHT_RELA: ret = "rela"; break;
    case SHT_HASH: ret = "hash"; break;
    case SHT_DYNAMIC: ret = "dynamic"; break;
    case SHT_NOTE: ret = "note"; break;
    case SHT_NOBITS: ret = "nobits"; break;
    case SHT_REL: ret = "rel"; break;
    case SHT_SHLIB: ret = "shlib"; break;
    case SHT_DYNSYM: ret = "dynsym"; break;
    case SHT_LOPROC: ret = "loproc"; break;
    case SHT_LOUSER: ret = "louser"; break;
    case SHT_HIUSER: ret = "hiuser"; break;
  }
  return ret;
}

int
printHdr32(Elf32_Ehdr *hdr) {
  printf("entry is %X\n", hdr->e_entry);
  log_info("not implemented");
  return 0;
}
int
printHdr64(Elf64_Ehdr *hdr) {
  printf("entry is %lX\n", hdr->e_entry);
  log_info("not implemented");
  return 0;
}

int
print64SectionHdr(Elf64_Shdr *sTab, uint16_t shnum) {
  printf(
      "name     type     flags    addr   offset     size     link     info"
      "    addralign  entsize\n");
  for (uint16_t i = 0; i < shnum; i++) {
    printf("%4x %8s %8lX %8lX %8lX %8X %8X %8X %8X %8X\n", sTab->sh_name,
           type2str(sTab->sh_type), sTab->sh_flags, sTab->sh_addr,
           sTab->sh_offset, sTab->sh_size, sTab->sh_link, sTab->sh_info,
           sTab->sh_addralign, sTab->sh_entsize);
    sTab += 1;
  }
  return 0;
}
int
read32elf(FILE *fp) {
  Elf32_Ehdr hdr;
  fread(&hdr, sizeof(hdr), 1, fp);
  printHdr32(&hdr);
  return 0;
}

int
read64elf(FILE *fp) {
  Elf64_Ehdr hdr;
  fread(&hdr, sizeof(hdr), 1, fp);
  printHdr64(&hdr);

  Elf64_Phdr *phdrp = (Elf64_Phdr *)malloc(hdr.e_phentsize * hdr.e_phnum);
  Elf64_Shdr *shdrp = (Elf64_Shdr *)malloc(hdr.e_shentsize * hdr.e_shnum);

  fseek(fp, hdr.e_phoff, SEEK_SET);
  // fread(phdrp, sizeof(Elf64_Phdr), hdr.e_phnum, fp);
  fread(phdrp, hdr.e_phentsize, hdr.e_phnum, fp);

  fseek(fp, hdr.e_shoff, SEEK_SET);
  // fread(shdrp, sizeof(Elf64_Shdr), hdr.e_shnum, fp);
  printf("the section hdr count %d\n", hdr.e_shnum);
  printf("the section hdr size %d\n", hdr.e_shentsize);
  fread(shdrp, hdr.e_shentsize, hdr.e_shnum, fp);

  print64SectionHdr(shdrp, hdr.e_shnum);

  free(shdrp);
  free(phdrp);
  return 0;
}

int
readElf(char *elfPath) {
  FILE *fp = fopen(elfPath, "rb");
  if (NULL == fp) {
    log_error("fail to open file [%s]: %s", elfPath, strerror(errno));
    return 1;
  }

  unsigned char e_ident[EI_NIDENT];
  log_debug("in");
  fread(e_ident, sizeof(unsigned char), EI_NIDENT, fp);
  if (e_ident[0] == 0x7f && e_ident[1] == 'E' && e_ident[2] == 'L' &&
      e_ident[3] == 'F') {
    log_debug("%s is a elf file. [checked by elf magic]", elfPath);
  } else {
    log_error("%s is not a elf file. [checked by elf magic]", elfPath);
    return 1;
  }

  rewind(fp);

  int bit = 0;
  if (e_ident[4] == ELFCLASS32) {
    log_info("32 bit elf binary");
    read32elf(fp);
  } else if (e_ident[4] == ELFCLASS64) {
    log_info("64 bit elf binary");
    read64elf(fp);
  } else {
    log_error("invalid architecture");
    return 1;
  }

  return 0;
}

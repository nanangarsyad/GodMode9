#pragma once

#include "common.h"

#define NCCH_MEDIA_UNIT 0x200

#define NCCH_EXTHDR_SIZE 0x800 // NCCH header says 0x400, which is not the full thing
#define NCCH_EXTHDR_OFFSET 0x200

#define NCCH_ENCRYPTED(ncch) (!(ncch->flags[7] & 0x04))

// see: https://www.3dbrew.org/wiki/NCCH/Extended_Header
// very limited, contains only required stuff
typedef struct {
    char name[8];
    u8   reserved[0x5];
    u8   flag; // bit 1 for SD
    u32  remaster_version;
    u8   sci_data[0x30];
    u8   dependencies[0x180];
    u8   sys_info[0x40];
    u8   aci_data[0x200];
    u8   signature[0x100];
    u8   public_key[0x100];
    u8   aci_limit_data[0x200];
} __attribute__((packed)) NcchExtHeader;

// see: https://www.3dbrew.org/wiki/NCCH#NCCH_Header
typedef struct {
    u8  signature[0x100];
    u8  magic[0x4];
    u32 size;
    u64 partitionId;
    u16 makercode;
    u16 version;
    u8  hash_seed[0x4];
    u64 programId;
    u8  reserved0[0x10];
    u8  hash_logo[0x20];
    char productcode[0x10];
    u8  hash_exthdr[0x20];
    u32 size_exthdr;
    u8  reserved1[0x4];
    u8  flags[0x8];
    u32 offset_plain;
    u32 size_plain;
    u32 offset_logo;
    u32 size_logo;
    u32 offset_exefs;
    u32 size_exefs;
    u32 size_exefs_hash;
    u8  reserved2[0x4];
    u32 offset_romfs;
    u32 size_romfs;
    u32 size_romfs_hash;
    u8  reserved3[0x4];
    u8  hash_exefs[0x20];
    u8  hash_romfs[0x20];
} __attribute__((packed)) NcchHeader;

u32 ValidateNcchHeader(NcchHeader* header);
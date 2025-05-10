#ifndef MMAP_H
#define MMAP_H

#include "file.h"
#include "param.h"
#include "proc.h"
#include "types.h"

#define MMAPBASE 0x40000000

struct mmap_area
{
    struct file *f;
    uint64 addr;
    int length;
    int offset;
    int prot;
    int flags;
    struct proc *p;
};

extern struct mmap_area mmap_area_Arr[64];

#endif
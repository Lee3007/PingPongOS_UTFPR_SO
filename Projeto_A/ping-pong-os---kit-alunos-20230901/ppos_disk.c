#include "ppos_disk.h"

int disk_mgr_init (int *numBlocks, int *blockSize){
    return 2;
}

int disk_block_read (int block, void* buffer){
    return 1;
}

int disk_block_write (int block, void* buffer){
    return 0;
}
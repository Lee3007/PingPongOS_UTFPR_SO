#include "ppos_disk.h"
#include "disk.h"
#include "ppos-core-globals.h"
#include "ppos.h"

task_t **disk_queue;

typedef struct disk_task {
    int val;
    struct disk_task * next;
} disk_task_t;

int disk_mgr_init (int *numBlocks, int *blockSize){
    return 0;
}

int disk_block_read (int block, void* buffer){
    int read_value = disk_cmd(DISK_CMD_READ, block, buffer); 

    disk_task_t* a = (disk_task_t*) malloc(sizeof(disk_task_t));

    task_suspend(taskExec, disk_queue);

    task_yield();

    return read_value;
}

int disk_block_write (int block, void* buffer){

    int write_value = disk_cmd(DISK_CMD_WRITE, block, buffer);

    task_suspend(taskExec, disk_queue);

    task_yield();

    return write_value;
}
#include "ppos_disk.h"
#include "disk.h"
#include "ppos-core-globals.h"
#include "ppos.h"

task_t *disk_queue;

typedef struct disk_task
{
    task_t task;
    int block;
    struct disk_task *next;
} disk_task_t;

int disk_mgr_init(int *numBlocks, int *blockSize)
{
    return 0;
}

int disk_block_read(int block, void *buffer)
{
    int read_status = disk_cmd(DISK_CMD_READ, block, buffer);

    disk_task_t *task = (disk_task_t *)malloc(sizeof(disk_task_t));

    task->task = taskExec;
    task->block = block;

    insert_disk_task(task);

    task_suspend(taskExec, disk_queue);

    task_yield();

    return read_status;
}

int disk_block_write(int block, void *buffer)
{

    int write_status = disk_cmd(DISK_CMD_WRITE, block, buffer);

    disk_task_t *task = (disk_task_t *)malloc(sizeof(disk_task_t));

    task->task = taskExec;
    task->block = block;

    insert_disk_task(task);

    task_suspend(taskExec, disk_queue);

    task_yield();

    return write_status;
}

void insert_disk_task(disk_task_t *task)
{
}

void escalonator_fcfs() // ja venho
{
    if (disk_queue != NULL)
    {
        task_t *task_to_resume = disk_queue;
        disk_queue = disk_queue->next;
        task_resume(task_to_resume);
    }
}

void escalonator_sstf()
{
}

void escalonator_cscan()
{
}
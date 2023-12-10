#include "ppos_disk.h"
#include "disk.h"
#include "disk.c"
#include "ppos-core-aux.c"

// Disco
disk_t disk;

// Queue de tarefas do disco após leitura/escrita
task_t *disk_queue;

// Tarefa gerenciadora de disco 
task_t disk_manager_task;
// Lista encadeada de tarefas do disco
typedef struct disk_task
{
    task_t *task;
    int block;
    struct disk_task *next;
} disk_task_t;

int disk_mgr_init(int *numBlocks, int *blockSize)
{

    if (disk_cmd(DISK_CMD_INIT, NULL, NULL) < 0)
        return -1;

    disk.numblocks = disk_cmd(DISK_CMD_DISKSIZE, NULL, NULL);

    disk.blocksize = disk_cmd(DISK_CMD_BLOCKSIZE, NULL, NULL);

    if (disk.blocksize < 0 || disk.blocksize < 0)
        return -1;

    task_create(&disk_manager_task, disk_mgr_body, NULL);
    task_setprio(&disk_manager_task, 0);
    task_set_eet(&disk_manager_task, INT_MAX - 20);

    printf("disk_mgr_init Succeed!");

    return 0;
}

void disk_mgr_body()
{
    while (1)
    {
        

        

        
    }
}

int disk_block_read(int block, void *buffer)
{
    int read_status = disk_cmd(DISK_CMD_READ, block, buffer);

    insert_disk_task(taskExec, block);

    return read_status;
}

int disk_block_write(int block, void *buffer)
{

    int write_status = disk_cmd(DISK_CMD_WRITE, block, buffer);

    insert_disk_task(taskExec, block);

    return write_status;
}

void insert_disk_task(task_t *task, int block)
{
    disk_task_t *disk_task = (disk_task_t *)malloc(sizeof(disk_task_t));

    disk_task->task = task;
    disk_task->block = block;

    task_suspend(task, disk_queue);

    task_yield();
}

void escalonator_fcfs()
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
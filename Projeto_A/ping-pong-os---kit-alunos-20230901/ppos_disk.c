#include "ppos_disk.h"
#include "disk.h"
#include "disk.c"
#include "ppos-core-aux.c"
#include <stdbool.h>

// Disco
disk_t disk;

// Tarefa gerenciadora de disco 
task_t disk_manager_task;
// Lista encadeada de tarefas do disco
typedef struct disk_task
{
    task_t *task;
    int block;
    void *buffer;
    int type; // 0: read, 1: write
    struct disk_task *next;
} disk_task_t;

// Queue de tarefas do disco após leitura/escrita
disk_task_t *disk_queue;

void disk_mgr_body()
{
    while (true)
    { 
        if(disk_cmd(DISK_CMD_STATUS, 0, NULL) == 1 && disk_queue != NULL){
            
            disk_task_t *current_task = escalonator_fcfs();
            if(current_task->type == 1){
                disk_cmd(DISK_CMD_WRITE, current_task->block, current_task->buffer);
            }    
            else if(current_task->type == 0){   
                disk_cmd(DISK_CMD_READ, current_task->block, current_task->buffer);
            }
            
            task_suspend(&disk_manager_task, NULL);
            task_yield();

        }
    }
}

int disk_mgr_init(int *numBlocks, int *blockSize)
{

    if (disk_cmd(DISK_CMD_INIT, NULL, NULL) < 0)
        return -1;

    disk.numblocks = disk_cmd(DISK_CMD_DISKSIZE, NULL, NULL);
    disk.blocksize = disk_cmd(DISK_CMD_BLOCKSIZE, NULL, NULL);

    if (disk.blocksize < 0 || disk.blocksize < 0)
        return -1;

    task_create(&disk_manager_task, disk_mgr_body, NULL);
    task_set_eet(&disk_manager_task, INT_MAX - 1);
    signal(SIGUSR1, signal_handler_disk); 

    printf("disk_mgr_init Succeed!");

    return 0;
}

void signal_handler_disk()
{
    task_resume(&disk_manager_task);
}

int disk_block_read(int block, void *buffer)
{
    if(disk_cmd(DISK_CMD_STATUS, block, buffer) == 1){
        task_suspend(taskExec, disk_queue);
        return disk_cmd(DISK_CMD_READ, block, buffer);
    }else{
        insert_disk_task(taskExec, block, buffer, 0);
    }

    return -1;
}

int disk_block_write(int block, void *buffer)
{
    if(disk_cmd(DISK_CMD_STATUS, block, buffer) == 1){
        task_suspend(taskExec, disk_queue);
        return disk_cmd(DISK_CMD_WRITE, block, buffer);
    }else{
        insert_disk_task(taskExec, block, buffer, 1);
    }

    return -1;
}

void insert_disk_task(task_t *task, int block, void *buffer, int type)
{
    disk_task_t *disk_task = (disk_task_t *)malloc(sizeof(disk_task_t));

    disk_task->task = task;
    disk_task->block = block;
    disk_task->buffer = buffer;
    disk_task->type = type;

    task_suspend(task, NULL);

    task_yield();
}

disk_task_t *escalonator_fcfs()
{
    if (disk_queue != NULL && disk_queue->task != NULL)
    {
        disk_task_t *task_to_exec = disk_queue;
        disk_queue = disk_queue->next;
        return task_to_exec;
        // task_resume(task_to_exec);
    }
}

void escalonator_sstf()
{
}

void escalonator_cscan()
{
}
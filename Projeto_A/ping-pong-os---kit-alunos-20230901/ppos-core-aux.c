#include "ppos.h"
#include "ppos-core-globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
// ****************************************************************************
// Coloque aqui as suas modificações, p.ex. includes, defines variáveis,
// estruturas e funções

struct sigaction action;
struct itimerval timer;
const int quantum = 20;
int currentTaskRemainingTicks = quantum;

void task_set_eet(task_t *task, int et)
{
    if (task == NULL)
        task = taskExec;
    task->estimatedExecTime = et;
}

int task_get_eet(task_t *task)
{
    if (task == NULL)
        task = taskExec;
    return task->estimatedExecTime;
}

int task_get_ret(task_t *task)
{
    if (task == NULL)
        task = taskExec;
    return task->estimatedExecTime - task->executingTime;
}

void tick_handler(int signum)
{
    printf("Recebi o sinal %d\n", signum);

    if (taskExec->id == taskMain->id || taskExec->id == taskDisp->id)
        return;

    if (currentTaskRemainingTicks > 0)
    {
        taskExec->executingTime++;
        currentTaskRemainingTicks--;
    }
    else
    {
        task_yield();
    }
}

void task_setprio(task_t *task, int prio) {}

int task_getprio(task_t *task) { return 0; }

// ****************************************************************************

void before_ppos_init()
{
    // put your customization here
#ifdef DEBUG
    printf("\ninit - BEFORE");
#endif
}

void after_ppos_init()
{
    action.sa_handler = tick_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGALRM, &action, 0) < 0)
    {
        perror("Erro em sigaction: ");
        exit(1);
    }
    timer.it_value.tv_usec = 1000;    // primeiro disparo, em micro-segundos
    timer.it_interval.tv_usec = 1000; // disparos subsequentes, em micro-segundos
    if (setitimer(ITIMER_REAL, &timer, 0) < 0)
    {
        perror("Erro em setitimer: ");
        exit(1);
    }
    // put your customization here
#ifdef DEBUG
    printf("\ninit - AFTER");
#endif
}

void before_task_create(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_create - BEFORE - [%d]", task->id);
#endif
}

void after_task_create(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_create - AFTER - [%d]", task->id);
#endif
}

void before_task_exit()
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_exit - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_exit()
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_exit - AFTER- [%d]", taskExec->id);
#endif
}

void before_task_switch(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_switch - BEFORE - [%d -> %d]", taskExec->id, task->id);
#endif
}

void after_task_switch(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_switch - AFTER - [%d -> %d]", taskExec->id, task->id);
#endif
}

void before_task_yield()
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_yield - BEFORE - [%d]", taskExec->id);
#endif
}
void after_task_yield()
{
    // put your customization here
    currentTaskRemainingTicks = quantum;
#ifdef DEBUG
    printf("\ntask_yield - AFTER - [%d]", taskExec->id);
#endif
}

void before_task_suspend(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_suspend - BEFORE - [%d]", task->id);
#endif
}

void after_task_suspend(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_suspend - AFTER - [%d]", task->id);
#endif
}

void before_task_resume(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_resume - BEFORE - [%d]", task->id);
#endif
}

void after_task_resume(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_resume - AFTER - [%d]", task->id);
#endif
}

void before_task_sleep()
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_sleep - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_sleep()
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_sleep - AFTER - [%d]", taskExec->id);
#endif
}

int before_task_join(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_join - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_task_join(task_t *task)
{
    // put your customization here
#ifdef DEBUG
    printf("\ntask_join - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_create(semaphore_t *s, int value)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_create(semaphore_t *s, int value)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_down(semaphore_t *s)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_down - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_down(semaphore_t *s)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_down - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_up(semaphore_t *s)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_up - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_up(semaphore_t *s)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_up - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_destroy(semaphore_t *s)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_destroy(semaphore_t *s)
{
    // put your customization here
#ifdef DEBUG
    printf("\nsem_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_create(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_create(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_lock(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_lock - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_lock(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_lock - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_unlock(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_unlock - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_unlock(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_unlock - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_destroy(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_destroy(mutex_t *m)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_create(barrier_t *b, int N)
{
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_create(barrier_t *b, int N)
{
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_join(barrier_t *b)
{
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_join - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_join(barrier_t *b)
{
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_join - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_destroy(barrier_t *b)
{
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_destroy(barrier_t *b)
{
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_create(mqueue_t *queue, int max, int size)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_create(mqueue_t *queue, int max, int size)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_send(mqueue_t *queue, void *msg)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_send - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_send(mqueue_t *queue, void *msg)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_send - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_recv(mqueue_t *queue, void *msg)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_recv - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_recv(mqueue_t *queue, void *msg)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_recv - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_destroy(mqueue_t *queue)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_destroy(mqueue_t *queue)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_msgs(mqueue_t *queue)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_msgs - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_msgs(mqueue_t *queue)
{
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_msgs - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

task_t *scheduler()
{
    if (readyQueue == NULL)
        return NULL;

    // Fila é circular, então marcamos o inicial e se o inicial=proximo paramos
    // Percorre a lista e encontra o que possui menor ret
    int lowestRET = __INT_MAX__;
    int currentRET;

    task_t *selectedTask = NULL;
    task_t *taskIterator = readyQueue;

    do
    {
        currentRET = task_get_ret(taskIterator);
        if (currentRET < lowestRET)
        {
            lowestRET = currentRET;
            selectedTask = taskIterator;
        }
        taskIterator = taskIterator->next;
    } while (taskIterator != readyQueue);

    return selectedTask;
}
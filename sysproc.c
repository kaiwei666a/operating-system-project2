#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  /*
  if(growproc(n) < 0)
    return -1;
  */
 myproc()->sz += n;
  return addr;
}


int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_job_position(void) {
  int pid;
  if (argint(0, &pid) < 0)  // Get PID argument
      return -1;
  return job_position(pid);  // Call function in `proc.c`
}

int
sys_get_creation_time(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return get_creation_time(pid);
}

int
sys_get_start_time(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return get_start_time(pid);
}

int
sys_get_completion_time(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return get_completion_time(pid);
}

int
sys_get_total_run_time(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return get_total_run_time(pid);
}

int
sys_get_total_ready_time(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return get_total_ready_time(pid);
}

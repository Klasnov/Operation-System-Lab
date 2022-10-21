#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#define calNum 31

char *sysNam[calNum] = {
    "sys_fork",
    "sys_exit",
    "sys_wait",
    "sys_pipe",
    "sys_read",
    "sys_kill",
    "sys_exec",
    "sys_fstat",
    "sys_chdir",
    "sys_dup",
    "sys_getpid",
    "sys_sbrk",
    "sys_sleep",
    "sys_uptime",
    "sys_open",
    "sys_write",
    "sys_mknod",
    "sys_unlink",
    "sys_link",
    "sys_mkdir",
    "sys_close",
    "sys_trace",
    "sys_sysinfo"};

uint64 sys_exit(void)
{
  int n;
  if (argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0; // not reached
}

uint64 sys_getpid(void)
{
  return myproc()->pid;
}

uint64 sys_fork(void)
{
  return fork();
}

uint64 sys_wait(void)
{
  uint64 p;
  if (argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64 sys_sbrk(void)
{
  int addr;
  int n;
  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64 sys_sleep(void)
{
  int n;
  uint ticks0;
  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64 sys_kill(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64 sys_uptime(void)
{
  uint xticks;
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Trace the specified system call
uint64 sys_trace(void)
{
  int n;
  int sys_min = 1 << 1, sys_max = 1 << 30;
  unsigned int sys_all = ((unsigned int) (1 << 31)) - 1;
  argint(0, &n);
  struct proc *p = myproc();
  p->traced = 1;
  if (((n >= sys_min) && (n <= sys_max)) || (n == sys_all))
  {
    if (n == sys_all)
    {
      for (int i = 0; i < calNum; i++)
      {
        p->mask[i] = 1;
      }
    }
    else
    {
      int cal = n, cnt = 0;
      while (cal != 1)
      {
        cal >>= 1;
        cnt++;
      }
      p->mask[cnt - 1] = 1;
    }
    return 0;
  }
  else
  {
    return -1;
  }
}

// Get the system information
uint64 sys_sysinfo(void)
{
  
}

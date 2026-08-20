#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/fdtable.h>
struct mystat
{
    pid_t pid;
    pid_t ppid;
    int stat;
    int policy;
    long utime;
    long stime;
    long startime;
    unsigned long min_flt;
    unsigned long maj_flt;
    long open_files;
}
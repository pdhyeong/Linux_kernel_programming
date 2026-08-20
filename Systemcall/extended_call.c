#include <linux/unistd.h>>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage long sys_getsysinfo(void)
{
    printk("PID : %d\n",current->pid);
    printk("TGID : %d\n",current->tgid);
    printk("PPID : %d\n",current->parent->pid);
    printk("STATE : %d\n",current->state);
    printk("PRIORITY : %d\n",current->prio);
    printk("POLICY : %d\n",current->policy);
    printk("Numver of MAJOR FAULT : %d\n",current->maj_flt)
    printk("Numver of MINOR FAULT : %d\n",current->min_flt)
    return 0;
}
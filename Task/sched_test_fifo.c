#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <linux/sched.h>
#include <sys/syscall.h>

#ifndef __NR_sched_setattr
#define __NR_sched_setattr 314
#endif

struct sched_attr {
	uint32_t size;

	uint32_t sched_policy;
	uint64_t sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	uint32_t sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	uint32_t sched_priority;

	/* SCHED_DEADLINE */
	uint64_t sched_runtime;
	uint64_t sched_deadline;
	uint64_t sched_period;
};

int sched_setattr(pid_t pid,const struct sched_attr *attr,uint32_t flags)
{
    return syscall(__NR_sched_setattr, pid, attr, flags);
}

void check_policy(pid_t pid)
{
    int policy;


    policy = sched_getscheduler(pid);
    switch(policy)
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;

        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        
        default:
            printf("eeeeeee\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    struct sched_attr attr = {
        .size = sizeof(attr),
        .sched_policy = SCHED_FIFO,
        .sched_priority = 10,
        .sched_runtime = 0,
        .sched_period = 0,
        .sched_deadline = 0
    };

    check_policy(getpid());

    int ret_val;

    printf("change to SCEHD_FIFO\n");

    ret_val = sched_setattr(getpid(), &attr, 0);

    if (ret_val) {
        perror("Sched_setattr error\n");
        return -1;
    }

    check_policy(getpid());

    return 0;
}
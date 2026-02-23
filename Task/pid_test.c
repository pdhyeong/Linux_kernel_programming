#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>

#define STACK_SIZE (1024 * 1024)

int sub_func_b(void *arg) {
    long tid = syscall(SYS_gettid);
    printf("Child  - TGID(%d) PID(TID:%ld): %s\n", getpid(), tid, (char *)arg);
    sleep(2);
    return 0;
}

int main() {
    char *stack_a = malloc(STACK_SIZE);
    char *stack_b = malloc(STACK_SIZE);

    if (!stack_a || !stack_b) {
        perror("malloc");
        exit(1);
    }

    printf("Parent - TGID(%d) PID(TID:%ld)\n", getpid(), syscall(SYS_gettid));
    printf("-------------------------------------------\n");

    clone(sub_func_b, stack_a + STACK_SIZE, SIGCHLD, "Process (Not Shared)", NULL, NULL, NULL);

    clone(sub_func_b, stack_b + STACK_SIZE, 
          CLONE_VM | CLONE_THREAD | CLONE_SIGHAND | SIGCHLD, "Thread (Shared)", NULL, NULL, NULL);

    sleep(1);
    printf("-------------------------------------------\n");
    printf("After clone\n");

    free(stack_a);
    free(stack_b);

    return 0;
}
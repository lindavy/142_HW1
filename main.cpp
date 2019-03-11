#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <err.h>     // error
#include <unistd.h>  // chdir
#include "ChildProcess.h"

#define PATH_MAX 100

int main(int argc, char **argv)
{

    char *built_in_commands[3] = {"cd", "path", "exit"};

    int pid = fork();
    /*
     * Once fork() executes, the parent & child processes will be running concurrently
     * Cases:
     * 1. PID = -1 (Forking Error)
     * 2. PID = 0 (Child process still executing)
     * 3. PID > 0 (Parent Process, Fork Successful & Completed)
     */

    // Error
    if(pid < 0)
    {
        fprintf(stderr, "Forked Failed!\n");
        exit(-1);
    }
    // Child Process
    else if(pid == 0)
    {
        printf("child pid: %d\n", (int) getpid());
        exec();
    }
    // Parent Process
    else
    {
        int wait_child = wait(NULL); // wait for child to finish execution
        printf("parent pid: %d | child pid: %d\n", (int) getpid(), wait_child);
    }


}
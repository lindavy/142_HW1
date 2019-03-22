#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <err.h>     // error
#include <unistd.h>  // chdir
#include "Functions.h"

#define PATH_MAX 100
#define CWD_SIZE 512

/*
 * argc & argv are command line arguments
 * argc - argument count (default: 1 + no. of arguments)
 * argv - argument vector
 */
int main(int argc, char **argv)
{
    // Prologue
    char *buf; printf("Current Working Directory: %s\n", getcwd(buf, CWD_SIZE));
    printf("Parent PID: %i\n", getpid());

    int pid = fork(); // fork once execution command is ok
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
<<<<<<< HEAD
        printf("Fork Successful | Child PID: %d\n\n", (int) getpid());
        char *line = nullptr;
        size_t linesize = 0;
        ssize_t linelen;
        int i = 0;

        // Path
        char path_name[10][128]; // store 10 strings of size 128 each
        char *ptr = nullptr;
        char const *forward_slash = "/"; // char * isn't constant but the object "/" is, so you must define it as const

        // Execution
        int execv_ret; // check execv return value (-1 is error)

        // Redirect Output
        char const *redirect_arrow = ">";
        char *output_filename = nullptr;// {nullptr};
        bool read_arrow = false;

        printf("> ");
        while ((linelen = getline(&line, &linesize, stdin)) != -1)
        {
            // Built-in Commands
            if (strncmp("exit", line, 4) == 0)
            {
                exit(0);
            }
            else if (strncmp("cd", line, 2) == 0)
            {
                printf("entered cd\n");
            }
            else if (strncmp("path", line, 4) == 0)
            {
                ptr = std::strtok(line, " \n");
                while (ptr != nullptr &&  i < 10)
                {
                    ptr = std::strtok(nullptr, " \n"); // update ptr to ignore "path" command
                    snprintf(path_name[i], 511, "%s", ptr); // concatenates string to path_name
                    printf("Stored path %i: %s\n", i, path_name[i]);
                    i++;
                }
                i = 0; // reset counter
                printf("Stored all paths.\n");
            }
            else
            {
                /*
                char const *path1 = "/bin/ls";
                char * const instr[] = {"ls", "-l", nullptr};
                execv_ret = execv(path1, instr);
                printf("execv: %i", execv_ret);
                */

                // Store Instruction
                char *user_cmd[20];
                ptr = std::strtok(line, " \n");
                user_cmd[i++] = ptr;
                while (ptr != nullptr && i < 20)
                {
                    ptr = std::strtok(nullptr, " \n"); // update ptr
                    if (!strcmp(ptr, ">")) // if identical, it will return 0
                    {
                        ptr = std::strtok(nullptr, " \n");
                        output_filename = ptr;
                        read_arrow = true;
                        printf("Output redirected to %s\n", output_filename);
                        break;
                    }
                    user_cmd[i] = ptr;
                    //printf("Stored instruction: %s\n", user_cmd[i++]);
                }
                i = 0; // reset

                // Concatenate Forward Slash
                char * cat_forward_slash = (char *) malloc(1 + strlen(path_name[0]));
                strcpy(cat_forward_slash, forward_slash); // "/"
                strcat(cat_forward_slash, line);

                // Execute & Test Paths
                char * user_cat = (char *) malloc(1 + strlen(cat_forward_slash)+ strlen(path_name[0]));
                while(*path_name[i] != '\0')
                {
                    // Concatenate path & UNIX instruction type
                    strcpy(user_cat, path_name[i]); // "/bin"
                    strcat(user_cat, cat_forward_slash); // "/bin/ls"
                    printf("\nFinal Path: %s\n", user_cat);

                    // Check validity of path
                    if ((access(user_cat, X_OK)) == 0)
                    {
                        close(STDOUT_FILENO);
                        open(output_filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
                        printf("Path Exists | Child PID#2: %i | EXECV_RET: %i\n", getpid(), execv_ret);
                        if (read_arrow)
                        {
                            
                        }
                        execv_ret = execv(user_cat, user_cmd);
                        /* nothing will return unless it's an error (-1)
                         * once execution completes, program ends
                         * */
                    }
                    else
                        printf("Invalid Path\n");
                    i++;
                }
            }
            printf("> ");
        }
        // Free Heap Memory
        free(line); // deallocate memory block in heap
        if (ferror(stdin))
            err(1, "getline");
=======
        printf("child pid: %d\n", (int) getpid());
        exec(argc, argv);
>>>>>>> 13f60c5a4825123c518366814d9ea17bed61b08a
    }
    // Parent Process
    else
    {
        int wait_child = wait(nullptr); // wait for child to finish execution
        printf("\n~Reached Parent Process~\n");
    }
}
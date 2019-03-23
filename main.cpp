#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <err.h>     // error
#include <unistd.h>  // chdir
#include <fcntl.h> // file
#include "Functions.h"

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
        char redirect_arrow[2];
        strcpy(redirect_arrow, ">");

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
                // 1 Standard Error Message
                char *cd_path = nullptr;

                // Parse
                int check = 0;
                cd_path = std::strtok(line, " \n");
                cd_path = std::strtok(line, " \n");
//                cd_path = ptr;
//
//                while (ptr != nullptr && check <= 2)
//                {
//                    ptr = std::strtok(nullptr, " \n");
//                    check++;
//                }

                if (chdir(cd_path) == 0)
                    printf("Directory successfully changed to %s\n", cd_path);
                else
                    perror(cd_path);
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

                    // Check for redirection
                    if (*ptr == redirect_arrow[0])
                    {
                        ptr = std::strtok(nullptr, " \n");
                        output_filename = ptr;
                        read_arrow = true; // open file
                        printf("Output redirected to %s\n", output_filename);
                        break;
                    }
                    user_cmd[i] = ptr;
                    printf("Stored instruction: %s\n", user_cmd[i++]);
                }

//                for (int j = 0; j <= i; j++)
//                {
//                    printf(";Stored instruction: %s\n", user_cmd[j]);
//                }


                i = 0; // reset

                // Concatenate Forward Slash
                char *cat_final = cat_forward_slash(line, path_name[0]);

                // Execute & Test Paths
                char * user_cat = (char *) malloc(1 + strlen(cat_final)+ strlen(path_name[0]));

                while(*path_name[i] != '\0')
                {
                    // Concatenate path & UNIX instruction type
                    strcpy(user_cat, path_name[i]); // "/bin"
                    strcat(user_cat, cat_final); // "/bin/ls"
                    printf("Final Path: %s\n", user_cat);

                    // Check validity of path
                    if ((access(user_cat, X_OK)) == 0)
                    {
                        //open_output_file(read_arrow, output_filename);
                        if (read_arrow)
                        {
                            close(STDOUT_FILENO);
                            open(output_filename, O_CREAT | O_WRONLY| O_TRUNC, S_IRWXU);
                        }
                        printf("((Path Exists | Child PID#2: %i | EXECV_RET: %i\n", getpid(), execv_ret);
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
    }

    // Parent Process
    else
    {
        wait(nullptr); // wait for child to finish execution
        printf("\n~Reached Parent Process~\n");
    }
}
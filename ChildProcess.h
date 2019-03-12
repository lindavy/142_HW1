//
// Created by Linda Nguyen on 3/10/19.
//

#ifndef HW1_CHILDPROCESS_H
#define HW1_CHILDPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <err.h>     // error
#include <unistd.h>  // chdir
#define CWD_SIZE 512


void exec(int argc, char **argv) {
    printf("Entered Interactive Mode\n\n");

    char *line = NULL;
    size_t linesize = 0;
    ssize_t linelen;
    char path_name[512];

    // Path
    char *ptr = NULL;
    char *argvv[2] = {"ls", NULL}; char *buf;

    while ((linelen = getline(&line, &linesize, stdin)) != -1)
    {
        // Built-in Commands
        if (strncmp("exit", line, 4) == 0)
        {
            exit(0);  // user wants to exit
        }
        else if (strncmp("cd", line, 2) == 0)
        {
            printf("entered: cd\n");
        }
        else if (strncmp("path", line, 4) == 0)
        {
            printf("Current Working Directory: %s\n", getcwd(buf, CWD_SIZE));
            ptr = std::strtok(line, " \n");
            while (ptr != NULL)
            {
                ptr = std::strtok(NULL, " \n"); // update ptr to ignore "path" command

                // Search file directory
                snprintf(path_name, 511, "%s/ls", ptr);
                printf("\nSearching: %s\n", path_name);
                if ((access(ptr, X_OK)) == 0)
                {
                    printf("Path Exists\n");
                    //execv("ls", argvv); // nothing will return unless it's an error
                    //snprintf(path_name, 511, "%s/ls", ptr);
                }
                else
                    printf("Invalid Path\n");
            }
        }
        // other commands
        else
        {
            for(int i = 0; i < argc; i++)
            {
                printf(" %s", argv[i]);
            }
        }

        //fwrite(line, linelen, 1, stdout);
        printf("\nend of while loop\n\n");
    }

    free(line); // deallocate memory block in heap
    if (ferror(stdin))
        err(1, "getline");
}

#endif //HW1_CHILDPROCESS_H

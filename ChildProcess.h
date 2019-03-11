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


void exec() {
    printf("Interactive Mode:\n");

    char *line = NULL;
    size_t linesize = 0;
    ssize_t linelen;
    char path_name[512];

    // Path
    char *ptr = NULL; char delim[] = " ";
    char *paths[5];
    unsigned int ACCESS_OK = 0;

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
            ptr = std::strtok(line, delim);
            while (ptr != NULL)
            {
                ptr = std::strtok(NULL, delim); // update ptr to ignore "path" command

                // Search file directory
                snprintf(path_name, 511, "%s/ls", ptr);
                printf("Searching: %s\n", path_name);
                if ((access(ptr, X_OK)) == 0)
                {
                    printf("path exists!\n");
                }
                else
                    printf("invalid path\n");
            }
        }
        fwrite(line, linelen, 1, stdout);
    }

    free(line); // deallocate memory block in heap
    if (ferror(stdin))
        err(1, "getline");
}

#endif //HW1_CHILDPROCESS_H

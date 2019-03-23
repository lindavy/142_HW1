////
//// Created by Linda Nguyen on 3/21/19.
////
//
#ifndef INC_142_HW1_FUNCTIONS_H
#define INC_142_HW1_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
//
//void StoreInstruction(char *ptr, char *line, char *output_filename, bool read_arrow)
//{
//    char *user_cmd[20];
//    int i = 0;
//
//    ptr = std::strtok(line, " \n");
//    user_cmd[i++] = ptr;
//    while (ptr != nullptr && i < 20)
//    {
//        ptr = std::strtok(nullptr, " \n"); // update ptr
//        if (!(strcmp(ptr, ">"))) // if identical, it will return 0
//        {
//            ptr = std::strtok(nullptr, " \n");
//            output_filename = ptr;
//            read_arrow = true;
//            printf("Output redirected to %s\n", output_filename);
//            break;
//        }
//        user_cmd[i] = ptr;
//        printf("Stored instruction: %s\n", user_cmd[i++]);
//    }
//    //i = 0; // reset
//}
void open_output_file(char *output_filename)
{
    close(STDOUT_FILENO);
    open(output_filename, O_CREAT | O_WRONLY| O_TRUNC, S_IRWXU);
}

bool check_for_redirection(char *ptr, char *output_filename)
{
    if (strcmp(ptr, ">") == 0) // if identical, it will return
    {
        ptr = std::strtok(nullptr, " \n");
        output_filename = ptr;
        //read_arrow = true; // open file
        open_output_file(output_filename);
        printf("Output redirected to %s\n", output_filename);
        return true;
    }
    return false;
}
char *cat_forward_slash(char *line, char *path_name)
{
    char * cat_forward_slash = (char *) malloc(1 + strlen(path_name));
    strcpy(cat_forward_slash, "/"); // "/"
    strcat(cat_forward_slash, line);
    return cat_forward_slash;
}

//void execute_instruction(char *line, char *path_name[], char *user_cmd[], bool read_arrow, char *output_filename)
//{
//    int execv_ret = 0;
//    int i = 0;
//
//    // Concatenate Forward Slash
//    char *cat_final = cat_forward_slash(line, path_name[0]);
//
//    // Execute & Test Paths
//    char * user_cat = (char *) malloc(1 + strlen(cat_final)+ strlen(path_name[0]));
//
//    while(*path_name[i] != '\0')
//    {
//        // Concatenate path & UNIX instruction type
//        strcpy(user_cat, path_name[i]); // "/bin"
//        strcat(user_cat, cat_final); // "/bin/ls"
//        printf("Final Path: %s\n", user_cat);
//
//        // Check validity of path
//        if ((access(user_cat, X_OK)) == 0)
//        {
//            //open_output_file(read_arrow, output_filename);
//            if (read_arrow)
//            {
//                close(STDOUT_FILENO);
//                open(output_filename, O_CREAT | O_WRONLY| O_TRUNC, S_IRWXU);
//            }
//            printf("((Path Exists | Child PID#2: %i | EXECV_RET: %i\n", getpid(), execv_ret);
//            execv_ret = execv(user_cat, user_cmd);
//            /* nothing will return unless it's an error (-1)
//             * once execution completes, program ends
//             * */
//        }
//        else
//            printf("Invalid Path\n");
//        i++;
//    }
//}


#endif //INC_142_HW1_FUNCTIONS_H
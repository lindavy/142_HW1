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




#endif //INC_142_HW1_FUNCTIONS_H
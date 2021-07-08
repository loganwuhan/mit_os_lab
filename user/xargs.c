#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("usage: xargs <command>\n");
        exit(0);
    }

    char input_command_buf[100];

    char* exec_argv[argc+1];
    for(int i = 0; i < argc-1 ; ++i)
    {
        exec_argv[i] = argv[i+1];
    }
    exec_argv[argc-1] = input_command_buf;
    exec_argv[argc] = 0;

    char buf[500];
    char * p = buf;
    while(read(0, p++, 1) == 1)
        ;
    *(p-1) = 0;
    p = buf;

    for( ; *p == '\n'; p++)
        ;

    int length = strlen(p);
    if (length == 0) exit(0);

    //printf("%s \n", exec_argv[0]);
    //printf("%s %d \n", p, length);
    
    int count = 0;
    int commnad_count = 0;
    while(count < length)
    {
        if (p[count] != '\n')
        {
            input_command_buf[commnad_count++] = p[count++];
        }
        else
        {
            input_command_buf[commnad_count] = 0;
            //printf("%s\n", input_command_buf);
            if(fork() == 0)
            {
                //printf("%s\n", exec_argv[0]);
                exec(exec_argv[0], exec_argv);
            }
            else
            {
                wait(0);
            }
            count++;
            commnad_count = 0;
        }
    }
    if(commnad_count > 0)
    {
        input_command_buf[commnad_count] = 0;
        if(fork() == 0)
        {
            exec(exec_argv[0], exec_argv);
        }
        else
        {
            wait(0);
        }
    }

    exit(0);
}


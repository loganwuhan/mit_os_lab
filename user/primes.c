#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//#include <unistd.h>

#define MAX_NUM 35

int main(int argc, char *argv[])
{
    int prev_pipe[2];
    if ( pipe(prev_pipe) != 0) exit(1);
    //printf("prime 2\n");

    if (fork() != 0)
    {    
        //printf("prime 2\n");
        int temp;
        for(temp = 2 ; temp <= MAX_NUM ; ++temp)
        {
            write(prev_pipe[1], &temp, 4);
        }
        close(prev_pipe[1]);
        wait(0);
        //while(read(prev_pipe[0], &temp, 1);
    }
    else
    {
        //int write_finish = 0;
        int next_pipe[2];
        
        int first;
        while(1)
        {
            close(prev_pipe[1]);
            int byte_count = read(prev_pipe[0], &first, 4);
            if (byte_count < 4)
            {
                //printf("fuck\n");
                exit(1);
            }
            printf("prime %d\n", first);
            /*if (first > 10)
            {
                write
            }
            else
            {

            }*/
            pipe(next_pipe);
            if(fork() > 0)
            {
                
                break;
            }
            else
            {
                //close(prev_pipe[0]);close(prev_pipe[1]);
                memcpy(prev_pipe, next_pipe, 2*sizeof(int));
            }
        }

        int temp;
        while(read(prev_pipe[0], &temp, 4) > 0)
        {
            if (temp % first > 0)
            {
                write(next_pipe[1], &temp, 4);
            }
        }
        close(next_pipe[1]);
        wait(0);
        exit(0);
    }

    exit(0);
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pipe1[2];
    int pipe2[2];

    char pipe_error[] = "Error when creating pipe\n";

    if (pipe(pipe1) != 0 || pipe(pipe2) != 0 )
    {
        write(2, pipe_error, strlen(pipe_error));
    }
    if (fork() > 0)
    {
        write(pipe1[1], "a", 1);
        char recv_buffer;
        if(read(pipe2[0], &recv_buffer, 1) == 1)
        {
            int parent_pid = getpid();
            //int pid_digit = 1;
            //write(1, "%d: received ping\n", 17 + pid_digit);
            printf("%d: received pong\n", parent_pid);
            exit(0);
        }
        exit(1);
    }
    else
    {
        char recv_buffer;
        if (read(pipe1[0], &recv_buffer, 1) == 1)
        {
            int child_pid = getpid();
            //int pid_digit = 1;
            //write(1, "%d: received ping\n", 17 + pid_digit);
            printf("%d: received ping\n", child_pid);

            write(pipe2[1], &recv_buffer, 1);
            exit(0);
        }
        exit(1);
    }

    exit(0);
}
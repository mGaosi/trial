
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>

int main(int argc, char *argv[])
{
    int fd[2];
    if(::pipe2(fd, O_DIRECT) == 0)
    {
        if (fork() == 0)
        {
            // ::write(fd[0], "Hello PIPE!", 12); // error only for read!
            close(fd[0]);
            ::write(fd[1], "Hello PIPE!", 12);
            close(fd[1]);
        }
        else
        {
            close(fd[1]);
            char buffer[16] = {0};
            ::read(fd[0], buffer, 16);
            printf("%s\n", buffer);
            close(fd[0]);
        }
    }
    else
    {
        printf("Make PIPE error %d.\n", errno);
    }
    return 0;
}

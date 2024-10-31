#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>

#define FIFO_NAME "/tmp/fifo11S2"
int main(int argc, char *argv[])
{
    if(::mkfifo(FIFO_NAME, 0644) == 0)
    {
        int fp = ::open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
        if (fp < 0)
        {
            printf("Open FIFO error %d.\n", errno);
            return 1;
        }
        printf("FIFO capacity %d.\n", fcntl(fp, F_GETPIPE_SZ));
        //int fd = ::open(FIFO_NAME, O_WRONLY | O_NONBLOCK);
        int fd = ::open(FIFO_NAME, O_WRONLY | O_NONBLOCK);
        if (fd == -1)
        {
            printf("Open FIFO for write error %d.\n", errno);
        }
        else
        {
            ::write(fd, "This is FIFO message!\n", 23);
        }
        unlink(FIFO_NAME);
        ::close(fd);
        ::close(fp);
    }
    else
    {
        printf("Make FIFO error %d.\n", errno);
    }
    return 0;
}

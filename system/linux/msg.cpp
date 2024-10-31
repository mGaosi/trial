#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>

int main(int argc, char *argv[])
{
    key_t key = 900;
    int msq = msgget(key, IPC_CREAT | 0666);
    if (msq < 0)
    {
        printf("msgget error %d.\n", errno);
    }
    else
    {
        ::msgsnd(msq, "This is message 1!", 19, IPC_NOWAIT);
        if (fork() == 0)
        {
            char buffer[1024];
            while(true)
            {
                ssize_t len = ::msgrcv(msq, buffer, sizeof(buffer), 0, MSG_NOERROR);
                if (len < 0)
                {
                    break;
                }
                printf("# %s\n", buffer);
            }
        }
        else
        {
            ::msgsnd(msq, "This is message 2!", 19, IPC_NOWAIT);
        }
    }
    return 0;
}

#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

int sNumber = 0;

int main(int argc, char *argv[])
{
    {
        int iNumber = 0;
        char* pBuf = new char[1];
        pBuf[0] = 0;
        printf("sNumber@%p iNumber@%p pBuf@%p\n", &sNumber, &iNumber, pBuf);
        auto pid = fork();
        if (pid == 0)
        {
            // child process
            sNumber = 1;
            iNumber = 1;
            pBuf[0] = 1;
            printf("Child sNumber@%p iNumber@%p pBuf@%p\n", &sNumber, &iNumber, pBuf);
        }
        else
        {
#if 0 //Not shared memory, never return.
            while (iNumber < 1)
            {
                sleep(1);
            }
#endif
            int status = 0;
            waitpid(pid, &status, 0); //https://linux.die.net/man/2/waitpid
        }
        printf("sNumber=%d iNumber=%d pBuf[0]=%d\n", sNumber, iNumber, pBuf[0]);
    }
    return sNumber;
}

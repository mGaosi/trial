#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <spawn.h>
#include <unistd.h>
#include <mutex>
#include <filesystem>
#include <fstream>

int spawnp(char **arg)
{
    pid_t pid = 0;
    char arg1[1]= {0};
    char* argv[] = {
        arg[0],
        arg1,
        nullptr
    };
    char* envp[] = {nullptr};
    posix_spawn_file_actions_t actions;
    ::posix_spawn_file_actions_init(&actions);
    if (::posix_spawnp(&pid, argv[0], &actions, nullptr, argv, envp) == 0)
    {
        while (true)
        {
            int status = 0;
            const int id = ::waitpid(pid, &status, 0);
            if (id < 0)
            {
                printf("Wait for %d error %d.", pid, errno);
                break;
            }
            if (id > 0)
            {
                if (WIFEXITED(status))
                {
                    printf("The %d exit(%d).", pid, WEXITSTATUS(status));
                    break;
                }
                if (WIFSIGNALED(status))
                {
                    printf("The %d killed by signal(%d).", pid, WTERMSIG(status));
                    break;
                }
                if (WIFSTOPPED(status))
                {
                    printf("The %d stopped by signal(%d).", pid, WSTOPSIG(status));
                }
                else if (WIFCONTINUED(status))
                {
                    printf("The %d continued.", pid);
                }
            }
        }
    }
    ::posix_spawn_file_actions_destroy(&actions);
    return 0;
}

int main(int argc, char **argv)
{
    printf("%s[%d] argc=%d.\n", argv[0], ::getpid(), argc);
    if (argc <= 1)
    {
        spawnp(argv);
    }
    else
    {
        while (true)
        {
            sleep(1);
        }
    }
}

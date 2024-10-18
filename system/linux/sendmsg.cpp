#include <cstdint>
#include <cstdio>
#include <cerrno>
#include <memory>
#include <chrono>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        printf("socket() error %d\n", errno);
        return errno;
    }
    sockaddr_in addr{};
    {
        addr.sin_family = AF_INET;
        if (argc > 1)
        {
            addr.sin_addr.s_addr = inet_addr(argv[1]); //repleace with your ip
        }
        else
        {
            addr.sin_addr.s_addr = inet_addr("192.168.0.3"); //repleace with your ip
        }
        addr.sin_port = htons(12345);
        connect(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    }
    {
        //case1: one iov
        msghdr mh{};
        iovec iov{};
        mh.msg_name = reinterpret_cast<sockaddr*>(&addr);
        mh.msg_namelen = sizeof(addr);
        mh.msg_iov = &iov;
        mh.msg_iovlen = 1;
        std::unique_ptr<char[]> packet = std::make_unique<char[]>(2048);
        auto now = std::chrono::steady_clock::now();
        auto end = now + std::chrono::seconds(10);
        auto next = now;
        while (now < end)
        //for (size_t i = 0; i < 50000; i++)
        {
            next = next + std::chrono::microseconds((1364 * 8) / 800);
            // or
            //std::unique_ptr<char[]> packet = std::make_unique<char[]>(1364);
            iov.iov_base = packet.get();
            iov.iov_len = 1364;
            const int snd = sendmsg(fd, &mh, 0);
            //if (snd < 0) {/*todo: handle error*/}
            now = std::chrono::steady_clock::now();
            if (now < next)
            {
                timespec ts[2]{};
                ts[0].tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(next - now).count();
                int index = 0;
                while (nanosleep(&ts[index], &ts[1 - index]) && errno == EINTR)
                {
                    index = 1 - index;
                }
            }
            else
            {
                if ((now - next) > std::chrono::microseconds(1000))
                {
                    next = now;
                }
            }
        }
    }
    {
        //case2: two iov
        msghdr mh{};
        iovec iov[2]{};
        mh.msg_name = reinterpret_cast<sockaddr*>(&addr);
        mh.msg_namelen = sizeof(sockaddr_in);
        mh.msg_iov = iov;
        mh.msg_iovlen = 2;
        std::unique_ptr<char[]> hdr = std::make_unique<char[]>(48);
        std::unique_ptr<char[]> payload = std::make_unique<char[]>(1316);
        auto end = std::chrono::steady_clock::now() + std::chrono::seconds(10);
        while (std::chrono::steady_clock::now() < end)
        //for (size_t i = 0; i < 50000; i++)
        {
            // or
            //std::unique_ptr<char[]> hdr = std::make_unique<char[]>(48);
            //std::unique_ptr<char[]> payload = std::make_unique<char[]>(1316);
            iov[0].iov_base = hdr.get();
            iov[0].iov_len = 48;
            iov[1].iov_base = hdr.get();
            iov[1].iov_len = 1316;
            const int snd = sendmsg(fd, &mh, 0);
            //if (snd < 0) {/*todo: handle error*/}
        }
    }
    close(fd);
    return 0;
}

#include <cstdint>
#include <cstdio>
#include <cerrno>
#include <memory>
#include <chrono>
#include <array>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>

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
        addr.sin_addr.s_addr = inet_addr("192.168.0.3"); //repleace with your ip
        addr.sin_port = htons(12345);
    }
    {
        mmsghdr msgs[8] = {0};//replace with your size
        //case1: one iov
        iovec iov{};
        for (size_t i = 0; i < std::size(msgs); i++)
        {
            msgs[i].msg_hdr.msg_name = reinterpret_cast<sockaddr*>(&addr);
            msgs[i].msg_hdr.msg_namelen = sizeof(sockaddr_in);
            msgs[i].msg_hdr.msg_iov = &iov;
            msgs[i].msg_hdr.msg_iovlen = 1;
        }
        std::unique_ptr<char[]> packet = std::make_unique<char[]>(1364);
        auto end = std::chrono::steady_clock::now() + std::chrono::seconds(10);
        while (std::chrono::steady_clock::now() < end)
        //for (size_t i = 0; i < 50000; i++)
        {
            //or
            // std::unique_ptr<char[]> packet = std::make_unique<char[]>(1364);
            iov.iov_base = packet.get();
            iov.iov_len = 1364;
            const int snd = sendmmsg(fd, msgs, std::size(msgs), 0);
            //if (snd < 0) {/*todo: handle error*/}
        }
    }
    {
        //case2: two iov
        mmsghdr msgs[8] = {0};//replace with your size
        iovec iov[2]{};
        for (size_t i = 0; i < std::size(msgs); i++)
        {
            msgs[i].msg_hdr.msg_name = reinterpret_cast<sockaddr*>(&addr);
            msgs[i].msg_hdr.msg_namelen = sizeof(sockaddr_in);
            msgs[i].msg_hdr.msg_iov = iov;
            msgs[i].msg_hdr.msg_iovlen = 2;
        }
        std::unique_ptr<char[]> hdr = std::make_unique<char[]>(48);
        std::unique_ptr<char[]> payload = std::make_unique<char[]>(1316);
        auto end = std::chrono::steady_clock::now() + std::chrono::seconds(10);
        while (std::chrono::steady_clock::now() < end)
        //for (size_t i = 0; i < 50000; i++)
        {
            //or
            // std::unique_ptr<char[]> hdr = std::make_unique<char[]>(48);
            // std::unique_ptr<char[]> payload = std::make_unique<char[]>(1316);
            iov[0].iov_base = hdr.get();
            iov[0].iov_len = 48;
            iov[1].iov_base = hdr.get();
            iov[1].iov_len = 1316;
            const int snd = sendmmsg(fd, msgs, std::size(msgs), 0);
            //if (snd < 0) {/*todo: handle error*/}
        }
    }
    close(fd);
    return 0;
}

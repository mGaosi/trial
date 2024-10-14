/**
 * @file mmap.cpp
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-24
 * 
 * 
 */

#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>

int test_mmap()
{
    int fd = open("/var/tmp/frame.yuv", O_RDONLY);
    if (fd < 0)
    {
        std::cout << "open(\"/var/tmp/frame.yuv\", O_RDONLY) = " << fd << std::endl;
        return 0;
    }
    struct stat i;
    fstat(fd, &i);
    if (i.st_size <= 0)
    {
        std::cout << "file size not read." << std::endl;
        close(fd);
        return -EIO;
    }
    uint8_t* buffer = new uint8_t[4096u];
    auto tick1 = std::chrono::steady_clock::now().time_since_epoch();
    uint8_t* m = (uint8_t*)mmap(NULL, i.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (MAP_FAILED == m)
    {
        close(fd);
        return -EIO;
    }
    uint8_t* src = m;
    int len = i.st_size;
    while (len > 0)
    {
        int r = std::min(4096, len);
        memcpy(buffer, src, r);
        src += r;
        len -= r;
    }
    munmap(m, i.st_size);
    auto tick2 = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "mmap " << i.st_size << " bytes of file used " << (tick2 - tick1).count() << " ns." << std::endl;
    delete[] buffer;
    close(fd);
    return 0;
}

int test_mmap_large()
{
    int fd = open("/var/tmp/4k.p010.yuv", O_RDONLY);
    if (fd < 0)
    {
        std::cout << "open(\"/var/tmp/4k.p010.yuv\", O_RDONLY) = " << fd << std::endl;
        return 0;
    }
    struct stat64 sta;
    fstat64(fd, &sta);
    if (sta.st_size <= 0)
    {
        std::cout << "file size not read." << std::endl;
        close(fd);
        return -EIO;
    }
    uint8_t* buffer = new uint8_t[4096u];
    auto tick1 = std::chrono::steady_clock::now().time_since_epoch();
    size_t block_size = (100u * 1024 * 1024);
    size_t blocks = sta.st_size / block_size  + 1u;
    for (size_t i = 0; i < blocks; ++i)
    {
        uint8_t* m = (uint8_t*)mmap(NULL, block_size, PROT_READ, MAP_SHARED, fd, i * block_size);
        if (MAP_FAILED == m)
        {
            close(fd);
            return -EIO;
        }
        uint8_t* src = m;
        int len = std::min(size_t(sta.st_size - block_size * i), block_size);
        while (len > 0)
        {
            int r = std::min(4096, len);
            memcpy(buffer, src, r);
            src += r;
            len -= r;
        }
        munmap(m, block_size);
    }
    auto tick2 = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "mmap large " << sta.st_size << " bytes of file used " << (tick2 - tick1).count() << " ns." << std::endl;
    delete[] buffer;
    close(fd);
    return 0;
}

int test_read()
{
    int fd = open("/var/tmp/frame.yuv", O_RDONLY);
    if (fd < 0)
    {
        std::cout << "open(\"/var/tmp/frame.yuv\", O_RDONLY) = " << fd << std::endl;
        return 0;
    }
    struct stat i;
    fstat(fd, &i);
    if (i.st_size <= 0)
    {
        std::cout << "file size not read." << std::endl;
        close(fd);
        return -EIO;
    }
    uint8_t* buffer = new uint8_t[4096u];
    auto tick1 = std::chrono::steady_clock::now().time_since_epoch();
    while (read(fd, buffer, 4096u) > 0);
    auto tick2 = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "read " << i.st_size << " bytes of file used " << (tick2 - tick1).count() << " ns." << std::endl;
    delete[] buffer;
    close(fd);
    return 0;
}

int test_read_large()
{
    int fd = open("/var/tmp/4k.p010.yuv", O_RDONLY);
    if (fd < 0)
    {
        std::cout << "open(\"/var/tmp/4k.p010.yuv\", O_RDONLY) = " << fd << std::endl;
        return 0;
    }
    struct stat64 i;
    fstat64(fd, &i);
    if (i.st_size <= 0)
    {
        std::cout << "file size not read." << std::endl;
        close(fd);
        return -EIO;
    }
    uint8_t* buffer = new uint8_t[4096u];
    auto tick1 = std::chrono::steady_clock::now().time_since_epoch();
    while (read(fd, buffer, 4096u) > 0);
    auto tick2 = std::chrono::steady_clock::now().time_since_epoch();
    std::cout << "read large " << i.st_size << " bytes of file used " << (tick2 - tick1).count() << " ns." << std::endl;
    delete[] buffer;
    close(fd);
    return 0;
}

int main()
{
    test_mmap();
    test_read();
    test_mmap_large();
    test_read_large();
}
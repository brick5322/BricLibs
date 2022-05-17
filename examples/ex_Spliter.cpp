#include <iostream>
#include "Spliter.h"

int main(int argc, char *argv[])
{
    Spliter spliter('.',move);
    
    spliter << "www.baidu.com";
    for (const char* i : Spliter::iterator(spliter))
        std::cout << i << std::endl;

    spliter << "www.zhihu.com";
    for (const char* i : Spliter::iterator(spliter))
        std::cout << i << std::endl;

    spliter << "www.bilibili.com";
    char buffer[20];
    spliter[0] >> buffer;
    std::cout << buffer << std::endl;
    spliter[1] >> buffer;
    std::cout << buffer << std::endl;
    spliter[2] >> buffer;
    std::cout << buffer << std::endl;

    
    return 0;
}


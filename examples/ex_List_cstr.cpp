
#include <iostream>
#include "List_cstr.h"

int main(int argc, char *argv[])
{
    const char* teststr = "hello world!\n";
    char testarr[] = "hello World!\n";
    List_cstr list_str;
    list_str.add(teststr);
    list_str.add(teststr, move);
    list_str.add(testarr);
    list_str.add(testarr, move);
    testarr[5] = '-';
    for (int i = 0; i < 4; i++)
        std::cout << list_str[i] << std::endl;
    return 0;
}


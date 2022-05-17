#include <iostream>
#include "List_cstr.h"
#include "Spliter.h"
extern"C"
{
#include "List.h"
#include "Node.h"
}

void test0()
{
    BasicList* lst = BasicList_alloc(0);
    int p = 0;
    for (int i = 0; i < 10; i++)
        *(int*)(BasicList_add(lst, 0, sizeof(int))->data) = i;
    for (int i = 0; i < lst->length; i++)
        std::cout << i << ":" << *(int*)BasicList_get(lst, i)->data << std::endl;
    //BasicList_delete(lst, 8);
    //*(int*)BasicList_insert(lst, 8, 0, sizeof(int))->data = 114514;
    *(int*)BasicList_update(lst, 8, 0, sizeof(int))->data = 114514;
    for (int i = 0; i < lst->length; i++)
        std::cout << i << ":" << *(int*)BasicList_get(lst, i)->data << std::endl;
}

void test1()
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
}

void test_spliter()
{
    Spliter spliter('.',move);
    spliter << "www.baidu.com";
    for (const char* i : Spliter::iterator(spliter))
        std::cout << i << std::endl;
    std::cout << "---------------------" << std::endl;
    spliter << "www.zhihu.com";
    for (const char* i : Spliter::iterator(spliter))
        std::cout << i << std::endl;
    std::cout << "---------------------" << std::endl;
    spliter << "www.bilibili.com";
    for (const char* i : Spliter::iterator(spliter))
        std::cout << i << std::endl;
    std::cout << "---------------------" << std::endl;
    char buffer[20];
    spliter[0] >> buffer;
    std::cout << buffer << std::endl;
    spliter[1] >> buffer;
    std::cout << buffer << std::endl;
    spliter[2] >> buffer;
    std::cout << buffer << std::endl;
    std::cout << "---------------------" << std::endl;
}

int main(int argc, char *argv[])
{
    test_spliter();
    return 0;
}

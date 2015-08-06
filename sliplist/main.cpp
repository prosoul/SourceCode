#include <iostream>
#include "sliplist.h"
#include<string>
using namespace std;


int main()
{
    SlipList sliplist;

    //test insert function
    std::cout << "test is starting ....." << std::endl;
    for(int i = 0; i < 100000; i++){
        sliplist.Insert(i,i+10);
    }
    size_t size = sliplist.size();
    std::cout << "the number of elements in the sliplist is : "
         << size
         << std::endl;

    if( size == 100000)
        std::cout << "insert success......." << std::endl;
    else
        std::cout << "insert failure......." << std::endl;

    //test search function
    bool is_search_success = true;
    for(int i = 0; i <100000; i++){
        int value;
        if(!(sliplist.Search(i,value) && (value == i + 10))){
            is_search_success = false;
            break;
        }
    }
    if(is_search_success)
        std::cout << "search success......." << std::endl;
    else
        std::cout << "insert failure......." << std::endl;

    //test delte function
    bool is_delete_success = true;

    for(int i = 0; i < 100000; i++){
        int value;
        if(!sliplist.Delete(i,value)){
            is_delete_success = false;
            break;
        }
    }

    if(is_delete_success)
        std::cout << "delete success......." << std::endl;
    else
        std::cout << "insert failure......." << std::endl;

    return 0;
}

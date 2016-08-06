/**
 * @file   main.cpp
 * @Author Vinod Gopalan (kgvinod@gmail.com)
 * @date   July, 2016
 * @brief  A client for receiving multicast streams - test app
 *
 */
 
#include <string>
#include <iostream>

#include "MulticastClient.h"

int main() 
{

    MulticastClient *client = new MulticastClient("192.168.0.57", "239.1.17.1", 11001);
    
    return 0;
}


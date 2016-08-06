/**
 * @file   MulticastClient.h
 * @Author Vinod Gopalan (kgvinod@gmail.com)
 * @date   July, 2016
 * @brief  A client for receiving multicast streams
 *
 */
 
#ifndef MCLIENT_H
#define MCLIENT_H

#include <string>
#include <iostream>


// FsNode class
class MulticastClient {

    public:
    
        // Disallow Default Constructor 
        MulticastClient() = delete; 
        
        // Constructor
        MulticastClient(std::string local_ip, std::string multicast_ip, int multicast_port) : mLocalIp{local_ip}, mMulticastIp{multicast_ip}, mMulticastPort{multicast_port} {}
        
        // Destructor
        ~MulticastClient() {};
        
        // Start
        void start();
            
    
    private:
    
        std::string mLocalIp; 
        std::string mMulticastIp;
        int mMulticastPort;
};

#endif //#ifndef FSNODE_H

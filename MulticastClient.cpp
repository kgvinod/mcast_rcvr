/**
 * @file   MulticastClient.cpp
 * @Author Vinod Gopalan (kgvinod@gmail.com)
 * @date   July, 2016
 * @brief  A client for receiving multicast streams
 *
 */

#include "MulticastClient.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor
MulticastClient::MulticastClient(std::string local_ip, std::string multicast_ip, unsigned int multicast_port) 
  : mLocalIp {local_ip}, 
    mMulticastIp {multicast_ip}, 
    mMulticastPort {multicast_port},
    mSockFd {-1} 
{
    // invariants 
    if (multicast_port > MAX_PORT_NUM)
        throw range_error( "The port range is in error!" );
}


// Destructor
MulticastClient::~MulticastClient() 
{
    if (mSockFd >= 0) {
        cout << "Closing socket\n";
        close(mSockFd);
    }
}


// Open
int MulticastClient::open()
{

    // Step 1 : Create a datagram socket.
    mSockFd = socket(AF_INET, SOCK_DGRAM, 0);

    if(mSockFd < 0) {
        cout << "Opening datagram socket - ERROR !\n";
        return -1;
    }
    else {
        printf("Opening datagram socket - OK.\n");
    }


    // Step 2 : Enable SO_REUSEADDR to allow multiple instances
    // to receive copies of the multicast stream.

    int reuse = 1;
    if(setsockopt(mSockFd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) {
        cout << "Setting SO_REUSEADDR - ERROR !\n";
        close(mSockFd);
        return -1;
    }
    else {
        printf("Setting SO_REUSEADDR - OK.\n");
    }

    // Step 3 : Bind to the multicast port number

    memset((char *) &mLocalSock, 0, sizeof(mLocalSock));
    mLocalSock.sin_family = AF_INET;
    mLocalSock.sin_port = htons(mMulticastPort);
    mLocalSock.sin_addr.s_addr = INADDR_ANY;

    if(bind(mSockFd, (struct sockaddr*)&mLocalSock, sizeof(mLocalSock)))
    {
        cout << "Binding to socket - ERROR !\n";
        close(mSockFd);
        return -1;
    }
    else {
        printf("Binding to socket - OK.\n");
    }

    // Step 4 : Join the multicast group

    mGroup.imr_multiaddr.s_addr = inet_addr(mMulticastIp.c_str());
    mGroup.imr_interface.s_addr = inet_addr(mLocalIp.c_str());
    if(setsockopt(mSockFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mGroup, sizeof(mGroup)) < 0)
    {
        cout << "Joining multicast group - ERROR !\n";
        close(mSockFd);
        return -1;
    }
    else {
        printf("Joining multicast group - OK.\n");
    }

    return 0;

}


// Read mcast stream
int MulticastClient::readData(char *buffer, unsigned int size)
{

    if (buffer != nullptr) {
        // Read from socket
        return read(mSockFd, buffer, size);
    } 
    
    return -1;

}

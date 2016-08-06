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
using namespace std;

/* VLC command for sending a multicast stream:
 vlc -vvv ~/Videos/00027.MTS --sout '#transcode{vcodec=mp4v,acodec=mpga,vb=800,ab=128,deinterlace}:rtp{mux=ts,dst=239.1.17.1,port=11001,sdp=sap,name="TestStream"}'
*/

int main()
{

    int datalen;
    char databuf[1024];
    long total_data = 0;
    FILE *ptr_myfile;
    const char *filename = "mcast.data";
    
    // Open a file to store multicast data
    ptr_myfile=fopen(filename,"wb");    

    MulticastClient *client = new MulticastClient("10.0.0.246", "239.1.17.1", 11001);
    client->open();
    
    while (1)
    {
        /* Read from the socket. */
        datalen = sizeof(databuf);
        if(client->readData(databuf, datalen) < 0)
        {
            cout << "Reading datagram message error \n";
        }
        else
        {
            total_data += datalen;
            printf(".");
            if ((total_data % 1024000) == 0)
                printf ("%ld\n", total_data);
            fflush(stdout);
            //printf("The message from multicast server is: \"%s\"\n", databuf);
            fwrite(databuf, datalen, 1, ptr_myfile);
        }
    }

    return 0;
}


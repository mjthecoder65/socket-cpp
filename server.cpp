#include <iostream>
#include <string>
#include <stdio.h>
#include "socket.h"

using namespace std;

const int PORT = 3000; 

int main(int argc, char *argv[])
{
    char msg[1500];

    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
        
    if(bindStatus < 0)
    {
        cerr << "ERROR: Binding the socket to the local address!" << endl;
        exit(0);
    }

    cout << "Server listening on port number "<< PORT << " ...." << endl;
    listen(serverSd, 10);

    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "ERROR: couldn't accept request from client!" << endl;
        exit(1);
    }

    cout << "Connected with client!" << endl;
    while(1)
    {
        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg)); 

        recv(newSd, (char*)&msg, sizeof(msg), 0);

        if(!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }
        cout << "Hana is online: " << msg << endl;
        cout << "> ";
        string data; // c++ string, and it is an object not address
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        //send the message to client
        send(newSd, (char*)&msg, strlen(msg), 0);
    }
    
    //we need to close the socket descriptors after we're all done
    close(newSd);
    close(serverSd);
    cout << "Connection terminated..." << endl;
    return 0;   
}
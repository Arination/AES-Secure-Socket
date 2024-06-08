//#include "cryptlib.h"
//#include "rijndael.h"
//#include "modes.h"
//#include "files.h"
//#include "osrng.h"
//#include "hex.h"

#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <WS2tcpip.h>
#include <tchar.h>
#include <vector>

using namespace std;
//using namespace CryptoPP;

#pragma comment(lib, "ws2_32.lib")

bool initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void interact(SOCKET clientsocket, vector<SOCKET>& clients) {
    //send/recv client
    cout << "client connected" << endl;
    char buffer[4096];

    while (1) { 
        int bytesrecvd = recv(clientsocket, buffer, sizeof(buffer), 0);

        if (bytesrecvd <= 0) {
            cout << "client disconnected" << endl;
            break;
        }

        string message(buffer, bytesrecvd);
        cout << "message from client: " << message << endl;

        for (auto client : clients) {
            if (client != clientsocket) {
                send(client, message.c_str(), message.length(), 0);
            }
        }
    }

    auto it = find(clients.begin(), clients.end(), clientsocket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    closesocket(clientsocket);
}

int main() {
    if (!initialize()) {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }

    cout << "Server running" << endl;

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    // Convert address structure
    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    // Convert the IP address to binary format
    if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
        cout << "Setting address structure failed" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Bind
    if (bind(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Bind failed" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    //listen
    if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen failed" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Successful completion
    cout << "Server setup complete on port: "<<port<< endl;

    vector<SOCKET> clients;

    while (1) {

        //accept
        SOCKET clientsocket = accept(s, nullptr, nullptr);
        if (clientsocket == INVALID_SOCKET) {
            cout << "invalid client socket" << endl;
        }

        clients.push_back(clientsocket);
        thread t1(interact, clientsocket, std::ref(clients));
        t1.detach();
    }

    
    closesocket(s);
    WSACleanup();

    return 0;
}

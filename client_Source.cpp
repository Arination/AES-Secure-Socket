#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <thread>

using namespace std;
using namespace CryptoPP;

#pragma comment(lib, "ws2_32.lib")

bool initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

string AESMessEncrypt(const string& plaintext, SecByteBlock& key, SecByteBlock& iv) {
    string encryptMess;

    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource s(plaintext, true,
            new StreamTransformationFilter(e,
                new StringSink(encryptMess)
            )
        );
    }
    catch (const Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    return encryptMess;
}

string AESMessDecrypt(const string& cyphertext, const byte key[], const byte iv[]) {
    string decryptMess;

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);

        StringSource s(cyphertext, true,
            new StreamTransformationFilter(d,
                new StringSink(decryptMess)
            )
        );
    }
    catch (const Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    return decryptMess;
}


void sendMessage(SOCKET s) {

    AutoSeededRandomPool prng;

    cout << "Enter your name: ";
    string name;
    getline(cin, name);
    string message;

    while (1) {
        getline(cin, message);
        string msg = name + " : " + message;

        SecByteBlock key(AES::DEFAULT_KEYLENGTH);
        SecByteBlock iv(AES::BLOCKSIZE);

        prng.GenerateBlock(key, key.size());
        prng.GenerateBlock(iv, iv.size());

        string encMess = AESMessEncrypt(msg, key, iv);

        string keyStr(reinterpret_cast<const char*>(key.data()), key.size());
        string ivStr(reinterpret_cast<const char*>(iv.data()), iv.size());

        string fullMessage = keyStr + ivStr + encMess;

        int bytesend = send(s, fullMessage.c_str(), fullMessage.length(), 0);
        if (bytesend == SOCKET_ERROR) {
            cout << "Error sending message" << endl;
            break;
        }

        if (message == "quit") {
            cout << "Exiting chat" << endl;
            break;
        }
    }

    closesocket(s);
    WSACleanup();
}

void receiveMessage(SOCKET s) {
    char buffer[4096];
    int recvlength;

    while (1) {
        recvlength = recv(s, buffer, sizeof(buffer), 0);

        if (recvlength <= 0) {
            cout << "Disconnected from the server" << endl;
            break;
        }
        else {
            if (recvlength < AES::DEFAULT_KEYLENGTH + AES::BLOCKSIZE) {
                cout << "Bad message received" << endl;
                continue;
            }

            string received(buffer, recvlength);
            SecByteBlock key(reinterpret_cast<const byte*>(received.data()), AES::DEFAULT_KEYLENGTH);
            SecByteBlock iv(reinterpret_cast<const byte*>(received.data() + AES::DEFAULT_KEYLENGTH), AES::BLOCKSIZE);

            string encryptMess = received.substr(AES::DEFAULT_KEYLENGTH + AES::BLOCKSIZE);
            string msg = AESMessDecrypt(encryptMess, key.data(), iv.data());
            cout << msg << endl;
        }
    }

    closesocket(s);
    WSACleanup();
}

int main() {
    if (!initialize()) {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        cout << "Invalid socket created" << endl;
        return 1;
    }

    int port = 12345;
    string serveraddress = "127.0.0.1";
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

    if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Connection error, unable to connect: " << WSAGetLastError() << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout << "Client connecting" << endl;

    thread sendert(sendMessage, s);
    thread receivert(receiveMessage, s);

    sendert.join();
    receivert.join();

    return 0;
}

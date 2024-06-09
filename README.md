# AES Secure Socket
 
This is a AES encrypted implementation of Socket Programming (in C++) which allows multiple clients to connect and chat as a group

## Description
Socket Programming is a way of connecting two nodes on a network to communicate with each other, where one node (socket) listens on one of it assigned ports for connections and the other node (socket) reaches out to make connections and relay messages.

Here, in this project the one listening is called the SEVER and the other one is called the CLIENT, which trying to connect to the server. I have used Winsock API to create a network locally on our windows machine for multiple clients to connect to the server in a TCP based connection.

### How do they work?
  1. You start the server which listens on the assigned port for connections.
  2. Then initiate the client side application, for it to connect to the server.
  3. Now, after such subsequent connection the server automatically creates another socket (similar to the previous one) and listens for other connection request from other clients.
     
This implementation facilitates multiple client connections through the use of threads.

### Here's where you can learn the basic Socket implementation:
[Part 1: SOCKETS](https://www.youtube.com/watch?v=gntyAFoZp-E&t=1992s&pp=ygUZc29ja2V0IHByb2dyYW1taW5nIGluIGMrKw%3D%3D)

[Part 2: TCP and UDP](https://www.youtube.com/watch?v=sXW_sNGvqcU)

### But there's a drawback! 
  1. The message or any information exchange between clients and the server is happening in clear text.
  2. Easily intercepatable by an adversary.
  
This project was created keeping in mind the deficiencies in the basic traditional socket creation. Hence this secure (encrypted) tunneled connection is _safe, easy to use, and non interceptable._


### Setup AES using Crypto++ library.

Note :- **Visual Studio** is used for the development of this application, so make sure you have it installed already. I would suggest you to use community edition.


1. Clone the Crypto++ library from the link below or just search Cyptoo++ github.(you can also download it by searching it on Crypto++ site, I preferred cloning it.)
2. Also download (clone) the CryptoPP PEM pack.

   Make sure to note the location of the cloned repositories or dowloads.

3. Now, copy and paste the contents of the CryptoPP PEM folder in the Cryptopp folder. (skip the files if there's a collision.)
4. Search for **cryptlib.vcxproj** in the Cryptopp folder and open it with Visual Studio.
5. Click on the cyptlib to view the dependencies and right click to add the header files, source files as shown.
6. Change the solution configuration to **Release**, **x64**.
7. Now right click on the cryptlib solution and click build.
8. Will take some time to complete and upon completion it will show Build success message in the Output area.

[Crypto++ Repo.](https://github.com/weidai11/cryptopp)

[Crypto PEM.](https://github.com/noloader/cryptopp-pem)



### Setting Up and Compiling the C++ AES implementation:
1. Create a new blank project -> Empty C++ project in Visual Studio.
2. Add C++ source file in the Source files section.
3. Get the code from the CryptoPP site (link is below) or from the CPP file in this repository. ([Cryptopp.cpp](https://github.com/Arination/AES-Secure-Socket/blob/main/Cryptopp.cpp)).
4. Change the solution configuration to **Release**, **x64**.
5. Paste the code and you will find that the IDE is unable to resolve path for the incuded header files. Don't worry let's add their path.
6. Open the project properties as shown.
7. Check that the configuration is set to **Active(Release)** and Platform **Active(x64)**.
8. Navigate to C/C++ option in left panel, expand it and click General properties. Click **Additional Include Directories** and edit it with the path to **cryptopp** folder as shown.
9. Click OK. Then go to Code Generation and change **Runtime Library** to **Multi-threaded (/MT).**
10. Once this is done, collapse the C/C++ property and expand **Linker** properties.
11. Click General properties. Click **Additional Library Directories** and edit it with the path to **cryptopp\x64\Output\Release** folder as shown. Click Ok
12. Also change the **Enable Incremental Linking** to **No (/INCREMENTAL:NO)**.
13. Go to the **Input** properties and Click **Additional Dependencies**, edit it and write **cryptlib.lib** and click Ok.
14. Once all this is done Click Apply and Ok.
15. Woah! Everything will be resolved (hope you followed the steps correctly :)).

[AES Code](https://www.cryptopp.com/wiki/Advanced_Encryption_Standard)

## Now Let's Dive into SECURE SOCKET implementation.
1. Create a new project and an empty C++ project, name it **Server side**.
2. Add a C++ source file and copy the code from the repository. ([click here](
``` sudo git clone https://github.com/yuvrajmalhi/Ultra-Fast-Port-Scanner.git```           
```cd Ultra-Fast-Port-Scanner/```                   
```gcc scanner.c -o scanner```           
```ls```  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp; - &emsp;  *Confirm that ther 'scanner' executable and file are present*        

Here's how:   




Do share if you liked my work. Thanks!

:smile:

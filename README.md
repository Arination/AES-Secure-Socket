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

Note :- **Visual Studio** is used for the development of this application, so make sure you have it installed already with C++ development environment package. I would suggest you to use community edition.


1. Clone the Crypto++ library from the link below or just search Cyptoo++ github.(you can also download it by searching it on Crypto++ site, I preferred cloning it.)
2. Also download (clone) the CryptoPP PEM pack.

   Make sure to note the location of the cloned repositories or downloads.

3. Now, copy and paste the contents of the CryptoPP PEM folder in the Cryptopp folder. (skip the files if there's a collision.)
4. Search for **cryptlib.vcxproj** in the Cryptopp folder and open it with Visual Studio.
   
   ![Screenshot (33)](https://github.com/Arination/AES-Secure-Socket/assets/87356283/e4136fae-7092-4a2b-a0e4-3bf70ed75e60)
   
5. Click on the cyptlib to view the dependencies and right click to add the header files (existing .h files), source files (existing .cpp files) as shown.
   
![VID_20240610212527](https://github.com/Arination/AES-Secure-Socket/assets/87356283/4efde533-66b9-4769-8d76-82722c06ffb2)

6. Change the solution configuration to **Release**, **x64**.
7. Now right click on the cryptlib solution and click build.
8. Will take some time to complete and upon completion it will show Build success message in the Output area.

(I already did this process, so it shows me successfully Updated message.)

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

### Server Side:
1. Create a new project and an empty C++ project, name it **Server side**.
2. Add a C++ source file and copy the code from the repository ([click here](https://github.com/Arination/AES-Secure-Socket/blob/main/server_Source.cpp)).
3. Change the solution configuration to **Release**, **x64**.
4. Save the Solution.

### Client Side:
1. Create a new project and an empty C++ project, name it **Client side**.
2. Add a C++ source file and copy the code from the repository ([click here](https://github.com/Arination/AES-Secure-Socket/blob/main/client_Source.cpp)).
3. Change the solution configuration to **Release**, **x64**.
 
Caution this is the most important part for Client Side.

4. Follow the Same steps as followed for basic AES setup above.
5. Save the Solution.

## Now to test it!
1. Run the Server Side code first by clicking the **Local Windows Debugger**.
2. Then run the Client side code.
3. The terminal windows will appear showing the connection successful message.
4. Now just enter the name in the client side terminal and Viola! you can send messages and see if they are encrypted or not.

## Multiple Clients:
1. This requires nothing special, just create multiple client projects as you have done for single client as it is.
2. Run the code once the server is running, enter the names and Bingo! you are all set up.
3. Clients can leave the chat if the enter **"quit"** in chat.

# Pros Of This Implementation.
1. Generates random keys and IV everytime and for every message, even if the same message was sent multiple times. Making the cipher text unique everytime, un-interceptable and un-decodable.
2. Multiple clients can connect and chat without any restrictions.
   
Do share if you liked my work. Thanks!

:smile:

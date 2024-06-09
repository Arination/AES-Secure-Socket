# AES Secure Socket
 
This is a AES encrypted implementation of Socket Programming (in C++) which allows multiple clients to connect and chat as a group

## Description
Socket Programming is a way of connecting two nodes on a network to communicate with each other, where one node (socket) listens on one of it assigned ports for connections and the other node (socket) reaches out to make connections and relay messages.
Here, in this project the one socket listening is called the SEVER and the other one is called the CLIENT, which trying to connect to the server. I have used Winsock API to create a network locally on our windows machine for multiple clients to connect to the server in a TCP based connection.
### How do they work?
  1. You start the server which listening on the assigned port for connection.
  2. Then initiate the client side application, for it to connect to the server.
  3. Now, after such subsequent connection the server automatically creates another socket (similar to the previous one) and listens for other connection request from other clients.
This implementation facilitates multiple client connections through the use of threads.

### Here's where you can learn the basic implementation:
![Part 1:](https://www.youtube.com/watch?v=gntyAFoZp-E&t=1992s&pp=ygUZc29ja2V0IHByb2dyYW1taW5nIGluIGMrKw%3D%3D)

### But there's a drawback! 
  1. The message or any information exchange between clients and the server is happening in clear text.
  2. Easily intercepatable by an adversary.
  
This project was created keeping in mind the deficiencies in the basic traditional socket creation. Hence this secure (encrypted) tunneled connection is _safe, easy to use, and non interceptable._


### Setup AES using Crypto++ library.
Run the following commands to download and compile the scanner:
``` sudo git clone https://github.com/yuvrajmalhi/Ultra-Fast-Port-Scanner.git```           
```cd Ultra-Fast-Port-Scanner/```                   
```gcc scanner.c -o scanner```           
```ls```  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp; - &emsp;  *Confirm that ther 'scanner' executable and file are present*        

Here's how:   
![Setup_scanner](https://user-images.githubusercontent.com/76866159/135032180-a1f9f85a-7afa-450d-aee0-4114443e388f.gif)   


### Usage
Make a new file "webpages.txt" and enter enter the website URLs you want to scan line-by-line using vi-editor. 

```vi webpages.txt```  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp; - &emsp;  *Enter the URLs. Eg: google.com, yahoo.com*   
```ls```           
```sudo ./scanner```       
        
Give ~20 seconds for the program to run and watch as the results come!    

Watch this for a quick demo:      

![Demo](https://user-images.githubusercontent.com/76866159/135033161-52de5f03-9faa-4e36-b521-a44d7c403117.gif)

Complete! 
Now you can see the results which are **5X** faster than nmap and also very easy to understand.
For each website the program shows a list of:
  1. IPv4 addresses
  2. IPv6 addresses
  3. Ports open on the IPv4 addresses
  4. Ports open on the IPv6 addresses
  5. Services running on each of the above open ports.
  

## Working
For those of you who are coders and network engineers, I have explained the working of the code below:
(Note that I will just give a brief description of the code implementation. For detailed implementaion, open and read through scanner.c)

### Step 1: Service-Port Reading - populate()
This function registers all the important TCP ports and their respective services from port numbers 1-1024.
To have a look at which ports and services these are, run the command:   
 ```sudo cat /etc/services```
                
 ![image](https://user-images.githubusercontent.com/76866159/134986426-3aa0d621-e8a0-4502-b5e3-c36c0d1b2f09.png)
 
 ### Step 2: Parse domains - domainparse()
 In this step, the names of domains that you just entered in "webpages.txt" is read out of the whole URL, the relevant **domain name** is extracted.
 For example, if I enter: _https://github.com/yuvrajmalhi/Ultra-Fast-Port-Scanner/_ 
 
 then the domain name will be: _github.com_

### Step 3: DNS lookup - lookup_webpage() -> getaddrinfo()
After a website's domain name has been read, then it's IP addresses (IPv4 and IPv6) are fetched using DNS protocol. If no addresses are returned, then an error is shown and the function returns.

If valid IP addresses are received then they are displayed and for each IP address Step 4 is carried out.

### Step 4: DNS lookup - lookup_webpage() -> connect()
Now for each of the port read in Step 1:

> This function registers all the important TCP ports and their respective services from port numbers 1-1024.

A child process for each port is created using fork() which connects to a port number on the IP address received from Step 3. This results in two possible outcomes:
  1. If connect() fails or times out    -    The port is probably closed, hence ignored.
  2. If connect() succeeds              -    The port is surely open, hence displayed.

To make the above process faster, maximum of 100 processes at a time are allowed to connect to their ports. This way, the stop and wait condition is eliminated.
The timeouts are implemented in using gettimeofday() function.

If you want to speed the process up further, reduce the sleep value in line 155:     
```sleep(4)```

However, this might make your program skip a few open ports. So it is not recommended.



Do share if you liked my work. Thanks!

:smile:

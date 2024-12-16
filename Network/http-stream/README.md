# HTTP Client Example in C

---

## 🚀 **Project Overview**

This project demonstrates a simple HTTP client implemented in **C** that connects to a remote HTTP server, sends a basic GET request, and prints the server's response. The example uses low-level socket programming to establish a TCP connection and communicate with the server.

---

## 📂 **Table of Contents**

1. [Introduction](#introduction)  
2. [Features](#features)  
3. [Prerequisites](#prerequisites)  
4. [How to Build](#how-to-build)  
5. [How to Run](#how-to-run)  
6. [Code Walkthrough](#code-walkthrough)  
7. [Troubleshooting](#troubleshooting)  
8. [License](#license)  

---

## 🏆 **Introduction**

This project provides a basic example of how to:

- Establish a TCP connection to a server using sockets.  
- Send an HTTP GET request to fetch data from a web server.  
- Receive and process the server's response.

---

## ✨ **Features**

- Connects to `www.example.com` (or a server defined by its IP address).
- Sends a standard HTTP GET request to fetch the root page `/`.
- Handles basic TCP socket communication for sending and receiving data.
- Outputs the server's response directly to the console.

---

## 🖥️ **Prerequisites**

Before running the program, ensure you have:

- A **C compiler** like `gcc`.  
- A **Linux/Unix-based system** (since the example uses POSIX socket calls).  
- Basic understanding of how sockets and HTTP requests work.

---

## ⚙️ **How to Build**

1. Open a terminal on your Linux/Unix system.  
2. Navigate to the directory containing `http_client.c`.  
3. Compile the code using `gcc`:  

```bash
gcc -o http_client http_client.c
```

This will produce an executable named `http_client`.

---

## 🏃‍♂️ **How to Run**

After building the program, execute the client as follows:

```bash
./http_client
```

Upon execution, the client will connect to the server at `www.example.com`, send the request, and print the server's response in the terminal.

---

## 🛠️ **Code Walkthrough**

### 1. **Socket Creation**
The client initializes a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`:

```c
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
}
```

This establishes the communication endpoint for the HTTP request.

---

### 2. **Server Address Configuration**
The server's IP address (`93.184.216.34` for `www.example.com`) is set in the `server` struct:

```c
server.sin_addr.s_addr = inet_addr("93.184.216.34");
server.sin_family = AF_INET;
server.sin_port = htons(80);
```

Here:
- `AF_INET` denotes IPv4.  
- `htons(80)` sets the HTTP default port.

---

### 3. **Establish Connection**
The client attempts to connect to the server:

```c
if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
}
```

If the connection fails, an error is raised.

---

### 4. **Send the HTTP Request**
The client sends an HTTP GET request:

```c
if (send(sock, message, strlen(message), 0) < 0) {
    perror("Send failed");
    exit(EXIT_FAILURE);
}
```

The request follows the standard HTTP request format:

```text
GET / HTTP/1.1
Host: www.example.com
```

---

### 5. **Receive the Server Response**
The server's response is received using a loop:

```c
while (recv(sock, buffer, BUFFER_SIZE, 0) > 0) {
    printf("%s", buffer);
    memset(buffer, 0, BUFFER_SIZE);
}
```

The client keeps receiving data until no more is sent by the server.

---

### 6. **Close the Connection**
After data is fully received, the connection is closed:

```c
close(sock);
```

---

## 🛑 **Troubleshooting**

1. **Connection Refused Errors**:
   - Ensure your network allows access to the server's IP/port.
   - Confirm the server's IP and port are correct.

2. **Permission Denied**:
   - You might need appropriate permissions. Run as a normal user or adjust firewall rules if necessary.

3. **Compilation Issues**:
   - Ensure `gcc` is installed (`sudo apt install gcc`) and that there are no syntax errors.

4. **Network Unreachable**:
   - Check your connection to the internet or firewall configurations.
# 📊 Web-Based Live Polling System

## 📝 Introduction
The **Live Polling System** is a real-time voting application that allows multiple users to vote and instantly see results. The system is built using:

- **C** for backend socket communications.
- **Python** as a relay layer for message forwarding.
- **JavaScript** (WebSockets) for real-time web updates.

This architecture ensures a **fast, efficient, and scalable** voting system.

---

## 🏗 System Overview
The system follows a **Client-Server Model** with a **Relay Layer** to facilitate smooth communication between different components.

### 📌 Components of the System

#### 1️⃣ Server (`server.c`)
- Manages incoming client connections.
- Processes and updates votes.
- Sends real-time vote counts to clients.

#### 2️⃣ Clients (`client.c`)
- Connects to the server to cast votes.
- Receives updated poll results from the server.
- Displays results dynamically in the console.

#### 3️⃣ Relay (`relay.py`)
- Acts as middleware between `server.c` and `client.c`.
- Uses Python sockets for message forwarding.
- Enhances scalability and reliability.

#### 4️⃣ Web Interface (`index.html`)
- Provides a graphical display of poll results.
- Uses WebSockets (JavaScript) for real-time updates.
- Dynamically displays vote counts.

---

## 🚀 Installation & Setup

### 📌 Prerequisites
Ensure you have the following installed:
- **GCC Compiler** (for C programs)
- **Python 3.x**
- **Web Browser** (for the web interface)

### 🛠 Steps to Run the Project

1️⃣ **Clone the Repository**
```sh
 git clone https://github.com/your-username/live-polling-system.git
 cd live-polling-system
```

2️⃣ **Compile and Start the Server**
```sh
gcc server.c -o server
./server
```

3️⃣ **Run the Relay Script**
```sh
python3 relay.py
```

4️⃣ **Start a Client to Vote**
```sh
gcc client.c -o client
./client
```

5️⃣ **Open the Web Interface**
- Open `index.html` in a browser to see live results.

---

## 🎯 Features
✅ Real-time voting updates 📊  
✅ Multi-user support 👥  
✅ Scalable and efficient ⚡  
✅ WebSocket-based live visualization 🌍  

---


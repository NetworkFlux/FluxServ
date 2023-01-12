# -- FluxServ --

## Usage (UNIX only) -- 👈

```bash
git clone https://github.com/NetworkFlux/FluxServ.git && cd FluxServ/v1-Fluxserv && make
```
To launch the server :
```bash
./server
```
Launch the script to launch multiple connection on another terminal to see how te server reacts :
```bash
bash manyclients.bash
```
## Topics -- 🗝
1. Web Server
2. HTTP
3. Thread Pools
4. Networking
5. System

## Challenge -- 💡
This project is about setting up functionnal and optimized HTTP Web Server. The server doesn't do much as it completely set for optimization. It utilize thread pools in order to handle a large amount of connections really fast.
It would of course need additionnal server behaviour but this wasn't the purpose of this project.

## Objectives -- ✅
- Creating and setting up an efficient system of thread pools.
- Getting familiar with networking and HTTP.
- Deep dive into reliability and optimizations

## Comments -- ⚙️
Be carefull because as this server is right now it is still vulnerable to some cyberattacks (DDOS). Make sure to secure it by youself if you plan on launching this in the wild ‼️

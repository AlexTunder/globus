#pragma once
#ifndef SCFD
#define SCFD 1
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <stdio.h>
#include <string.h> 
#include <string>
#include <sys/ioctl.h>
#include <net/if.h>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#define DEFAULT_LISTENER        0
#define STOP_LISTENER           1
#define FILE_REQUEST_LISTENER   2
#define STREAM_LISTENER         3
#define SOCKEXC_DISCONN         0x71
#define SOCKEXC_BROKENP         0x71

class Socket{
    public:
        /** Comment this later **/
        Socket();
        char *buffer;
        int bitrade;
        struct sockaddr_in address; 
        int fd, **connection, opt, cc;
        size_t al = sizeof(address);
        /** Communicate with connection **/
        std::string read();
        std::string read(int conn);
        int send(std::string data);
        int send(std::string data, int conn);
        /** Connection managment; **/
        int kill(int conn);
        int close(int conn);
        int addConnection();
        int setActive(int conn);
        int setBitrade(int bitrade);
        char *setBuffer(char *buffer);
};

class ___SockPTR___uniQED__{
    public:
        ___SockPTR___uniQED__(void *client, bool isServer);
        int *fd;
        int **conn;
        int *cc;
        int *bitrade;
        char *buffer;
        /** Communicate with connection **/
        std::string read();
        std::string read(int conn);
        int send(std::string data);
        int send(std::string data, int conn);
        /** Connection managment; **/
        int kill(int conn);
        int close(int conn);
        int setBitrade(int bitrade);
        char *setBuffer(char *buffer);
        int connn;
};

class SocketException{
    public:
        SocketException(char *address, char *description, char *additional, int port, int code);
        char *address, *description, *additional;
        int port, codeOfError;
};

class NetworkListener;

class SocketServer : public Socket{
    public:
        struct throwenSocketServerStruct{
            SocketServer *socketServer = nullptr;
            void *(*listener)(void *arg);
            int connectionID;
            ___SockPTR___uniQED__ *sockPtr = nullptr;
        };
        /*** I should to use this structure, becouse it's have dependes ***/
        int bind(std::string addr, int port, int protocol = SOCK_STREAM);
        void start(void *(*listener)(void *arg), int maxClients);
        void start(NetworkListener *listener, int maxClients);
        struct throwenSocketServerStruct arg;
        static void *listen(void *arg);
        pthread_t **threadStorage;
        NetworkListener *listener;
        int port; std::string me;
        pthread_t mainThread;
        pthread_attr_t attr;
        SocketServer();
        int state = 0;
        pthread_mutex_t mutex;
        pthread_mutexattr_t mutexattr;
};

class NetworkListener{
    private:
        char command[3][3];
        struct listenersStruct{
            ___SockPTR___uniQED__ *arg;
            void (*stopListener)(void *arg);
            void (*streamListener)(void *arg);
            void (*defaultListener)(void *arg);
            void (*fileReaquestListener)(void *arg);
        }listeners;
        void *(*mainListener)(void *parg);
    public:
        // char*read(void *arg);
        void setStopCom(char com[3]);
        void setStreanCom(char com[3]);
        // void send(void *arg,char *data);
        static void *threadable(void *arg);
        void setFileRequestCom(char com[3]);
        // char*read(void (*descriptor)(char *));
        // void send(char *data, void (*descriptor)(char *));
        void SetListener(int type, void (*listener)(void *parg));

        void Set___SockPTR___uniQED__(___SockPTR___uniQED__ *sockptr);
};

class SocketClient : public Socket{
    public:
        SocketClient();
        int connect(std::string addr, int port, int protocol = SOCK_STREAM);
        int read();
};

class throwNetAttr{
    public:
        SocketServer::throwenSocketServerStruct *ptsd;
        int connID;
        NetworkListener *listener;
        throwNetAttr(SocketServer::throwenSocketServerStruct *netData, int connID); 
        throwNetAttr(SocketServer::throwenSocketServerStruct *attr, int conn, NetworkListener *listener);
};

class ListenerStream{
    private:
        throwNetAttr *attributes;
        char *buffer;
    public:
        void close();
        int getCurrent();
        std::string read();
        ListenerStream(void *arg);
        void send(std::string data);
        void setBuffer(char *buffer);
};

class Coder{
    private:
        char *src, *out;
    public:
        void (*algo)(char*, char*);
};

class Encoder : public Coder{
    public:
        char *operator()(char *src, char *key);
};

class Decoder : public Coder{
    public:
        char *operator()(char *src, char *key);
};

void anonimusEncode(char*, char*);
void anonimusDecode(char*, char*);

___SockPTR___uniQED__* getSockPointerFromAttr(SocketServer::throwenSocketServerStruct *attr);

#define netServerAttribures SocketServer::throwenSocketServerStruct
#define NetworkAttributes ___SockPTR___uniQED__ 
#include "Socket.cpp"
#endif
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <arpa/inet.h>
#include <unistd.h>

typedef struct _TcpHandle {
    int m_sockFD;
    char m_recvBuf[1024];
    struct sockaddr_in m_servAddr;
} TcpHandle;

struct _TcpClientMap {
    TcpHandle * (*Create)(const char *host, int port);
    void (*Close)(TcpHandle *a_handle);
    size_t (*Send)(TcpHandle *a_handle, char *a_buffer, size_t a_length);
    size_t (*Read)(TcpHandle *a_handle, char *a_buffer, size_t a_maxLength);

};

const struct _TcpClientMap TcpClient;

#endif

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "TcpSocket.h"

static TcpHandle *Create(const char *host, int port)
{
    TcpHandle *handle = malloc(sizeof(TcpHandle));
    handle->m_sockFD = 0;
    memset(handle->m_recvBuf, 0, sizeof(handle->m_recvBuf));

    handle->m_sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (handle->m_sockFD < 0)
    {
        free(handle);
        return NULL;
    }

    memset(&(handle->m_servAddr), '0', sizeof(handle->m_servAddr));
    handle->m_servAddr.sin_family = AF_INET;
    handle->m_servAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &(handle->m_servAddr).sin_addr) <= 0)
    {
        free(handle);
        return NULL;
    }

    if (connect(handle->m_sockFD, (struct sockaddr *)&(handle->m_servAddr),
                sizeof(handle->m_servAddr)) < 0)
    {
        free(handle);
        return NULL;
    }

    return handle;
}

static void Close(TcpHandle *a_handle) {
    close(a_handle->m_sockFD);
    free(a_handle);
}

static size_t Send(TcpHandle *a_handle, char *a_buffer, size_t a_length)
{
    return write(a_handle->m_sockFD, a_buffer, a_length);
}

static size_t Read(TcpHandle *a_handle, char *a_buffer, size_t a_maxLength)
{
    return read(a_handle->m_sockFD, a_buffer, a_maxLength);
}

const struct _TcpSocketMap TcpSocket = {
    .Create = Create,
    .Close = Close,
    .Send = Send,
    .Read = Read,
};

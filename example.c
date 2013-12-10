#include <stdio.h>
#include <string.h>

#include "TcpClient.h"

int main(int argc, char **argv) {
    char *host;
    int port;
    char response[256];
    size_t len;

    if (argc > 3)
    {
        TcpHandle *handle = TcpClient.Create(argv[1], atoi(argv[2]));
        if (handle)
        {
            printf("\n-> %s\n", argv[3]);
            TcpClient.Send(handle, argv[3], strlen(argv[3]));
            TcpClient.Send(handle, "\n", strlen("\n"));
            len = TcpClient.Read(handle, response, sizeof(response)-1);
            response[len] = 0;
            printf("\n<- %s\n", response);
            TcpClient.Close(handle);
        }
        else
        {
            printf("Failed to connect to %s:%s\n", argv[1], argv[2]);
        }
    }
    else
    {
        printf("Usage: %s host port message\n", argv[0]);
    }
}

#include "LpcProxy.h"
#include "Lpc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int sendqid;
int receiveqid;

void Init(void) {
    sendqid = msgget(ftok("12", 1), IPC_CREAT | 0644);

    receiveqid = msgget(ftok("21", 1), IPC_CREAT | 0644);
}

int OpenFile(char *path, int flags) {

    int a1;
    int a2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_OPEN_FILE;
    pLpcRequest.numArg = 2;
    strcpy(pLpcRequest.lpcArgs[0].argData, path);
    pLpcRequest.lpcArgs[0].argSize = sizeof(path);
    sprintf(pLpcRequest.lpcArgs[1].argData, "%d", flags);
    pLpcRequest.lpcArgs[1].argSize = 4;

    if ((a1 = msgsnd(sendqid, (void *)&pLpcRequest,
                     sizeof(LpcRequest) - sizeof(long), 0)) == -1) {
        perror("msgsnd() error");
        return -1;
    }

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    a2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    return atoi(pLpcResponse->responseData);
}

int ReadFile(int fd, void *pBuf, int size) {

    int b1;
    int b2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_READ_FILE;
    pLpcRequest.numArg = 2;
    sprintf(pLpcRequest.lpcArgs[0].argData, "%d", fd);
    pLpcRequest.lpcArgs[0].argSize = 4;
    sprintf(pLpcRequest.lpcArgs[1].argData, "%d", size);
    pLpcRequest.lpcArgs[1].argSize = 4;

    b1 = msgsnd(sendqid, (void *)&pLpcRequest,
                sizeof(LpcRequest) - sizeof(long), 0);

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    b2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    strcpy((char *)pBuf, pLpcResponse->responseData);
    return pLpcResponse->responseSize;
}

int WriteFile(int fd, void *pBuf, int size) {

    int c1;
    int c2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_WRITE_FILE;
    pLpcRequest.numArg = 3;
    sprintf(pLpcRequest.lpcArgs[0].argData, "%d", fd);
    pLpcRequest.lpcArgs[0].argSize = 4;
    strcpy(pLpcRequest.lpcArgs[1].argData, pBuf);
    pLpcRequest.lpcArgs[1].argSize = sizeof(pBuf);
    sprintf(pLpcRequest.lpcArgs[2].argData, "%d", size);
    pLpcRequest.lpcArgs[2].argSize = 4;

    c1 = msgsnd(sendqid, (void *)&pLpcRequest,
                sizeof(LpcRequest) - sizeof(long), 0);

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    c2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    return atoi(pLpcResponse->responseData);
}

off_t SeekFile(int fd, off_t offset, int whence) {

    int d1;
    int d2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_SEEK_FILE;
    pLpcRequest.numArg = 3;
    sprintf(pLpcRequest.lpcArgs[0].argData, "%d", fd);
    pLpcRequest.lpcArgs[0].argSize = 4;
    sprintf(pLpcRequest.lpcArgs[1].argData, "%ld", offset);
    pLpcRequest.lpcArgs[1].argSize = sizeof(offset);
    sprintf(pLpcRequest.lpcArgs[2].argData, "%d", whence);
    pLpcRequest.lpcArgs[2].argSize = 4;

    d1 = msgsnd(sendqid, (void *)&pLpcRequest,
                sizeof(LpcRequest) - sizeof(long), 0);

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    d2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    return (off_t)atoi(pLpcResponse->responseData);
}

int CloseFile(int fd) {

    int e1;
    int e2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_CLOSE_FILE;
    pLpcRequest.numArg = 1;
    sprintf(pLpcRequest.lpcArgs[0].argData, "%d", fd);
    pLpcRequest.lpcArgs[0].argSize = 4;

    e1 = msgsnd(sendqid, (void *)&pLpcRequest,
                sizeof(LpcRequest) - sizeof(long), 0);

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    e2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    return atoi(pLpcResponse->responseData);
}

int MakeDirectory(char *path, int mode) {

    int f1;
    int f2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_MAKE_DIRECTORY;
    pLpcRequest.numArg = 2;
    strcpy(pLpcRequest.lpcArgs[0].argData, path);
    pLpcRequest.lpcArgs[0].argSize = sizeof(path);
    sprintf(pLpcRequest.lpcArgs[1].argData, "%d", mode);
    pLpcRequest.lpcArgs[1].argSize = 4;

    f1 = msgsnd(sendqid, (void *)&pLpcRequest,
                sizeof(LpcRequest) - sizeof(long), 0);

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    f2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    return atoi(pLpcResponse->responseData);
}

int RemoveDirectory(char *path) {

    int g1;
    int g2;

    LpcRequest pLpcRequest;

    pLpcRequest.pid = getpid();
    pLpcRequest.service = LPC_REMOVE_DIRECTORY;
    pLpcRequest.numArg = 1;
    strcpy(pLpcRequest.lpcArgs[0].argData, path);
    pLpcRequest.lpcArgs[0].argSize = sizeof(path);

    g1 = msgsnd(sendqid, (void *)&pLpcRequest,
                sizeof(LpcRequest) - sizeof(long), 0);

    LpcResponse *pLpcResponse;
    pLpcResponse = malloc(sizeof(LpcResponse));

    g2 = msgrcv(receiveqid, pLpcResponse, sizeof(LpcResponse) - sizeof(long),
                pLpcRequest.pid, 0);
    return atoi(pLpcResponse->responseData);
}

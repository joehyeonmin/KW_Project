#include "LpcStub.h"

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

int requestqid;
int responseqid;

void Init(void) {

    requestqid = msgget(ftok("12", 1), IPC_CREAT | 0644);

    responseqid = msgget(ftok("21", 1), IPC_CREAT | 0644);
}
int OpenFile(char *path, int flag, int clientPid) {

    int fd;
    int a;

    if (flag == O_CREAT) {

        fd = open(path, flag, S_IRUSR | S_IWUSR);
    }

    else {
        fd = open(path, flag);
    }

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    sprintf(pLpcResponse.responseData, "%d", fd);
    pLpcResponse.responseSize = 4;

    a = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);

    return fd;
}

int ReadFile(int fd, int readCount, int clientPid) {

    int fd2;
    int b;
    char readc[readCount];

    fd2 = read(fd, readc, sizeof(readc));

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    strcpy(pLpcResponse.responseData, readc);
    pLpcResponse.responseSize = fd2;

    b = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);
    return fd2;
}

int WriteFile(int fd, char *readc, int writeCount, int clientPid) {

    int fd3;
    int c;

    fd3 = write(fd, readc, writeCount);

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    sprintf(pLpcResponse.responseData, "%d", fd3);
    pLpcResponse.responseSize = 4;

    c = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);
    return fd3;
}

off_t SeekFile(int fd, off_t offset, int whence, int clientPid) {

    off_t off;
    int d;

    off = lseek(fd, offset, whence);

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    sprintf(pLpcResponse.responseData, "%ld", off);
    pLpcResponse.responseSize = sizeof(off);

    d = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);
    return off;
}

int CloseFile(int fd, int clientPid) {

    int e;
    int temp;

    temp = close(fd);

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    sprintf(pLpcResponse.responseData, "%d", temp);
    pLpcResponse.responseSize = 4;

    e = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);
    return 0;
}

int MakeDirectory(char *path, int mode, int clientPid) {

    int f;
    int mk;

    mk = mkdir(path, mode);

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    sprintf(pLpcResponse.responseData, "%d", mk);
    pLpcResponse.responseSize = 4;

    f = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);
    return mk;
}

int RemoveDirectory(char *path, int clientPid) {

    int g;
    int rm;

    rm = rmdir(path);

    LpcResponse pLpcResponse;
    pLpcResponse.pid = clientPid;
    pLpcResponse.errorno = 0;
    sprintf(pLpcResponse.responseData, "%d", rm);
    pLpcResponse.responseSize = 4;

    g = msgsnd(responseqid, (void *)&pLpcResponse,
               sizeof(LpcResponse) - sizeof(pLpcResponse.pid), 0);
    return rm;
}

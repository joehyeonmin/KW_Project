#include "Lpc.h"
#include "LpcStub.h"
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

int main(void) {

    int a;

    Init();
    requestqid = msgget(ftok("12", 1), IPC_CREAT | 0644);

    responseqid = msgget(ftok("21", 1), IPC_CREAT | 0644);

    // request
    LpcRequest *pLpcRequest;
    pLpcRequest = malloc(sizeof(LpcRequest));

    while (1) {

        a = msgrcv(requestqid, pLpcRequest, sizeof(LpcRequest) - sizeof(long),
                   0, 0);

        if (a < 0)
            continue;

        if (pLpcRequest->service == LPC_OPEN_FILE) {
            OpenFile(pLpcRequest->lpcArgs[0].argData,
                     atoi(pLpcRequest->lpcArgs[1].argData), pLpcRequest->pid);
            continue;
        }

        else if (pLpcRequest->service == LPC_READ_FILE) {
            ReadFile(atoi(pLpcRequest->lpcArgs[0].argData),
                     atoi(pLpcRequest->lpcArgs[1].argData), pLpcRequest->pid);
            continue;
        }

        else if (pLpcRequest->service == LPC_WRITE_FILE) {
            WriteFile(atoi(pLpcRequest->lpcArgs[0].argData),
                      pLpcRequest->lpcArgs[1].argData,
                      atoi(pLpcRequest->lpcArgs[2].argData), pLpcRequest->pid);
            continue;
        }

        else if (pLpcRequest->service == 6) {
            SeekFile(atoi(pLpcRequest->lpcArgs[0].argData),
                     (off_t)atoi(pLpcRequest->lpcArgs[1].argData),
                     atoi(pLpcRequest->lpcArgs[2].argData), pLpcRequest->pid);
            continue;
        }

        else if (pLpcRequest->service == LPC_CLOSE_FILE) {
            CloseFile(atoi(pLpcRequest->lpcArgs[0].argData), pLpcRequest->pid);
            continue;
        }

        else if (pLpcRequest->service == LPC_MAKE_DIRECTORY) {
            MakeDirectory(pLpcRequest->lpcArgs[0].argData,
                          atoi(pLpcRequest->lpcArgs[1].argData),
                          pLpcRequest->pid);
            continue;
        }

        else if (pLpcRequest->service == LPC_REMOVE_DIRECTORY) {
            RemoveDirectory(pLpcRequest->lpcArgs[0].argData, pLpcRequest->pid);
            continue;
        }

        else {
            perror("error");
            continue;
        }
    }

    return 0;
}

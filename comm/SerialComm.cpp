#include "SerialComm.h"


void btInterrupt() {
    flag.set(BT_READABLE);
}

void rpiInterrupt() {
    flag.set(RPI_READABLE);
}

void inputProcess() {
    const int BUF_SIZE = 32;

    char btBuf[BUF_SIZE], rpiBuf[BUF_SIZE], ch;
    int btPtr = 0, rpiPtr = 0;

    auto charProcess = [&](char buffer[], int &ptr) {
        if (ch == '\n' || ch == '\r' || ch == '\0' || ptr == 31) {
            buffer[ptr] = '\0';
            CmdInfo *msg = cmdMail.alloc();
            if (msg) {
                std::memcpy(msg->text, buffer, ptr + 1);
                msg->len = ptr;
                cmdMail.put(msg);
            }
            memset(buffer, 0, BUF_SIZE);
            ptr = 0;
        } else {
            buffer[ptr++] = ch;
        }
    };

    while (true) {
        flag.wait_any(BT_READABLE | RPI_READABLE);

        while (bt.readable()) {
            bt.read(&ch, 1);
            charProcess(btBuf, btPtr);
        }

        while (rpi.readable()) {
            rpi.read(&ch, 1);
            charProcess(rpiBuf, rpiPtr);
        }
    }
}

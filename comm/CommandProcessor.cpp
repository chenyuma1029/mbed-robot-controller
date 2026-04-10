#include "CommandProcessor.h"
#include "../common_libs/Vector.hpp"

void cmdProcess(const char* text, int len) {
    printf("Len: %d, %s\r\n", len, text);
    bt.write(text, strlen(text));
    fflush(stdout);

    
    if (text[0] == '#') {
        char command = text[2];

        if (isupper(command)) {
            Direction tmp(0, 0, 0, 0);
            auto update = [&] {
                carMotion.addDir(tmp);
                carMotion.updateMotion();
            };
            switch (command) {
                case 'U': tmp.f = 1; update(); break;
                case 'D': tmp.b = 1; update(); break;
                case 'L': tmp.l = 1; update(); break;
                case 'R': tmp.r = 1; update(); break;
                case 'B': carMotion.setRotation(-1); break;
                case 'E': carMotion.setRotation(1);  break;
                case 'S':
                    sonicSwitch = !sonicSwitch;
                    char str[32];
                    sprintf(str, "Ultrasonic Mode: %d\n", sonicSwitch);
                    bt.write(str, strlen(str));
                    break;
            }
        }

        if (islower(command)) {
            Direction tmp(1, 1, 1, 1);
            auto update = [&] {
                carMotion.delDir(tmp);
                carMotion.updateMotion();
            };
            switch (command) {
                case 'u': tmp.f = 0; update(); break;
                case 'd': tmp.b = 0; update(); break;
                case 'l': tmp.l = 0; update(); break;
                case 'r': tmp.r = 0; update(); break;
                case 'b':
                case 'e': carMotion.setRotation(0); break;
                case 's': break;
            }
        }
    }

    
    if (text[0] == ':') {
        char command[16];
        sscanf(text + 2, "%15s", command);

        if (strcmp(command, "SPD") == 0) {
            int speed;
            sscanf(text + 6, "%d", &speed);
            carMotion.setBaseSpeed(5 + speed * 0.5);
        }

        if (strcmp(command, "V") == 0) {
            double vx, vy;
            sscanf(text + 4, "%lf%lf", &vx, &vy);
            carMotion.updateMotion(Vector<double>(vx, vy));
        }

        if (strcmp(command, "SM") == 0) {
            char mode[8];
            sscanf(text + 5, "%7s", mode);
            if (strcmp(mode, "JS") == 0) carMotion.changeMode(JOYSTICK);
            if (strcmp(mode, "BT") == 0) carMotion.changeMode(BUTTON);
        }

        if (strcmp(command, "OBJ") == 0) {
            
        }

        bool isRpi = ((strcmp(command, "SVO") == 0) ||
                       (strcmp(command, "CAM") == 0) ||
                       (strcmp(command, "TRK") == 0) ||
                       (strcmp(command, "AI")  == 0));

        if (isRpi) {
            char msg[32];
            sprintf(msg, "Sent \"%s\"\n", text);
            bt.write(msg, strlen(msg));
            memset(msg, 0, sizeof(msg));
            sprintf(msg, "%s\n", text);
            rpi.write(msg, strlen(msg));
        }
    }
}

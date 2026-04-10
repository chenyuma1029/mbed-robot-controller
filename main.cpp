#include "config.h"
#include "SerialComm.h"
#include "CommandProcessor.h"


StdMotor BR(p21, p19, p18, period);
StdMotor BL(p22, p17, p16, period);
StdMotor FR(p23, p15, p14, period);
StdMotor FL(p24, p13, p12, period);
MotionControl carMotion(FL, FR, BL, BR);

BufferedSerial pc(USBTX, USBRX);
BufferedSerial bt(p9, p10);
BufferedSerial rpi(p28, p27);
Ultrasonic sonar(p29, p30);


bool sonicSwitch = 0;
EventFlags flag;
Mail<CmdInfo, 16> cmdMail;


Thread inputThread;

int main() {
   
    bt.sigio(callback(btInterrupt));
    bt.set_blocking(0);
    bt.set_baud(9600);

    
    rpi.sigio(callback(rpiInterrupt));
    rpi.set_blocking(1);
    rpi.set_baud(115200);

   
    inputThread.start(callback(inputProcess));

    printf("Successfully started.\n");

    while (true) {
       
        float dist      = sonar.getDistance();
        float distLimit  = 15 * speedGrade - 70;
        bool  isLocked   = (sonicSwitch && dist < distLimit && dist > 2.0f);

        FL.setForwardLock(isLocked);
        FR.setForwardLock(isLocked);
        BL.setForwardLock(isLocked);
        BR.setForwardLock(isLocked);

       
        osEvent evt = cmdMail.get(0);
        if (evt.status == osEventMail) {
            CmdInfo* msg = (CmdInfo*)evt.value.p;
            cmdProcess(msg->text, msg->len);
            cmdMail.free(msg);
        }
    }
}

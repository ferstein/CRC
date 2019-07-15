#ifndef CAMERA_H
#define CAMERA_H
#include "VISCA.h"
#include "serialport.h"
class Camera
{
public:
    Camera();
    ~Camera();
    unsigned int CamCtrlEnabled;
    int CommandSelector;
    int ZoomJoy;
    int FocusPosJoy;
    int FocusSpeedJoy;
    float ZoomMagnification; //from camera
    unsigned int DigitalZoomValue;
    void Init(void);
    void process(void);
    float ZoomPositionToMagnification(uint32_t position);
private:
    int ZoomPosCalc;         // integrain and limitting result from ZoomJoy
    int ZoomSpeed;
    int FocusPos;
    serialport serial;
    int fd;
};

#endif // CAMERA_H

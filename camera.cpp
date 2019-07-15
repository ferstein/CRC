#include "camera.h"
#include "VISCA.h"
#include "serialport.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

Camera::Camera()
{
    Init();
}
Camera::~Camera()
{
    close(fd);
}

void Camera::Init(void)
{
    printf ("Opening camera control serial port! \n");
    fd=serial.init("/dev/ttyO4",Baud115200);
    if(fd>0) printf("Camera serial opened %i \n",fd);
    else perror("Camera serial error :");
    CamCtrlEnabled=1;
    camEO.camnum=CAM1;
    camEO.category=VISCA_CATEGORY_CAMERA1;
}

void Camera::process(void)
{
    switch(CommandSelector){
    case 0:{ //Zoom speed control section
        ZoomSpeed = abs(ZoomJoy/40);
        if(ZoomSpeed>7)ZoomSpeed=7;
        if(ZoomJoy>1) {camEO.command=visca_zoom_tele_speed;}
        else
            if(ZoomJoy<-1){camEO.command=visca_zoom_wide_speed;}
            else {camEO.command=visca_zoom_stop;}
        camEO.value=ZoomSpeed;
    }break;
    case 1:{ //Focus
        FocusPos+=FocusSpeedJoy;
        if(FocusPos<0x1000)FocusPos=0x1000;
        if(FocusPos>0xE000)FocusPos=0xE000;
        int focus = FocusPos+FocusPosJoy*10;
        if(focus<0x1000)focus=0x1000;
        if(focus>0xE000)focus=0xE000;
        camEO.command=visca_focus_direct;
        camEO.value = focus;
        CommandSelector=10;
    }break;
    case 2:{camEO.command=visca_focus_manual;}break;           //Focus manual
    case 3:{camEO.command=visca_focus_auto;}break;             //Focus Auto
    case 4:{camEO.command=visca_focus_one_push_trigger;}break; //Focus One Push;
    case 5:{camEO.command=visca_dzoom_on; }break;              //Digital zoom on
    case 6:{camEO.command=visca_dzoom_off; }break;             //Digital zoom off
    case 7:{camEO.command=visca_dzoom_separate_mode; }break;   //Digital zoom separate
    case 8:{camEO.command=visca_dzoom_combine_mode; }break;    //Digital zoom combine mode
    case 9:{camEO.command=visca_dzoom_direct;                  //Digital zoom direct
        if(DigitalZoomValue>0xeb)DigitalZoomValue = 0xeb;
        camEO.value = DigitalZoomValue;}break;
    default :{CommandSelector=0;}break;
    }
    if(CamCtrlEnabled!=0){
        ViscaCamCommandPack(&visca_paket,&camEO);
        write(fd,&visca_paket.bytes,visca_paket.length);
        write(fd,"\r\n",2);

        if(CommandSelector==0){
            camEO.inquiry=CAM_ZoomPosInq;
            ViscaInquiryCommandPack(&visca_paket,&camEO);
            write(fd,&visca_paket.bytes,visca_paket.length);
            write(fd,"\r\n",2);
        }
    }

    CommandSelector++;
    if(CommandSelector>1)CommandSelector=0;

    char buf[40];
    int len;
    len = read(fd,&buf,100);
    if(len>0){

        //printf("Camera says %i \n",len);
        //for(int i=0;i<len;i++) printf("0x%02X ",buf[i]);
        //printf("\n");

        ViscaParseBuf ((uint8_t*)buf,len ,&viscaParser,&camEO);
        ZoomMagnification=( ZoomMagnification*0.8 ) + (0.2* ZoomPositionToMagnification(camEO.ZoomPosition));
    }
}
float Camera::ZoomPositionToMagnification(uint32_t position)
{
    int i;
    float opt,dig;
    const uint16_t OpticalZoomTable [12]={
        /* 1× */0x0000,/* 2× */0x1970,/* 3× */0x249C,/* 4× */0x2B5F,
        /* 5× */0x3020,/* 6× */0x33C4,/* 7× */0x36B7,/* 8× */0x392F,
        /* 9× */0x3B4D,/* 10× */0x3D1E,/* 11× */0x3EAD,/* 12× */0x4000};

    const uint16_t DigitalZoomTable [12]={
        /* 1× */0x4000,/* 2× */0x6000,/* 3× */0x6A80,/* 4× */0x7000,
        /* 5× */0x7300,/* 6× */0x7540,/* 7× */0x76C0,/* 8× */0x7800,
        /* 9× */0x78C0,/* 10× */ 0x7980,/* 11× */ 0x7A00,/* 12× */ 0x7AC0};
    //if(position==0)return(1);
    if(position<OpticalZoomTable[11]){
        for(i=1;OpticalZoomTable[i]<=position;i++)
        {
            if(i==12){break;}
        }
        opt=i;
        float f = ((float)(position-OpticalZoomTable[i-1]));
        float f1 = ((float)(OpticalZoomTable[i]-OpticalZoomTable[i-1]));
        if(f1!=0){opt+=f/f1;}
        dig=1.0f;
    }
    else
    {
        opt=12.0f;
        for(i=1;DigitalZoomTable[i]<=position;i++)
        {
            if(i==12){break;}
        }
        dig=i;

        float f = ((float)(position-DigitalZoomTable[i-1]));
        float f1 = ((float)(DigitalZoomTable[i]-DigitalZoomTable[i-1]));
        if(f1!=0){dig+=f/f1;}
    }
    return (opt*dig);
}

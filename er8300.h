#ifndef ER8300_H
#define ER8300_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

class er8300
{
public:
    er8300();
};
    /*
    struct CameraContext {
        Power_t Power;
        uint16_t Zoom;
        uint8_t DZoom;
    };

};
typedef enum Generic{
    On = 0x02,
    Off= 0x03,
}Generic_t;

typedef enum Power{
    On = 0x0002,
    Off= 0x0003,
}Power_t;
typedef enum DZoomMode{
    On = 0x0602,
    Off= 0x0603,
    SuperResolution  = 0x0604,
    Combine = 0x3600,
    Separate = 0x3601,
}DZoomMode_t;

typedef struct DZoom{
    DZoomMode_t Mode;

}DZoom_t;

    //_____________________________________________________________________________________

    typedef  struct RegisterSettings{
        uint8_t InitialSettings;
        uint8_t RegisterNum;
        char RegisterName[32];
        uint8_t NumPossibleValues;
        uint8_t PossibleValues[20];
        char ValuesDescription[20][120];
    }Registercontent_t;
*/
#ifdef __cplusplus
} /* closing brace for extern "C" */

#endif

#endif // ER8300_H



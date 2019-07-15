#ifndef __VISCA_H__
#define __VISCA_H__

#include "stdint.h"
#include <stdbool.h>
/**********************/
/* Message formatting */
/**********************/
#define VISCA_DEFAULT_CAM_NR             0x01
#define VISCA_COMMAND                    0x01
#define VISCA_INQUIRY                    0x09
#define VISCA_TERMINATOR                 0xFF

#define VISCA_BROADCAST      0x88
#define VISCA_HEADER         0x80


/* Known Vendor IDs */
#define VISCA_VENDOR_SONY    0x0020

/* Known Model IDs. The manual can be taken from  */

#define VISCA_MODEL_IX47x    0x0401          /* from FCB-IX47, FCB-IX470 instruction list */
#define VISCA_MODEL_EX47xL   0x0402          /* from FCB-EX47L, FCB-EX470L instruction list */
#define VISCA_MODEL_IX10     0x0404          /* FCB-IX10, FCB-IX10P instruction list */
#define VISCA_MODEL_EX780    0x0411          /* from EX780S(P) tech-manual */
#define VISCA_MODEL_EX480A   0x0412          /* from EX48A/EX480A tech-manual */
#define VISCA_MODEL_EX480AP  0x0413
#define VISCA_MODEL_EX48A    0x0414
#define VISCA_MODEL_EX48AP   0x0414
#define VISCA_MODEL_EX45M    0x041E
#define VISCA_MODEL_EX45MCE  0x041F
#define VISCA_MODEL_IX47A    0x0418          /* from IX47A tech-manual */
#define VISCA_MODEL_IX47AP   0x0419
#define VISCA_MODEL_IX45A    0x041A
#define VISCA_MODEL_IX45AP   0x041B
#define VISCA_MODEL_IX10A    0x041C          /* from IX10A tech-manual */
#define VISCA_MODEL_IX10AP   0x041D
#define VISCA_MODEL_EX780B   0x0420          /* from EX78/EX780 tech-manual */
#define VISCA_MODEL_EX780BP  0x0421
#define VISCA_MODEL_EX78B    0x0422
#define VISCA_MODEL_EX78BP   0x0423
#define VISCA_MODEL_EX480B   0x0424          /* from EX48/EX480 tech-manual */
#define VISCA_MODEL_EX480BP  0x0425
#define VISCA_MODEL_EX48B    0x0426
#define VISCA_MODEL_EX48BP   0x0427
#define VISCA_MODEL_EX980S   0x042E          /* from EX98/EX980 tech-manual */
#define VISCA_MODEL_EX980SP  0x042F
#define VISCA_MODEL_EX980    0x0430
#define VISCA_MODEL_EX980P   0x0431
#define VISCA_MODEL_H10      0x044A	         /* from H10 tech-manual */
#define VISCA_MODEL_FCB_EV7500 0x0467
#define VISCA_MODEL_FCB_ER8300 0x0700
#define VISCA_MODEL_FCB_CR8300 0x0701

/**************************/
/* DIRECT REGISTER ACCESS */
/**************************/

#define VISCA_REGISTER_VALUE                0x24

#define VISCA_REGISTER_VISCA_BAUD           0x00
#define VISCA_REGISTER_BD9600               0x00
#define VISCA_REGISTER_BD19200              0x01
#define VISCA_REGISTER_BD38400              0x02

/* FCB-H10: Video Standard */
#define VISCA_REGISTER_VIDEO_SIGNAL         0x70

#define VISCA_REGISTER_VIDEO_1080I_60       0x01
#define VISCA_REGISTER_VIDEO_720P_60        0x02
#define VISCA_REGISTER_VIDEO_D1_CROP_60     0x03
#define VISCA_REGISTER_VIDEO_D1_SQ_60       0x04

#define VISCA_REGISTER_VIDEO_1080I_50       0x11
#define VISCA_REGISTER_VIDEO_720P_50        0x12
#define VISCA_REGISTER_VIDEO_D1_CROP_50     0x13
#define VISCA_REGISTER_VIDEO_D1_SQ_50       0x14


/*****************/
/* D30/D31 CODES */
/*****************/
#define VISCA_WIDE_CON_LENS		             0x26
#define VISCA_WIDE_CON_LENS_SET            0x00

#define VISCA_AT_MODE                      0x01
#define VISCA_AT_ONOFF                     0x10
#define VISCA_AT_AE                        0x02
#define VISCA_AT_AUTOZOOM                  0x03
#define VISCA_ATMD_FRAMEDISPLAY            0x04
#define VISCA_AT_FRAMEOFFSET               0x05
#define VISCA_ATMD_STARTSTOP               0x06
#define VISCA_AT_CHASE                     0x07
#define VISCA_AT_CHASE_NEXT                0x10

#define VISCA_MD_MODE                      0x08
#define VISCA_MD_ONOFF                     0x10
#define VISCA_MD_FRAME                     0x09
#define VISCA_MD_DETECT                    0x0A

#define VISCA_MD_ADJUST                    0x00
#define VISCA_MD_ADJUST_YLEVEL             0x0B
#define VISCA_MD_ADJUST_HUELEVEL           0x0C
#define VISCA_MD_ADJUST_SIZE               0x0D
#define VISCA_MD_ADJUST_DISPTIME           0x0F
#define VISCA_MD_ADJUST_REFTIME            0x0B
#define VISCA_MD_ADJUST_REFMODE            0x10

#define VISCA_AT_ENTRY                     0x15
#define VISCA_AT_LOSTINFO                  0x20
#define VISCA_MD_LOSTINFO                  0x21
#define VISCA_ATMD_LOSTINFO1               0x20
#define VISCA_ATMD_LOSTINFO2               0x07

#define VISCA_MD_MEASURE_MODE_1            0x27
#define VISCA_MD_MEASURE_MODE_2            0x28

#define VISCA_ATMD_MODE                    0x22
#define VISCA_AT_MODE_QUERY                0x23
#define VISCA_MD_MODE_QUERY                0x24
#define VISCA_MD_REFTIME_QUERY             0x11
#define VISCA_AT_POSITION                  0x20
#define VISCA_MD_POSITION                  0x21

/***************/
/* ERROR CODES */
/***************/

/* these two are defined by me, not by the specs. */
#define VISCA_SUCCESS                    0x00
#define VISCA_FAILURE                    0xFF

/* specs errors: */
#define VISCA_ERROR_MESSAGE_LENGTH       0x01
#define VISCA_ERROR_SYNTAX               0x02
#define VISCA_ERROR_CMD_BUFFER_FULL      0x03
#define VISCA_ERROR_CMD_CANCELLED        0x04
#define VISCA_ERROR_NO_SOCKET            0x05
#define VISCA_ERROR_CMD_NOT_EXECUTABLE   0x41

/* Generic definitions */
#define VISCA_ON                         0x02
#define VISCA_OFF                        0x03
#define VISCA_RESET                      0x00
#define VISCA_UP                         0x02
#define VISCA_DOWN                       0x03

/* response types */
#define VISCA_RESPONSE_CLEAR             0x40
#define VISCA_RESPONSE_ADDRESS           0x30
#define VISCA_RESPONSE_ACK               0x40
#define VISCA_RESPONSE_COMPLETED         0x50
#define VISCA_RESPONSE_ERROR             0x60
#ifdef __cplusplus
extern "C" {
#endif
typedef enum VISCA_commands
{
    //page 1/6  (sony ev-7500 manual)==================================================================================
    visca_addressset                = 0x3001,// 88 30 01 FF Address setting
    visca_if_clear                  = 0x0001,// 8x 01 00 01 FF , 88 01 00 01 FF I/F Clear
    command_cancel                  = 0x20FF,// 8x 2p FF p: Socket No. (=1 or 2)
    visca_power_on                  = 0x0002,// 8x 01 04 00 02 FF Power ON
    visca_power_off                 = 0x0003,// 8x 01 04 00 02 FF Power OFF
    visca_zoom_stop                 = 0x0700,// 8x 01 04 07 00 FF Stop
    visca_zoom_tele                 = 0x0702,// 8x 01 04 07 02 FF Tele (Standard)
    visca_zoom_wide                 = 0x0703,// 8x 01 04 07 03 FF Wide (Standard)
    visca_zoom_tele_speed           = 0x0720,// 8x 01 04 07 2p FF Tele (Variable)  p=0 (Low) to 7 (High)
    visca_zoom_wide_speed           = 0x0730,// 8x 01 04 07 3p FF Wide (Variable)
    visca_zoom_direct               = 0x4700,// 8x 01 04 47 0p 0q 0r 0s FF Direct pqrs: Zoom Position
    visca_zoom_focus                = 0x4799,
    visca_dzoom_on                  = 0x0602,// 8x 01 04 06 02 FF On Digital zoom ON/OFF
    visca_dzoom_off                 = 0x0603,// 8x 01 04 06 03 FF Off
    visca_dzoom_combine_mode        = 0x3600,// 8x 01 04 36 00 FF Combine Mode Optical/Digital Zoom Combined
    visca_dzoom_separate_mode       = 0x3601,// 8x 01 04 36 01 FF Separate Mode Optical/Digital Zoom Separate
    visca_dzoom_stop                = 0x0600,// 8x 01 04 06 00 FF Stop
    visca_dzoom_x1_max              = 0x0610,// 8x 01 04 06 10 FF x1/MAX Magnification Switchover, * Enabled during Separate Mode
    visca_dzoom_tele                = 0x0620,// 8x 01 04 06 2p FF Tele (Variable) p=0 (Low) to 7 (High),
    visca_dzoom_whide               = 0x0630,// 8x 01 04 06 3p FF * Enabled Wide (Variable)  during Separate Mode
    visca_dzoom_direct              = 0x4600,// 8x 01 04 46 00 00 0p 0q FF Direct pq: D-Zoom Position, * Enabled during Separate Mode
    visca_focus_stop                = 0x0800,// 8x 01 04 08 00 FF Stop
    visca_focus_far_standard        = 0x0802,// 8x 01 04 08 02 FF Far (Standard)
    visca_focus_near_standard       = 0x0803,// 8x 01 04 08 03 FF Near(Standard)
    visca_focus_far_variable        = 0x0820,// 8x 01 04 08 2p FF Far (Variable) p=0 (Low) to 7 (High)
    visca_focus_near_variable       = 0x0830,// 8x 01 04 08 3p FF Near(Variable)
    visca_focus_direct              = 0x4800,// 8x 01 04 48 0p 0q 0r 0s FF Direct pqrs: Focus Position
    visca_focus_auto                = 0x3802,// 8x 01 04 38 02 FF Auto Focus AF ON/OFF
    visca_focus_manual              = 0x3803,// 8x 01 04 38 03 FF Manual Focus
    visca_focus_auto_manual         = 0x3810,// 8x 01 04 38 10 FF Auto/Manual
    visca_focus_one_push_trigger    = 0x1801,// 8x 01 04 18 01 FF One Push AF Trigger
    visca_focus_near_limit          = 0x2800,// 8x 01 04 28 0p 0q 0r 0s FF pqrs: Focus Near Limit Position
    visca_af_sensitivity_normal     = 0x5802,// 8x 01 04 58 02 FF Normal AF Sensitivity High/Low
    visca_af_sensitivity_low        = 0x5803,// 8x 01 04 58 03 FF Low
    visca_af_mode_normal            = 0x5700,// AF 8x 01 04 57 00 FF AF Normal  Movement Mode
    visca_af_mode_interval          = 0x5701,// AF 8x 01 04 57 01 FF Interval
    visca_af_mode_zoom_trigger      = 0x5702,// 8x 01 04 57 02 FF Zoom Trigger AF
    visca_af_mode_active_interval_time=0x2700,//8x 01 04 27 0p 0q 0r 0s FF Active/Interval Time pq: Movement Time, rs: Interval
    visca_ircorrection_standard     = 0x1100,// 8x 01 04 11 00 FF Standard FOCUS IR compensation data switching
    visca_ircorrection_ir_light     = 0x1101,// 8x 01 04 11 01 FF IR Light
    visca_initialize_lens           = 0x1901,// 8x 01 04 19 01 FF Lens Initialization Start
    visca_initialize_camera         = 0x1903,// 8x 01 04 19 03 FF Camera reset
    //page 2/6  (sony ev-7500 manual)==================================================================================
    visca_cam_wb_auto               = 0x3500,// 8x 01 04 35 00 FF Normal Auto
    visca_cam_wb_indoor             = 0x3501,// 8x 01 04 35 01 FF Indoor mode
    visca_cam_wb_outdoor            = 0x3502,// 8x 01 04 35 02 FF Outdoor mode
    visca_cam_wb_one_push           = 0x3503,// 8x 01 04 35 03 FF One Push WB mode
    visca_cam_wb_atw                = 0x3504,// 8x 01 04 35 04 FF Auto Tracing White Balance
    visca_cam_wb_manual             = 0x3505,// 8x 01 04 35 05 FF Manual Control mode
    visca_cam_wb_one_push_trigger   = 0x1005,// 8x 01 04 10 05 FF One Push WB Trigger
    visca_cam_wb_outdoor_auto       = 0x3506,// 8x 01 04 35 06 FF Outdoor auto
    visca_cam_wb_sodium_lamp_auto   = 0x3507,// 8x 01 04 35 07 FF Auto including sodium lamp source
    visca_cam_wb_sodium_lamp        = 0x3508,// 8x 01 04 35 08 FF Sodium lamp source fixed mode
    visca_cam_wb_sodium_lamp_outdoor_auto = 0x3509,// 8x 01 04 35 09 FF Outdoor auto including sodium lamp source
    visca_cam_rgain_reset           = 0x0300,// 8x 01 04 03 00 FF Reset Manual Control of R Gain
    visca_cam_rgain_up              = 0x0302,// 8x 01 04 03 02 FF Up
    visca_cam_rgain_down            = 0x0303,// 8x 01 04 03 03 FF Down
    visca_cam_rgain_direct          = 0x4300,// 8x 01 04 43 00 00 0p 0q FF, pq: R Gain
    visca_cam_bgain_reset           = 0x0400,// 8x 01 04 04 00 FF Reset  Manual Control of B Gain
    visca_cam_bgain_up              = 0x0402,// 8x 01 04 04 02 FF Up
    visca_cam_bgain_down            = 0x0403,// 8x 01 04 04 03 FF Down
    visca_cam_bgain_direct          = 0x4400,// 8x 01 04 44 00 00 0p 0q FF, pq: B Gain
    visca_cam_ae_full_auto          = 0x3900,// 8x 01 04 39 00 FF Full Auto Automatic Exposure mode
    visca_cam_ae_manual             = 0x3903,// 8x 01 04 39 03 FF Manual Control mode
    visca_cam_ae_shutter_priority   = 0x390A,// 8x 01 04 39 0A FF Shutter Priority Automatic Exposure mode
    visca_cam_ae_iris_priority      = 0x390B,// 8x 01 04 39 0B FF Iris Priority Automatic Exposure mode
    visca_cam_ae_bright             = 0x390D,// 8x 01 04 39 0D FF Bright Mode (Manual control)
    visca_cam_autoslowshutter_on    = 0x5A02,// 8x 01 04 5A 02 FF On Auto Slow Shutter ON/OFF
    visca_cam_autoslowshutter_off   = 0x5A03,// 8x 01 04 5A 03 FF Off
    visca_cam_cam_shutter_reset     = 0x0A00,// 8x 01 04 0A 00 FF Reset Shutter Setting
    visca_cam_shutter_up            = 0x0A02,// 8x 01 04 0A 02 FF Up
    visca_cam_shutter_down          = 0x0A03,// 8x 01 04 0A 03 FF Down
    visca_cam_shutter_direct        = 0x4A00,// 8x 01 04 4A 00 00 0p 0q FF Direct pq: Shutter Position
    visca_cam_iris_reset            = 0x0B00,// 8x 01 04 0B 00 FF Reset Iris Setting
    visca_cam_iris_up               = 0x0B02,// 8x 01 04 0B 02 FF Up
    visca_cam_iris_down             = 0x0B03,// 8x 01 04 0B 03 FF Down
    visca_cam_iris_direct           = 0x4B00,// 8x 01 04 4B 00 00 0p 0q FF Direct  pq: Iris Position
    visca_cam_gain_reset            = 0x0C00,// 8x 01 04 0C 00 FF Reset Gain Setting
    visca_cam_gain_up               = 0x0C02,// 8x 01 04 0C 02 FF Up
    visca_cam_gain_down             = 0x0C03,// 8x 01 04 0C 03 FF Down
    visca_cam_gain_direct           = 0x4C00,// 8x 01 04 4C 00 00 0p 0q FF Direct,pq: Gain Position
    visca_cam_gain_gain_limit       = 0x2C00,// 8x 01 04 2C 0p FF Gain Limit p: Gain Position
    visca_cam_bright_reset          = 0x0D00,// 8x 01 04 0D 00 FF Reset Bright Setting
    visca_cam_bright_up             = 0x0D02,// 8x 01 04 0D 02 FF Up
    visca_cam_bright_down           = 0x0D03,// 8x 01 04 0D 03 FF Down
    visca_cam_bright_direct         = 0x4D00,// 8x 01 04 4D 00 00 0p 0q FF Direct,pq: Bright Position
    //page 3/6  (sony ev-7500 manual)==================================================================================
    visca_cam_expcomp_on            = 0x3E02,// 8x 01 04 3E 02 FF On Exposure Compensation ON/OFF
    visca_cam_expcomp_off           = 0x3E03,// 8x 01 04 3E 03 FF Off
    visca_cam_expcomp_reset         = 0x0E00,// 8x 01 04 0E 00 FF Reset Exposure Compensation Amount Setting
    visca_cam_expcomp_up            = 0x0E02,// 8x 01 04 0E 02 FF Up
    visca_cam_expcomp_down          = 0x0E03,// 8x 01 04 0E 03 FF Down
    visca_cam_expcomp_direct        = 0x4E00,// 8x 01 04 4E 00 00 0p 0q FF Direct pq: ExpComp Position
    visca_cam_cam_backlight_on      = 0x3302,// 8x 01 04 33 02 FF On Back Light Compensation ON/OFF
    visca_cam_backlight_off         = 0x3303,// 8x 01 04 33 03 FF Off
    visca_cam_spotae_on             = 0x5902,// 8x 01 04 33 02 FF On Back Light Compensation ON/OFF
    visca_cam_spotae_off            = 0x5903,// 8x 01 04 33 03 FF Off
    visca_cam_spotae_position       = 0x2900,// 8x 01 04 29 0p 0q 0r 0s FF Position,pq: X (0 to F), rs: Y (0 to F)
    visca_cam_ae_response_direct    = 0x5D00,// 8x 01 04 5D pp FF Direct,pp: Automatic Exposure Response Setting (01h to 30h),default value: 01
    visca_cam_wd_on                 = 0x3d02,// 8x 01 04 3D 02 FF Wide-D ON
    visca_cam_wd_off                = 0x3d03,// 8x 01 04 3D 03 FF Wide-D OFF
    visca_cam_wd_ve_on              = 0x3d06,// 8x 01 04 3D 06 FF VE On
    visca_cam_wd_set_parameter      = 0x2D00,//Set Parameter 8x 01 04 2D 00 0q 0r 0s 00 00 00 00 FF
    /*q: Display brightness level (0: Dark to 6: Bright)
                                            r: Brightness compensation selection (0: Very dark, 1: Dark,
                                            2: Standard, 3: Bright)
                                            s: Compensation level (0: Low, 1: Mid, 2: High)*/
    visca_cam_aperture_reset        = 0x0200,// 8x 01 04 02 00 FF Reset Aperture Control
    visca_cam_aperture_up           = 0x0202,// 8x 01 04 02 02 FF Up
    visca_cam_aperture_down         = 0x0203,// 8x 01 04 02 03 FF Down
    visca_cam_aperture_direct       = 0x4200,// 8x 01 04 42 00 00 0p 0q FF Direct,pq: Aperture Gain
    visca_cam_hr_on                 = 0x5202,// 8x 01 04 52 02 FF On High-Resolusion Mode ON/OFF
    visca_cam_hr_off                = 0x5203,// 8x 01 04 52 03 FF Off
    visca_cam_nr                    = 0x5300,// 8x 01 04 53 0p FF,p: NR Setting (0: OFF, level 1 to 5)
    visca_cam_gamma                 = 0x5000,// 8x 01 04 5B 0p FF p: Gamma setting (0: Standard, 1: Straight), p: Gamma setting (0: Standard, 1: Straight)
    visca_cam_highsensitivity_on    = 0x5E02,// 8x 01 04 5E 02 FF On    High Sensitivity mode ON/OFF
    visca_cam_highsensitivity_off   = 0x5E03,// 8x 01 04 5E 03 FF Off
    visca_cam_lr_reverse_on         = 0x6102,// 8x 01 04 61 02 FF On Mirror Image ON/OFF
    visca_cam_lr_reverse_off        = 0x6103,// 8x 01 04 61 03 FF Off
    visca_cam_freeze_on             = 0x6202,// 8x 01 04 62 02 FF On Still Image ON/OFF
    visca_cam_freeze_off            = 0x6203,// 8x 01 04 62 03 FF Off
    visca_cam_pictureeffect_off     = 0x6300,// 8x 01 04 63 00 FF Off Picture Effect Setting
    visca_cam_pictureeffect_negart  = 0x6302,// 8x 01 04 63 02 FF Neg.Art
    visca_cam_pictureeffect_bw      = 0x6304,// 8x 01 04 63 04 FF Black & White
    visca_cam_defog_on              = 0x3702,// 8x 01 04 37 02 00 FF On Defog ON/OFF
    visca_cam_defog_off             = 0x3703,// 8x 01 04 37 03 00 FF Off
    visca_cam_pictureflip_on        = 0x6602,// 8x 01 04 66 02 FF On    Picture flip ON/OFF
    visca_cam_pictureflip_off       = 0x6603,// 8x 01 04 66 03 FF Off
    //page 4/6  (sony ev-7500 manual)==================================================================================
    visca_cam_icr_on                = 0x0102,// 8x 01 04 01 02 FF On Infrared Mode ON/OFF
    visca_cam_icr_off               = 0x0103,// 8x 01 04 01 03 FF Off
    visca_cam_autoicr_on            = 0x5102,// 8x 01 04 51 02 FF On Auto dark-field mode On/Off
    visca_cam_autoicr_off           = 0x5103,// 8x 01 04 51 03 FF Off
    visca_cam_autoicr_threshold     = 0x2100,// 8x 01 04 21 00 00 0p 0q FF Threshold,pq: ICR ON -> OFF Threshold Level
    visca_cam_autoicralarmreply_on  = 0x3102,// 8x 01 04 31 02 FF On Auto ICR switching Alarm ON/OFF
    visca_cam_autoicralarmreply_off = 0x3103,// 8x 01 04 31 03 FF Off
    visca_cam_auto_icr_alarm_reply  = 0x0007,// y0 07 04 31 03 FF ICR ON -> OFF y0 07 04 31 02 FF,//ICR OFF -> ON
    visca_cam_stabilizer_on         = 0x3402,// 8x 01 04 34 02 FF On Stabilizer ON/OFF/HOLD
    visca_cam_stabilizer_off        = 0x3403,// 8x 01 04 34 03 FF Off
    visca_cam_stabilizer_hold       = 0x3400,// 8x 01 04 34 00 FF Hold
    visca_cam_memory_reset          = 0x3F00,// 8x 01 04 3F 00 0p FF Reset,p: Memory Number (=0h to Fh)
    visca_cam_memory_set            = 0x3F01,// 8x 01 04 3F 01 0p FF Set
    visca_cam_memory_recall         = 0x3F02,// 8x 01 04 3F 02 0p FF Recall
    visca_cam_custom_reset          = 0x3F00,// 8x 01 04 3F 00 7F FF Reset Starts up in this mode when the power is turned on.
    visca_cam_custom_set            = 0x3F01,// 8x 01 04 3F 01 7F FF Set
    visca_cam_custom_recall         = 0x3F02,// 8x 01 04 3F 02 7F FF Recall
    visca_cam_memsave_write         = 0x2300,// 8x 01 04 23 0X 0p 0q 0r 0s FF Write,X: 00 to 07 (Address), total 16 byte pqrs: 0000h to FFFFh (Data)
    visca_cam_display_on            = 0x1502,// 8x 01 04 15 02 FF On Display ON/OFF (8x 01 06 06 02 FF)
    visca_cam_display_off           = 0x1503,// 8x 01 04 15 03 FF Off   (8x 01 06 06 03 FF)
    visca_cam_display_on_off        = 0x1510,// 8x 01 04 15 10 FF On/Off(8x 01 06 06 10 FF)
    visca_cam_multi_line_title_set1 = 0x7310,// 8x 01 04 73 1L 00 nn pp qq 00 00 00 00 00 00 FF,
    //l: line number, nn: h-position, pp: color, qq: blink
    visca_cam_multi_line_title_set2 = 0x7320,// 8x 01 04 73 2L mm nn pp qq rr ss tt uu vv ww FF,
    //l: line number,mnpqrstuvw: setting of characters (1 to 10)
    visca_cam_multi_line_title_set3 = 0x7330,// 8x 01 04 73 3L mm nn pp qq rr ss tt uu vv ww FF,
    //line number,mnpqrstuvw: setting of characters (11 to 20)
    visca_cam_multi_line_title_clear= 0x7410,// 8x 01 04 74 1p FF, p:Title Setting clear (p: 0h to Ah, F= all lines)
    visca_cam_multi_line_title_on   = 0x7420,// 8x 01 04 74 2p FF On,p:Title display On/Off (0h to Ah, F= all lines)
    visca_cam_multi_line_title_off  = 0x7430,// 8x 01 04 74 3p FF Off
    visca_cam_mute_on               = 0x7502,// 8x 01 04 75 02 FF On Muting ON/OFF
    visca_cam_mute_off              = 0x7503,// 8x 01 04 75 03 FF Off
    visca_cam_mute_on_off           = 0x7510,// 8x 01 04 75 10 FF On/Off
    //visca_cam_privacyzone_setmask   = 0x7600,// 8x 01 04 76 mm nn 0r 0r 0s 0s FF,mm: Mask Settings,nn 00: Modify, 01: New,rr: W, ss: H
    //visca_cam_privacyzone_display   = 0x7700,// 8x 01 04 77 pp pp pp pp FF Mask Display ON/OFF, pp pp pp pp: Mask Settings (0: OFF, 1: ON)
    //visca_cam_privacyzone_setmaskcolor     = 0x7800,// 8x 01 04 78 pp pp pp pp qq rr FF,pp pp pp pp: Mask Color Settings,qq: Color Setting when 0 is selected,rr: Color Setting when 1 is selected
    //visca_cam_privacyzone_setpantiltangle  = 0x7900,// 8x 01 04 79 0p 0p 0p 0q 0q 0q FF,Pan/Tilt Angle Settings ppp: Pan qqq: Tilt
    //visca_cam_privacyzone_setptzmask       = 0x7B00,// 8x 01 04 7B mm 0p 0p 0p 0q 0q 0q 0r 0r 0r 0r FF Pan/Tilt/Zoom Settings for Mask ppp: Pan, qqq: Tilt, rrrr: Zoom, mm: Mask Settings
    //visca_cam_privacyzone_non_interlockmask= 0x6F00,// 8x 01 04 6F mm 0p 0p 0q 0q 0r 0r 0s 0s FF mm: Non_Interlock Mask Settings pp: X, q: Y, rr: W, ss: H
    visca_cam_privacyzone_centerlineoff    = 0x7C03,// 8x 01 04 7C 03 FF Center Line Display Off
    visca_cam_privacyzone_centerlineon     = 0x7C04,// 8x 01 04 7C 04 FF Center Line Display On
    //page 5/6  (sony ev-7500 manual)==================================================================================
    visca_cam_id_write               = 0x2200,// 8x 01 04 22 0p 0q 0r 0s FF,pqrs: Camera ID (=0000h to FFFFh)
    visca_cam_md_on                  = 0x1B02,//On    8x 01 04 1B 02 FF Motion Detection (MD) On/Off
    visca_cam_md_off                 = 0x1B03,//Off   8x 01 04 1B 03 FF
    //visca_cam_md_function_set        = 0x1C00,//Function Set 8x 01 04 1C 0m 0n 0p 0q 0r 0s FF,m: Display mode,n: Detection Frame Set (00h to 0Fh),pq: Threshold Level (00h to FFh),rs: Interval Time set (00h to FFh)
    //visca_cam_md_window_set          = 0x1D00,//Window Set   8x 01 04 1D 0m 0p 0q 0r 0s FF,m: Select Detection Frame (0,1,2,3),p: Start Horizontal Position (00h to 0Fh),q: Start Vertical Position (00h to 07h),
    /*r: Stop Horizontal Position (01h to 10h)
s: Stop Vertical Position (01h to 08h)*/
    //visca_cam_md_alarm            = 0x0007,//y0 07 04 1B 0p FF p: Detection Frame Number
    visca_cam_continuous_zoom_pos_reply_on = 0x6902,//On  8x 01 04 69 02 FF ZoomPosition data Continuous Output On/Off
    visca_cam_continuous_zoom_pos_reply_off= 0x6903,//Off 8x 01 04 69 03 FF
    //visca_cam_continuous_zoom_pos_reply  = 0x0007,//y0 07 04 69 0p 0p 0q 0q 0q 0q FF,pp: D-Zoom Position,* 00: When Zoom Mode is Combine,qqqq: Zoom Position
    //visca_cam_zoom_pos_reply_interval_time_set      = 0x6A00,//0x6A 00 00 0p 0p FF pp: Interval Time [V cycle]
    visca_cam_continuous_focus_pos_reply_on         = 0x1602,//On 8x 01 04 16 02 FF Focus Position data Continuous Output ON/OFF
    visca_cam_continuous_focus_pos_reply_off        = 0x1603,//Off 8x 01 04 16 03 FF
    //visca_cam_continuous_focus_pos_reply            = 0x0007,// y0 07 04 16 00 00 0p 0p 0p 0p FF pppp: Focus Position
    //visca_cam_cam_focus_pos_reply_interval_time_set = 0x6A00,//8x 01 04 6A 00 00 0p 0p FF pp: Interval Time [V cycle]
    visca_cam_registervalue                         = 0x2400,// 8x 01 04 24 mm 0p 0p FF mm: Register No. (=00h to 7Fh) pp: Register Value (=00h to FFh)
    //visca_cam_color_enhance_parameter_set           = 0x2000,// 8x 01 04 20 mm 00 pp qq rr ss tt uu FF
    /*
mm: Threshold level
pp: Y fixed color for high-intensity
qq: Cr fixed color for high-intensity
rr: Cb fixed color for high-intensity
ss: Y fixed color for low-intensity
tt: Cr fixed color for low-intensity
uu: Cb fixed color for low-intensity
Each parameter setting 00h to 7Fh 
*/
    visca_cam_color_enhance_parameter_on  = 0x5002,//On  8x 01 04 50 02 FF Color Enhancement ON/OFF
    visca_cam_color_enhance_parameter_off = 0x5003,//Off 8x 01 04 50 03 FF
    visca_cam_chroma_suppress             = 0x5F00,//8x 01 04 5F pp FF,pp: chroma suppress setting level 00: OFF 01h to 03h: ON (3 levels).effect increases as the level number increases.*/
    visca_cam_color_gain_direct           = 0x4900,//8x 01 04 49 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
    visca_cam_color_hue_direct            = 0x4F00,//8x 01 04 4F 00 00 00 0p FF p: Color Hue setting 0h (-14 degrees) to Eh (+14 degrees)
    //visca_cam_gamma_offset_direct         = 0x1E00,//8x 01 04 1E 00 00 00 0s 0t 0u FF s: Polarity offset (0 is plus, 1 is minus) tu: Offset (0 to 40h)
    //page 6/6  (sony ev-7500 manual)==================================================================================
    visca_cam_ex_exp_comp_reset           = 0x0E00,//8x 01 04 1F 0E 00 00 FF Exposure compensation reset
    visca_cam_ex_exp_comp_up              = 0x0E02,//8x 01 04 1F 0E 02 pp FF Exposure compensation up
    //pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    visca_cam_ex_exp_comp_down            = 0x0e03,//8x 01 04 1F 0E 03 pp FF Exposure compensation down
    //pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    visca_cam_ex_exp_comp_direct          = 0x1f4e,//8x 01 04 1F 4E 00 00 0p 0q FF Set the exposure compensation to
    // the specified level pq: Level pq=00h to FFh
    visca_cam_ex_aperture_reset           = 0x0200,//8x 01 04 1F 02 00 00 FF Aperture control reset
    visca_cam_ex_aperture_up              = 0x0202,//8x 01 04 1F 02 02 pp FF Aperture control up
    //pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    visca_cam_ex_aperture_down            = 0x0203,//8x 01 04 1F 02 03 pp FF Aperture control down pp: Step number pp=00h to 7Fh
    //(However, 00h is the same operation as 01h.)
    visca_cam_ex_aperture_direct          = 0x1F42,//8x 01 04 1F 42 00 00 0p 0q FF Set the aperture control
    //to the specified level pq: Level pq=00h to FFh
    visca_cam_ex_auto_icr          = 0x1f21,//8x 01 04 1F 21 00 00 0p 0q FF pq: ICR ON->OFF threshold when Auto ICR is on pq=00h to FFh
    //8x 01 04 1F 21 01 00 0r 0s FF pq: On level ICR OFF->ON when Auto ICR is on pq=00h to 1Ch
} VISCA_commands_t;


typedef enum Inquiry_Command_List:uint8_t
{
    //Inquiry Command List (1/3)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    CAM_PowerInq              = 0x00,//8x 09 04 00 FF , y0 50 02 FF On , y0 50 03 FF Off (Standby)
    CAM_ZoomPosInq            = 0x47,//8x 09 04 47 FF , y0 50 0p 0q 0r 0s FF pqrs: Zoom Position
    CAM_DZoomModeInq          = 0x06,//8x 09 04 06 FF , y0 50 02 FF D-Zoom On , y0 50 03 FF D-Zoom Off
    CAM_DZoomC_SModeInq       = 0X36,//8x 09 04 36 FF , y0 50 00 FF Combine Mode , y0 50 01 FF Separate Mode
    CAM_DZoomPosInq           = 0x46,//8x 09 04 46 FF , y0 50 00 00 0p 0q FF pq: D-Zoom Position
    CAM_FocusModeInq          = 0x38,//8x 09 04 38 FF , y0 50 02 FF Auto Focus , y0 50 03 FF Manual Focus
    CAM_FocusPosInq           = 0x48,//8x 09 04 48 FF , y0 50 0p 0q 0r 0s FF pqrs: Focus Position
    CAM_FocusNearLimitInq     = 0x28,//8x 09 04 28 FF , y0 50 0p 0q 0r 0s FF pqrs: Focus Near Limit Position
    CAM_AFSensitivityInq      = 0x58,//8x 09 04 58 FF , y0 50 02 FF AF Sensitivity Normal , y0 50 03 FF AF Sensitivity Low
    CAM_AFModeInq             = 0x57,//8x 09 04 57 FF , y0 50 00 FF Normal AF , y0 50 01 FF Interval AF , y0 50 02 FF Zoom Trigger AF
    CAM_AFTimeSettingInq      = 0x27,//8x 09 04 27 FF , y0 50 0p 0q 0r 0s FF pq: Movement Time, rs: Interval
    CAM_IRCorrectionInq       = 0x11,//8x 09 04 11 FF , y0 50 00 FF Standard, y0 50 01 FF IR Light
    CAM_WBModeInq             = 0x35,//8x 09 04 35 FF
    /*
, y0 50 00 FF Auto
, y0 50 01 FF Indoor
, y0 50 02 FF Outdoor
, y0 50 03 FF One Push WB
, y0 50 04 FF ATW
, y0 50 05 FF Manual
, y0 50 06 FF Outdoor Auto
, y0 50 07 FF Sodium Lamp Auto
, y0 50 08 FF Sodium Lamp
, y0 50 09 FF Sodium Lamp Outdoor Auto*/
    CAM_RGainInq              = 0x43,//8x 09 04 43 FF , y0 50 00 00 0p 0q FF pq: R Gain
    CAM_BGainInq              = 0x44,//8x 09 04 44 FF , y0 50 00 00 0p 0q FF pq: B Gain
    CAM_AEModeInq             = 0x39,//8x 09 04 39 FF , y0 50 00 FF Full Auto
    /*y0 50 03 FF Manual
, y0 50 0A FF Shutter Priority
, y0 50 0B FF Iris Priority
, y0 50 0D FF Bright*/
    CAM_AutoSlowShutterInq    = 0x5A,//8x 09 04 5A FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_ShutterPosInq         = 0x4A,//8x 09 04 4A FF , y0 50 00 00 0p 0q FF pq: Shutter Position
    CAM_IrisPosInq            = 0x4B,//8x 09 04 4B FF , y0 50 00 00 0p 0q FF pq: Iris Position
    CAM_GainPosInq            = 0x4C,//8x 09 04 4C FF , y0 50 00 00 0p 0q FF pq: Gain Position
    CAM_GainLimitInq          = 0x2C,//8x 09 04 2C FF , y0 50 0q FF p: Gain Limit
    CAM_BrightPosInq          = 0x4D,//8x 09 04 4D FF , y0 50 00 00 0p 0q FF pq: Bright Position
    CAM_ExpCompModeInq        = 0x3E,//8x 09 04 3E FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_ExpCompPosInq         = 0x4E,//8x 09 04 4E FF , y0 50 00 00 0p 0q FF pq: ExpComp Position
    CAM_BackLightModeInq      = 0x33,//8x 09 04 33 FF , y0 50 02 FF On, y0 50 03 FF Off
    //Inquiry Command List (1/3)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    CAM_SpotAEModeInq         = 0x59,//8x 09 04 59 FF , y0 50 02 FF On , y0 50 03 FF Off
    CAM_SpotAEPosInq          = 0x29,//8x 09 04 29 FF , y0 50 0p 0q 0r 0s FF pq: X position, rs: Y position
    CAM_WDModeInq             = 0x3D,//8x 09 04 3D FF , y0 50 02 FF On, y0 50 03 FF Off, y0 50 06 FF VE On
    CAM_WDParameterInq        = 0x2D,//8x 09 04 2D FF , y0 50 00 0q 0r 0s 0t 0u 00 00 FF
    /*q: Display brightness level (0: Dark to 6: Bright)
r: Brightness compensation selection (0: Very dark,
1: Dark, 2: Standard, 3: Bright)
s: Compensation level (00h: Low, 01h: Mid, 02h: High)
tu: Always 0*/
    CAM_AE_ResponseInq        = 0x5D,//8x 09 04 5D FF , y0 50 pp FF pp: 01h to 30h
    CAM_DefogInq              = 0x37,//8x 09 04 37 FF , y0 50 02 00 FF Defog ON , y0 50 03 00 FF Defog OFF
    CAM_ApertureInq           = 0x42,//8x 09 04 42 FF , y0 50 00 00 0p 0q FF pq: Aperture Gain
    CAM_HRModeInq             = 0x52,//8x 09 04 52 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_NRModeInq             = 0x53,//8x 09 04 53 FF , y0 50 0p FF Noise Reduction p: 00h to 05h
    CAM_GammaInq              = 0x5B,//8x 09 04 5B FF , y0 50 0p FF Gamma p: 00h to 04h
    CAM_HighSensitivityInq    = 0x5E,//8x 09 04 5E FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_LR_ReverseModeInq     = 0x61,//8x 09 04 61 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_FreezeModeInq         = 0x62,//8x 09 04 62 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_PictureEffectModeInq  = 0x63,//8x 09 04 63 FF , y0 50 00 FF Off, y0 50 02 FF Neg.Art, y0 50 04 FF Black & White
    CAM_PictureFlipModeInq    = 0x66,//8x 09 04 66 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_ICRModeInq            = 0x01,//8x 09 04 01 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_AutoICRModeInq        = 0x51,//8x 09 04 51 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_AutoICRThresholdInq   = 0x21,//8x 09 04 21 FF , y0 50 00 00 0p 0q FF pq: ICR ON ? OFF Threshold Level
    CAM_AutoICRAlarmReplyInq  = 0x31,//8x 09 04 31 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_MemoryInq             = 0x3F,//8x 09 04 3F FF , y0 50 pp FF pp: Memory number recalled last
    CAM_MemSaveInq            = 0x23,//8x 09 04 23 0X FF , y0 50 0p 0q 0r 0s FF X: 00h to 07h (Address)
    //pqrs: 0000h to FFFFh (Data)
    CAM_DisplayModeInq        = 0x15,//8x 09 04 15 FF(8x 09 06 06 FF) , y0 50 02 FF On, y0 50 03 FF Off
    CAM_StabilizerModeInq     = 0x34,//8x 09 04 34 FF , y0 05 02 FF On, y0 05 03 FF Off, y0 05 00 FF Hold
    //Inquiry Command List (3/3)
    //Inquiry Command         |        Command Packet | Inquiry Packet Comments
    CAM_MuteModeInq           = 0x75,//8x 09 04 75 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_PrivacyDisplayInq     = 0x77,//8x 09 04 77 FF , y0 50 pp pp pp pp FF pp pp pp pp: Mask Display (0: OFF, 1: ON)
    CAM_PrivacyPanTiltInq     = 0x79,//8x 09 04 79 FF , y0 50 0p 0p 0p 0q 0q 0q FF ppp: Pan, qqq: Tilt
    CAM_PrivacyPTZInq         = 0x7B,//8x 09 04 7B mm FF , y0 50 0p 0p 0p 0q 0q 0q 0r 0r 0r 0r FF
    /*mm: Mask Settings
ppp: Pan                      
qqq: Tilt                     
rrrr: Zoom*/                  
    CAM_PrivacyMonitorInq     = 0x6F,//8x 09 04 6F FF , y0 50 pp pp pp pp FF pp pp pp pp: Mask is displayed now.
    CAM_IDInq                 = 0x22,//8x 09 04 22 FF , y0 50 0p 0q 0r 0s FF pqrs: Camera ID
    CAM_VersionInq            = 0x02,//8x 09 00 02 FF , y0 50 00 20 mn pq rs tu vw FF
    /*mnpq: Model Code (04xx)
rstu: ROM version             
vw: Socket Number (= 0x02)*/  
    CAM_MDModeInq             = 0x1B,//8x 09 04 1B FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_MDFunctionInq         = 0x1C,//8x 09 04 1C FF , y0 50 0m 0n 0p 0q 0r 0s FF m: Display mode
    /*n: Detection Frame Set (00h to 0Fh)
pq: Threshold Level (00h to FFh)
rs: Interval Time set (00h to FFh)*/
    CAM_MDWindowInq           = 0x1D,//8x 09 04 1D 0m FF , y0 50 0p 0q 0r 0s FF m: Select Detection Frame (0, 1, 2, 3)
    /*p: Start Horizontal Position (00h to 0Fh)
q: Start Vertical Position (00h to 07h)
r: Stop Horizontal Position (01h to 10h)
s: Stop Vertical Position (01h to 08h)*/
    CAM_ContinuousZoomPosReplyModeInq = 0x69,//8x 09 04 69 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_ZoomPosReplyIntervalTimeInq   = 0x6A,//8x 09 04 6A FF , y0 50 00 00 0p 0p FF pp: Interval Time
    CAM_ContinuousFocusPosReplyModeInq= 0x16,//8x 09 04 16 FF , y0 50 02 FF On, y0 50 03 FF Off
    CAM_FocusReplyIntervalTimeInq     = 0x1A,//8x 09 04 1A FF , y0 50 00 00 0p 0p FF pp: Interval Time
    CAM_RegisterValueInq      = 0x24,//8x 09 04 24 mm FF , y0 50 0p 0p FF mm: Register No. (= 0x00h to 7Fh)
    //pp: Register Value (= 0x00h to FFh)
    CAM_ColorEnhanceInq       = 0x20,//8x 09 04 20 FF , y0 50 mm 00 pp qq rr ss tt uu FF mm: Threshold level
    /*pp: Y fixed color for high-intensity
qq: Cr fixed color for high-intensity
rr: Cb fixed color for high-intensity
ss: Y fixed color for low-intensity
tt: Cr fixed color for low-intensity
uu: Cb fixed color for low-intensity
8x 09 04 50 FF , y0 50 02 FF On, y0 50 03 FF Off*/
    CAM_ChromaSuppressInq     = 0x5F,//8x 09 04 5F FF , y0 50 pp FF pp: Chroma Suppress setting level
    CAM_ColorGainInq          = 0x49,//8x 09 04 49 FF , y0 50 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
    CAM_ColorHueInq           = 0x4F,//8x 09 04 4F FF , y0 50 00 00 00 0p FF p: Color Hue setting 0h (- 14 degrees) to Eh (+ 14 degrees)
    CAM_TempInq               = 0x68,//8x 09 04 68 FF , y0 50 00 00 0p 0q FF pq: Lens Temperature
    CAM_inq_none = 0xff,
}inquiry_command_list_t;
typedef enum ext_inquiry_command_list
{
    CAM_ExExpCompPosInq       = 0x1F4EFF00,//8x 09 04 1F 4E FF , y0 50 00 00 0p 0q FF pq: Exposure compensation level
    CAM_ExApertureInq         = 0x1F42FF00,//8x 09 04 1F 42 FF , y0 50 00 00 0p 0q FF pq: Exposure compensation level
    CAM_ExColorGainInq        = 0x1F4900FF,//8x 09 04 1F 49 0p FF , y0 50 0q 0r FF, p: Color, qr: Gain
    CAM_ExColorHueInq         = 0x1F4F00FF,//8x 09 04 1F 4F 0p FF , y0 50 0q 0r FF p: Color, qr: Hue
    CAM_ExAutoICRThresholdInq = 0x1F2100FF,//8x 09 04 1F 21 00 FF , y0 50 00 00 0p 0q FF ICR ON?OFF threshold when Auto ICR is on
    CAM_ExAutoICROnLevelInq   = 0x1F2101FF,//8x 09 04 1F 21 01 FF , y0 50 00 00 0p 0q FF ICR OFF?ON when Auto ICR is on
}ext_inquiry_command_list_t;

typedef enum _VISCA_CAM 
{
    CAM1=1,
    CAM2=2,
    CAM3=3,
    CAM4=4,
    CAM5=5,
    CAM6=6,
    CAM7=7,
    BROADCAST = 8,
} VISCA_Cam_t;

typedef enum _VISCA_Category
{
    VISCA_CATEGORY_INTERFACE   =      0x00,
    VISCA_CATEGORY_CAMERA1     =      0x04,
    VISCA_CATEGORY_PAN_TILTER  =      0x06,
    VISCA_CATEGORY_CAMERA2     =      0x07,
}VISCA_Category_t;
/* TITLE STRUCTURE */
typedef struct _VISCA_title
{
    uint8_t line;
    uint8_t hposition;
    uint8_t color;
    uint8_t blink;
    uint8_t chars[10];

} VISCATitleData_t;

typedef struct _VISCA_packet
{
    uint8_t length;
    uint8_t bytes[32];

} VISCAPacket_t;

/* CAMERA STRUCTURE */
typedef struct _VISCA_camera
{
    // VISCA data:
    VISCA_Cam_t camnum;
    VISCA_Category_t category;
    VISCA_commands_t command;
    int16_t value;
    int16_t value2;
    VISCATitleData_t title;
    inquiry_command_list_t inquiry;

    // camera info:
    uint32_t vendor;
    uint32_t model;
    uint32_t rom_version;
    uint32_t socket_num;

    uint16_t ZoomPosition;
    uint16_t DZoomPosition;
    float FocusInMetters;
    bool  FocusAuto;

    uint8_t WhiteBallance;
    uint8_t Brightness;
    uint8_t RGain;
    uint8_t BGain;
    uint8_t ColorGain;
    uint8_t ColorHue;

    uint8_t AutoExpoMode;
    uint16_t Shutter;    //Presented as divider only 1/50 = 50
    float Iris;
    uint8_t Gain;

    bool CenterlineIsOn;

    bool HiRes;
    bool HiSense;
    bool Defog;
    bool IrFilter;
    bool Stabilisation;


} VISCACamera_t;

typedef struct visca_parser_state
{
    uint8_t step;
    uint8_t datalen;
    int data;
}visca_parser_state_t;

extern VISCACamera_t camEO;
extern VISCAPacket_t visca_paket;
extern visca_parser_state_t  viscaParser;

/* GENERAL FUNCTIONS */
uint8_t ViscaCamCommandPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera);
void ViscaInquiryCommandPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera);
void ViscaExtInquiryCommandPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera,ext_inquiry_command_list_t inq);
void ViscaLensControlSystemInquiryPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera);
void visca_init_parser (visca_parser_state_t * vp);
uint8_t ViscaParseBuf (uint8_t* buf, uint8_t chars ,visca_parser_state_t * vp,VISCACamera_t * camera);

#ifdef __cplusplus
}
#endif
#endif


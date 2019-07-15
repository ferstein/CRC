#include "VISCA.h"
VISCACamera_t camEO;
VISCAPacket_t visca_paket;
visca_parser_state_t  viscaParser;

uint8_t ViscaCamCommandPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera)
{
    if(camera->camnum > BROADCAST || camera->camnum < CAM1)
        return(VISCA_ERROR_CMD_NOT_EXECUTABLE);
    
    VISCA_packet->length = 0x06;
    VISCA_packet->bytes[0] = VISCA_HEADER+camera->camnum;
    VISCA_packet->bytes[1] = VISCA_COMMAND;
    VISCA_packet->bytes[2] = camera->category;
    VISCA_packet->bytes[5] = VISCA_TERMINATOR;
    switch(camera->command)
    {
    case visca_addressset: // 88 30 01 FF Address setting
        VISCA_packet->length = 0x04;
        VISCA_packet->bytes[0] = VISCA_BROADCAST;
        VISCA_packet->bytes[1] = 0x30;
        VISCA_packet->bytes[2] = camera->camnum;
        VISCA_packet->bytes[3] = VISCA_TERMINATOR;
        break;
    case visca_if_clear  : // 8x 01 00 01 FF , 88 01 00 01 FF I/F Clear
        VISCA_packet->length = 0x05;
        //P = (uint16_t *)(&VISCA_packet->bytes[2]);
        //*P = camera->command;
        VISCA_packet->bytes[0] = VISCA_BROADCAST;
        VISCA_packet->bytes[1] = 0x01;
        VISCA_packet->bytes[2] = camera->command>>8;
        VISCA_packet->bytes[3] = (uint8_t)camera->command;
        VISCA_packet->bytes[4] = VISCA_TERMINATOR;
        break;
    case command_cancel  : // 8x 2p FF p: Socket No. (=1 or 2)
        VISCA_packet->length = 0x03;
        VISCA_packet->bytes[1] = (camera->command>>8) + camera->category;
        VISCA_packet->bytes[2] = (uint8_t)(camera->command>>8);
        break;
        /*
    case visca_power_on  :
    case visca_power_off :
    case visca_zoom_stop :
    case visca_zoom_tele :
    case visca_zoom_wide :
    case visca_dzoom_on  :
    case visca_dzoom_off :
    case visca_dzoom_combine_mode :
    case visca_dzoom_separate_mode:
    case visca_dzoom_stop :
    case visca_dzoom_x1_max:
    case visca_focus_stop :
    case visca_focus_far_standard :
    case visca_focus_near_standard:
    case visca_focus_auto:
    case visca_focus_manual :
    case visca_focus_auto_manual :
    case visca_focus_one_push_trigger:
    case visca_af_sensitivity_normal:
    case visca_af_sensitivity_low:
    case visca_af_mode_normal    :
    case visca_af_mode_interval   :
    case visca_af_mode_zoom_trigger:
    case visca_ircorrection_standard:
    case visca_ircorrection_ir_light:
    case visca_initialize_lens:
    case visca_initialize_camera:
//page 2/6  (sony ev-7500 manual)===============================================
    case visca_cam_wb_auto : //Normal Auto
    case visca_cam_wb_indoor : //Indoor mode
    case visca_cam_wb_outdoor ://Outdoor mode
    case visca_cam_wb_one_push ://One Push WB mode
    case visca_cam_wb_atw : // Auto Tracing White Balance
    case visca_cam_wb_manual :// Manual Control mode
    case visca_cam_wb_one_push_trigger://One Push WB Trigger
    case visca_cam_wb_outdoor_auto ://Outdoor auto
    case visca_cam_wb_sodium_lamp_auto://Auto including sodium lamp source
    case visca_cam_wb_sodium_lamp :// Sodium lamp source fixed mode
    case visca_cam_wb_sodium_lamp_outdoor_auto:// Outdoor auto including sodium lamp source
    case visca_cam_rgain_reset ://  Manual Control of R Gain
    case visca_cam_rgain_up :
    case visca_cam_rgain_down :
    case visca_cam_bgain_reset:
    case visca_cam_bgain_up:
    case visca_cam_bgain_down:
    case visca_cam_ae_full_auto:
    case visca_cam_ae_manual :
    case visca_cam_ae_shutter_priority:
    case visca_cam_ae_iris_priority :
    case visca_cam_ae_bright :
    case visca_cam_autoslowshutter_on:///Auto Slow Shutter ON/OFF
    case visca_cam_autoslowshutter_off:
    case visca_cam_cam_shutter_reset://Shutter Setting
    case visca_cam_shutter_up :
    case visca_cam_shutter_down :
    case visca_cam_iris_reset:
    case visca_cam_iris_up :
    case visca_cam_iris_down:
    case visca_cam_gain_reset:
    case visca_cam_gain_up:
    case visca_cam_gain_down:
    case visca_cam_bright_reset:
    case visca_cam_bright_up:
    case visca_cam_bright_down:
//page 3/6  (sony ev-7500 manual)===============================================      
    case visca_cam_expcomp_on :   // = 0x3E02,//On     8x 01 04 3E 02 FF Exposure Compensation ON/OFF
    case visca_cam_expcomp_off :  // = 0x3E03,//Off    8x 01 04 3E 03 FF
    case visca_cam_expcomp_reset: // = 0x0E00,//Reset  8x 01 04 0E 00 FF Exposure Compensation Amount Setting
    case visca_cam_expcomp_up:    // = 0x0E02,//Up     8x 01 04 0E 02 FF
    case visca_cam_expcomp_down : // = 0x0E03,//Down   8x 01 04 0E 03 FF
    case visca_cam_cam_backlight_on://=0x3302,//On     8x 01 04 33 02 FF Back Light Compensation ON/OFF
    case visca_cam_backlight_off: // = 0x3303,//Off    8x 01 04 33 03 FF
    case visca_cam_spotae_on:     // = 0x5902,// On    8x 01 04 33 02 FF Back Light Compensation ON/OFF
    case visca_cam_spotae_off:    // = 0x5903,//Off    8x 01 04 33 03 FF
    case visca_cam_wd_on:         // = 0x3d02,//On     8x 01 04 3D 02 FF Wide-D ON
    case visca_cam_wd_off:        // = 0x3d03,//Off    8x 01 04 3D 03 FF Wide-D OFF
    case visca_cam_wd_ve_on:      // = 0x3d06,//VE On  8x 01 04 3D 06 FF VE On
    case visca_cam_aperture_reset:// = 0x0200,//Reset  8x 01 04 02 00 FF Aperture Control
    case visca_cam_aperture_up   :// = 0x0202,//Up     8x 01 04 02 02 FF
    case visca_cam_aperture_down :// = 0x0203,//Down   8x 01 04 02 03 FF
    case visca_cam_hr_on         :// = 0x5202,//On     8x 01 04 52 02 FF High-Resolusion Mode ON/OFF
    case visca_cam_hr_off        :// = 0x5203,//Off    8x 01 04 52 03 FF
    case visca_cam_highsensitivity_on: //= 0x5E02,//On 8x 01 04 5E 02 FF High Sensitivity mode ON/OFF
    case visca_cam_highsensitivity_off://= 0x5E03,//Off8x 01 04 5E 03 FF
    case visca_cam_lr_reverse_on :// = 0x6102,//On     8x 01 04 61 02 FF Mirror Image ON/OFF
    case visca_cam_lr_reverse_off:// = 0x6103,//Off    8x 01 04 61 03 FF
    case visca_cam_freeze_on     :// = 0x6202,//On     8x 01 04 62 02 FF Still Image ON/OFF
    case visca_cam_freeze_off    :// = 0x6203,//Off    8x 01 04 62 03 FF
    case visca_cam_pictureeffect_off://0x6300,//Off    8x 01 04 63 00 FF Picture Effect Setting
    case visca_cam_pictureeffect_negart://0x6302NegArt 8x 01 04 63 02 FF
    case visca_cam_pictureeffect_bw://=0x6304,//B & W  8x 01 04 63 04 FF
    case visca_cam_pictureflip_on:// = 0x6602,//On     8x 01 04 66 02 FF Picture flip ON/OFF
    case visca_cam_pictureflip_off://= 0x6603,//Off    8x 01 04 66 03 FF
//page 4/6  (sony ev-7500 manual)===============================================      
    case visca_cam_icr_on :       // = 0x0102,//On     8x 01 04 01 02 FF Infrared Mode ON/OFF
    case visca_cam_icr_off:       // = 0x0103,//Off    8x 01 04 01 03 FF
    case visca_cam_autoicr_on    :// = 0x5102,//On     8x 01 04 51 02 FF Auto dark-field mode On/Off
    case visca_cam_autoicr_off   :// = 0x5103,//Off    8x 01 04 51 03 FF
    case visca_cam_auto_icr_alarm_reply://=0x0007,//   y0 07 04 31 03 FF,   //ICR ON -> OFF y0 07 04 31 02 FF,//ICR OFF -> ON
    case visca_cam_stabilizer_on :// = 0x3402,//On     8x 01 04 34 02 FF Stabilizer ON/OFF/HOLD
    case visca_cam_stabilizer_off:// = 0x3403,//Off    8x 01 04 34 03 FF
    case visca_cam_stabilizer_hold://= 0x3400,//Hold   8x 01 04 34 00 FF
    case visca_cam_display_on    :// = 0x1502,//On     8x 01 04 15 02 FFDisplay ON/OFF (8x 01 06 06 02 FF)
    case visca_cam_display_off   :// = 0x1503,//Off    8x 01 04 15 03 FF (8x 01 06 06 03 FF)
    case visca_cam_display_on_off:// = 0x1510,//On/Off 8x 01 04 15 10 FF (8x 01 06 06 10 FF)
    case visca_cam_mute_on       :// = 0x7502,//On     8x 01 04 75 02 FF Muting ON/OFF
    case visca_cam_mute_off      :// = 0x7503,//Off    8x 01 04 75 03 FF
    case visca_cam_mute_on_off   :// = 0x7510,//On/Off 8x 01 04 75 10 FF
//page 5/6  (sony ev-7500 manual)===============================================
    case visca_cam_md_on         :// = 0x1B02,//On     8x 01 04 1B 02 FF Motion Detection (MD) On/Off
    case visca_cam_md_off        :// = 0x1B03,//Off    8x 01 04 1B 03 FF
    case visca_cam_continuous_zoom_pos_reply_on ://On  8x 01 04 69 02 FF ZoomPosition data Continuous Output On/Off
    case visca_cam_continuous_zoom_pos_reply_off://Off 8x 01 04 69 03 FF
    case visca_cam_continuous_focus_pos_reply_on://On  8x 01 04 16 02 FF Focus Position data Continuous Output ON/OFF
    case visca_cam_continuous_focus_pos_reply_off://Off8x 01 04 16 03 FF
    case visca_cam_color_enhance_parameter_on ://On    8x 01 04 50 02 FF Color Enhancement ON/OFF
    case visca_cam_color_enhance_parameter_off://Off   8x 01 04 50 03 FF
    *P = camera->command;
      break;
    */
    case visca_zoom_tele_speed :    //Tele (Variable) 8x 01 04 07 2p FF p=0 (Low) to 7 (High)
    case visca_zoom_wide_speed :    //Wide (Variable) 8x 01 04 07 3p FF
    case visca_dzoom_tele:          //Tele (Variable) 8x 01 04 06 2p FF p=0 (Low) to 7 (High)
    case visca_dzoom_whide:         //Wide (Variable) 8x 01 04 06 3p FF during Separate Mode
    case visca_focus_far_variable : //Far  (Variable) 8x 01 04 08 2p FF p=0 (Low) to 7 (High)
    case visca_focus_near_variable: //Near (Variable) 8x 01 04 08 3p FF
    case visca_cam_gain_gain_limit: //Gain Limit      8x 01 04 2C 0p FF p: Gain Position
    case visca_cam_nr             : //NR Setting      8x 01 04 53 0p FF p: (0: OFF, level 1 to 5)
    case visca_cam_gamma          : //Gamma           8x 01 04 5B 0p FF p: Gamma setting (0: Standard, 1: Straight)
    case visca_cam_multi_line_title_clear :        // 8x 01 04 74 1p FF Title Setting clear,p: (p: 0h to Ah, F= all lines)
    case visca_cam_multi_line_title_on:            // 8x 01 04 74 2p FF On ,p:Title display On/Off (0h to Ah, F= all lines)
    case visca_cam_multi_line_title_off:           // 8x 01 04 74 3p FF Off
        if(camera->value > 0x0f ) return (VISCA_ERROR_CMD_NOT_EXECUTABLE);
        VISCA_packet->bytes[3] = camera->command>>8;
        VISCA_packet->bytes[4] = (uint8_t)(camera->command + (camera->value & 0x000f));
        break;
    case visca_cam_ae_response_direct://8x 01 04 5D pp FF,pp:Automatic Exposure
        //Response Setting (01h to 30h),default value: 01
    case visca_cam_chroma_suppress:   //8x 01 04 5F pp FF,pp:chroma suppress
        //setting level 00: OFF 01h to 03h: ON (3 levels).effect increases as the level number increases.
        VISCA_packet->bytes[3] = camera->command>>8;
        VISCA_packet->bytes[4] = (uint8_t) (camera->command + (camera->value & 0x00FF));
        break;
        // Commands 7 bytes without arguments
    case visca_cam_defog_on:       //8x 01 04 37 02 00 FF On Defog ON/OFF
    case visca_cam_defog_off:      //8x 01 04 37 03 00 FF Off
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[3] = camera->command >> 8;
        VISCA_packet->bytes[4] = (uint8_t) (camera->command );
        VISCA_packet->bytes[5] = 0x00;
        VISCA_packet->bytes[6] = 0xFF;
        break;
    case visca_cam_custom_reset:   //8x 01 04 3F 00 7F FF Reset Starts up in this mode when the power is turned on.
    case visca_cam_custom_set:     //8x 01 04 3F 01 7F FF Set
    case visca_cam_custom_recall:  //8x 01 04 3F 02 7F FF Recall
        // Commands 7 bytes with arguments
        //case visca_cam_memory_reset:   //8x 01 04 3F 00 0p FF Reset,p: Memory Number (=0h to Fh)
        //case visca_cam_memory_set:     //8x 01 04 3F 01 0p FF Set
        //case visca_cam_memory_recall:  //8x 01 04 3F 02 0p FF Recall
        VISCA_packet->length = 0x07;
        VISCA_packet->bytes[3] = camera->command >> 8;
        VISCA_packet->bytes[4] = (uint8_t) (camera->command );
        VISCA_packet->bytes[6] = 0xFF;
        if(camera->value > 0x0F)  VISCA_packet->bytes[5] = 0x7F;
        else VISCA_packet->bytes[5] = (uint8_t)(camera->value);
        break;
        //Commands 8 byte with 2arguments
    case visca_cam_registervalue:  //8x 01 04 24 mm 0p 0p FF mm: Register No. (=00h to 7Fh)
        //pp: Register Value (=00h to FFh)
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = camera->command>>8;
        VISCA_packet->bytes[4] = (uint8_t)(camera->value & 0x00ff);
        VISCA_packet->bytes[5] = (uint8_t)((camera->value2 & 0x00f0)<<4);
        VISCA_packet->bytes[6] = (uint8_t) (camera->value2 & 0x000f);
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;

    case visca_cam_ex_exp_comp_reset://0x0E00,//8x 01 04 1F 0E 00 00 FF Exposure compensation reset
    case visca_cam_ex_aperture_reset://0x0200,//8x 01 04 1F 02 00 00 FF Aperture control reset
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = 0x1f;
        VISCA_packet->bytes[4] = camera->command >>8;
        VISCA_packet->bytes[5] = (uint8_t)camera->command;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;
    case visca_cam_ex_exp_comp_up:
        //0x0E02,//8x 01 04 1F 0E 02 pp FF Exposure compensation up
        //pp: Step number pp=00h to 7Fh
        //(However, 00h is the same operation as 01h.)
    case visca_cam_ex_exp_comp_down :
        // 0x0e03,//8x 01 04 1F 0E 03 pp FF Exposure compensation down
        //pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    case visca_cam_ex_aperture_up :
        //0x0202,//8x 01 04 1F 02 02 pp FF Aperture control up
        //pp: Step number pp=00h to 7Fh (However, 00h is the same operation as 01h.)
    case visca_cam_ex_aperture_down :
        //0x0203,//8x 01 04 1F 02 03 pp FF Aperture control down pp: Step number pp=00h to 7Fh
        //(However, 00h is the same operation as 01h.)
        VISCA_packet->length = 0x08;
        VISCA_packet->bytes[3] = 0x1f;
        VISCA_packet->bytes[4] = camera->command >>8;
        VISCA_packet->bytes[5] = (uint8_t)camera->command;
        VISCA_packet->bytes[6] = (uint8_t)(camera->value & 0x00ff);
        VISCA_packet->bytes[7] = VISCA_TERMINATOR;
        break;
        // Standart command 9 bytes with arguments
    case visca_zoom_direct:        //8x 01 04 47 0p 0q 0r 0s FF pqrs: Zoom Position
    case visca_dzoom_direct:       //8x 01 04 46 00 00 0p 0q FF pq:   D-Zoom Position
    case visca_focus_direct:       //8x 01 04 48 0p 0q 0r 0s FF pqrs: Focus Position
    case visca_focus_near_limit:   //8x 01 04 28 0p 0q 0r 0s FF pqrs: Focus Near Limit Position
    case visca_af_mode_active_interval_time:
        //8x 01 04 27 0p 0q 0r 0s FF Movement Time,pqrs: Interval
    case visca_cam_rgain_direct:   //8x 01 04 43 00 00 0p 0q FF R Gain,pq:
    case visca_cam_bgain_direct:   //8x 01 04 44 00 00 0p 0q FF B Gain,pq:
    case visca_cam_shutter_direct: //8x 01 04 4A 00 00 0p 0q FF Direct,pq: Shutter Position
    case visca_cam_iris_direct:    //8x 01 04 4B 00 00 0p 0q FF Direct,pq: Iris Position
    case visca_cam_gain_direct:    //8x 01 04 4C 00 00 0p 0q FF Direct,pq: Gain Position
    case visca_cam_bright_direct:  //8x 01 04 4D 00 00 0p 0q FF Direct,pq: Bright Position
    case visca_cam_expcomp_direct: //8x 01 04 4E 00 00 0p 0q FF Direct,pq: ExpComp Position
    case visca_cam_spotae_position://8x 01 04 29 0p 0q 0r 0s FF Position,pq: X (0 to F), rs: Y (0 to F)
    case visca_cam_aperture_direct://8x 01 04 42 00 00 0p 0q FF Direct,pq: Aperture Gain
    case visca_cam_autoicr_threshold:
        //8x 01 04 21 00 00 0p 0q FF Threshold,pq: ICR ON -> OFF Threshold Level
    case visca_cam_id_write:       //8x 01 04 22 0p 0q 0r 0s FF,pqrs: Camera ID (=0000h to FFFFh)
    case visca_cam_color_gain_direct://8x 01 04 49 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
    case visca_cam_color_hue_direct://8x 01 04 4F 00 00 00 0p FF p: Color Hue setting 0h (-14 degrees) to Eh (+14 degrees)

        VISCA_packet->length = 0x09;
        VISCA_packet->bytes[3] = (camera->command>>8);
        VISCA_packet->bytes[4] = (uint8_t)((camera->value & 0xf000)>>12);
        VISCA_packet->bytes[5] = (uint8_t)((camera->value & 0x0f00)>>8 );
        VISCA_packet->bytes[6] = (uint8_t)((camera->value & 0x00f0)>>4 );
        VISCA_packet->bytes[7] = (uint8_t) (camera->value & 0x000f     );
        VISCA_packet->bytes[8] = 0xff;
        break;
        //Special command with 10 bytes and 2 arguments
    case visca_cam_memsave_write:  //8x 01 04 23 0X 0p 0q 0r 0s FF
        //X: 00 to 07 (Address), total 16 byte ,pqrs: 0000h to FFFFh (Data)
        VISCA_packet->length = 0x0A;
        VISCA_packet->bytes[3] = (camera->command>>8);
        VISCA_packet->bytes[4] = (uint8_t)(camera->value2 & 0x000F);
        VISCA_packet->bytes[5] = (uint8_t)((camera->value & 0xF000)>>12);
        VISCA_packet->bytes[6] = (uint8_t)((camera->value & 0x0F00)>>8 );
        VISCA_packet->bytes[7] = (uint8_t)((camera->value & 0x00F0)>>4 );
        VISCA_packet->bytes[8] = (uint8_t) (camera->value & 0x000F     );
        VISCA_packet->bytes[9] = VISCA_TERMINATOR;
        break;
    case visca_cam_ex_auto_icr :// 0x1f21,
        //8x 01 04 1F 21 00 00 0p 0q FF pq: ICR ON->OFF threshold when Auto ICR is on pq=00h to FFh
        //8x 01 04 1F 21 01 00 0r 0s FF pq: On level ICR OFF->ON when Auto ICR is on pq=00h to 1Ch
        VISCA_packet->length = 0x0A;
        VISCA_packet->bytes[3] = camera->command >>8;
        VISCA_packet->bytes[4] = (uint8_t)camera->command;
        VISCA_packet->bytes[5] = (uint8_t)(camera->value2 & 0x0001);
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = (uint8_t)(camera->value & 0x00F0);
        VISCA_packet->bytes[8] = (uint8_t)(camera->value & 0x000F);
        VISCA_packet->bytes[9] = VISCA_TERMINATOR;
        break;
    case visca_cam_ex_exp_comp_direct : //0x1f4e //8x 01 04 1F 4E 00 00 0p 0q FF
        //Set the exposure compensation to the specified level pq: Level pq=00h to FFh
    case visca_cam_ex_aperture_direct : //0x1f42,//8x 01 04 1F 42 00 00 0p 0q FF
        //Set the aperture control to the specified level pq: Level pq=00h to FFh
        VISCA_packet->length = 0x0A;
        VISCA_packet->bytes[3] = camera->command >> 8;
        VISCA_packet->bytes[4] = (uint8_t)camera->command;
        VISCA_packet->bytes[5] = 0x00;
        VISCA_packet->bytes[6] = 0x00;
        VISCA_packet->bytes[7] = (uint8_t)(camera->value & 0x00F0);
        VISCA_packet->bytes[8] = (uint8_t)(camera->value & 0x000F);
        VISCA_packet->bytes[9] = VISCA_TERMINATOR;
        break;
        //Special command 13 bytes and 3 arguments
    case visca_cam_wd_set_parameter:

        //Set Parameter 8x 01 04 2D 00 0q 0r 0s 00 00 00 00 FF
        /*q: Display brightness level (0: Dark to 6: Bright)
          r: Brightness compensation selection (0: Very dark, 1: Dark,2: Standard, 3: Bright)
          s: Compensation level (0: Low, 1: Mid, 2: High)*/
        VISCA_packet->length = 0x0d;
        VISCA_packet->bytes[3] = 0x2D;
        VISCA_packet->bytes[4] = 0x00;
        VISCA_packet->bytes[5] = (uint8_t)((camera->value & 0x0F00)>>8 );
        VISCA_packet->bytes[6] = (uint8_t)((camera->value & 0x00F0)>>4 );
        VISCA_packet->bytes[7] = (uint8_t) (camera->value & 0x000F     );
        VISCA_packet->bytes[8] = 0x00;
        VISCA_packet->bytes[9] = 0x00;
        VISCA_packet->bytes[10] = 0x00;
        VISCA_packet->bytes[11] = 0x00;
        VISCA_packet->bytes[11] = VISCA_TERMINATOR;
        break;
        //visca_zoom_focus: 0x4799
    case visca_zoom_focus://CAM_ZoomFocus Direct 8x 01 04 47 0p 0q 0r 0s 0t 0u 0v 0w FF
        //pqrs: Zoom Position , tuvw: Focus Position
        VISCA_packet->length = 0x0d;
        VISCA_packet->bytes[3] = 0x47;

        VISCA_packet->bytes[4] = (uint8_t)((camera->value & 0xf000)>>12);
        VISCA_packet->bytes[5] = (uint8_t)((camera->value & 0x0f00)>>8 );
        VISCA_packet->bytes[6] = (uint8_t)((camera->value & 0x00f0)>>4 );
        VISCA_packet->bytes[7] = (uint8_t) (camera->value & 0x000f     );

        VISCA_packet->bytes[8] = (uint8_t)((camera->value2 & 0xf000)>>12);
        VISCA_packet->bytes[9] = (uint8_t)((camera->value2 & 0x0f00)>>8 );
        VISCA_packet->bytes[10] = (uint8_t)((camera->value2 & 0x00f0)>>4 );
        VISCA_packet->bytes[11] = (uint8_t) (camera->value2 & 0x000f     );

        VISCA_packet->bytes[12] = VISCA_TERMINATOR;
        break;
        // Titles
    case visca_cam_multi_line_title_set1:
        // 8x 01 04 73 1L 00 nn pp qq 00 00 00 00 00 00 FF,
        //l: line number, nn: h-position, pp: color, qq: blink
        VISCA_packet->length = 0x10;
        VISCA_packet->bytes[3] = camera->command>>8;
        VISCA_packet->bytes[4] = (uint8_t)camera->command + (camera->title.line & 0x0F);
        VISCA_packet->bytes[5] = 0x00;
        VISCA_packet->bytes[6] = camera->title.hposition;
        VISCA_packet->bytes[7] = camera->title.color;
        VISCA_packet->bytes[8] = camera->title.blink;
        VISCA_packet->bytes[9]  = 0x00;
        VISCA_packet->bytes[10] = 0x00;
        VISCA_packet->bytes[11] = 0x00;
        VISCA_packet->bytes[12] = 0x00;
        VISCA_packet->bytes[13] = 0x00;
        VISCA_packet->bytes[14] = 0x00;
        VISCA_packet->bytes[15] = VISCA_TERMINATOR;
        break;
    case visca_cam_multi_line_title_set2:
        // 8x 01 04 73 2L mm nn pp qq rr ss tt uu vv ww FF,
        //L: line number,mnpqrstuvw: setting of characters (1 to 10)
    case visca_cam_multi_line_title_set3:
        // 8x 01 04 73 3L mm nn pp qq rr ss tt uu vv ww FF,
        //L: line number,mnpqrstuvw: setting of characters (11 to 20)
        VISCA_packet->length = 0x10;
        VISCA_packet->bytes[3] = camera->command>>8;
        VISCA_packet->bytes[4] = (uint8_t)camera->command + (camera->title.line & 0x0F);
        uint8_t ttlcnt;
        for(ttlcnt = 0 ;ttlcnt<10;ttlcnt++)
        {
            VISCA_packet->bytes[5+ttlcnt] = camera->title.chars[ttlcnt];
        }
        VISCA_packet->bytes[15] = VISCA_TERMINATOR;
        break;
        //Standart command 6 bytes without arguments
    default:
        VISCA_packet->bytes[3] = camera->command >>8;
        VISCA_packet->bytes[4] = (uint8_t)camera->command;
    }
    return (VISCA_SUCCESS);
}
void ViscaInquiryCommandPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera)
{
    VISCA_packet->length = 0x05;
    VISCA_packet->bytes[0] = VISCA_HEADER+camera->camnum;
    VISCA_packet->bytes[1] = VISCA_INQUIRY;
    VISCA_packet->bytes[2] = camera->category;
    VISCA_packet->bytes[3] = camera->inquiry;
    VISCA_packet->bytes[4] = VISCA_TERMINATOR;
}

void ViscaExtInquiryCommandPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera,ext_inquiry_command_list_t inq)
{
    uint32_t * P2;
    P2 = (uint32_t *)(&VISCA_packet->bytes[3]);
    if(inq == CAM_ExExpCompPosInq || inq == CAM_ExApertureInq )
        VISCA_packet->length = 0x06;
    else VISCA_packet->length = 0x07;
    VISCA_packet->bytes[0] = VISCA_HEADER+camera->camnum;
    VISCA_packet->bytes[1] = VISCA_INQUIRY;
    VISCA_packet->bytes[2] = camera->category;
    *P2 = inq;
    if(inq == CAM_ExColorGainInq || inq == CAM_ExColorHueInq)
    {
        VISCA_packet->bytes[5] = camera->value & 0x0f;
    }
}

void ViscaLensControlSystemInquiryPack(VISCAPacket_t * VISCA_packet ,  VISCACamera_t * camera)
{
    VISCA_packet->length = 0x06;
    VISCA_packet->bytes[0] = VISCA_HEADER+camera->camnum;
    VISCA_packet->bytes[1] = VISCA_INQUIRY;
    VISCA_packet->bytes[2] = 0x7e;
    VISCA_packet->bytes[3] = 0x7e;
    VISCA_packet->bytes[4] = 0x00;
    VISCA_packet->bytes[5] = VISCA_TERMINATOR;
}

void visca_init_parser (visca_parser_state_t * vp)
{
    vp->step = 0;
}
uint8_t ViscaParseBuf (uint8_t* buf, uint8_t chars ,visca_parser_state_t * vp,VISCACamera_t *cam)
{
    uint8_t i = 0;
    while (i< chars)
    {
        switch (vp->step){
        case 0 :
        {
            if(buf[i]>=0x90 &&buf[i]<=0xf0)vp->step++;//
            //Cam address decode must be here RespondedCamAddr=(buf[i]-0x80)>>4;
        }break;
        case 1:
        {
            if(buf[i]==0x50)vp->step++;
            else vp->step=0;
        }break;
        case 2:{
            switch(cam->inquiry){
            case CAM_ZoomPosInq        : // y0 50 0p 0q 0r 0s FF pqrs: Zoom Position
            {
                vp->datalen++;
                switch(vp->datalen){
                case 1:vp->data=buf[i]<<12;break;
                case 2:vp->data+=buf[i]<<8;break;
                case 3:vp->data+=buf[i]<<4;break;
                case 4:vp->data+=buf[i];   break;
                case 5:
                    if(buf[i]==0xff){cam->ZoomPosition=vp->data;}
                    vp->datalen=0;
                    vp->step=0;
                    cam->inquiry=CAM_inq_none;
                    break;
                default:vp->datalen=0;vp->step=0;break;
                }
            }break;
            case CAM_DZoomPosInq       : // y0 50 00 00 0p 0q FF pq: D-Zoom Position
            {}break;
            case CAM_FocusPosInq       : // y0 50 0p 0q 0r 0s FF pqrs: Focus Position
            {}break;
            case CAM_FocusNearLimitInq : // y0 50 0p 0q 0r 0s FF pqrs: Focus Near Limit Position

            {}break;
            case CAM_PowerInq          : // y0 50 02 FF On , y0 50 03 FF Off (Standby)
            {}break;
            case CAM_DZoomModeInq      : // y0 50 02 FF D-Zoom On , y0 50 03 FF D-Zoom Off
            {}break;
            case CAM_DZoomC_SModeInq   : // y0 50 00 FF Combine Mode , y0 50 01 FF Separate Mode
            {}break;
            case CAM_FocusModeInq      : // y0 50 02 FF Auto Focus , y0 50 03 FF Manual Focus
            {}break;
            case CAM_AFSensitivityInq  : // y0 50 02 FF AF Sensitivity Normal , y0 50 03 FF AF Sensitivity Low
            {}break;
            case CAM_AFModeInq         : // y0 50 00 FF Normal AF , y0 50 01 FF Interval AF , y0 50 02 FF Zoom Trigger AF
            {}break;
            case CAM_AFTimeSettingInq  : // y0 50 0p 0q 0r 0s FF pq: Movement Time, rs: Interval
            {}break;
            case CAM_IRCorrectionInq   : // y0 50 00 FF Standard, y0 50 01 FF IR Light
            {}break;
            case CAM_WBModeInq         : // y0 50 00 FF Auto, y0 50 01 FF Indoor, y0 50 02 FF Outdoor, y0 50 03 FF One Push WB
                // y0 50 04 FF ATW, y0 50 05 FF Manual, y0 50 06 FF Outdoor Auto, y0 50 07 FF Sodium Lamp Auto
                // y0 50 08 FF Sodium Lamp, y0 50 09 FF Sodium Lamp Outdoor Auto
            {}break;
            case CAM_RGainInq          : // y0 50 00 00 0p 0q FF pq: R Gain
            {}break;
            case CAM_BGainInq          : // y0 50 00 00 0p 0q FF pq: B Gain
            {}break;
            case CAM_AEModeInq         : // y0 50 00 FF Full Auto, y0 50 03 FF Manual
                // y0 50 0A FF Shutter Priority, y0 50 0B FF Iris Priority, y0 50 0D FF Bright*/
            {}break;
            case CAM_AutoSlowShutterInq: // y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_ShutterPosInq     : // y0 50 00 00 0p 0q FF pq: Shutter Position
            {}break;
            case CAM_IrisPosInq        : // y0 50 00 00 0p 0q FF pq: Iris Position
            {}break;
            case CAM_GainPosInq        : // y0 50 00 00 0p 0q FF pq: Gain Position
            {}break;
            case CAM_GainLimitInq      : // y0 50 0q FF p: Gain Limit
            {}break;
            case CAM_BrightPosInq      : // y0 50 00 00 0p 0q FF pq: Bright Position
            {}break;
            case CAM_ExpCompModeInq    : // y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_ExpCompPosInq     : // y0 50 00 00 0p 0q FF pq: ExpComp Position
            {}break;
            case CAM_BackLightModeInq  : // y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_SpotAEModeInq     : // y0 50 02 FF On , y0 50 03 FF Off
            {}break;
            case CAM_SpotAEPosInq      : // y0 50 0p 0q 0r 0s FF pq: X position, rs: Y position
            {}break;
            case CAM_WDModeInq         : // y0 50 02 FF On, y0 50 03 FF Off, y0 50 06 FF VE On
            {}break;
            case CAM_WDParameterInq    : // y0 50 00 0q 0r 0s 0t 0u 00 00 FF
                /*q: Display brightness level (0: Dark to 6: Bright)
                                    r: Brightness compensation selection (0: Very dark,
                                    1: Dark, 2: Standard, 3: Bright)
                                    s: Compensation level (00h: Low, 01h: Mid, 02h: High)
                                    tu: Always 0*/
            {}break;
            case CAM_AE_ResponseInq       :// y0 50 pp FF pp: 01h to 30h
            {}break;
            case CAM_DefogInq             :// y0 50 02 00 FF Defog ON , y0 50 03 00 FF Defog OFF
            {}break;
            case CAM_ApertureInq          :// y0 50 00 00 0p 0q FF pq: Aperture Gain
            {}break;
            case CAM_HRModeInq            :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_NRModeInq            :// y0 50 0p FF Noise Reduction p: 00h to 05h
            {}break;
            case CAM_GammaInq             :// y0 50 0p FF Gamma p: 00h to 04h
            {}break;
            case CAM_HighSensitivityInq   :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_LR_ReverseModeInq    :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_FreezeModeInq        :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_PictureEffectModeInq :// y0 50 00 FF Off, y0 50 02 FF Neg.Art, y0 50 04 FF Black & White
            {}break;
            case CAM_PictureFlipModeInq   :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_ICRModeInq           :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_AutoICRModeInq       :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_AutoICRThresholdInq  :// y0 50 00 00 0p 0q FF pq: ICR ON ? OFF Threshold Level
            {}break;
            case CAM_AutoICRAlarmReplyInq :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_MemoryInq            :// y0 50 pp FF pp: Memory number recalled last
            {}break;
            case CAM_MemSaveInq           :// y0 50 0p 0q 0r 0s FF X: 00h to 07h (Address)pqrs: 0000h to FFFFh (Data)
            {}break;
            case CAM_DisplayModeInq       :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_StabilizerModeInq    :// y0 05 02 FF On, y0 05 03 FF Off, y0 05 00 FF Hold
            {}break;
            case CAM_MuteModeInq          :// y0 50 02 FF On, y0 50 03 FF Off
            {}break;
            case CAM_PrivacyMonitorInq    :// y0 50 pp pp pp pp FF pp pp pp pp: Mask is displayed now.
            {}break;
            case CAM_IDInq                :// y0 50 0p 0q 0r 0s FF pqrs: Camera ID
            {}break;
            case CAM_VersionInq           :// y0 50 00 20 mn pq rs tu vw FF,mnpq: Model Code (04xx)rstu: ROM version vw: Socket Number (= 0x02)*/
            {}break;
            case CAM_ColorEnhanceInq      :// y0 50 mm 00 pp qq rr ss tt uu FF mm: Threshold level
                                           /*pp: Y fixed color for high-intensity
                                           qq: Cr fixed color for high-intensity
                                           rr: Cb fixed color for high-intensity
                                           ss: Y fixed color for low-intensity
                                           tt: Cr fixed color for low-intensity
                                           uu: Cb fixed color for low-intensity
                                           8x 09 04 50 FF , y0 50 02 FF On, y0 50 03 FF Off*/
            {}break;
            case CAM_ChromaSuppressInq     :// y0 50 pp FF pp: Chroma Suppress setting level
            {}break;
            case CAM_ColorGainInq          :// y0 50 00 00 00 0p FF p: Color Gain setting 0h (60%) to Eh (200%)
            {}break;
            case CAM_ColorHueInq           :// y0 50 00 00 00 0p FF p: Color Hue setting 0h (- 14 degrees) to Eh (+ 14 degrees)
            {}break;
            case CAM_TempInq               ://
            {}break;
            case CAM_inq_none : break;
            default :
                vp->step=0;
                vp->datalen=0;
                break;
            }

        }break;
        default :vp->step = 0; break;
        }

        if(buf[i] == VISCA_TERMINATOR) vp->step = 0;
        i++;
    }
    return(0);
}

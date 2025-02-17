#ifndef __AWT_GFX_H_

#define __AWT_GFX_H_

/*
awt_gfx - gfx-lib for ATW800/2
Andre Saischowa / 2024
*/
#include "as_int.h"
#include <string.h>

/*
ATW800/2 Memorymap -- 21.10.2024
#80000070 - #80000FFF internal memory
#80001000 - #80800FFF external memory, configurable
#40000000 - #400003FF RGB LUT
#40000400 - #400007FF FPGA version string
#40001000 - #4000103F Video Timing Generator register

Register Video Timing Generator (VTG):

C/DFF800 Control Register :
  bit 0 = enable VTG
  bit 1 = posHsync
  bit 2 = posVsync
  bit 3 = transition 0 to 1 transfers PLL registers
  bit 4 und 5 = Video Mode, see below
  bit 6 = RGB LUT select 0 = Atari, 1 = Transputer


C/DFF802 HFPreg : 8 bit horizontal front porch
C/DFF804 HSYreg : 8 bit horizontal sync
C/DFF806 HBPreg : 8 bit horizontal back porch
C/DFF808 HDIreg : 12 bit horizontal display
C/DFF80A VFPreg : 8 bit vertical front porch
C/DFF80C VSYreg : 8 bit vertical sync
C/DFF80E VBPreg : 8 bit vertical back porch
C/DFF810 VDIreg : 12 bit vertical display
C/DFF812 PLLfbdsel : video PLL value for feedback divider, register value = real value -1
C/DFF814 PLLidsel  : video PLL value for input divider, register value = real value -1
C/DFF816 PLLodsel  : video PLL value for output divider, register value = real value
C/DFF818 VidMemStartAddress : video memory start address lower 16 bits
C/DFF81A VidMemStartAddress : video memory start address upper 7 bits
C/DFF81E A20Gate : 0 = 1MB address space, 1 = 2 MB address space, all Cxxxxx IO addresses remap to Dxxxxx

*/
#define AWT_VTG_CTRL               0
#define AWT_VTG_HFPreg             1      /*: 8 bit horizontal front porch */
#define AWT_VTG_HSYreg             2      /* 8 bit horizontal sync */
#define AWT_VTG_HBPreg             3      /* 8 bit horizontal back porch */
#define AWT_VTG_HDIreg             4      /* 12 bit horizontal display */
#define AWT_VTG_VFPreg             5      /* 8 bit vertical front porch */
#define AWT_VTG_VSYreg             6      /* 8 bit vertical sync */
#define AWT_VTG_BPreg              7      /* 8 bit vertical back porch */
#define AWT_VTG_VDIreg             8      /* 12 bit vertical display */
#define AWT_VTG_PLLfbdsel          9      /* video PLL value for feedback divider, register value = real value -1 */
#define AWT_VTG_PLLidsel           10     /* video PLL value for input divider, register value = real value -1 */
#define AWT_VTG_PLLodsel           11     /* video PLL value for output divider, register value = real value */
#define AWT_VTG_VidMemStartAddress 12     /* video memory start address lower 16 bits */
#define AWT_VTG_A20Gate            13     /* 0 = 1MB address space, 1 = 2 MB address space, all Cxxxxx IO addresses remap to Dxxxxx */




#ifndef AS_AWT_SCREEN_WIDTH
#define AS_AWT_SCREEN_WIDTH  640
#endif
#ifndef AS_AWT_SCREEN_HEIGHT
#define AS_AWT_SCREEN_HEIGHT 480
#endif
#ifndef AS_AWT_SCREEN_STRIDE
#define AS_AWT_SCREEN_STRIDE 640
#endif

#ifndef AS_AWT_SCREEN_COLORDEPTH
#define AS_AWT_SCREEN_COLORDEPTH 8 /*(1,8,15,16 Bit)*/
#endif

#ifndef AS_AWT_SCREEN_VRAM
#define AS_AWT_SCREEN_VRAM 0x80600000
#endif

#define AWTCOLOUR_PALETTE    0x40000000
#define VTG_REGISTER          0x40001000

#define COLOR_565(G,B,R)  ((G & 0xFC) << 3) | ((B & 0xF8) >> 3) | ((R & 0xF8) << 8)

extern void awtInitVTG(void);
extern void awtClose(void);
extern void awtSetPaletteColor(int idx, uint8_t r, uint8_t g,uint8_t b);
extern void awtClearScreen(void);
extern void awtBlitRect(int x, int y, int w, int h, uint8_t * srcAdr, int src_stride);

#ifdef AWT_GFX_IMPLEMENTATION



void awtInitVTG(void){
  int * vtg_register;
  vtg_register=(int*)VTG_REGISTER;
#ifdef AWT_INIT_VTG
/*VTG-Register setting*/
   vtg_register[AWT_VTG_CTRL]    = 0; /* VTG aus */
       vtg_register[AWT_VTG_A20Gate] = 1; /*  auf 2MB schalten */

       switch(AS_AWT_SCREEN_WIDTH) {
          case 640:
              vtg_register[AWT_VTG_PLLfbdsel] = 16;
              vtg_register[AWT_VTG_PLLidsel]  = 2;
              vtg_register[AWT_VTG_PLLodsel]  = 3;

              vtg_register[AWT_VTG_HFPreg]  = 16;
              vtg_register[AWT_VTG_HSYreg]  = 96;
              vtg_register[AWT_VTG_HBPreg]  = 48;
              vtg_register[AWT_VTG_HDIreg]  = 640;

              vtg_register[AWT_VTG_VFPreg]  = 1;
              vtg_register[AWT_VTG_VSYreg]  = 3;
              vtg_register[AWT_VTG_BPreg]  = 16;
              vtg_register[AWT_VTG_VDIreg]  = 480;
              printf("Init 640x480\r\n");

            break;
          case 800:
              vtg_register[AWT_VTG_PLLfbdsel] = 36;
              vtg_register[AWT_VTG_PLLidsel]  = 4;
              vtg_register[AWT_VTG_PLLodsel]  = 3;

              vtg_register[AWT_VTG_HFPreg]  = 40;
              vtg_register[AWT_VTG_HSYreg]  = 128;
              vtg_register[AWT_VTG_HBPreg]  = 88;
              vtg_register[AWT_VTG_HDIreg]  = 800;

              vtg_register[AWT_VTG_VFPreg]  = 1;
              vtg_register[AWT_VTG_VSYreg]  = 4;
              vtg_register[AWT_VTG_BPreg]  = 23;
              vtg_register[AWT_VTG_VDIreg]  = 600;
              printf("Init 800x600\r\n");
            break;
          case 1024:
              vtg_register[AWT_VTG_PLLfbdsel] = 35;
              vtg_register[AWT_VTG_PLLidsel]  = 2;
              vtg_register[AWT_VTG_PLLodsel]  = 1;

              vtg_register[AWT_VTG_HFPreg]  = 24;
              vtg_register[AWT_VTG_HSYreg]  = 136;
              vtg_register[AWT_VTG_HBPreg]  = 160;
              vtg_register[AWT_VTG_HDIreg]  = 1024;

              vtg_register[AWT_VTG_VFPreg]  = 3;
              vtg_register[AWT_VTG_VSYreg]  = 6;
              vtg_register[AWT_VTG_BPreg]   = 29;
              vtg_register[AWT_VTG_VDIreg]  = 768;
              printf("Init 1024x768\r\n");
            break;
          default:
            break;
       }

       switch(AS_AWT_SCREEN_COLORDEPTH) {
          case 1:
            vtg_register[AWT_VTG_CTRL] = (int)(0x09 | 0x40);
            break;
          case 15:
            vtg_register[AWT_VTG_CTRL] = (int)(0x39 | 0x40);
            break;
          case 16:
            vtg_register[AWT_VTG_CTRL] = (int)(0x29 | 0x40);
            break;
          default: /*8 Bit*/
            vtg_register[AWT_VTG_CTRL] = (int)(0x19 | 0x40);
            break;
       }

#else
       switch(AS_AWT_SCREEN_COLORDEPTH) {
          case 1:
            vtg_register[AWT_VTG_CTRL] = (int)(0x01 | 0x40);
            break;
          case 8:
            vtg_register[AWT_VTG_CTRL] = (int)(0x11 | 0x40);
            break;
           default:
            break;
       }

#endif

}

void awtClose(void){
  int * vtg_register;
  /*CLUT switching to Atari-CLUT*/
  vtg_register=(int*)VTG_REGISTER;

  switch(AS_AWT_SCREEN_COLORDEPTH) {
    case 1:
      vtg_register[AWT_VTG_CTRL] = (int)(0x01);
      break;
    case 8:
      vtg_register[AWT_VTG_CTRL] = (int)(0x11);
      break;
      default:
      break;
  }
}

void awtSetPaletteColor(int idx, uint8_t r, uint8_t g,uint8_t b){
       int * clutbase = NULL;
       clutbase = (int*)AWTCOLOUR_PALETTE;
       clutbase[idx]   = COLOR_565(g,b,r);

}

void awtClearScreen(void){
    int i;
    /*first Row per Hand*/
    unsigned char * screenBuf= (unsigned char *)AS_AWT_SCREEN_VRAM;
    for(i=0;i < AS_AWT_SCREEN_WIDTH;i++){
         screenBuf[i]=0;
    }
    /*the rest with power*/
    for(i=1;i < AS_AWT_SCREEN_HEIGHT;i++){
       memcpy(screenBuf+AS_AWT_SCREEN_STRIDE,screenBuf,AS_AWT_SCREEN_WIDTH);
       screenBuf += (AS_AWT_SCREEN_STRIDE);
    }
}
void awtBlitRect(int x, int y, int w, int h, uint8_t * srcAdr, int src_stride){
       int _y;
       uint8_t * atwAdr = (uint8_t*)(AS_AWT_SCREEN_VRAM + (AS_AWT_SCREEN_STRIDE*y)+x);

       for(_y=0;_y < h;_y++){
          memcpy(atwAdr,srcAdr,w);
          atwAdr += AS_AWT_SCREEN_STRIDE;
          srcAdr += src_stride;
       }
}
#endif

#endif

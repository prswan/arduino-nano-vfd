//
// Copyright (c) 2025, Paul R. Swan
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#ifndef Sym_h
#define Sym_h

//
// Symbol identification
//
typedef enum {

    SymNone = 0,

    // Sony TC-WR775
    SymText_DOLBY_NR,
    SymText_A_plus_B,
    SymText_B,
    SymText_C,
    SymMinus,
    SymText_MEMORY,
    SymDecimalPoint,
    SymText_HIGH,
    SymText_NORM,
    SymPlayReverse,
    SymPlayForward,
    SymTextBox_FADE,
    SymFadeArrowHeadForward,
    SymFadeArrowHeadReverse,
    SymText_PLAY,
    SymText_AUTO_PAUSE,
    SymPause,
    SymText_REC,
    SymText_BLANK_SKIP,
    SymDotBar123,
    SymDotBar4,

    // Sony DVP-NS725P Additions
    SymText_DVD,
    SymText_TRK,
    SymText_V,
    SymText_CD,
    SymRepeat,
    SymText_1,
    SymMovieCamera,
    SymColon,
    SymDolbyDoubleD_D,
    SymText_MP3,
    SymText_dts,

    // Panasonic DVD-RV32 Additions
    SymText_PGM,    
    SymText_A_minus,
    SymText_GROUP,  
    SymText_TITLE,  
    SymText_TRACK,  
    SymText_CHAP,   
    SymText_D_N_R,  
    SymText_PG,     
    SymText_D_MIX,  
    SymText_A_SRD,  
    SymText_BASS,   
    SymText_CINEMA, 
    SymText_D_ENH,  
    SymText_VIDEO,  
    SymText_RND,    
    SymText_AUDIO,  
    SymText_WMA,    
    SymText_VR,     

    // Samsung BD-P1590 Additions
    SymDiscIn,   
    SymText_BD,  
    SymText_USB, 
    SymText_HDMI,
    SymText_HD,  
    SymText_24F, 

    // Samsung BD-P1590 Graphic Symbol Additions, Group 0
    SymBarBottom,
    SymSquare,

    // Samsung BD-P1590 Graphic Symbol Additions, Group 1
    SymArrowHeadForwardLight,
    SymArrowHeadForward,
    SymArrowHeadForwardBold,
    SymChevron,
    SymText_8,

    // Pioneer DVR-220 Additions
    SymText_HDD,
    SymArrowHeadReverse,
    SymText_PL,
    SymText_PM,
    SymText_2,
    SymText_3,
    SymText_REM,
    SymText_P,
    SymText_R,
    SymText_W,
    SymClock,
    SymText_DISC,
    SymText_FINE,
    SymText_AUTO,
    SymText_SP,
    SymText_L,
    SymText_SAP,
    SymText_LP,
    SymArrowForward,
    SymText_CH,
    SymText_VPS,
    SymText_OVER,
    SymText_EP,
    SymArrowReverse,
    SymText_H,
    SymText_M,
    SymText_S,
    SymText_PDC,
    SymText_NTSC,
    SymText_MN,

    // TEAC PD-D1200 Additions
    SymText_EDIT,
    SymText_INTRO,
    SymText_SHUFFLE,
    SymText_MIN,
    SymText_SEC,
    SymText_TOTAL,
    SymText_PAUSE,
    SymText_EACH,
    SymText_REMAIN,
    SymText_REPEAT,
    SymText_ONE,
    SymText_ALL,

    //
    SymEnd
} Sym;

#endif

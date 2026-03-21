# Layout Finding the TEAC PD-D1200 VFD



This is on a Universal VFD V1.10 driver board driven by 1 x A5818 32-bit driver IC.

* The driver IC is the 1st IC in the serial chain.
* The display is fitted solder side up lay flat against the PCB.



NOTE: this is a 0.156" pitch display installed on V1, but wire strapped on the 2mm matrix.

* V1 pins 41 (A50) \& 42 (A51) are cut trace isolated in the 2mm matrix for Fil2.
* V2 pins 4,5,8 (A1,A2,A5) are wire strapped to V2 pins 38,39,40.



## 1st Pass Configuration



There was no freely available/downloadable service manual was found, visually taking a guess and assigning pin functions:

* 10 Grids
* 10 Segments



```

//

// Pin Layout

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VFD Func :  F   F                                 G10  G9  G8      G7  G6  G5  G4  G3      G2                  G1  S1  S2  S3  S4      S5  S6  S7  S8      S9 S10           F   F

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VFD Pin  :  1   2                                  11  12  13      15  16  17  18  19      21                  26  27  28  29  30      32  33  34  35      37  38          41  42

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// V1 Pin   : 42  41  40  39  38  37  36  35  34  33  32  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// A Func.  :  F   F                                   5   2   1  34  32  31  30  29  26  25  24  23  21  20  19  18  16  15  14  13  11  10   9   8   6   5   4   3   1   F   F   F

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// U1 OUT   :                                         30   1  32      16  17  15  18  13  20  12  21  22  10  23   9   8  25   7  26  27   5  28   4   3  30   2  31  32

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//

static const PinMap s\_pinMapGrid\[] PROGMEM =

{

    {0, 0},

    // pin, bit (OUT-1)

    {26, ( 9-1)}, // G1

    {21, (12-1)}, // G2

    {19, (13-1)}, // G3

    {18, (18-1)}, // G4

    {17, (15-1)}, // G5

    {16, (17-1)}, // G6

    {15, (16-1)}, // G7

    {13, (32-1)}, // G8

    {12, ( 1-1)}, // G9

    {11, (30-1)}  // G10

};



//

static const PinMap s\_pinMapSegment\[] PROGMEM =

{

    {0, 0},

    // pin, bit (OUT-1)

    {27, ( 8-1)}, // S1

    {28, (27-1)}, // S2

    {29, ( 7-1)}, // S3

    {30, (26-1)}, // S4

    {32, ( 5-1)}, // S5

    {33, (28-1)}, // S6

    {34, ( 4-1)}, // S7

    {35, ( 3-1)}, // S8

    {37, ( 2-1)}, // S9

    {38, (31-1)}  // S10

};





## 1st Pass Layout Finder Results



```

0101 - reg 1 col 2 seg a 

0201 - reg 1 col 1 seg a 

0301 - reg 1 col 0 seg a 

0401 - nothing

0501 - nothing

0601 - reg 0 col 2 seg a 

0701 - nothing

0801 - reg 0 col 1 seg a 

0901 - nothing

1001 - reg 0 col 0 seg a 



0101 - reg 1 col 2 seg a 

0102 - nothing

0103 - reg 1 col 2 seg f

0104 - nothing

0105 - nothing

0106 - reg 1 col 2 seg b

0107 - reg 1 col 2 seg g

0108 - reg 1 col 2 seg e

0109 - reg 1 col 2 seg c

0110 - reg 1 col 2 seg d



&nbsp;=> Grid pins 1,2,3,6,8,10 confirmed grid pins

&nbsp;=> Seg pins 1,3,6,7,8,9,10 confirmed segment pins



Grid 04

-------

0401,0402,0403 nothing

0404 - number "2" (2nd to last grid)

0405 - number "4" (last grid)

&nbsp;=> Segment pins 04 \& 05 are grid pins 

&nbsp;=> Grid pin 04 is a segment pin

0406 - nothing

0407 - nothing

0408 - nothing

0409 - nothing

0410 - nothing



Grid 05

-------

0501,0502,0503 - nothing

0504 - number "7"

0505 - number "9"

0506 -> 0510 nothing

&nbsp;=> Grid pin 05 is a segment pin



Grid 07

-------

0701,0702,0703 - nothing

0704 - number "12"

0705 - number "14"

0706 -> 0710 - nothing

&nbsp;=> Grid pin 07 is a segment.



Grid 09

-------

0901,0902,0903 - nothing

0904 - number "17"

0905 - number "19"

0906 -> 0910 - nothing

&nbsp;=> Grid 09 is a segment.



Seg 02

------

What we know:

0102,0402,0502,0702,0902 - nothing

1002 - nothing

0202 - nothing

0302 - nothing

0602 - nothing

0802 - nothing



&nbsp;=> Counts

&nbsp;   - 11 segments

&nbsp;   -  8 grids



&nbsp;=> Seg pin 02 is likely a grid pin, but we need to check the pin translation on why it appears unconnected



## 2nd Pass Configuration



Applying the changes from the 1st pass and resequencing the functions numbers we have:



```

//

// Pin Layout

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VFD Func :  F   F                                  G1  S1  G2      S2  G3  S3  S4  G4      G5                  G6  S5  G7  S6  G8      G9  S7  S8  S9     S10 S11           F   F  

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// VFD Pin  :  1   2                                  11  12  13      15  16  17  18  19      21                  26  27  28  29  30      32  33  34  35      37  38          41  42

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// V1 Pin   : 42  41  40  39  38  37  36  35  34  33  32  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1    

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// A Func.  :  F   F                                   5   2   1  34  32  31  30  29  26  25  24  23  21  20  19  18  16  15  14  13  11  10   9   8   6   5   4   3   1   F   F   F  

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// U1 OUT   :                                         30   1  32      16  17  15  18  13  20  12  21  22  10  23   9   8  25   7  26  27   5  28   4   3  30   2  31  32

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//

static const PinMap s\_pinMapGrid\[] PROGMEM =

{

&nbsp;   {0, 0},

&nbsp;   // pin, bit (OUT-1)

&nbsp;   {11, (30-1)}, // G1

&nbsp;   {13, (32-1)}, // G2

&nbsp;   {16, (17-1)}, // G3

&nbsp;   {19, (13-1)}, // G4

&nbsp;   {21, (12-1)}, // G5

&nbsp;   {26, ( 9-1)}, // G6

&nbsp;   {28, (25-1)}, // G7

&nbsp;   {30, (26-1)}, // G8

&nbsp;   {32, ( 5-1)}  // G9

};



//

// TBD.

//

static const PinMap s\_pinMapSegment\[] PROGMEM =

{

&nbsp;   {0, 0},

&nbsp;   // pin, bit (OUT-1)

&nbsp;   {12, ( 1-1)}, // S1

&nbsp;   {15, (16-1)}, // S2

&nbsp;   {17, (15-1)}, // S3

&nbsp;   {18, (18-1)}, // S4

&nbsp;   {27, ( 8-1)}, // S5

&nbsp;   {29, ( 7-1)}, // S6

&nbsp;   {33, (28-1)}, // S7

&nbsp;   {34, ( 4-1)}, // S8

&nbsp;   {35, ( 3-1)}, // S9

&nbsp;   {37, ( 2-1)}, // S10

&nbsp;   {38, (31-1)}  // S11

};



## 2nd Pass Layout Finder Results



```
0101 - DISC

0201 - number "20"

0301 - TRACK

0401 - TOTAL

0501 - INTRO

0601 - SHUFFLE

0701 - MEMORY

0801 - number "17"

0901 - number "19"



&nbsp;=> All grids accounted for



Grid 04

-------

0401 - TOTAL

0402 - EACH

0403 - REMAIN

0404 - EDIT

0405 - reg 1 col 0 seg a 

0406 - reg 1 col 0 seg f

0407 - reg 1 col 0 seg b

0408 - reg 1 col 0 seg g

0409 - reg 1 col 0 seg e

0410 - reg 1 col 0 seg c

0411 - reg 1 col 0 seg d



Remaining Digits

----------------

0511 - reg 1 col 1 seg d

0611 - reg 1 col 2 seg d

0711 - reg 1 col 3 seg d

0811 - nothing

0911 - nothing



0111 - reg 0 col 0 seg d

0211 - reg 0 col 1 seg d

0311 - reg 0 col 2 seg d



&nbsp;=> All segments \& digits accounted for






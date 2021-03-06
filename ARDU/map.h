const unsigned char PROGMEM tiles[][32] = 
{
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
  {0xff,0xff,0xe3,0xc7,0xff,0xe7,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe3,0xc7,0xff,0xe7,0xf3,0xff,0xff},
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xcf,0xf7,0xfb,0xfd,0xfd,0xfe,0xfe,0xfe,0xfe,0xfd,0xfd,0xfb,0xf7,0xcf,0x3f},
  {0xfe,0xfd,0xfb,0xf7,0xe7,0xdb,0xbd,0x7e,0xfe,0xfd,0xfb,0xf7,0xe7,0xdb,0xbd,0x7e,0xfe,0xfd,0xfb,0xf7,0xe7,0xdb,0xbd,0x7e,0xfe,0xfd,0xfb,0xf7,0xe7,0xdb,0xbd,0x7e},
  {0xfe,0xfd,0xfb,0xf7,0xe7,0xdb,0xbd,0x7e,0xfe,0xfd,0xfb,0xf7,0xe7,0xdb,0xbd,0x7e,0x01,0xfe,0x02,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x02,0xfe,0x01},
  {0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x00,0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x00},
  {0xfb,0xfb,0x03,0xf3,0x73,0x03,0xf3,0xf3,0xf3,0xf3,0x03,0xf3,0xf3,0x03,0xfb,0xfb,0x7f,0x7f,0x80,0xbc,0xb9,0x81,0xb8,0xbf,0xbf,0xbf,0x80,0xbf,0xbf,0x80,0x7f,0x7f},
  {0x2b,0x45,0x0b,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x17,0x2b,0x55,0x2b,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0x55},
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f,0x6f},
  {0x01,0xda,0xda,0xc1,0x15,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0x15,0xc1,0xda,0xda,0x01,0x00,0xdd,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xee,0xdd,0x00},
  {0x00,0xb6,0xbf,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xbf,0xb6,0x00,0x80,0x7e,0x7e,0x80,0x9a,0x9a,0x9a,0x1a,0x9a,0x9a,0x9a,0x9a,0x80,0x7e,0x7e,0x00},
  {0x01,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0x01,0xf0,0x8b,0x6b,0x6b,0x8b,0xcb,0x8b,0x4b,0xcb,0xcb,0xcb,0x8b,0x6b,0x6b,0x8b,0x70},
  {0x03,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0xbd,0x03,0x00,0xff,0x40,0x6c,0x60,0x6c,0x6c,0x60,0x6c,0x60,0x6c,0x60,0x6c,0x40,0xff,0x00},
  {0x00,0xff,0x20,0x36,0x36,0x36,0x32,0x34,0x32,0x30,0x36,0x30,0x36,0x20,0xff,0x00,0x80,0x5f,0x50,0x9b,0x98,0x9b,0x9b,0x18,0x9b,0x98,0x9b,0x98,0x9b,0x50,0x5f,0x00},
  {0x00,0x7e,0x7e,0x00,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,0x00,0x7e,0x7e,0x00,0x00,0x7d,0x01,0x79,0x79,0x71,0x6d,0x51,0x51,0x6d,0x71,0x79,0x79,0x01,0x7d,0x00},
  {0x00,0xfd,0xfd,0xfd,0xfd,0x05,0x15,0x15,0x15,0x15,0x05,0xfd,0xfd,0xfd,0xfd,0x00,0x00,0x6f,0x6f,0x6f,0x6c,0x1a,0x6a,0x6a,0x6a,0x6a,0x1a,0x6c,0x6f,0x6f,0x6f,0x00},
  {0x02,0xf2,0xa2,0x52,0xa2,0x52,0xf2,0x02,0x02,0xf2,0xa2,0x52,0xa2,0x52,0xf2,0x02,0x00,0x3f,0x6a,0x55,0x6a,0x55,0x3f,0x00,0x00,0x3f,0x6a,0x55,0x6a,0x55,0x3f,0x00},
  {0x02,0x72,0x22,0x52,0x22,0x52,0x72,0x02,0x02,0x72,0x22,0x52,0x22,0x52,0x72,0x02,0x7f,0x53,0x55,0x65,0x7f,0x41,0x77,0x41,0x7f,0x63,0x5d,0x63,0x7f,0x41,0x75,0x7b},
  {0xff,0x03,0xfb,0xfb,0x5b,0x5b,0xd9,0x7a,0x5a,0x59,0xdb,0x5b,0xfb,0xfb,0x03,0xff,0xff,0xfc,0xfb,0xfb,0xfb,0xfb,0x83,0x73,0x73,0x83,0xfb,0xfb,0xfb,0xfb,0xfc,0xff},
  {0x18,0x65,0xba,0x7d,0xfa,0x75,0xfa,0x75,0xfa,0x75,0xfa,0x75,0xba,0x7d,0xa2,0x18,0xfe,0xfd,0xfa,0xb9,0x42,0x65,0x62,0x65,0x62,0x65,0x62,0x45,0xba,0xf9,0xfc,0xfe},
  {0x1f,0x67,0xbb,0x5d,0xfd,0x7e,0xbe,0x7e,0xfe,0x7e,0xbe,0x7d,0xfd,0x5b,0xa7,0x1f,0x18,0x65,0xba,0x7d,0xfa,0x75,0xfa,0x75,0xfa,0x75,0xfa,0x75,0xba,0x7d,0xa2,0x18},
  {0x18,0x61,0xb8,0x5d,0xfc,0x7e,0xbe,0x7e,0xfe,0x7e,0xbe,0x7d,0xfc,0x59,0xa0,0x00,0x18,0x65,0xba,0x7d,0xfa,0x75,0xfa,0x75,0xfa,0x75,0xfa,0x75,0xba,0x7d,0xa2,0x10},
  {0x00,0x15,0x2a,0x15,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55,0xc0,0x95,0x2a,0x15,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55},
  {0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55},
  {0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x8b,0xc5,0xe2,0x00,0x2b,0x55,0x2b,0x17,0x2b,0x17,0x2b,0x55,0x2b,0x55,0x2b,0x17,0x2b,0x15,0x8a,0xc0},
  {0x71,0x8e,0xdf,0xdf,0xd8,0x07,0xf7,0xf0,0xc0,0x83,0x0f,0x1f,0x3f,0x3f,0x7f,0x7f,0x38,0xc7,0xef,0xef,0xf7,0xe3,0x1c,0xbd,0xbb,0x7b,0x7b,0x78,0xb6,0xce,0xde,0xde},
  {0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0xee,0xee,0xee,0xc4,0x38,0xbc,0xbe,0x7e,0x7e,0x7e,0x7e,0x3c,0xc0,0xdc,0xde,0xde},
  {0x7f,0x7f,0x3f,0x3f,0x1f,0x0f,0x83,0xc0,0xf0,0xf7,0x07,0xd8,0xdf,0xdf,0x8e,0x71,0xee,0xee,0xce,0xb6,0x78,0x7b,0x7b,0xbb,0xbd,0x1c,0xe3,0xf7,0xef,0xef,0xc7,0x38},
  {0x0c,0xf3,0xf7,0xf7,0xe3,0xdc,0x3f,0xbf,0xbf,0xbf,0xbf,0x0e,0xf1,0xfb,0xfb,0xfb,0xff,0xfe,0xfd,0xfd,0xfd,0xf0,0xef,0xdf,0xdf,0xdf,0xdf,0xc3,0xbc,0x7e,0x7d,0x7d},
  {0xf7,0xf7,0xf7,0xe3,0x1c,0xbf,0xbf,0xbf,0x7f,0x7f,0x7f,0x3e,0xcd,0xf3,0xfb,0xfb,0x7d,0x7d,0xb1,0x8e,0xbf,0xbf,0x7f,0x7f,0x7f,0x7f,0xbf,0x8e,0xb1,0x7b,0x7b,0x7b},
  {0xfb,0xf7,0xf7,0xf3,0x0c,0xbf,0xbf,0xbf,0xbf,0x3f,0xde,0xe1,0xf7,0xf7,0xf3,0x00,0x7b,0x7d,0x7d,0xb8,0xc7,0xdf,0xdf,0xdf,0xdf,0xef,0xf0,0xfd,0xfd,0xfd,0xfe,0xff},
  {0x7e,0x7e,0x7e,0x7e,0x7e,0xfe,0xfe,0xfe,0xfe,0xfe,0xfd,0xfd,0xfb,0xf7,0xcf,0x3f,0x86,0x7a,0x7c,0x7c,0x18,0xe0,0xc0,0x01,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
  {0x3f,0xcf,0xf7,0xfb,0xfd,0xfd,0xfe,0xfe,0xfe,0xfe,0xfe,0x7e,0x7e,0x7e,0x7e,0x7e,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x03,0x01,0xc0,0xe0,0x18,0x7c,0x7c,0x7a,0x86},
  {0xf3,0x25,0xce,0x9e,0x1e,0x3e,0x3e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0xff,0xfe,0xfd,0xe3,0xdb,0xbb,0xba,0xb8,0xb6,0x8e,0x6e,0x6e,0x6c,0x60,0x9c,0xbe},
  {0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x3e,0x3e,0x1e,0x9e,0xce,0x25,0xf3,0xbe,0x9c,0x60,0x6c,0x6e,0x6e,0x8e,0xb6,0xb8,0xba,0xbb,0xdb,0xe3,0xfd,0xfe,0xff},
  {0x38,0xc7,0xef,0xef,0x0e,0xf5,0xf3,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x86,0x79,0x7b,0x7b,0x30,0xcf,0xef,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
  {0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xf3,0xf5,0x0e,0xef,0xef,0xc7,0x38,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xef,0xcf,0x30,0x7b,0x7b,0x79,0x86},
  {0xaa,0x55,0xaa,0x5d,0xaa,0x5d,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xba,0x55,0xba,0x55,0xaa,0x55},
  {0xfe,0xfd,0x13,0xcd,0x35,0xda,0xd6,0x36,0x2e,0xde,0xde,0x3d,0xcb,0x13,0xbd,0x7e,0xfe,0xfd,0xe3,0x9a,0x58,0x24,0x3a,0x03,0xbb,0x3a,0x24,0x58,0x9a,0xc3,0xbd,0x7e},
  {0xff,0xe7,0x17,0xd3,0x2d,0xae,0x2e,0xbe,0xbe,0x2e,0xae,0x2d,0xd3,0x17,0xe7,0xff,0xff,0xff,0xe7,0x9a,0x58,0x65,0x5b,0x93,0x93,0x5b,0x65,0x58,0x9a,0xe7,0xff,0xff}
};

const unsigned char PROGMEM blocks[][16] =
{
  {0,0,0,0,
   0,0,1,0,
   1,0,0,0,
   0,0,0,0},

  {21,20,21,21,
   21,21,21,19,
   21,21,21,20,
   21,19,21,21},

{20,20,0,20,
21,21,20,21,
21,21,21,21,
21,19,21,21},

{21,20,21,21,
21,21,21,21,
21,19,21,21,
19,0,19,19},

{20,1,0,0,
19,0,0,1,
0,0,0,0,
0,1,0,0},

{0,1,0,20,
0,0,0,19,
0,1,0,0,
0,0,0,1},

{1,0,0,0,
0,0,0,1,
20,0,0,0,
19,1,0,0},

{0,1,0,0,
0,0,0,1,
0,0,0,20,
0,1,0,19},

{0,0,0,1,
1,20,20,0,
0,19,19,0,
0,0,1,0},

{0,0,0,1,
26,26,26,26,
29,29,29,29,
0,1,0,0},


{0,35,0,1,
1,25,26,26,
0,28,29,29,
0,0,0,0},

{1,0,36,0,
26,26,27,0,
29,29,30,1,
0,0,0,0},

{0,35,0,0,
0,35,1,0,
1,35,0,0,
0,35,0,1},

{1,0,36,0,
0,0,36,1,
0,1,36,0,
0,0,36,0},

{1,0,0,0,
26,31,0,1,
29,35,0,0,
0,35,0,0},

{0,0,1,0,
0,0,32,26,
1,0,36,29,
0,0,36,0,
},

{16,16,16,0,
15,6,15,0,
1,0,1,0,
0,0,0,0},

{26,26,26,26,
23,23,7,23,
0,1,0,1,
0,0,0,0},

{1,0,1,0,
26,5,26,26,
29,5,29,29,
1,0,1,0}
};

const unsigned char PROGMEM world[][32] =
{
  {2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,2},
  {2,4,5,6,9,9,1,1,7,6,8,7,7,6,5,1,7,1,7,7,6,8,8,6,8,7,8,7,9,6,4,2},
  {2,5,5,7,5,1,5,5,6,5,1,8,6,5,5,8,5,8,9,6,6,1,8,5,6,1,6,7,7,6,6,2},
  {2,7,6,6,5,6,7,5,6,5,6,5,7,8,5,8,8,7,1,6,6,7,7,5,7,6,8,1,8,6,7,2},
  {2,8,7,16,10,19,10,15,5,8,8,1,1,5,5,5,7,5,8,7,6,6,6,6,5,8,9,6,1,8,8,2},
  {4,6,6,14,3,5,6,11,10,15,8,8,1,9,9,5,7,7,1,8,8,8,5,9,8,5,7,6,5,6,8,2},
  {10,10,19,12,4,1,9,17,3,13,5,9,5,8,1,5,6,9,5,8,6,8,1,8,8,9,7,5,8,1,6,2},
  {3,8,6,17,1,1,6,3,2,13,7,8,9,9,5,6,9,7,1,9,7,9,5,8,8,1,7,5,5,1,5,2},
  {2,7,6,8,6,5,9,4,4,11,10,10,10,7,7,7,1,6,8,8,1,1,6,8,9,9,6,9,7,8,7,2},
  {4,5,16,10,10,19,10,10,10,10,10,10,10,5,6,6,1,5,6,9,1,5,6,8,8,8,6,8,7,7,7,2},
  {10,10,12,6,9,6,7,6,5,5,1,6,6,7,7,7,1,9,7,5,1,5,9,9,6,5,7,6,8,8,8,2},
  {3,7,8,7,9,6,8,1,1,6,6,1,8,7,7,6,8,6,7,5,5,8,8,5,6,5,5,7,7,5,7,2},
  {2,8,8,1,1,8,5,6,7,5,5,8,8,5,7,8,6,7,7,9,8,5,8,6,8,5,6,5,9,6,6,2},
  {2,1,6,6,5,1,7,1,5,1,5,1,8,9,7,9,5,8,6,5,5,1,7,9,8,5,1,8,1,1,7,2},
  {2,5,5,8,7,1,8,9,7,7,1,5,6,8,6,6,6,6,8,9,5,5,6,7,1,7,7,7,5,1,7,2},
  {2,7,7,5,8,6,5,8,7,6,9,5,7,6,9,5,8,5,6,8,7,5,9,8,8,5,6,5,9,1,5,2},
  {2,5,6,8,6,5,1,7,5,9,5,8,5,6,1,5,1,1,9,8,8,7,5,9,7,1,7,7,1,6,6,2},
  {2,7,6,6,6,8,6,6,7,6,5,8,6,6,7,9,1,9,7,8,7,8,5,9,8,7,7,8,7,8,1,2},
  {2,8,6,6,5,5,1,8,8,5,8,9,6,1,5,5,7,8,1,1,5,6,5,7,8,6,7,5,6,1,1,2},
  {2,6,7,9,9,8,8,8,7,5,9,9,1,1,1,8,6,7,5,1,1,7,8,6,5,6,6,5,5,6,8,2},
  {2,8,5,7,8,8,1,5,8,1,5,5,5,7,1,9,6,5,7,8,1,7,6,9,6,7,6,1,5,7,8,2},
  {2,6,8,6,6,6,1,8,5,6,6,9,9,8,1,6,9,5,9,9,9,9,9,8,5,6,9,8,9,7,7,2},
  {2,7,1,7,7,9,9,9,9,8,8,5,9,1,7,9,1,8,8,7,1,9,6,7,1,8,9,7,6,7,6,2},
  {2,1,8,1,8,9,8,9,7,9,9,9,6,6,9,7,5,5,6,7,9,8,5,8,7,1,5,9,1,7,5,2},
  {2,5,8,9,5,6,9,8,9,6,5,5,8,1,5,6,9,5,6,7,1,8,7,6,8,6,5,8,1,8,6,2},
  {2,5,5,5,6,9,9,1,6,6,1,8,7,8,5,8,5,6,7,8,8,9,7,6,6,7,8,7,6,6,9,2},
  {2,1,1,6,5,6,6,8,5,9,7,5,1,7,7,8,8,6,1,9,1,6,5,1,8,6,9,9,7,6,5,2},
  {2,9,7,5,5,7,1,8,1,9,5,7,8,6,6,6,1,7,1,9,7,8,7,6,7,1,7,8,5,1,7,2},
  {2,5,5,1,8,5,7,6,6,6,6,1,8,6,9,6,7,6,1,1,1,1,7,6,7,9,1,6,9,5,6,2},
  {2,7,1,6,5,6,5,8,6,5,9,6,9,5,9,5,6,6,6,9,9,9,6,1,5,8,6,9,8,5,8,2},
  {2,3,1,5,9,8,8,5,6,7,6,6,6,8,9,7,9,5,9,9,7,8,6,8,9,7,8,5,1,8,3,2},
  {2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//------------------------
// DOORS
//------------------------

struct Door
{
  char locationMap, locationX, locationY, destinationMap;
  int destinationX, destinationY;
};

const byte DOORSAMOUNT = 1;
const Door doors[DOORSAMOUNT] =
{
  // Door to house
  {0, 13, 29, 1, 4, 258},
};


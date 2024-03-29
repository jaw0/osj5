
// file: font/osr21.bdf
// font: -FreeType-Old Standard TT-Medium-R-Normal--29-290-72-72-P-153-ISO10646-1

#include <font.h>

const struct Font font_osr21 = {
    .type       = 1,
    .name	= "osr21",
    .height	= 29,
    .width	= 32,
    .lineheight = 29,
    .bytescol	= 4,
    .numcol     = 32,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 25, .ncol = 4, .xadj = -24, .pos = 0 }, // 33 [15]
	{ .l0 = 3, .r0 = 22, .ncol = 7, .xadj = -21, .pos = 13 }, // 34 [26]
	{ .l0 = 3, .r0 = 14, .ncol = 15, .xadj = -13, .pos = 22 }, // 35 [55]
	{ .l0 = 3, .r0 = 16, .ncol = 13, .xadj = -15, .pos = 59 }, // 36 [48]
	{ .l0 = 4, .r0 = 9, .ncol = 19, .xadj = -7, .pos = 98 }, // 37 [69]
	{ .l0 = 3, .r0 = 9, .ncol = 20, .xadj = -9, .pos = 139 }, // 38 [73]
	{ .l0 = 3, .r0 = 26, .ncol = 3, .xadj = -25, .pos = 186 }, // 39 [11]
	{ .l0 = 4, .r0 = 22, .ncol = 6, .xadj = -22, .pos = 190 }, // 40 [22]
	{ .l0 = 3, .r0 = 23, .ncol = 6, .xadj = -21, .pos = 203 }, // 41 [22]
	{ .l0 = 3, .r0 = 19, .ncol = 10, .xadj = -18, .pos = 216 }, // 42 [37]
	{ .l0 = 2, .r0 = 6, .ncol = 24, .xadj = -6, .pos = 239 }, // 43 [87]
	{ .l0 = 3, .r0 = 25, .ncol = 4, .xadj = -24, .pos = 267 }, // 44 [15]
	{ .l0 = 3, .r0 = 22, .ncol = 7, .xadj = -21, .pos = 274 }, // 45 [26]
	{ .l0 = 3, .r0 = 25, .ncol = 4, .xadj = -24, .pos = 282 }, // 46 [15]
	{ .l0 = 3, .r0 = 20, .ncol = 9, .xadj = -19, .pos = 287 }, // 47 [33]
	{ .l0 = 2, .r0 = 16, .ncol = 14, .xadj = -15, .pos = 297 }, // 48 [51]
	{ .l0 = 4, .r0 = 18, .ncol = 10, .xadj = -15, .pos = 327 }, // 49 [37]
	{ .l0 = 3, .r0 = 17, .ncol = 12, .xadj = -15, .pos = 348 }, // 50 [44]
	{ .l0 = 3, .r0 = 17, .ncol = 12, .xadj = -15, .pos = 385 }, // 51 [44]
	{ .l0 = 3, .r0 = 15, .ncol = 14, .xadj = -15, .pos = 424 }, // 52 [51]
	{ .l0 = 3, .r0 = 17, .ncol = 12, .xadj = -15, .pos = 457 }, // 53 [44]
	{ .l0 = 3, .r0 = 17, .ncol = 12, .xadj = -15, .pos = 491 }, // 54 [44]
	{ .l0 = 4, .r0 = 17, .ncol = 11, .xadj = -15, .pos = 526 }, // 55 [40]
	{ .l0 = 3, .r0 = 15, .ncol = 14, .xadj = -15, .pos = 548 }, // 56 [51]
	{ .l0 = 3, .r0 = 17, .ncol = 12, .xadj = -15, .pos = 590 }, // 57 [44]
	{ .l0 = 3, .r0 = 25, .ncol = 4, .xadj = -24, .pos = 624 }, // 58 [15]
	{ .l0 = 3, .r0 = 25, .ncol = 4, .xadj = -24, .pos = 633 }, // 59 [15]
	{ .l0 = 3, .r0 = 7, .ncol = 22, .xadj = -5, .pos = 644 }, // 60 [80]
	{ .l0 = 2, .r0 = 6, .ncol = 24, .xadj = -6, .pos = 686 }, // 61 [87]
	{ .l0 = 4, .r0 = 6, .ncol = 22, .xadj = -5, .pos = 735 }, // 62 [80]
	{ .l0 = 3, .r0 = 18, .ncol = 11, .xadj = -18, .pos = 777 }, // 63 [40]
	{ .l0 = 3, .r0 = 8, .ncol = 21, .xadj = -7, .pos = 806 }, // 64 [77]
	{ .l0 = 2, .r0 = 10, .ncol = 20, .xadj = -10, .pos = 873 }, // 65 [73]
	{ .l0 = 3, .r0 = 13, .ncol = 16, .xadj = -12, .pos = 910 }, // 66 [58]
	{ .l0 = 3, .r0 = 14, .ncol = 15, .xadj = -13, .pos = 957 }, // 67 [55]
	{ .l0 = 3, .r0 = 10, .ncol = 19, .xadj = -10, .pos = 990 }, // 68 [69]
	{ .l0 = 3, .r0 = 12, .ncol = 17, .xadj = -12, .pos = 1031 }, // 69 [62]
	{ .l0 = 3, .r0 = 12, .ncol = 17, .xadj = -12, .pos = 1076 }, // 70 [62]
	{ .l0 = 3, .r0 = 11, .ncol = 18, .xadj = -11, .pos = 1112 }, // 71 [66]
	{ .l0 = 3, .r0 = 9, .ncol = 20, .xadj = -9, .pos = 1154 }, // 72 [73]
	{ .l0 = 3, .r0 = 21, .ncol = 8, .xadj = -20, .pos = 1201 }, // 73 [29]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 1221 }, // 74 [48]
	{ .l0 = 3, .r0 = 10, .ncol = 19, .xadj = -10, .pos = 1247 }, // 75 [69]
	{ .l0 = 3, .r0 = 13, .ncol = 16, .xadj = -12, .pos = 1294 }, // 76 [58]
	{ .l0 = 3, .r0 = 8, .ncol = 21, .xadj = -7, .pos = 1324 }, // 77 [77]
	{ .l0 = 3, .r0 = 9, .ncol = 20, .xadj = -9, .pos = 1369 }, // 78 [73]
	{ .l0 = 3, .r0 = 12, .ncol = 17, .xadj = -12, .pos = 1403 }, // 79 [62]
	{ .l0 = 3, .r0 = 12, .ncol = 17, .xadj = -12, .pos = 1438 }, // 80 [62]
	{ .l0 = 3, .r0 = 12, .ncol = 17, .xadj = -12, .pos = 1477 }, // 81 [62]
	{ .l0 = 3, .r0 = 11, .ncol = 18, .xadj = -11, .pos = 1520 }, // 82 [66]
	{ .l0 = 4, .r0 = 14, .ncol = 14, .xadj = -14, .pos = 1565 }, // 83 [51]
	{ .l0 = 3, .r0 = 12, .ncol = 17, .xadj = -11, .pos = 1604 }, // 84 [62]
	{ .l0 = 3, .r0 = 9, .ncol = 20, .xadj = -9, .pos = 1636 }, // 85 [73]
	{ .l0 = 3, .r0 = 9, .ncol = 20, .xadj = -9, .pos = 1670 }, // 86 [73]
	{ .l0 = 3, .r0 = 0, .ncol = 29, .xadj = 0, .pos = 1702 }, // 87 [106]
	{ .l0 = 3, .r0 = 10, .ncol = 19, .xadj = -10, .pos = 1752 }, // 88 [69]
	{ .l0 = 2, .r0 = 11, .ncol = 19, .xadj = -11, .pos = 1798 }, // 89 [69]
	{ .l0 = 3, .r0 = 14, .ncol = 15, .xadj = -13, .pos = 1832 }, // 90 [55]
	{ .l0 = 4, .r0 = 22, .ncol = 6, .xadj = -21, .pos = 1871 }, // 91 [22]
	{ .l0 = 3, .r0 = 20, .ncol = 9, .xadj = -19, .pos = 1890 }, // 92 [33]
	{ .l0 = 3, .r0 = 23, .ncol = 6, .xadj = -21, .pos = 1900 }, // 93 [22]
	{ .l0 = 3, .r0 = 16, .ncol = 13, .xadj = -15, .pos = 1919 }, // 94 [48]
	{ .l0 = 1, .r0 = 16, .ncol = 15, .xadj = -17, .pos = 1933 }, // 95 [55]
	{ .l0 = 3, .r0 = 24, .ncol = 5, .xadj = -19, .pos = 1949 }, // 96 [19]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 1955 }, // 97 [48]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 1983 }, // 98 [48]
	{ .l0 = 2, .r0 = 20, .ncol = 10, .xadj = -20, .pos = 2010 }, // 99 [37]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 2032 }, // 100 [48]
	{ .l0 = 2, .r0 = 20, .ncol = 10, .xadj = -19, .pos = 2061 }, // 101 [37]
	{ .l0 = 2, .r0 = 20, .ncol = 10, .xadj = -22, .pos = 2086 }, // 102 [37]
	{ .l0 = 3, .r0 = 15, .ncol = 14, .xadj = -16, .pos = 2110 }, // 103 [51]
	{ .l0 = 2, .r0 = 16, .ncol = 14, .xadj = -16, .pos = 2160 }, // 104 [51]
	{ .l0 = 2, .r0 = 24, .ncol = 6, .xadj = -25, .pos = 2188 }, // 105 [22]
	{ .l0 = 0, .r0 = 24, .ncol = 8, .xadj = -23, .pos = 2202 }, // 106 [29]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 2223 }, // 107 [48]
	{ .l0 = 2, .r0 = 23, .ncol = 7, .xadj = -24, .pos = 2254 }, // 108 [26]
	{ .l0 = 2, .r0 = 9, .ncol = 21, .xadj = -9, .pos = 2270 }, // 109 [77]
	{ .l0 = 2, .r0 = 16, .ncol = 14, .xadj = -16, .pos = 2308 }, // 110 [51]
	{ .l0 = 2, .r0 = 18, .ncol = 12, .xadj = -18, .pos = 2333 }, // 111 [44]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 2356 }, // 112 [48]
	{ .l0 = 2, .r0 = 17, .ncol = 13, .xadj = -17, .pos = 2386 }, // 113 [48]
	{ .l0 = 2, .r0 = 20, .ncol = 10, .xadj = -20, .pos = 2415 }, // 114 [37]
	{ .l0 = 3, .r0 = 19, .ncol = 10, .xadj = -19, .pos = 2433 }, // 115 [37]
	{ .l0 = 2, .r0 = 22, .ncol = 8, .xadj = -22, .pos = 2461 }, // 116 [29]
	{ .l0 = 2, .r0 = 16, .ncol = 14, .xadj = -16, .pos = 2477 }, // 117 [51]
	{ .l0 = 1, .r0 = 16, .ncol = 15, .xadj = -17, .pos = 2499 }, // 118 [55]
	{ .l0 = 1, .r0 = 9, .ncol = 22, .xadj = -10, .pos = 2519 }, // 119 [80]
	{ .l0 = 2, .r0 = 16, .ncol = 14, .xadj = -16, .pos = 2550 }, // 120 [51]
	{ .l0 = 1, .r0 = 16, .ncol = 15, .xadj = -17, .pos = 2580 }, // 121 [55]
	{ .l0 = 2, .r0 = 20, .ncol = 10, .xadj = -19, .pos = 2607 }, // 122 [37]
	{ .l0 = 4, .r0 = 22, .ncol = 6, .xadj = -20, .pos = 2632 }, // 123 [22]
	{ .l0 = 5, .r0 = 26, .ncol = 1, .xadj = -24, .pos = 2649 }, // 124 [4]
	{ .l0 = 4, .r0 = 22, .ncol = 6, .xadj = -20, .pos = 2654 }, // 125 [22]
	{ .l0 = 2, .r0 = 14, .ncol = 16, .xadj = -14, .pos = 2670 }, // 126 [58]
	{ .l0 = 32, .r0 = 0, .ncol = 0, .xadj = -32, .pos = 2689 }, // 127 [0]
    },
    .data       = {
	0x15, 0x62, 0x4f, 0x7, 0x2, 0xc, 0x47, 0x7, 0x1, 0x14, 0x4d, 0x62, 0x60,	// 33
	0x4, 0xcd, 0xc1, 0xf8, 0xd4, 0xcd, 0xc1, 0xf8, 0x10,	// 34
	0x39, 0x39, 0xa1, 0x39, 0xa1, 0x39, 0xa1, 0x3f, 0x71, 0xf, 0x2, 0x6f, 0x2, 0x21, 0x73, 0x19, 0x39, 0xa1, 0x39, 0xa1, 0x39, 0x14, 0x71, 0x27, 0x1, 0x77, 0x2, 0x9, 0x77, 0x39, 0xa1, 0x39, 0xa1, 0x39, 0xa1, 0x39, 0x90,	// 35
	0x8b, 0x75, 0x36, 0x52, 0x23, 0x23, 0x19, 0x49, 0x2b, 0x51, 0x41, 0x3b, 0x49, 0x37, 0x7, 0x7, 0x4, 0x31, 0x43, 0x49, 0x2f, 0x7, 0x7, 0x4, 0x31, 0x4b, 0x39, 0x49, 0x43, 0x39, 0x49, 0x1b, 0x1b, 0x22, 0x5e, 0x27, 0x6c, 0x3c, 0x80,	// 36
	0x25, 0xb7, 0x2, 0x99, 0x42, 0x91, 0x49, 0x91, 0x49, 0x42, 0x42, 0x39, 0x3a, 0x5f, 0x2, 0x2a, 0x7d, 0x2a, 0xd1, 0xd2, 0xca, 0xca, 0x35, 0x72, 0x37, 0x1, 0x61, 0x41, 0x39, 0x4a, 0x41, 0x41, 0x41, 0x51, 0x41, 0xa1, 0x39, 0xa7, 0x1, 0xbd, 0x50,	// 37
	0x84, 0xbf, 0xaf, 0x2, 0x5c, 0x22, 0x39, 0x4f, 0x1, 0xa, 0x41, 0x49, 0x25, 0x91, 0x3d, 0x39, 0x41, 0x3e, 0x31, 0x41, 0x31, 0x1d, 0x21, 0x49, 0x1a, 0x2d, 0x19, 0x54, 0x46, 0xc5, 0x91, 0x34, 0x91, 0x2a, 0xb, 0x89, 0x1a, 0x29, 0x8c, 0xca, 0x49, 0x89, 0x51, 0x89, 0x49, 0x91, 0xb0,	// 38
	0x4, 0xcd, 0xc1, 0xe8,	// 39
	0x4f, 0x4, 0x7b, 0x53, 0x5a, 0x82, 0x3a, 0xa2, 0x22, 0xb2, 0x12, 0xc9, 0x18,	// 40
	0x2, 0xc2, 0x12, 0xb2, 0x2a, 0x93, 0x3b, 0x73, 0x5c, 0x44, 0x8f, 0x2, 0x60,	// 41
	0x1a, 0x1a, 0xb3, 0x12, 0xba, 0x11, 0xc9, 0x9, 0xb3, 0x12, 0x13, 0x8f, 0x5, 0x91, 0x1a, 0x19, 0xb1, 0x11, 0xc2, 0x12, 0xb3, 0x12, 0xc8,	// 42
	0x69, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x87, 0x7, 0x7, 0x4, 0x81, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x78,	// 43
	0x9b, 0xd3, 0x21, 0xab, 0x19, 0xbd, 0x40,	// 44
	0x6a, 0xda, 0xda, 0xda, 0xda, 0xda, 0xda, 0x98,	// 45
	0x9a, 0xd4, 0xcc, 0xd2, 0x60,	// 46
	0xcb, 0xbc, 0xb3, 0xb4, 0xb4, 0xb4, 0xb4, 0xac, 0xbb, 0xe8,	// 47
	0x47, 0x1, 0x97, 0x7, 0x6f, 0x7, 0x3, 0x5a, 0x7a, 0x51, 0x91, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x49, 0x8a, 0x52, 0x6b, 0x67, 0x7, 0x1, 0x87, 0x5, 0xb2, 0x90,	// 48
	0x29, 0x79, 0x61, 0x79, 0x61, 0x79, 0x61, 0x79, 0x5f, 0x7, 0x4, 0x4f, 0x7, 0x6, 0x47, 0x7, 0x7, 0xe1, 0xe1, 0xe1, 0x68,	// 49
	0x24, 0x5b, 0x51, 0x13, 0x45, 0x49, 0x23, 0x32, 0xb, 0x41, 0x2a, 0x32, 0x1a, 0x41, 0x62, 0x22, 0x41, 0x5a, 0x2a, 0x41, 0x59, 0x32, 0x41, 0x51, 0x3a, 0x49, 0x3a, 0x42, 0x4f, 0x3, 0x3b, 0x57, 0x1, 0x43, 0x5d, 0x3e, 0x58,	// 50
	0x1b, 0x5c, 0x55, 0x4e, 0x49, 0xb, 0x1a, 0x23, 0x11, 0x41, 0x1a, 0x1a, 0x2a, 0x11, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x42, 0x41, 0x49, 0x4a, 0x2a, 0x9, 0x3a, 0x4f, 0x2, 0xf, 0x2, 0x5f, 0x1f, 0x79, 0x3d, 0x70,	// 51
	0x72, 0xd3, 0xc2, 0x11, 0xba, 0x19, 0xaa, 0x29, 0x29, 0x6b, 0x31, 0x29, 0x62, 0x41, 0x29, 0x57, 0x7, 0x5, 0x4f, 0x7, 0x6, 0x47, 0x7, 0x7, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0x48,	// 52
	0x84, 0x57, 0x4, 0x1e, 0x4b, 0x29, 0x2c, 0x11, 0x4a, 0x21, 0x3a, 0x19, 0x4a, 0x21, 0x61, 0x4a, 0x21, 0x61, 0x4a, 0x21, 0x61, 0x4a, 0x21, 0x61, 0x49, 0x31, 0x4b, 0x41, 0x3f, 0x5, 0x97, 0x3, 0xae, 0x78,	// 53
	0x47, 0x2, 0x8f, 0x7, 0x1, 0x6f, 0x7, 0x3, 0x53, 0x32, 0x33, 0x49, 0x39, 0x51, 0x41, 0x39, 0x59, 0x41, 0x39, 0x59, 0x41, 0x39, 0x59, 0x41, 0x13, 0x12, 0x4a, 0x4d, 0x1f, 0x4, 0x5b, 0x2f, 0x2, 0xb5, 0x78,	// 54
	0xe, 0xbb, 0xd2, 0xda, 0x75, 0x42, 0x5f, 0x1, 0x42, 0x4f, 0x3, 0x42, 0x43, 0x1d, 0x42, 0x32, 0x9a, 0x29, 0xaa, 0x13, 0xb4, 0xc8,	// 55
	0x25, 0x2d, 0x6f, 0x1f, 0x1, 0x57, 0x2, 0xf, 0x2, 0x51, 0x2b, 0x9, 0x3a, 0x41, 0x3b, 0x49, 0x41, 0x3b, 0x49, 0x41, 0x43, 0x41, 0x41, 0x43, 0x41, 0x41, 0x44, 0x39, 0x49, 0x3c, 0x39, 0x4a, 0x29, 0xc, 0x29, 0x5e, 0x1f, 0x2, 0x64, 0x2f, 0xc2, 0x70,	// 56
	0x2d, 0xb7, 0x2, 0x2c, 0x57, 0x4, 0x1e, 0x49, 0x49, 0x1b, 0x11, 0x41, 0x59, 0x39, 0x41, 0x59, 0x39, 0x41, 0x59, 0x39, 0x41, 0x51, 0x41, 0x49, 0x42, 0x32, 0x5f, 0x2, 0x24, 0x6f, 0x7, 0x97, 0x1, 0x90,	// 57
	0x4a, 0x42, 0x84, 0x34, 0x7c, 0x34, 0x82, 0x42, 0x60,	// 58
	0x52, 0x3b, 0x84, 0x33, 0x21, 0x5c, 0x33, 0x12, 0x6a, 0x45, 0x40,	// 59
	0x72, 0xda, 0xd4, 0xc9, 0x11, 0xc2, 0x19, 0xb9, 0x22, 0xaa, 0x29, 0xa9, 0x32, 0x99, 0x41, 0x92, 0x42, 0x89, 0x51, 0x82, 0x52, 0x79, 0x61, 0x72, 0x69, 0x69, 0x72, 0x5a, 0x79, 0x59, 0x82, 0x49, 0x91, 0x42, 0x92, 0x39, 0xa1, 0x32, 0xa2, 0x29, 0xb1, 0x20,	// 60
	0x51, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0xb1, 0x29, 0x60,	// 61
	0x19, 0xb1, 0x2a, 0xa2, 0x31, 0xa1, 0x3a, 0x92, 0x41, 0x91, 0x51, 0x82, 0x52, 0x79, 0x61, 0x72, 0x62, 0x69, 0x71, 0x61, 0x7a, 0x52, 0x81, 0x51, 0x8a, 0x42, 0x91, 0x41, 0xa1, 0x32, 0xa1, 0x31, 0xb1, 0x22, 0xb2, 0x19, 0xc1, 0x11, 0xcc, 0xd2, 0xda, 0x78,	// 62
	0x1c, 0xc1, 0x13, 0xb9, 0x13, 0xb1, 0x1a, 0x33, 0x1a, 0x49, 0x4a, 0x19, 0xc, 0x41, 0x42, 0x21, 0xc, 0x41, 0x3a, 0x29, 0x12, 0x51, 0x23, 0x1b, 0x7f, 0x1, 0xb5, 0xd1, 0xc0,	// 63
	0x3f, 0x1, 0x9a, 0x42, 0x7a, 0x61, 0x6a, 0x71, 0x5a, 0x3d, 0x21, 0x51, 0x37, 0x1, 0x21, 0x41, 0x37, 0x3, 0x19, 0x41, 0x2b, 0x39, 0x19, 0x41, 0x22, 0x49, 0x19, 0x41, 0x21, 0x51, 0x19, 0x41, 0x19, 0x51, 0x69, 0x19, 0x42, 0x29, 0x41, 0x19, 0x2e, 0x21, 0x41, 0x27, 0x5, 0x19, 0x41, 0x1f, 0x1, 0x21, 0x19, 0x41, 0x1c, 0x41, 0x11, 0x51, 0x11, 0x59, 0x11, 0x59, 0x61, 0x81, 0x51, 0x92, 0x32, 0xae, 0xc0,	// 64
	0xa9, 0xe1, 0xe1, 0xd3, 0xbe, 0xa5, 0x19, 0x8e, 0x29, 0x7c, 0x19, 0x29, 0x63, 0x39, 0x7d, 0x41, 0x77, 0x2, 0x29, 0x8f, 0x2, 0x11, 0x29, 0x77, 0x2, 0x29, 0x8f, 0x2, 0x11, 0xa7, 0x2, 0xbe, 0xd3, 0xe1, 0xe1, 0xe1, 0x58,	// 65
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x42, 0x49, 0x49, 0x31, 0x9, 0x41, 0x57, 0x1, 0xf, 0x3, 0x5e, 0x1f, 0x1, 0x6c, 0x35, 0x50,	// 66
	0x37, 0x1, 0x9f, 0x6, 0x77, 0x7, 0x3, 0x5a, 0x7a, 0x49, 0x91, 0x49, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x42, 0x91, 0x4a, 0x89, 0x52, 0x72, 0x56, 0x4b, 0x57, 0x1, 0x2b, 0x90,	// 67
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x49, 0x89, 0x52, 0x7a, 0x5c, 0x4c, 0x6f, 0x7, 0x8f, 0x4, 0xb3, 0x88,	// 68
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x43, 0x41, 0x41, 0x2f, 0x2, 0x29, 0x41, 0x99, 0x41, 0x99, 0x41, 0x92, 0x43, 0x7b, 0x45, 0x5d, 0x47, 0x37, 0x1, 0x50,	// 69
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x43, 0x89, 0x2f, 0x2, 0x71, 0xe1, 0xe1, 0xe3, 0xd5, 0xc7, 0xc0,	// 70
	0x37, 0x2, 0x97, 0x6, 0x77, 0x7, 0x3, 0x5a, 0x7a, 0x4a, 0x91, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x49, 0x49, 0x41, 0x49, 0x42, 0x49, 0x41, 0x3a, 0x53, 0x37, 0x2, 0x64, 0x27, 0x1, 0x5f, 0x1, 0x17, 0x4, 0x91, 0xe1, 0xe1, 0xc0,	// 71
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x89, 0xe1, 0xe1, 0xe1, 0x99, 0x41, 0x51, 0x41, 0x41, 0x51, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x58,	// 72
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x99, 0x41, 0x99, 0x38,	// 73
	0x8b, 0xce, 0xbb, 0x11, 0xbb, 0x11, 0xe1, 0x41, 0x99, 0x41, 0x99, 0x41, 0x92, 0x47, 0x7, 0x6, 0x4f, 0x7, 0x5, 0x57, 0x7, 0x2, 0x69, 0xe1, 0xf8, 0x18,	// 74
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x49, 0x49, 0x41, 0x41, 0x51, 0x83, 0xce, 0xb1, 0x15, 0x31, 0x41, 0x21, 0x2d, 0x21, 0x41, 0x12, 0x45, 0x11, 0x44, 0x57, 0x43, 0x6d, 0x42, 0x83, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x40,	// 75
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0xe1, 0xe1, 0xe1, 0xda, 0xda, 0xcc, 0xaf, 0x1, 0x38,	// 76
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x44, 0x81, 0x47, 0x69, 0x4f, 0x2, 0x51, 0x6f, 0x1, 0xc7, 0x2, 0xbf, 0x2, 0xc6, 0xb4, 0xb3, 0xb4, 0x49, 0x5c, 0x69, 0x43, 0x89, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x99, 0x41, 0x99, 0x70,	// 77
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x44, 0x81, 0x45, 0x79, 0x55, 0x69, 0x5d, 0xd5, 0xcd, 0xd5, 0xce, 0xcd, 0x69, 0x65, 0x59, 0x6d, 0x51, 0x7d, 0x47, 0x7, 0x7, 0x41, 0xe1, 0xe1, 0xf8,	// 78
	0x47, 0x9f, 0x6, 0x7f, 0x7, 0x1, 0x63, 0x6b, 0x51, 0x89, 0x49, 0x99, 0x41, 0x99, 0x41, 0x99, 0x39, 0xa1, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x4a, 0x7a, 0x5b, 0x5b, 0x6f, 0x7, 0x1, 0x87, 0x4, 0xba, 0x98,	// 79
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x49, 0x49, 0x41, 0x49, 0x91, 0x49, 0x91, 0x49, 0x92, 0x39, 0xa2, 0x2a, 0xa7, 0x1, 0xb6, 0xd1, 0xc8,	// 80
	0x47, 0x9f, 0x6, 0x7f, 0x7, 0x1, 0x63, 0x6a, 0x59, 0x82, 0x49, 0x92, 0x41, 0x84, 0x41, 0x7a, 0x11, 0x39, 0x81, 0x21, 0x39, 0x79, 0x21, 0x39, 0x87, 0x29, 0x8f, 0x2a, 0x7a, 0x1b, 0x2b, 0x5c, 0x22, 0x37, 0x7, 0x1, 0x32, 0x47, 0x4, 0x2c, 0x72, 0x41, 0x50,	// 81
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x99, 0x41, 0x99, 0x43, 0x8a, 0x31, 0xf, 0x2, 0x5f, 0x1, 0x1f, 0x1, 0x57, 0x3e, 0x5c, 0x62, 0xda, 0xc3, 0x78,	// 82
	0x16, 0x27, 0x2, 0x4f, 0x1, 0x3b, 0x52, 0x24, 0x3a, 0x51, 0x34, 0x41, 0x49, 0x3b, 0x49, 0x41, 0x3c, 0x41, 0x41, 0x43, 0x41, 0x41, 0x43, 0x8a, 0x3c, 0x39, 0x4a, 0x3b, 0x39, 0x52, 0x34, 0x31, 0x47, 0x1, 0x1c, 0x21, 0xaf, 0xc4, 0x68,	// 83
	0xf, 0x1, 0xad, 0xc2, 0xd9, 0xe1, 0x99, 0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0xe2, 0xdc, 0xcf, 0x1, 0xb8,	// 84
	0x9, 0xe1, 0xe1, 0xe7, 0x7, 0x3, 0x67, 0x7, 0x5, 0x57, 0x7, 0x6, 0x49, 0x92, 0x41, 0x99, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x41, 0x99, 0x41, 0x91, 0x49, 0x89, 0x57, 0x7, 0x4, 0x59, 0xe1, 0xe1, 0xf8,	// 85
	0x9, 0xe1, 0xe1, 0xe3, 0xd6, 0xbf, 0x2, 0xa1, 0x17, 0x2, 0x89, 0x2f, 0x2, 0x71, 0x47, 0x1, 0xc7, 0x1, 0xc7, 0xbc, 0x49, 0x63, 0x69, 0x44, 0x81, 0x2c, 0x9f, 0xb4, 0xca, 0xd9, 0xe1, 0xf8,	// 86
	0x9, 0xe1, 0xe1, 0xe4, 0xcf, 0xb7, 0x4, 0x91, 0x27, 0x2, 0x79, 0x3f, 0x3, 0xbf, 0x3, 0xb6, 0x41, 0x64, 0x61, 0x45, 0x79, 0x25, 0x9e, 0xbf, 0xb7, 0x4, 0x91, 0x1f, 0x3, 0x79, 0x3f, 0x3, 0x59, 0x57, 0x3, 0xbf, 0xac, 0x59, 0x54, 0x71, 0x3c, 0x89, 0x24, 0xa6, 0xba, 0xd9, 0xe1, 0xe1, 0xf8, 0x18,	// 87
	0x9, 0x99, 0x41, 0x99, 0x41, 0x99, 0x41, 0x8b, 0x43, 0x74, 0x45, 0x52, 0x19, 0x47, 0x3a, 0x21, 0x41, 0x16, 0x1a, 0x31, 0x41, 0x25, 0xa, 0xb6, 0xce, 0x79, 0x2a, 0x16, 0x21, 0x41, 0x1a, 0x36, 0x11, 0x45, 0x4f, 0x43, 0x6d, 0x42, 0x83, 0x41, 0x99, 0x41, 0x99, 0x41, 0x99, 0x40,	// 88
	0x9, 0xe1, 0xe1, 0xe2, 0xdc, 0xce, 0x71, 0x47, 0x69, 0x41, 0x1d, 0x59, 0x41, 0x2d, 0x49, 0x7f, 0x7, 0x8f, 0x5, 0x8f, 0x5, 0x41, 0x32, 0x59, 0x41, 0x22, 0x69, 0x45, 0x79, 0x43, 0xd2, 0xd9, 0xe1, 0xe0,	// 89
	0xa2, 0x55, 0x5b, 0x44, 0x65, 0x43, 0x66, 0x42, 0x5d, 0x11, 0x41, 0x56, 0x19, 0x41, 0x4d, 0x29, 0x41, 0x3d, 0x39, 0x41, 0x2e, 0x41, 0x41, 0x25, 0x51, 0x41, 0x15, 0x61, 0x41, 0xd, 0x69, 0x45, 0x72, 0x43, 0x74, 0x42, 0x5f, 0x1, 0x60,	// 90
	0xf, 0x7, 0x7, 0x6, 0x17, 0x7, 0x7, 0x6, 0x17, 0x7, 0x7, 0x6, 0x11, 0xc9, 0x11, 0xc9, 0x11, 0xc9, 0x18,	// 91
	0x3, 0xe4, 0xeb, 0xec, 0xe4, 0xe4, 0xeb, 0xec, 0xe3, 0x20,	// 92
	0x9, 0xc9, 0x11, 0xc9, 0x11, 0xc9, 0x17, 0x7, 0x7, 0x6, 0x17, 0x7, 0x7, 0x6, 0x17, 0x7, 0x7, 0x6, 0x18,	// 93
	0x59, 0xd3, 0xca, 0xca, 0xcb, 0xca, 0xca, 0xea, 0xe3, 0xe2, 0xea, 0xe3, 0xe1, 0xc0,	// 94
	0xd1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x38,	// 95
	0xa, 0xdb, 0xdb, 0xe1, 0xe9, 0xf0,	// 96
	0x8c, 0x93, 0x1d, 0x8c, 0x17, 0x79, 0x12, 0x11, 0x29, 0x79, 0x29, 0x31, 0x79, 0x29, 0x31, 0x79, 0x29, 0x29, 0x87, 0x5, 0x97, 0x6, 0x8f, 0x5, 0xe1, 0xda, 0xcb, 0x78,	// 97
	0x9, 0xe1, 0xe7, 0x7, 0x7, 0x47, 0x7, 0x5, 0x57, 0x7, 0x5, 0x91, 0x51, 0x81, 0x61, 0x79, 0x61, 0x79, 0x61, 0x7a, 0x52, 0x87, 0x5, 0x97, 0x3, 0xba, 0xa0,	// 98
	0x66, 0xaf, 0x3, 0x97, 0x5, 0x82, 0x52, 0x79, 0x61, 0x79, 0x61, 0x79, 0x61, 0x79, 0x19, 0x41, 0x81, 0xb, 0x2a, 0x93, 0x29, 0x80,	// 99
	0x66, 0xaf, 0x3, 0x97, 0x5, 0x82, 0x52, 0x79, 0x61, 0x79, 0x61, 0x41, 0x31, 0x61, 0x41, 0x3a, 0x49, 0x4f, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0xe1, 0xe1, 0x70,	// 100
	0x66, 0xaf, 0x3, 0x97, 0x5, 0x82, 0x21, 0x2a, 0x79, 0x29, 0x31, 0x79, 0x29, 0x31, 0x79, 0x29, 0x31, 0x82, 0x19, 0x31, 0x86, 0x29, 0x9c, 0x13, 0x78,	// 101
	0x41, 0x61, 0x79, 0x61, 0x57, 0x7, 0x5, 0x4f, 0x7, 0x6, 0x47, 0x7, 0x7, 0x41, 0x31, 0x61, 0x41, 0x31, 0x61, 0x41, 0xa, 0xd3, 0xd9, 0xf8,	// 102
	0x5c, 0x22, 0x1b, 0x5f, 0x11, 0xa, 0x9, 0x19, 0x57, 0x1, 0x9, 0xb, 0x29, 0x42, 0x32, 0x1a, 0x29, 0x41, 0x41, 0x1a, 0x29, 0x41, 0x41, 0x19, 0x31, 0x41, 0x41, 0x19, 0x31, 0x42, 0x32, 0x19, 0x31, 0x4f, 0x1, 0x21, 0x31, 0x4f, 0x2a, 0x21, 0x49, 0x14, 0x32, 0x1a, 0x49, 0xa, 0x55, 0x54, 0xd9, 0xa0,	// 103
	0x9, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x82, 0x51, 0x81, 0xd9, 0xe1, 0x61, 0x7f, 0x7, 0x87, 0x6, 0x8f, 0x5, 0xe1, 0xe1, 0x48,	// 104
	0x41, 0x61, 0x43, 0x27, 0x7, 0x43, 0x27, 0x7, 0x43, 0x27, 0x7, 0xe1, 0xe1, 0x48,	// 105
	0xcb, 0xcd, 0xc9, 0x11, 0x41, 0x99, 0x41, 0x92, 0xb, 0x27, 0x7, 0x6, 0x13, 0x27, 0x7, 0x5, 0x21, 0x2f, 0x7, 0x2, 0x28,	// 106
	0x9, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0xaa, 0x29, 0xa4, 0xa1, 0x12, 0xc, 0x19, 0x7b, 0x2e, 0x7a, 0x3d, 0x79, 0x53, 0x79, 0x61, 0x79, 0x61, 0x70,	// 107
	0x9, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0xe1, 0xe1, 0x60,	// 108
	0x41, 0x61, 0x79, 0x61, 0x7f, 0x7, 0x7f, 0x7, 0x7f, 0x7, 0x82, 0x51, 0x81, 0xd9, 0xe1, 0x61, 0x7f, 0x7, 0x87, 0x6, 0x8f, 0x5, 0x8a, 0x49, 0x81, 0x59, 0x79, 0xe1, 0x61, 0x7a, 0x59, 0x7f, 0x7, 0x87, 0x6, 0xe1, 0xe1, 0x70,	// 109
	0x41, 0x61, 0x79, 0x61, 0x7f, 0x7, 0x7f, 0x7, 0x7f, 0x7, 0x82, 0x51, 0x81, 0xd9, 0xe1, 0x61, 0x7f, 0x7, 0x87, 0x6, 0x8f, 0x5, 0xe1, 0xe1, 0x48,	// 110
	0x66, 0xaf, 0x3, 0x97, 0x5, 0x89, 0x51, 0x81, 0x61, 0x79, 0x61, 0x79, 0x61, 0x79, 0x61, 0x82, 0x42, 0x97, 0x3, 0xa7, 0x1, 0xc2, 0x88,	// 111
	0x41, 0x99, 0x41, 0x99, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x47, 0x7, 0x7, 0x49, 0x51, 0x39, 0x41, 0x61, 0x79, 0x61, 0x79, 0x61, 0x7a, 0x52, 0x87, 0x5, 0x97, 0x3, 0xba, 0xa0,	// 112
	0x66, 0xaf, 0x3, 0x97, 0x5, 0x82, 0x52, 0x79, 0x61, 0x79, 0x61, 0x79, 0x61, 0x31, 0x49, 0x51, 0x39, 0x57, 0x7, 0x5, 0x57, 0x7, 0x5, 0x47, 0x7, 0x7, 0xe1, 0xe1, 0x38,	// 113
	0x41, 0x61, 0x79, 0x61, 0x7f, 0x7, 0x7f, 0x7, 0x7f, 0x7, 0x8a, 0x49, 0x81, 0xd9, 0xe1, 0xa, 0xd3, 0xb8,	// 114
	0x4d, 0x16, 0x81, 0x12, 0x22, 0x89, 0x22, 0x29, 0x81, 0x22, 0x31, 0x79, 0x2a, 0x29, 0x79, 0x2a, 0x29, 0x81, 0x23, 0x21, 0x82, 0x22, 0x21, 0x7d, 0x13, 0x11, 0xc4, 0x78,	// 115
	0x41, 0xe1, 0xd7, 0x7, 0x1, 0x57, 0x7, 0x6, 0x79, 0x5a, 0x79, 0x61, 0x79, 0x5a, 0xc4, 0x40,	// 116
	0x41, 0xe1, 0xe7, 0x5, 0x8f, 0x6, 0x87, 0x7, 0xe1, 0xe1, 0xd9, 0x81, 0x51, 0x8f, 0x7, 0x7f, 0x7, 0x7f, 0x7, 0xe1, 0xe1, 0x48,	// 117
	0x41, 0xe1, 0xe2, 0xdc, 0xce, 0xb9, 0x16, 0xa1, 0x2d, 0xd6, 0xcb, 0x81, 0x33, 0x99, 0x1b, 0xb4, 0xc9, 0xe1, 0xe1, 0xc8,	// 118
	0x41, 0xe1, 0xe2, 0xdc, 0xce, 0xb9, 0x16, 0xa1, 0x2d, 0xd6, 0x79, 0x44, 0x81, 0x2b, 0xa6, 0xbe, 0xbf, 0x1, 0xa9, 0x26, 0xd6, 0xcb, 0x81, 0x33, 0x99, 0x1b, 0xb4, 0xc9, 0xe1, 0xe1, 0xb0,	// 119
	0xa9, 0x79, 0x61, 0x7a, 0x59, 0x7b, 0x43, 0x7d, 0x29, 0x11, 0x79, 0x14, 0xa, 0xbc, 0xd5, 0x19, 0x79, 0x12, 0x15, 0x9, 0x7b, 0x35, 0x7a, 0x4b, 0x79, 0x61, 0x79, 0x61, 0xe1, 0x48,	// 120
	0x41, 0xe1, 0x83, 0x49, 0x84, 0x44, 0x71, 0x9, 0x47, 0x69, 0x41, 0x17, 0x49, 0x49, 0x2f, 0x22, 0xa7, 0xb4, 0x79, 0x33, 0x99, 0x1b, 0xb4, 0xc9, 0xe1, 0xe1, 0xc8,	// 121
	0x45, 0x3a, 0x7a, 0x4b, 0x79, 0x45, 0x79, 0x35, 0x9, 0x79, 0x2c, 0x19, 0x79, 0x1c, 0x29, 0x79, 0x14, 0x31, 0x7d, 0x41, 0x7b, 0x4a, 0x7a, 0x3d, 0x68,	// 122
	0x71, 0xe1, 0x8e, 0x21, 0x9, 0x26, 0x2f, 0x5, 0xf, 0x5, 0x1a, 0x2c, 0x2c, 0x31, 0x11, 0xc9, 0x18,	// 123
	0x7, 0x7, 0x7, 0x7, 0x20,	// 124
	0x9, 0xc9, 0x19, 0x26, 0x1e, 0x22, 0x1f, 0x5, 0xf, 0x5, 0x34, 0x32, 0x2c, 0x91, 0xe1, 0x80,	// 125
	0x6b, 0xc9, 0x19, 0xba, 0xda, 0xdb, 0xda, 0xdb, 0xda, 0xdb, 0xd3, 0xdb, 0xd3, 0xda, 0xda, 0xb9, 0x1a, 0xc4, 0x68,	// 126
	0x0,	// 127

    }
};

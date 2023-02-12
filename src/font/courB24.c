
// file: font/courB24.bdf
// font: -Adobe-Courier-Bold-R-Normal--24-240-75-75-M-150-ISO10646-1

#include <font.h>

const struct Font font_courB24 = {
    .type       = 1,
    .name	= "courB24",
    .height	= 21,
    .width	= 16,
    .bytescol	= 4,
    .numcol     = 16,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 5, .r0 = 7, .ncol = 4, .xadj = -1, .pos = 0 }, // 33 [11]
	{ .l0 = 3, .r0 = 5, .ncol = 8, .xadj = -1, .pos = 11 }, // 34 [21]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 32 }, // 35 [32]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 64 }, // 36 [27]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 91 }, // 37 [27]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 118 }, // 38 [29]
	{ .l0 = 5, .r0 = 8, .ncol = 3, .xadj = -1, .pos = 147 }, // 39 [8]
	{ .l0 = 6, .r0 = 5, .ncol = 5, .xadj = -1, .pos = 155 }, // 40 [14]
	{ .l0 = 3, .r0 = 8, .ncol = 5, .xadj = -1, .pos = 169 }, // 41 [14]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 183 }, // 42 [27]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 210 }, // 43 [32]
	{ .l0 = 4, .r0 = 7, .ncol = 5, .xadj = -1, .pos = 242 }, // 44 [14]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 256 }, // 45 [29]
	{ .l0 = 5, .r0 = 8, .ncol = 3, .xadj = -1, .pos = 285 }, // 46 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 293 }, // 47 [29]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 322 }, // 48 [27]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 349 }, // 49 [27]
	{ .l0 = 1, .r0 = 4, .ncol = 11, .xadj = -1, .pos = 376 }, // 50 [29]
	{ .l0 = 1, .r0 = 4, .ncol = 11, .xadj = -1, .pos = 405 }, // 51 [29]
	{ .l0 = 1, .r0 = 4, .ncol = 11, .xadj = -1, .pos = 434 }, // 52 [29]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 463 }, // 53 [29]
	{ .l0 = 3, .r0 = 3, .ncol = 10, .xadj = -1, .pos = 492 }, // 54 [27]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 519 }, // 55 [27]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 546 }, // 56 [27]
	{ .l0 = 3, .r0 = 3, .ncol = 10, .xadj = -1, .pos = 573 }, // 57 [27]
	{ .l0 = 5, .r0 = 8, .ncol = 3, .xadj = -1, .pos = 600 }, // 58 [8]
	{ .l0 = 3, .r0 = 8, .ncol = 5, .xadj = -1, .pos = 608 }, // 59 [14]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 622 }, // 60 [35]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 657 }, // 61 [32]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 689 }, // 62 [35]
	{ .l0 = 3, .r0 = 4, .ncol = 9, .xadj = -1, .pos = 724 }, // 63 [24]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 748 }, // 64 [27]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 775 }, // 65 [37]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 812 }, // 66 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 847 }, // 67 [35]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 882 }, // 68 [37]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 919 }, // 69 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 954 }, // 70 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 989 }, // 71 [35]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1024 }, // 72 [37]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 1061 }, // 73 [27]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1088 }, // 74 [35]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1123 }, // 75 [37]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 1160 }, // 76 [32]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1192 }, // 77 [37]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1229 }, // 78 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1264 }, // 79 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1299 }, // 80 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1334 }, // 81 [35]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1369 }, // 82 [37]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 1406 }, // 83 [32]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 1438 }, // 84 [32]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1470 }, // 85 [35]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1505 }, // 86 [37]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1542 }, // 87 [37]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1579 }, // 88 [37]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 1616 }, // 89 [37]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 1653 }, // 90 [29]
	{ .l0 = 6, .r0 = 5, .ncol = 5, .xadj = -1, .pos = 1682 }, // 91 [14]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 1696 }, // 92 [29]
	{ .l0 = 3, .r0 = 8, .ncol = 5, .xadj = -1, .pos = 1725 }, // 93 [14]
	{ .l0 = 3, .r0 = 5, .ncol = 8, .xadj = -1, .pos = 1739 }, // 94 [21]
	{ .l0 = 0, .r0 = 1, .ncol = 15, .xadj = -1, .pos = 1760 }, // 95 [40]
	{ .l0 = 4, .r0 = 7, .ncol = 5, .xadj = -1, .pos = 1800 }, // 96 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 1814 }, // 97 [32]
	{ .l0 = 0, .r0 = 3, .ncol = 13, .xadj = -1, .pos = 1846 }, // 98 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1881 }, // 99 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 1916 }, // 100 [35]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 1951 }, // 101 [32]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 1983 }, // 102 [29]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 2012 }, // 103 [35]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 2047 }, // 104 [37]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 2084 }, // 105 [27]
	{ .l0 = 2, .r0 = 6, .ncol = 8, .xadj = -1, .pos = 2111 }, // 106 [21]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 2132 }, // 107 [35]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 2167 }, // 108 [27]
	{ .l0 = 0, .r0 = 0, .ncol = 16, .xadj = -1, .pos = 2194 }, // 109 [42]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 2236 }, // 110 [37]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 2273 }, // 111 [32]
	{ .l0 = 0, .r0 = 3, .ncol = 13, .xadj = -1, .pos = 2305 }, // 112 [35]
	{ .l0 = 1, .r0 = 2, .ncol = 13, .xadj = -1, .pos = 2340 }, // 113 [35]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 2375 }, // 114 [32]
	{ .l0 = 2, .r0 = 3, .ncol = 11, .xadj = -1, .pos = 2407 }, // 115 [29]
	{ .l0 = 1, .r0 = 4, .ncol = 11, .xadj = -1, .pos = 2436 }, // 116 [29]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 2465 }, // 117 [37]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 2502 }, // 118 [37]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 2539 }, // 119 [37]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 2576 }, // 120 [32]
	{ .l0 = 0, .r0 = 2, .ncol = 14, .xadj = -1, .pos = 2608 }, // 121 [37]
	{ .l0 = 2, .r0 = 4, .ncol = 10, .xadj = -1, .pos = 2645 }, // 122 [27]
	{ .l0 = 4, .r0 = 5, .ncol = 7, .xadj = -1, .pos = 2672 }, // 123 [19]
	{ .l0 = 6, .r0 = 8, .ncol = 2, .xadj = -1, .pos = 2691 }, // 124 [6]
	{ .l0 = 3, .r0 = 6, .ncol = 7, .xadj = -1, .pos = 2697 }, // 125 [19]
	{ .l0 = 1, .r0 = 3, .ncol = 12, .xadj = -1, .pos = 2716 }, // 126 [32]
	{ .l0 = 16, .r0 = 0, .ncol = 0, .xadj = -16, .pos = 2748 }, // 127 [0]
    },
    .data       = {
	254, 0, 224, 255, 25, 252, 63, 3, 127, 0, 0,	// 33
	254, 0, 192, 7, 0, 120, 0, 0, 0, 0, 0, 0, 0, 252, 1, 128, 15, 0, 240, 0, 0,	// 34
	0, 24, 0, 24, 3, 0, 227, 31, 224, 255, 243, 255, 1, 254, 49, 0, 48, 254, 1, 254, 63, 255, 31, 224, 31, 3, 0, 99, 0, 96, 0, 0,	// 35
	240, 240, 0, 63, 30, 48, 134, 1, 134, 97, 240, 48, 252, 30, 134, 31, 198, 48, 224, 49, 7, 60, 126, 0, 128, 7, 0,	// 36
	0, 4, 128, 135, 0, 152, 25, 0, 33, 1, 32, 180, 7, 204, 154, 1, 79, 33, 0, 44, 4, 128, 204, 0, 16, 15, 0,	// 37
	0, 120, 0, 206, 31, 224, 31, 3, 198, 97, 192, 112, 12, 24, 220, 1, 7, 31, 192, 224, 3, 0, 238, 0, 192, 24, 0, 0, 3,	// 38
	62, 0, 192, 31, 0, 248, 0, 0,	// 39
	192, 63, 0, 255, 63, 248, 0, 159, 3, 0, 55, 0, 192, 0,	// 40
	3, 0, 236, 0, 192, 249, 0, 31, 252, 255, 0, 252, 3, 0,	// 41
	24, 0, 0, 195, 0, 192, 28, 0, 208, 1, 240, 15, 0, 254, 1, 0, 232, 0, 128, 57, 0, 24, 6, 0, 3, 0, 0,	// 42
	0, 3, 0, 96, 0, 0, 12, 0, 128, 1, 0, 48, 0, 248, 255, 1, 255, 63, 0, 24, 0, 0, 3, 0, 96, 0, 0, 12, 0, 128, 1, 0,	// 43
	0, 0, 6, 0, 112, 0, 128, 7, 0, 112, 0, 0, 6, 0,	// 44
	0, 3, 0, 96, 0, 0, 12, 0, 128, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0, 0, 3, 0, 96, 0, 0, 12, 0,	// 45
	0, 224, 0, 0, 28, 0, 128, 3,	// 46
	0, 0, 12, 0, 224, 1, 0, 15, 0, 120, 0, 192, 3, 0, 30, 0, 240, 0, 128, 7, 0, 60, 0, 224, 1, 0, 12, 0, 0,	// 47
	248, 31, 192, 255, 15, 24, 128, 129, 1, 96, 48, 0, 12, 6, 128, 193, 0, 48, 48, 0, 3, 254, 127, 0, 255, 3, 0,	// 48
	6, 192, 192, 0, 24, 24, 0, 131, 3, 96, 240, 255, 15, 254, 255, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0,	// 49
	0, 192, 128, 3, 28, 120, 192, 131, 3, 124, 48, 192, 13, 6, 156, 193, 192, 49, 24, 28, 6, 199, 193, 192, 31, 24, 240, 1, 3,	// 50
	0, 48, 128, 1, 14, 56, 128, 131, 3, 96, 48, 24, 12, 6, 131, 193, 96, 48, 24, 14, 6, 231, 227, 192, 239, 15, 240, 248, 0,	// 51
	0, 12, 0, 224, 1, 0, 63, 0, 120, 6, 192, 195, 12, 28, 152, 193, 1, 51, 248, 255, 7, 255, 255, 0, 128, 25, 0, 48, 3,	// 52
	0, 48, 224, 31, 14, 252, 131, 131, 97, 96, 48, 6, 12, 198, 128, 193, 24, 48, 24, 7, 7, 195, 113, 96, 248, 15, 0, 124, 0,	// 53
	224, 31, 0, 255, 15, 240, 204, 1, 199, 112, 96, 12, 12, 142, 129, 193, 48, 48, 24, 14, 7, 131, 127, 96, 224, 7, 0,	// 54
	7, 0, 224, 0, 0, 12, 0, 128, 1, 0, 48, 0, 14, 6, 248, 193, 224, 7, 152, 31, 0, 127, 0, 224, 1, 0, 0,	// 55
	60, 62, 192, 239, 15, 24, 143, 131, 193, 96, 48, 24, 12, 6, 131, 193, 96, 48, 48, 30, 7, 126, 127, 128, 199, 7, 0,	// 56
	248, 193, 192, 127, 24, 24, 28, 131, 1, 99, 48, 96, 12, 6, 140, 193, 192, 24, 48, 140, 3, 254, 63, 0, 255, 1, 0,	// 57
	224, 224, 0, 28, 28, 128, 131, 3,	// 58
	0, 0, 6, 0, 112, 128, 131, 7, 112, 112, 0, 14, 6, 0,	// 59
	0, 3, 0, 96, 0, 0, 30, 0, 192, 3, 0, 204, 0, 128, 25, 0, 24, 6, 0, 195, 0, 48, 48, 0, 6, 6, 96, 128, 1, 12, 48, 128, 0, 4, 0,	// 60
	192, 12, 0, 152, 1, 0, 51, 0, 96, 6, 0, 204, 0, 128, 25, 0, 48, 3, 0, 102, 0, 192, 12, 0, 152, 1, 0, 51, 0, 96, 6, 0,	// 61
	8, 64, 0, 3, 12, 96, 128, 1, 24, 24, 0, 3, 3, 192, 48, 0, 24, 6, 0, 102, 0, 192, 12, 0, 240, 0, 0, 30, 0, 128, 1, 0, 48, 0, 0,	// 62
	60, 0, 192, 7, 0, 24, 0, 0, 3, 103, 96, 240, 12, 12, 6, 128, 99, 0, 224, 15, 0, 248, 0, 0,	// 63
	248, 127, 192, 255, 63, 24, 0, 134, 193, 131, 49, 252, 48, 198, 57, 134, 25, 198, 240, 255, 12, 248, 159, 1, 0, 3, 0,	// 64
	0, 192, 0, 0, 30, 24, 240, 3, 195, 111, 96, 254, 12, 252, 153, 129, 7, 3, 240, 96, 0, 252, 204, 0, 252, 25, 0, 126, 3, 0, 126, 0, 0, 15, 0, 128, 1,	// 65
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 24, 12, 12, 131, 129, 97, 48, 48, 12, 6, 134, 193, 192, 57, 24, 240, 143, 3, 188, 63, 0, 224, 3, 0,	// 66
	224, 15, 0, 255, 7, 240, 224, 1, 6, 48, 96, 0, 12, 12, 128, 129, 1, 48, 48, 0, 6, 6, 192, 192, 0, 24, 48, 128, 1, 31, 56, 224, 3, 3, 0,	// 67
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 0, 12, 12, 128, 129, 1, 48, 48, 0, 6, 6, 192, 192, 0, 24, 48, 128, 3, 30, 56, 128, 255, 3, 192, 31, 0,	// 68
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 48, 12, 12, 134, 129, 193, 48, 48, 126, 6, 198, 207, 192, 0, 24, 248, 0, 3, 31, 124, 0, 128, 15, 0,	// 69
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 48, 12, 12, 134, 129, 193, 48, 48, 126, 6, 198, 15, 192, 0, 0, 24, 0, 0, 31, 0, 224, 3, 0, 0,	// 70
	224, 15, 0, 255, 7, 240, 224, 1, 6, 48, 96, 0, 12, 12, 128, 129, 1, 48, 48, 48, 6, 6, 198, 192, 192, 24, 48, 152, 1, 31, 63, 224, 227, 3, 0,	// 71
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 24, 12, 12, 131, 1, 96, 0, 0, 12, 0, 134, 193, 192, 48, 24, 248, 255, 3, 255, 127, 96, 0, 12, 12, 128, 1,	// 72
	6, 192, 192, 0, 24, 24, 0, 3, 3, 96, 224, 255, 15, 252, 255, 129, 1, 48, 48, 0, 6, 6, 192, 192, 0, 24, 0,	// 73
	0, 60, 0, 128, 15, 0, 128, 3, 3, 96, 96, 0, 12, 12, 128, 129, 1, 48, 48, 0, 7, 254, 127, 192, 255, 7, 24, 0, 0, 3, 0, 96, 0, 0, 0,	// 74
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 56, 12, 140, 131, 1, 248, 0, 128, 59, 0, 62, 14, 192, 131, 7, 56, 224, 3, 3, 112, 96, 0, 12, 0, 128, 1,	// 75
	6, 192, 192, 0, 24, 24, 0, 3, 255, 127, 224, 255, 15, 12, 128, 129, 1, 48, 48, 0, 6, 0, 192, 0, 0, 24, 0, 224, 3, 0, 124, 0,	// 76
	6, 192, 192, 255, 31, 248, 255, 3, 31, 96, 128, 15, 12, 128, 7, 0, 192, 1, 0, 56, 0, 192, 3, 0, 31, 24, 248, 0, 3, 255, 127, 224, 255, 15, 12, 128, 1,	// 77
	6, 192, 192, 255, 31, 248, 255, 3, 15, 96, 128, 7, 12, 192, 3, 0, 224, 1, 0, 240, 0, 6, 120, 192, 0, 28, 248, 255, 3, 255, 127, 96, 0, 0, 0,	// 78
	224, 15, 0, 255, 7, 240, 224, 1, 6, 48, 96, 0, 12, 12, 128, 129, 1, 48, 48, 0, 6, 6, 192, 128, 1, 12, 240, 224, 1, 252, 31, 0, 254, 0, 0,	// 79
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 96, 12, 12, 140, 129, 129, 49, 48, 48, 6, 6, 6, 192, 192, 0, 48, 12, 0, 254, 1, 128, 31, 0, 0,	// 80
	224, 15, 0, 255, 7, 240, 224, 25, 6, 176, 99, 0, 124, 12, 128, 135, 1, 240, 48, 0, 54, 6, 192, 134, 1, 204, 240, 224, 25, 252, 159, 1, 254, 48, 0,	// 81
	6, 192, 192, 0, 24, 248, 255, 3, 255, 127, 96, 48, 12, 12, 134, 129, 193, 0, 48, 56, 0, 6, 15, 128, 177, 7, 240, 231, 3, 124, 112, 0, 0, 12, 0, 128, 1,	// 82
	0, 248, 0, 15, 31, 240, 131, 1, 231, 96, 96, 24, 12, 12, 131, 129, 225, 48, 48, 24, 6, 6, 195, 128, 225, 28, 248, 248, 1, 31, 30, 0,	// 83
	126, 0, 192, 15, 0, 24, 0, 3, 3, 96, 96, 0, 12, 252, 255, 129, 255, 63, 48, 0, 6, 6, 192, 192, 0, 24, 248, 1, 0, 63, 0, 0,	// 84
	6, 0, 192, 255, 3, 248, 255, 1, 3, 112, 96, 0, 12, 0, 128, 1, 0, 48, 0, 0, 6, 6, 192, 192, 0, 28, 248, 255, 1, 255, 15, 96, 0, 0, 0,	// 85
	6, 0, 192, 3, 0, 248, 3, 0, 243, 3, 96, 240, 1, 0, 240, 1, 0, 56, 0, 0, 7, 0, 248, 192, 224, 3, 152, 31, 0, 127, 0, 224, 1, 0, 12, 0, 0,	// 86
	6, 0, 192, 255, 0, 248, 255, 3, 3, 124, 96, 240, 15, 128, 31, 0, 124, 0, 128, 15, 0, 192, 15, 192, 224, 31, 24, 224, 3, 255, 127, 224, 127, 0, 12, 0, 0,	// 87
	6, 192, 192, 1, 28, 120, 192, 3, 31, 124, 96, 199, 13, 204, 157, 1, 240, 0, 0, 30, 0, 230, 206, 192, 142, 27, 248, 224, 3, 15, 120, 224, 0, 14, 12, 128, 1,	// 88
	6, 0, 192, 1, 0, 120, 0, 0, 31, 96, 96, 15, 12, 140, 131, 1, 224, 63, 0, 252, 7, 198, 193, 192, 30, 24, 248, 0, 3, 15, 0, 224, 0, 0, 12, 0, 0,	// 89
	62, 224, 192, 7, 30, 24, 224, 3, 3, 111, 96, 240, 12, 12, 135, 129, 121, 48, 176, 7, 6, 62, 192, 192, 3, 31, 56, 224, 3,	// 90
	255, 255, 239, 255, 255, 13, 0, 176, 1, 0, 54, 0, 192, 0,	// 91
	3, 0, 224, 1, 0, 240, 0, 0, 120, 0, 0, 60, 0, 0, 30, 0, 0, 15, 0, 128, 7, 0, 192, 3, 0, 224, 1, 0, 48,	// 92
	3, 0, 108, 0, 128, 13, 0, 176, 255, 255, 247, 255, 255, 0,	// 93
	192, 0, 0, 30, 0, 240, 0, 128, 7, 0, 240, 0, 0, 120, 0, 0, 60, 0, 0, 6, 0,	// 94
	0, 0, 12, 0, 128, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0, 0, 3, 0, 96, 0, 0, 12, 0, 128, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0, 0, 3,	// 95
	2, 0, 192, 0, 0, 48, 0, 0, 12, 0, 0, 1, 0, 0,	// 96
	0, 120, 0, 152, 31, 128, 51, 3, 48, 99, 0, 102, 12, 192, 140, 1, 152, 49, 0, 55, 3, 192, 255, 0, 240, 31, 0, 0, 3, 0, 96, 0,	// 97
	3, 192, 96, 0, 24, 252, 255, 131, 255, 127, 0, 28, 7, 192, 193, 1, 24, 48, 0, 3, 6, 96, 192, 0, 28, 28, 0, 199, 1, 224, 63, 0, 240, 1, 0,	// 98
	0, 31, 0, 248, 15, 0, 199, 1, 112, 112, 0, 6, 12, 192, 128, 1, 24, 48, 0, 3, 6, 224, 192, 0, 56, 24, 128, 143, 3, 240, 49, 0, 0, 6, 0,	// 99
	0, 31, 0, 248, 15, 0, 199, 1, 112, 112, 0, 6, 12, 192, 128, 1, 24, 48, 24, 7, 7, 195, 113, 224, 255, 31, 252, 255, 3, 0, 96, 0, 0, 12, 0,	// 100
	0, 31, 0, 248, 15, 0, 247, 1, 112, 118, 0, 198, 12, 192, 152, 1, 24, 51, 0, 99, 6, 224, 204, 0, 184, 29, 0, 191, 1, 128, 55, 0,	// 101
	96, 192, 0, 12, 24, 128, 1, 3, 254, 127, 224, 255, 15, 206, 128, 193, 24, 48, 24, 3, 6, 99, 192, 96, 12, 24, 12, 0, 0,	// 102
	0, 31, 0, 248, 15, 0, 199, 97, 112, 112, 12, 6, 140, 193, 128, 49, 24, 48, 6, 7, 199, 192, 113, 28, 252, 255, 129, 255, 31, 48, 0, 0, 6, 0, 0,	// 103
	3, 192, 96, 0, 24, 252, 255, 131, 255, 127, 0, 28, 12, 192, 129, 1, 24, 0, 0, 3, 0, 96, 192, 0, 28, 24, 0, 255, 3, 192, 127, 0, 0, 12, 0, 128, 1,	// 104
	0, 192, 0, 12, 24, 128, 1, 131, 51, 96, 112, 254, 15, 206, 255, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0,	// 105
	96, 0, 24, 12, 0, 131, 1, 96, 48, 0, 124, 6, 128, 207, 0, 248, 249, 255, 3, 255, 63,	// 106
	3, 192, 96, 0, 24, 252, 255, 131, 255, 127, 0, 96, 0, 0, 30, 0, 224, 7, 0, 207, 7, 224, 240, 0, 12, 28, 128, 1, 3, 0, 96, 0, 0, 12, 0,	// 107
	0, 192, 96, 0, 24, 12, 0, 131, 1, 96, 240, 255, 15, 254, 255, 1, 0, 48, 0, 0, 6, 0, 192, 0, 0, 24, 0,	// 108
	96, 192, 0, 12, 24, 128, 255, 3, 224, 127, 0, 14, 12, 192, 0, 0, 24, 0, 0, 255, 7, 192, 255, 0, 28, 24, 128, 1, 3, 48, 0, 0, 254, 15, 128, 255, 1, 0, 48, 0, 0, 6,	// 109
	96, 192, 0, 12, 24, 128, 255, 3, 240, 127, 0, 24, 12, 128, 129, 1, 24, 0, 0, 3, 0, 96, 192, 0, 28, 24, 0, 255, 3, 192, 127, 0, 0, 12, 0, 128, 1,	// 110
	0, 31, 0, 248, 15, 0, 199, 1, 112, 112, 0, 6, 12, 192, 128, 1, 24, 48, 0, 3, 6, 224, 224, 0, 56, 14, 0, 255, 1, 128, 15, 0,	// 111
	96, 0, 24, 12, 0, 131, 255, 127, 240, 255, 15, 28, 135, 193, 193, 49, 24, 48, 6, 3, 6, 96, 192, 0, 28, 28, 0, 199, 1, 224, 63, 0, 240, 1, 0,	// 112
	0, 31, 0, 248, 15, 0, 199, 1, 112, 112, 0, 6, 12, 192, 128, 1, 24, 48, 6, 7, 199, 192, 113, 24, 252, 255, 131, 255, 127, 48, 0, 12, 6, 128, 1,	// 113
	0, 192, 0, 12, 24, 128, 1, 3, 240, 127, 0, 254, 15, 128, 131, 1, 48, 48, 0, 3, 6, 96, 192, 0, 12, 24, 128, 3, 0, 96, 0, 0,	// 114
	128, 241, 0, 120, 30, 128, 143, 1, 48, 99, 0, 102, 12, 192, 156, 1, 24, 51, 0, 102, 6, 224, 249, 0, 60, 15, 0, 192, 0,	// 115
	96, 0, 0, 12, 0, 248, 255, 0, 255, 63, 0, 6, 14, 192, 128, 1, 24, 48, 0, 3, 6, 96, 224, 0, 12, 12, 0, 128, 1,	// 116
	96, 0, 0, 12, 0, 128, 255, 0, 240, 63, 0, 0, 14, 0, 128, 1, 0, 48, 0, 0, 6, 96, 192, 0, 12, 12, 128, 255, 3, 240, 127, 0, 0, 12, 0, 128, 1,	// 117
	96, 0, 0, 12, 0, 128, 7, 0, 240, 3, 0, 230, 1, 192, 240, 0, 0, 56, 0, 0, 7, 96, 120, 0, 204, 3, 128, 31, 0, 240, 0, 0, 6, 0, 192, 0, 0,	// 118
	96, 0, 0, 60, 0, 128, 127, 0, 48, 127, 0, 6, 15, 0, 120, 0, 224, 3, 0, 124, 0, 0, 60, 0, 12, 30, 128, 249, 3, 240, 15, 0, 30, 0, 192, 0, 0,	// 119
	96, 192, 0, 12, 24, 128, 131, 3, 240, 120, 0, 182, 13, 0, 28, 0, 128, 3, 0, 219, 6, 224, 241, 0, 28, 28, 128, 1, 3, 48, 96, 0,	// 120
	96, 0, 0, 12, 0, 131, 7, 96, 240, 3, 12, 246, 193, 1, 248, 62, 0, 248, 7, 128, 207, 0, 124, 0, 236, 3, 128, 31, 0, 240, 0, 0, 6, 0, 192, 0, 0,	// 121
	224, 225, 0, 60, 30, 128, 225, 3, 48, 110, 0, 230, 12, 192, 142, 1, 248, 48, 0, 15, 6, 224, 240, 0, 12, 30, 0,	// 122
	0, 2, 0, 224, 0, 240, 255, 15, 255, 254, 51, 0, 192, 2, 0, 80, 0, 0, 2,	// 123
	255, 255, 227, 255, 127, 0,	// 124
	1, 0, 40, 0, 0, 13, 0, 48, 255, 254, 195, 255, 63, 0, 14, 0, 128, 0, 0,	// 125
	0, 6, 0, 224, 0, 0, 14, 0, 192, 0, 0, 24, 0, 0, 7, 0, 192, 1, 0, 48, 0, 0, 6, 0, 224, 0, 0, 14, 0, 192, 0, 0,	// 126
		// 127

    }
};


// file: font/lubI18.bdf
// font: -B&H-LucidaBright-Medium-I-Normal--18-180-75-75-P-102-ISO10646-1

#include <font.h>

const struct Font font_lubI18 = {
    .type       = 1,
    .name	= "lubI18",
    .height	= 17,
    .width	= 19,
    .bytescol	= 4,
    .numcol     = 19,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 12, .ncol = 4, .xadj = -14, .pos = 0 }, // 33 [9]
	{ .l0 = 4, .r0 = 10, .ncol = 5, .xadj = -12, .pos = 9 }, // 34 [11]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -8, .pos = 20 }, // 35 [24]
	{ .l0 = 4, .r0 = 6, .ncol = 9, .xadj = -8, .pos = 44 }, // 36 [20]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -5, .pos = 64 }, // 37 [28]
	{ .l0 = 2, .r0 = 4, .ncol = 13, .xadj = -6, .pos = 92 }, // 38 [28]
	{ .l0 = 4, .r0 = 13, .ncol = 2, .xadj = -15, .pos = 120 }, // 39 [5]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -13, .pos = 125 }, // 40 [13]
	{ .l0 = 1, .r0 = 12, .ncol = 6, .xadj = -13, .pos = 138 }, // 41 [13]
	{ .l0 = 4, .r0 = 8, .ncol = 7, .xadj = -11, .pos = 151 }, // 42 [15]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -8, .pos = 166 }, // 43 [24]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -14, .pos = 190 }, // 44 [7]
	{ .l0 = 3, .r0 = 12, .ncol = 4, .xadj = -13, .pos = 197 }, // 45 [9]
	{ .l0 = 2, .r0 = 14, .ncol = 3, .xadj = -14, .pos = 206 }, // 46 [7]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -11, .pos = 213 }, // 47 [24]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 237 }, // 48 [22]
	{ .l0 = 3, .r0 = 9, .ncol = 7, .xadj = -8, .pos = 259 }, // 49 [15]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 274 }, // 50 [22]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -8, .pos = 296 }, // 51 [20]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -8, .pos = 316 }, // 52 [20]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 336 }, // 53 [22]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 358 }, // 54 [22]
	{ .l0 = 4, .r0 = 5, .ncol = 10, .xadj = -8, .pos = 380 }, // 55 [22]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -8, .pos = 402 }, // 56 [20]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 422 }, // 57 [22]
	{ .l0 = 2, .r0 = 13, .ncol = 4, .xadj = -14, .pos = 444 }, // 58 [9]
	{ .l0 = 2, .r0 = 12, .ncol = 5, .xadj = -14, .pos = 453 }, // 59 [11]
	{ .l0 = 3, .r0 = 5, .ncol = 11, .xadj = -8, .pos = 464 }, // 60 [24]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -8, .pos = 488 }, // 61 [24]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -8, .pos = 512 }, // 62 [24]
	{ .l0 = 4, .r0 = 8, .ncol = 7, .xadj = -11, .pos = 536 }, // 63 [15]
	{ .l0 = 3, .r0 = 2, .ncol = 14, .xadj = -3, .pos = 551 }, // 64 [30]
	{ .l0 = 1, .r0 = 5, .ncol = 13, .xadj = -6, .pos = 581 }, // 65 [28]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -8, .pos = 609 }, // 66 [24]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -6, .pos = 633 }, // 67 [26]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -5, .pos = 659 }, // 68 [30]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -9, .pos = 689 }, // 69 [24]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -9, .pos = 713 }, // 70 [24]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -5, .pos = 737 }, // 71 [26]
	{ .l0 = 1, .r0 = 2, .ncol = 16, .xadj = -5, .pos = 763 }, // 72 [34]
	{ .l0 = 1, .r0 = 10, .ncol = 8, .xadj = -13, .pos = 797 }, // 73 [17]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -11, .pos = 814 }, // 74 [22]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -6, .pos = 836 }, // 75 [30]
	{ .l0 = 1, .r0 = 8, .ncol = 10, .xadj = -9, .pos = 866 }, // 76 [22]
	{ .l0 = 2, .r0 = 0, .ncol = 17, .xadj = -3, .pos = 888 }, // 77 [37]
	{ .l0 = 1, .r0 = 2, .ncol = 16, .xadj = -5, .pos = 925 }, // 78 [34]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -5, .pos = 959 }, // 79 [28]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -9, .pos = 987 }, // 80 [26]
	{ .l0 = 3, .r0 = 2, .ncol = 14, .xadj = -5, .pos = 1013 }, // 81 [30]
	{ .l0 = 1, .r0 = 6, .ncol = 12, .xadj = -7, .pos = 1043 }, // 82 [26]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -9, .pos = 1069 }, // 83 [22]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -7, .pos = 1091 }, // 84 [26]
	{ .l0 = 4, .r0 = 2, .ncol = 13, .xadj = -6, .pos = 1117 }, // 85 [28]
	{ .l0 = 3, .r0 = 3, .ncol = 13, .xadj = -7, .pos = 1145 }, // 86 [28]
	{ .l0 = 3, .r0 = 0, .ncol = 16, .xadj = -3, .pos = 1173 }, // 87 [34]
	{ .l0 = 1, .r0 = 4, .ncol = 14, .xadj = -8, .pos = 1207 }, // 88 [30]
	{ .l0 = 3, .r0 = 4, .ncol = 12, .xadj = -7, .pos = 1237 }, // 89 [26]
	{ .l0 = 2, .r0 = 5, .ncol = 12, .xadj = -8, .pos = 1263 }, // 90 [26]
	{ .l0 = 2, .r0 = 10, .ncol = 7, .xadj = -13, .pos = 1289 }, // 91 [15]
	{ .l0 = 4, .r0 = 10, .ncol = 5, .xadj = -11, .pos = 1304 }, // 92 [11]
	{ .l0 = 1, .r0 = 11, .ncol = 7, .xadj = -13, .pos = 1315 }, // 93 [15]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -8, .pos = 1330 }, // 94 [24]
	{ .l0 = 2, .r0 = 10, .ncol = 7, .xadj = -10, .pos = 1354 }, // 95 [15]
	{ .l0 = 7, .r0 = 9, .ncol = 3, .xadj = -9, .pos = 1369 }, // 96 [7]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -8, .pos = 1376 }, // 97 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -8, .pos = 1398 }, // 98 [22]
	{ .l0 = 3, .r0 = 8, .ncol = 8, .xadj = -10, .pos = 1420 }, // 99 [17]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -8, .pos = 1437 }, // 100 [24]
	{ .l0 = 3, .r0 = 8, .ncol = 8, .xadj = -10, .pos = 1461 }, // 101 [17]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -12, .pos = 1478 }, // 102 [20]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -8, .pos = 1498 }, // 103 [22]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 1520 }, // 104 [22]
	{ .l0 = 3, .r0 = 12, .ncol = 4, .xadj = -14, .pos = 1542 }, // 105 [9]
	{ .l0 = 0, .r0 = 10, .ncol = 9, .xadj = -13, .pos = 1551 }, // 106 [20]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -9, .pos = 1571 }, // 107 [20]
	{ .l0 = 2, .r0 = 12, .ncol = 5, .xadj = -14, .pos = 1591 }, // 108 [11]
	{ .l0 = 3, .r0 = 1, .ncol = 15, .xadj = -2, .pos = 1602 }, // 109 [32]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 1634 }, // 110 [22]
	{ .l0 = 3, .r0 = 7, .ncol = 9, .xadj = -9, .pos = 1656 }, // 111 [20]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -8, .pos = 1676 }, // 112 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -8, .pos = 1698 }, // 113 [22]
	{ .l0 = 3, .r0 = 8, .ncol = 8, .xadj = -11, .pos = 1720 }, // 114 [17]
	{ .l0 = 2, .r0 = 9, .ncol = 8, .xadj = -11, .pos = 1737 }, // 115 [17]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -13, .pos = 1754 }, // 116 [13]
	{ .l0 = 3, .r0 = 6, .ncol = 10, .xadj = -8, .pos = 1767 }, // 117 [22]
	{ .l0 = 2, .r0 = 7, .ncol = 10, .xadj = -9, .pos = 1789 }, // 118 [22]
	{ .l0 = 2, .r0 = 3, .ncol = 14, .xadj = -5, .pos = 1811 }, // 119 [30]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -10, .pos = 1841 }, // 120 [20]
	{ .l0 = 1, .r0 = 7, .ncol = 11, .xadj = -9, .pos = 1861 }, // 121 [24]
	{ .l0 = 2, .r0 = 8, .ncol = 9, .xadj = -9, .pos = 1885 }, // 122 [20]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -13, .pos = 1905 }, // 123 [13]
	{ .l0 = 2, .r0 = 13, .ncol = 4, .xadj = -15, .pos = 1918 }, // 124 [9]
	{ .l0 = 3, .r0 = 10, .ncol = 6, .xadj = -13, .pos = 1927 }, // 125 [13]
	{ .l0 = 2, .r0 = 6, .ncol = 11, .xadj = -8, .pos = 1940 }, // 126 [24]
	{ .l0 = 19, .r0 = 0, .ncol = 0, .xadj = -19, .pos = 1964 }, // 127 [0]
    },
    .data       = {
	0, 32, 0, 79, 248, 1, 112, 0, 0,	// 33
	30, 0, 12, 0, 0, 0, 240, 0, 32, 0, 0,	// 34
	0, 34, 64, 52, 128, 24, 0, 29, 0, 38, 3, 199, 129, 201, 0, 112, 1, 48, 2, 88, 4, 136, 0, 0,	// 35
	0, 56, 112, 64, 240, 129, 49, 254, 161, 31, 226, 48, 130, 192, 3, 7, 3, 6, 0, 0,	// 36
	0, 32, 112, 96, 24, 97, 16, 34, 32, 38, 192, 39, 0, 32, 3, 160, 31, 176, 33, 48, 65, 48, 98, 16, 120, 32, 0, 0,	// 37
	0, 15, 0, 63, 0, 194, 0, 2, 129, 7, 130, 63, 132, 208, 9, 17, 14, 190, 56, 56, 89, 0, 142, 0, 4, 0, 8, 0,	// 38
	6, 0, 60, 0, 0,	// 39
	0, 63, 128, 191, 193, 1, 68, 0, 64, 0, 64, 0, 0,	// 40
	0, 0, 1, 0, 1, 0, 17, 192, 193, 255, 0, 126, 0,	// 41
	72, 0, 144, 1, 192, 0, 112, 1, 32, 13, 0, 3, 0, 2, 0,	// 42
	0, 1, 0, 2, 0, 4, 0, 8, 0, 208, 3, 124, 0, 70, 0, 128, 0, 0, 1, 0, 2, 0, 4, 0,	// 43
	0, 0, 1, 224, 3, 192, 1,	// 44
	0, 1, 0, 2, 0, 4, 0, 8, 0,	// 45
	0, 48, 0, 96, 0, 192, 0,	// 46
	0, 0, 1, 0, 1, 128, 1, 192, 0, 192, 0, 96, 0, 48, 0, 48, 0, 24, 0, 8, 0, 8, 0, 0,	// 47
	192, 15, 224, 63, 224, 192, 96, 0, 97, 0, 66, 0, 134, 0, 6, 131, 7, 252, 3, 224, 0, 0,	// 48
	0, 32, 0, 64, 0, 128, 16, 240, 33, 254, 195, 31, 132, 1, 8,	// 49
	0, 32, 0, 112, 32, 176, 32, 16, 33, 32, 66, 32, 132, 32, 8, 99, 16, 126, 0, 120, 0, 0,	// 50
	0, 56, 0, 64, 32, 130, 48, 4, 33, 8, 66, 16, 134, 208, 7, 63, 7, 60, 0, 0,	// 51
	0, 2, 0, 6, 0, 11, 0, 17, 1, 33, 2, 193, 7, 249, 15, 126, 17, 6, 2, 0,	// 52
	0, 56, 0, 64, 240, 128, 16, 1, 33, 2, 66, 12, 130, 240, 7, 193, 7, 2, 0, 4, 0, 0,	// 53
	128, 15, 224, 63, 224, 195, 96, 2, 65, 4, 66, 8, 134, 48, 6, 225, 7, 14, 7, 8, 0, 0,	// 54
	0, 48, 4, 112, 8, 56, 16, 24, 32, 8, 64, 8, 128, 8, 0, 9, 0, 14, 0, 4, 0, 0,	// 55
	0, 30, 0, 126, 224, 130, 96, 7, 33, 12, 66, 56, 134, 240, 7, 159, 7, 28, 0, 0,	// 56
	0, 24, 224, 65, 224, 135, 32, 8, 33, 16, 66, 32, 130, 64, 7, 195, 7, 252, 3, 224, 0, 0,	// 57
	0, 48, 128, 96, 128, 65, 0, 3, 0,	// 58
	0, 0, 1, 224, 3, 193, 3, 3, 0, 6, 0,	// 59
	0, 1, 0, 2, 0, 10, 0, 52, 0, 68, 0, 8, 1, 8, 2, 16, 8, 16, 32, 32, 0, 32, 0, 0,	// 60
	0, 4, 0, 9, 0, 18, 0, 36, 0, 72, 0, 144, 0, 32, 1, 64, 2, 128, 4, 0, 9, 0, 2, 0,	// 61
	0, 32, 0, 32, 32, 64, 128, 64, 0, 130, 0, 132, 0, 16, 1, 96, 1, 128, 2, 0, 2, 0, 4, 0,	// 62
	12, 32, 12, 76, 8, 12, 16, 4, 32, 4, 192, 7, 0, 7, 0,	// 63
	192, 7, 64, 16, 96, 64, 64, 0, 65, 124, 130, 132, 132, 4, 9, 9, 17, 146, 19, 228, 15, 72, 16, 32, 32, 64, 32, 0, 63, 0,	// 64
	0, 32, 0, 96, 0, 160, 0, 48, 1, 56, 0, 88, 0, 140, 0, 12, 1, 62, 34, 252, 79, 0, 255, 0, 128, 1, 0, 2,	// 65
	0, 32, 0, 64, 8, 240, 16, 255, 225, 31, 194, 17, 132, 32, 8, 193, 24, 66, 31, 124, 62, 112, 0, 0,	// 66
	128, 15, 192, 63, 224, 225, 224, 128, 65, 0, 194, 0, 132, 0, 8, 1, 16, 2, 16, 4, 32, 56, 0, 112, 0, 0,	// 67
	0, 32, 0, 64, 8, 248, 16, 255, 225, 31, 194, 1, 132, 0, 8, 1, 16, 2, 48, 4, 32, 24, 96, 112, 112, 192, 127, 0, 63, 0,	// 68
	0, 32, 0, 64, 8, 252, 240, 255, 225, 15, 66, 16, 132, 32, 8, 193, 16, 194, 56, 4, 0, 56, 0, 0,	// 69
	0, 32, 0, 64, 8, 252, 240, 255, 225, 15, 66, 16, 128, 32, 0, 193, 0, 194, 0, 4, 0, 56, 0, 0,	// 70
	128, 15, 192, 63, 224, 224, 224, 128, 65, 0, 194, 0, 132, 0, 8, 129, 16, 2, 31, 4, 62, 56, 4, 48, 8, 0,	// 71
	0, 32, 0, 64, 0, 240, 16, 255, 225, 31, 194, 17, 128, 32, 0, 65, 0, 128, 32, 0, 65, 0, 226, 16, 254, 225, 63, 194, 3, 128, 0, 0, 1, 0,	// 72
	0, 32, 0, 64, 0, 240, 16, 254, 225, 31, 194, 3, 128, 0, 0, 1, 0,	// 73
	0, 192, 1, 128, 2, 0, 4, 0, 12, 0, 79, 240, 143, 255, 1, 31, 0, 6, 0, 4, 0, 0,	// 74
	0, 32, 0, 64, 0, 240, 16, 255, 225, 31, 194, 19, 128, 240, 0, 145, 19, 48, 46, 32, 120, 40, 192, 48, 0, 97, 0, 64, 0, 0,	// 75
	0, 32, 0, 64, 8, 248, 16, 255, 225, 31, 194, 1, 132, 0, 8, 1, 16, 0, 48, 0, 112, 0,	// 76
	0, 32, 0, 64, 8, 248, 144, 15, 225, 0, 192, 15, 0, 252, 1, 128, 7, 0, 6, 0, 3, 0, 131, 128, 129, 129, 249, 195, 127, 132, 15, 8, 1, 0, 2, 0, 0,	// 77
	0, 32, 0, 64, 8, 248, 144, 15, 225, 0, 192, 3, 0, 30, 0, 112, 0, 128, 3, 0, 30, 0, 240, 16, 240, 32, 31, 192, 1, 128, 0, 0, 1, 0,	// 78
	128, 15, 192, 63, 224, 192, 64, 0, 65, 0, 194, 0, 132, 0, 8, 1, 8, 2, 24, 12, 24, 48, 28, 224, 31, 0, 15, 0,	// 79
	0, 32, 0, 64, 0, 240, 16, 255, 225, 63, 194, 35, 132, 64, 0, 129, 0, 130, 1, 132, 1, 248, 1, 224, 1, 0,	// 80
	128, 15, 192, 63, 224, 192, 64, 0, 65, 0, 194, 0, 132, 0, 24, 1, 56, 2, 152, 12, 56, 50, 60, 228, 31, 8, 7, 16, 0, 32,	// 81
	0, 32, 0, 64, 0, 240, 16, 255, 225, 31, 194, 17, 128, 96, 0, 193, 3, 66, 30, 204, 112, 248, 192, 64, 0, 1,	// 82
	0, 28, 0, 96, 224, 128, 224, 3, 97, 14, 66, 24, 132, 96, 4, 129, 15, 6, 14, 56, 0, 0,	// 83
	14, 0, 12, 64, 8, 128, 16, 224, 33, 254, 195, 63, 132, 3, 8, 1, 0, 2, 0, 4, 0, 8, 0, 112, 0, 0,	// 84
	2, 15, 252, 63, 248, 193, 48, 0, 33, 0, 2, 0, 4, 0, 8, 0, 8, 0, 12, 196, 7, 120, 0, 16, 0, 32, 0, 0,	// 85
	2, 0, 28, 0, 248, 7, 16, 255, 33, 192, 3, 0, 1, 128, 1, 192, 0, 192, 0, 96, 0, 104, 0, 48, 0, 32, 0, 0,	// 86
	2, 0, 252, 1, 248, 255, 16, 192, 32, 96, 0, 48, 0, 24, 0, 12, 0, 254, 31, 240, 127, 0, 48, 0, 24, 0, 12, 64, 6, 128, 3, 0, 3, 0,	// 87
	0, 32, 0, 64, 0, 192, 16, 64, 97, 96, 192, 67, 128, 126, 0, 225, 17, 224, 47, 96, 120, 96, 192, 112, 0, 97, 0, 64, 0, 0,	// 88
	2, 0, 12, 64, 120, 192, 208, 247, 33, 254, 3, 16, 4, 16, 0, 16, 0, 16, 0, 28, 0, 24, 0, 16, 0, 0,	// 89
	0, 32, 0, 96, 32, 240, 112, 112, 33, 112, 66, 48, 132, 48, 8, 57, 16, 58, 32, 60, 112, 24, 0, 16, 0, 0,	// 90
	0, 128, 1, 248, 131, 63, 244, 7, 232, 0, 64, 0, 128, 0, 0,	// 91
	6, 0, 240, 0, 0, 30, 0, 192, 3, 0, 24,	// 92
	0, 0, 1, 0, 2, 0, 23, 224, 47, 252, 193, 31, 128, 1, 0,	// 93
	0, 8, 0, 24, 0, 12, 0, 12, 0, 4, 0, 6, 0, 2, 0, 7, 0, 240, 0, 0, 15, 0, 32, 0,	// 94
	0, 64, 0, 128, 0, 0, 1, 0, 2, 0, 4, 0, 8, 0, 16,	// 95
	2, 0, 12, 0, 32, 0, 0,	// 96
	0, 28, 0, 126, 0, 134, 0, 2, 1, 2, 1, 4, 1, 8, 9, 144, 31, 224, 47, 192, 64, 0,	// 97
	0, 48, 4, 126, 232, 159, 240, 9, 33, 8, 2, 8, 4, 8, 4, 16, 6, 224, 7, 128, 3, 0,	// 98
	0, 30, 0, 127, 0, 131, 0, 2, 1, 2, 2, 4, 4, 8, 4, 112, 0,	// 99
	0, 28, 0, 126, 0, 134, 0, 2, 1, 2, 1, 4, 1, 8, 9, 17, 31, 242, 47, 252, 65, 24, 0, 0,	// 100
	0, 30, 0, 127, 0, 203, 0, 18, 1, 34, 2, 68, 6, 120, 4, 96, 4,	// 101
	0, 128, 65, 248, 131, 255, 192, 15, 224, 2, 32, 4, 64, 8, 128, 0, 0, 7, 0, 0,	// 102
	0, 128, 0, 124, 3, 254, 4, 6, 9, 4, 18, 4, 34, 8, 59, 16, 63, 224, 15, 192, 1, 0,	// 103
	0, 48, 4, 127, 232, 31, 240, 9, 32, 8, 0, 8, 0, 8, 8, 16, 31, 224, 63, 128, 65, 0,	// 104
	32, 48, 192, 127, 136, 135, 16, 0, 0,	// 105
	0, 192, 1, 0, 2, 0, 4, 0, 8, 0, 12, 132, 15, 248, 7, 241, 0, 2, 0, 0,	// 106
	0, 48, 4, 127, 248, 15, 240, 24, 0, 240, 0, 144, 3, 48, 14, 48, 16, 32, 32, 0,	// 107
	0, 48, 4, 126, 200, 159, 240, 3, 97, 0, 0,	// 108
	32, 48, 64, 127, 128, 15, 0, 13, 0, 12, 0, 8, 0, 8, 14, 240, 31, 224, 3, 0, 3, 0, 3, 0, 3, 0, 226, 3, 252, 7, 48, 8,	// 109
	32, 48, 64, 127, 128, 31, 0, 9, 0, 8, 0, 8, 0, 8, 8, 16, 31, 224, 63, 128, 65, 0,	// 110
	0, 30, 0, 127, 0, 131, 0, 2, 1, 2, 2, 4, 2, 24, 7, 240, 7, 192, 3, 0,	// 111
	0, 128, 65, 248, 131, 255, 0, 31, 1, 8, 2, 8, 4, 8, 4, 16, 6, 224, 7, 128, 3, 0,	// 112
	0, 28, 0, 126, 0, 134, 0, 2, 1, 2, 1, 4, 1, 8, 121, 144, 127, 224, 15, 192, 0, 0,	// 113
	32, 48, 64, 127, 128, 15, 0, 13, 0, 12, 0, 8, 0, 24, 0, 16, 0,	// 114
	0, 24, 0, 96, 0, 135, 0, 31, 1, 50, 2, 196, 6, 8, 7, 112, 0,	// 115
	32, 28, 192, 127, 240, 135, 224, 1, 1, 2, 0, 4, 0,	// 116
	32, 24, 192, 127, 128, 143, 0, 1, 1, 0, 1, 0, 1, 8, 9, 144, 31, 224, 47, 192, 64, 0,	// 117
	32, 0, 64, 0, 128, 3, 0, 254, 1, 224, 3, 0, 3, 0, 3, 0, 1, 160, 1, 192, 1, 0,	// 118
	32, 0, 192, 0, 128, 15, 0, 252, 1, 128, 1, 192, 0, 224, 0, 240, 0, 192, 63, 0, 56, 0, 48, 0, 48, 0, 26, 0, 28, 0,	// 119
	0, 48, 64, 112, 128, 49, 0, 47, 0, 120, 0, 224, 3, 32, 14, 112, 24, 96, 32, 0,	// 120
	0, 0, 65, 0, 130, 0, 6, 7, 6, 252, 3, 192, 3, 0, 2, 0, 2, 0, 2, 64, 3, 128, 3, 0,	// 121
	0, 32, 0, 96, 128, 227, 0, 113, 1, 114, 2, 52, 4, 56, 8, 48, 28, 32, 0, 0,	// 122
	0, 226, 0, 252, 67, 119, 228, 7, 96, 0, 64, 0, 0,	// 123
	0, 192, 1, 254, 224, 15, 112, 0, 0,	// 124
	0, 0, 1, 0, 2, 224, 19, 246, 35, 31, 128, 35, 0,	// 125
	0, 7, 0, 1, 0, 2, 0, 4, 0, 24, 0, 96, 0, 128, 1, 0, 2, 0, 4, 0, 12, 0, 6, 0,	// 126
		// 127

    }
};

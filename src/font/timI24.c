
// file: font/timI24.bdf
// font: -Adobe-Times-Medium-I-Normal--24-240-75-75-P-125-ISO10646-1

#include <font.h>

const struct Font font_timI24 = {
    .type       = 1,
    .name	= "timI24",
    .height	= 24,
    .width	= 22,
    .bytescol	= 4,
    .numcol     = 22,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 6, .r0 = 9, .ncol = 7, .xadj = -14, .pos = 0 }, // 33 [21]
	{ .l0 = 9, .r0 = 7, .ncol = 6, .xadj = -11, .pos = 21 }, // 34 [18]
	{ .l0 = 5, .r0 = 4, .ncol = 13, .xadj = -9, .pos = 39 }, // 35 [39]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 78 }, // 36 [33]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -2, .pos = 111 }, // 37 [48]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -3, .pos = 159 }, // 38 [48]
	{ .l0 = 8, .r0 = 12, .ncol = 2, .xadj = -17, .pos = 207 }, // 39 [6]
	{ .l0 = 6, .r0 = 9, .ncol = 7, .xadj = -14, .pos = 213 }, // 40 [21]
	{ .l0 = 4, .r0 = 11, .ncol = 7, .xadj = -14, .pos = 234 }, // 41 [21]
	{ .l0 = 6, .r0 = 7, .ncol = 9, .xadj = -9, .pos = 255 }, // 42 [27]
	{ .l0 = 8, .r0 = 2, .ncol = 12, .xadj = -5, .pos = 282 }, // 43 [36]
	{ .l0 = 4, .r0 = 15, .ncol = 3, .xadj = -16, .pos = 318 }, // 44 [9]
	{ .l0 = 6, .r0 = 10, .ncol = 6, .xadj = -14, .pos = 327 }, // 45 [18]
	{ .l0 = 5, .r0 = 15, .ncol = 2, .xadj = -16, .pos = 345 }, // 46 [6]
	{ .l0 = 5, .r0 = 10, .ncol = 7, .xadj = -15, .pos = 351 }, // 47 [21]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 372 }, // 48 [36]
	{ .l0 = 6, .r0 = 7, .ncol = 9, .xadj = -10, .pos = 408 }, // 49 [27]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 435 }, // 50 [33]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 468 }, // 51 [33]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 501 }, // 52 [36]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 537 }, // 53 [36]
	{ .l0 = 6, .r0 = 5, .ncol = 11, .xadj = -10, .pos = 573 }, // 54 [33]
	{ .l0 = 6, .r0 = 4, .ncol = 12, .xadj = -10, .pos = 606 }, // 55 [36]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 642 }, // 56 [36]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 678 }, // 57 [36]
	{ .l0 = 6, .r0 = 11, .ncol = 5, .xadj = -14, .pos = 714 }, // 58 [15]
	{ .l0 = 6, .r0 = 11, .ncol = 5, .xadj = -14, .pos = 729 }, // 59 [15]
	{ .l0 = 6, .r0 = 2, .ncol = 14, .xadj = -5, .pos = 744 }, // 60 [42]
	{ .l0 = 7, .r0 = 2, .ncol = 13, .xadj = -5, .pos = 786 }, // 61 [39]
	{ .l0 = 7, .r0 = 1, .ncol = 14, .xadj = -5, .pos = 825 }, // 62 [42]
	{ .l0 = 8, .r0 = 5, .ncol = 9, .xadj = -10, .pos = 867 }, // 63 [27]
	{ .l0 = 6, .r0 = 1, .ncol = 16, .xadj = 1, .pos = 894 }, // 64 [48]
	{ .l0 = 3, .r0 = 3, .ncol = 16, .xadj = -7, .pos = 942 }, // 65 [48]
	{ .l0 = 4, .r0 = 3, .ncol = 15, .xadj = -7, .pos = 990 }, // 66 [45]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -6, .pos = 1035 }, // 67 [48]
	{ .l0 = 4, .r0 = 0, .ncol = 18, .xadj = -4, .pos = 1083 }, // 68 [54]
	{ .l0 = 4, .r0 = 2, .ncol = 16, .xadj = -7, .pos = 1137 }, // 69 [48]
	{ .l0 = 4, .r0 = 2, .ncol = 16, .xadj = -7, .pos = 1185 }, // 70 [48]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -4, .pos = 1233 }, // 71 [48]
	{ .l0 = 4, .r0 = 0, .ncol = 18, .xadj = -4, .pos = 1281 }, // 72 [54]
	{ .l0 = 4, .r0 = 8, .ncol = 10, .xadj = -14, .pos = 1335 }, // 73 [30]
	{ .l0 = 4, .r0 = 6, .ncol = 12, .xadj = -11, .pos = 1365 }, // 74 [36]
	{ .l0 = 4, .r0 = 0, .ncol = 18, .xadj = -6, .pos = 1401 }, // 75 [54]
	{ .l0 = 4, .r0 = 4, .ncol = 14, .xadj = -8, .pos = 1455 }, // 76 [42]
	{ .l0 = 4, .r0 = 0, .ncol = 18, .xadj = -2, .pos = 1497 }, // 77 [54]
	{ .l0 = 4, .r0 = 0, .ncol = 18, .xadj = -6, .pos = 1551 }, // 78 [54]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -4, .pos = 1605 }, // 79 [48]
	{ .l0 = 4, .r0 = 2, .ncol = 16, .xadj = -7, .pos = 1653 }, // 80 [48]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -4, .pos = 1701 }, // 81 [48]
	{ .l0 = 4, .r0 = 3, .ncol = 15, .xadj = -7, .pos = 1749 }, // 82 [45]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 1794 }, // 83 [36]
	{ .l0 = 7, .r0 = 1, .ncol = 14, .xadj = -8, .pos = 1830 }, // 84 [42]
	{ .l0 = 7, .r0 = 0, .ncol = 15, .xadj = -4, .pos = 1872 }, // 85 [45]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -7, .pos = 1917 }, // 86 [48]
	{ .l0 = 6, .r0 = 0, .ncol = 16, .xadj = -1, .pos = 1965 }, // 87 [48]
	{ .l0 = 4, .r0 = 0, .ncol = 18, .xadj = -7, .pos = 2013 }, // 88 [54]
	{ .l0 = 7, .r0 = 1, .ncol = 14, .xadj = -8, .pos = 2067 }, // 89 [42]
	{ .l0 = 4, .r0 = 2, .ncol = 16, .xadj = -8, .pos = 2109 }, // 90 [48]
	{ .l0 = 6, .r0 = 7, .ncol = 9, .xadj = -12, .pos = 2157 }, // 91 [27]
	{ .l0 = 5, .r0 = 10, .ncol = 7, .xadj = -15, .pos = 2184 }, // 92 [21]
	{ .l0 = 5, .r0 = 8, .ncol = 9, .xadj = -12, .pos = 2205 }, // 93 [27]
	{ .l0 = 6, .r0 = 6, .ncol = 10, .xadj = -11, .pos = 2232 }, // 94 [30]
	{ .l0 = 5, .r0 = 4, .ncol = 13, .xadj = -9, .pos = 2262 }, // 95 [39]
	{ .l0 = 9, .r0 = 8, .ncol = 5, .xadj = -14, .pos = 2301 }, // 96 [15]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -9, .pos = 2316 }, // 97 [36]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 2352 }, // 98 [33]
	{ .l0 = 5, .r0 = 7, .ncol = 10, .xadj = -11, .pos = 2385 }, // 99 [30]
	{ .l0 = 5, .r0 = 4, .ncol = 13, .xadj = -9, .pos = 2415 }, // 100 [39]
	{ .l0 = 5, .r0 = 8, .ncol = 9, .xadj = -12, .pos = 2454 }, // 101 [27]
	{ .l0 = 0, .r0 = 7, .ncol = 15, .xadj = -15, .pos = 2481 }, // 102 [45]
	{ .l0 = 4, .r0 = 6, .ncol = 12, .xadj = -10, .pos = 2526 }, // 103 [36]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -9, .pos = 2562 }, // 104 [33]
	{ .l0 = 5, .r0 = 11, .ncol = 6, .xadj = -15, .pos = 2595 }, // 105 [18]
	{ .l0 = 1, .r0 = 11, .ncol = 10, .xadj = -16, .pos = 2613 }, // 106 [30]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -11, .pos = 2643 }, // 107 [33]
	{ .l0 = 5, .r0 = 11, .ncol = 6, .xadj = -16, .pos = 2676 }, // 108 [18]
	{ .l0 = 5, .r0 = 0, .ncol = 17, .xadj = -2, .pos = 2694 }, // 109 [51]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -9, .pos = 2745 }, // 110 [33]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 2778 }, // 111 [33]
	{ .l0 = 2, .r0 = 6, .ncol = 14, .xadj = -10, .pos = 2811 }, // 112 [42]
	{ .l0 = 5, .r0 = 5, .ncol = 12, .xadj = -10, .pos = 2853 }, // 113 [36]
	{ .l0 = 5, .r0 = 8, .ncol = 9, .xadj = -13, .pos = 2889 }, // 114 [27]
	{ .l0 = 5, .r0 = 9, .ncol = 8, .xadj = -13, .pos = 2916 }, // 115 [24]
	{ .l0 = 5, .r0 = 10, .ncol = 7, .xadj = -15, .pos = 2940 }, // 116 [21]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 2961 }, // 117 [33]
	{ .l0 = 5, .r0 = 6, .ncol = 11, .xadj = -10, .pos = 2994 }, // 118 [33]
	{ .l0 = 5, .r0 = 1, .ncol = 16, .xadj = -5, .pos = 3027 }, // 119 [48]
	{ .l0 = 4, .r0 = 7, .ncol = 11, .xadj = -11, .pos = 3075 }, // 120 [33]
	{ .l0 = 4, .r0 = 6, .ncol = 12, .xadj = -11, .pos = 3108 }, // 121 [36]
	{ .l0 = 5, .r0 = 8, .ncol = 9, .xadj = -12, .pos = 3144 }, // 122 [27]
	{ .l0 = 6, .r0 = 7, .ncol = 9, .xadj = -12, .pos = 3171 }, // 123 [27]
	{ .l0 = 5, .r0 = 11, .ncol = 6, .xadj = -16, .pos = 3198 }, // 124 [18]
	{ .l0 = 4, .r0 = 9, .ncol = 9, .xadj = -12, .pos = 3216 }, // 125 [27]
	{ .l0 = 7, .r0 = 5, .ncol = 10, .xadj = -8, .pos = 3243 }, // 126 [30]
	{ .l0 = 22, .r0 = 0, .ncol = 0, .xadj = -22, .pos = 3273 }, // 127 [0]
    },
    .data       = {
	0, 128, 3, 0, 128, 3, 0, 28, 0, 192, 7, 0, 248, 1, 0, 62, 0, 0, 14, 0, 0,	// 33
	62, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 14, 0, 0,	// 34
	0, 16, 2, 64, 208, 3, 64, 252, 0, 192, 31, 0, 248, 17, 0, 94, 16, 2, 64, 208, 3, 64, 252, 0, 192, 31, 0, 248, 17, 0, 94, 16, 0, 64, 0, 0, 64, 0, 0,	// 35
	0, 224, 1, 0, 128, 1, 56, 0, 3, 252, 0, 14, 198, 241, 3, 130, 31, 2, 242, 3, 3, 30, 135, 1, 7, 254, 1, 12, 120, 0, 60, 0, 0,	// 36
	224, 3, 0, 248, 7, 0, 28, 6, 0, 4, 4, 2, 2, 134, 3, 2, 195, 1, 198, 113, 0, 124, 28, 0, 4, 7, 0, 196, 240, 1, 116, 252, 3, 30, 14, 3, 6, 3, 2, 0, 1, 3, 0, 129, 1, 0, 227, 0,	// 37
	0, 240, 0, 0, 248, 1, 0, 28, 3, 0, 12, 2, 0, 6, 2, 0, 3, 2, 248, 7, 2, 252, 63, 1, 198, 248, 1, 98, 224, 1, 62, 178, 3, 28, 26, 3, 0, 14, 2, 0, 6, 2, 0, 2, 3, 0, 0, 1,	// 38
	62, 0, 0, 14, 0, 0,	// 39
	0, 248, 3, 0, 255, 31, 192, 7, 120, 240, 0, 0, 56, 0, 0, 12, 0, 0, 2, 0, 0,	// 40
	0, 0, 64, 0, 0, 48, 0, 0, 28, 0, 0, 15, 30, 224, 3, 248, 255, 0, 192, 31, 0,	// 41
	216, 0, 0, 216, 0, 0, 80, 0, 0, 38, 6, 0, 254, 7, 0, 32, 0, 0, 80, 0, 0, 216, 0, 0, 216, 0, 0,	// 42
	0, 12, 0, 0, 12, 0, 0, 12, 0, 0, 12, 0, 0, 12, 0, 224, 255, 1, 224, 255, 1, 0, 12, 0, 0, 12, 0, 0, 12, 0, 0, 12, 0, 0, 12, 0,	// 43
	0, 0, 16, 0, 128, 27, 0, 128, 15,	// 44
	0, 24, 0, 0, 24, 0, 0, 24, 0, 0, 24, 0, 0, 24, 0, 0, 24, 0,	// 45
	0, 128, 3, 0, 128, 3,	// 46
	0, 0, 3, 0, 224, 3, 0, 124, 0, 128, 15, 0, 240, 1, 0, 62, 0, 0, 6, 0, 0,	// 47
	0, 254, 0, 192, 255, 1, 240, 7, 3, 248, 0, 2, 28, 0, 2, 4, 0, 3, 6, 0, 3, 2, 192, 1, 2, 240, 0, 14, 127, 0, 252, 31, 0, 240, 7, 0,	// 48
	0, 0, 2, 0, 0, 2, 0, 0, 3, 4, 224, 3, 4, 254, 3, 196, 63, 2, 254, 7, 2, 126, 0, 0, 6, 0, 0,	// 49
	0, 0, 3, 0, 128, 3, 24, 192, 3, 28, 96, 3, 4, 48, 3, 6, 24, 3, 6, 12, 3, 6, 6, 3, 142, 3, 3, 252, 129, 1, 248, 192, 0,	// 50
	0, 128, 1, 0, 128, 3, 0, 0, 3, 8, 0, 2, 4, 1, 2, 2, 1, 2, 130, 3, 3, 130, 135, 1, 198, 254, 0, 126, 60, 0, 28, 0, 0,	// 51
	0, 56, 0, 0, 60, 0, 0, 54, 0, 0, 51, 0, 128, 49, 0, 192, 48, 3, 96, 240, 3, 48, 254, 0, 152, 63, 0, 252, 51, 0, 126, 48, 0, 14, 0, 0,	// 52
	0, 128, 3, 0, 128, 3, 64, 0, 3, 112, 0, 2, 252, 0, 2, 230, 0, 3, 198, 1, 1, 198, 195, 1, 134, 255, 0, 6, 62, 0, 6, 0, 0, 2, 0, 0,	// 53
	0, 254, 0, 128, 255, 1, 192, 131, 3, 224, 1, 3, 176, 0, 2, 152, 0, 3, 136, 128, 1, 140, 227, 1, 6, 255, 0, 6, 62, 0, 2, 0, 0,	// 54
	24, 0, 3, 14, 128, 3, 6, 192, 1, 6, 112, 0, 6, 56, 0, 6, 14, 0, 134, 7, 0, 198, 1, 0, 118, 0, 0, 62, 0, 0, 14, 0, 0, 2, 0, 0,	// 55
	0, 240, 0, 0, 248, 1, 0, 12, 3, 120, 4, 2, 252, 2, 2, 198, 1, 2, 130, 3, 2, 2, 7, 3, 130, 142, 1, 198, 252, 1, 124, 120, 0, 56, 0, 0,	// 56
	0, 0, 2, 224, 3, 2, 248, 7, 3, 60, 14, 1, 12, 140, 1, 6, 200, 0, 2, 104, 0, 2, 116, 0, 6, 60, 0, 14, 31, 0, 252, 7, 0, 248, 1, 0,	// 57
	0, 128, 3, 0, 128, 3, 0, 0, 0, 128, 3, 0, 128, 3, 0,	// 58
	0, 0, 16, 0, 128, 27, 0, 128, 15, 128, 3, 0, 128, 3, 0,	// 59
	0, 12, 0, 0, 12, 0, 0, 30, 0, 0, 30, 0, 0, 51, 0, 0, 51, 0, 128, 97, 0, 128, 97, 0, 128, 225, 0, 192, 192, 0, 192, 192, 0, 96, 128, 1, 96, 128, 1, 96, 128, 1,	// 60
	0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0, 0, 51, 0,	// 61
	96, 128, 1, 96, 128, 1, 96, 128, 1, 192, 192, 0, 192, 192, 0, 192, 97, 0, 128, 97, 0, 128, 97, 0, 0, 51, 0, 0, 51, 0, 0, 30, 0, 0, 30, 0, 0, 12, 0, 0, 12, 0,	// 62
	0, 128, 3, 24, 176, 3, 30, 28, 0, 6, 14, 0, 2, 3, 0, 130, 1, 0, 198, 1, 0, 252, 0, 0, 60, 0, 0,	// 63
	0, 252, 3, 0, 255, 7, 128, 15, 14, 224, 1, 24, 96, 0, 48, 48, 240, 49, 24, 252, 35, 8, 30, 99, 8, 3, 66, 140, 1, 67, 196, 0, 67, 196, 128, 65, 68, 224, 64, 196, 248, 65, 132, 63, 66, 204, 7, 34,	// 64
	0, 0, 2, 0, 0, 3, 0, 128, 3, 0, 192, 3, 0, 112, 2, 0, 28, 0, 0, 14, 0, 128, 11, 0, 192, 8, 0, 112, 8, 0, 24, 8, 2, 6, 8, 2, 255, 255, 3, 255, 255, 3, 0, 0, 2, 0, 0, 2,	// 65
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 2, 2, 30, 2, 2, 2, 2, 3, 2, 2, 3, 2, 199, 1, 6, 253, 1, 252, 253, 0, 252, 112, 0, 48, 0, 0,	// 66
	0, 60, 0, 0, 255, 0, 192, 255, 1, 240, 129, 1, 48, 0, 3, 28, 0, 2, 12, 0, 2, 4, 0, 2, 2, 0, 2, 2, 0, 3, 2, 0, 1, 2, 128, 1, 6, 192, 0, 12, 64, 0, 60, 0, 0, 6, 0, 0,	// 67
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 0, 2, 30, 0, 2, 2, 0, 2, 2, 0, 3, 2, 0, 1, 2, 128, 1, 6, 192, 0, 6, 112, 0, 12, 124, 0, 252, 31, 0, 248, 7, 0, 224, 0, 0,	// 68
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 2, 2, 30, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 2, 2, 31, 2, 194, 1, 3, 2, 128, 3, 6, 192, 0, 30, 0, 0,	// 69
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 2, 2, 30, 2, 0, 2, 2, 0, 2, 2, 0, 2, 6, 0, 2, 31, 0, 194, 1, 0, 2, 0, 0, 6, 0, 0, 30, 0, 0,	// 70
	0, 56, 0, 0, 255, 0, 192, 255, 1, 240, 129, 1, 112, 0, 3, 28, 0, 2, 12, 0, 2, 4, 0, 2, 6, 0, 2, 2, 0, 2, 2, 4, 1, 2, 4, 1, 6, 228, 1, 12, 252, 1, 60, 28, 0, 6, 4, 0,	// 71
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 2, 0, 30, 2, 0, 2, 2, 0, 2, 2, 0, 0, 2, 2, 0, 2, 2, 0, 194, 3, 0, 250, 3, 130, 127, 2, 242, 15, 2, 254, 0, 0, 30, 0, 0,	// 72
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 0, 0, 30, 0, 0, 2, 0, 0, 2, 0, 0,	// 73
	0, 128, 1, 0, 128, 3, 0, 0, 2, 0, 0, 2, 0, 128, 3, 0, 248, 1, 130, 127, 0, 242, 15, 0, 254, 0, 0, 30, 0, 0, 2, 0, 0, 2, 0, 0,	// 74
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 1, 0, 14, 3, 0, 130, 15, 2, 194, 62, 2, 96, 248, 2, 32, 224, 3, 18, 128, 3, 26, 0, 3, 14, 0, 2, 6, 0, 2, 2, 0, 0, 2, 0, 0,	// 75
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 0, 2, 30, 0, 2, 2, 0, 2, 2, 0, 2, 0, 0, 2, 0, 0, 3, 0, 128, 3, 0, 192, 0,	// 76
	0, 0, 2, 0, 0, 3, 0, 240, 3, 2, 62, 2, 226, 7, 2, 62, 0, 0, 254, 3, 0, 254, 255, 3, 0, 254, 1, 0, 96, 0, 0, 48, 0, 0, 12, 2, 0, 7, 2, 128, 1, 3, 96, 224, 3, 48, 254, 3, 252, 63, 2, 254, 3, 2,	// 77
	0, 0, 2, 0, 0, 3, 0, 240, 3, 2, 62, 2, 226, 7, 2, 126, 0, 0, 14, 0, 0, 126, 0, 0, 240, 3, 0, 128, 15, 0, 0, 126, 0, 0, 248, 1, 0, 192, 3, 0, 252, 0, 130, 15, 0, 250, 0, 0, 30, 0, 0, 6, 0, 0,	// 78
	0, 56, 0, 0, 255, 0, 192, 255, 1, 240, 129, 1, 112, 0, 3, 28, 0, 2, 12, 0, 2, 4, 0, 3, 6, 0, 3, 2, 128, 1, 2, 192, 1, 6, 112, 0, 12, 124, 0, 252, 31, 0, 248, 7, 0, 224, 0, 0,	// 79
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 127, 2, 242, 15, 2, 254, 2, 0, 30, 2, 0, 2, 2, 0, 2, 2, 0, 2, 3, 0, 2, 3, 0, 134, 1, 0, 252, 1, 0, 252, 0, 0, 112, 0, 0,	// 80
	0, 56, 96, 0, 255, 96, 192, 255, 49, 240, 129, 59, 112, 0, 63, 28, 0, 54, 12, 0, 98, 4, 0, 99, 6, 0, 99, 2, 128, 97, 2, 192, 97, 6, 112, 96, 12, 124, 32, 252, 31, 48, 248, 7, 16, 224, 0, 8,	// 81
	0, 0, 2, 0, 0, 2, 0, 192, 3, 0, 248, 3, 130, 63, 2, 242, 3, 2, 126, 2, 0, 14, 6, 0, 2, 30, 0, 2, 122, 0, 2, 227, 1, 134, 193, 3, 252, 1, 3, 252, 0, 2, 48, 0, 2,	// 82
	0, 128, 3, 0, 224, 1, 0, 0, 3, 120, 0, 2, 252, 1, 2, 198, 3, 2, 130, 7, 2, 2, 31, 3, 2, 254, 1, 6, 248, 0, 60, 0, 0, 14, 0, 0,	// 83
	30, 0, 2, 6, 0, 2, 2, 192, 3, 2, 248, 3, 130, 127, 2, 242, 15, 2, 254, 0, 0, 30, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 30, 0, 0, 6, 0, 0,	// 84
	0, 248, 0, 130, 255, 1, 242, 135, 3, 254, 0, 3, 30, 0, 3, 2, 0, 2, 2, 0, 2, 0, 0, 3, 0, 0, 1, 0, 128, 1, 0, 224, 0, 2, 62, 0, 194, 7, 0, 254, 0, 0, 14, 0, 0,	// 85
	2, 0, 0, 6, 0, 0, 126, 0, 0, 254, 15, 0, 194, 255, 3, 2, 248, 1, 0, 192, 0, 0, 48, 0, 0, 28, 0, 0, 7, 0, 128, 1, 0, 226, 0, 0, 58, 0, 0, 14, 0, 0, 6, 0, 0, 2, 0, 0,	// 86
	2, 0, 0, 2, 0, 0, 254, 255, 3, 254, 255, 1, 2, 112, 0, 0, 24, 0, 0, 14, 0, 130, 3, 0, 226, 0, 0, 254, 255, 3, 254, 255, 1, 2, 192, 0, 2, 48, 0, 0, 28, 0, 0, 7, 0, 192, 1, 0,	// 87
	0, 0, 2, 0, 0, 3, 2, 128, 3, 2, 192, 3, 6, 96, 2, 30, 48, 0, 254, 24, 0, 242, 15, 0, 2, 7, 2, 128, 63, 2, 192, 248, 3, 96, 192, 3, 50, 0, 3, 30, 0, 2, 14, 0, 2, 6, 0, 0, 2, 0, 0, 2, 0, 0,	// 88
	2, 0, 2, 6, 0, 2, 30, 192, 3, 254, 248, 3, 226, 63, 2, 2, 7, 2, 128, 1, 0, 192, 0, 0, 96, 0, 0, 50, 0, 0, 30, 0, 0, 14, 0, 0, 6, 0, 0, 2, 0, 0,	// 89
	0, 0, 2, 0, 0, 3, 24, 128, 3, 14, 192, 3, 6, 240, 2, 2, 56, 2, 2, 28, 2, 2, 14, 2, 130, 3, 2, 194, 1, 2, 226, 0, 3, 114, 0, 3, 62, 128, 3, 14, 192, 1, 6, 96, 0, 2, 0, 0,	// 90
	0, 0, 60, 0, 128, 63, 0, 248, 35, 128, 127, 32, 240, 7, 0, 126, 0, 0, 14, 0, 0, 2, 0, 0, 2, 0, 0,	// 91
	6, 0, 0, 62, 0, 0, 240, 1, 0, 128, 15, 0, 0, 124, 0, 0, 224, 3, 0, 0, 3,	// 92
	0, 0, 32, 0, 0, 32, 0, 0, 56, 0, 0, 63, 0, 240, 7, 2, 255, 0, 226, 15, 0, 254, 0, 0, 30, 0, 0,	// 93
	0, 6, 0, 128, 7, 0, 192, 1, 0, 112, 0, 0, 56, 0, 0, 14, 0, 0, 30, 0, 0, 248, 0, 0, 224, 7, 0, 0, 7, 0,	// 94
	0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96, 0, 0, 96,	// 95
	6, 0, 0, 14, 0, 0, 28, 0, 0, 24, 0, 0, 32, 0, 0,	// 96
	0, 224, 1, 0, 248, 3, 0, 28, 3, 0, 6, 3, 0, 3, 1, 0, 129, 0, 128, 65, 0, 128, 192, 3, 128, 248, 3, 0, 63, 2, 128, 7, 1, 128, 1, 0,	// 97
	0, 192, 3, 0, 252, 3, 128, 31, 2, 242, 7, 2, 126, 4, 3, 14, 2, 1, 0, 129, 1, 128, 193, 0, 128, 113, 0, 128, 63, 0, 0, 15, 0,	// 98
	0, 240, 1, 0, 252, 3, 0, 30, 3, 0, 7, 2, 0, 1, 2, 128, 1, 3, 128, 0, 1, 128, 128, 1, 128, 131, 0, 0, 3, 0,	// 99
	0, 224, 1, 0, 248, 3, 0, 28, 3, 0, 6, 3, 0, 3, 1, 0, 129, 0, 128, 65, 0, 128, 192, 3, 128, 240, 3, 0, 127, 2, 242, 7, 1, 254, 0, 0, 30, 0, 0,	// 100
	0, 240, 1, 0, 252, 3, 0, 30, 3, 0, 19, 2, 0, 17, 2, 128, 9, 3, 128, 140, 1, 128, 199, 0, 0, 3, 0,	// 101
	0, 0, 48, 0, 0, 112, 0, 0, 64, 0, 0, 64, 0, 0, 56, 128, 128, 63, 128, 248, 7, 128, 255, 0, 240, 15, 0, 252, 0, 0, 140, 0, 0, 130, 0, 0, 130, 0, 0, 14, 0, 0, 12, 0, 0,	// 102
	0, 0, 120, 0, 0, 108, 0, 28, 198, 0, 191, 131, 0, 227, 131, 128, 65, 135, 128, 64, 198, 128, 32, 78, 128, 57, 124, 128, 31, 60, 128, 14, 0, 128, 0, 0,	// 103
	0, 192, 3, 0, 252, 3, 128, 127, 0, 242, 31, 0, 126, 4, 0, 14, 2, 0, 0, 1, 0, 0, 129, 3, 128, 241, 3, 128, 127, 2, 0, 15, 1,	// 104
	0, 128, 1, 0, 240, 3, 128, 124, 2, 128, 31, 1, 140, 3, 0, 12, 0, 0,	// 105
	0, 0, 48, 0, 0, 112, 0, 0, 64, 0, 0, 96, 0, 0, 62, 0, 224, 15, 128, 252, 1, 128, 63, 0, 140, 3, 0, 12, 0, 0,	// 106
	0, 192, 3, 0, 252, 3, 128, 63, 0, 242, 11, 0, 126, 24, 0, 14, 124, 0, 128, 226, 1, 128, 129, 3, 128, 1, 3, 128, 0, 1, 0, 128, 0,	// 107
	0, 192, 1, 0, 252, 3, 128, 63, 2, 242, 7, 1, 126, 128, 0, 14, 0, 0,	// 108
	0, 128, 3, 0, 240, 3, 128, 124, 0, 128, 31, 0, 128, 7, 0, 0, 2, 0, 0, 1, 0, 0, 129, 3, 128, 241, 3, 128, 127, 0, 0, 15, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 128, 129, 3, 128, 241, 3, 128, 127, 2,	// 109
	0, 128, 3, 0, 240, 3, 128, 124, 0, 128, 31, 0, 128, 7, 0, 0, 2, 0, 0, 1, 0, 0, 129, 3, 128, 241, 3, 128, 127, 2, 0, 15, 1,	// 110
	0, 240, 0, 0, 252, 1, 0, 30, 3, 0, 7, 2, 0, 3, 2, 128, 1, 3, 128, 0, 1, 128, 192, 1, 128, 241, 0, 0, 127, 0, 0, 30, 0,	// 111
	0, 0, 64, 0, 0, 96, 0, 0, 124, 0, 224, 95, 128, 252, 67, 128, 63, 2, 128, 7, 2, 0, 4, 3, 0, 2, 1, 0, 129, 1, 128, 193, 0, 128, 113, 0, 128, 63, 0, 0, 15, 0,	// 112
	0, 224, 1, 0, 248, 3, 0, 28, 3, 0, 6, 3, 0, 3, 65, 0, 129, 64, 128, 65, 120, 128, 192, 127, 128, 248, 67, 0, 63, 0, 128, 7, 0, 128, 1, 0,	// 113
	0, 128, 3, 0, 240, 3, 128, 124, 0, 128, 31, 0, 128, 7, 0, 0, 2, 0, 0, 1, 0, 128, 3, 0, 128, 3, 0,	// 114
	0, 192, 3, 0, 0, 3, 0, 15, 2, 128, 31, 2, 128, 60, 3, 128, 240, 1, 128, 225, 0, 128, 3, 0,	// 115
	0, 192, 1, 128, 252, 3, 192, 127, 2, 224, 7, 1, 240, 0, 1, 128, 128, 0, 128, 0, 0,	// 116
	0, 224, 1, 128, 252, 3, 128, 31, 3, 128, 3, 1, 128, 0, 1, 0, 128, 0, 0, 192, 3, 0, 240, 3, 0, 124, 2, 128, 31, 0, 128, 3, 0,	// 117
	128, 0, 0, 128, 0, 0, 128, 15, 0, 128, 255, 3, 0, 240, 1, 0, 192, 0, 0, 96, 0, 0, 48, 0, 128, 28, 0, 128, 7, 0, 128, 3, 0,	// 118
	128, 0, 0, 128, 0, 0, 128, 15, 0, 128, 255, 3, 0, 240, 1, 0, 192, 0, 0, 96, 0, 0, 24, 0, 128, 255, 3, 128, 255, 3, 0, 128, 1, 0, 192, 0, 0, 96, 0, 128, 24, 0, 128, 15, 0, 128, 3, 0,	// 119
	0, 0, 3, 0, 0, 3, 0, 129, 1, 128, 193, 0, 128, 99, 0, 0, 63, 0, 0, 252, 0, 0, 228, 3, 0, 3, 3, 128, 1, 1, 128, 129, 0,	// 120
	0, 0, 96, 128, 0, 96, 128, 0, 64, 128, 7, 48, 128, 127, 28, 0, 248, 7, 0, 128, 3, 0, 192, 0, 0, 112, 0, 128, 28, 0, 128, 7, 0, 128, 3, 0,	// 121
	0, 0, 3, 0, 131, 3, 128, 193, 3, 128, 97, 3, 128, 49, 3, 128, 25, 3, 128, 13, 3, 128, 135, 1, 128, 3, 0,	// 122
	0, 8, 0, 0, 24, 28, 0, 252, 63, 0, 247, 64, 240, 3, 64, 120, 0, 0, 4, 0, 0, 2, 0, 0, 2, 0, 0,	// 123
	0, 0, 120, 0, 128, 15, 0, 240, 0, 0, 31, 0, 240, 1, 0, 30, 0, 0,	// 124
	0, 0, 64, 0, 0, 64, 0, 0, 32, 0, 0, 30, 2, 192, 15, 2, 239, 0, 252, 63, 0, 56, 24, 0, 0, 16, 0,	// 125
	0, 48, 0, 0, 24, 0, 0, 12, 0, 0, 12, 0, 0, 28, 0, 0, 56, 0, 0, 48, 0, 0, 48, 0, 0, 24, 0, 0, 12, 0,	// 126
		// 127

    }
};


// file: font/uti24.bdf
// font: -Adobe-Utopia-Regular-I-Normal--25-240-75-75-P-133-ISO10646-1

#include <font.h>

const struct Font font_uti24 = {
    .type       = 1,
    .name	= "uti24",
    .height	= 24,
    .width	= 25,
    .bytescol	= 4,
    .numcol     = 25,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 16, .ncol = 6, .xadj = -19, .pos = 0 }, // 33 [18]
	{ .l0 = 4, .r0 = 14, .ncol = 7, .xadj = -16, .pos = 18 }, // 34 [21]
	{ .l0 = 3, .r0 = 9, .ncol = 13, .xadj = -12, .pos = 39 }, // 35 [39]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 78 }, // 36 [36]
	{ .l0 = 4, .r0 = 5, .ncol = 16, .xadj = -5, .pos = 114 }, // 37 [48]
	{ .l0 = 4, .r0 = 4, .ncol = 17, .xadj = -6, .pos = 162 }, // 38 [51]
	{ .l0 = 4, .r0 = 18, .ncol = 3, .xadj = -20, .pos = 213 }, // 39 [9]
	{ .l0 = 5, .r0 = 12, .ncol = 8, .xadj = -16, .pos = 222 }, // 40 [24]
	{ .l0 = 2, .r0 = 15, .ncol = 8, .xadj = -16, .pos = 246 }, // 41 [24]
	{ .l0 = 4, .r0 = 13, .ncol = 8, .xadj = -15, .pos = 270 }, // 42 [24]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 294 }, // 43 [36]
	{ .l0 = 2, .r0 = 18, .ncol = 5, .xadj = -19, .pos = 330 }, // 44 [15]
	{ .l0 = 4, .r0 = 14, .ncol = 7, .xadj = -15, .pos = 345 }, // 45 [21]
	{ .l0 = 3, .r0 = 18, .ncol = 4, .xadj = -19, .pos = 366 }, // 46 [12]
	{ .l0 = 4, .r0 = 13, .ncol = 8, .xadj = -14, .pos = 378 }, // 47 [24]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 402 }, // 48 [36]
	{ .l0 = 3, .r0 = 13, .ncol = 9, .xadj = -12, .pos = 438 }, // 49 [27]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 465 }, // 50 [36]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 501 }, // 51 [36]
	{ .l0 = 3, .r0 = 11, .ncol = 11, .xadj = -12, .pos = 537 }, // 52 [33]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 570 }, // 53 [36]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 606 }, // 54 [36]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -12, .pos = 642 }, // 55 [36]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 678 }, // 56 [36]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -12, .pos = 714 }, // 57 [36]
	{ .l0 = 3, .r0 = 16, .ncol = 6, .xadj = -19, .pos = 750 }, // 58 [18]
	{ .l0 = 2, .r0 = 16, .ncol = 7, .xadj = -19, .pos = 768 }, // 59 [21]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 789 }, // 60 [36]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 825 }, // 61 [36]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 861 }, // 62 [36]
	{ .l0 = 4, .r0 = 13, .ncol = 8, .xadj = -14, .pos = 897 }, // 63 [24]
	{ .l0 = 4, .r0 = 4, .ncol = 17, .xadj = -6, .pos = 921 }, // 64 [51]
	{ .l0 = 1, .r0 = 7, .ncol = 17, .xadj = -9, .pos = 972 }, // 65 [51]
	{ .l0 = 2, .r0 = 7, .ncol = 16, .xadj = -9, .pos = 1023 }, // 66 [48]
	{ .l0 = 4, .r0 = 5, .ncol = 16, .xadj = -8, .pos = 1071 }, // 67 [48]
	{ .l0 = 2, .r0 = 4, .ncol = 19, .xadj = -6, .pos = 1119 }, // 68 [57]
	{ .l0 = 2, .r0 = 8, .ncol = 15, .xadj = -10, .pos = 1176 }, // 69 [45]
	{ .l0 = 2, .r0 = 8, .ncol = 15, .xadj = -11, .pos = 1221 }, // 70 [45]
	{ .l0 = 4, .r0 = 4, .ncol = 17, .xadj = -7, .pos = 1266 }, // 71 [51]
	{ .l0 = 2, .r0 = 2, .ncol = 21, .xadj = -6, .pos = 1317 }, // 72 [63]
	{ .l0 = 2, .r0 = 12, .ncol = 11, .xadj = -16, .pos = 1380 }, // 73 [33]
	{ .l0 = 0, .r0 = 13, .ncol = 12, .xadj = -17, .pos = 1413 }, // 74 [36]
	{ .l0 = 2, .r0 = 5, .ncol = 18, .xadj = -9, .pos = 1449 }, // 75 [54]
	{ .l0 = 2, .r0 = 9, .ncol = 14, .xadj = -11, .pos = 1503 }, // 76 [42]
	{ .l0 = 2, .r0 = 0, .ncol = 23, .xadj = -2, .pos = 1545 }, // 77 [69]
	{ .l0 = 2, .r0 = 2, .ncol = 21, .xadj = -6, .pos = 1614 }, // 78 [63]
	{ .l0 = 4, .r0 = 4, .ncol = 17, .xadj = -6, .pos = 1677 }, // 79 [51]
	{ .l0 = 2, .r0 = 7, .ncol = 16, .xadj = -10, .pos = 1728 }, // 80 [48]
	{ .l0 = 4, .r0 = 4, .ncol = 17, .xadj = -6, .pos = 1776 }, // 81 [51]
	{ .l0 = 2, .r0 = 6, .ncol = 17, .xadj = -9, .pos = 1827 }, // 82 [51]
	{ .l0 = 3, .r0 = 9, .ncol = 13, .xadj = -12, .pos = 1878 }, // 83 [39]
	{ .l0 = 4, .r0 = 7, .ncol = 14, .xadj = -10, .pos = 1917 }, // 84 [42]
	{ .l0 = 5, .r0 = 2, .ncol = 18, .xadj = -5, .pos = 1959 }, // 85 [54]
	{ .l0 = 4, .r0 = 4, .ncol = 17, .xadj = -9, .pos = 2013 }, // 86 [51]
	{ .l0 = 4, .r0 = 0, .ncol = 21, .xadj = -2, .pos = 2064 }, // 87 [63]
	{ .l0 = 2, .r0 = 5, .ncol = 18, .xadj = -9, .pos = 2127 }, // 88 [54]
	{ .l0 = 3, .r0 = 5, .ncol = 17, .xadj = -10, .pos = 2181 }, // 89 [51]
	{ .l0 = 3, .r0 = 6, .ncol = 16, .xadj = -9, .pos = 2232 }, // 90 [48]
	{ .l0 = 3, .r0 = 14, .ncol = 8, .xadj = -17, .pos = 2280 }, // 91 [24]
	{ .l0 = 4, .r0 = 13, .ncol = 8, .xadj = -15, .pos = 2304 }, // 92 [24]
	{ .l0 = 3, .r0 = 14, .ncol = 8, .xadj = -17, .pos = 2328 }, // 93 [24]
	{ .l0 = 5, .r0 = 10, .ncol = 10, .xadj = -11, .pos = 2352 }, // 94 [30]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -13, .pos = 2382 }, // 95 [36]
	{ .l0 = 5, .r0 = 14, .ncol = 6, .xadj = -15, .pos = 2418 }, // 96 [18]
	{ .l0 = 4, .r0 = 8, .ncol = 13, .xadj = -11, .pos = 2436 }, // 97 [39]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 2475 }, // 98 [36]
	{ .l0 = 4, .r0 = 10, .ncol = 11, .xadj = -13, .pos = 2511 }, // 99 [33]
	{ .l0 = 4, .r0 = 8, .ncol = 13, .xadj = -11, .pos = 2544 }, // 100 [39]
	{ .l0 = 4, .r0 = 10, .ncol = 11, .xadj = -13, .pos = 2583 }, // 101 [33]
	{ .l0 = 0, .r0 = 11, .ncol = 14, .xadj = -17, .pos = 2616 }, // 102 [42]
	{ .l0 = 2, .r0 = 9, .ncol = 14, .xadj = -12, .pos = 2658 }, // 103 [42]
	{ .l0 = 4, .r0 = 7, .ncol = 14, .xadj = -10, .pos = 2700 }, // 104 [42]
	{ .l0 = 4, .r0 = 15, .ncol = 6, .xadj = -18, .pos = 2742 }, // 105 [18]
	{ .l0 = 0, .r0 = 15, .ncol = 10, .xadj = -18, .pos = 2760 }, // 106 [30]
	{ .l0 = 4, .r0 = 8, .ncol = 13, .xadj = -11, .pos = 2790 }, // 107 [39]
	{ .l0 = 4, .r0 = 15, .ncol = 6, .xadj = -18, .pos = 2829 }, // 108 [18]
	{ .l0 = 4, .r0 = 0, .ncol = 21, .xadj = -2, .pos = 2847 }, // 109 [63]
	{ .l0 = 4, .r0 = 7, .ncol = 14, .xadj = -10, .pos = 2910 }, // 110 [42]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 2952 }, // 111 [36]
	{ .l0 = 3, .r0 = 9, .ncol = 13, .xadj = -11, .pos = 2988 }, // 112 [39]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -11, .pos = 3027 }, // 113 [36]
	{ .l0 = 4, .r0 = 11, .ncol = 10, .xadj = -15, .pos = 3063 }, // 114 [30]
	{ .l0 = 3, .r0 = 12, .ncol = 10, .xadj = -15, .pos = 3093 }, // 115 [30]
	{ .l0 = 5, .r0 = 12, .ncol = 8, .xadj = -16, .pos = 3123 }, // 116 [24]
	{ .l0 = 4, .r0 = 7, .ncol = 14, .xadj = -10, .pos = 3147 }, // 117 [42]
	{ .l0 = 4, .r0 = 9, .ncol = 12, .xadj = -12, .pos = 3189 }, // 118 [36]
	{ .l0 = 4, .r0 = 2, .ncol = 19, .xadj = -5, .pos = 3225 }, // 119 [57]
	{ .l0 = 3, .r0 = 9, .ncol = 13, .xadj = -12, .pos = 3282 }, // 120 [39]
	{ .l0 = 1, .r0 = 10, .ncol = 14, .xadj = -13, .pos = 3321 }, // 121 [42]
	{ .l0 = 3, .r0 = 10, .ncol = 12, .xadj = -13, .pos = 3363 }, // 122 [36]
	{ .l0 = 3, .r0 = 14, .ncol = 8, .xadj = -17, .pos = 3399 }, // 123 [24]
	{ .l0 = 5, .r0 = 18, .ncol = 2, .xadj = -18, .pos = 3423 }, // 124 [6]
	{ .l0 = 3, .r0 = 14, .ncol = 8, .xadj = -17, .pos = 3429 }, // 125 [24]
	{ .l0 = 6, .r0 = 8, .ncol = 11, .xadj = -10, .pos = 3453 }, // 126 [33]
	{ .l0 = 25, .r0 = 0, .ncol = 0, .xadj = -25, .pos = 3486 }, // 127 [0]
    },
    .data       = {
	0, 0, 2, 0, 0, 7, 128, 31, 7, 252, 7, 2, 252, 0, 0, 28, 0, 0,	// 33
	224, 1, 0, 124, 0, 0, 28, 0, 0, 0, 0, 0, 224, 1, 0, 124, 0, 0, 28, 0, 0,	// 34
	0, 32, 0, 0, 32, 7, 128, 240, 7, 128, 254, 0, 224, 47, 0, 252, 33, 0, 156, 32, 7, 128, 240, 7, 128, 254, 0, 224, 47, 0, 252, 33, 0, 156, 0, 0, 128, 0, 0,	// 35
	0, 0, 3, 0, 0, 7, 224, 1, 6, 240, 3, 28, 248, 135, 7, 12, 127, 4, 196, 31, 6, 60, 252, 3, 7, 248, 1, 12, 240, 0, 28, 0, 0, 24, 0, 0,	// 36
	192, 1, 0, 240, 7, 4, 24, 4, 6, 4, 4, 1, 4, 196, 0, 4, 99, 0, 252, 17, 0, 120, 12, 0, 8, 198, 1, 8, 241, 7, 200, 24, 4, 104, 4, 4, 24, 4, 4, 12, 4, 3, 4, 252, 1, 0, 112, 0,	// 37
	0, 240, 1, 0, 248, 3, 0, 252, 3, 0, 12, 6, 112, 6, 4, 248, 3, 4, 136, 7, 4, 4, 15, 4, 132, 60, 2, 196, 112, 2, 124, 224, 1, 56, 192, 1, 0, 192, 3, 0, 96, 7, 0, 60, 6, 0, 30, 4, 0, 14, 4,	// 38
	224, 1, 0, 124, 0, 0, 28, 0, 0,	// 39
	0, 240, 15, 0, 255, 31, 192, 15, 32, 240, 0, 32, 56, 0, 0, 8, 0, 0, 4, 0, 0, 4, 0, 0,	// 40
	0, 0, 32, 0, 0, 32, 0, 0, 16, 0, 0, 28, 4, 0, 15, 4, 240, 3, 248, 255, 0, 240, 15, 0,	// 41
	192, 0, 0, 216, 0, 0, 88, 3, 0, 224, 3, 0, 124, 0, 0, 172, 1, 0, 176, 1, 0, 48, 0, 0,	// 42
	0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 128, 255, 7, 128, 255, 7, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0,	// 43
	0, 0, 32, 0, 0, 18, 0, 0, 15, 0, 0, 7, 0, 0, 2,	// 44
	0, 32, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 16, 0,	// 45
	0, 0, 2, 0, 0, 7, 0, 0, 7, 0, 0, 2,	// 46
	0, 0, 6, 0, 192, 7, 0, 240, 1, 0, 62, 0, 128, 15, 0, 240, 1, 0, 124, 0, 0, 12, 0, 0,	// 47
	0, 252, 1, 128, 255, 3, 224, 255, 7, 240, 3, 6, 120, 0, 4, 8, 0, 4, 4, 0, 6, 4, 192, 3, 12, 248, 1, 252, 255, 0, 248, 63, 0, 240, 7, 0,	// 48
	0, 0, 4, 0, 0, 4, 0, 0, 6, 0, 192, 7, 8, 252, 7, 200, 255, 7, 252, 63, 4, 252, 3, 4, 60, 0, 0,	// 49
	0, 0, 7, 0, 128, 7, 48, 192, 7, 56, 96, 6, 24, 48, 6, 12, 16, 6, 4, 8, 6, 4, 12, 6, 12, 6, 6, 252, 3, 7, 248, 129, 1, 240, 0, 0,	// 50
	0, 0, 3, 0, 0, 7, 48, 0, 6, 56, 0, 4, 24, 2, 4, 12, 2, 4, 4, 2, 6, 4, 135, 7, 140, 255, 3, 252, 253, 1, 248, 120, 0, 112, 0, 0,	// 51
	0, 112, 0, 0, 120, 0, 0, 78, 4, 0, 71, 4, 128, 67, 6, 224, 193, 7, 120, 248, 7, 60, 255, 7, 156, 127, 4, 204, 71, 4, 0, 64, 0,	// 52
	0, 0, 3, 0, 0, 7, 128, 3, 6, 224, 1, 4, 60, 1, 4, 12, 1, 4, 12, 1, 6, 12, 131, 7, 12, 254, 3, 12, 252, 1, 12, 120, 0, 4, 0, 0,	// 53
	0, 252, 1, 128, 255, 3, 224, 255, 7, 240, 7, 6, 120, 2, 4, 8, 2, 4, 4, 2, 6, 4, 134, 3, 4, 254, 3, 12, 252, 1, 28, 120, 0, 24, 0, 0,	// 54
	48, 0, 0, 28, 0, 0, 12, 0, 0, 12, 192, 3, 12, 240, 7, 12, 252, 3, 12, 62, 0, 140, 3, 0, 204, 0, 0, 60, 0, 0, 28, 0, 0, 12, 0, 0,	// 55
	0, 224, 1, 0, 240, 3, 224, 248, 7, 240, 13, 6, 248, 7, 4, 8, 7, 4, 4, 6, 4, 4, 14, 2, 4, 254, 3, 12, 251, 1, 248, 241, 0, 240, 0, 0,	// 56
	0, 0, 3, 192, 3, 7, 240, 7, 6, 248, 15, 4, 56, 12, 4, 12, 8, 4, 4, 8, 2, 4, 200, 3, 12, 252, 1, 252, 255, 0, 248, 63, 0, 240, 7, 0,	// 57
	0, 0, 2, 0, 0, 7, 128, 0, 7, 192, 1, 2, 192, 1, 0, 128, 0, 0,	// 58
	0, 0, 32, 0, 0, 18, 0, 0, 15, 128, 0, 7, 192, 1, 2, 192, 1, 0, 128, 0, 0,	// 59
	0, 48, 0, 0, 48, 0, 0, 120, 0, 0, 120, 0, 0, 204, 0, 0, 204, 0, 0, 134, 1, 0, 134, 1, 0, 3, 3, 0, 3, 3, 128, 1, 6, 128, 1, 6,	// 60
	0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1, 0, 140, 1,	// 61
	128, 1, 6, 128, 1, 6, 0, 3, 3, 0, 3, 3, 0, 134, 1, 0, 134, 1, 0, 204, 0, 0, 204, 0, 0, 120, 0, 0, 120, 0, 0, 48, 0, 0, 48, 0,	// 62
	48, 24, 2, 56, 60, 7, 12, 38, 7, 4, 34, 2, 4, 17, 0, 140, 1, 0, 252, 0, 0, 120, 0, 0,	// 63
	0, 63, 0, 192, 255, 0, 96, 128, 1, 48, 0, 3, 24, 60, 2, 8, 127, 6, 140, 67, 4, 132, 64, 4, 68, 32, 4, 68, 16, 4, 68, 60, 4, 196, 127, 4, 204, 67, 6, 8, 96, 2, 24, 48, 0, 112, 28, 0, 192, 7, 0,	// 64
	0, 0, 4, 0, 0, 4, 0, 0, 6, 0, 0, 7, 0, 192, 4, 0, 48, 4, 0, 24, 0, 0, 22, 0, 128, 17, 0, 96, 16, 0, 248, 16, 4, 252, 63, 4, 252, 255, 7, 0, 255, 7, 0, 192, 7, 0, 0, 4, 0, 0, 4,	// 65
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 4, 4, 12, 4, 4, 4, 4, 4, 4, 4, 6, 4, 14, 7, 12, 251, 3, 252, 251, 3, 248, 241, 1, 240, 0, 0,	// 66
	0, 126, 0, 192, 255, 1, 224, 255, 3, 240, 129, 3, 56, 0, 6, 24, 0, 4, 12, 0, 4, 12, 0, 4, 4, 0, 4, 4, 0, 4, 4, 0, 4, 4, 0, 2, 4, 0, 3, 12, 128, 3, 124, 192, 0, 24, 0, 0,	// 67
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 0, 4, 12, 0, 4, 4, 0, 4, 4, 0, 4, 4, 0, 6, 4, 0, 6, 4, 0, 3, 12, 128, 3, 56, 240, 1, 248, 255, 0, 240, 127, 0, 192, 15, 0,	// 68
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 4, 4, 12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 28, 6, 4, 7, 7, 60, 128, 1, 12, 0, 0,	// 69
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 4, 4, 12, 4, 0, 4, 4, 0, 4, 4, 0, 4, 28, 0, 4, 7, 0, 60, 0, 0, 12, 0, 0,	// 70
	0, 126, 0, 192, 255, 1, 224, 255, 3, 240, 129, 3, 56, 0, 6, 24, 0, 4, 12, 0, 4, 12, 0, 4, 4, 0, 4, 4, 0, 4, 4, 16, 6, 4, 144, 7, 4, 240, 3, 12, 240, 3, 124, 112, 0, 24, 16, 0, 0, 16, 0,	// 71
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 4, 0, 12, 4, 0, 4, 4, 0, 4, 4, 4, 0, 4, 4, 0, 4, 6, 4, 228, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 0, 4, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 72
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 0, 4, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 73
	0, 0, 64, 0, 0, 64, 0, 0, 96, 0, 0, 60, 4, 224, 63, 132, 255, 31, 252, 255, 3, 252, 31, 0, 124, 0, 0, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 74
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 8, 4, 12, 28, 0, 4, 62, 0, 4, 121, 0, 128, 240, 1, 64, 224, 3, 36, 192, 7, 28, 0, 7, 12, 0, 6, 4, 0, 4, 4, 0, 4,	// 75
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 0, 4, 12, 0, 4, 4, 0, 4, 4, 0, 4, 0, 0, 6, 0, 0, 7, 0, 128, 1,	// 76
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 4, 63, 4, 252, 1, 4, 60, 0, 0, 252, 3, 0, 252, 63, 0, 192, 255, 3, 0, 252, 7, 0, 192, 3, 0, 192, 0, 0, 48, 0, 0, 24, 4, 0, 6, 4, 0, 3, 6, 192, 192, 7, 96, 254, 7, 248, 255, 7, 252, 63, 4, 252, 1, 4, 12, 0, 0,	// 77
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 4, 63, 4, 252, 1, 4, 28, 0, 0, 124, 0, 0, 252, 1, 0, 240, 7, 0, 192, 31, 0, 0, 127, 0, 0, 252, 1, 0, 240, 7, 0, 192, 7, 4, 224, 7, 4, 63, 0, 252, 1, 0, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 78
	0, 126, 0, 192, 255, 1, 224, 255, 3, 240, 129, 3, 56, 0, 6, 24, 0, 4, 12, 0, 4, 12, 0, 4, 4, 0, 4, 4, 0, 6, 4, 0, 6, 4, 0, 3, 12, 128, 3, 56, 240, 1, 248, 255, 0, 240, 127, 0, 192, 15, 0,	// 79
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 4, 4, 12, 4, 0, 4, 4, 0, 4, 4, 0, 4, 6, 0, 12, 3, 0, 252, 3, 0, 248, 1, 0, 240, 0, 0,	// 80
	0, 126, 0, 192, 255, 1, 224, 255, 3, 240, 129, 3, 56, 0, 6, 24, 0, 4, 12, 0, 4, 12, 0, 12, 4, 0, 60, 4, 0, 126, 4, 0, 118, 4, 0, 227, 12, 128, 195, 56, 240, 129, 248, 255, 128, 240, 127, 0, 192, 15, 0,	// 81
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 4, 4, 12, 4, 0, 4, 4, 0, 4, 28, 0, 4, 254, 1, 12, 251, 7, 252, 243, 7, 248, 1, 7, 240, 0, 4, 0, 0, 4,	// 82
	0, 0, 3, 0, 192, 7, 224, 1, 6, 248, 3, 4, 248, 7, 4, 12, 7, 4, 4, 14, 4, 4, 30, 6, 4, 252, 3, 4, 248, 3, 12, 240, 0, 124, 0, 0, 24, 0, 0,	// 83
	28, 0, 4, 12, 0, 4, 4, 0, 6, 4, 224, 7, 132, 255, 7, 252, 255, 7, 252, 31, 4, 124, 0, 4, 12, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 12, 0, 0, 28, 0, 0,	// 84
	4, 240, 1, 132, 255, 3, 252, 255, 7, 252, 15, 6, 124, 0, 4, 12, 0, 4, 4, 0, 4, 4, 0, 4, 0, 0, 6, 0, 0, 7, 4, 224, 3, 4, 255, 1, 252, 255, 0, 252, 31, 0, 252, 0, 0, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 85
	4, 0, 0, 4, 0, 0, 252, 0, 0, 252, 63, 0, 252, 255, 7, 4, 255, 7, 4, 192, 3, 0, 192, 0, 0, 48, 0, 0, 12, 0, 0, 2, 0, 132, 1, 0, 100, 0, 0, 28, 0, 0, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 86
	4, 0, 0, 4, 0, 0, 252, 3, 0, 252, 255, 7, 252, 255, 7, 4, 252, 1, 4, 96, 0, 0, 24, 0, 0, 6, 0, 128, 1, 0, 96, 0, 0, 252, 3, 0, 252, 255, 7, 252, 255, 7, 0, 252, 1, 0, 96, 0, 0, 24, 0, 0, 6, 0, 132, 1, 0, 100, 0, 0, 28, 0, 0,	// 87
	0, 0, 4, 0, 0, 4, 0, 0, 6, 4, 0, 7, 4, 128, 7, 28, 192, 4, 124, 48, 0, 252, 25, 0, 228, 15, 0, 128, 31, 0, 0, 127, 4, 128, 249, 5, 228, 224, 7, 60, 128, 7, 28, 0, 6, 12, 0, 4, 4, 0, 4, 4, 0, 0,	// 88
	4, 0, 0, 4, 0, 4, 12, 0, 4, 124, 0, 6, 252, 199, 7, 252, 255, 7, 132, 255, 7, 4, 60, 4, 0, 12, 4, 0, 3, 0, 128, 1, 0, 196, 0, 0, 52, 0, 0, 28, 0, 0, 12, 0, 0, 4, 0, 0, 4, 0, 0,	// 89
	0, 0, 6, 0, 0, 7, 0, 128, 7, 60, 192, 7, 12, 224, 5, 4, 248, 4, 4, 60, 4, 4, 30, 4, 4, 15, 4, 196, 7, 4, 228, 3, 4, 244, 0, 6, 124, 0, 7, 60, 128, 1, 28, 0, 0, 12, 0, 0,	// 90
	0, 0, 60, 0, 192, 63, 0, 252, 33, 192, 31, 32, 252, 1, 0, 28, 0, 0, 4, 0, 0, 4, 0, 0,	// 91
	12, 0, 0, 124, 0, 0, 240, 1, 0, 128, 15, 0, 0, 62, 0, 0, 240, 1, 0, 192, 7, 0, 0, 6,	// 92
	0, 0, 32, 0, 0, 32, 0, 0, 56, 0, 128, 63, 4, 248, 3, 132, 63, 0, 252, 3, 0, 60, 0, 0,	// 93
	0, 12, 0, 0, 15, 0, 192, 3, 0, 240, 0, 0, 60, 0, 0, 60, 0, 0, 240, 0, 0, 192, 3, 0, 0, 15, 0, 0, 12, 0,	// 94
	0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64,	// 95
	2, 0, 0, 7, 0, 0, 6, 0, 0, 12, 0, 0, 8, 0, 0, 16, 0, 0,	// 96
	0, 248, 1, 0, 254, 3, 0, 255, 7, 128, 15, 4, 128, 3, 4, 192, 0, 2, 64, 0, 1, 64, 192, 3, 128, 252, 7, 192, 255, 7, 192, 63, 4, 192, 3, 2, 0, 0, 1,	// 97
	0, 128, 7, 2, 254, 7, 242, 255, 7, 255, 63, 2, 255, 3, 4, 15, 1, 4, 128, 0, 6, 64, 128, 3, 64, 224, 3, 192, 255, 1, 128, 255, 0, 0, 63, 0,	// 98
	0, 248, 1, 0, 254, 3, 0, 255, 7, 128, 15, 6, 128, 3, 4, 192, 0, 4, 64, 0, 4, 64, 0, 2, 192, 0, 1, 192, 3, 0, 128, 1, 0,	// 99
	0, 248, 1, 0, 254, 3, 0, 255, 7, 128, 15, 4, 128, 3, 4, 192, 0, 2, 64, 0, 1, 64, 192, 3, 66, 252, 7, 226, 255, 7, 255, 63, 4, 255, 3, 2, 31, 0, 1,	// 100
	0, 248, 1, 0, 254, 3, 0, 255, 7, 128, 47, 6, 128, 35, 4, 192, 16, 4, 64, 16, 4, 64, 12, 2, 192, 15, 1, 192, 7, 0, 128, 3, 0,	// 101
	0, 0, 64, 0, 0, 224, 0, 0, 192, 0, 0, 128, 0, 0, 127, 64, 248, 63, 192, 255, 31, 248, 255, 0, 252, 7, 0, 126, 0, 0, 65, 0, 0, 67, 0, 0, 7, 0, 0, 2, 0, 0,	// 102
	0, 0, 112, 0, 0, 120, 0, 0, 252, 0, 142, 199, 0, 223, 131, 128, 255, 131, 192, 48, 131, 64, 32, 135, 64, 32, 70, 192, 48, 126, 192, 31, 62, 128, 15, 28, 192, 7, 0, 64, 0, 0,	// 103
	0, 128, 7, 2, 252, 7, 226, 255, 7, 255, 127, 0, 255, 11, 0, 31, 4, 0, 0, 2, 0, 0, 1, 0, 128, 128, 3, 64, 248, 7, 192, 255, 7, 192, 127, 4, 128, 7, 2, 0, 0, 1,	// 104
	128, 192, 3, 128, 252, 7, 196, 255, 7, 206, 63, 4, 206, 3, 2, 4, 0, 1,	// 105
	0, 0, 64, 0, 0, 224, 0, 0, 192, 0, 0, 128, 128, 0, 127, 128, 248, 63, 196, 255, 31, 206, 255, 0, 206, 7, 0, 4, 0, 0,	// 106
	0, 128, 7, 2, 252, 7, 226, 255, 7, 255, 127, 0, 255, 19, 0, 31, 48, 0, 0, 120, 0, 0, 252, 1, 0, 226, 3, 0, 129, 7, 128, 1, 7, 192, 1, 2, 128, 0, 1,	// 107
	0, 192, 3, 2, 254, 7, 242, 255, 7, 255, 63, 4, 255, 1, 2, 15, 0, 1,	// 108
	128, 128, 7, 128, 252, 7, 192, 255, 7, 192, 127, 0, 192, 11, 0, 0, 4, 0, 0, 2, 0, 0, 1, 0, 128, 128, 7, 64, 240, 7, 192, 255, 7, 192, 127, 0, 128, 15, 0, 0, 4, 0, 0, 2, 0, 0, 1, 0, 128, 128, 3, 64, 248, 7, 192, 255, 7, 192, 127, 4, 128, 7, 2,	// 109
	128, 128, 7, 128, 252, 7, 192, 255, 7, 192, 127, 0, 192, 11, 0, 0, 4, 0, 0, 2, 0, 0, 1, 0, 128, 128, 3, 64, 248, 7, 192, 255, 7, 192, 127, 4, 128, 7, 2, 0, 0, 1,	// 110
	0, 248, 1, 0, 254, 3, 0, 255, 7, 128, 15, 6, 128, 3, 4, 192, 0, 4, 64, 0, 6, 64, 128, 3, 192, 224, 3, 192, 255, 1, 128, 255, 0, 0, 63, 0,	// 111
	0, 0, 240, 128, 128, 255, 128, 252, 255, 192, 255, 15, 192, 127, 2, 192, 3, 4, 0, 1, 4, 128, 0, 6, 64, 128, 3, 64, 224, 3, 192, 255, 1, 128, 255, 0, 0, 63, 0,	// 112
	0, 248, 1, 0, 254, 3, 0, 255, 7, 128, 15, 4, 128, 3, 4, 192, 0, 2, 64, 0, 241, 64, 128, 255, 128, 252, 255, 128, 255, 15, 192, 127, 0, 224, 3, 0,	// 113
	128, 128, 7, 128, 248, 7, 192, 255, 7, 192, 127, 0, 192, 7, 0, 0, 1, 0, 128, 1, 0, 192, 1, 0, 192, 1, 0, 128, 0, 0,	// 114
	0, 0, 3, 0, 0, 7, 0, 15, 6, 128, 31, 4, 192, 60, 4, 64, 120, 6, 64, 240, 3, 192, 224, 1, 192, 1, 0, 128, 1, 0,	// 115
	64, 192, 3, 64, 254, 7, 224, 255, 7, 240, 63, 4, 248, 1, 2, 64, 0, 1, 64, 128, 0, 64, 0, 0,	// 116
	128, 192, 3, 128, 252, 7, 192, 255, 7, 192, 63, 4, 192, 3, 2, 0, 0, 1, 0, 128, 0, 0, 64, 0, 0, 160, 3, 0, 252, 7, 192, 255, 7, 192, 127, 4, 192, 3, 2, 0, 128, 1,	// 117
	128, 192, 3, 128, 252, 7, 192, 255, 7, 192, 63, 4, 192, 3, 4, 0, 0, 2, 0, 0, 1, 0, 128, 0, 0, 96, 0, 128, 60, 0, 192, 31, 0, 192, 3, 0,	// 118
	128, 192, 3, 128, 252, 7, 192, 255, 7, 192, 63, 4, 192, 3, 4, 0, 0, 2, 0, 0, 1, 0, 128, 0, 0, 252, 3, 192, 255, 7, 192, 63, 4, 192, 3, 4, 0, 0, 2, 0, 0, 1, 0, 128, 0, 0, 96, 0, 128, 60, 0, 192, 31, 0, 192, 3, 0,	// 119
	0, 0, 7, 0, 0, 6, 128, 0, 3, 128, 128, 1, 192, 195, 0, 192, 127, 0, 192, 255, 3, 0, 252, 7, 0, 134, 7, 0, 3, 4, 128, 1, 2, 192, 0, 1, 192, 1, 0,	// 120
	0, 0, 64, 0, 0, 224, 128, 0, 192, 128, 0, 128, 192, 7, 64, 192, 255, 63, 192, 255, 31, 0, 248, 7, 0, 128, 1, 0, 96, 0, 0, 24, 0, 0, 6, 0, 192, 1, 0, 192, 0, 0,	// 121
	0, 0, 6, 0, 0, 7, 0, 131, 1, 192, 193, 1, 192, 160, 3, 192, 144, 3, 192, 8, 7, 192, 4, 7, 192, 2, 6, 192, 1, 2, 192, 128, 1, 64, 0, 0,	// 122
	0, 8, 0, 0, 8, 31, 0, 252, 63, 192, 231, 32, 248, 3, 32, 60, 0, 0, 4, 0, 0, 4, 0, 0,	// 123
	252, 255, 7, 252, 255, 7,	// 124
	0, 0, 32, 0, 0, 32, 0, 0, 62, 4, 224, 31, 132, 243, 1, 252, 31, 0, 120, 8, 0, 0, 8, 0,	// 125
	0, 32, 0, 0, 16, 0, 0, 24, 0, 0, 24, 0, 0, 24, 0, 0, 16, 0, 0, 48, 0, 0, 48, 0, 0, 48, 0, 0, 16, 0, 0, 8, 0,	// 126
		// 127

    }
};

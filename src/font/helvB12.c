
// file: font/helvB12.bdf
// font: -Adobe-Helvetica-Bold-R-Normal--12-120-75-75-P-70-ISO10646-1

#include <font.h>

const struct Font font_helvB12 = {
    .type       = 1,
    .name	= "helvB12",
    .height	= 12,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 0 }, // 33 [3]
	{ .l0 = 2, .r0 = 6, .ncol = 3, .xadj = -6, .pos = 3 }, // 34 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 8 }, // 35 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 19 }, // 36 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 10, .xadj = 1, .pos = 28 }, // 37 [15]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -2, .pos = 43 }, // 38 [14]
	{ .l0 = 2, .r0 = 8, .ncol = 1, .xadj = -8, .pos = 57 }, // 39 [2]
	{ .l0 = 2, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 59 }, // 40 [6]
	{ .l0 = 2, .r0 = 5, .ncol = 4, .xadj = -5, .pos = 65 }, // 41 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 71 }, // 42 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 79 }, // 43 [9]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 88 }, // 44 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 91 }, // 45 [6]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 97 }, // 46 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -7, .pos = 100 }, // 47 [6]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 106 }, // 48 [9]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -4, .pos = 115 }, // 49 [6]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 121 }, // 50 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 130 }, // 51 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 139 }, // 52 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 150 }, // 53 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 159 }, // 54 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 168 }, // 55 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 177 }, // 56 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 186 }, // 57 [9]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 195 }, // 58 [3]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 198 }, // 59 [3]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 201 }, // 60 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 209 }, // 61 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 218 }, // 62 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 226 }, // 63 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 9, .xadj = 1, .pos = 235 }, // 64 [14]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 249 }, // 65 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 261 }, // 66 [11]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 272 }, // 67 [11]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 283 }, // 68 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -3, .pos = 294 }, // 69 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 303 }, // 70 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 312 }, // 71 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 324 }, // 72 [11]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 335 }, // 73 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 338 }, // 74 [9]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 347 }, // 75 [12]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 359 }, // 76 [9]
	{ .l0 = 2, .r0 = 0, .ncol = 9, .xadj = 0, .pos = 368 }, // 77 [14]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 382 }, // 78 [11]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 393 }, // 79 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 405 }, // 80 [11]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 416 }, // 81 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 428 }, // 82 [11]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 439 }, // 83 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 450 }, // 84 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -2, .pos = 462 }, // 85 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 473 }, // 86 [12]
	{ .l0 = 1, .r0 = 0, .ncol = 10, .xadj = -1, .pos = 485 }, // 87 [15]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 500 }, // 88 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 512 }, // 89 [12]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 524 }, // 90 [11]
	{ .l0 = 2, .r0 = 6, .ncol = 3, .xadj = -7, .pos = 535 }, // 91 [5]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -7, .pos = 540 }, // 92 [6]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 546 }, // 93 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 551 }, // 94 [11]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 562 }, // 95 [11]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 573 }, // 96 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 578 }, // 97 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 589 }, // 98 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 598 }, // 99 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 607 }, // 100 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 616 }, // 101 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 625 }, // 102 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 633 }, // 103 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 642 }, // 104 [9]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 651 }, // 105 [3]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 654 }, // 106 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 659 }, // 107 [11]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 670 }, // 108 [3]
	{ .l0 = 1, .r0 = 0, .ncol = 10, .xadj = 0, .pos = 673 }, // 109 [15]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 688 }, // 110 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 697 }, // 111 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 706 }, // 112 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 715 }, // 113 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 724 }, // 114 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 732 }, // 115 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 741 }, // 116 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 749 }, // 117 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 758 }, // 118 [11]
	{ .l0 = 1, .r0 = 0, .ncol = 10, .xadj = 0, .pos = 769 }, // 119 [15]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 784 }, // 120 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 793 }, // 121 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 804 }, // 122 [8]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 812 }, // 123 [6]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -7, .pos = 818 }, // 124 [3]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 821 }, // 125 [6]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 827 }, // 126 [11]
	{ .l0 = 11, .r0 = 0, .ncol = 0, .xadj = -11, .pos = 838 }, // 127 [0]
    },
    .data       = {
	191, 241, 25,	// 33
	7, 0, 0, 7, 0,	// 34
	64, 128, 28, 120, 224, 28, 120, 224, 4, 8, 0,	// 35
	204, 224, 25, 18, 241, 127, 50, 65, 14,	// 36
	6, 240, 0, 9, 240, 24, 230, 128, 1, 198, 48, 30, 32, 1, 30,	// 37
	224, 96, 31, 31, 145, 17, 191, 97, 14, 224, 0, 27, 0, 1,	// 38
	7, 0,	// 39
	248, 225, 127, 7, 30, 128,	// 40
	1, 120, 224, 254, 135, 31,	// 41
	2, 224, 0, 7, 224, 0, 2, 0,	// 42
	32, 0, 2, 248, 128, 15, 32, 0, 2,	// 43
	128, 5, 56,	// 44
	32, 0, 2, 32, 0, 2,	// 45
	128, 1, 24,	// 46
	128, 129, 31, 31, 48, 0,	// 47
	254, 240, 31, 1, 17, 16, 255, 225, 15,	// 48
	2, 32, 0, 255, 241, 31,	// 49
	194, 49, 30, 49, 145, 17, 15, 97, 16,	// 50
	130, 48, 24, 9, 145, 16, 255, 97, 15,	// 51
	96, 0, 5, 76, 32, 4, 255, 241, 31, 64, 0,	// 52
	204, 240, 28, 11, 145, 16, 249, 17, 15,	// 53
	254, 240, 31, 17, 17, 17, 243, 33, 14,	// 54
	1, 16, 24, 241, 209, 7, 15, 48, 0,	// 55
	246, 240, 31, 9, 145, 16, 255, 97, 15,	// 56
	142, 240, 25, 17, 17, 17, 255, 225, 15,	// 57
	140, 193, 24,	// 58
	140, 197, 56,	// 59
	32, 0, 7, 80, 128, 13, 136, 0,	// 60
	80, 0, 5, 80, 0, 5, 80, 0, 5,	// 61
	136, 128, 13, 80, 0, 7, 32, 0,	// 62
	6, 112, 0, 177, 145, 27, 15, 96, 0,	// 63
	248, 96, 16, 98, 18, 41, 137, 146, 36, 241, 146, 8, 66, 0,	// 64
	192, 129, 31, 62, 48, 2, 35, 224, 3, 248, 1, 28,	// 65
	255, 241, 31, 17, 17, 17, 17, 241, 31, 238, 0,	// 66
	124, 224, 15, 131, 17, 16, 1, 49, 24, 130, 0,	// 67
	255, 241, 31, 1, 17, 16, 131, 225, 15, 124, 0,	// 68
	255, 241, 31, 17, 17, 17, 17, 17, 17,	// 69
	255, 241, 31, 17, 16, 1, 17, 16, 0,	// 70
	124, 224, 15, 131, 17, 16, 17, 17, 17, 243, 32, 31,	// 71
	255, 241, 31, 16, 0, 1, 16, 240, 31, 255, 1,	// 72
	255, 241, 31,	// 73
	192, 0, 28, 0, 1, 16, 255, 241, 15,	// 74
	255, 241, 31, 24, 192, 3, 102, 48, 12, 129, 1, 16,	// 75
	255, 241, 31, 0, 1, 16, 0, 1, 16,	// 76
	255, 241, 31, 28, 0, 7, 192, 1, 7, 28, 240, 31, 255, 1,	// 77
	255, 241, 31, 6, 128, 1, 96, 240, 31, 255, 1,	// 78
	124, 224, 15, 131, 17, 16, 1, 49, 24, 254, 192, 7,	// 79
	255, 241, 31, 17, 16, 1, 17, 240, 1, 14, 0,	// 80
	124, 224, 15, 131, 17, 16, 97, 49, 28, 254, 193, 23,	// 81
	255, 241, 31, 17, 16, 1, 49, 240, 31, 206, 1,	// 82
	198, 240, 28, 9, 145, 17, 49, 113, 31, 230, 0,	// 83
	1, 16, 0, 1, 240, 31, 255, 17, 0, 1, 16, 0,	// 84
	127, 240, 31, 128, 1, 16, 128, 241, 31, 127, 0,	// 85
	3, 240, 1, 124, 0, 28, 192, 193, 7, 31, 48, 0,	// 86
	7, 240, 3, 240, 1, 28, 63, 240, 3, 192, 1, 31, 63, 112, 0,	// 87
	131, 113, 28, 108, 128, 3, 56, 192, 6, 199, 49, 24,	// 88
	3, 240, 0, 28, 0, 31, 240, 193, 1, 15, 48, 0,	// 89
	129, 17, 28, 113, 145, 19, 13, 113, 16, 3, 1,	// 90
	255, 255, 255, 1, 8,	// 91
	3, 240, 1, 248, 1, 24,	// 92
	1, 248, 255, 255, 15,	// 93
	8, 192, 0, 6, 48, 0, 6, 192, 0, 8, 0,	// 94
	0, 8, 128, 0, 8, 128, 0, 8, 128, 0, 8,	// 95
	1, 48, 0, 2, 0,	// 96
	200, 192, 30, 36, 65, 18, 252, 128, 31, 0, 1,	// 97
	255, 241, 31, 136, 64, 16, 252, 129, 15,	// 98
	248, 192, 31, 4, 65, 16, 140, 129, 8,	// 99
	248, 192, 31, 4, 129, 8, 255, 241, 31,	// 100
	248, 192, 31, 36, 65, 18, 188, 129, 11,	// 101
	4, 224, 31, 255, 81, 0, 1, 0,	// 102
	248, 196, 223, 4, 137, 136, 252, 207, 127,	// 103
	255, 241, 31, 8, 64, 0, 252, 129, 31,	// 104
	253, 209, 31,	// 105
	0, 216, 255, 253, 7,	// 106
	255, 241, 31, 48, 128, 7, 204, 64, 24, 0, 1,	// 107
	255, 241, 31,	// 108
	252, 129, 31, 4, 64, 0, 252, 129, 31, 4, 64, 0, 252, 129, 31,	// 109
	252, 193, 31, 8, 64, 0, 252, 129, 31,	// 110
	248, 192, 31, 4, 65, 16, 252, 129, 15,	// 111
	252, 207, 255, 136, 64, 16, 252, 129, 15,	// 112
	248, 192, 31, 4, 193, 8, 248, 207, 255,	// 113
	252, 193, 31, 24, 192, 0, 12, 0,	// 114
	152, 192, 25, 52, 65, 22, 236, 129, 12,	// 115
	4, 240, 15, 255, 65, 16, 128, 0,	// 116
	252, 192, 31, 0, 1, 8, 252, 193, 31,	// 117
	12, 192, 3, 240, 0, 28, 240, 192, 3, 12, 0,	// 118
	12, 192, 7, 240, 1, 24, 124, 192, 7, 128, 1, 31, 124, 192, 0,	// 119
	140, 193, 29, 112, 0, 7, 220, 193, 24,	// 120
	12, 192, 131, 240, 12, 124, 240, 193, 3, 12, 0,	// 121
	132, 65, 28, 116, 193, 17, 12, 1,	// 122
	32, 224, 127, 223, 31, 128,	// 123
	255, 255, 255,	// 124
	1, 248, 253, 254, 7, 2,	// 125
	32, 0, 3, 16, 0, 3, 32, 0, 3, 16, 0,	// 126
		// 127

    }
};

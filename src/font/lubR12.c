
// file: font/lubR12.bdf
// font: -B&H-LucidaBright-Medium-R-Normal--12-120-75-75-P-68-ISO10646-1

#include <font.h>

const struct Font font_lubR12 = {
    .type       = 1,
    .name	= "lubR12",
    .height	= 11,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -6, .pos = 2 }, // 34 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 5 }, // 35 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 15 }, // 36 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 22 }, // 37 [9]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 31 }, // 38 [11]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -8, .pos = 42 }, // 39 [5]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 47 }, // 40 [5]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 52 }, // 41 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -5, .pos = 57 }, // 42 [7]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 64 }, // 43 [10]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 74 }, // 44 [2]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 76 }, // 45 [5]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 81 }, // 46 [2]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 83 }, // 47 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 92 }, // 48 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 101 }, // 49 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 108 }, // 50 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 115 }, // 51 [7]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 122 }, // 52 [9]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 131 }, // 53 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 138 }, // 54 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 147 }, // 55 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 156 }, // 56 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 165 }, // 57 [9]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 174 }, // 58 [2]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 176 }, // 59 [2]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 178 }, // 60 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 188 }, // 61 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 198 }, // 62 [10]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -5, .pos = 208 }, // 63 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 10, .xadj = -1, .pos = 215 }, // 64 [14]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 229 }, // 65 [13]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 242 }, // 66 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 251 }, // 67 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -2, .pos = 261 }, // 68 [11]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 272 }, // 69 [9]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 281 }, // 70 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 290 }, // 71 [11]
	{ .l0 = 0, .r0 = 2, .ncol = 9, .xadj = -2, .pos = 301 }, // 72 [13]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 314 }, // 73 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -6, .pos = 319 }, // 74 [7]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 326 }, // 75 [11]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 337 }, // 76 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 10, .xadj = -1, .pos = 346 }, // 77 [14]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 360 }, // 78 [11]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 371 }, // 79 [11]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 382 }, // 80 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 10, .xadj = -2, .pos = 391 }, // 81 [14]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 405 }, // 82 [11]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 416 }, // 83 [7]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -3, .pos = 423 }, // 84 [10]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -2, .pos = 433 }, // 85 [11]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 444 }, // 86 [11]
	{ .l0 = 0, .r0 = 0, .ncol = 11, .xadj = 0, .pos = 455 }, // 87 [16]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 471 }, // 88 [11]
	{ .l0 = 0, .r0 = 3, .ncol = 8, .xadj = -3, .pos = 482 }, // 89 [11]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -3, .pos = 493 }, // 90 [9]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 502 }, // 91 [3]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 505 }, // 92 [9]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -7, .pos = 514 }, // 93 [3]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 517 }, // 94 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 527 }, // 95 [7]
	{ .l0 = 2, .r0 = 6, .ncol = 3, .xadj = -4, .pos = 534 }, // 96 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -4, .pos = 539 }, // 97 [9]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 548 }, // 98 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 558 }, // 99 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 565 }, // 100 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 575 }, // 101 [7]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -6, .pos = 582 }, // 102 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 589 }, // 103 [9]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -3, .pos = 598 }, // 104 [10]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 608 }, // 105 [5]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 613 }, // 106 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 618 }, // 107 [10]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 628 }, // 108 [5]
	{ .l0 = 0, .r0 = 0, .ncol = 11, .xadj = 0, .pos = 633 }, // 109 [16]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -3, .pos = 649 }, // 110 [10]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 659 }, // 111 [9]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -3, .pos = 668 }, // 112 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 678 }, // 113 [10]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 688 }, // 114 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 694 }, // 115 [7]
	{ .l0 = 0, .r0 = 7, .ncol = 4, .xadj = -6, .pos = 701 }, // 116 [6]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -3, .pos = 707 }, // 117 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 717 }, // 118 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 10, .xadj = -1, .pos = 727 }, // 119 [14]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 741 }, // 120 [10]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 751 }, // 121 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -4, .pos = 761 }, // 122 [7]
	{ .l0 = 0, .r0 = 8, .ncol = 3, .xadj = -7, .pos = 768 }, // 123 [5]
	{ .l0 = 1, .r0 = 9, .ncol = 1, .xadj = -8, .pos = 773 }, // 124 [2]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 775 }, // 125 [5]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 780 }, // 126 [10]
	{ .l0 = 11, .r0 = 0, .ncol = 0, .xadj = -11, .pos = 790 }, // 127 [0]
    },
    .data       = {
	127, 1,	// 33
	7, 56, 0,	// 34
	32, 32, 143, 15, 74, 195, 135, 19, 16, 0,	// 35
	206, 209, 200, 255, 34, 50, 14,	// 36
	6, 73, 134, 13, 240, 97, 145, 112, 0,	// 37
	240, 112, 76, 66, 114, 98, 28, 72, 192, 5, 34,	// 38
	3, 56, 192, 0, 0,	// 39
	252, 17, 80, 0, 1,	// 40
	1, 20, 16, 127, 0,	// 41
	2, 112, 192, 0, 28, 32, 0,	// 42
	32, 0, 1, 8, 252, 3, 2, 16, 128, 0,	// 43
	0, 7,	// 44
	32, 0, 1, 8, 0,	// 45
	0, 1,	// 46
	0, 4, 28, 56, 112, 224, 128, 0, 0,	// 47
	124, 16, 68, 64, 2, 34, 8, 62, 0,	// 48
	1, 9, 200, 127, 0, 2, 16,	// 49
	134, 9, 74, 72, 34, 226, 16,	// 50
	131, 137, 72, 68, 34, 226, 14,	// 51
	48, 192, 1, 9, 70, 242, 31, 144, 0,	// 52
	143, 73, 72, 66, 50, 19, 15,	// 53
	124, 144, 68, 66, 18, 146, 152, 121, 0,	// 54
	129, 9, 71, 12, 50, 80, 128, 1, 0,	// 55
	230, 200, 76, 68, 34, 146, 27, 115, 0,	// 56
	158, 25, 73, 72, 66, 34, 9, 62, 0,	// 57
	8, 1,	// 58
	136, 7,	// 59
	16, 128, 1, 30, 144, 64, 8, 66, 8, 4,	// 60
	80, 128, 2, 20, 160, 0, 5, 40, 64, 1,	// 61
	2, 33, 4, 33, 144, 128, 7, 24, 128, 0,	// 62
	7, 8, 64, 92, 50, 96, 0,	// 63
	120, 32, 132, 96, 228, 210, 148, 190, 244, 37, 9, 98, 224, 1,	// 64
	0, 1, 14, 14, 92, 112, 2, 30, 192, 5, 48, 0, 1,	// 65
	1, 249, 79, 68, 34, 146, 19, 115, 0,	// 66
	124, 16, 70, 96, 2, 18, 144, 128, 28, 2,	// 67
	1, 249, 79, 64, 2, 18, 144, 128, 8, 130, 15,	// 68
	1, 249, 79, 68, 34, 146, 147, 193, 0,	// 69
	1, 249, 79, 68, 34, 144, 131, 1, 0,	// 70
	124, 16, 70, 96, 2, 18, 144, 144, 156, 7, 4,	// 71
	1, 249, 79, 68, 32, 0, 1, 8, 68, 228, 63, 1, 1,	// 72
	1, 249, 79, 64, 0,	// 73
	0, 6, 96, 0, 255, 23, 0,	// 74
	1, 249, 79, 68, 80, 80, 148, 225, 4, 6, 32,	// 75
	1, 249, 79, 64, 0, 2, 16, 192, 0,	// 76
	1, 249, 207, 65, 56, 0, 14, 48, 96, 224, 32, 255, 9, 8,	// 77
	1, 249, 143, 65, 16, 0, 131, 32, 252, 39, 0,	// 78
	124, 16, 68, 64, 2, 18, 144, 128, 8, 130, 15,	// 79
	1, 249, 79, 68, 34, 144, 1, 7, 0,	// 80
	124, 16, 68, 64, 2, 18, 144, 128, 9, 142, 143, 0, 4, 32,	// 81
	1, 249, 79, 68, 34, 16, 7, 103, 0, 4, 32,	// 82
	206, 73, 72, 68, 98, 114, 14,	// 83
	1, 8, 64, 64, 254, 19, 144, 0, 4, 0,	// 84
	1, 248, 71, 96, 0, 2, 144, 192, 252, 35, 0,	// 85
	1, 56, 64, 6, 192, 1, 24, 56, 60, 96, 0,	// 86
	1, 56, 64, 30, 128, 195, 131, 3, 240, 0, 56, 112, 120, 64, 0, 0,	// 87
	1, 25, 206, 25, 114, 128, 3, 166, 12, 38, 32,	// 88
	1, 24, 64, 67, 240, 131, 145, 6, 28, 32, 0,	// 89
	3, 9, 78, 76, 26, 114, 144, 192, 0,	// 90
	255, 15, 32,	// 91
	1, 112, 0, 14, 192, 1, 56, 0, 2,	// 92
	1, 252, 63,	// 93
	192, 128, 3, 3, 6, 192, 0, 56, 0, 3,	// 94
	0, 2, 16, 128, 0, 4, 32,	// 95
	1, 8, 64, 0, 0,	// 96
	200, 64, 9, 74, 80, 2, 31, 128, 0,	// 97
	1, 248, 15, 66, 16, 130, 16, 140, 192, 3,	// 98
	240, 192, 12, 66, 16, 130, 17,	// 99
	240, 64, 12, 66, 16, 146, 144, 255, 0, 4,	// 100
	240, 64, 13, 74, 80, 2, 19,	// 101
	8, 249, 79, 66, 18, 50, 0,	// 102
	176, 67, 42, 82, 145, 138, 83, 132, 1,	// 103
	1, 249, 15, 66, 16, 128, 16, 252, 0, 4,	// 104
	8, 201, 15, 64, 0,	// 105
	0, 70, 96, 254, 1,	// 106
	1, 249, 15, 72, 224, 128, 9, 132, 32, 4,	// 107
	1, 249, 15, 64, 0,	// 108
	8, 193, 15, 66, 16, 128, 16, 252, 32, 4, 1, 8, 193, 15, 64, 0,	// 109
	8, 193, 15, 66, 16, 128, 16, 252, 0, 4,	// 110
	240, 192, 12, 66, 16, 130, 25, 120, 0,	// 111
	8, 196, 63, 66, 17, 130, 16, 140, 192, 3,	// 112
	240, 64, 12, 66, 16, 130, 80, 252, 3, 16,	// 113
	8, 193, 15, 66, 48, 0,	// 114
	240, 65, 9, 90, 144, 130, 15,	// 115
	8, 240, 15, 66, 16, 2,	// 116
	8, 192, 15, 64, 0, 130, 16, 252, 0, 4,	// 117
	8, 192, 1, 26, 0, 3, 12, 28, 96, 0,	// 118
	8, 192, 1, 114, 128, 1, 3, 28, 0, 3, 48, 120, 192, 0,	// 119
	8, 193, 12, 30, 192, 0, 30, 204, 32, 4,	// 120
	8, 192, 33, 26, 1, 7, 12, 60, 96, 0,	// 121
	24, 65, 14, 90, 48, 130, 24,	// 122
	32, 240, 94, 0, 1,	// 123
	255, 7,	// 124
	1, 244, 30, 8, 0,	// 125
	96, 128, 0, 4, 64, 0, 4, 32, 192, 0,	// 126
		// 127

    }
};

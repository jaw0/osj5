
// file: font/helvBO10.bdf
// font: -Adobe-Helvetica-Bold-O-Normal--10-100-75-75-P-60-ISO10646-1

#include <font.h>

const struct Font font_helvBO10 = {
    .type       = 1,
    .name	= "helvBO10",
    .height	= 10,
    .width	= 11,
    .bytescol	= 2,
    .numcol     = 11,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 5, .ncol = 4, .xadj = -7, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -5, .pos = 5 }, // 34 [8]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 13 }, // 35 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 22 }, // 36 [8]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -2, .pos = 30 }, // 37 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 40 }, // 38 [9]
	{ .l0 = 3, .r0 = 5, .ncol = 3, .xadj = -8, .pos = 49 }, // 39 [4]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 53 }, // 40 [7]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 60 }, // 41 [7]
	{ .l0 = 3, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 67 }, // 42 [5]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 72 }, // 43 [7]
	{ .l0 = 1, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 79 }, // 44 [3]
	{ .l0 = 2, .r0 = 5, .ncol = 4, .xadj = -6, .pos = 82 }, // 45 [5]
	{ .l0 = 2, .r0 = 8, .ncol = 1, .xadj = -8, .pos = 87 }, // 46 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -6, .pos = 89 }, // 47 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 97 }, // 48 [8]
	{ .l0 = 3, .r0 = 4, .ncol = 4, .xadj = -5, .pos = 105 }, // 49 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 110 }, // 50 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 118 }, // 51 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 126 }, // 52 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 134 }, // 53 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 142 }, // 54 [8]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 150 }, // 55 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 157 }, // 56 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 165 }, // 57 [8]
	{ .l0 = 2, .r0 = 7, .ncol = 2, .xadj = -8, .pos = 173 }, // 58 [3]
	{ .l0 = 1, .r0 = 7, .ncol = 3, .xadj = -8, .pos = 176 }, // 59 [4]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 180 }, // 60 [7]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 187 }, // 61 [7]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 194 }, // 62 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -5, .pos = 201 }, // 63 [8]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -1, .pos = 209 }, // 64 [12]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 221 }, // 65 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 230 }, // 66 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 239 }, // 67 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 248 }, // 68 [10]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -5, .pos = 258 }, // 69 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -6, .pos = 267 }, // 70 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 276 }, // 71 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -4, .pos = 286 }, // 72 [10]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -8, .pos = 296 }, // 73 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -5, .pos = 301 }, // 74 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 310 }, // 75 [10]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 320 }, // 76 [7]
	{ .l0 = 1, .r0 = 0, .ncol = 10, .xadj = -1, .pos = 327 }, // 77 [13]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -3, .pos = 340 }, // 78 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 352 }, // 79 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -4, .pos = 362 }, // 80 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 372 }, // 81 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 382 }, // 82 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -4, .pos = 392 }, // 83 [10]
	{ .l0 = 2, .r0 = 3, .ncol = 6, .xadj = -5, .pos = 402 }, // 84 [8]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -4, .pos = 410 }, // 85 [10]
	{ .l0 = 3, .r0 = 1, .ncol = 7, .xadj = -3, .pos = 420 }, // 86 [9]
	{ .l0 = 2, .r0 = 0, .ncol = 9, .xadj = -1, .pos = 429 }, // 87 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -4, .pos = 441 }, // 88 [10]
	{ .l0 = 2, .r0 = 1, .ncol = 8, .xadj = -4, .pos = 451 }, // 89 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 8, .xadj = -4, .pos = 461 }, // 90 [10]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -7, .pos = 471 }, // 91 [8]
	{ .l0 = 3, .r0 = 6, .ncol = 2, .xadj = -6, .pos = 479 }, // 92 [3]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -7, .pos = 482 }, // 93 [8]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 490 }, // 94 [7]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -5, .pos = 497 }, // 95 [8]
	{ .l0 = 3, .r0 = 6, .ncol = 2, .xadj = -8, .pos = 505 }, // 96 [3]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 508 }, // 97 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 516 }, // 98 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 524 }, // 99 [7]
	{ .l0 = 1, .r0 = 3, .ncol = 7, .xadj = -5, .pos = 531 }, // 100 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 540 }, // 101 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -8, .pos = 548 }, // 102 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 555 }, // 103 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 563 }, // 104 [8]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -8, .pos = 571 }, // 105 [5]
	{ .l0 = 0, .r0 = 6, .ncol = 5, .xadj = -8, .pos = 576 }, // 106 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 583 }, // 107 [8]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -8, .pos = 591 }, // 108 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 9, .xadj = -2, .pos = 596 }, // 109 [12]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 608 }, // 110 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 616 }, // 111 [8]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -5, .pos = 624 }, // 112 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 633 }, // 113 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -7, .pos = 641 }, // 114 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 648 }, // 115 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 5, .xadj = -7, .pos = 656 }, // 116 [7]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 663 }, // 117 [8]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 671 }, // 118 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 7, .xadj = -3, .pos = 678 }, // 119 [9]
	{ .l0 = 0, .r0 = 4, .ncol = 7, .xadj = -6, .pos = 687 }, // 120 [9]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 696 }, // 121 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -6, .pos = 704 }, // 122 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 6, .xadj = -6, .pos = 712 }, // 123 [8]
	{ .l0 = 1, .r0 = 6, .ncol = 4, .xadj = -7, .pos = 720 }, // 124 [5]
	{ .l0 = 0, .r0 = 5, .ncol = 6, .xadj = -6, .pos = 725 }, // 125 [8]
	{ .l0 = 2, .r0 = 4, .ncol = 5, .xadj = -5, .pos = 733 }, // 126 [7]
	{ .l0 = 11, .r0 = 0, .ncol = 0, .xadj = -11, .pos = 740 }, // 127 [0]
    },
    .data       = {
	128, 240, 242, 192, 0,	// 33
	4, 12, 16, 0, 1, 3, 4, 0,	// 34
	32, 160, 131, 131, 59, 56, 184, 128, 0,	// 35
	64, 112, 103, 143, 55, 119, 16, 0,	// 36
	130, 28, 81, 130, 20, 232, 144, 34, 68, 0,	// 37
	96, 192, 227, 201, 54, 125, 156, 3, 11,	// 38
	4, 12, 16, 0,	// 39
	112, 240, 231, 248, 128, 1, 0,	// 40
	0, 6, 124, 156, 63, 56, 0,	// 41
	10, 24, 240, 128, 0,	// 42
	16, 192, 193, 7, 7, 16, 0,	// 43
	0, 2, 7,	// 44
	16, 64, 0, 1, 4,	// 45
	192, 0,	// 46
	128, 128, 131, 131, 3, 3, 4, 0,	// 47
	120, 248, 51, 72, 48, 127, 120, 0,	// 48
	226, 248, 243, 193, 0,	// 49
	224, 200, 179, 73, 34, 143, 24, 0,	// 50
	64, 8, 179, 72, 62, 119, 24, 0,	// 51
	48, 160, 64, 142, 62, 63, 12, 0,	// 52
	64, 48, 243, 72, 62, 113, 4, 0,	// 53
	120, 248, 243, 72, 62, 123, 8, 0,	// 54
	193, 196, 211, 195, 3, 3, 0,	// 55
	112, 248, 243, 72, 62, 127, 24, 0,	// 56
	64, 56, 243, 73, 52, 127, 248, 0,	// 57
	192, 48, 0,	// 58
	0, 2, 199, 0,	// 59
	16, 224, 128, 6, 19, 4, 0,	// 60
	32, 160, 128, 2, 10, 8, 0,	// 61
	64, 144, 193, 2, 14, 16, 0,	// 62
	128, 200, 178, 67, 2, 15, 24, 0,	// 63
	240, 48, 68, 174, 164, 74, 234, 171, 8, 17, 56, 0,	// 64
	192, 192, 195, 131, 11, 35, 252, 195, 15,	// 65
	224, 240, 243, 201, 34, 201, 244, 113, 3,	// 66
	112, 240, 227, 200, 32, 193, 156, 97, 0,	// 67
	224, 240, 243, 201, 32, 193, 196, 241, 131, 3,	// 68
	224, 240, 243, 201, 34, 137, 36, 16, 0,	// 69
	224, 240, 243, 193, 2, 9, 4, 16, 0,	// 70
	112, 240, 227, 200, 32, 209, 196, 51, 131, 4,	// 71
	224, 240, 243, 193, 2, 232, 240, 243, 193, 0,	// 72
	224, 240, 243, 193, 0,	// 73
	96, 128, 3, 8, 56, 124, 124, 48, 0,	// 74
	224, 240, 243, 193, 6, 60, 152, 51, 76, 0,	// 75
	224, 240, 243, 201, 32, 128, 0,	// 76
	224, 240, 243, 193, 1, 252, 192, 129, 1, 59, 254, 124, 0,	// 77
	224, 240, 243, 193, 3, 56, 128, 195, 207, 7, 3, 0,	// 78
	112, 240, 227, 200, 32, 193, 196, 241, 131, 3,	// 79
	224, 240, 243, 193, 4, 17, 100, 240, 128, 1,	// 80
	112, 240, 227, 200, 32, 193, 196, 243, 139, 35,	// 81
	224, 240, 243, 193, 2, 201, 228, 115, 131, 1,	// 82
	96, 128, 227, 200, 39, 249, 196, 49, 128, 0,	// 83
	225, 244, 243, 193, 0, 1, 4, 0,	// 84
	96, 240, 243, 201, 32, 224, 240, 241, 193, 0,	// 85
	63, 252, 3, 12, 28, 60, 60, 48, 0,	// 86
	31, 252, 3, 14, 14, 7, 252, 3, 14, 15, 15, 0,	// 87
	192, 140, 243, 3, 6, 252, 152, 51, 64, 0,	// 88
	3, 60, 195, 15, 14, 12, 24, 48, 64, 0,	// 89
	192, 128, 19, 75, 38, 153, 52, 114, 192, 0,	// 90
	0, 131, 207, 239, 7, 3, 4, 0,	// 91
	15, 192, 3,	// 92
	0, 2, 12, 126, 63, 31, 12, 0,	// 93
	8, 48, 96, 192, 0, 15, 0,	// 94
	0, 2, 8, 32, 128, 0, 2, 8,	// 95
	1, 8, 0,	// 96
	96, 160, 67, 9, 29, 252, 96, 2,	// 97
	224, 240, 243, 200, 49, 124, 96, 0,	// 98
	112, 224, 195, 8, 49, 76, 0,	// 99
	96, 224, 195, 8, 49, 252, 124, 48, 0,	// 100
	96, 224, 195, 9, 53, 92, 96, 0,	// 101
	228, 248, 243, 65, 1, 1, 0,	// 102
	96, 226, 203, 56, 113, 252, 112, 0,	// 103
	224, 240, 243, 192, 57, 252, 96, 0,	// 104
	224, 240, 211, 65, 0,	// 105
	0, 130, 207, 95, 7, 1, 0,	// 106
	224, 240, 243, 193, 30, 236, 16, 2,	// 107
	224, 240, 243, 193, 0,	// 108
	224, 240, 131, 1, 57, 252, 96, 64, 14, 63, 24, 0,	// 109
	224, 240, 195, 0, 57, 252, 96, 0,	// 110
	112, 224, 195, 8, 49, 124, 224, 0,	// 111
	0, 131, 207, 15, 35, 196, 240, 129, 1,	// 112
	96, 224, 195, 56, 241, 252, 112, 0,	// 113
	224, 240, 131, 1, 3, 4, 0,	// 114
	64, 32, 195, 9, 61, 108, 32, 0,	// 115
	100, 240, 243, 201, 1, 4, 0,	// 116
	112, 240, 195, 8, 24, 252, 112, 0,	// 117
	124, 240, 3, 4, 15, 28, 0,	// 118
	124, 240, 3, 4, 31, 192, 240, 192, 1,	// 119
	128, 16, 195, 6, 14, 248, 48, 67, 0,	// 120
	0, 114, 204, 31, 56, 60, 112, 0,	// 121
	192, 144, 67, 11, 37, 156, 48, 0,	// 122
	16, 192, 199, 190, 131, 3, 4, 0,	// 123
	0, 131, 195, 193, 0,	// 124
	0, 2, 28, 222, 59, 30, 64, 0,	// 125
	16, 32, 128, 1, 4, 8, 0,	// 126
		// 127

    }
};

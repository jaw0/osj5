
// file: font/7x13B.bdf
// font: -Misc-Fixed-Bold-R-Normal--13-120-75-75-C-70-ISO10646-1

#include <font.h>

const struct Font font_7x13B = {
    .type       = 1,
    .name	= "7x13B",
    .height	= 13,
    .width	= 7,
    .bytescol	= 2,
    .numcol     = 7,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 4 }, // 34 [9]
	{ .l0 = 1, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 13 }, // 35 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 22 }, // 36 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 32 }, // 37 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 42 }, // 38 [10]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 52 }, // 39 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 56 }, // 40 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 63 }, // 41 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 70 }, // 42 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 80 }, // 43 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 90 }, // 44 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 97 }, // 45 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 107 }, // 46 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 114 }, // 47 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 124 }, // 48 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 134 }, // 49 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 144 }, // 50 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 154 }, // 51 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 164 }, // 52 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 174 }, // 53 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 184 }, // 54 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 194 }, // 55 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 204 }, // 56 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 214 }, // 57 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 224 }, // 58 [7]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 231 }, // 59 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 238 }, // 60 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 248 }, // 61 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 258 }, // 62 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 268 }, // 63 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 278 }, // 64 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 288 }, // 65 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 298 }, // 66 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 308 }, // 67 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 318 }, // 68 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 328 }, // 69 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 338 }, // 70 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 348 }, // 71 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 358 }, // 72 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 368 }, // 73 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 378 }, // 74 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 388 }, // 75 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 398 }, // 76 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 408 }, // 77 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 418 }, // 78 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 428 }, // 79 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 438 }, // 80 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 448 }, // 81 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 458 }, // 82 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 468 }, // 83 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 478 }, // 84 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 488 }, // 85 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 498 }, // 86 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 508 }, // 87 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 518 }, // 88 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 528 }, // 89 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 538 }, // 90 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 548 }, // 91 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 555 }, // 92 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 565 }, // 93 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 572 }, // 94 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 582 }, // 95 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 592 }, // 96 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 599 }, // 97 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 609 }, // 98 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 619 }, // 99 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 629 }, // 100 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 639 }, // 101 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 649 }, // 102 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 659 }, // 103 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 669 }, // 104 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 679 }, // 105 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 689 }, // 106 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 699 }, // 107 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 709 }, // 108 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 719 }, // 109 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 729 }, // 110 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 739 }, // 111 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 749 }, // 112 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 759 }, // 113 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 769 }, // 114 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 779 }, // 115 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 789 }, // 116 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 799 }, // 117 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 809 }, // 118 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 819 }, // 119 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 829 }, // 120 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 839 }, // 121 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 849 }, // 122 [10]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 859 }, // 123 [7]
	{ .l0 = 2, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 866 }, // 124 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 870 }, // 125 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 877 }, // 126 [10]
	{ .l0 = 7, .r0 = 0, .ncol = 0, .xadj = -7, .pos = 887 }, // 127 [0]
    },
    .data       = {
	252, 134, 223, 0,	// 33
	28, 128, 3, 0, 0, 14, 192, 1, 0,	// 34
	176, 129, 255, 192, 6, 254, 3, 27, 0,	// 35
	48, 1, 73, 240, 31, 254, 131, 36, 32, 3,	// 36
	28, 134, 114, 112, 3, 176, 131, 83, 24, 14,	// 37
	184, 131, 255, 16, 17, 254, 131, 51, 0, 11,	// 38
	60, 128, 7, 0,	// 39
	224, 0, 127, 112, 28, 2, 2,	// 40
	4, 132, 227, 224, 15, 112, 0,	// 41
	192, 0, 90, 128, 7, 240, 0, 45, 128, 1,	// 42
	192, 0, 24, 192, 15, 248, 1, 12, 128, 1,	// 43
	0, 8, 224, 1, 28, 128, 1,	// 44
	128, 0, 16, 0, 2, 64, 0, 8, 0, 1,	// 45
	0, 4, 192, 1, 56, 0, 2,	// 46
	0, 6, 240, 0, 7, 56, 192, 3, 24, 0,	// 47
	240, 1, 127, 16, 16, 2, 130, 63, 224, 3,	// 48
	16, 4, 129, 240, 31, 254, 3, 64, 0, 8,	// 49
	24, 135, 243, 16, 19, 34, 194, 71, 112, 8,	// 50
	4, 130, 200, 144, 17, 58, 194, 125, 24, 7,	// 51
	192, 1, 60, 192, 4, 140, 192, 127, 248, 15,	// 52
	124, 130, 207, 144, 16, 18, 66, 126, 136, 7,	// 53
	248, 131, 255, 16, 17, 34, 194, 124, 16, 7,	// 54
	4, 128, 192, 16, 30, 242, 192, 7, 56, 0,	// 55
	184, 131, 255, 16, 17, 34, 194, 127, 112, 7,	// 56
	56, 130, 207, 16, 17, 34, 194, 127, 240, 7,	// 57
	32, 4, 206, 193, 57, 16, 2,	// 58
	32, 8, 238, 193, 29, 144, 1,	// 59
	64, 0, 28, 192, 6, 140, 193, 96, 8, 8,	// 60
	32, 1, 36, 128, 4, 144, 0, 18, 64, 2,	// 61
	4, 132, 193, 96, 12, 216, 0, 14, 128, 0,	// 62
	24, 128, 3, 16, 27, 98, 195, 7, 112, 0,	// 63
	248, 131, 128, 144, 19, 82, 194, 111, 240, 5,	// 64
	248, 135, 255, 16, 1, 34, 192, 127, 240, 15,	// 65
	252, 135, 255, 16, 17, 34, 194, 127, 112, 7,	// 66
	248, 131, 255, 16, 16, 2, 194, 96, 16, 4,	// 67
	252, 135, 255, 16, 16, 2, 194, 127, 240, 7,	// 68
	252, 135, 255, 16, 17, 34, 66, 68, 8, 8,	// 69
	252, 135, 255, 16, 1, 34, 64, 4, 8, 0,	// 70
	248, 131, 255, 16, 16, 34, 194, 124, 144, 15,	// 71
	252, 135, 255, 0, 1, 32, 192, 127, 248, 15,	// 72
	4, 132, 128, 240, 31, 254, 67, 64, 8, 8,	// 73
	0, 2, 192, 0, 16, 0, 194, 127, 248, 7,	// 74
	252, 135, 255, 128, 3, 216, 128, 49, 24, 12,	// 75
	252, 135, 255, 0, 16, 0, 2, 64, 0, 8,	// 76
	252, 7, 255, 192, 0, 24, 128, 127, 248, 15,	// 77
	252, 135, 255, 192, 1, 224, 192, 127, 248, 15,	// 78
	248, 131, 255, 16, 16, 2, 194, 127, 240, 7,	// 79
	252, 135, 255, 16, 1, 34, 192, 7, 112, 0,	// 80
	248, 131, 255, 16, 20, 2, 195, 255, 240, 23,	// 81
	252, 135, 255, 16, 3, 226, 192, 55, 112, 12,	// 82
	56, 130, 207, 16, 17, 34, 194, 124, 16, 7,	// 83
	4, 128, 0, 240, 31, 254, 67, 0, 8, 0,	// 84
	252, 131, 255, 0, 16, 0, 194, 127, 248, 7,	// 85
	28, 128, 31, 0, 30, 192, 195, 15, 56, 0,	// 86
	252, 135, 127, 0, 6, 192, 192, 63, 248, 15,	// 87
	12, 6, 119, 128, 3, 112, 128, 59, 24, 12,	// 88
	12, 128, 7, 192, 31, 248, 195, 3, 24, 0,	// 89
	4, 135, 240, 16, 19, 50, 194, 67, 56, 8,	// 90
	252, 135, 255, 16, 16, 2, 2,	// 91
	12, 128, 7, 192, 1, 224, 0, 120, 0, 12,	// 92
	4, 132, 128, 240, 31, 254, 3,	// 93
	48, 0, 3, 48, 0, 6, 128, 1, 96, 0,	// 94
	0, 12, 128, 1, 48, 0, 6, 192, 0, 24,	// 95
	2, 192, 0, 48, 0, 4, 0,	// 96
	0, 3, 244, 128, 18, 80, 2, 126, 128, 15,	// 97
	252, 135, 255, 128, 16, 16, 2, 126, 128, 7,	// 98
	192, 3, 252, 128, 16, 16, 2, 102, 128, 4,	// 99
	192, 3, 252, 128, 16, 16, 194, 127, 248, 15,	// 100
	192, 3, 252, 128, 18, 80, 2, 110, 128, 5,	// 101
	64, 0, 255, 240, 31, 34, 192, 0, 16, 0,	// 102
	192, 10, 252, 131, 84, 144, 10, 220, 193, 17,	// 103
	252, 135, 255, 128, 0, 16, 0, 126, 128, 15,	// 104
	0, 4, 132, 176, 31, 246, 3, 64, 0, 8,	// 105
	0, 8, 0, 3, 64, 0, 200, 254, 217, 31,	// 106
	252, 135, 255, 0, 6, 224, 1, 102, 64, 8,	// 107
	0, 132, 128, 240, 31, 254, 3, 64, 0, 8,	// 108
	224, 7, 252, 0, 3, 112, 0, 126, 128, 15,	// 109
	224, 7, 252, 128, 0, 16, 0, 126, 128, 15,	// 110
	192, 3, 252, 128, 16, 16, 2, 126, 128, 7,	// 111
	224, 31, 252, 131, 8, 16, 1, 62, 128, 3,	// 112
	192, 1, 124, 128, 8, 16, 1, 254, 193, 63,	// 113
	224, 7, 252, 128, 0, 16, 0, 6, 128, 0,	// 114
	64, 2, 220, 128, 18, 144, 2, 118, 128, 4,	// 115
	32, 0, 127, 224, 31, 16, 2, 98, 0, 4,	// 116
	224, 3, 252, 0, 16, 0, 2, 126, 192, 15,	// 117
	224, 0, 124, 0, 28, 128, 3, 62, 192, 1,	// 118
	224, 3, 252, 0, 12, 128, 1, 126, 192, 7,	// 119
	96, 6, 252, 0, 6, 192, 0, 126, 192, 12,	// 120
	224, 9, 124, 3, 72, 0, 9, 254, 193, 31,	// 121
	32, 6, 228, 128, 20, 80, 2, 78, 192, 8,	// 122
	88, 131, 255, 144, 18, 2, 2,	// 123
	252, 135, 255, 0,	// 124
	4, 132, 148, 240, 31, 172, 1,	// 125
	24, 128, 1, 48, 0, 12, 128, 1, 24, 0,	// 126
		// 127

    }
};

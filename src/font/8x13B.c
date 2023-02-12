
// file: font/8x13B.bdf
// font: -Misc-Fixed-Bold-R-Normal--13-120-75-75-C-80-ISO10646-1

#include <font.h>

const struct Font font_8x13B = {
    .type       = 1,
    .name	= "8x13B",
    .height	= 13,
    .width	= 8,
    .bytescol	= 2,
    .numcol     = 8,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 3, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 0 }, // 33 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 4 }, // 34 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 13 }, // 35 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 25 }, // 36 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 37 }, // 37 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 49 }, // 38 [12]
	{ .l0 = 3, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 61 }, // 39 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 65 }, // 40 [9]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 74 }, // 41 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 83 }, // 42 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 95 }, // 43 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 105 }, // 44 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 112 }, // 45 [10]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 122 }, // 46 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 129 }, // 47 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 141 }, // 48 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 153 }, // 49 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 163 }, // 50 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 175 }, // 51 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 187 }, // 52 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 199 }, // 53 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 211 }, // 54 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 223 }, // 55 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 235 }, // 56 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 247 }, // 57 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 259 }, // 58 [7]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 266 }, // 59 [7]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 273 }, // 60 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 283 }, // 61 [10]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 293 }, // 62 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 303 }, // 63 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 315 }, // 64 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 327 }, // 65 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 339 }, // 66 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 351 }, // 67 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 363 }, // 68 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 375 }, // 69 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 387 }, // 70 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 399 }, // 71 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 411 }, // 72 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 423 }, // 73 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 430 }, // 74 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 442 }, // 75 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 454 }, // 76 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 466 }, // 77 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 478 }, // 78 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 490 }, // 79 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 502 }, // 80 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 514 }, // 81 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 526 }, // 82 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 538 }, // 83 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 550 }, // 84 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 560 }, // 85 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 572 }, // 86 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 584 }, // 87 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 596 }, // 88 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 608 }, // 89 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 618 }, // 90 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 630 }, // 91 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 639 }, // 92 [12]
	{ .l0 = 1, .r0 = 2, .ncol = 5, .xadj = 0, .pos = 651 }, // 93 [9]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 660 }, // 94 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 672 }, // 95 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 684 }, // 96 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 691 }, // 97 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 703 }, // 98 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 715 }, // 99 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 727 }, // 100 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 739 }, // 101 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 751 }, // 102 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 763 }, // 103 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 775 }, // 104 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 787 }, // 105 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 794 }, // 106 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 806 }, // 107 [12]
	{ .l0 = 2, .r0 = 2, .ncol = 4, .xadj = 0, .pos = 818 }, // 108 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 825 }, // 109 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 837 }, // 110 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 849 }, // 111 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 861 }, // 112 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 873 }, // 113 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 885 }, // 114 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 897 }, // 115 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 909 }, // 116 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 921 }, // 117 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 933 }, // 118 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 945 }, // 119 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 957 }, // 120 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 969 }, // 121 [12]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 981 }, // 122 [12]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 993 }, // 123 [10]
	{ .l0 = 3, .r0 = 3, .ncol = 2, .xadj = 0, .pos = 1003 }, // 124 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 6, .xadj = 0, .pos = 1007 }, // 125 [10]
	{ .l0 = 0, .r0 = 1, .ncol = 7, .xadj = 0, .pos = 1017 }, // 126 [12]
	{ .l0 = 8, .r0 = 0, .ncol = 0, .xadj = -8, .pos = 1029 }, // 127 [0]
    },
    .data       = {
	254, 198, 223, 0,	// 33
	30, 192, 3, 0, 0, 15, 224, 1, 0,	// 34
	176, 129, 255, 240, 31, 216, 192, 127, 248, 15, 108, 0,	// 35
	56, 130, 207, 144, 17, 255, 71, 76, 152, 15, 226, 0,	// 36
	14, 70, 225, 56, 7, 120, 128, 115, 28, 138, 193, 1,	// 37
	96, 3, 254, 64, 18, 72, 2, 127, 192, 14, 64, 1,	// 38
	30, 192, 3, 0,	// 39
	224, 0, 127, 112, 28, 3, 38, 128, 0,	// 40
	2, 200, 128, 113, 28, 252, 1, 14, 0,	// 41
	32, 0, 100, 128, 7, 124, 0, 30, 64, 6, 8, 0,	// 42
	96, 0, 12, 224, 7, 252, 0, 6, 192, 0,	// 43
	128, 8, 240, 1, 30, 192, 1,	// 44
	64, 0, 8, 0, 1, 32, 0, 4, 128, 0,	// 45
	0, 2, 224, 0, 28, 0, 1,	// 46
	0, 7, 112, 0, 3, 48, 0, 3, 56, 128, 3, 0,	// 47
	248, 129, 127, 24, 24, 1, 98, 96, 248, 7, 126, 0,	// 48
	8, 132, 129, 248, 31, 255, 3, 64, 0, 8,	// 49
	12, 198, 225, 8, 22, 97, 34, 70, 124, 8, 7, 1,	// 50
	2, 66, 192, 136, 16, 25, 162, 67, 220, 143, 241, 0,	// 51
	224, 0, 30, 96, 2, 70, 224, 127, 252, 15, 32, 0,	// 52
	62, 194, 199, 200, 16, 9, 34, 65, 228, 143, 248, 0,	// 53
	248, 131, 255, 152, 25, 17, 34, 66, 196, 15, 240, 0,	// 54
	2, 64, 0, 8, 30, 241, 35, 7, 60, 128, 3, 0,	// 55
	220, 195, 255, 136, 16, 17, 34, 66, 252, 15, 247, 0,	// 56
	60, 192, 143, 8, 17, 33, 98, 102, 252, 7, 127, 0,	// 57
	16, 2, 231, 224, 28, 8, 1,	// 58
	144, 8, 247, 225, 30, 200, 1,	// 59
	64, 0, 28, 192, 6, 140, 193, 96, 8, 8,	// 60
	32, 1, 36, 128, 4, 144, 0, 18, 64, 2,	// 61
	4, 132, 193, 96, 12, 216, 0, 14, 128, 0,	// 62
	12, 192, 1, 8, 0, 97, 35, 110, 124, 0, 7, 0,	// 63
	248, 131, 255, 48, 24, 246, 194, 83, 120, 10, 126, 1,	// 64
	248, 135, 255, 24, 1, 35, 96, 4, 248, 15, 254, 1,	// 65
	2, 196, 255, 248, 31, 17, 34, 66, 252, 15, 247, 0,	// 66
	252, 195, 255, 24, 24, 1, 34, 64, 28, 14, 195, 0,	// 67
	2, 196, 255, 248, 31, 1, 34, 64, 252, 15, 255, 0,	// 68
	254, 199, 255, 136, 16, 17, 34, 66, 4, 136, 0, 1,	// 69
	254, 199, 255, 136, 0, 17, 32, 2, 4, 128, 0, 0,	// 70
	252, 195, 255, 8, 16, 1, 34, 72, 28, 15, 227, 0,	// 71
	254, 199, 255, 128, 0, 16, 0, 2, 252, 143, 255, 1,	// 72
	2, 196, 255, 248, 31, 1, 2,	// 73
	0, 3, 224, 0, 16, 0, 34, 64, 252, 143, 255, 0,	// 74
	254, 199, 255, 128, 1, 120, 128, 25, 28, 142, 129, 1,	// 75
	254, 199, 255, 0, 16, 0, 2, 64, 0, 8, 128, 1,	// 76
	254, 199, 255, 96, 0, 24, 128, 1, 252, 143, 255, 1,	// 77
	254, 199, 255, 224, 0, 48, 0, 28, 252, 143, 255, 1,	// 78
	252, 195, 255, 8, 16, 1, 34, 64, 252, 15, 255, 0,	// 79
	254, 199, 255, 8, 1, 33, 32, 4, 252, 0, 15, 0,	// 80
	252, 195, 255, 8, 16, 1, 35, 96, 252, 31, 255, 2,	// 81
	254, 199, 255, 136, 1, 49, 32, 30, 124, 15, 135, 1,	// 82
	28, 195, 231, 136, 16, 17, 34, 66, 220, 15, 243, 0,	// 83
	2, 64, 0, 248, 31, 255, 35, 0, 4, 0,	// 84
	254, 195, 255, 0, 16, 0, 2, 64, 252, 143, 255, 0,	// 85
	30, 192, 31, 0, 15, 128, 3, 60, 252, 129, 7, 0,	// 86
	254, 195, 255, 0, 24, 192, 1, 96, 252, 143, 255, 0,	// 87
	6, 198, 243, 224, 7, 48, 128, 31, 60, 143, 129, 1,	// 88
	14, 192, 7, 192, 31, 248, 227, 3, 28, 0,	// 89
	2, 71, 240, 8, 19, 49, 34, 67, 60, 136, 3, 1,	// 90
	254, 207, 255, 9, 32, 1, 36, 128, 0,	// 91
	14, 128, 3, 192, 0, 48, 0, 12, 0, 7, 192, 1,	// 92
	2, 72, 0, 9, 32, 255, 231, 255, 0,	// 93
	16, 0, 3, 48, 0, 3, 192, 0, 48, 0, 4, 0,	// 94
	0, 8, 0, 1, 32, 0, 4, 128, 0, 16, 0, 2,	// 95
	2, 192, 0, 48, 0, 4, 0,	// 96
	128, 3, 250, 64, 17, 40, 2, 37, 224, 15, 248, 1,	// 97
	254, 199, 255, 128, 8, 8, 2, 65, 224, 15, 248, 0,	// 98
	224, 3, 254, 192, 24, 8, 2, 65, 96, 12, 136, 0,	// 99
	224, 3, 254, 64, 16, 8, 2, 34, 252, 143, 255, 1,	// 100
	224, 3, 254, 64, 18, 72, 2, 73, 224, 13, 184, 0,	// 101
	64, 128, 255, 248, 31, 33, 32, 4, 140, 0, 1, 0,	// 102
	224, 10, 254, 67, 92, 136, 11, 95, 225, 57, 4, 2,	// 103
	254, 199, 255, 128, 0, 8, 0, 1, 224, 15, 248, 1,	// 104
	32, 132, 253, 176, 31, 0, 2,	// 105
	0, 12, 128, 3, 64, 0, 8, 2, 217, 63, 251, 3,	// 106
	254, 199, 255, 0, 3, 240, 0, 51, 32, 12, 0, 1,	// 107
	2, 196, 255, 248, 31, 0, 2,	// 108
	224, 7, 254, 192, 0, 112, 0, 3, 224, 15, 248, 1,	// 109
	240, 7, 254, 128, 0, 8, 0, 1, 224, 15, 248, 1,	// 110
	224, 3, 254, 64, 16, 8, 2, 65, 224, 15, 248, 0,	// 111
	240, 31, 254, 131, 8, 8, 2, 65, 224, 15, 248, 0,	// 112
	224, 3, 254, 64, 16, 8, 2, 34, 224, 63, 252, 7,	// 113
	240, 7, 254, 128, 0, 8, 0, 1, 96, 0, 8, 0,	// 114
	32, 2, 206, 64, 19, 72, 2, 89, 96, 14, 136, 0,	// 115
	32, 192, 127, 248, 31, 16, 2, 66, 64, 12, 128, 0,	// 116
	240, 3, 254, 0, 16, 0, 2, 32, 224, 15, 252, 1,	// 117
	240, 0, 126, 0, 28, 0, 2, 112, 224, 7, 60, 0,	// 118
	240, 3, 254, 0, 24, 192, 1, 96, 224, 15, 252, 0,	// 119
	48, 6, 238, 0, 7, 64, 0, 28, 224, 14, 140, 1,	// 120
	240, 9, 126, 3, 72, 0, 9, 16, 225, 63, 252, 3,	// 121
	16, 6, 226, 64, 22, 104, 2, 71, 96, 8, 4, 1,	// 122
	64, 128, 235, 248, 63, 81, 36, 128, 4, 16,	// 123
	254, 199, 255, 0,	// 124
	2, 72, 0, 137, 34, 255, 199, 117, 128, 0,	// 125
	24, 128, 1, 48, 0, 14, 128, 1, 48, 0, 3, 0,	// 126
		// 127

    }
};

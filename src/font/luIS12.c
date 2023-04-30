
// file: font/luIS12.bdf
// font: -B&H-Lucida-Medium-I-Normal-Sans-12-120-75-75-P-71-ISO10646-1

#include <font.h>

const struct Font font_luIS12 = {
    .type       = 1,
    .name	= "luIS12",
    .height	= 12,
    .width	= 12,
    .lineheight = 12,
    .bytescol	= 2,
    .numcol     = 12,
    .startchar  = 33,
    .lastchar	= 127,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 1, .r0 = 8, .ncol = 3, .xadj = -9, .pos = 0 }, // 33 [5]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -7, .pos = 4 }, // 34 [5]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -4, .pos = 7 }, // 35 [12]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 20 }, // 36 [9]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 31 }, // 37 [12]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 52 }, // 38 [11]
	{ .l0 = 2, .r0 = 9, .ncol = 1, .xadj = -9, .pos = 68 }, // 39 [2]
	{ .l0 = 2, .r0 = 6, .ncol = 4, .xadj = -8, .pos = 70 }, // 40 [6]
	{ .l0 = 0, .r0 = 8, .ncol = 4, .xadj = -8, .pos = 76 }, // 41 [6]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -6, .pos = 82 }, // 42 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 89 }, // 43 [9]
	{ .l0 = 1, .r0 = 9, .ncol = 2, .xadj = -9, .pos = 96 }, // 44 [3]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -8, .pos = 99 }, // 45 [5]
	{ .l0 = 2, .r0 = 9, .ncol = 1, .xadj = -9, .pos = 103 }, // 46 [2]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -6, .pos = 105 }, // 47 [11]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 113 }, // 48 [9]
	{ .l0 = 4, .r0 = 5, .ncol = 3, .xadj = -4, .pos = 124 }, // 49 [5]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 129 }, // 50 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 144 }, // 51 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 159 }, // 52 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 169 }, // 53 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 182 }, // 54 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 195 }, // 55 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 206 }, // 56 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 221 }, // 57 [9]
	{ .l0 = 2, .r0 = 8, .ncol = 2, .xadj = -9, .pos = 234 }, // 58 [3]
	{ .l0 = 1, .r0 = 8, .ncol = 3, .xadj = -9, .pos = 237 }, // 59 [5]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 241 }, // 60 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 254 }, // 61 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 267 }, // 62 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 280 }, // 63 [8]
	{ .l0 = 3, .r0 = 1, .ncol = 8, .xadj = -1, .pos = 289 }, // 64 [12]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 311 }, // 65 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 322 }, // 66 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 337 }, // 67 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 350 }, // 68 [11]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 363 }, // 69 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -6, .pos = 376 }, // 70 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 385 }, // 71 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 398 }, // 72 [11]
	{ .l0 = 2, .r0 = 8, .ncol = 2, .xadj = -8, .pos = 406 }, // 73 [3]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -7, .pos = 409 }, // 74 [6]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 414 }, // 75 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 426 }, // 76 [8]
	{ .l0 = 2, .r0 = 1, .ncol = 9, .xadj = -1, .pos = 433 }, // 77 [14]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 444 }, // 78 [11]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 452 }, // 79 [12]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 467 }, // 80 [9]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -2, .pos = 478 }, // 81 [12]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 496 }, // 82 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 508 }, // 83 [9]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 521 }, // 84 [11]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -3, .pos = 530 }, // 85 [11]
	{ .l0 = 3, .r0 = 3, .ncol = 6, .xadj = -4, .pos = 539 }, // 86 [9]
	{ .l0 = 3, .r0 = 0, .ncol = 9, .xadj = -1, .pos = 547 }, // 87 [14]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -4, .pos = 559 }, // 88 [12]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 572 }, // 89 [9]
	{ .l0 = 1, .r0 = 3, .ncol = 8, .xadj = -5, .pos = 579 }, // 90 [12]
	{ .l0 = 1, .r0 = 6, .ncol = 5, .xadj = -8, .pos = 597 }, // 91 [8]
	{ .l0 = 2, .r0 = 6, .ncol = 4, .xadj = -6, .pos = 605 }, // 92 [6]
	{ .l0 = 0, .r0 = 7, .ncol = 5, .xadj = -8, .pos = 610 }, // 93 [8]
	{ .l0 = 3, .r0 = 4, .ncol = 5, .xadj = -4, .pos = 618 }, // 94 [8]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 624 }, // 95 [9]
	{ .l0 = 4, .r0 = 6, .ncol = 2, .xadj = -5, .pos = 631 }, // 96 [3]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 634 }, // 97 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 645 }, // 98 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 657 }, // 99 [8]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 666 }, // 100 [11]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 678 }, // 101 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -7, .pos = 690 }, // 102 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 700 }, // 103 [9]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 715 }, // 104 [9]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -8, .pos = 724 }, // 105 [5]
	{ .l0 = 0, .r0 = 7, .ncol = 5, .xadj = -8, .pos = 728 }, // 106 [8]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 734 }, // 107 [9]
	{ .l0 = 2, .r0 = 7, .ncol = 3, .xadj = -8, .pos = 745 }, // 108 [5]
	{ .l0 = 2, .r0 = 0, .ncol = 10, .xadj = 0, .pos = 749 }, // 109 [15]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 762 }, // 110 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -5, .pos = 770 }, // 111 [8]
	{ .l0 = 1, .r0 = 4, .ncol = 7, .xadj = -4, .pos = 779 }, // 112 [11]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 791 }, // 113 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 803 }, // 114 [8]
	{ .l0 = 1, .r0 = 5, .ncol = 6, .xadj = -6, .pos = 809 }, // 115 [9]
	{ .l0 = 2, .r0 = 6, .ncol = 4, .xadj = -7, .pos = 822 }, // 116 [6]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -4, .pos = 830 }, // 117 [9]
	{ .l0 = 2, .r0 = 5, .ncol = 5, .xadj = -6, .pos = 838 }, // 118 [8]
	{ .l0 = 2, .r0 = 2, .ncol = 8, .xadj = -3, .pos = 844 }, // 119 [12]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 853 }, // 120 [9]
	{ .l0 = 0, .r0 = 5, .ncol = 7, .xadj = -6, .pos = 862 }, // 121 [11]
	{ .l0 = 2, .r0 = 4, .ncol = 6, .xadj = -5, .pos = 870 }, // 122 [9]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -8, .pos = 883 }, // 123 [6]
	{ .l0 = 1, .r0 = 8, .ncol = 3, .xadj = -9, .pos = 894 }, // 124 [5]
	{ .l0 = 1, .r0 = 7, .ncol = 4, .xadj = -8, .pos = 898 }, // 125 [6]
	{ .l0 = 2, .r0 = 3, .ncol = 7, .xadj = -4, .pos = 909 }, // 126 [11]
	{ .l0 = 12, .r0 = 0, .ncol = 0, .xadj = -12, .pos = 917 }, // 127 [0]
    },
    .data       = {
	0x42, 0x33, 0x33, 0x60,	// 33
	0x3, 0xab, 0x68,	// 34
	0x39, 0x39, 0x1b, 0x2d, 0x2b, 0x19, 0x39, 0x1b, 0x2d, 0x2b, 0x19, 0x39, 0x40,	// 35
	0x41, 0x2b, 0x21, 0x19, 0x1e, 0xe, 0x19, 0x19, 0x23, 0x29, 0x48,	// 36
	0x12, 0x29, 0x19, 0x11, 0x19, 0x21, 0x11, 0x11, 0x32, 0xa, 0x4a, 0xa, 0x31, 0x11, 0x11, 0x21, 0x19, 0x11, 0x19, 0x2a, 0x18,	// 37
	0x33, 0x41, 0x19, 0x24, 0x19, 0x19, 0x1a, 0x11, 0x19, 0x11, 0x12, 0x2a, 0x21, 0x4a, 0x9, 0x30,	// 38
	0x3, 0x68,	// 39
	0x26, 0x22, 0x31, 0x11, 0x51, 0x58,	// 40
	0x51, 0x51, 0x11, 0x32, 0x26, 0x28,	// 41
	0x21, 0x49, 0x63, 0x3b, 0x61, 0x49, 0x48,	// 42
	0x29, 0x59, 0x5c, 0x2c, 0x59, 0x59, 0x30,	// 43
	0x51, 0x4a, 0x10,	// 44
	0x29, 0x59, 0x59, 0x50,	// 45
	0x42, 0x30,	// 46
	0x4a, 0x49, 0x4a, 0x49, 0x4a, 0x49, 0x4a, 0x70,	// 47
	0x2c, 0x2b, 0x21, 0x19, 0x39, 0x19, 0x39, 0x19, 0x23, 0x2c, 0x30,	// 48
	0x11, 0x59, 0x15, 0x1d, 0x50,	// 49
	0x42, 0x21, 0x21, 0x9, 0x19, 0x21, 0x11, 0x19, 0x21, 0x11, 0x19, 0x19, 0x19, 0x23, 0x38,	// 50
	0x41, 0x29, 0x11, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x11, 0xb, 0x2a, 0x40,	// 51
	0x2a, 0x49, 0x9, 0x3a, 0x11, 0x31, 0x24, 0x1e, 0x59, 0x28,	// 52
	0x41, 0x33, 0x19, 0x1a, 0x11, 0x19, 0x19, 0x19, 0x11, 0x21, 0x22, 0x29, 0x50,	// 53
	0x33, 0x33, 0x19, 0x21, 0x11, 0x19, 0x19, 0x19, 0x19, 0x19, 0x23, 0x29, 0x48,	// 54
	0x42, 0x19, 0x22, 0x29, 0x19, 0x39, 0x11, 0x41, 0x9, 0x4a, 0x48,	// 55
	0x33, 0x2a, 0x9, 0x19, 0x19, 0x11, 0x21, 0x19, 0x19, 0x11, 0x21, 0x11, 0xa, 0x32, 0x40,	// 56
	0x41, 0x2b, 0x21, 0x19, 0x19, 0x19, 0x19, 0x19, 0x11, 0x21, 0x1b, 0x33, 0x38,	// 57
	0x42, 0x2a, 0x38,	// 58
	0x51, 0x4a, 0x2a, 0x58,	// 59
	0x31, 0x51, 0x9, 0x49, 0x11, 0x39, 0x19, 0x39, 0x21, 0x29, 0x29, 0x29, 0x60,	// 60
	0x31, 0x49, 0x9, 0x49, 0x9, 0x49, 0x9, 0x49, 0x9, 0x49, 0x9, 0x49, 0x58,	// 61
	0x49, 0x29, 0x29, 0x29, 0x21, 0x39, 0x19, 0x39, 0x11, 0x49, 0x9, 0x51, 0x48,	// 62
	0x42, 0x21, 0x12, 0x31, 0x11, 0x41, 0x11, 0x4a, 0x60,	// 63
	0x24, 0x39, 0x21, 0x29, 0x31, 0x19, 0x1a, 0x11, 0x19, 0x11, 0x11, 0x9, 0x19, 0x9, 0x19, 0x9, 0x19, 0x9, 0xa, 0x3b, 0x11, 0x20,	// 64
	0x3b, 0x3a, 0x49, 0x9, 0x41, 0x11, 0x39, 0x19, 0x37, 0x2, 0x10,	// 65
	0x2d, 0x1d, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x12, 0x11, 0x2a, 0x12, 0x20,	// 66
	0x2c, 0x32, 0x1a, 0x21, 0x31, 0x21, 0x31, 0x19, 0x39, 0x19, 0x31, 0x29, 0x68,	// 67
	0x2d, 0x1d, 0x19, 0x19, 0x39, 0x19, 0x39, 0x19, 0x31, 0x22, 0x1a, 0x34, 0x50,	// 68
	0x2d, 0x1d, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x39, 0x19, 0x50,	// 69
	0x2d, 0x1d, 0x39, 0x19, 0x39, 0x19, 0x39, 0x59, 0x50,	// 70
	0x2c, 0x32, 0x1a, 0x21, 0x31, 0x21, 0x31, 0x19, 0x39, 0x19, 0x24, 0x21, 0x68,	// 71
	0x2d, 0x1d, 0x59, 0x59, 0x59, 0x5d, 0x1d, 0x50,	// 72
	0x2d, 0x1d, 0x30,	// 73
	0x59, 0x52, 0x2e, 0x15, 0x30,	// 74
	0x2d, 0x1d, 0x59, 0x51, 0x9, 0x41, 0x1a, 0x29, 0x2a, 0x19, 0x39, 0x30,	// 75
	0x2d, 0x1d, 0x19, 0x59, 0x59, 0x59, 0x30,	// 76
	0x34, 0x1d, 0x39, 0x5d, 0x62, 0x42, 0x3b, 0x49, 0x24, 0x1d, 0x50,	// 77
	0x34, 0x1d, 0x3a, 0x64, 0x62, 0x45, 0x1c, 0x58,	// 78
	0x2c, 0x32, 0x1a, 0x21, 0x31, 0x21, 0x31, 0x19, 0x31, 0x21, 0x31, 0x22, 0x1a, 0x34, 0x30,	// 79
	0x2d, 0x1c, 0x9, 0x31, 0x21, 0x31, 0x21, 0x31, 0x19, 0x43, 0x38,	// 80
	0x2c, 0x32, 0x1a, 0x21, 0x31, 0x21, 0x31, 0x19, 0x31, 0x9, 0x11, 0x31, 0x9, 0x12, 0x1a, 0x19, 0x14, 0x29,	// 81
	0x2d, 0x1d, 0x39, 0x19, 0x39, 0x1b, 0x29, 0x11, 0x1a, 0x22, 0x29, 0x10,	// 82
	0x41, 0x2b, 0x21, 0x19, 0x12, 0x19, 0x19, 0x1a, 0x11, 0x19, 0x23, 0x29, 0x48,	// 83
	0x9, 0x59, 0x59, 0x1d, 0x1d, 0x39, 0x59, 0x59, 0x70,	// 84
	0x2c, 0x25, 0x12, 0x59, 0x59, 0x51, 0x43, 0x2c, 0x58,	// 85
	0xf, 0x2, 0x51, 0x51, 0x51, 0x4a, 0x3b, 0x40,	// 86
	0xf, 0x2, 0x51, 0x4a, 0x42, 0x47, 0x1, 0x51, 0x4a, 0x42, 0x3b, 0x60,	// 87
	0x42, 0x19, 0x29, 0x2a, 0x19, 0x43, 0x5b, 0x41, 0x1a, 0x29, 0x29, 0x1a, 0x48,	// 88
	0xd, 0x64, 0x41, 0x51, 0x4a, 0x42, 0x48,	// 89
	0x42, 0x49, 0x9, 0x19, 0x21, 0x11, 0x19, 0x19, 0x19, 0x19, 0x11, 0x21, 0x19, 0x9, 0x29, 0x1a, 0x51, 0x50,	// 90
	0x43, 0x2c, 0x11, 0xc, 0x31, 0x9, 0x59, 0x78,	// 91
	0x3, 0x62, 0x63, 0x63, 0x8,	// 92
	0x51, 0x59, 0x9, 0x34, 0x9, 0x14, 0x2b, 0x68,	// 93
	0x32, 0x49, 0x51, 0x51, 0x56, 0x40,	// 94
	0x51, 0x59, 0x59, 0x59, 0x59, 0x59, 0x8,	// 95
	0x1, 0x61, 0x50,	// 96
	0x33, 0x3a, 0x19, 0x29, 0x29, 0x29, 0x21, 0x31, 0x1b, 0x2c, 0x28,	// 97
	0x34, 0x2b, 0x19, 0x13, 0x9, 0x21, 0x29, 0x29, 0x29, 0x1a, 0x3b, 0x28,	// 98
	0x2c, 0x39, 0x21, 0x29, 0x29, 0x29, 0x29, 0x31, 0x58,	// 99
	0x33, 0x3a, 0x19, 0x29, 0x29, 0x29, 0x21, 0x31, 0x1b, 0x2c, 0x2b, 0x68,	// 100
	0x2c, 0x39, 0x9, 0x11, 0x29, 0x11, 0x11, 0x29, 0x11, 0x11, 0x32, 0x50,	// 101
	0x52, 0x19, 0x1b, 0x2c, 0x33, 0x41, 0x11, 0x41, 0x11, 0x40,	// 102
	0x32, 0x19, 0x22, 0x11, 0x11, 0x19, 0x21, 0x11, 0x19, 0x19, 0x11, 0x21, 0x14, 0x2b, 0x30,	// 103
	0x3b, 0x2c, 0x2b, 0x9, 0x51, 0x59, 0x1b, 0x2c, 0x28,	// 104
	0x3b, 0x2c, 0x2a, 0x70,	// 105
	0x59, 0x59, 0x43, 0x25, 0x22, 0x70,	// 106
	0x3b, 0x2c, 0x2b, 0x19, 0x51, 0x9, 0x41, 0x19, 0x31, 0x29, 0x10,	// 107
	0x3b, 0x2c, 0x2b, 0x68,	// 108
	0x3b, 0x2c, 0x49, 0x51, 0x59, 0x1b, 0x2c, 0x49, 0x51, 0x59, 0x1b, 0x2c, 0x28,	// 109
	0x3b, 0x2c, 0x49, 0x51, 0x59, 0x1b, 0x2c, 0x28,	// 110
	0x2c, 0x39, 0x21, 0x29, 0x29, 0x29, 0x21, 0x3c, 0x40,	// 111
	0x52, 0x34, 0x2b, 0x19, 0x31, 0x21, 0x29, 0x29, 0x29, 0x1a, 0x3b, 0x48,	// 112
	0x33, 0x3a, 0x19, 0x29, 0x29, 0x29, 0x21, 0xa, 0x19, 0x1b, 0x2c, 0x28,	// 113
	0x34, 0x2c, 0x49, 0x51, 0x59, 0x60,	// 114
	0x41, 0x3a, 0x19, 0x29, 0xa, 0x11, 0x29, 0x12, 0x9, 0x29, 0x1a, 0x39, 0x38,	// 115
	0x19, 0x14, 0x2b, 0x19, 0x1b, 0x29, 0x29, 0x40,	// 116
	0x33, 0x33, 0x19, 0x59, 0x51, 0x4c, 0x2b, 0x30,	// 117
	0x1f, 0x51, 0x51, 0x51, 0x43, 0x50,	// 118
	0x1f, 0x51, 0x51, 0x43, 0x63, 0x51, 0x4a, 0x3b, 0x30,	// 119
	0x42, 0x2a, 0x11, 0x4a, 0x5a, 0x49, 0x12, 0x2a, 0x38,	// 120
	0x59, 0x51, 0x27, 0x51, 0x51, 0x51, 0x43, 0x50,	// 121
	0x49, 0x29, 0x22, 0x29, 0x12, 0x9, 0x29, 0xa, 0x11, 0x2a, 0x21, 0x29, 0x40,	// 122
	0x29, 0x12, 0x22, 0x9, 0x9, 0x11, 0x11, 0x11, 0x9, 0x29, 0x58,	// 123
	0x3c, 0x2b, 0x2c, 0x60,	// 124
	0x51, 0x29, 0x9, 0x11, 0x11, 0x11, 0x9, 0xa, 0x22, 0x11, 0x30,	// 125
	0x31, 0x51, 0x59, 0x5a, 0x59, 0x59, 0x51, 0x50,	// 126
	0x0,	// 127

    }
};

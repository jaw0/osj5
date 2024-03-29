
// file: font/6x9.bdf
// font: -Misc-Fixed-Medium-R-Normal--9-90-75-75-C-60-ISO10646-1

#include <font.h>

const struct Font font_6x9 = {
    .type       = 1,
    .name	= "6x9",
    .height	= 9,
    .width	= 6,
    .lineheight = 9,
    .bytescol	= 2,
    .numcol     = 6,
    .startchar  = 33,
    .lastchar	= 148,
    .metrics    = 0,
    .fdata      = (const struct FontData[]){
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 0 }, // 33 [2]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 3 }, // 34 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 6 }, // 35 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 15 }, // 36 [6]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 28 }, // 37 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 41 }, // 38 [6]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 54 }, // 39 [2]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 56 }, // 40 [3]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 60 }, // 41 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 64 }, // 42 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 74 }, // 43 [6]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 80 }, // 44 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 84 }, // 45 [6]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 90 }, // 46 [3]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 93 }, // 47 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 98 }, // 48 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 105 }, // 49 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 110 }, // 50 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 120 }, // 51 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 130 }, // 52 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 138 }, // 53 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 149 }, // 54 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 158 }, // 55 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 165 }, // 56 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 176 }, // 57 [5]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 185 }, // 58 [3]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 190 }, // 59 [3]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 196 }, // 60 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 206 }, // 61 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 217 }, // 62 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 227 }, // 63 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 235 }, // 64 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 246 }, // 65 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 255 }, // 66 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 268 }, // 67 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 276 }, // 68 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 283 }, // 69 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 293 }, // 70 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 300 }, // 71 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 309 }, // 72 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 314 }, // 73 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 320 }, // 74 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 327 }, // 75 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 334 }, // 76 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 339 }, // 77 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 345 }, // 78 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 350 }, // 79 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 359 }, // 80 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 366 }, // 81 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 375 }, // 82 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 383 }, // 83 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 394 }, // 84 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 400 }, // 85 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 405 }, // 86 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 410 }, // 87 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 416 }, // 88 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 426 }, // 89 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 432 }, // 90 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 443 }, // 91 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 449 }, // 92 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 454 }, // 93 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 460 }, // 94 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 466 }, // 95 [6]
	{ .l0 = 2, .r0 = 2, .ncol = 2, .xadj = 0, .pos = 472 }, // 96 [3]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 475 }, // 97 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 482 }, // 98 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 489 }, // 99 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 497 }, // 100 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 504 }, // 101 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 512 }, // 102 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 518 }, // 103 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 527 }, // 104 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 532 }, // 105 [4]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 538 }, // 106 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 544 }, // 107 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 550 }, // 108 [4]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 555 }, // 109 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 561 }, // 110 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 566 }, // 111 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 573 }, // 112 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 580 }, // 113 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 587 }, // 114 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 592 }, // 115 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 601 }, // 116 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 607 }, // 117 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 612 }, // 118 [5]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 617 }, // 119 [6]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 623 }, // 120 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 630 }, // 121 [5]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 638 }, // 122 [5]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 647 }, // 123 [4]
	{ .l0 = 2, .r0 = 3, .ncol = 1, .xadj = 0, .pos = 653 }, // 124 [2]
	{ .l0 = 1, .r0 = 2, .ncol = 3, .xadj = 0, .pos = 655 }, // 125 [4]
	{ .l0 = 1, .r0 = 1, .ncol = 4, .xadj = 0, .pos = 661 }, // 126 [5]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 666 }, // 127 [0]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 667 }, // 128 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 675 }, // 129 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 681 }, // 130 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 689 }, // 131 [6]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 695 }, // 132 [6]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 705 }, // 133 [7]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 712 }, // 134 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 713 }, // 135 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 714 }, // 136 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 715 }, // 137 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 716 }, // 138 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 717 }, // 139 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 718 }, // 140 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 719 }, // 141 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 720 }, // 142 [0]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 721 }, // 143 [0]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 722 }, // 144 [7]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 739 }, // 145 [7]
	{ .l0 = 6, .r0 = 0, .ncol = 0, .xadj = -6, .pos = 756 }, // 146 [0]
	{ .l0 = 0, .r0 = 0, .ncol = 6, .xadj = 0, .pos = 757 }, // 147 [7]
	{ .l0 = 0, .r0 = 1, .ncol = 5, .xadj = 0, .pos = 771 }, // 148 [6]
    },
    .data       = {
	0xc, 0x9, 0x48,	// 33
	0xb, 0x7b, 0x50,	// 34
	0x19, 0x9, 0x27, 0x21, 0x9, 0x27, 0x21, 0x9, 0x30,	// 35
	0x12, 0x11, 0x19, 0x11, 0x11, 0xf, 0x2, 0x9, 0x11, 0x11, 0x19, 0x12, 0x28,	// 36
	0x9, 0x39, 0x9, 0x12, 0x19, 0x11, 0x39, 0x11, 0x1a, 0x11, 0x9, 0x39, 0x20,	// 37
	0x12, 0xa, 0x19, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1a, 0xa, 0x39, 0x9, 0x20,	// 38
	0xb, 0x60,	// 39
	0x15, 0x19, 0x29, 0x38,	// 40
	0x9, 0x29, 0x1d, 0x40,	// 41
	0x11, 0x9, 0x9, 0x2b, 0x39, 0x3b, 0x29, 0x9, 0x9, 0x28,	// 42
	0x21, 0x41, 0x35, 0x31, 0x41, 0x38,	// 43
	0x29, 0x11, 0x2b, 0x38,	// 44
	0x21, 0x41, 0x41, 0x41, 0x41, 0x38,	// 45
	0x2a, 0x3a, 0x40,	// 46
	0x2a, 0x31, 0x39, 0x32, 0x50,	// 47
	0x14, 0x21, 0x21, 0x19, 0x21, 0x24, 0x38,	// 48
	0x11, 0x19, 0x1e, 0x41, 0x38,	// 49
	0x11, 0x19, 0x19, 0x1a, 0x19, 0x11, 0x9, 0x22, 0x11, 0x30,	// 50
	0x9, 0x21, 0x19, 0x9, 0x11, 0x1b, 0x11, 0x19, 0x12, 0x38,	// 51
	0x22, 0x31, 0x9, 0x29, 0x11, 0x26, 0x39, 0x30,	// 52
	0xb, 0x11, 0x19, 0x9, 0x11, 0x19, 0x9, 0x11, 0x19, 0x12, 0x38,	// 53
	0x14, 0x21, 0x9, 0x11, 0x19, 0x9, 0x11, 0x32, 0x38,	// 54
	0x9, 0x41, 0x1a, 0x19, 0x11, 0x2b, 0x48,	// 55
	0x11, 0xa, 0x21, 0x9, 0x11, 0x19, 0x9, 0x11, 0x21, 0xa, 0x38,	// 56
	0x12, 0x31, 0x11, 0x9, 0x19, 0x11, 0x9, 0x24, 0x38,	// 57
	0x12, 0xa, 0x22, 0xa, 0x40,	// 58
	0x12, 0x9, 0x11, 0x12, 0xb, 0x38,	// 59
	0x21, 0x39, 0x9, 0x31, 0x9, 0x29, 0x19, 0x21, 0x19, 0x28,	// 60
	0x19, 0x9, 0x31, 0x9, 0x31, 0x9, 0x31, 0x9, 0x31, 0x9, 0x30,	// 61
	0x11, 0x19, 0x21, 0x19, 0x29, 0x9, 0x31, 0x9, 0x39, 0x38,	// 62
	0x9, 0x39, 0x12, 0x9, 0x11, 0x11, 0x32, 0x50,	// 63
	0x14, 0x21, 0x21, 0x19, 0xa, 0x9, 0x1a, 0x9, 0x9, 0x29, 0x40,	// 64
	0x1c, 0x21, 0x9, 0x29, 0x11, 0x31, 0x9, 0x3c, 0x28,	// 65
	0xe, 0x19, 0x9, 0x11, 0x19, 0x9, 0x11, 0x19, 0x9, 0x11, 0x21, 0xa, 0x30,	// 66
	0x14, 0x21, 0x21, 0x19, 0x21, 0x21, 0x11, 0x38,	// 67
	0xe, 0x19, 0x21, 0x19, 0x21, 0x24, 0x38,	// 68
	0xe, 0x19, 0x9, 0x11, 0x19, 0x9, 0x11, 0x19, 0x21, 0x30,	// 69
	0xe, 0x19, 0x9, 0x31, 0x9, 0x31, 0x58,	// 70
	0x14, 0x21, 0x21, 0x19, 0x11, 0x9, 0x21, 0xa, 0x38,	// 71
	0xe, 0x29, 0x41, 0x36, 0x30,	// 72
	0x9, 0x21, 0x1e, 0x19, 0x21, 0x38,	// 73
	0x29, 0x49, 0x19, 0x21, 0x1d, 0x21, 0x50,	// 74
	0xe, 0x29, 0x39, 0x9, 0x29, 0x1a, 0x30,	// 75
	0xe, 0x41, 0x41, 0x41, 0x30,	// 76
	0xe, 0x21, 0x4a, 0x31, 0x3e, 0x28,	// 77
	0xe, 0x21, 0x49, 0x36, 0x30,	// 78
	0x14, 0x21, 0x21, 0x19, 0x21, 0x19, 0x21, 0x24, 0x30,	// 79
	0xe, 0x19, 0x11, 0x29, 0x11, 0x32, 0x48,	// 80
	0x14, 0x21, 0x11, 0x9, 0x19, 0x1a, 0x24, 0x9, 0x28,	// 81
	0xe, 0x19, 0x11, 0x29, 0x11, 0x32, 0xa, 0x30,	// 82
	0x11, 0x11, 0x21, 0x9, 0x11, 0x19, 0x11, 0x9, 0x21, 0x11, 0x38,	// 83
	0x9, 0x41, 0x46, 0x19, 0x41, 0x50,	// 84
	0xd, 0x49, 0x41, 0x1d, 0x38,	// 85
	0xc, 0x43, 0x33, 0x1c, 0x40,	// 86
	0xe, 0x39, 0x32, 0x49, 0x26, 0x28,	// 87
	0x9, 0x21, 0x21, 0x11, 0x32, 0x31, 0x11, 0x21, 0x21, 0x28,	// 88
	0xa, 0x49, 0x4b, 0x29, 0x32, 0x48,	// 89
	0x9, 0x1a, 0x19, 0x11, 0x9, 0x19, 0x9, 0x11, 0x1a, 0x19, 0x30,	// 90
	0xe, 0x19, 0x21, 0x19, 0x21, 0x38,	// 91
	0xa, 0x49, 0x49, 0x4a, 0x30,	// 92
	0x9, 0x21, 0x19, 0x21, 0x1e, 0x38,	// 93
	0x19, 0x39, 0x39, 0x49, 0x49, 0x40,	// 94
	0x41, 0x41, 0x41, 0x41, 0x41, 0x18,	// 95
	0x9, 0x49, 0x60,	// 96
	0x22, 0x31, 0x11, 0x29, 0x11, 0x2c, 0x30,	// 97
	0xe, 0x29, 0x11, 0x29, 0x11, 0x32, 0x38,	// 98
	0x22, 0x31, 0x11, 0x29, 0x11, 0x29, 0x11, 0x30,	// 99
	0x22, 0x31, 0x11, 0x29, 0x11, 0x1e, 0x30,	// 100
	0x22, 0x31, 0xa, 0x2a, 0x9, 0x31, 0x9, 0x30,	// 101
	0x21, 0x35, 0x19, 0x11, 0x31, 0x50,	// 102
	0x22, 0x31, 0x11, 0x9, 0x19, 0x11, 0x9, 0x24, 0x28,	// 103
	0xe, 0x29, 0x41, 0x4b, 0x30,	// 104
	0x19, 0x11, 0x19, 0xc, 0x41, 0x38,	// 105
	0x39, 0x21, 0x21, 0x9, 0xd, 0x30,	// 106
	0xe, 0x31, 0x39, 0x9, 0x49, 0x30,	// 107
	0x9, 0x21, 0x1e, 0x41, 0x38,	// 108
	0x1c, 0x29, 0x4a, 0x31, 0x4b, 0x28,	// 109
	0x1c, 0x29, 0x41, 0x4b, 0x30,	// 110
	0x22, 0x31, 0x11, 0x29, 0x11, 0x32, 0x38,	// 111
	0x1e, 0x19, 0x11, 0x29, 0x11, 0x32, 0x38,	// 112
	0x22, 0x31, 0x11, 0x29, 0x11, 0x2e, 0x20,	// 113
	0x1c, 0x31, 0x39, 0x49, 0x40,	// 114
	0x21, 0x9, 0x2a, 0x9, 0x29, 0xa, 0x29, 0x9, 0x38,	// 115
	0x19, 0x35, 0x31, 0x11, 0x39, 0x38,	// 116
	0x1b, 0x49, 0x41, 0x2c, 0x30,	// 117
	0x1a, 0x4a, 0x3a, 0x2a, 0x40,	// 118
	0x1b, 0x49, 0x32, 0x49, 0x2b, 0x30,	// 119
	0x19, 0x11, 0x32, 0x3a, 0x31, 0x11, 0x30,	// 120
	0x1b, 0x9, 0x39, 0x9, 0x31, 0x9, 0x1d, 0x28,	// 121
	0x19, 0x11, 0x29, 0xa, 0x2a, 0x9, 0x29, 0x11, 0x30,	// 122
	0x19, 0x32, 0xa, 0x19, 0x29, 0x38,	// 123
	0xf, 0x40,	// 124
	0x1, 0x29, 0x1a, 0xa, 0x31, 0x50,	// 125
	0x19, 0x39, 0x49, 0x39, 0x50,	// 126
	0x0,	// 127
	0x21, 0x3b, 0x29, 0x9, 0x9, 0x31, 0x41, 0x38,	// 128
	0x19, 0x39, 0x3e, 0x21, 0x49, 0x40,	// 129
	0x21, 0x41, 0x31, 0x9, 0x9, 0x2b, 0x39, 0x38,	// 130
	0x21, 0x49, 0x26, 0x39, 0x39, 0x38,	// 131
	0x19, 0x9, 0x29, 0x19, 0x1f, 0x19, 0x19, 0x29, 0x9, 0x30,	// 132
	0x21, 0x3b, 0x39, 0x41, 0x3b, 0x39, 0x30,	// 133
	0x0,	// 134
	0x0,	// 135
	0x0,	// 136
	0x0,	// 137
	0x0,	// 138
	0x0,	// 139
	0x0,	// 140
	0x0,	// 141
	0x0,	// 142
	0x0,	// 143
	0xe, 0x11, 0x9, 0x9, 0x11, 0x9, 0x21, 0x9, 0x9, 0x21, 0x9, 0x9, 0x9, 0x9, 0x11, 0x16, 0x20,	// 144
	0xe, 0x11, 0x9, 0x11, 0x9, 0x9, 0x19, 0x11, 0x9, 0x19, 0x11, 0x9, 0x9, 0x11, 0x9, 0x16, 0x20,	// 145
	0x0,	// 146
	0xd, 0x19, 0x29, 0x11, 0x11, 0x11, 0x11, 0x9, 0x9, 0x9, 0x11, 0x29, 0x1d, 0x28,	// 147
	0x13, 0x2d, 0x2d, 0x1d, 0x2b, 0x38,	// 148

    }
};

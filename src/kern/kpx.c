
static void kprintn(unsigned long ul, int base);

void
kprintf(const char *fmt, ...){
        va_list ap;
        va_start(ap,fmt);

	char *p;
	int ch, n;
	unsigned long ul;
	int lflag, set;

	for (;;) {
		while ((ch = *fmt++) != '%') {
			if (ch == '\0')
				return;
			stm32_putchar(ch);
		}
		lflag = 0;
reswitch:	switch (ch = *fmt++) {
                case '0': case '1': case '2': case '3':
                case '4': case '5': case '6': case '7':
                case '8': case '9': case '.': case '-':
                    /* ignore */
                    goto reswitch;

                case '\0':
			/* XXX print the last format character? */
			return;
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'c':
			ch = va_arg(ap, int);
				stm32_putchar(ch & 0x7f);
			break;
		case 's':
			p = va_arg(ap, char *);
			while ((ch = *p++))
				stm32_putchar(ch);
			break;
		case 'd':
			ul = lflag ?
			    va_arg(ap, long) : va_arg(ap, int);
			if ((long)ul < 0) {
				stm32_putchar('-');
				ul = -(long)ul;
			}
			kprintn(ul, 10);
			break;
		case 'o':
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 8);
			break;
		case 'u':
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 10);
			break;
		case 'p':
			stm32_putchar('0');
			stm32_putchar('x');
			lflag = 1;
			/* fall through */
		case 'x':
			ul = lflag ?
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 16);
			break;
		default:
			stm32_putchar('%');
			if (lflag)
				stm32_putchar('l');
			stm32_putchar(ch);
		}
	}
}

static void
kprintn(unsigned long ul, int base){
    /* hold a long in base 8 */
	char *p, buf[(sizeof(long) * 8 / 3) + 1];

	p = buf;
	do {
		*p++ = "0123456789abcdef"[ul % base];
	} while (ul /= base);
	do {
		stm32_putchar(*--p);
	} while (p > buf);
}

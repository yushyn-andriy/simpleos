#include "stdlib.h"
#include "kernel.h"
#include "string/string.h"
#include "terminal/terminal.h"


void print(const char *str)
{
	size_t len = strlen(str);
	for(int i = 0; i<len; i++)
		terminal_writechar(str[i], TERMINAL_DEFAULT_COLOR);
}


void print_size_t(size_t n)
{
	char res[SIZE_T_MAX_LEN+1];

	if(n == 0) {
		res[0] = 0x30;
		res[1] = 0;
		goto pout;
	} 


	int i = 0;
	while(n>0) {
		int rest = n % 10;
		n =  (n - rest) / 10;
		res[i] = rest + 0x30;
		i++;
	}
	res[i] = 0;
	strrev(res);

pout:
	print(res);
}

void print_hex(unsigned int num) {
    char hex_chars[] = "0123456789ABCDEF";
    int i;
    int started = 0;

	terminal_writechar('0', TERMINAL_DEFAULT_COLOR);
	terminal_writechar('x', TERMINAL_DEFAULT_COLOR);

    for (i = 28; i >= 0; i -= 4) {
        int digit = (num >> i) & 0xF;
        if (digit != 0 || started || i == 0) {
			terminal_writechar(hex_chars[digit], TERMINAL_DEFAULT_COLOR);
            started = 1;
        }
    }
}

void terminal_ascii_test() {
	for(char ch = 0x21; ch<=0x7e; ch++)
		terminal_writechar(ch, TERMINAL_DEFAULT_COLOR);
}
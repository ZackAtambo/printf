#include <stdio.h>

#define PRINTF_CHAR        1
#define PRINTF_STRING      2
#define PRINTF_PERCENT     3

int _printf(const char *format, ...);

int main(void)
{
    int len;
    int len2;
    unsigned int ui;
    void *addr;

    len = _printf(" printf a simple sentence.\n");
    len2 = printf(" printf a simple sentence.\n");
    ui = (unsigned int)INT_MAX + 1024;
    addr = (void *)0x7ffe637541f0;
    _printf("Length:[%d, %i]\n", len, len);
    printf("Length:[%d, %i]\n", len2, len2);
    _printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    _printf("Unsigned octal:[%o]\n", ui);
    printf("Unsigned octal:[%o]\n", ui);
    _printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    _printf("Character:[%c]\n", 'H');
    printf("Character:[%c]\n", 'H');
    _printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");
    _printf("Address:[%p]\n", addr);
    printf("Address:[%p]\n", addr);
    len = _printf("Percent:[%%]\n");
    len2 = printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);
    _printf("Unknown:[%r]\n");
    printf("Unknown:[%r]\n");
    return (0);
}

int _printf(const char *format, ...) {
    int count = 0;
    char ch;
    char *str;
    void *ptr;

    while (*format) {
        if (*format == '%') {
            format++; // Move past the '%'

            // Handle conversion specifiers
            switch (*format) {
                case 'c':
                    ch = (char) *(int *)&format;
                    format += sizeof(int);
                    putchar(ch);
                    count++;
                    break;
                case 's':
                    str = *(char **)&format;
                    format += sizeof(char *);
                    while (*str) {
                        putchar(*str);
                        str++;
                        count++;
                    }
                    break;
                case '%':
                    putchar('%');
                    count++;
                    break;
                default:
                    // Unsupported conversion specifier, ignore
                    break;
            }
        } else {
            putchar(*format);
            count++;
        }

        format++;
    }

    return count;
}

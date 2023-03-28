#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

#ifndef TRUE
#define TRUE 1
#endif
#ifndef T
#define T 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif
#define MAX_WIDTH "2147483647"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) > (0) ? (a) : (0 - (a)))
#define NO_NEG(a) ((a) < (0) ? (0) : ((a)))
#define NO_LESS(a, b) ((a) < (b) ? (b) : ((a)))
#define TO_UPPER(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 6 - 26 : (c))
#define TO_LOWER(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + 6 + 26 : (c))
#define FMT_PREC_EMPTY(fmt_inf) (fmt_inf->is_precision_set && !fmt_inf->prec)

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/* Handlers */
unsigned char handle_flags(const char *flags, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/* Helper Functions */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);
/**
 * struct format_info - Contains information about the options
 * \ and flags appearing in an instance of the conversion specifier
 * @prec: The specified precision
 * @width: The length of the formatted data
 * @spec: The specified conversion specifier character
 * @is_long_double: Specifies the presence of the 'L' length modifier
 * @is_long_long: Specifies the presence of the 'll' length modifier
 * @is_long: Specifies the presence of the 'l' length modifier
 * @is_short: Specifies the presence of the 'h' length modifier
 * @is_char: Specifies the presence of the 'hh' length modifier
 * @is_precision_set: Specifies the presence of a precision value
 * @is_width_set: Specifies the presence of a width value
 * @alt: Specifies the presence of the '#' flag
 * @space: Specifies the presence of the ' ' (invisible plus sign) flag
 * @left: Specifies the presence of the '-' (left-align) flag
 * @show_sign: Specifies the presence of the '+' flag
 * @group: The current locale's digit separator for integers
 * @pad: This is the character to use for padding the output
 */
struct format_info
{
	int prec;
	int width;
	char spec;
	char is_long_double;
	char is_long;
	char is_long_long;
	char is_short;
	char is_char;
	char is_precision_set;
	char is_width_set;
	char alt;
	char space;
	char left;
	char show_sign;
	char group;
	char pad;
};
typedef struct format_info fmt_info_t;
/**
 * struct spec_printer - Represents a function that prints an argument
 * \ based on a determined format
 * @spec: The conversion specifier
 * @print_arg: The pointer to the printing function
 */
struct spec_printer
{
	char spec;
	void (*print_arg)(va_list *args, fmt_info_t *fmt_info);
};
typedef struct spec_printer spec_printer_t;
typedef unsigned char uchar_t;
typedef unsigned short ushort_t;

/**
 * struct float_info - Represents the IEE754 specification of a float
 * @sign: The sign of the float
 * @exponent: The exponent of the float
 * @mantissa: The mantissa of the float
 */
struct float_info
{
	char sign;
	char *exponent;
	char *mantissa;
};
typedef struct float_info float_info_t;


int _putchar(char c);
int _putstr(char *str);
int write_to_buffer(char c, char action);
int _printf(const char *format, ...);
void write_format(va_list *args_list, fmt_info_t *fmt_info);


void print_repeat(char c, int n);
void _putnchars(int n, ...);
char is_letter(char c);
void set_format_error(const char *, int *, int len, int, int *);
void put_num(int zeros_count, long num, char *str);


void init_format_info(fmt_info_t *spec);
fmt_info_t *new_format_info();
float_info_t *new_float_info(ushort_t exponent_size, ushort_t mantissa_size);
void free_float_info(float_info_t *flt_info);


int set_number(const char *str, int *number);
void set_length(char cur, int *pos, fmt_info_t *fmt_info);
int set_flags(const char *str, fmt_info_t *fmt_info);
void set_precision(const char *str, va_list args,
	fmt_info_t *fmt_info, int *i, int *error_status);
int read_format_info(const char *, va_list, fmt_info_t *, int *);


void convert_fmt_percent(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_p(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_c(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_s(va_list *args_list, fmt_info_t *fmt_info);

void convert_fmt_di(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_xX(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_o(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_u(va_list *args_list, fmt_info_t *fmt_info);

void convert_fmt_b(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_R(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_r(va_list *args_list, fmt_info_t *fmt_info);
void convert_fmt_S(va_list *args_list, fmt_info_t *fmt_info);

void convert_fmt_fF(va_list *args_list, fmt_info_t *fmt_info);


int str_len(char *str);
void mem_set(char *str, int n, char c);
void left_shift(char *str, int n);
int index_of(char *str, char c);
void rev_string(char *s);

char *append_char(char *str, char c, int n, char can_free);
char *delete_char(char *str, char c, char can_free);
char *insert_char(char *str, int pos, char c, char can_free);
int count_char(char *str, char c);
char *str_cat(char *left, char *right, char can_free);

char *sub_str(char *str, int i, char can_free);
char *trim_start(char *str, char c, char can_free);
char *trim_end(char *str, char c, char can_free);
char *str_copy(char *str);


char hex_digit(char c);
char cmp_nums(char *left, char *right);
int str_to_int(char *num);
int bin_to_int(char *bin_str);
char *long_to_oct(unsigned long num);

char *multiply(char *num, char *multiple);
char *add_int(char *left, char *right, int can_free);
char *add_float(char *left, char *right, char can_free);
char *mul_int(char *num1, char *num2, char can_free);
char *mul_float(char *left, char *right, char can_free);

char *div_by_10_exp(char *num, unsigned short n, char can_free);
char *two_exp(short n);
char *five_exp(unsigned short n);
unsigned int two_pexp(unsigned int n);
char *u_long_to_hex(unsigned long num, char upper);

char *round_float(char *num, unsigned int precision, char can_free);
char *round_float_to_int(char *num, int len, int dec_pos, int frac_len);


char *u_long_to_str(unsigned long num);
char *long_to_str(long num);
char *ptr_to_str(void *ptr);
char *is_invalid(float_info_t *flt_info);

void set_float_parts(double num,	uchar_t exponent_size,
	uchar_t mantissa_size, float_info_t *float_info);
char *mantissa_to_dec_fraction(char *mantissa, unsigned short frac_len);
char *float_to_str(float_info_t *flt_info, char can_free);


char is_digit(char c);
char is_non_custom_specifier(char c);
char is_specifier(char c);
char is_flag(char c);
char is_length(char c);

#endif

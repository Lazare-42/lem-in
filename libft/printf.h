/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 19:50:49 by lazrossi          #+#    #+#             */
/*   Updated: 2018/07/24 17:19:57 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H

# define BUFF_SIZE 4096
# define RESET "\x1B[0m"
# define BLD "\x1B[1m"
# define ITA "\x1B[3m"
# define BLK "\x1B[6m"
# define SWP "\x1B[7m"
# define UND "\x1B[4m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define BCK "\x1B[40m"
# define FRM "\x1B[51m"

# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>

typedef struct		s_str
{
	int		position;
	char	str[BUFF_SIZE];
}					t_str;

typedef struct		s_printf
{
	int				arg_len;
	int				activate_precision;
	char			percentage_presence;
	char			type;
	char			zeros_width;
	char			modifier[3];
	char			sign[3];
	char			left_align_output;
	char			show_sign;
	char			sharp;
	int				width;
	int				precision;
	t_str			*argument_str;
}					t_printf;

int					get_char_len(va_list ap, t_printf *argument);
int					get_number_len(va_list ap, t_printf *argument);
void				update_str(t_str *argument, void *to_cpy, int mem_op_size);
int					get_precision(va_list ap, t_printf *argument,
		const char *format);
int					get_width(va_list ap, t_printf *argument,
		const char *format);
int					get_flags(t_printf *argument, const char	*format);
int					get_modifier(t_printf *argument, const char	*format);
int					ft_printf(const char *restrict format, ...);
void				store_char_data(va_list ap, t_printf *argument,
		t_str *argument_str);
void				store_number_data(va_list ap, t_printf *argument);
const char			*parse(const char *format, t_printf *argument, va_list ap);
void				get_hex_ptr_adr(va_list ap, t_printf *argument);
void				apply_width(t_printf *argument, t_str *argument_str);
void				apply_flag_padding(t_printf *argument, t_str *argument_str);
void				apply_plus_minus_flags(t_printf *argument,
		t_str *argument_str);
void				apply_precision(t_printf *argument, t_str *argument_str);
void				apply_sharp(t_printf *argument_specs, t_str *argument_str);
void				printf_u_base_converter(int base_size, uintmax_t number,
		int sizeof_var, t_printf *argument);
int					u_base_converter_len(int base_size,
		uintmax_t number, int sizeof_var, t_printf *argument);
int					s_base_converter_len(int base_size,
		intmax_t number, int sizeof_var, t_printf *argument);
unsigned long long	take_out_bits(uintmax_t to_change, int sizeof_var);
intmax_t			convert_overflow(int sizeof_var, intmax_t number);
void				printf_s_base_converter(int base_size, intmax_t number,
		int sizeof_var, t_printf *argument);
int					set_get_return(int action);
void				store_unicode_str(wchar_t *data, t_str *argument_str,
		t_printf *argument);
void				store_unicode(wint_t data, int precision,
		t_str *argument_str);
const char			*terminal_formatting(const char	*format, t_str *argument);
void				print(t_printf *arg, int location);
int					launch_string_print(const char *format, va_list ap,
		t_str *argument_str, int flush);
int					set_get_fd(int action);
const char			*choose_set_file_descriptor(const char *format,
		t_str *argument);
void				apply_precision_width(t_printf *argument_specs,
		t_str *argument_str);
t_printf			initialize_elem(void);
void				treat_and_store_argument(va_list ap,
		t_printf *argument_specs,
					t_str *argument_str);
const char			*store_string(const char *format, t_str *argument_str);

#endif

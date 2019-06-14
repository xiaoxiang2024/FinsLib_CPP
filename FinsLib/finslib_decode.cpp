#include <ctype.h>
#include "fins.h"

/*
* bool XX_finslib_decode_address( const char *str, fins_address_tp *address );
*
* 将一个字符串作为参数并将其解码为一个同名地址对。
* 该功能跳过空格和其他明显的非功能性字符。 
* 成功时，返回false值，并在转换出现问题时返回true。
*
* 位引用必须使用DOT符号，例如H82.1来生成正确的地址。
*/

bool XX_finslib_decode_address(const char *str, struct fins_address_tp *address) {

	size_t num_char;
	uint32_t main_address;
	uint32_t sub_address;
	char name[4];
	const char *ptr;

	if (str == NULL || address == NULL) return true;

	num_char = 0;
	ptr = str;
	main_address = 0;
	sub_address = 0;

	while (isspace(*ptr)) ptr++;

	while (isalpha(*ptr) && num_char < 3) {

		name[num_char] = (char)toupper(*ptr);
		num_char++;
		ptr++;
	}
	if (isalpha(*ptr)) return true;

	while (num_char < 4) name[num_char++] = 0;

	while (isspace(*ptr)) ptr++;
	if (!isdigit(*ptr)) return true;

	while (isdigit(*ptr)) {

		main_address *= 10;
		main_address += *ptr - '0';
		ptr++;
	}

	if (*ptr == '.') {

		ptr++;
		while (isdigit(*ptr)) {

			sub_address *= 10;
			sub_address += *ptr - '0';
			ptr++;
		}

		if (sub_address > 15) return true;
	}

	while (isdigit(*ptr)) ptr++;

	if (*ptr) return true;

	address->name[0] = name[0];
	address->name[1] = name[1];
	address->name[2] = name[2];
	address->name[3] = name[3];

	address->main_address = main_address;
	address->sub_address = sub_address;

	return false;

}  /* XX_finslib_decode_address */

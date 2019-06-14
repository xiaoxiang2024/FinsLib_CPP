#include "fins.h"

/*
* int finslib_memory_area_write_int16( struct fins_sys_tp *sys, const char *start, const int16_t *data, size_t num_int16 );
*
* 在远程PLC的存储区中写入一组有符号的16位整数。
* 传入参数为FINS设备指针，起始地址的char指针，格式类似“CIO100”，要写入的数据所在的内存指针，需要写入的int16_t的个数
*/

int finslib_memory_area_write_int16(struct fins_sys_tp *sys, const char *start, const int16_t *data, size_t num_int16) {

	return finslib_memory_area_write_uint16(sys, start, (const uint16_t *)data, num_int16);

}  /* finslib_memory_area_write_int16 */



   /*
   * int finslib_memory_area_write_uint16( struct fins_sys_tp *sys, const char *start, const uint16_t *data, size_t num_uint16 );
   *
   * 在远程PLC的存储区中写入一组无符号的16位整数。
   *
   * 该函数返回FINS_RETVAL _...列表中的成功或错误代码。
   * 传入参数为FINS设备指针，起始地址的char指针，格式类似“CIO100”，要写入的数据所在的内存指针，需要写入的uint16_t的个数
   */

int finslib_memory_area_write_uint16(struct fins_sys_tp *sys, const char *start, const uint16_t *data, size_t num_uint16) {

	size_t chunk_start;
	size_t chunk_length;
	size_t offset;
	size_t a;
	size_t todo;
	size_t bodylen;
	struct fins_command_tp fins_cmnd;
	const struct fins_area_tp *area_ptr;
	struct fins_address_tp address;
	int retval;

	if (num_uint16 == 0) return FINS_RETVAL_SUCCESS;
	if (sys == NULL) return FINS_RETVAL_NOT_INITIALIZED;
	if (start == NULL) return FINS_RETVAL_NO_WRITE_ADDRESS;
	if (data == NULL) return FINS_RETVAL_NO_DATA_BLOCK;
	if (sys->sockfd == INVALID_SOCKET) return FINS_RETVAL_NOT_CONNECTED;
	if (XX_finslib_decode_address(start, &address)) return FINS_RETVAL_INVALID_WRITE_ADDRESS;

	area_ptr = XX_finslib_search_area(sys, &address, 16, FI_WR, false);
	if (area_ptr == NULL) return FINS_RETVAL_INVALID_WRITE_AREA;

	offset = 0;
	todo = num_uint16;
	chunk_start = address.main_address;
	chunk_start += area_ptr->low_addr >> 8;
	chunk_start -= area_ptr->low_id;

	do {
		chunk_length = FINS_MAX_WRITE_WORDS_SYSWAY;
		if (chunk_length > todo) chunk_length = todo;

		XX_finslib_init_command(sys, &fins_cmnd, 0x01, 0x02);

		bodylen = 0;

		fins_cmnd.body[bodylen++] = area_ptr->area;
		fins_cmnd.body[bodylen++] = (chunk_start >> 8) & 0xff;
		fins_cmnd.body[bodylen++] = (chunk_start) & 0xff;
		fins_cmnd.body[bodylen++] = 0x00;
		fins_cmnd.body[bodylen++] = (chunk_length >> 8) & 0xff;
		fins_cmnd.body[bodylen++] = (chunk_length) & 0xff;

		for (a = 0; a<chunk_length; a++) {

			fins_cmnd.body[bodylen++] = (data[offset + a] >> 8) & 0xff;
			fins_cmnd.body[bodylen++] = (data[offset + a]) & 0xff;
		}

		if ((retval = XX_finslib_communicate(sys, &fins_cmnd, &bodylen)) != FINS_RETVAL_SUCCESS) return retval;

		if (bodylen != 2) return FINS_RETVAL_BODY_TOO_SHORT;

		todo -= chunk_length;
		offset += chunk_length;
		chunk_start += chunk_length;

	} while (todo > 0);

	return FINS_RETVAL_SUCCESS;

}  /* finslib_memory_area_write_uint16 */

#include <iostream>
#include "../FinsLib/fins.h"
int main()
{
	fins_sys_tp* plc = NULL;
	int error_val;
	int error_max = 10;
	int error_code = 0;
	int16_t resultWrite = 7854;
	int16_t resultRead = 0;
	plc = finslib_tcp_connect(plc, "192.168.0.1",9600,2,&error_val, error_max);
	if(plc->error_count !=0)
	{
		int a = 0;
	}
	else
	{
		error_code = finslib_memory_area_write_int16(plc, "DM3", &resultWrite, 1);
		error_code = finslib_memory_area_read_int16(plc, "DM3", &resultRead, 1);
	}
	finslib_disconnect(plc);
	system("pause");
}
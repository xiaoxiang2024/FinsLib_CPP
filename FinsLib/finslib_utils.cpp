#include <string.h>
#include <time.h>
#include "fins.h"



time_t finslib_monotonic_sec_timer(void) {

#if defined(_WIN32)
	return GetTickCount64() / 1000;
#else
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec;
#endif

}  /* finslib_monotonic_sec_timer */


   /*
   * void finslib_milli_second_sleep( int msec );
   *
   * 让进程休眠一定时间，防止短时间发送大量不同的指令
   */

void finslib_milli_second_sleep(int msec) {

#ifdef _WIN32
	Sleep(msec);
#else
	usleep(1000 * msec);
#endif

}  /* finslib_milli_second_sleep */
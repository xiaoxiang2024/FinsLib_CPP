#include "fins.h"

/*
* void XX_finslib_init_command( fins_command_tp *command, uint8_t snn, uint8_t cnn );
*
* 初始化FINS命令结构，该命令结构将用于包含要发送到远程PLC的命令。
*/

void XX_finslib_init_command(struct fins_sys_tp *sys, struct fins_command_tp *command, uint8_t mrc, uint8_t src) {

	command->header[FINS_ICF] = 0x80;
	command->header[FINS_RSV] = 0x00;
	command->header[FINS_GCT] = 0x02;
	command->header[FINS_DNA] = sys->remote_net;
	command->header[FINS_DA1] = sys->remote_node;
	command->header[FINS_DA2] = sys->remote_unit;
	command->header[FINS_SNA] = sys->local_net;
	command->header[FINS_SA1] = sys->local_node;
	command->header[FINS_SA2] = sys->local_unit;
	command->header[FINS_SID] = sys->sid++;
	command->header[FINS_MRC] = mrc;
	command->header[FINS_SRC] = src;

} /* XX_finslib_init_command */

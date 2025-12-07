
#include "irx_imports.h"
#include "sifcmd.h"

void sceSifInitCmd(void) {
	// FIXME: stub
}

void sceSifExitCmd(void) {
	// FIXME: stub
}

unsigned int sceSifGetSreg(int index) {
	// FIXME: stub
	return 0;
}

void sceSifSetSreg(int index, unsigned int value) {
	// FIXME: stub
}

void sceSifSetCmdBuffer(SifCmdHandlerData_t *cmdBuffer, int size) {
	// FIXME: stub
}

void sceSifSetSysCmdBuffer(SifCmdSysHandlerData_t *sysCmdBuffer, int size) {
	// FIXME: stub
}

void sceSifAddCmdHandler(int cid, SifCmdHandler_t handler, void *harg) {
	// FIXME: stub
}

void sceSifRemoveCmdHandler(int cid) {
	// FIXME: stub
}

unsigned int sceSifSendCmd(int cmd, void *packet, int packet_size, void *src_extra, void *dest_extra, int size_extra) {
	// FIXME: stub
	return 0;
}


unsigned int isceSifSendCmd(int cmd, void *packet, int packet_size, void *src_extra, void *dest_extra, int size_extra) {
	// FIXME: stub
	return 0;
}

void sceSifInitRpc(int mode) {
	// FIXME: stub
}

int sceSifBindRpc(SifRpcClientData_t * client, int rpc_number, int mode) {
	// FIXME: stub
	return 0;
}

int sceSifCallRpc(SifRpcClientData_t * client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, SifRpcEndFunc_t end_function, void *end_param) {
	// FIXME: stub
	return 0;
}

void sceSifRegisterRpc(SifRpcServerData_t *sd, int sid, SifRpcFunc_t func, void *buf, SifRpcFunc_t cfunc, void *cbuf, SifRpcDataQueue_t *qd) {
	// FIXME: stub
}

int sceSifCheckStatRpc(SifRpcClientData_t * cd) {
	// FIXME: stub
	return 0;
}

void sceSifSetRpcQueue(SifRpcDataQueue_t *q, int thread_id) {
	// FIXME: stub
}

SifRpcServerData_t *sceSifGetNextRequest(SifRpcDataQueue_t * qd) {
	// FIXME: stub
	return NULL;
}

void sceSifExecRequest(SifRpcServerData_t * srv) {
	// FIXME: stub
}

void sceSifRpcLoop(SifRpcDataQueue_t *qd) {
	// FIXME: stub
}

int sceSifGetOtherData(SifRpcReceiveData_t *rd, void *src, void *dest, int size, int mode) {
	// FIXME: stub
	return 0;
}

SifRpcServerData_t *sceSifRemoveRpc(SifRpcServerData_t *sd, SifRpcDataQueue_t *qd) {
	// FIXME: stub
}

SifRpcDataQueue_t *sceSifRemoveRpcQueue(SifRpcDataQueue_t *qd) {
	// FIXME: stub
}

void sceSifSetSif1CB(void (*func)(void *userdata), void *userdata) {
	// FIXME: stub
}

void sceSifClearSif1CB(void) {
	// FIXME: stub
}

unsigned int sceSifSendCmdIntr(int cid, void * packet, int packet_size, void * src_extra, void * dest_extra, int size_extra, void (*completioncb)(void *userdata), void * userdata) {
	// FIXME: stub
	return 0;
}

unsigned int isceSifSendCmdIntr(int cid, void * packet, int packet_size, void * src_extra, void * dest_extra, int size_extra, void (*completioncb)(void *userdata), void * userdata) {
	// FIXME: stub
	return 0;
}




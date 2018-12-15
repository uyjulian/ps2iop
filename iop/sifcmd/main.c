
#include "irx_imports.h"
#include "sifcmd.h"

void sceSifInitCmd(void) {

}

void sceSifExitCmd(void) {

}

void sceSifGetSreg(int index) {

}

void sceSifSetSreg(int index, unsigned int value) {

}

void sceSifSetCmdBuffer(SifCmdHandlerData_t *cmdBuffer, int size) {

}

void sceSifSetSysCmdBuffer(SifCmdHandlerData_t *sysCmdBuffer, int size) {

}

void sceSifAddCmdHandler(int cid, SifCmdHandler_t handler, void *harg) {

}

void sceSifRemoveCmdHandler(int cid) {

}

unsigned int sceSifSendCmd(int cmd, void *packet, int packet_size, void *src_extra, void *dest_extra, int size_extra) {
	return 0;
}


unsigned int isceSifSendCmd(int cmd, void *packet, int packet_size, void *src_extra, void *dest_extra, int size_extra) {
	return 0;
}

void sceSifInitRpc(int mode) {

}

int sceSifBindRpc(SifRpcClientData_t * client, int rpc_number, int mode) {
	return 0;
}

int sceSifCallRpc(SifRpcClientData_t * client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, SifRpcEndFunc_t end_function, void *end_param) {
	return 0;
}

void sceSifRegisterRpc(SifRpcServerData_t *sd, int sid, SifRpcFunc_t func, void *buf, SifRpcFunc_t cfunc, void *cbuf, SifRpcDataQueue_t *qd) {

}

int sceSifCheckStatRpc(SifRpcClientData_t * cd) {
	return 0;
}

SifRpcDataQueue_t * sceSifSetRpcQueue(SifRpcDataQueue_t *q, int thread_id) {
	return NULL;
}

SifRpcServerData_t *sceSifGetNextRequest(SifRpcDataQueue_t * qd) {
	return NULL;
}

void sceSifExecRequest(SifRpcServerData_t * srv) {

}

void sceSifRpcLoop(SifRpcDataQueue_t *qd) {

}

int sceSifGetOtherData(SifRpcReceiveData_t *rd, void *src, void *dest, int size, int mode) {
	return 0;
}

SifRpcServerData_t *sceSifRemoveRpc(SifRpcServerData_t *sd, SifRpcDataQueue_t *qd) {

}

SifRpcDataQueue_t *sceSifRemoveRpcQueue(SifRpcDataQueue_t *qd) {

}

void sceSifSetSif1CB(void *func, int param) {

}

void sceSifClearSif1CB(void) {

}

unsigned int sceSifSendCmdIntr(unsigned int a, void * b, int c, void * d, void * e, int f, void (*g)(), void * h) {
	return 0;
}

unsigned int isceSifSendCmdIntr(unsigned int a, void * b, int c, void * d, void * e, int f, void (*g)(), void * h) {
	return 0;
}




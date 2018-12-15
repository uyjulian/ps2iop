
#include "irx_imports.h"
#include "ioman.h"

int open(const char *name, int mode) {
	// FIXME: stub
	return 0;
}

int close(int fd) {
	// FIXME: stub
	return 0;
}

int read(int fd, void *ptr, size_t size) {
	// FIXME: stub
	return 0;
}

int write(int fd, void *ptr, size_t size) {
	// FIXME: stub
	return 0;
}

int lseek(int fd, int pos, int mode) {
	// FIXME: stub
	return 0;
}

int ioctl(int fd, int command, void *arg) {
	// FIXME: stub
	return 0;
}

int remove(const char *name) {
	// FIXME: stub
	return 0;
}

int mkdir(const char *path) {
	// FIXME: stub
	return 0;
}

int rmdir(const char *path) {
	// FIXME: stub
	return 0;
}

int dopen(const char *path, int mode) {
	// FIXME: stub
	return 0;
}

int dclose(int fd) {
	// FIXME: stub
	return 0;
}

int dread(int fd, fio_dirent_t *buf) {
	// FIXME: stub
	return 0;
}

int getstat(const char *name, fio_stat_t *stat) {
	// FIXME: stub
	return 0;
}

int chstat(const char *name, fio_stat_t *stat, unsigned int statmask) {
	// FIXME: stub
	return 0;
}

int format(const char *dev) {
	// FIXME: stub
	return 0;
}

int AddDrv(iop_device_t *device) {
	// FIXME: stub
	return 0;
}

int DelDrv(const char *name) {
	// FIXME: stub
	return 0;
}

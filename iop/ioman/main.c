
#include "irx_imports.h"
#include <iomanX.h>

#include <errno.h>
#include <stdarg.h>

#ifdef IOP
IRX_ID("IO/File_Manager", 2, 3);
#endif
extern struct irx_export_table _exp_ioman;

static int open_tty_handles(const char *tty_name);
static int xx_stat(int op, const char *name, iox_stat_t *stat, unsigned int statmask);
static int xx_rename(int op, const char *oldname, const char *newname);
static int xx_dir(int op, const char *name, int mode);
static int _ioabort(const char *str1, const char *str2);
static iomanX_iop_file_t *new_iob(void);
static iomanX_iop_file_t *get_iob(int fd);
static iomanX_iop_device_t *lookup_dev(const char *name, int show_unkdev_msg);
static const char *parsefile(const char *path, iomanX_iop_device_t **p_device, int *p_unit);
static int tty_noop(void);
unsigned int iomanX_GetDevType(int fd);
static void ShowDrv(void);
static void register_tty(void);
static void register_dummytty(void);

struct ioman_dev_listentry
{
	struct ioman_dev_listentry *next;
	iomanX_iop_device_t *device;
};

int showdrvflag = 1;  // weak
iomanX_iop_device_ops_t dev_tty_dev_operations = {
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	(void *)&tty_noop,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};
iomanX_iop_device_t dev_tty = {
	"tty",
	IOP_DT_CHAR,
	1,
	"CONSOLE",
	&dev_tty_dev_operations,
};
iomanX_iop_device_t dev_dummytty = {
	"dummytty",
	IOP_DT_CHAR,
	1,
	"CONSOLE",
	&dev_tty_dev_operations,
};
int adddeldrv_in_process;
struct ioman_dev_listentry *device_entry_empty_list_head;
int errno_local;
struct ioman_dev_listentry *device_entry_used_list_head;
iomanX_iop_file_t file_table[32];
struct ioman_dev_listentry device_entry_list[16];

#ifndef isnum
#define isnum(c) ((c) >= '0' && (c) <= '9')
#endif

#define HANDLE_RESULT_CLEAR_INFO 1
#define HANDLE_RESULT_CLEAR_INFO_ON_ERROR 2
#define HANDLE_RESULT_RETURN_ZERO 4
#define HANDLE_RESULT_RETURN_FD 8

static inline void write_str_to_stdout(const char *in_str)
{
	iomanX_write(1, (void *)in_str, strlen(in_str));
}

static inline int set_errno(int in_errno)
{
	errno_local = in_errno;
	return -in_errno;
}

static inline void handle_result_pre(int in_result, iomanX_iop_file_t *f, int op)
{
	if ( (op & HANDLE_RESULT_CLEAR_INFO) )
	{
		if ( f )
		{
			f->mode = 0;
			f->device = NULL;
		}
	}
	if ( (op & HANDLE_RESULT_CLEAR_INFO_ON_ERROR) )
	{
		if ( f && (in_result < 0) )
		{
			// Unofficial: also clear mode
			f->mode = 0;
			f->device = NULL;
		}
	}
}

static inline int handle_result(int in_result, iomanX_iop_file_t *f, int op)
{
	handle_result_pre(in_result, f, op);
	if ( in_result < 0 )
		return set_errno(-in_result);
	if ( (op & HANDLE_RESULT_RETURN_ZERO) )
		return 0;
	if ( (op & HANDLE_RESULT_RETURN_FD) )
		return f - file_table;
	return in_result;
}

static inline s64 handle_result64(s64 in_result, iomanX_iop_file_t *f, int op)
{
	handle_result_pre(in_result, f, op);
	if ( in_result < 0 )
		return set_errno(-(int)in_result);
	if ( (op & HANDLE_RESULT_RETURN_ZERO) )
		return 0;
	if ( (op & HANDLE_RESULT_RETURN_FD) )
		return f - file_table;
	return in_result;
}

int _start(int ac, char **av)
{
	unsigned int i;

	(void)ac;
	(void)av;

	if ( RegisterLibraryEntries(&_exp_ioman) )
		return 1;
#if 0
	SetRebootTimeLibraryHandlingMode(&_exp_ioman, 2);
#else
	// Call termination before disabling interrupts
	_exp_ioman.mode &= ~6;
	_exp_ioman.mode |= 2;
#endif
	adddeldrv_in_process = 0;
	// Unofficial: memset instead of bzero
	memset(device_entry_list, 0, sizeof(device_entry_list));
	device_entry_used_list_head = NULL;
	device_entry_empty_list_head = device_entry_list;
	// Unofficial: link forwards instead of backwards
	for ( i = 0; i < ((sizeof(device_entry_list) / sizeof(device_entry_list[0])) - 1); i += 1 )
		device_entry_list[i].next = &device_entry_list[i + 1];
	// Unofficial: memset instead of bzero
	memset(file_table, 0, sizeof(file_table));
	iomanX_StdioInit(0);
	return 0;
}

int _ioman_deinit(int arg)
{
	struct ioman_dev_listentry *i;

	if ( !arg )
	{
		for ( i = device_entry_used_list_head; i; i = i->next )
		{
			i->device->ops->deinit(i->device);
			i->device = NULL;
		}
	}
	return 0;
}

void iomanX_StdioInit(int mode)
{
	const int *BootMode;
	iop_thread_info_t thinfo;

	BootMode = QueryBootMode(3);
	if ( BootMode && (BootMode[1] & 4) )
		return;
	ReferThreadStatus(0, &thinfo);
	ChangeThreadPriority(0, 4);
	switch ( mode )
	{
		case 0:
		{
			iomanX_close(0);
			iomanX_close(1);
			register_tty();
			open_tty_handles("tty:");
			break;
		}
		case 1:
		{
			iomanX_close(0);
			iomanX_close(1);
			register_dummytty();
			open_tty_handles("dummytty:");
			break;
		}
		default:
			break;
	}
	ChangeThreadPriority(0, thinfo.currentPriority);
}

static int open_tty_handles(const char *tty_name)
{
	if ( iomanX_open(tty_name, 3) != 0 || iomanX_open(tty_name, 2) != 1 )
		return -1;
	return 0;
}

int iomanX_open(const char *name, int flags, ...)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;
	int mode;
	va_list va;

	va_start(va, flags);
	mode = va_arg(va, int);
	va_end(va);
	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(name, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	f->mode = flags;
	return handle_result(
		f->device->ops->open(f, parsefile_res, flags, mode),
		f,
		HANDLE_RESULT_CLEAR_INFO_ON_ERROR | HANDLE_RESULT_RETURN_FD);
}

int iomanX_lseek(int fd, int offset, int mode)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f )
		return handle_result(-EBADF, f, 0);
	switch ( mode )
	{
		case FIO_SEEK_SET:
		case FIO_SEEK_CUR:
		case FIO_SEEK_END:
			return handle_result(f->device->ops->lseek(f, offset, mode), f, 0);
		default:
			write_str_to_stdout("invalid lseek arg\r\n");
			return handle_result(-EINVAL, f, 0);
	}
}

s64 iomanX_lseek64(int fd, s64 offset, int whence)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f )
		return handle_result(-EBADF, f, 0);
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, 0);
	switch ( whence )
	{
		case FIO_SEEK_SET:
		case FIO_SEEK_CUR:
		case FIO_SEEK_END:
			return handle_result64(f->device->ops->lseek64(f, offset, whence), f, 0);
		default:
			write_str_to_stdout("invalid lseek arg\r\n");
			return handle_result(-EINVAL, f, 0);
	}
}

int iomanX_read(int fd, void *ptr, int size)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f || !(f->mode & FIO_O_RDONLY) )
		return handle_result(-EBADF, f, 0);
	return handle_result(f->device->ops->read(f, ptr, size), f, 0);
}

int iomanX_write(int fd, void *ptr, int size)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f || !(f->mode & FIO_O_WRONLY) )
		return handle_result(-EBADF, f, 0);
	return handle_result(f->device->ops->write(f, ptr, size), f, 0);
}

int iomanX_close(int fd)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f )
		return handle_result(-EBADF, f, 0);
	return handle_result(
		(f->mode & FIO_O_DIROPEN) ? f->device->ops->dclose(f) : f->device->ops->close(f),
		f,
		HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_FD);
}

int iomanX_ioctl(int fd, int cmd, void *param)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f )
		return handle_result(-EBADF, f, 0);
	return handle_result(f->device->ops->ioctl(f, cmd, param), f, 0);
}

int iomanX_ioctl2(int fd, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f )
		return handle_result(-EBADF, f, 0);
	// The filesystem must support these ops.
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, 0);
	return handle_result(f->device->ops->ioctl2(f, cmd, arg, arglen, buf, buflen), f, 0);
}

int iomanX_dopen(const char *path)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(path, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	f->mode = FIO_O_DIROPEN;
	return handle_result(
		f->device->ops->dopen(f, parsefile_res), f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR | HANDLE_RESULT_RETURN_FD);
}

int iomanX_dread(int fd, iox_dirent_t *buf)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f || !(f->mode & FIO_O_DIROPEN) )
		return handle_result(-EBADF, f, 0);
	return handle_result(f->device->ops->dread(f, buf), f, 0);
}

int iomanX_remove(const char *name)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(name, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	return handle_result(
		f->device->ops->remove(f, parsefile_res), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
}

int iomanX_mkdir(const char *path, int mode)
{
	return xx_dir(4, path, mode);
}

int iomanX_rmdir(const char *path)
{
	return xx_dir(5, path, 0);
}

static int xx_stat(int op, const char *name, iox_stat_t *stat, unsigned int statmask)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(name, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	switch ( op )
	{
		case 1:
			return handle_result(
				f->device->ops->chstat(f, parsefile_res, stat, statmask),
				f,
				HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		case 2:
			return handle_result(
				f->device->ops->getstat(f, parsefile_res, stat), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		default:
			// Unofficial: return negative instead of positive if op not found
			return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	}
}

int iomanX_getstat(const char *name, iox_stat_t *stat)
{
	return xx_stat(2, name, stat, 0);
}

int iomanX_chstat(const char *name, iox_stat_t *stat, unsigned int statmask)
{
	return xx_stat(1, name, stat, statmask);
}

int iomanX_format(const char *dev, const char *blockdev, void *arg, int arglen)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(dev, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	return handle_result(
		f->device->ops->format(f, parsefile_res, blockdev, arg, arglen),
		f,
		HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
}

static int xx_rename(int op, const char *oldname, const char *newname)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;
	const char *parsefile_res_new;
	iomanX_iop_device_t *device_new;
	int unit_new;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(oldname, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// Unofficial: initialize variables and check if newname is not NULL
	parsefile_res_new = newname;
	device_new = f->device;
	unit_new = f->unit;
	if ( newname && index(newname, ':') )
		parsefile_res_new = parsefile(newname, &device_new, &unit_new);
	// Make sure the user isn't attempting to link across devices.
	if ( !parsefile_res_new || (device_new != f->device) || (unit_new != f->unit) )
		return handle_result(-EXDEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// The filesystem must support these ops.
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	switch ( op )
	{
		case 7:
			return handle_result(
				f->device->ops->rename(f, parsefile_res, parsefile_res_new),
				f,
				HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		case 8:
			return handle_result(
				f->device->ops->symlink(f, parsefile_res, parsefile_res_new),
				f,
				HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		default:
			// Unofficial: return negative instead of positive if op not found
			return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	}
}

// cppcheck-suppress funcArgNamesDifferent
int iomanX_rename(const char *oldname, const char *newname)
{
	return xx_rename(7, oldname, newname);
}

// cppcheck-suppress funcArgNamesDifferent
int iomanX_symlink(const char *oldname, const char *newname)
{
	return xx_rename(8, oldname, newname);
}

int iomanX_chdir(const char *name)
{
	return xx_dir(0x103, name, 0);
}

/* Because mkdir, rmdir, chdir, and sync have similiar arguments (each starts
	 with a path followed by an optional integer), we use a common routine to
	 handle all of them.  */
static int xx_dir(int op, const char *name, int mode)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(name, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// The filesystem must support these ops.
	if ( (op & 0x100) && ((f->device->type & 0xF0000000) != IOP_DT_FSEXT) )
		return handle_result(-EUNSUP, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	switch ( op )
	{
		case 4:
			return handle_result(
				f->device->ops->mkdir(f, parsefile_res, mode), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		case 5:
			return handle_result(
				f->device->ops->rmdir(f, parsefile_res), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		case 0x103:
			return handle_result(
				f->device->ops->chdir(f, parsefile_res), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		case 0x106:
			return handle_result(
				f->device->ops->sync(f, parsefile_res, mode), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
		default:
			// Unofficial: return negative instead of positive if op not found
			return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	}
}

int iomanX_sync(const char *dev, int flag)
{
	return xx_dir(0x106, dev, flag);
}

int iomanX_mount(const char *fsname, const char *devname, int flag, void *arg, int arglen)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(fsname, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// The filesystem must support these ops.
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	return handle_result(
		f->device->ops->mount(f, parsefile_res, devname, flag, arg, arglen),
		f,
		HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
}

int iomanX_umount(const char *fsname)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(fsname, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// The filesystem must support these ops.
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	return handle_result(
		f->device->ops->umount(f, parsefile_res), f, HANDLE_RESULT_CLEAR_INFO | HANDLE_RESULT_RETURN_ZERO);
}

int iomanX_devctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(name, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// The filesystem must support these ops.
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	return handle_result(
		f->device->ops->devctl(f, parsefile_res, cmd, arg, arglen, buf, buflen), f, HANDLE_RESULT_CLEAR_INFO);
}

int iomanX_readlink(const char *path, char *buf, unsigned int buflen)
{
	iomanX_iop_file_t *f;
	const char *parsefile_res;

	f = new_iob();
	if ( !f )
		return handle_result(-EMFILE, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	parsefile_res = parsefile(path, &(f->device), &(f->unit));
	if ( !parsefile_res )
		return handle_result(-ENODEV, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	// The filesystem must support these ops.
	if ( (f->device->type & 0xF0000000) != IOP_DT_FSEXT )
		return handle_result(-EUNSUP, f, HANDLE_RESULT_CLEAR_INFO_ON_ERROR);
	return handle_result(f->device->ops->readlink(f, parsefile_res, buf, buflen), f, HANDLE_RESULT_CLEAR_INFO);
}

static int _ioabort(const char *str1, const char *str2)
{
	return Kprintf("ioabort exit:%s %s\n", str1, str2);
}

static iomanX_iop_file_t *new_iob(void)
{
	iomanX_iop_file_t *file_table_entry;
	int state;

	CpuSuspendIntr(&state);
	file_table_entry = file_table;
	while ( (file_table_entry < &file_table[sizeof(file_table) / sizeof(file_table[0])]) && file_table_entry->mode )
		file_table_entry += 1;
	if ( file_table_entry >= &file_table[sizeof(file_table) / sizeof(file_table[0])] )
		file_table_entry = NULL;
	// fill in "device" temporarily to mark the fd as allocated.
	if ( file_table_entry )
		file_table_entry->mode = -20;
	CpuResumeIntr(state);
	if ( !file_table_entry )
		_ioabort("out of file descriptors", "[too many open]");
	return file_table_entry;
}

static iomanX_iop_file_t *get_iob(int fd)
{
	if ( ((unsigned int)fd >= (sizeof(file_table) / sizeof(file_table[0]))) || (!file_table[fd].device) )
		return NULL;
	return &file_table[fd];
}

static iomanX_iop_device_t *lookup_dev(const char *name, int show_unkdev_msg)
{
	struct ioman_dev_listentry *entry;
	int state;

	CpuSuspendIntr(&state);
	entry = device_entry_used_list_head;
	while ( entry && strcmp(name, entry->device->name) )
		entry = entry->next;
	if ( !entry && show_unkdev_msg )
	{
		Kprintf("Unknown device '%s'\n", name);
		ShowDrv();
	}
	CpuResumeIntr(state);
	return entry ? entry->device : NULL;
}

static const char *parsefile(const char *path, iomanX_iop_device_t **p_device, int *p_unit)
{
	const char *path_trimmed;
	char *colon_index;
	size_t devname_len;
	iomanX_iop_device_t *device;
	int unit;
	int unit_index;
	char canon[32];

	path_trimmed = path;
	while ( *path_trimmed == ' ' )
		path_trimmed += 1;
	colon_index = index(path_trimmed, ':');
	// Unofficial: On error, return NULL instead of -1
	if ( !colon_index )
	{
		Kprintf("Unknown device '%s'\n", path_trimmed);
		return NULL;
	}
	devname_len = colon_index - path_trimmed;
	// Unofficial: bounds check
	if ( devname_len > (sizeof(canon) - 1) )
		return NULL;
	strncpy(canon, path_trimmed, devname_len);
	canon[devname_len] = 0;
	unit_index = devname_len - 1;
	unit = 0;
	// Search backward for the unit number.
	if ( isnum(canon[unit_index]) )
	{
		while ( isnum(canon[unit_index]) )
			unit_index -= 1;
		unit = strtol(&canon[unit_index], 0, 10);
		canon[unit_index] = 0;
	}
	// Find the actual device.
	device = lookup_dev(canon, 1);
	// Unofficial: On error, return NULL instead of -1
	if ( !device )
		return NULL;
	// Unofficial: set unit and device only after success
	*p_unit = unit;
	*p_device = device;
	// This is the name passed to the device op.
	return colon_index + 1;
}

// Unofficial: unused "io request for unsupported operation" func removed

static int tty_noop(void)
{
	return 0;
}

int iomanX_AddDrv(iomanX_iop_device_t *device)
{
	struct ioman_dev_listentry *entry;
	struct ioman_dev_listentry *old_head;
	int state;

	CpuSuspendIntr(&state);
	if ( adddeldrv_in_process )
	{
		Kprintf("AddDrv()/DelDrv() recursive/mutithread call error !!");
		CpuResumeIntr(state);
		return -1;
	}
	// Unofficial: move list check out of interrupt disabled area
	adddeldrv_in_process = 1;
	CpuResumeIntr(state);
	entry = device_entry_empty_list_head;
	// Unofficial: check if entry exists first
	if ( !entry || lookup_dev(device->name, 0) )
	{
		adddeldrv_in_process = 0;
		return -1;
	}
	entry->device = device;
	device_entry_empty_list_head = entry->next;
	if ( device->ops->init(device) < 0 )
	{
		old_head = device_entry_empty_list_head;
		entry->device = NULL;
		device_entry_empty_list_head = entry;
		entry->next = old_head;
		adddeldrv_in_process = 0;
		return -1;
	}
	old_head = device_entry_used_list_head;
	device_entry_used_list_head = entry;
	showdrvflag = 1;
	entry->next = old_head;
	adddeldrv_in_process = 0;
	return 0;
}

int iomanX_DelDrv(const char *name)
{
	struct ioman_dev_listentry *entry;
	struct ioman_dev_listentry **p_next;
	struct ioman_dev_listentry *old_head;
	int state;

	CpuSuspendIntr(&state);
	if ( adddeldrv_in_process )
	{
		Kprintf("AddDrv()/DelDrv() recursive/mutithread call error !!");
		CpuResumeIntr(state);
		return -1;
	}
	adddeldrv_in_process = 1;
	CpuResumeIntr(state);
	entry = device_entry_used_list_head;
	p_next = &device_entry_used_list_head;
	while ( entry && strcmp(name, entry->device->name) )
	{
		p_next = &entry->next;
		entry = entry->next;
	}
	if ( !entry || entry->device->ops->deinit(entry->device) < 0 )
	{
		adddeldrv_in_process = 0;
		return -1;
	}
	old_head = device_entry_empty_list_head;
	entry->device = NULL;
	device_entry_empty_list_head = entry;
	*p_next = entry->next;
	entry->next = old_head;
	adddeldrv_in_process = 0;
	return 0;
}

unsigned int iomanX_GetDevType(int fd)
{
	iomanX_iop_file_t *f;

	f = get_iob(fd);
	if ( !f )
		return handle_result(-EBADF, f, 0);
	return f->device->type;
}

static void ShowDrv(void)
{
	struct ioman_dev_listentry *i;

	if ( !showdrvflag )
		return;
	Kprintf("Known devices are ");
	for ( i = device_entry_used_list_head; i; i = i->next )
		Kprintf(" %s:(%s) ", i->device->name, i->device->desc);
	Kprintf("\n");
	showdrvflag = 0;
}

static void register_tty(void)
{
	iomanX_DelDrv(dev_tty.name);
	iomanX_AddDrv(&dev_tty);
}

static void register_dummytty(void)
{
	iomanX_DelDrv(dev_dummytty.name);
	iomanX_AddDrv(&dev_dummytty);
}

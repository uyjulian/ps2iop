
#include "irx_imports.h"
#include "sysclib.h"

int setjmp(jmp_buf env) {
	// FIXME: stub
	return 0;
}

void longjmp(jmp_buf env, int val) {
	// FIXME: stub
}

char _toupper(char c) {
	// FIXME: stub
	return 0;
}

char _tolower(char c) {
	// FIXME: stub
	return 0;
}

unsigned char look_ctype_table(char character) {
	// FIXME: stub
	return 0;
}

void *get_ctype_table() {
	// FIXME: stub
	return NULL;
}

void *memchr(const void *s, int c, size_t n) {
	// FIXME: stub
	return NULL;
}

int memcmp(const void *p, const void *q, size_t size) {
	// FIXME: stub
	return 0;
}

void *memcpy(void *dest, const void *src, size_t size) {
	// FIXME: stub
	return NULL;
}

void *memmove(void *dest, const void *src, size_t size) {
	// FIXME: stub
	return NULL;
}

void *memset(void *ptr, int c, size_t size) {
	// FIXME: stub
	return NULL;
}

int bcmp(const void * x, const void * y, size_t z) {
	// FIXME: stub
	return 0;
}

void bcopy(const void * x, void * y, size_t z) {
	// FIXME: stub
}

void bzero(void * x, size_t y) {
	// FIXME: stub
}

int prnt(print_callback_t x, void *context, const char * format, va_list ap) {
	// FIXME: stub
	return 0;
}

int sprintf(char *str, const char *format, ...) {
	// FIXME: stub
	return 0;
}

char *strcat(char *dest, const char *src) {
	// FIXME: stub
	return NULL;
}

char *strchr(const char *s, int c) {
	// FIXME: stub
	return NULL;
}

int strcmp(const char *p, const char *q) {
	// FIXME: stub
	return 0;
}

char *strcpy(char *dest, const char *src) {
	// FIXME: stub
	return NULL;
}

size_t strcspn(const char *s, const char *reject) {
	// FIXME: stub
	return 0;
}

char *index(const char *s, int c) {
	// FIXME: stub
	return NULL;
}

char *rindex(const char *s, int c) {
	// FIXME: stub
	return NULL;
}

size_t strlen(const char *s) {
	// FIXME: stub
	return 0;
}

char *strncat(char *dest, const char *src, size_t size) {
	// FIXME: stub
	return NULL;
}

int strncmp(const char *p, const char *q, size_t size) {
	// FIXME: stub
	return 0;
}

char *strncpy(char *dest, const char *src, size_t size) {
	// FIXME: stub
	return NULL;
}

char *strpbrk(const char *s, const char *accept) {
	// FIXME: stub
	return NULL;
}

char *strrchr(const char *s, int c) {
	// FIXME: stub
	return NULL;
}

size_t strspn(const char *s, const char *accept) {
	// FIXME: stub
	return 0;
}

char *strstr(const char *haystack, const char *needle) {
	// FIXME: stub
	return NULL;
}

char *strtok(char *s, const char *delim) {
	// FIXME: stub
	return NULL;
}

long strtol(const char *s, char **endptr, int base) {
	// FIXME: stub
	return 0;
}

char *atob(char *s, int *i) {
	// FIXME: stub
	return NULL;
}

unsigned long strtoul(const char *s, char **endptr, int base) {
	// FIXME: stub
	return 0;
}

void *wmemcopy(u32 *dest, const u32 *src, size_t size) {
	// FIXME: stub
	return NULL;
}

void *wmemset(u32 *dest, u32 c, size_t size) {
	// FIXME: stub
	return NULL;
}

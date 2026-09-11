#if defined(__linux__) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#if defined(__linux__) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#ifndef V_THREAD_STACK_SIZE
#define V_THREAD_STACK_SIZE 8388608
#endif
#include <float.h>
#include <sys/mman.h>

typedef signed char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char u8;
typedef unsigned char byte;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
static inline i64 __v_pow_i64(i64 base, i64 exponent) { if (exponent < 0) { if (base == 0) return -1; if (base != 1 && base != -1) return 0; return (exponent & 1) != 0 ? base : 1; } i64 value = 1; i64 power = base; for (; exponent > 0; exponent >>= 1) { if ((exponent & 1) != 0) value *= power; power *= power; } return value; }
static inline u64 __v_pow_u64(u64 base, i64 exponent) { if (exponent < 0) { if (base == 0) return (u64)-1; return base == 1 ? 1 : 0; } u64 value = 1; u64 power = base; for (; exponent > 0; exponent >>= 1) { if ((exponent & 1) != 0) value *= power; power *= power; } return value; }
#ifdef _MSC_VER
#ifdef _WIN64
typedef unsigned __int64 size_t;
typedef __int64 ptrdiff_t;
typedef unsigned __int64 uintptr_t;
typedef __int64 intptr_t;
#else
typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef unsigned int uintptr_t;
typedef int intptr_t;
#endif
#else
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTPTR_TYPE__ intptr_t;
#endif
#ifndef __bool_true_false_are_defined
#ifdef _MSC_VER
typedef unsigned char bool;
#else
typedef _Bool bool;
#endif
#define __bool_true_false_are_defined 1
#endif
typedef void* voidptr;
typedef int int_literal;
typedef double float_literal;
struct sync__Channel;
typedef struct sync__Channel* chan;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#define _S(s) ((string){.str=(u8*)("" s), .len=(sizeof(s)-1), .is_lit=1})
#if !defined(VNORETURN)
#if defined(__TINYC__)
#define VNORETURN __attribute__((noreturn))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define VNORETURN _Noreturn
#elif defined(__GNUC__) && __GNUC__ >= 2
#define VNORETURN __attribute__((noreturn))
#endif
#ifndef VNORETURN
#define VNORETURN
#endif
#endif
typedef ptrdiff_t isize;
typedef size_t usize;
typedef char* charptr;
typedef unsigned char* byteptr;
typedef int (*qsort_callback_func)(const void*, const void*);
#ifndef VCALLCONV
#define VCALLCONV(x)
#endif
#if defined(__linux__) && !defined(__ANDROID__)
#include <features.h>
#endif
#ifdef sprintf
#undef sprintf
#endif
#ifdef snprintf
#undef snprintf
#endif
#ifdef vsnprintf
#undef vsnprintf
#endif
#ifdef memcpy
#undef memcpy
#endif
#ifdef memmove
#undef memmove
#endif
#ifdef memset
#undef memset
#endif
// c_headers
typedef int (*qsort_callback_func)(const void*, const void*);
#if defined(_MSC_VER) && !defined(__clang__)
	#define V_CRT_LINKAGE __declspec(dllimport)
	#define V_CRT_CALL VCALLCONV(cdecl)
#else
	#define V_CRT_LINKAGE
	#define V_CRT_CALL
#endif
#if (defined(__MINGW32__) || defined(__MINGW64__)) && defined(__V_GCC__)
	#define V_CRT_STDIO_LINKAGE __attribute__((dllimport))
#else
	#define V_CRT_STDIO_LINKAGE V_CRT_LINKAGE
#endif
#if (defined(_MSC_VER) && !defined(__clang__)) || defined(__cplusplus)
// Under C++ (g++/clang++), let libc declare FILE/stdio/string/stdlib to keep
// noexcept specifiers consistent — the manual extern "C" prototypes below
// would otherwise conflict with system headers under -std=c++NN.
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef va_copy
	#define va_copy(dest, src) ((dest) = (src))
#endif
#ifndef _TRUNCATE
	#define _TRUNCATE ((size_t)-1)
#endif
#elif defined(__NetBSD__)
// NetBSD exposes stdin/stdout/stderr as macros into a single `__sF[3]`
// array whose element size (sizeof(FILE)) depends on the platform and libc
// version, so we cannot forward-declare them. The FreeBSD-style
// `__stdinp/__stdoutp/__stderrp` symbols also do not exist on NetBSD (see
// vlang/v#27190). Defer to the system headers for FILE, the stdio streams,
// and the libc prototypes that would otherwise clash with the
// `__restrict`-qualified declarations in NetBSD libc.
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#elif defined(__TINYC__) && (defined(__FreeBSD__) || defined(__OpenBSD__))
// TinyCC reports a hard redefinition error if system OpenSSL pulls in
// <stdarg.h> after V has provided its own va_start macro. Include it first,
// but keep V manual FILE declarations on these BSD libc variants.
#include <stdarg.h>
#if defined(__FreeBSD__)
typedef struct __sFILE FILE;
extern FILE* __stdinp;
extern FILE* __stdoutp;
extern FILE* __stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
#else
typedef struct __sFILE FILE;
#ifndef _STDFILES_DECLARED
	#define _STDFILES_DECLARED
struct __sFstub { long _stub; };
extern struct __sFstub __stdin[];
extern struct __sFstub __stdout[];
extern struct __sFstub __stderr[];
#endif
#define stdin ((struct __sFILE *)__stdin)
#define stdout ((struct __sFILE *)__stdout)
#define stderr ((struct __sFILE *)__stderr)
#endif
#elif (defined(__MINGW32__) || defined(__MINGW64__)) && defined(__V_GCC__)
// mingw-w64 stdio.h provides fprintf/vfprintf as static inline overrides
// when __USE_MINGW_ANSI_STDIO is enabled, so use the system declarations
// instead of the manual formatted-stdio prototypes below.
#include <stdarg.h>
#include <stdio.h>
#elif defined(__MINGW32__) || defined(__MINGW64__) || (defined(__clang__) && (defined(_WIN32) || defined(_WIN64)))
typedef struct _iobuf FILE;
FILE* __cdecl __acrt_iob_func(unsigned index);
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#elif defined(__TINYC__) && (defined(_WIN32) || defined(_WIN64))
#ifndef _FILE_DEFINED
struct _iobuf {
	char *_ptr;
	int _cnt;
	char *_base;
	int _flag;
	int _file;
	int _charbuf;
	int _bufsiz;
	char *_tmpfname;
};
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif
	#if defined(_WIN64)
FILE* __cdecl __iob_func(void);
	#else
		#ifdef _MSVCRT_
extern FILE _iob[];
			#define __iob_func() (_iob)
		#else
extern FILE (*_imp___iob)[];
			#define __iob_func() (*_imp___iob)
			#define _iob __iob_func()
		#endif
	#endif
#define stdin (&__iob_func()[0])
#define stdout (&__iob_func()[1])
#define stderr (&__iob_func()[2])
#elif defined(__vinix__)
typedef struct __file FILE;
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
struct __thread_data;
struct __threadattr;
// pthread_t handling for vinix builds:
//  - Vinix kernel (freestanding, __STDC_HOSTED__=0): no libc, define
//    pthread_t ourselves so V code that references it compiles.
//  - util-vinix cross-compiled on a libc-providing host (hosted, e.g.
//    glibc on Linux or macOS with -D__vinix__): pull pthread_t from
//    libc to avoid colliding with the libc typedef.
#if defined(__STDC_HOSTED__) && __STDC_HOSTED__ && defined(__has_include) && __has_include(<pthread.h>)
#include <pthread.h>
#else
typedef struct __thread_data *pthread_t;
#endif
typedef __builtin_va_list va_list;
#ifndef va_start
	#define va_start(ap, v) __builtin_va_start(ap, v)
#endif
#ifndef va_arg
	#define va_arg(ap, t) __builtin_va_arg(ap, t)
#endif
#ifndef va_end
	#define va_end(ap) __builtin_va_end(ap)
#endif
#ifndef va_copy
	#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif
#else
	#if defined(__APPLE__) || defined(__FreeBSD__)
typedef struct __sFILE FILE;
extern FILE* __stdinp;
extern FILE* __stdoutp;
extern FILE* __stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
	#elif defined(__DragonFly__)
typedef struct __sFILE FILE;
extern FILE* __stdinp;
extern FILE* __stdoutp;
extern FILE* __stderrp;
#define stdin __stdinp
#define stdout __stdoutp
#define stderr __stderrp
	#elif defined(__OpenBSD__)
typedef struct __sFILE FILE;
#ifndef _STDFILES_DECLARED
	#define _STDFILES_DECLARED
struct __sFstub { long _stub; };
extern struct __sFstub __stdin[];
extern struct __sFstub __stdout[];
extern struct __sFstub __stderr[];
#endif
#define stdin ((struct __sFILE *)__stdin)
#define stdout ((struct __sFILE *)__stdout)
#define stderr ((struct __sFILE *)__stderr)
	#elif defined(__BIONIC__)
struct __sFILE;
typedef struct __sFILE FILE;
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
	#elif defined(__linux__) && !defined(__GLIBC__) && !defined(__GNU_LIBRARY__) && !defined(__BIONIC__) && !defined(__UCLIBC__)
typedef struct _IO_FILE FILE;
// musl exposes the stdio streams as `FILE *const`, so match that to stay
// compatible with later <stdio.h> includes from headers like miniz.h.
extern FILE* const stdin;
extern FILE* const stdout;
extern FILE* const stderr;
	#else
typedef struct _IO_FILE FILE;
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
#if defined(__GLIBC__) || defined(__GNU_LIBRARY__)
// V declares the stdio functions manually here, instead of including <stdio.h>.
// glibc defines L_tmpnam only while <stdio.h> is being processed (it sits behind
// `#ifdef _STDIO_H` in <bits/stdio_lim.h>), and it is the one stdio limit macro that
// <stdio.h> itself uses in a prototype: char *tmpnam(char[L_tmpnam]). So a <stdio.h>
// pulled in later by a module header (sqlite3.h, gc.h, ...) can fail with L_tmpnam
// being undeclared; see vlang/v#28108. Define it here, to the stable glibc value,
// without adding an include. A later identical redefinition by glibc is a no-op.
#ifndef L_tmpnam
#define L_tmpnam 20
#endif
#endif
	#endif
typedef __builtin_va_list va_list;
#ifndef va_start
	#define va_start(ap, v) __builtin_va_start(ap, v)
#endif
#ifndef va_arg
	#define va_arg(ap, t) __builtin_va_arg(ap, t)
#endif
#ifndef va_end
	#define va_end(ap) __builtin_va_end(ap)
#endif
#ifndef va_copy
	#define va_copy(dest, src) __builtin_va_copy(dest, src)
#endif
#endif
#if (!defined(_MSC_VER) || defined(__clang__)) && !defined(__cplusplus) && !defined(__NetBSD__)
// mingw-w64 stdio.h declares these as static __mingw_ovr inline overrides
// when __USE_MINGW_ANSI_STDIO is on. Skip them under gcc+mingw to avoid
// static-after-extern conflicts; clang+mingw needs them because it builds
// with -Werror=implicit-function-declaration and does not hit the conflict.
// NetBSD pulls these prototypes from <stdio.h>/<stdlib.h>/<string.h> via
// the include block above to avoid `__restrict` qualifier conflicts.
#if !((defined(__MINGW32__) || defined(__MINGW64__)) && !defined(__clang__))
V_CRT_LINKAGE int V_CRT_CALL vfprintf(FILE *stream, const char *format, va_list ap);
V_CRT_LINKAGE int V_CRT_CALL vsnprintf(char *str, size_t size, const char *format, va_list ap);
V_CRT_LINKAGE int V_CRT_CALL fprintf(FILE *stream, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL printf(const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL snprintf(char *str, size_t size, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL sprintf(char *str, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL sscanf(const char *str, const char *format, ...);
V_CRT_LINKAGE int V_CRT_CALL scanf(const char *format, ...);
#endif
V_CRT_LINKAGE int V_CRT_CALL puts(const char *str);
V_CRT_LINKAGE void V_CRT_CALL perror(const char *str);
V_CRT_LINKAGE int V_CRT_CALL fputs(const char *str, FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL getchar(void);
V_CRT_LINKAGE int V_CRT_CALL putchar(int ch);
V_CRT_LINKAGE int V_CRT_CALL getc(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL fgetc(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL ungetc(int ch, FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL fflush(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL feof(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL ferror(FILE *stream);
V_CRT_LINKAGE void V_CRT_CALL clearerr(FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL setvbuf(FILE *stream, char *buf, int mode, size_t size);
V_CRT_LINKAGE long V_CRT_CALL ftell(FILE *stream);
V_CRT_LINKAGE void V_CRT_CALL rewind(FILE *stream);
V_CRT_LINKAGE FILE * V_CRT_CALL fopen(const char *filename, const char *mode);
V_CRT_LINKAGE FILE * V_CRT_CALL fdopen(int fd, const char *mode);
V_CRT_LINKAGE FILE * V_CRT_CALL freopen(const char *filename, const char *mode, FILE *stream);
V_CRT_LINKAGE int V_CRT_CALL fileno(FILE *stream);
V_CRT_LINKAGE size_t V_CRT_CALL fread(void *ptr, size_t size, size_t items, FILE *stream);
V_CRT_LINKAGE size_t V_CRT_CALL fwrite(const void *ptr, size_t size, size_t items, FILE *stream);
#if defined(__vinix__)
V_CRT_LINKAGE char * V_CRT_CALL fgets(char *str, size_t size, FILE *stream);
#else
V_CRT_LINKAGE char * V_CRT_CALL fgets(char *str, int size, FILE *stream);
#endif
V_CRT_LINKAGE int V_CRT_CALL fclose(FILE *stream);
#if defined(__vinix__)
V_CRT_LINKAGE FILE * V_CRT_CALL popen(char *command, char *mode);
#else
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL popen(const char *command, const char *mode);
#endif
V_CRT_STDIO_LINKAGE int V_CRT_CALL pclose(FILE *stream);
V_CRT_LINKAGE void * V_CRT_CALL malloc(size_t size);
V_CRT_LINKAGE void * V_CRT_CALL calloc(size_t nitems, size_t size);
V_CRT_LINKAGE void * V_CRT_CALL realloc(void *ptr, size_t size);
V_CRT_LINKAGE void * V_CRT_CALL aligned_alloc(size_t alignment, size_t size);
V_CRT_LINKAGE int V_CRT_CALL posix_memalign(void **memptr, size_t alignment, size_t size);
V_CRT_LINKAGE void V_CRT_CALL free(void *ptr);
V_CRT_LINKAGE int V_CRT_CALL rand(void);
V_CRT_LINKAGE void V_CRT_CALL srand(unsigned int seed);
V_CRT_LINKAGE int V_CRT_CALL atexit(void (*cb)(void));
V_CRT_LINKAGE void V_CRT_CALL exit(int status);
V_CRT_LINKAGE int V_CRT_CALL abs(int n);
V_CRT_LINKAGE int V_CRT_CALL atoi(const char *str);
V_CRT_LINKAGE double V_CRT_CALL atof(const char *str);
V_CRT_LINKAGE char * V_CRT_CALL getenv(const char *name);
V_CRT_LINKAGE int V_CRT_CALL setenv(const char *name, const char *value, int overwrite);
V_CRT_LINKAGE int V_CRT_CALL unsetenv(const char *name);
V_CRT_LINKAGE int V_CRT_CALL system(const char *command);
V_CRT_LINKAGE int V_CRT_CALL remove(const char *path);
V_CRT_LINKAGE int V_CRT_CALL rename(const char *old_path, const char *new_path);
V_CRT_LINKAGE char * V_CRT_CALL realpath(const char *path, char *resolved_path);
V_CRT_LINKAGE int V_CRT_CALL mkstemp(char *stemplate);
V_CRT_LINKAGE void V_CRT_CALL qsort(void *base, size_t items, size_t item_size, qsort_callback_func cb);
#if defined(__vinix__)
V_CRT_LINKAGE int V_CRT_CALL strcmp(char *left, char *right);
V_CRT_LINKAGE int V_CRT_CALL strncmp(char *left, char *right, size_t n);
#else
V_CRT_LINKAGE int V_CRT_CALL strcmp(const char *left, const char *right);
V_CRT_LINKAGE int V_CRT_CALL strncmp(const char *left, const char *right, size_t n);
#endif
#if !defined(_WIN32) && !defined(_WIN64) && !defined(__BIONIC__)
V_CRT_LINKAGE char * V_CRT_CALL strdup(const char *str);
#endif
#if !defined(_WIN32) && !defined(_WIN64)
V_CRT_LINKAGE int V_CRT_CALL strcasecmp(const char *left, const char *right);
V_CRT_LINKAGE int V_CRT_CALL strncasecmp(const char *left, const char *right, size_t n);
#endif
#if defined(__vinix__)
V_CRT_LINKAGE size_t V_CRT_CALL strlen(char *str);
#else
V_CRT_LINKAGE size_t V_CRT_CALL strlen(const char *str);
#endif
V_CRT_LINKAGE char * V_CRT_CALL strerror(int errnum);
V_CRT_LINKAGE void * V_CRT_CALL memcpy(void *dest, const void *src, size_t n);
V_CRT_LINKAGE void * V_CRT_CALL memmove(void *dest, const void *src, size_t n);
V_CRT_LINKAGE void * V_CRT_CALL memset(void *dest, int ch, size_t n);
V_CRT_LINKAGE int V_CRT_CALL memcmp(const void *left, const void *right, size_t n);
// memchr/strchr/strrchr/strstr are the C23 type-generic string functions, and
// glibc 2.42+ implements them as function-like macros over _Generic, so that a
// const-qualified argument yields a const-qualified return type. If any include
// above already pulled in <string.h> (mbedtls/net_sockets.h, netdb.h, dirent.h,
// ... all do, and gcc 15 defaults to -std=gnu23), the name is already a macro
// here, and a declaration like
// `void *memchr(const void *str, int c, size_t n);` expands into the middle of
// a _Generic expression, which fails to parse:
// `error: expected identifier or ( before _Generic`.
// A defined macro also means <string.h> has already declared the real function,
// so skipping the declaration below loses nothing in that case. The reverse
// order stays fine as-is: a <string.h> pulled in later by a module header
// defines the macro after these declarations, which C permits.
#ifndef memchr
V_CRT_LINKAGE void * V_CRT_CALL memchr(const void *str, int c, size_t n);
#endif
#ifndef strchr
V_CRT_LINKAGE char * V_CRT_CALL strchr(const char *str, int c);
#endif
#ifndef strrchr
V_CRT_LINKAGE char * V_CRT_CALL strrchr(const char *str, int c);
#endif
#ifndef strstr
V_CRT_LINKAGE char * V_CRT_CALL strstr(const char *haystack, const char *needle);
#endif
V_CRT_LINKAGE int V_CRT_CALL fseek(FILE *stream, long offset, int whence);
V_CRT_LINKAGE isize V_CRT_CALL getline(char **lineptr, size_t *n, FILE *stream);
#if defined(_WIN32) || defined(_WIN64)
V_CRT_STDIO_LINKAGE int V_CRT_CALL _fseeki64(FILE *stream, i64 offset, int whence);
V_CRT_LINKAGE int V_CRT_CALL fgetpos(FILE *stream, i64 *pos);
V_CRT_STDIO_LINKAGE int V_CRT_CALL _fileno(FILE *stream);
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL _wfopen(const unsigned short *filename, const unsigned short *mode);
V_CRT_STDIO_LINKAGE int V_CRT_CALL freopen_s(FILE **new_stream, const char *filename, const char *mode, FILE *stream);
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL _wfreopen(const unsigned short *filename, const unsigned short *mode, FILE *stream);
V_CRT_STDIO_LINKAGE FILE * V_CRT_CALL _wpopen(const unsigned short *command, const unsigned short *mode);
V_CRT_STDIO_LINKAGE int V_CRT_CALL _pclose(FILE *stream);
V_CRT_STDIO_LINKAGE int V_CRT_CALL _wremove(const unsigned short *path);
V_CRT_LINKAGE void * V_CRT_CALL _aligned_malloc(size_t size, size_t alignment);
V_CRT_LINKAGE void * V_CRT_CALL _aligned_realloc(void *memory, size_t size, size_t alignment);
V_CRT_LINKAGE void V_CRT_CALL _aligned_free(void *memory);
V_CRT_LINKAGE unsigned short * V_CRT_CALL _wgetenv(const unsigned short *varname);
V_CRT_LINKAGE int V_CRT_CALL _wputenv(const unsigned short *envstring);
#endif
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef _TRUNCATE
	#define _TRUNCATE ((size_t)-1)
#endif
V_CRT_LINKAGE int V_CRT_CALL _vscprintf(const char *format, va_list ap);
V_CRT_LINKAGE int V_CRT_CALL _vsnprintf_s(char *buffer, size_t size, size_t count, const char *format, va_list ap);
#endif
#endif
#ifndef _IOFBF
	#define _IOFBF 0
#endif
#ifndef _IOLBF
	#define _IOLBF 1
#endif
#ifndef _IONBF
	#define _IONBF 2
#endif
#ifndef EOF
	#define EOF (-1)
#endif
#ifndef SEEK_SET
	#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
	#define SEEK_CUR 1
#endif
#ifndef SEEK_END
	#define SEEK_END 2
#endif
#ifndef RAND_MAX
enum {
	#if defined(_MSC_VER)
		RAND_MAX = 0x7fff
	#else
		RAND_MAX = 2147483647
	#endif
};
#endif
#undef V_CRT_STDIO_LINKAGE
#undef V_CRT_LINKAGE
#undef V_CRT_CALL
void abort(void);
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <wchar.h>
#if defined(_WIN32) && defined(__TINYC__)
#include "/home/yorche3/.local/share/vlang/thirdparty/stdatomic/win/atomic.h"
#else
#if defined(__OBJC__) && defined(__GNUC__) && !defined(__clang__)
#define _Atomic volatile
#endif
#include <stdatomic.h>
#if defined(__OBJC__) && defined(__GNUC__) && !defined(__clang__)
#undef _Atomic
#endif
#endif
#if defined(__linux__) || defined(__ANDROID__)
#include <sys/syscall.h>
#endif
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#include <sys/event.h>
#endif
#ifdef _WIN32
#include <io.h>
#include <process.h>
#include <windows.h>
#else
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <utime.h>
#endif
#ifdef __APPLE__
#include <mach/mach_time.h>
#include <mach-o/dyld.h>
#endif
#if defined(__linux__) || defined(__ANDROID__)
#include <sys/epoll.h>
#endif
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#include <sys/event.h>
#endif
#if defined(__has_include) && !defined(__TINYC__)
	#if __has_include(<execinfo.h>) && !defined(_WIN32)
		#define __V_HAVE_EXECINFO_H 1
		#include <execinfo.h>
	#endif
#elif (defined(__linux__) && (defined(__GLIBC__) || defined(__GNU_LIBRARY__))) || defined(__APPLE__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)
	#define __V_HAVE_EXECINFO_H 1
	#include <execinfo.h>
#endif
#if !defined(__V_HAVE_EXECINFO_H) && !defined(_WIN32)
int backtrace(void** __array, int __size);
char** backtrace_symbols(void* const* __array, int __size);
void backtrace_symbols_fd(void* const* __array, int __size, int __fd);
#endif

#ifdef _WIN32
typedef struct { HANDLE handle; void* context; } __v_thread;
static bool __v_thread_equal(__v_thread a, __v_thread b) { return a.handle == b.handle; }
typedef void* (*__v_thread_start_fn)(void*);
typedef struct { __v_thread_start_fn start; void* arg; void* result; } __v_windows_thread_context;
static const size_t __v_thread_stack_size = V_THREAD_STACK_SIZE;
static void* __v_thread_alloc(size_t size) { void* p = malloc(size); if (!p) { fprintf(stderr, "V thread allocation failed\n"); abort(); } return p; }
static DWORD WINAPI __v_windows_thread_start(void* raw_context) { __v_windows_thread_context* context = (__v_windows_thread_context*)raw_context; context->result = context->start(context->arg); return 0; }
static __v_thread __v_thread_spawn(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_thread result;
	__v_windows_thread_context* context = (__v_windows_thread_context*)__v_thread_alloc(sizeof(__v_windows_thread_context));
	context->start = start; context->arg = arg; context->result = NULL;
	result.context = context;
	result.handle = CreateThread(NULL, __v_thread_stack_size, __v_windows_thread_start, context, 0, NULL);
	if (!result.handle) { DWORD error = GetLastError(); free(context); if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %lu\n", (unsigned long)error); abort(); }
	return result;
}
static void* __v_thread_join(__v_thread thread) {
	DWORD rc = WaitForSingleObject(thread.handle, INFINITE);
	if (rc != WAIT_OBJECT_0) { fprintf(stderr, "V thread join failed: %lu\n", (unsigned long)rc); abort(); }
	void* result = ((__v_windows_thread_context*)thread.context)->result;
	if (!CloseHandle(thread.handle)) { DWORD error = GetLastError(); free(thread.context); fprintf(stderr, "V thread handle cleanup failed: %lu\n", (unsigned long)error); abort(); }
	free(thread.context);
	return result;
}
#else
typedef struct { pthread_t handle; } __v_thread;
static bool __v_thread_equal(__v_thread a, __v_thread b) { return pthread_equal(a.handle, b.handle) != 0; }
typedef void* (*__v_thread_start_fn)(void*);
static const size_t __v_thread_stack_size = V_THREAD_STACK_SIZE;
static void* __v_thread_alloc(size_t size) { void* p = malloc(size); if (!p) { fprintf(stderr, "V thread allocation failed\n"); abort(); } return p; }
static __v_thread __v_thread_spawn(__v_thread_start_fn start, void* arg, void (*cleanup)(void*)) {
	__v_thread result;
	pthread_attr_t attr;
	int rc = pthread_attr_init(&attr);
	if (rc != 0) { if (cleanup) cleanup(arg); fprintf(stderr, "V thread attribute initialization failed: %d\n", rc); abort(); }
	rc = pthread_attr_setstacksize(&attr, __v_thread_stack_size);
	if (rc != 0) { pthread_attr_destroy(&attr); if (cleanup) cleanup(arg); fprintf(stderr, "V thread stack size setup failed: %d\n", rc); abort(); }
	rc = pthread_create(&result.handle, &attr, (void*)start, arg);
	int attr_rc = pthread_attr_destroy(&attr);
	if (rc != 0) { if (cleanup) cleanup(arg); fprintf(stderr, "V thread creation failed: %d\n", rc); abort(); }
	if (attr_rc != 0) { fprintf(stderr, "V thread attribute cleanup failed: %d\n", attr_rc); abort(); }
	return result;
}
static void* __v_thread_join(__v_thread thread) { void* result = NULL; int rc = pthread_join(thread.handle, &result); if (rc != 0) { fprintf(stderr, "V thread join failed: %d\n", rc); abort(); } return result; }
#endif
#ifndef __V_architecture
#define __V_architecture 0
#endif
#if defined(__x86_64__) || defined(_M_AMD64)
#define __V_amd64 1
#undef __V_architecture
#define __V_architecture 1
#endif
#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
#define __V_arm64 1
#undef __V_architecture
#define __V_architecture 2
#endif
#if defined(__arm__) || defined(_M_ARM)
#define __V_arm32 1
#undef __V_architecture
#define __V_architecture 3
#endif
#if defined(__riscv) && __riscv_xlen == 64
#define __V_rv64 1
#undef __V_architecture
#define __V_architecture 4
#endif
#if defined(__riscv) && __riscv_xlen == 32
#define __V_rv32 1
#undef __V_architecture
#define __V_architecture 5
#endif
#if defined(__i386__) || defined(_M_IX86)
#define __V_x86 1
#undef __V_architecture
#define __V_architecture 6
#endif
#if defined(__s390x__)
#define __V_s390x 1
#undef __V_architecture
#define __V_architecture 7
#endif
#if defined(__powerpc64__) && defined(__LITTLE_ENDIAN__)
#define __V_ppc64le 1
#undef __V_architecture
#define __V_architecture 8
#endif
#if defined(__loongarch64)
#define __V_loongarch64 1
#undef __V_architecture
#define __V_architecture 9
#endif
#if defined(__sparc__)
#define __V_sparc64 1
#undef __V_architecture
#define __V_architecture 10
#endif
#if defined(__powerpc64__) && defined(__BIG_ENDIAN__)
#define __V_ppc64 1
#undef __V_architecture
#define __V_architecture 11
#endif
#if (defined(__powerpc__) || defined(__powerpc) || defined(__POWERPC__) || defined(__ppc__) || defined(__ppc) || defined(__PPC__)) && !defined(__powerpc64__) && !defined(__ppc64__) && !defined(__PPC64__)
#define __V_ppc 1
#undef __V_architecture
#define __V_architecture 12
#endif

#define elem_size element_size
#define c_name types__c_name
#define builtin__string_clone string__clone
#define builtin__tos2 tos2
/* V3CACHE_NATIVE_DIRECTIVES_BEGIN */
#include "/home/yorche3/.local/share/vlang/vlib/builtin/track_heap_checks.h"

/* V3CACHE_NATIVE_DIRECTIVES_END */
typedef enum {
	ArrayFlags__noslices = 1,
	ArrayFlags__noshrink = 2,
	ArrayFlags__nogrow = 4,
	ArrayFlags__nofree = 8,
	ArrayFlags__managed = 16,
	ArrayFlags__noscan_data = 32,
	ArrayFlags__is_slice = 64,
} ArrayFlags;

typedef enum {
	ChanState__success = 0,
	ChanState__not_ready = 1,
	ChanState__closed = 2,
} ChanState;

typedef enum {
	GraphemeBreakProperty__other = 0,
	GraphemeBreakProperty__cr = 1,
	GraphemeBreakProperty__lf = 2,
	GraphemeBreakProperty__control = 3,
	GraphemeBreakProperty__extend = 4,
	GraphemeBreakProperty__regional_indicator = 5,
	GraphemeBreakProperty__prepend = 6,
	GraphemeBreakProperty__spacing_mark = 7,
	GraphemeBreakProperty__l = 8,
	GraphemeBreakProperty__v = 9,
	GraphemeBreakProperty__t = 10,
	GraphemeBreakProperty__lv = 11,
	GraphemeBreakProperty__lvt = 12,
	GraphemeBreakProperty__zwj = 13,
} GraphemeBreakProperty;

typedef enum {
	AttributeKind__plain = 0,
	AttributeKind__string = 1,
	AttributeKind__number = 2,
	AttributeKind__bool = 3,
	AttributeKind__comptime_define = 4,
} AttributeKind;

typedef enum {
	MapMode__to_upper = 0,
	MapMode__to_lower = 1,
	MapMode__to_title = 2,
} MapMode;

typedef enum {
	TrimMode__trim_left = 0,
	TrimMode__trim_right = 1,
	TrimMode__trim_both = 2,
} TrimMode;

typedef enum {
	StrIntpType__si_no_str = 0,
	StrIntpType__si_c = 1,
	StrIntpType__si_u8 = 2,
	StrIntpType__si_i8 = 3,
	StrIntpType__si_u16 = 4,
	StrIntpType__si_i16 = 5,
	StrIntpType__si_u32 = 6,
	StrIntpType__si_i32 = 7,
	StrIntpType__si_u64 = 8,
	StrIntpType__si_i64 = 9,
	StrIntpType__si_e32 = 10,
	StrIntpType__si_e64 = 11,
	StrIntpType__si_f32 = 12,
	StrIntpType__si_f64 = 13,
	StrIntpType__si_g32 = 14,
	StrIntpType__si_g64 = 15,
	StrIntpType__si_s = 16,
	StrIntpType__si_p = 17,
	StrIntpType__si_r = 18,
	StrIntpType__si_vp = 19,
} StrIntpType;

typedef enum {
	strings__IndentState__normal = 0,
	strings__IndentState__in_string = 1,
} strings__IndentState;

typedef enum {
	strconv__Align_text__right = 0,
	strconv__Align_text__left = 1,
	strconv__Align_text__center = 2,
} strconv__Align_text;

typedef enum {
	strconv__ParserState__ok = 0,
	strconv__ParserState__pzero = 1,
	strconv__ParserState__mzero = 2,
	strconv__ParserState__pinf = 3,
	strconv__ParserState__minf = 4,
	strconv__ParserState__invalid_number = 5,
	strconv__ParserState__extra_char = 6,
} strconv__ParserState;

typedef enum {
	strconv__Char_parse_state__start = 0,
	strconv__Char_parse_state__norm_char = 1,
	strconv__Char_parse_state__field_char = 2,
	strconv__Char_parse_state__pad_ch = 3,
	strconv__Char_parse_state__len_set_start = 4,
	strconv__Char_parse_state__len_set_in = 5,
	strconv__Char_parse_state__check_type = 6,
	strconv__Char_parse_state__check_float = 7,
	strconv__Char_parse_state__check_float_in = 8,
	strconv__Char_parse_state__reset_params = 9,
} strconv__Char_parse_state;

typedef struct ArrayDataHeader ArrayDataHeader;
typedef struct AutostrAddrStackState AutostrAddrStackState;
typedef struct DenseArray DenseArray;
typedef struct EnumData EnumData;
typedef struct Error Error;
typedef struct FieldData FieldData;
typedef struct FunctionData FunctionData;
typedef struct FunctionParam FunctionParam;
typedef struct GCHeapUsage GCHeapUsage;
typedef struct GraphemeState GraphemeState;
typedef struct InputRuneIterator InputRuneIterator;
typedef struct MessageError MessageError;
typedef struct None__ None__;
typedef struct Option Option;
typedef struct OwnershipIErrorPayload OwnershipIErrorPayload;
typedef struct OwnershipV3InterfacePayload OwnershipV3InterfacePayload;
typedef struct PreallocStats PreallocStats;
typedef struct RepIndex RepIndex;
typedef struct RunesIterator RunesIterator;
typedef struct SliceIndex SliceIndex;
typedef struct SortedMap SortedMap;
typedef struct StrIntpCgenData StrIntpCgenData;
typedef struct StrIntpData StrIntpData;
typedef union StrIntpMem StrIntpMem;
typedef struct ToWideConfig ToWideConfig;
typedef struct VAssertMetaInfo VAssertMetaInfo;
typedef struct VAttribute VAttribute;
typedef struct VCastTypeIndexName VCastTypeIndexName;
typedef struct VContext VContext;
typedef struct VMemoryBlock VMemoryBlock;
typedef struct VPreallocBlockCache VPreallocBlockCache;
typedef struct VPreallocRange VPreallocRange;
typedef struct VPreallocScope VPreallocScope;
typedef struct VariantData VariantData;
typedef struct WrapConfig WrapConfig;
typedef struct _option _option;
typedef struct _result _result;
typedef struct array array;
typedef struct map map;
typedef struct mapnode mapnode;
typedef struct strconv__AtoF64Param strconv__AtoF64Param;
typedef struct strconv__BF_param strconv__BF_param;
typedef struct strconv__Dec32 strconv__Dec32;
typedef struct strconv__Dec64 strconv__Dec64;
typedef union strconv__Float32u strconv__Float32u;
typedef union strconv__Float64u strconv__Float64u;
typedef struct strconv__PrepNumber strconv__PrepNumber;
typedef union strconv__Uf32 strconv__Uf32;
typedef union strconv__Uf64 strconv__Uf64;
typedef struct strconv__Uint128 strconv__Uint128;
typedef struct string string;
typedef struct strings__IndentParam strings__IndentParam;
typedef struct IError IError;
typedef struct hash__Hash hash__Hash;
typedef struct hash__Hash32er hash__Hash32er;
typedef struct hash__Hash64er hash__Hash64er;
typedef array Array;

typedef struct multi_return_u32_u32 multi_return_u32_u32;
typedef struct multi_return_string_string multi_return_string_string;
typedef struct multi_return_i64_i64 multi_return_i64_i64;
typedef struct multi_return_u32_i64 multi_return_u32_i64;
typedef struct multi_return_size_t_size_t_size_t_size_t_size_t multi_return_size_t_size_t_size_t_size_t_size_t;
typedef struct multi_return_u64_i64 multi_return_u64_i64;
typedef struct multi_return_u32_u32_u32 multi_return_u32_u32_u32;
typedef struct multi_return_int_strconv__PrepNumber multi_return_int_strconv__PrepNumber;
typedef struct multi_return_strconv__Dec32_bool multi_return_strconv__Dec32_bool;
typedef struct multi_return_strconv__Dec64_bool multi_return_strconv__Dec64_bool;
typedef struct multi_return_u64_u64 multi_return_u64_u64;
typedef struct multi_return_double_i64 multi_return_double_i64;

typedef double Array_fixed_double_36[36];
typedef i32 Array_fixed_i32_1264[1264];
typedef i64 Array_fixed_i64_64[64];
typedef u32 Array_fixed_u32_10[10];
typedef u64 Array_fixed_u64_18[18];
typedef u64 Array_fixed_u64_20[20];
typedef u64 Array_fixed_u64_309[309];
typedef u64 Array_fixed_u64_31[31];
typedef u64 Array_fixed_u64_324[324];
typedef u64 Array_fixed_u64_47[47];
typedef u64 Array_fixed_u64_584[584];
typedef u64 Array_fixed_u64_652[652];
typedef u8 Array_fixed_u8_256[256];
typedef u8 Array_fixed_u8_26[26];
typedef u8 Array_fixed_u8_32[32];
typedef u8 Array_fixed_u8_512[512];
typedef u8 Array_fixed_u8_64[64];
typedef void* Array_fixed_voidptr_11[11];
typedef void* Array_fixed_voidptr_512[512];
typedef void* Array_fixed_voidptr_64[64];

typedef bool (*_fn_ptr_c95f092653bee64)(void*, void*);
typedef i64 (*_fn_ptr_ed95774d3a4e97ab)(void*, void*);
typedef u64 (*_fn_ptr_1e8d64a3d95a0da1)(void*);
typedef void (*_fn_ptr_a73f2ae88698453e)(char*, size_t);
typedef void (*_fn_ptr_39790037d38ea68)(void);
typedef void (*_fn_ptr_5373f7edc7b60e26)(void*);
typedef void (*_fn_ptr_1a3da2026b1489ea)(void*, void*);

typedef struct ArrayDataHeader ArrayDataHeader;
typedef struct AutostrAddrStackState AutostrAddrStackState;
typedef struct DenseArray DenseArray;
typedef struct EnumData EnumData;
typedef struct Error Error;
typedef struct FieldData FieldData;
typedef struct FunctionData FunctionData;
typedef struct FunctionParam FunctionParam;
typedef struct GCHeapUsage GCHeapUsage;
typedef struct GraphemeState GraphemeState;
typedef struct InputRuneIterator InputRuneIterator;
typedef struct MessageError MessageError;
typedef struct None__ None__;
typedef struct Option Option;
typedef struct OwnershipIErrorPayload OwnershipIErrorPayload;
typedef struct OwnershipV3InterfacePayload OwnershipV3InterfacePayload;
typedef struct PreallocStats PreallocStats;
typedef struct RepIndex RepIndex;
typedef struct RunesIterator RunesIterator;
typedef struct SliceIndex SliceIndex;
typedef struct SortedMap SortedMap;
typedef struct StrIntpCgenData StrIntpCgenData;
typedef struct StrIntpData StrIntpData;
typedef union StrIntpMem StrIntpMem;
typedef struct ToWideConfig ToWideConfig;
typedef struct VAssertMetaInfo VAssertMetaInfo;
typedef struct VAttribute VAttribute;
typedef struct VCastTypeIndexName VCastTypeIndexName;
typedef struct VContext VContext;
typedef struct VMemoryBlock VMemoryBlock;
typedef struct VPreallocBlockCache VPreallocBlockCache;
typedef struct VPreallocRange VPreallocRange;
typedef struct VPreallocScope VPreallocScope;
typedef struct VariantData VariantData;
typedef struct WrapConfig WrapConfig;
typedef struct _option _option;
typedef struct _result _result;
typedef struct array array;
typedef struct map map;
typedef struct mapnode mapnode;
typedef struct strconv__AtoF64Param strconv__AtoF64Param;
typedef struct strconv__BF_param strconv__BF_param;
typedef struct strconv__Dec32 strconv__Dec32;
typedef struct strconv__Dec64 strconv__Dec64;
typedef union strconv__Float32u strconv__Float32u;
typedef union strconv__Float64u strconv__Float64u;
typedef struct strconv__PrepNumber strconv__PrepNumber;
typedef union strconv__Uf32 strconv__Uf32;
typedef union strconv__Uf64 strconv__Uf64;
typedef struct strconv__Uint128 strconv__Uint128;
typedef struct string string;
typedef struct strings__IndentParam strings__IndentParam;
typedef struct IError IError;
typedef struct hash__Hash hash__Hash;
typedef struct hash__Hash32er hash__Hash32er;
typedef struct hash__Hash64er hash__Hash64er;
typedef array Array;
struct string {
	u8* str;
	i64 len;
	i64 is_lit;
};

struct IError {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
	string message;
	int code;
};

typedef struct Optional { bool ok; IError err; int value; } Optional;

struct array {
	void* data;
	i64 offset;
	i64 len;
	i64 cap;
	int flags;
	i64 element_size;
};

struct hash__Hash {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

struct hash__Hash32er {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

struct hash__Hash64er {
	void* _object;
	union {
		void* _interface_meta;
		struct {
			u32 _typ : 31;
			u32 _object_is_boxed : 1;
		};
	};
};

#pragma pack(push, 1)
struct ArrayDataHeader {
	bool has_slices;
};
#pragma pack(pop)

typedef string Array_fixed_string_11[11];
typedef ptrdiff_t Array_fixed_ptrdiff_t_512[512];
struct AutostrAddrStackState {
	void* addrs[64];
	i64 types[64];
	i64 len;
	i64 overflow_depth;
};

struct DenseArray {
	i64 key_bytes;
	i64 value_bytes;
	i64 cap;
	i64 len;
	u32 deletes;
	u8* all_deleted;
	u8* keys;
	u8* values;
};

struct EnumData {
	string name;
	i64 value;
	Array attrs;
};

struct Error {
	u8 _dummy;
};

struct FieldData {
	string name;
	i64 typ;
	i64 unaliased_typ;
	Array attrs;
	bool is_pub;
	bool is_mut;
	bool is_embed;
	bool is_shared;
	bool is_atomic;
	bool is_option;
	bool is_array;
	bool is_map;
	bool is_chan;
	bool is_enum;
	bool is_struct;
	bool is_alias;
	u8 indirections;
};

struct FunctionData {
	string name;
	string location;
	Array attrs;
	Array attributes;
	Array args;
	i64 return_type;
	i64 typ;
};

struct FunctionParam {
	i64 typ;
	string name;
};

struct GCHeapUsage {
	size_t heap_size;
	size_t free_bytes;
	size_t total_bytes;
	size_t unmapped_bytes;
	size_t bytes_since_gc;
};

struct GraphemeState {
	int prev_prop;
	i64 ri_count;
	u8 extended_pictographic_state;
};

struct InputRuneIterator {
	u8 _dummy;
};

struct MessageError {
	string msg;
	i64 code;
};

struct None__ {
	Error Error;
};

struct Option {
	u8 state;
	IError err;
};

struct OwnershipIErrorPayload {
	void* payload;
};

struct OwnershipV3InterfacePayload {
	void* payload;
	i64 typ;
	bool is_boxed;
};

struct PreallocStats {
	bool enabled;
	u64 allocation_count;
	u64 allocated_bytes;
};

struct RepIndex {
	i64 idx;
	i64 val_idx;
};

struct RunesIterator {
	string s;
	i64 i;
};

struct SliceIndex {
	bool is_range;
	i64 value;
	i64 low;
	i64 high;
	bool has_low;
	bool has_high;
};

struct SortedMap {
	i64 value_bytes;
	mapnode* root;
	i64 len;
};

struct StrIntpCgenData {
	string str;
	string fmt;
	string d;
};

union StrIntpMem {
	u32 d_c;
	u8 d_u8;
	i8 d_i8;
	u16 d_u16;
	i16 d_i16;
	u32 d_u32;
	i32 d_i32;
	u64 d_u64;
	i64 d_i64;
	float d_f32;
	double d_f64;
	string d_s;
	string d_r;
	void* d_p;
	void* d_vp;
};

struct ToWideConfig {
	bool from_ansi;
};

struct VAssertMetaInfo {
	string fpath;
	i64 line_nr;
	string fn_name;
	string src;
	string op;
	string llabel;
	string rlabel;
	string lvalue;
	string rvalue;
	string message;
	bool has_msg;
};

struct VAttribute {
	string name;
	bool has_arg;
	string arg;
	int kind;
};

struct VCastTypeIndexName {
	i64 tindex;
	string tname;
};

struct VContext {
	i64 allocator;
};

struct VMemoryBlock {
	u8* current;
	u8* stop;
	u8* start;
	VMemoryBlock* previous;
	VMemoryBlock* next;
	VPreallocScope* scope;
	VPreallocBlockCache* recycle_cache;
	ptrdiff_t min_block_size;
	bool is_scope;
	bool mmap_allocated;
	i64 id;
	i64 mallocs;
};

struct VPreallocBlockCache {
	i64 count;
	ptrdiff_t bytes;
	void* starts[512];
	ptrdiff_t sizes[512];
};

struct VPreallocRange {
	size_t start;
	size_t stop;
};

struct VPreallocScope {
	VMemoryBlock* previous;
	VMemoryBlock* first;
	size_t min_address;
	size_t max_address;
	VPreallocRange* ranges;
	i64 ranges_len;
	i64 ranges_cap;
	i32 refs;
	i32 free_requested;
	i32 abandoned;
	i32 finalized;
};

struct VariantData {
	i64 typ;
};

struct WrapConfig {
	i64 width;
	string end;
};

struct _option {
	u8 state;
	IError err;
};

struct _result {
	bool is_error;
	IError err;
};

struct map {
	i64 key_bytes;
	i64 value_bytes;
	u32 even_index;
	u8 cached_hashbits;
	u8 shift;
	DenseArray key_values;
	u32* metas;
	u32 extra_metas;
	bool has_string_keys;
	_fn_ptr_1e8d64a3d95a0da1 hash_fn;
	_fn_ptr_c95f092653bee64 key_eq_fn;
	_fn_ptr_1a3da2026b1489ea clone_fn;
	_fn_ptr_5373f7edc7b60e26 free_fn;
	i64 len;
};

struct mapnode {
	void** children;
	i64 len;
	string keys[11];
	void* values[11];
};

struct strconv__AtoF64Param {
	bool allow_extra_chars;
};

struct strconv__BF_param {
	u8 pad_ch;
	i64 len0;
	i64 len1;
	bool positive;
	bool sign_flag;
	int align;
	bool rm_tail_zero;
};

struct strconv__Dec32 {
	u32 m;
	i64 e;
};

struct strconv__Dec64 {
	u64 m;
	i64 e;
};

union strconv__Float32u {
	float f;
	u32 u;
};

union strconv__Float64u {
	double f;
	u64 u;
};

struct strconv__PrepNumber {
	bool negative;
	i64 exponent;
	u64 mantissa;
};

union strconv__Uf32 {
	float f;
	u32 u;
};

union strconv__Uf64 {
	double f;
	u64 u;
};

struct strconv__Uint128 {
	u64 lo;
	u64 hi;
};

struct strings__IndentParam {
	u32 block_start;
	u32 block_end;
	u32 indent_char;
	i64 indent_count;
	i64 starting_level;
};

struct StrIntpData {
	string str;
	u32 fmt;
	StrIntpMem d;
	i64 dyn_width;
	i64 dyn_precision;
	u8 dyn_flags;
};

struct multi_return_u32_u32 {
	u32 arg0;
	u32 arg1;
};
struct multi_return_string_string {
	string arg0;
	string arg1;
};
struct multi_return_i64_i64 {
	i64 arg0;
	i64 arg1;
};
struct multi_return_u32_i64 {
	u32 arg0;
	i64 arg1;
};
struct multi_return_size_t_size_t_size_t_size_t_size_t {
	size_t arg0;
	size_t arg1;
	size_t arg2;
	size_t arg3;
	size_t arg4;
};
struct multi_return_u64_i64 {
	u64 arg0;
	i64 arg1;
};
struct multi_return_u32_u32_u32 {
	u32 arg0;
	u32 arg1;
	u32 arg2;
};
struct multi_return_int_strconv__PrepNumber {
	int arg0;
	strconv__PrepNumber arg1;
};
struct multi_return_strconv__Dec32_bool {
	strconv__Dec32 arg0;
	bool arg1;
};
struct multi_return_strconv__Dec64_bool {
	strconv__Dec64 arg0;
	bool arg1;
};
struct multi_return_u64_u64 {
	u64 arg0;
	u64 arg1;
};
struct multi_return_double_i64 {
	double arg0;
	i64 arg1;
};

typedef struct Optional_double { bool ok; IError err; double value; } Optional_double;
typedef struct Optional_i16 { bool ok; IError err; i16 value; } Optional_i16;
typedef struct Optional_i32 { bool ok; IError err; i32 value; } Optional_i32;
typedef struct Optional_i64 { bool ok; IError err; i64 value; } Optional_i64;
typedef struct Optional_i8 { bool ok; IError err; i8 value; } Optional_i8;
typedef struct Optional_multi_return_i64_i64 { bool ok; IError err; multi_return_i64_i64 value; } Optional_multi_return_i64_i64;
typedef struct Optional_multi_return_string_string { bool ok; IError err; multi_return_string_string value; } Optional_multi_return_string_string;
typedef struct Optional_string { bool ok; IError err; string value; } Optional_string;
typedef struct Optional_u16 { bool ok; IError err; u16 value; } Optional_u16;
typedef struct Optional_u32 { bool ok; IError err; u32 value; } Optional_u32;
typedef struct Optional_u64 { bool ok; IError err; u64 value; } Optional_u64;
typedef struct Optional_u8 { bool ok; IError err; u8 value; } Optional_u8;

/* V3CACHE_SOURCE_DIRECTIVES_BEGIN */
/* V3CACHE_SOURCE_DIRECTIVES_END */
#ifndef __linux__
#define pthread_rwlockattr_setkind_np(attr, kind) 0
#endif
#define array_new(elem_size, len, cap) __new_array((len), (cap), (elem_size))
#define array_push array__push
void array__push_many(array* a, void* val, i64 size);
#define array_push_many_ptr(a, val, size) array__push_many((a), (void*)(val), (size))
#define array_get array__get
#define array_set(a, i, ...) array__set(&(a), (i), __VA_ARGS__)
array array__clone(array* a);
#define array_slice array__slice
#define array_delete array__delete
#define array_ensure_cap array__ensure_cap
#define map__get_or_set map__get_and_set
#ifndef V_COMMIT_HASH
#define V_COMMIT_HASH ""
#endif
#ifndef memory_order_relaxed
#define memory_order_relaxed 0
#define memory_order_acquire 2
#define memory_order_release 3
#define memory_order_acq_rel 4
#define memory_order_seq_cst 5
#endif
#if defined(_WIN32) && defined(__TINYC__)
/* V atomic.h supplies atomic_thread_fence on Windows TCC. */
#elif defined(__TINYC__) && (defined(__i386__) || defined(__arm__) || defined(__aarch64__) || defined(__riscv))
extern void _V_atomic_thread_fence(int order);
#define atomic_thread_fence(order) _V_atomic_thread_fence(order)
#define __atomic_thread_fence(order) _V_atomic_thread_fence(order)
#else
#define atomic_thread_fence(order) __atomic_thread_fence(order)
#endif
__attribute__((weak)) void vheap_alloc(void* p, u64 n) { (void)p; (void)n; }
__attribute__((weak)) void vheap_free(void* p) { (void)p; }
static inline int v3_sum_ptr_type_idx(const void* p) { return p == NULL ? 0 : *(const int*)p; }
static inline int v_prealloc_atomic_add_i32(int *ptr, int delta) { return __atomic_add_fetch(ptr, delta, 5); }
static inline int v_prealloc_atomic_load_i32(int *ptr) { return __atomic_add_fetch(ptr, 0, 5); }
static inline long long v_prealloc_atomic_add_i64(long long *ptr, long long delta) { return __atomic_add_fetch(ptr, delta, 5); }
static inline long long v_prealloc_atomic_load_i64(long long *ptr) { return __atomic_add_fetch(ptr, 0, 5); }
#ifdef __TINYC__
static inline int v_prealloc_atomic_store_i32(int *ptr, int val) { return (int)__atomic_exchange_4((u32*)ptr, (u32)val, 5); }
static inline int v_prealloc_atomic_cas_i32(int *ptr, int expected, int desired) { u32 e = (u32)expected; return __atomic_compare_exchange_4((u32*)ptr, &e, (u32)desired, 5, 5); }
#else
static inline int v_prealloc_atomic_store_i32(int *ptr, int val) { return __atomic_exchange_n(ptr, val, 5); }
static inline int v_prealloc_atomic_cas_i32(int *ptr, int expected, int desired) { return __atomic_compare_exchange_n(ptr, &expected, desired, 0, 5, 5); }
#endif
static inline byte atomic_fetch_add_byte(void* ptr, byte delta) { return __atomic_fetch_add((byte*)ptr, delta, 5); }
static inline u16 atomic_fetch_add_u16(void* ptr, u16 delta) { return __atomic_fetch_add((u16*)ptr, delta, 5); }
static inline u32 atomic_fetch_add_u32(void* ptr, u32 delta) { return __atomic_fetch_add((u32*)ptr, delta, 5); }
static inline u64 atomic_fetch_add_u64(void* ptr, u64 delta) { return __atomic_fetch_add((u64*)ptr, delta, 5); }
static inline void* atomic_fetch_add_ptr(void* ptr, void* delta) { return (void*)(uintptr_t)__atomic_fetch_add((uintptr_t*)ptr, (uintptr_t)delta, 5); }
static inline byte atomic_fetch_sub_byte(void* ptr, byte delta) { return __atomic_fetch_sub((byte*)ptr, delta, 5); }
static inline u16 atomic_fetch_sub_u16(void* ptr, u16 delta) { return __atomic_fetch_sub((u16*)ptr, delta, 5); }
static inline u32 atomic_fetch_sub_u32(void* ptr, u32 delta) { return __atomic_fetch_sub((u32*)ptr, delta, 5); }
static inline u64 atomic_fetch_sub_u64(void* ptr, u64 delta) { return __atomic_fetch_sub((u64*)ptr, delta, 5); }
static inline void* atomic_fetch_sub_ptr(void* ptr, void* delta) { return (void*)(uintptr_t)__atomic_fetch_sub((uintptr_t*)ptr, (uintptr_t)delta, 5); }
static inline byte atomic_load_byte(void* ptr) { return __atomic_fetch_add((byte*)ptr, 0, 5); }
static inline u16 atomic_load_u16(void* ptr) { return __atomic_fetch_add((u16*)ptr, 0, 5); }
static inline u32 atomic_load_u32(void* ptr) { return __atomic_fetch_add((u32*)ptr, 0, 5); }
static inline u64 atomic_load_u64(void* ptr) { return __atomic_fetch_add((u64*)ptr, 0, 5); }
#ifdef __TINYC__
extern u64 __atomic_exchange_8(u64* ptr, u64 val, int order);
static inline void* atomic_load_ptr(void* ptr) { return (void*)(uintptr_t)__atomic_fetch_add((uintptr_t*)ptr, (uintptr_t)0, 5); }
static inline byte atomic_exchange_byte(void* ptr, byte val) { return __atomic_exchange_1((byte*)ptr, val, 5); }
static inline u16 atomic_exchange_u16(void* ptr, u16 val) { return __atomic_exchange_2((u16*)ptr, val, 5); }
static inline u32 atomic_exchange_u32(void* ptr, u32 val) { return __atomic_exchange_4((u32*)ptr, val, 5); }
static inline u64 atomic_exchange_u64(void* ptr, u64 val) { return __atomic_exchange_8((u64*)ptr, val, 5); }
static inline void atomic_store_byte(void* ptr, byte val) { __atomic_store_1((byte*)ptr, val, 5); }
static inline void atomic_store_u16(void* ptr, u16 val) { __atomic_store_2((u16*)ptr, val, 5); }
static inline void atomic_store_u32(void* ptr, u32 val) { __atomic_store_4((u32*)ptr, val, 5); }
static inline void atomic_store_u64(void* ptr, u64 val) { __atomic_store_8((u64*)ptr, val, 5); }
#if UINTPTR_MAX == 0xFFFFFFFF
static inline void* atomic_exchange_ptr(void* ptr, void* val) { return (void*)(size_t)__atomic_exchange_4((u32*)ptr, (u32)(size_t)val, 5); }
static inline void atomic_store_ptr(void* ptr, void* val) { __atomic_store_4((u32*)ptr, (u32)(size_t)val, 5); }
#else
static inline void* atomic_exchange_ptr(void* ptr, void* val) { return (void*)(size_t)__atomic_exchange_8((u64*)ptr, (u64)(size_t)val, 5); }
static inline void atomic_store_ptr(void* ptr, void* val) { __atomic_store_8((u64*)ptr, (u64)(size_t)val, 5); }
#endif
static inline bool atomic_compare_exchange_strong_byte(void* ptr, byte* expected, byte desired) { return __atomic_compare_exchange_1((byte*)ptr, expected, desired, 5, 5); }
static inline bool atomic_compare_exchange_strong_u16(void* ptr, u16* expected, u16 desired) { return __atomic_compare_exchange_2((u16*)ptr, expected, desired, 5, 5); }
static inline bool atomic_compare_exchange_strong_u32(void* ptr, u32* expected, u32 desired) { return __atomic_compare_exchange_4((u32*)ptr, expected, desired, 5, 5); }
static inline bool atomic_compare_exchange_strong_u64(void* ptr, u64* expected, u64 desired) { return __atomic_compare_exchange_8((u64*)ptr, expected, desired, 5, 5); }
#if UINTPTR_MAX == 0xFFFFFFFF
static inline bool atomic_compare_exchange_strong_ptr(void* ptr, void* expected, ptrdiff_t desired) { return __atomic_compare_exchange_4((u32*)ptr, (u32*)expected, (u32)desired, 5, 5); }
#else
static inline bool atomic_compare_exchange_strong_ptr(void* ptr, void* expected, ptrdiff_t desired) { return __atomic_compare_exchange_8((u64*)ptr, (u64*)expected, (u64)desired, 5, 5); }
#endif
static inline bool atomic_compare_exchange_weak_byte(void* ptr, byte* expected, byte desired) { return __atomic_compare_exchange_1((byte*)ptr, expected, desired, 5, 5); }
static inline bool atomic_compare_exchange_weak_u16(void* ptr, u16* expected, u16 desired) { return __atomic_compare_exchange_2((u16*)ptr, expected, desired, 5, 5); }
static inline bool atomic_compare_exchange_weak_u32(void* ptr, u32* expected, u32 desired) { return __atomic_compare_exchange_4((u32*)ptr, expected, desired, 5, 5); }
static inline bool atomic_compare_exchange_weak_u64(void* ptr, u64* expected, u64 desired) { return __atomic_compare_exchange_8((u64*)ptr, expected, desired, 5, 5); }
#else
static inline void* atomic_load_ptr(void* ptr) { return __atomic_load_n((void**)ptr, 5); }
static inline byte atomic_exchange_byte(void* ptr, byte val) { return __atomic_exchange_n((byte*)ptr, val, 5); }
static inline u16 atomic_exchange_u16(void* ptr, u16 val) { return __atomic_exchange_n((u16*)ptr, val, 5); }
static inline u32 atomic_exchange_u32(void* ptr, u32 val) { return __atomic_exchange_n((u32*)ptr, val, 5); }
static inline u64 atomic_exchange_u64(void* ptr, u64 val) { return __atomic_exchange_n((u64*)ptr, val, 5); }
static inline void* atomic_exchange_ptr(void* ptr, void* val) { return __atomic_exchange_n((void**)ptr, val, 5); }
static inline void atomic_store_byte(void* ptr, byte val) { __atomic_store_n((byte*)ptr, val, 5); }
static inline void atomic_store_u16(void* ptr, u16 val) { __atomic_store_n((u16*)ptr, val, 5); }
static inline void atomic_store_u32(void* ptr, u32 val) { __atomic_store_n((u32*)ptr, val, 5); }
static inline void atomic_store_u64(void* ptr, u64 val) { __atomic_store_n((u64*)ptr, val, 5); }
static inline void atomic_store_ptr(void* ptr, void* val) { __atomic_store_n((void**)ptr, val, 5); }
static inline bool atomic_compare_exchange_strong_byte(void* ptr, byte* expected, byte desired) { return __atomic_compare_exchange_n((byte*)ptr, expected, desired, 0, 5, 5); }
static inline bool atomic_compare_exchange_strong_u16(void* ptr, u16* expected, u16 desired) { return __atomic_compare_exchange_n((u16*)ptr, expected, desired, 0, 5, 5); }
static inline bool atomic_compare_exchange_strong_u32(void* ptr, u32* expected, u32 desired) { return __atomic_compare_exchange_n((u32*)ptr, expected, desired, 0, 5, 5); }
static inline bool atomic_compare_exchange_strong_u64(void* ptr, u64* expected, u64 desired) { return __atomic_compare_exchange_n((u64*)ptr, expected, desired, 0, 5, 5); }
static inline bool atomic_compare_exchange_strong_ptr(void* ptr, void* expected, ptrdiff_t desired) { return __atomic_compare_exchange_n((void**)ptr, (void**)expected, (void*)desired, 0, 5, 5); }
static inline bool atomic_compare_exchange_weak_byte(void* ptr, byte* expected, byte desired) { return __atomic_compare_exchange_n((byte*)ptr, expected, desired, 1, 5, 5); }
static inline bool atomic_compare_exchange_weak_u16(void* ptr, u16* expected, u16 desired) { return __atomic_compare_exchange_n((u16*)ptr, expected, desired, 1, 5, 5); }
static inline bool atomic_compare_exchange_weak_u32(void* ptr, u32* expected, u32 desired) { return __atomic_compare_exchange_n((u32*)ptr, expected, desired, 1, 5, 5); }
static inline bool atomic_compare_exchange_weak_u64(void* ptr, u64* expected, u64 desired) { return __atomic_compare_exchange_n((u64*)ptr, expected, desired, 1, 5, 5); }
#endif
static inline bool atomic_compare_exchange_weak_ptr(void* ptr, void* expected, ptrdiff_t desired) { return atomic_compare_exchange_strong_ptr(ptr, expected, desired); }
#ifdef __TINYC__
static inline void cpu_relax(void) { }
#else
static inline void cpu_relax(void) { __asm__ __volatile__("" ::: "memory"); }
#endif
static inline double math__abs(double a) { return a < 0 ? -a : a; }
static inline double math__min(double a, double b) { return a < b ? a : b; }
static const u64 _wyp[4] = {0x2d358dccaa6c78a5ull, 0x8bb84b93962eacc9ull, 0x4b33a62ed433d4a3ull, 0x4d5a2da51de1aa47ull};
static inline u64 _wymix(u64 a, u64 b) { u64 ha = a >> 32, hb = b >> 32, la = (u32)a, lb = (u32)b, hi, lo; u64 rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb, t = rl + (rm0 << 32), c = t < rl; lo = t + (rm1 << 32); c += lo < t; hi = rh + (rm0 >> 32) + (rm1 >> 32) + c; return lo ^ hi; }
static inline u64 wyhash64(u64 a, u64 b) { a ^= _wyp[0]; b ^= _wyp[1]; a *= 0xa0761d6478bd642full; b *= 0xe7037ed1a0b428dbull; return (a ^ (a >> 32)) ^ (b ^ (b >> 32)); }
#define V_WY_LOAD8(p) ((u64)(p)[0] | ((u64)(p)[1] << 8) | ((u64)(p)[2] << 16) | ((u64)(p)[3] << 24) | ((u64)(p)[4] << 32) | ((u64)(p)[5] << 40) | ((u64)(p)[6] << 48) | ((u64)(p)[7] << 56))
static inline u64 wyhash(const void* key, size_t len, u64 seed, const u64* secret) {
	const unsigned char* p = (const unsigned char*)key;
	size_t n = len;
	u64 h = seed ^ secret[0] ^ ((u64)len * 0x9e3779b97f4a7c15ull);
	while (n >= 8) { h = (h ^ V_WY_LOAD8(p)) * 0xa0761d6478bd642full; h ^= h >> 29; p += 8; n -= 8; }
	if (n > 0) {
		u64 v = 0;
		switch (n) {
			case 7: v |= (u64)p[6] << 48;
			case 6: v |= (u64)p[5] << 40;
			case 5: v |= (u64)p[4] << 32;
			case 4: v |= (u64)p[3] << 24;
			case 3: v |= (u64)p[2] << 16;
			case 2: v |= (u64)p[1] << 8;
			default: v |= (u64)p[0];
		}
		h = (h ^ v) * 0xe7037ed1a0b428dbull; h ^= h >> 29;
	}
	h *= 0x8ebc6af09c88c6e3ull; h ^= h >> 32; h *= 0x589965cc75374cc3ull; h ^= h >> 29;
	return h;
}
#define v_signal_with_handler_cast(sig, handler) signal((sig), ((void (*)(int))(handler)))
string string__clone(string a);
void string__free(string* s);
string string__plus(string s, string a);
string int__str(i64 n);
string i64__str(i64 n);
string u64__str(u64 nn);
string f64__str(double x);
string rune__str(u32 c);
u8* malloc_noscan(ptrdiff_t n);
void* memdup(void* src, ptrdiff_t sz);
static inline Array* v3_heap_array(Array value) { return (Array*)memdup(&value, sizeof(Array)); }
static int v3_array_sort_int_cmp(const void* a, const void* b) { i64 av = *(const i64*)a; i64 bv = *(const i64*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_int(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(i64), v3_array_sort_int_cmp); }
static int v3_array_sort_i8_cmp(const void* a, const void* b) { signed char av = *(const signed char*)a; signed char bv = *(const signed char*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_i8(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(signed char), v3_array_sort_i8_cmp); }
static int v3_array_sort_i16_cmp(const void* a, const void* b) { short av = *(const short*)a; short bv = *(const short*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_i16(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(short), v3_array_sort_i16_cmp); }
static int v3_array_sort_i64_cmp(const void* a, const void* b) { long long av = *(const long long*)a; long long bv = *(const long long*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_i64(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(long long), v3_array_sort_i64_cmp); }
static int v3_array_sort_u8_cmp(const void* a, const void* b) { unsigned char av = *(const unsigned char*)a; unsigned char bv = *(const unsigned char*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_u8(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(unsigned char), v3_array_sort_u8_cmp); }
static int v3_array_sort_u16_cmp(const void* a, const void* b) { unsigned short av = *(const unsigned short*)a; unsigned short bv = *(const unsigned short*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_u16(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(unsigned short), v3_array_sort_u16_cmp); }
static int v3_array_sort_u32_cmp(const void* a, const void* b) { unsigned av = *(const unsigned*)a; unsigned bv = *(const unsigned*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_u32(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(unsigned), v3_array_sort_u32_cmp); }
static int v3_array_sort_u64_cmp(const void* a, const void* b) { unsigned long long av = *(const unsigned long long*)a; unsigned long long bv = *(const unsigned long long*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_u64(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(unsigned long long), v3_array_sort_u64_cmp); }
static int v3_array_sort_isize_cmp(const void* a, const void* b) { ptrdiff_t av = *(const ptrdiff_t*)a; ptrdiff_t bv = *(const ptrdiff_t*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_isize(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(ptrdiff_t), v3_array_sort_isize_cmp); }
static int v3_array_sort_usize_cmp(const void* a, const void* b) { size_t av = *(const size_t*)a; size_t bv = *(const size_t*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_usize(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(size_t), v3_array_sort_usize_cmp); }
static int v3_array_sort_f32_cmp(const void* a, const void* b) { float av = *(const float*)a; float bv = *(const float*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_f32(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(float), v3_array_sort_f32_cmp); }
static int v3_array_sort_f64_cmp(const void* a, const void* b) { double av = *(const double*)a; double bv = *(const double*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_f64(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(double), v3_array_sort_f64_cmp); }
static int v3_array_sort_rune_cmp(const void* a, const void* b) { unsigned av = *(const unsigned*)a; unsigned bv = *(const unsigned*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_rune(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(unsigned), v3_array_sort_rune_cmp); }
static int v3_array_sort_char_cmp(const void* a, const void* b) { char av = *(const char*)a; char bv = *(const char*)b; return (av > bv) - (av < bv); }
static inline void v3_array_sort_char(Array* a) { if (a != NULL && a->len > 1) qsort(a->data, (size_t)a->len, sizeof(char), v3_array_sort_char_cmp); }
#ifdef _WIN32
void* _aligned_malloc(size_t size, size_t alignment);
void _aligned_free(void* memblock);
#else
int posix_memalign(void** memptr, size_t alignment, size_t size);
#endif
static inline void* v3_aligned_memdup(void* src, ptrdiff_t sz, size_t alignment) { void* p = NULL; if (alignment < sizeof(void*)) alignment = sizeof(void*);
#ifdef _WIN32
p = _aligned_malloc((size_t)sz, alignment);
#else
if (posix_memalign(&p, alignment, (size_t)sz) != 0) p = NULL;
#endif
if (p != NULL) memcpy(p, src, (size_t)sz); return p; }
static inline void v3_aligned_free(void* p) {
#ifdef _WIN32
_aligned_free(p);
#else
free(p);
#endif
}
static inline string v3_c_lit(const char* s, int len) { return (string){.str = (u8*)s, .len = len, .is_lit = 1}; }
static inline int v3_utf8_next_cp(const u8* s, int len, int* i) { u8 c = s[*i]; if (c < 0x80) { (*i)++; return c; } int n = (c & 0xE0) == 0xC0 ? 2 : ((c & 0xF0) == 0xE0 ? 3 : ((c & 0xF8) == 0xF0 ? 4 : 1)); if (*i + n > len) { (*i)++; return c; } int cp = c & (n == 2 ? 0x1F : (n == 3 ? 0x0F : (n == 4 ? 0x07 : 0x7F))); for (int j = 1; j < n; ++j) cp = (cp << 6) | (s[*i + j] & 0x3F); *i += n; return cp; }
static inline int v3_codepoint_is_combining(int cp) { return (cp >= 0x0300 && cp <= 0x036F) || (cp >= 0x1AB0 && cp <= 0x1AFF) || (cp >= 0x1DC0 && cp <= 0x1DFF) || (cp >= 0x20D0 && cp <= 0x20FF) || (cp >= 0xFE00 && cp <= 0xFE0F) || (cp >= 0xFE20 && cp <= 0xFE2F) || (cp >= 0x1F3FB && cp <= 0x1F3FF) || cp == 0x0E31 || (cp >= 0x0E34 && cp <= 0x0E3A) || (cp >= 0x0E47 && cp <= 0x0E4E); }
static inline int v3_codepoint_is_wide(int cp) { return (cp >= 0x1100 && cp <= 0x115F) || (cp >= 0x2329 && cp <= 0x232A) || (cp >= 0x2E80 && cp <= 0xA4CF) || (cp >= 0xAC00 && cp <= 0xD7A3) || (cp >= 0xF900 && cp <= 0xFAFF) || (cp >= 0xFE10 && cp <= 0xFE19) || (cp >= 0xFE30 && cp <= 0xFE6F) || (cp >= 0xFF00 && cp <= 0xFF60) || (cp >= 0xFFE0 && cp <= 0xFFE6) || (cp >= 0x1F000 && cp <= 0x1FAFF); }
static inline int v3_string_display_width(string s) { int width = 0; int join = 0; for (int i = 0; i < s.len;) { int cp = v3_utf8_next_cp(s.str, s.len, &i); if (cp == 0x200D) { join = 1; continue; } if (v3_codepoint_is_combining(cp)) continue; if (join) { join = 0; continue; } width += v3_codepoint_is_wide(cp) ? 2 : 1; } return width; }
static inline string v3_string_pad(string s, int width, int left) { if (width < 0) { left = 1; width = -width; } int visible = v3_string_display_width(s); if (visible >= width) return s; int pad = width - visible; int out_len = s.len + pad; u8* out = malloc_noscan((ptrdiff_t)out_len + 1); if (left) { memcpy(out, s.str, (size_t)s.len); memset(out + s.len, ' ', (size_t)pad); } else { memset(out, ' ', (size_t)pad); memcpy(out + pad, s.str, (size_t)s.len); } out[out_len] = 0; return (string){.str = out, .len = out_len, .is_lit = 0}; }
static inline string v3_string_upper_ascii(string s) { u8* out = malloc_noscan((ptrdiff_t)s.len + 1); for (int i = 0; i < s.len; ++i) { u8 c = s.str[i]; out[i] = c >= 'a' && c <= 'z' ? (u8)(c - ('a' - 'A')) : c; } out[s.len] = 0; return (string){.str = out, .len = s.len, .is_lit = 0}; }
static inline string v3_char_string(int c) { return rune__str((u32)c); }
static inline string v3_indent_multiline(string s) { int lines = 0; for (int i = 0; i < s.len; ++i) if (s.str[i] == '\n') ++lines; if (lines == 0) return s; int out_len = s.len + lines * 4; u8* out = malloc_noscan((ptrdiff_t)out_len + 1); int p = 0; for (int i = 0; i < s.len; ++i) { u8 c = s.str[i]; out[p++] = c; if (c == '\n') { memset(out + p, ' ', 4); p += 4; } } out[p] = 0; return (string){.str = out, .len = out_len, .is_lit = 0}; }
static inline double v3_f64_fixed_value(double x, int precision) { if (precision == 0) return x < 0.0 ? ceil(x - 0.5) : floor(x + 0.5); if (precision == 6) { double scale = 1000000.0; double ax = fabs(x) * scale; double base = floor(ax); double frac = ax - base; if (frac == 0.5) { double rounded = floor(ax + 0.5) / scale; return x < 0.0 ? -rounded : rounded; } } return x; }
static inline string v3_f64_fixed(double x, int precision) { if (precision >= 16) { char base[128]; int b = snprintf(base, sizeof(base), "%.16g", x); if (b >= 0 && b < (int)sizeof(base)) { int dot = -1; int has_exp = 0; for (int i = 0; i < b; ++i) { if (base[i] == '.') dot = i; if (base[i] == 'e' || base[i] == 'E') has_exp = 1; } if (!has_exp) { int frac = dot >= 0 ? b - dot - 1 : 0; if (frac <= precision) { int n = b + (dot < 0 ? 1 : 0) + (precision - frac); u8* out = malloc_noscan(n + 1); memcpy(out, base, b); int pos = b; if (dot < 0) out[pos++] = '.'; while (frac++ < precision) out[pos++] = '0'; out[pos] = 0; return (string){.str = out, .len = n, .is_lit = 0}; } } } } double y = v3_f64_fixed_value(x, precision); char tmp[128]; int n = snprintf(tmp, sizeof(tmp), "%.*f", precision, y); if (n < 0) return v3_c_lit("", 0); if (n < (int)sizeof(tmp)) { u8* out = malloc_noscan(n + 1); memcpy(out, tmp, n + 1); return (string){.str = out, .len = n, .is_lit = 0}; } u8* out = malloc_noscan(n + 1); snprintf((char*)out, (size_t)n + 1, "%.*f", precision, y); return (string){.str = out, .len = n, .is_lit = 0}; }
static inline string v3_f64_exp(double x, int precision, int upper) { char tmp[128]; int n = upper ? snprintf(tmp, sizeof(tmp), "%.*E", precision, x) : snprintf(tmp, sizeof(tmp), "%.*e", precision, x); if (n < 0) return v3_c_lit("", 0); if (n < (int)sizeof(tmp)) { u8* out = malloc_noscan(n + 1); memcpy(out, tmp, n + 1); return (string){.str = out, .len = n, .is_lit = 0}; } u8* out = malloc_noscan(n + 1); if (upper) snprintf((char*)out, (size_t)n + 1, "%.*E", precision, x); else snprintf((char*)out, (size_t)n + 1, "%.*e", precision, x); return (string){.str = out, .len = n, .is_lit = 0}; }
static inline string v3_f64_general(double x, int precision, int upper) { char tmp[128]; int n = upper ? snprintf(tmp, sizeof(tmp), "%.*G", precision, x) : snprintf(tmp, sizeof(tmp), "%.*g", precision, x); if (n < 0) return v3_c_lit("", 0); if (n < (int)sizeof(tmp)) { u8* out = malloc_noscan(n + 1); memcpy(out, tmp, n + 1); return (string){.str = out, .len = n, .is_lit = 0}; } u8* out = malloc_noscan(n + 1); if (upper) snprintf((char*)out, (size_t)n + 1, "%.*G", precision, x); else snprintf((char*)out, (size_t)n + 1, "%.*g", precision, x); return (string){.str = out, .len = n, .is_lit = 0}; }
static inline string v3_string_zpad(string s, int width) { if (s.len >= width) return s; int sign = s.len > 0 && s.str[0] == '-'; int pad = width - s.len; u8* out = malloc_noscan((ptrdiff_t)width + 1); int pos = 0; if (sign) out[pos++] = '-'; memset(out + pos, '0', (size_t)pad); pos += pad; memcpy(out + pos, s.str + sign, (size_t)(s.len - sign)); out[width] = 0; return (string){.str = out, .len = width, .is_lit = 0}; }
static inline string v3_int_zpad(i64 n, int width) { return v3_string_zpad(int__str(n), width); }
static inline string v3_i64_zpad(i64 n, int width) { return v3_string_zpad(i64__str(n), width); }
static inline string v3_u64_zpad(u64 n, int width) { return v3_string_zpad(u64__str(n), width); }
static inline string v3_string_rpad_zero(string s, int width) { if (s.len >= width) return s; u8* out = malloc_noscan((ptrdiff_t)width + 1); memcpy(out, s.str, (size_t)s.len); memset(out + s.len, '0', (size_t)(width - s.len)); out[width] = 0; return (string){.str = out, .len = width, .is_lit = 0}; }
static inline void v3_json_write_u16(u8* out, int* pos, u32 value, const char* hex) { out[(*pos)++] = 92; out[(*pos)++] = 117; out[(*pos)++] = (u8)hex[(value >> 12) & 15]; out[(*pos)++] = (u8)hex[(value >> 8) & 15]; out[(*pos)++] = (u8)hex[(value >> 4) & 15]; out[(*pos)++] = (u8)hex[value & 15]; }
static inline string v3_json_encode_string(string s) {
	const char* lower = "0123456789abcdef"; const char* upper = "0123456789ABCDEF";
	u8* out = malloc_noscan((ptrdiff_t)s.len * 6 + 14); int p = 0; out[p++] = 34;
	for (int i = 0; i < s.len;) {
		u8 c = s.str[i]; if (c < 128) { i++; if (c == 34) { out[p++]=92; out[p++]=34; } else if (c == 92) { out[p++]=92; out[p++]=92; } else if (c == 8) { out[p++]=92; out[p++]=98; } else if (c == 12) { out[p++]=92; out[p++]=102; } else if (c == 10) { out[p++]=92; out[p++]=110; } else if (c == 13) { out[p++]=92; out[p++]=114; } else if (c == 9) { out[p++]=92; out[p++]=116; } else if (c < 32) { v3_json_write_u16(out, &p, c, lower); } else { out[p++]=c; } continue; }
		u32 cp = 0xfffd; int width = 1; if (c >= 0xc2 && c <= 0xdf && i + 1 < s.len && (s.str[i+1] & 0xc0) == 0x80) { cp = ((u32)(c & 31) << 6) | (u32)(s.str[i+1] & 63); width = 2; } else if (c >= 0xe0 && c <= 0xef && i + 2 < s.len && (s.str[i+1] & 0xc0) == 0x80 && (s.str[i+2] & 0xc0) == 0x80) { u32 candidate = ((u32)(c & 15) << 12) | ((u32)(s.str[i+1] & 63) << 6) | (u32)(s.str[i+2] & 63); if (candidate >= 0x800 && !(candidate >= 0xd800 && candidate <= 0xdfff)) { cp = candidate; width = 3; } } else if (c >= 0xf0 && c <= 0xf4 && i + 3 < s.len && (s.str[i+1] & 0xc0) == 0x80 && (s.str[i+2] & 0xc0) == 0x80 && (s.str[i+3] & 0xc0) == 0x80) { u32 candidate = ((u32)(c & 7) << 18) | ((u32)(s.str[i+1] & 63) << 12) | ((u32)(s.str[i+2] & 63) << 6) | (u32)(s.str[i+3] & 63); if (candidate >= 0x10000 && candidate <= 0x10ffff) { cp = candidate; width = 4; } } i += width;
		if (cp <= 0xffff) { v3_json_write_u16(out, &p, cp, lower); } else { u32 adjusted = cp - 0x10000; v3_json_write_u16(out, &p, 0xd800 + ((adjusted >> 10) & 0x3ff), upper); v3_json_write_u16(out, &p, 0xdc00 + (adjusted & 0x3ff), lower); }
	}
	out[p++] = 34; out[p] = 0; return (string){.str = out, .len = p, .is_lit = 0};
}
static inline i64 v3_map_signed(void* p, int bytes) { if (bytes == 1) return *(signed char*)p; if (bytes == 2) return *(short*)p; if (bytes == 8) return *(long long*)p; return *(int*)p; }
static inline u64 v3_map_unsigned(void* p, int bytes) { if (bytes == 1) return *(unsigned char*)p; if (bytes == 2) return *(unsigned short*)p; if (bytes == 8) return *(unsigned long long*)p; return *(unsigned int*)p; }
static inline string v3_f32_array_str(float* vals, int n) { string out = v3_c_lit("[", 1); for (int i = 0; i < n; ++i) { if (i > 0) out = string__plus(out, v3_c_lit(", ", 2)); out = string__plus(out, f64__str((double)vals[i])); } return string__plus(out, v3_c_lit("]", 1)); }
static inline string v3_f64_array_str(double* vals, int n) { string out = v3_c_lit("[", 1); for (int i = 0; i < n; ++i) { if (i > 0) out = string__plus(out, v3_c_lit(", ", 2)); out = string__plus(out, f64__str(vals[i])); } return string__plus(out, v3_c_lit("]", 1)); }
static inline string v3_map_str_piece(void* p, int kind, int bytes, int fixed_len) {
	if (kind == 1) { return string__plus(string__plus(v3_c_lit("'", 1), *(string*)p), v3_c_lit("'", 1)); }
	if (kind == 2) { return v3_i64_zpad(v3_map_signed(p, bytes), 0); }
	if (kind == 3) { return u64__str(v3_map_unsigned(p, bytes)); }
	if (kind == 4) { u32 r = bytes == 1 ? (u32)(*(u8*)p) : *(u32*)p; return string__plus(string__plus(v3_c_lit("`", 1), rune__str(r)), v3_c_lit("`", 1)); }
	if (kind == 5) { if (bytes == (int)sizeof(float)) return f64__str((double)*(float*)p); return f64__str(*(double*)p); }
	if (kind == 6) { if (fixed_len == 0 && bytes == (int)sizeof(Array)) { Array a = *(Array*)p; if (a.element_size == (int)sizeof(float)) return v3_f32_array_str((float*)a.data, a.len); if (a.element_size == (int)sizeof(double)) return v3_f64_array_str((double*)a.data, a.len); } if (fixed_len > 0 && bytes == fixed_len * (int)sizeof(float)) return v3_f32_array_str((float*)p, fixed_len); int n = fixed_len > 0 ? fixed_len : bytes / (int)sizeof(double); return v3_f64_array_str((double*)p, n); }
	if (kind == 8) { return f64__str((double)*(float*)p); }
	if (kind == 9) { int n = fixed_len > 0 ? fixed_len : bytes / (int)sizeof(float); return v3_f32_array_str((float*)p, n); }
	if (kind == 7) { return *(bool*)p ? v3_c_lit("true", 4) : v3_c_lit("false", 5); }
	return v3_c_lit("<map value>", 11);
}
static inline string v3_map_str(map m, int key_kind, int val_kind, int val_fixed_len) {
	string out = v3_c_lit("{", 1); bool first = true;
	for (int i = 0; i < m.key_values.len; ++i) {
		if (m.key_values.deletes != 0 && m.key_values.all_deleted != 0 && m.key_values.all_deleted[i] != 0) continue;
		if (!first) out = string__plus(out, v3_c_lit(", ", 2));
		void* key = (void*)(m.key_values.keys + i * m.key_values.key_bytes);
		void* val = (void*)(m.key_values.values + i * m.key_values.value_bytes);
		out = string__plus(out, v3_map_str_piece(key, key_kind, m.key_values.key_bytes, 0));
		out = string__plus(out, v3_c_lit(": ", 2));
		out = string__plus(out, v3_map_str_piece(val, val_kind, m.value_bytes, val_fixed_len));
		first = false;
	}
	return string__plus(out, v3_c_lit("}", 1));
}
static inline int array_index_int(Array a, i64 val) { for (int i = 0; i < a.len; i++) if (((i64*)a.data)[i] == val) return i; return -1; }
static inline int array_last_index_int(Array a, i64 val) { for (int i = a.len - 1; i >= 0; i--) if (((i64*)a.data)[i] == val) return i; return -1; }
static inline bool array_contains_int(Array a, i64 val) { return array_index_int(a, val) >= 0; }
static inline int array_index_u8(Array a, u8 val) { for (int i = 0; i < a.len; i++) if (((u8*)a.data)[i] == val) return i; return -1; }
static inline int array_last_index_u8(Array a, u8 val) { for (int i = a.len - 1; i >= 0; i--) if (((u8*)a.data)[i] == val) return i; return -1; }
static inline bool array_contains_u8(Array a, u8 val) { return array_index_u8(a, val) >= 0; }
static inline int array_index_string(Array a, string val) { string* data = (string*)a.data; for (int i = 0; i < a.len; i++) if (data[i].len == val.len && memcmp(data[i].str, val.str, val.len) == 0) return i; return -1; }
static inline int array_last_index_string(Array a, string val) { string* data = (string*)a.data; for (int i = a.len - 1; i >= 0; i--) if (data[i].len == val.len && memcmp(data[i].str, val.str, val.len) == 0) return i; return -1; }
static inline bool array_contains_string(Array a, string val) { return array_index_string(a, val) >= 0; }
static inline int array_last_index_raw(Array a, const void* val) { for (int i = a.len - 1; i >= 0; i--) if (memcmp((u8*)a.data + (size_t)i * (size_t)a.element_size, val, (size_t)a.element_size) == 0) return i; return -1; }
static inline bool array_eq_raw(Array a, Array b, int elem_size) { return a.len == b.len && (a.len == 0 || memcmp(a.data, b.data, (size_t)a.len * elem_size) == 0); }
static inline bool array_eq_string(Array a, Array b) { if (a.len != b.len) return false; string* ad = (string*)a.data; string* bd = (string*)b.data; for (int i = 0; i < a.len; i++) if (ad[i].len != bd[i].len || memcmp(ad[i].str, bd[i].str, ad[i].len) != 0) return false; return true; }
static inline bool array_eq_array(Array a, Array b, int depth) { if (a.len != b.len || a.element_size != b.element_size) return false; if (depth <= 1 || a.element_size != sizeof(Array)) { if (a.element_size == sizeof(string)) return array_eq_string(a, b); return array_eq_raw(a, b, a.element_size); } Array* ad = (Array*)a.data; Array* bd = (Array*)b.data; for (int i = 0; i < a.len; i++) { if (!array_eq_array(ad[i], bd[i], depth - 1)) return false; } return true; }
void* map__get(map* m, void* key, void* zero);
bool map__exists(map* m, void* key);
static inline bool v3_map_map_eq(map a, map b);
static inline bool v3_map_value_eq(void* a, void* b, int value_bytes) { if (value_bytes == sizeof(string)) { string sa = *(string*)a; string sb = *(string*)b; return sa.len == sb.len && (sa.len == 0 || memcmp(sa.str, sb.str, sa.len) == 0); } if (value_bytes == sizeof(map)) { return v3_map_map_eq(*(map*)a, *(map*)b); } if (value_bytes == sizeof(string) + sizeof(map)) { string sa = *(string*)a; string sb = *(string*)b; if (!(sa.len == sb.len && (sa.len == 0 || memcmp(sa.str, sb.str, sa.len) == 0))) return false; map ma = *(map*)((u8*)a + sizeof(string)); map mb = *(map*)((u8*)b + sizeof(string)); return v3_map_map_eq(ma, mb); } if (value_bytes == sizeof(Array)) { Array aa = *(Array*)a; Array bb = *(Array*)b; if (aa.element_size != bb.element_size) return false; if (aa.element_size == sizeof(string)) return array_eq_string(aa, bb); if (aa.element_size == sizeof(Array)) return array_eq_array(aa, bb, 8); return array_eq_raw(aa, bb, aa.element_size); } return memcmp(a, b, value_bytes) == 0; }
static inline bool v3_map_map_eq(map a, map b) { if (a.len != b.len) return false; for (int i = 0; i < a.key_values.len; ++i) { if (a.key_values.deletes != 0 && a.key_values.all_deleted != 0 && a.key_values.all_deleted[i] != 0) continue; void* ak = (void*)(a.key_values.keys + i * a.key_values.key_bytes); if (!map__exists(&b, ak)) return false; void* av = (void*)(a.key_values.values + i * a.key_values.value_bytes); void* bv = map__get(&b, ak, av); if (!v3_map_value_eq(av, bv, a.value_bytes)) return false; } return true; }
static inline bool fixed_array_contains_string(const string* a, int len, string val) { for (int i = 0; i < len; i++) if (a[i].len == val.len && memcmp(a[i].str, val.str, val.len) == 0) return true; return false; }
static inline bool fixed_array_contains_u8(const u8* a, int len, u8 val) { for (int i = 0; i < len; i++) if (a[i] == val) return true; return false; }
static inline bool fixed_array_contains_int(const i64* a, int len, i64 val) { for (int i = 0; i < len; i++) if (a[i] == val) return true; return false; }
static inline string Array_str(Array a) { if (a.element_size == 1) { u8* buf = (u8*)malloc((size_t)a.len + 1); if (a.len > 0) memcpy(buf, a.data, (size_t)a.len); buf[a.len] = 0; return (string){buf, a.len, 0}; } return (string){(u8*)"[]", 2, 1}; }
#ifndef max_int
#define max_int max_i32
#endif
#ifndef min_int
#define min_int min_i32
#endif

static void v3_eprint_lit(const char* s) {
	fprintf(stderr, "%s", s);
}
static void v3_eprintln_string(string s) {
	fprintf(stderr, "%.*s\n", s.len, (char*)s.str);
}

i64 g_autostr_type_stack[64] = {0};
i64 g_autostr_type_stack_len;
#if defined(__TINYC__) && defined(_WIN32)
typedef DWORD (WINAPI *g_autostr_addr_state_fls_alloc_fn)(void (WINAPI *)(void*));
typedef void* (WINAPI *g_autostr_addr_state_fls_get_fn)(DWORD);
typedef BOOL (WINAPI *g_autostr_addr_state_fls_set_fn)(DWORD, void*);
static DWORD g_autostr_addr_state_key = 0xFFFFFFFF;
static g_autostr_addr_state_fls_get_fn g_autostr_addr_state_fls_get;
static g_autostr_addr_state_fls_set_fn g_autostr_addr_state_fls_set;
static void WINAPI g_autostr_addr_state_slot_free(void* p) { free(p); }
static void g_autostr_addr_state_key_init(void) __attribute__((constructor));
static void g_autostr_addr_state_key_init(void) {
	void* kernel32 = GetModuleHandleA("kernel32.dll");
	g_autostr_addr_state_fls_alloc_fn fls_alloc = (g_autostr_addr_state_fls_alloc_fn)GetProcAddress(kernel32, "FlsAlloc");
	g_autostr_addr_state_fls_get = (g_autostr_addr_state_fls_get_fn)GetProcAddress(kernel32, "FlsGetValue");
	g_autostr_addr_state_fls_set = (g_autostr_addr_state_fls_set_fn)GetProcAddress(kernel32, "FlsSetValue");
	g_autostr_addr_state_key = fls_alloc && g_autostr_addr_state_fls_get && g_autostr_addr_state_fls_set ? fls_alloc(g_autostr_addr_state_slot_free) : TlsAlloc();
}
static AutostrAddrStackState* g_autostr_addr_state_slot(void) { void* p = g_autostr_addr_state_fls_get ? g_autostr_addr_state_fls_get(g_autostr_addr_state_key) : TlsGetValue(g_autostr_addr_state_key); if (!p) { p = calloc(1, sizeof(AutostrAddrStackState)); if (g_autostr_addr_state_fls_set) g_autostr_addr_state_fls_set(g_autostr_addr_state_key, p); else TlsSetValue(g_autostr_addr_state_key, p); } return (AutostrAddrStackState*)p; }
#define g_autostr_addr_state (*g_autostr_addr_state_slot())
#elif defined(__TINYC__)
static pthread_key_t g_autostr_addr_state_key;
static void g_autostr_addr_state_key_init(void) __attribute__((constructor));
static void g_autostr_addr_state_key_init(void) { pthread_key_create(&g_autostr_addr_state_key, free); }
static AutostrAddrStackState* g_autostr_addr_state_slot(void) { void* p = pthread_getspecific(g_autostr_addr_state_key); if (!p) { p = calloc(1, sizeof(AutostrAddrStackState)); pthread_setspecific(g_autostr_addr_state_key, p); } return (AutostrAddrStackState*)p; }
#define g_autostr_addr_state (*g_autostr_addr_state_slot())
#elif defined(_MSC_VER)
__declspec(thread) AutostrAddrStackState g_autostr_addr_state = {0};
#elif defined(__cplusplus)
thread_local AutostrAddrStackState g_autostr_addr_state = {0};
#else
_Thread_local AutostrAddrStackState g_autostr_addr_state = {0};
#endif
Array as_cast_type_indexes = {0};
bool v_memory_panic;
i64 total_m;
i64 g_main_argc;
void* g_main_argv;
void* g_live_reload_info;
VMemoryBlock* g_memory_block;
i64 g_prealloc_allocation_count;
i64 g_prealloc_allocated_bytes;

/* V3CACHE_LATE_DIRECTIVES_BEGIN */
/* V3CACHE_LATE_DIRECTIVES_END */
string Array_rune__string(Array ra);
void Array_string__free(Array* a);
string Array_string__join(Array a, string sep);
string Array_string__join_lines(Array s);
void Array_string__sort_by_len(Array* s);
void Array_string__sort_ignore_case(Array* s);
string Array_string__str(Array a);
Optional_u32 Array_u8__byterune(Array b);
string Array_u8__bytestr(Array b);
string Array_u8__hex(Array b);
Optional_u32 Array_u8__utf8_to_utf32(Array _bytes);
i64 Error__code(Error err);
string Error__msg(Error err);
void IError__free(IError* ie);
string IError__str(IError err);
i64 MessageError__code(MessageError err);
void MessageError__free(MessageError* err);
string MessageError__msg(MessageError err);
void SortedMap__free(SortedMap* m);
void StrIntpData__process_str_intp_data(StrIntpData* data, Array* sb);
void VAssertMetaInfo__free(VAssertMetaInfo* ami);
array __new_array(i64 mylen, i64 cap, i64 elm_size);
void _result_ok_markused(void);
u64 abs64(i64 x);
array array__clone(array* a);
void array__delete(array* a, i64 i);
void array__delete_last(array* a);
void array__ensure_cap(array* a, i64 required);
void array__free(array* a);
void* array__get(array a, i64 i);
void* array__get_i64(array a, i64 i);
void* array__get_ni(array a, i64 i);
void* array__get_u64(array a, u64 i);
void* array__get_with_check_i64(array a, i64 i);
void* array__get_with_check_ni(array a, i64 i);
void* array__get_with_check_u64(array a, u64 i);
void array__insert(array* a, i64 i, void* val);
void array__insert_many(array* a, i64 i, void* val, i64 size);
void* array__pop_left(array* a);
void array__prepend(array* a, void* val);
void array__push(array* a, void* val);
void array__push_many(array* a, void* val, i64 size);
array array__reverse(array a);
void array__set(array* a, i64 i, void* val);
void array__set_i64(array* a, i64 i, void* val);
void array__set_ni(array* a, i64 i, void* val);
void array__set_u64(array* a, u64 i, void* val);
array array__slice(array a, i64 start, i64 _end);
array array__slice_ni(array a, i64 _start, i64 _end);
void array__sort_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback);
bool autostr_addr_in_stack(void* addr);
void autostr_addr_pop(void);
void autostr_addr_push(void* addr);
bool autostr_addr_type_in_stack(void* addr, i64 typ);
void autostr_addr_type_push(void* addr, i64 typ);
string autostr_array_circular(i64 len);
bool autostr_type_in_stack(i64 typ);
void autostr_type_pop(void);
void autostr_type_push(i64 typ);
string bool__str(bool b);
void builtin_init(void);
Array byteptr__vbytes(u8* data, i64 len);
string byteptr__vstring(u8* bp);
string byteptr__vstring_with_len(u8* bp, i64 len);
string char__hex(char c);
string charptr__vstring(char* cp);
string charptr__vstring_with_len(char* cp, i64 len);
i64 compare_lower_strings(string* a, string* b);
i64 compare_strings_by_len(string* a, string* b);
string data_to_hex_string(u8* data, i64 len);
void drop_owned_interface_T_IError(IError value);
void drop_owned_result_error(IError err);
void drop_owned_result_error_interface(IError err);
void drop_owned_v3_interface_T_IError(IError value);
void eprintln(string s);
IError error(string message);
IError error_with_code(string message, i64 code);
string f32__str(float x);
string f32__strg(float x);
string f64__str(double x);
string f64__strg(double x);
float fabs32(float x);
double fabs64(double x);
string i16__hex(i16 nn);
string i16__str(i16 n);
string i32__str(i32 n);
string i64__str(i64 nn);
string i8__hex(i8 nn);
string i8__str(i8 n);
u32 impl_utf8_to_utf32(u8* _bytes, i64 _bytes_len);
string int__hex(i64 nn);
string int__str(i64 n);
u8* malloc_noscan(ptrdiff_t n);
void map__clear(map* m);
map map__clone(map* m);
void map__delete(map* m, void* key);
bool map__exists(map* m, void* key);
void map__free(map* m);
void* map__get(map* m, void* key, void* zero);
void* map__get_and_set(map* m, void* key, void* zero);
void* map__get_check(map* m, void* key);
array map__keys(map* m);
void map__reserve(map* m, u32 n);
void map__set(map* m, void* key, void* value);
array map__values(map* m);
void map_clone_int_1(void* dest, void* pkey);
void map_clone_int_2(void* dest, void* pkey);
void map_clone_int_4(void* dest, void* pkey);
void map_clone_int_8(void* dest, void* pkey);
void map_clone_string(void* dest, void* pkey);
bool map_eq_int_1(void* a, void* b);
bool map_eq_int_2(void* a, void* b);
bool map_eq_int_4(void* a, void* b);
bool map_eq_int_8(void* a, void* b);
bool map_eq_string(void* a, void* b);
void map_free_nop(void* _0);
void map_free_string(void* pkey);
u64 map_hash_int_1(void* pkey);
u64 map_hash_int_2(void* pkey);
u64 map_hash_int_4(void* pkey);
u64 map_hash_int_8(void* pkey);
u64 map_hash_string(void* pkey);
bool map_map_eq(map a, map b);
void mapnode__free(mapnode* n);
void* memdup(void* src, ptrdiff_t sz);
array new_array_from_c_array(i64 len, i64 cap, i64 elm_size, void* c_array);
array new_array_from_c_array_noscan(i64 len, i64 cap, i64 elm_size, void* c_array);
void panic_n(string s, i64 number1);
void panic_n2(string s, i64 number1, i64 number2);
void println(string s);
string ptr_str(void* ptr);
Array rune__bytes(u32 c);
string rune__str(u32 c);
u32 rune__to_lower(u32 c);
string str_intp_sub(string base_str, string in_str);
string strconv__Dec32__get_string_32(strconv__Dec32 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__Dec64__get_string_64(strconv__Dec64 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__f32_to_str(float f, i64 n_digit);
string strconv__f32_to_str_l(float f);
string strconv__f32_to_str_l_with_dot(float f);
string strconv__f64_to_str(double f, i64 n_digit);
string strconv__f64_to_str_l(double f);
string strconv__f64_to_str_l_with_dot(double f);
string strconv__f64_to_str_lnd1(double f, i64 dec_digit);
string strconv__f64_to_str_pad(double f, i64 n_digit);
double strconv__fabs(double x);
string strconv__format_dec_old(u64 d, strconv__BF_param p);
void strconv__format_dec_sb(u64 d, strconv__BF_param p, Array* res);
string strconv__format_es(double f, strconv__BF_param p);
string strconv__format_es_old(double f, strconv__BF_param p);
string strconv__format_fl(double f, strconv__BF_param p);
string strconv__format_fl_old(double f, strconv__BF_param p);
string strconv__format_int(i64 n, i64 radix);
string strconv__format_str(string s, strconv__BF_param p);
void strconv__format_str_sb(string s, strconv__BF_param p, Array* sb);
string strconv__format_uint(u64 n, i64 radix);
string strconv__fxx_to_str_l_parse(string s);
string strconv__fxx_to_str_l_parse_with_dot(string s);
string strconv__remove_tail_zeros(string s);
string strconv__remove_tail_zeros_old(string s);
string strconv__v_sprintf(string str, Array pt);
void strconv__v_sprintf_panic(i64 idx, i64 len);
string string__all_after(string s, string sub);
string string__all_after_last(string s, string sub);
string string__all_before(string s, string sub);
string string__all_before_last(string s, string sub);
u8 string__at_i64(string s, i64 idx);
u8 string__at_ni(string s, i64 idx);
u8 string__at_u64(string s, u64 idx);
Optional_u8 string__at_with_check_i64(string s, i64 idx);
Optional_u8 string__at_with_check_ni(string s, i64 idx);
Optional_u8 string__at_with_check_u64(string s, u64 idx);
string string__clone(string a);
bool string__eq(string s, string a);
void string__free(string* s);
Optional_i64 string__index(string s, string p);
bool string__is_capital(string s);
bool string__lt(string s, string a);
string string__plus(string s, string a);
string string__substr(string s, i64 start, i64 _end);
string string__substr_ni(string s, i64 _start, i64 _end);
string string__to_lower_ascii(string s);
string string__to_upper(string s);
string string_plus_many(i64 data_len, string* input_base);
void strings__Builder__free(Array* b);
string strings__Builder__str(Array* b);
void strings__Builder__write_ptr(Array* b, u8* ptr, i64 len);
void strings__Builder__write_runes(Array* b, Array runes);
void strings__Builder__write_string(Array* b, string s);
void strings__Builder__write_u8(Array* b, u8 data);
Array strings__new_builder(i64 initial_size);
string tos(u8* s, i64 len);
string tos_clone(u8* const_s);
string u64__hex(u64 nn);
string u64__str(u64 nn);
string u8__ascii_str(u8 b);
void u8__free(u8* data);
string u8__hex(u8 nn);
bool u8__is_capital(u8 c);
bool u8__is_letter(u8 c);
string u8__str_escaped(u8 b);
string u8__vstring(u8* bp);
string u8__vstring_with_len(u8* bp, i64 len);
string utf32_to_str(u32 code);
void v_exit(i64 code);
i64 v_fixed_index_i64(i64 i, i64 len);
i64 v_fixed_index_ni(i64 i, i64 len);
i64 v_fixed_index_u64(u64 i, i64 len);
void v_free(void* ptr);
void v_panic(string s);
i64 v_slice_index_i64(i64 i);
i64 v_slice_index_u64(u64 i);
void* vmemcpy(void* dest, void* const_src, ptrdiff_t n);
Array voidptr__vbytes(void* data, i64 len);

DenseArray DenseArray__clone(DenseArray* d);
void DenseArray__delete(DenseArray* d, i64 i);
i64 DenseArray__expand(DenseArray* d);
bool DenseArray__has_index(DenseArray* d, i64 i);
void* DenseArray__key(DenseArray* d, i64 i);
void DenseArray__reserve(DenseArray* d, i64 n);
void DenseArray__trim_deleted_tail(DenseArray* d);
void* DenseArray__value(DenseArray* d, i64 i);
void DenseArray__zeros_to_end(DenseArray* d);
i64 Error__code(Error err);
string Error__msg(Error err);
void GraphemeState__push(GraphemeState* gs, u32 r, int prop);
void IError__free(IError* ie);
string IError__str(IError err);
Optional_u32 InputRuneIterator__next(InputRuneIterator* self);
i64 MessageError__code(MessageError err);
void MessageError__free(MessageError* err);
string MessageError__msg(MessageError err);
string MessageError__str(MessageError err);
string None____str(None__ _0);
Optional_u32 RunesIterator__next(RunesIterator* ri);
void SortedMap__delete(SortedMap* m, string key);
bool SortedMap__exists(SortedMap m, string key);
void SortedMap__free(SortedMap* m);
bool SortedMap__get(SortedMap m, string key, void* out);
Array SortedMap__keys(SortedMap* m);
void SortedMap__set(SortedMap* m, string key, void* value);
void StrIntpData__process_str_intp_data(StrIntpData* data, Array* sb);
string StrIntpType_str(int x);
void VAssertMetaInfo__free(VAssertMetaInfo* ami);
string _Atomic__int_str(i64 x);
void* __as_cast(void* obj, i64 obj_type, i64 expected_type);
u64 __at_least_one(u64 how_many);
array __new_array(i64 mylen, i64 cap, i64 elm_size);
array __new_array_noscan(i64 mylen, i64 cap, i64 elm_size);
array __new_array_with_array_default(i64 mylen, i64 cap, i64 elm_size, array val, i64 depth);
array __new_array_with_array_default_noscan(i64 mylen, i64 cap, i64 elm_size, array val, i64 depth);
array __new_array_with_default(i64 mylen, i64 cap, i64 elm_size, void* val);
array __new_array_with_default_noscan(i64 mylen, i64 cap, i64 elm_size, void* val);
array __new_array_with_map_default(i64 mylen, i64 cap, i64 elm_size, map val);
array __new_array_with_multi_default(i64 mylen, i64 cap, i64 elm_size, void* val);
array __new_array_with_multi_default_noscan(i64 mylen, i64 cap, i64 elm_size, void* val);
void __print_assert_failure(VAssertMetaInfo* i);
bool __v2_flag_all_int(i64 receiver, i64 flags);
bool __v2_flag_has_int(i64 receiver, i64 flag);
void _ht_alloc(u8* p, ptrdiff_t n);
void _ht_free(void* p);
void _memory_panic(string fname, ptrdiff_t size);
void _option_clone(_option* current, _option* option, i64 size);
void _option_none(void* data, _option* option, i64 size);
void _option_ok(void* data, _option* option, i64 size);
void _result_clone(_result* current, _result* res, i64 size);
void _result_ok(void* data, _result* res, i64 size);
void _result_ok_markused(void);
void _write_buf_to_fd(i64 fd, u8* buf, i64 buf_len);
void _writeln_to_fd(i64 fd, string s);
u64 abs64(i64 x);
void* alloc_array_data(u64 total_size);
void* alloc_array_data_noscan(u64 total_size);
void* alloc_array_data_noscan_uninit(u64 total_size);
void* alloc_array_data_uninit(u64 total_size);
Array arguments(void);
void* array__alloc_array_data_like(array a, u64 total_size);
void* array__alloc_array_data_like_uninit(array a, u64 total_size);
bool array__buffer_has_slices(array a);
void array__clear(array* a);
array array__clone(array* a);
void array__clone_shallow_to_cap(array* a, i64 new_cap);
array array__clone_static_to_depth(array a, i64 depth);
array array__clone_static_to_depth_noscan(array a, i64 depth);
array array__clone_to_depth(array* a, i64 depth);
array array__clone_to_depth_noscan(array* a, i64 depth);
ArrayDataHeader* array__data_header(array a);
void array__delete(array* a, i64 i);
void array__delete_last(array* a);
void array__delete_many(array* a, i64 i, i64 size);
void array__drop(array* a, i64 num);
void array__ensure_cap(array* a, i64 required);
void array__ensure_cap_noscan(array* a, i64 required);
void* array__first(array a);
void array__free(array* a);
void* array__get(array a, i64 i);
void* array__get_i64(array a, i64 i);
void* array__get_ni(array a, i64 i);
void* array__get_u64(array a, u64 i);
void* array__get_unsafe(array a, i64 i);
void* array__get_with_check(array a, i64 i);
void* array__get_with_check_i64(array a, i64 i);
void* array__get_with_check_ni(array a, i64 i);
void* array__get_with_check_u64(array a, u64 i);
void array__grow_cap(array* a, i64 amount);
void array__grow_cap_noscan(array* a, i64 amount);
void array__grow_len(array* a, i64 amount);
void array__grow_len_noscan(array* a, i64 amount);
void array__insert(array* a, i64 i, void* val);
void array__insert_many(array* a, i64 i, void* val, i64 size);
void array__insert_many_noscan(array* a, i64 i, void* val, i64 size);
void array__insert_noscan(array* a, i64 i, void* val);
bool array__is_slice_view(array a);
void* array__last(array a);
void array__mark_buffer_has_slices(array* a);
bool array__needs_unique_append(array a, i64 required);
bool array__needs_unique_shift(array a, i64 required);
bool array__needs_unique_shrink(array a);
Array array__pointers(array a);
void* array__pop(array* a);
void* array__pop_left(array* a);
void* array__pop_left_noscan(array* a);
void* array__pop_noscan(array* a);
void array__prepend(array* a, void* val);
void array__prepend_many(array* a, void* val, i64 size);
void array__prepend_many_noscan(array* a, void* val, i64 size);
void array__prepend_noscan(array* a, void* val);
void array__push(array* a, void* val);
void array__push_many(array* a, void* val, i64 size);
void array__push_many_noscan(array* a, void* val, i64 size);
void array__push_noscan(array* a, void* val);
array array__repeat(array a, i64 count);
array array__repeat_to_depth(array a, i64 count, i64 depth);
array array__repeat_to_depth_noscan(array a, i64 count, i64 depth);
void array__reset(array* a);
array array__reverse(array a);
void array__reverse_in_place(array* a);
array array__reverse_noscan(array a);
void array__set(array* a, i64 i, void* val);
void array__set_i64(array* a, i64 i, void* val);
void array__set_managed_flags(array* a, bool is_slice);
void array__set_ni(array* a, i64 i, void* val);
void array__set_u64(array* a, u64 i, void* val);
void array__set_unsafe(array* a, i64 i, void* val);
array array__slice(array a, i64 start, i64 _end);
array array__slice_ni(array a, i64 _start, i64 _end);
void array__sort_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback);
array array__sorted_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback);
void array__trim(array* a, i64 v_index);
bool array__uses_noscan_data(array a);
u64 array_data_allocation_size(u64 total_size);
i64 array_data_header_size(void);
Optional at_exit(_fn_ptr_39790037d38ea68 cb);
bool autostr_addr_in_stack(void* addr);
void autostr_addr_pop(void);
void autostr_addr_push(void* addr);
bool autostr_addr_type_in_stack(void* addr, i64 typ);
void autostr_addr_type_push(void* addr, i64 typ);
string autostr_array_circular(i64 len);
bool autostr_type_in_stack(i64 typ);
void autostr_type_pop(void);
void autostr_type_push(i64 typ);
string backtrace_addr2line_executable(string executable, string current_executable_name);
string backtrace_current_executable_name(void);
string backtrace_shell_quote(string s);
multi_return_u32_u32 bits__add_32(u32 x, u32 y, u32 carry);
multi_return_u64_u64 bits__add_64(u64 x, u64 y, u64 carry);
multi_return_u32_u32 bits__div_32(u32 hi, u32 lo, u32 y);
multi_return_u32_u32 bits__div_32_default(u32 hi, u32 lo, u32 y);
multi_return_u64_u64 bits__div_64(u64 hi, u64 lo, u64 v_y1);
multi_return_u64_u64 bits__div_64_default(u64 hi, u64 lo, u64 v_y1);
u32 bits__f32_bits(float f);
float bits__f32_from_bits(u32 b);
u64 bits__f64_bits(double f);
double bits__f64_from_bits(u64 b);
i64 bits__leading_zeros_16(u16 x);
i64 bits__leading_zeros_16_default(u16 x);
i64 bits__leading_zeros_32(u32 x);
i64 bits__leading_zeros_32_default(u32 x);
i64 bits__leading_zeros_64(u64 x);
i64 bits__leading_zeros_64_default(u64 x);
i64 bits__leading_zeros_8(u8 x);
i64 bits__leading_zeros_8_default(u8 x);
i64 bits__len_16(u16 x);
i64 bits__len_32(u32 x);
i64 bits__len_64(u64 x);
i64 bits__len_8(u8 x);
multi_return_u32_u32 bits__mul_32(u32 x, u32 y);
multi_return_u32_u32 bits__mul_32_default(u32 x, u32 y);
multi_return_u64_u64 bits__mul_64(u64 x, u64 y);
multi_return_u64_u64 bits__mul_64_default(u64 x, u64 y);
multi_return_u32_u32 bits__mul_add_32(u32 x, u32 y, u32 z);
multi_return_u32_u32 bits__mul_add_32_default(u32 x, u32 y, u32 z);
multi_return_u64_u64 bits__mul_add_64(u64 x, u64 y, u64 z);
multi_return_u64_u64 bits__mul_add_64_default(u64 x, u64 y, u64 z);
multi_return_double_i64 bits__normalize(double x);
i64 bits__ones_count_16(u16 x);
i64 bits__ones_count_16_default(u16 x);
i64 bits__ones_count_32(u32 x);
i64 bits__ones_count_32_default(u32 x);
i64 bits__ones_count_64(u64 x);
i64 bits__ones_count_64_default(u64 x);
i64 bits__ones_count_8(u8 x);
i64 bits__ones_count_8_default(u8 x);
u32 bits__rem_32(u32 hi, u32 lo, u32 y);
u64 bits__rem_64(u64 hi, u64 lo, u64 y);
u16 bits__reverse_16(u16 x);
u32 bits__reverse_32(u32 x);
u64 bits__reverse_64(u64 x);
u8 bits__reverse_8(u8 x);
u16 bits__reverse_bytes_16(u16 x);
u32 bits__reverse_bytes_32(u32 x);
u64 bits__reverse_bytes_64(u64 x);
u16 bits__rotate_left_16(u16 x, i64 k);
u32 bits__rotate_left_32(u32 x, i64 k);
u64 bits__rotate_left_64(u64 x, i64 k);
u8 bits__rotate_left_8(u8 x, i64 k);
multi_return_u32_u32 bits__sub_32(u32 x, u32 y, u32 borrow);
multi_return_u64_u64 bits__sub_64(u64 x, u64 y, u64 borrow);
i64 bits__trailing_zeros_16(u16 x);
i64 bits__trailing_zeros_16_default(u16 x);
i64 bits__trailing_zeros_32(u32 x);
i64 bits__trailing_zeros_32_default(u32 x);
i64 bits__trailing_zeros_64(u64 x);
i64 bits__trailing_zeros_64_default(u64 x);
i64 bits__trailing_zeros_8(u8 x);
i64 bits__trailing_zeros_8_default(u8 x);
string bool__str(bool b);
void break_if_debugger_attached(void);
Array bsd_backtrace_resolve_atos(void** buffer, i64 nr_frames);
void builtin_init(void);
string byteptr__str(u8* nn);
Array byteptr__vbytes(u8* data, i64 len);
string byteptr__vstring(u8* bp);
string byteptr__vstring_literal(u8* bp);
string byteptr__vstring_literal_with_len(u8* bp, i64 len);
string byteptr__vstring_with_len(u8* bp, i64 len);
string c_error_number_str(i64 errnum);
void chan__close(chan ch, Array err);
int chan__try_pop(chan ch, void* obj);
int chan__try_push(chan ch, void* obj);
string char__hex(char c);
string char__str(char* cptr);
string char__vstring(char* cp);
string char__vstring_literal(char* cp);
string char__vstring_literal_with_len(char* cp, i64 len);
string char__vstring_with_len(char* cp, i64 len);
string charptr__str(char* nn);
string charptr__vstring(char* cp);
string charptr__vstring_literal(char* cp);
string charptr__vstring_literal_with_len(char* cp, i64 len);
string charptr__vstring_with_len(char* cp, i64 len);
i64 compare_lower_strings(string* a, string* b);
i64 compare_strings(string* a, string* b);
i64 compare_strings_by_len(string* a, string* b);
i64 copy(Array* dst, Array src);
void copy_element_to(void* dest, void* src, i64 element_size);
string cstring_to_vstring(char* const_s);
string data_to_hex_string(u8* data, i64 len);
string demangle_backtrace_sym(string s);
string demangle_v_symbol(string cname);
void drop_owned_T_IError(IError value);
void drop_owned_interface_T_IError(IError value);
void drop_owned_result_error(IError err);
void drop_owned_result_error_interface(IError err);
void drop_owned_v3_interface_T_IError(IError value);
void eprint(string s);
void eprint_libbacktrace(i64 frames_to_skip);
void eprint_space_padding(string output, i64 max_len);
void eprintln(string s);
IError error(string message);
IError error_with_code(string message, i64 code);
bool f32__eq_epsilon(float a, float b);
string f32__str(float x);
string f32__strg(float x);
string f32__strlong(float x);
string f32__strsci(float x, i64 digit_num);
float f32_abs(float a);
float f32_max(float a, float b);
float f32_min(float a, float b);
bool f64__eq_epsilon(double a, double b);
string f64__str(double x);
string f64__strg(double x);
string f64__strlong(double x);
string f64__strsci(double x, i64 digit_num);
double f64_abs(double a);
double f64_max(double a, double b);
double f64_min(double a, double b);
float fabs32(float x);
double fabs64(double x);
bool fast_string_eq(string a, string b);
string float_literal__str(float_literal d);
void flush_stderr(void);
void flush_stdout(void);
void gc_check_leaks(void);
void gc_collect(void);
void gc_disable(void);
void gc_enable(void);
void gc_get_warn_proc(void);
GCHeapUsage gc_heap_usage(void);
bool gc_is_enabled(void);
size_t gc_memory_use(void);
void gc_set_warn_proc(_fn_ptr_a73f2ae88698453e cb);
u32 get_str_intp_u32_format(int fmt_type, i64 in_width, i64 in_precision, bool in_tail_zeros, bool in_sign, u8 in_pad_ch, i64 in_base, bool in_upper_case);
u64 get_str_intp_u64_format(int fmt_type, i64 in_width, i64 in_precision, bool in_tail_zeros, bool in_sign, u8 in_pad_ch, i64 in_base, bool in_upper_case);
int grapheme_break_property(u32 r);
u32 grapheme_hex_byte(string ranges, i64 i);
u32 grapheme_hex_nibble(u8 c);
u32 grapheme_range_value(string ranges, i64 value_idx);
GraphemeState grapheme_state_from_rune(u32 r, int prop);
u64 hash__sum64(Array key, u64 seed);
u64 hash__sum64_string(string key, u64 seed);
u64 hash__wyhash64_c(u64 a, u64 b);
u64 hash__wyhash_c(u8* key, u64 len, u64 seed);
u64 hash__wymum(u64 a, u64 b);
string i16__hex(i16 nn);
string i16__hex_full(i16 nn);
string i16__str(i16 n);
string i32__str(i32 n);
string i64__hex(i64 nn);
string i64__hex_full(i64 nn);
string i64__str(i64 nn);
string i8__hex(i8 nn);
string i8__hex_full(i8 nn);
string i8__str(i8 n);
string impl_i64_to_string(i64 nn);
u32 impl_utf8_to_utf32(u8* _bytes, i64 _bytes_len);
bool in_grapheme_ranges(u32 r, string ranges);
i64 input_character(void);
Optional_u32 input_rune(void);
InputRuneIterator input_rune_iterator(void);
string int__hex(i64 nn);
string int__hex2(i64 n);
string int__hex_full(i64 nn);
string int__str(i64 n);
string int__str_l(i64 nn, i64 max);
string int_literal__hex(int_literal nn);
string int_literal__hex_full(int_literal nn);
string int_literal__str(int_literal n);
i64 int_max(i64 a, i64 b);
i64 int_min(i64 a, i64 b);
void internal_gc_warn_proc_none(char* msg, size_t arg);
bool is_extended_pictographic(u32 r);
string isize__str(ptrdiff_t x);
bool isnil(void* v);
u8* malloc_noscan(ptrdiff_t n);
u8* malloc_noscan_uninit(ptrdiff_t n);
u8* malloc_uncollectable(ptrdiff_t n);
u8* malloc_uninit(ptrdiff_t n);
void map__cached_rehash(map* m, u32 old_cap);
void map__clear(map* m);
map map__clone(map* m);
void map__delete(map* m, void* key);
void map__ensure_extra_metas(map* m, u32 probe_count);
void map__ensure_extra_metas_grow(map* m);
bool map__exists(map* m, void* key);
void map__expand(map* m);
void map__free(map* m);
void* map__get(map* m, void* key, void* zero);
void* map__get_and_set(map* m, void* key, void* zero);
void* map__get_check(map* m, void* key);
void* map__get_key_check(map* m, void* key);
multi_return_u32_u32 map__key_to_index(map* m, void* pkey);
array map__keys(map* m);
void map__meta_greater(map* m, u32 _index, u32 _metas, u32 kvi);
multi_return_u32_u32 map__meta_less(map* m, u32 _index, u32 _metas);
map map__move(map* m);
void map__rehash(map* m);
void map__reserve(map* m, u32 n);
void map__reserve_metas(map* m, u32 meta_bytes);
void map__set(map* m, void* key, void* value);
array map__values(map* m);
void map_clone_int_1(void* dest, void* pkey);
void map_clone_int_2(void* dest, void* pkey);
void map_clone_int_4(void* dest, void* pkey);
void map_clone_int_8(void* dest, void* pkey);
void map_clone_string(void* dest, void* pkey);
void* map_enum_fn(i64 kind, i64 esize);
bool map_eq_int_1(void* a, void* b);
bool map_eq_int_2(void* a, void* b);
bool map_eq_int_4(void* a, void* b);
bool map_eq_int_8(void* a, void* b);
bool map_eq_string(void* a, void* b);
void map_free_nop(void* _0);
void map_free_string(void* pkey);
u64 map_hash_int_1(void* pkey);
u64 map_hash_int_2(void* pkey);
u64 map_hash_int_4(void* pkey);
u64 map_hash_int_8(void* pkey);
u64 map_hash_string(void* pkey);
bool map_map_eq(map a, map b);
void mapnode__borrow_from_next(mapnode* n, i64 idx);
void mapnode__borrow_from_prev(mapnode* n, i64 idx);
void mapnode__fill(mapnode* n, i64 idx);
i64 mapnode__find_key(mapnode* n, string k);
void mapnode__free(mapnode* n);
void mapnode__merge(mapnode* n, i64 idx);
void mapnode__remove_from_leaf(mapnode* n, i64 idx);
void mapnode__remove_from_non_leaf(mapnode* n, i64 idx);
bool mapnode__remove_key(mapnode* n, string k);
void mapnode__split_child(mapnode* n, i64 child_index, mapnode* y);
i64 mapnode__subkeys(mapnode* n, Array* keys, i64 at);
void* memdup(void* src, ptrdiff_t sz);
void* memdup_align(void* src, ptrdiff_t sz, ptrdiff_t align);
void* memdup_noscan(void* src, ptrdiff_t sz);
void* memdup_uncollectable(void* src, ptrdiff_t sz);
array new_array_from_array_and_c_array(array base, i64 new_count, i64 elm_size, void* c_array);
array new_array_from_c_array(i64 len, i64 cap, i64 elm_size, void* c_array);
array new_array_from_c_array_no_alloc(i64 len, i64 cap, i64 elm_size, void* c_array);
array new_array_from_c_array_noscan(i64 len, i64 cap, i64 elm_size, void* c_array);
DenseArray new_dense_array(i64 key_bytes, i64 value_bytes);
map new_map(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn);
map new_map_init(_fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn, i64 n, i64 key_bytes, i64 value_bytes, void* keys, void* values);
map new_map_init_noscan_key(_fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn, i64 n, i64 key_bytes, i64 value_bytes, void* keys, void* values);
map new_map_init_noscan_key_value(_fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn, i64 n, i64 key_bytes, i64 value_bytes, void* keys, void* values);
map new_map_init_noscan_value(_fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn, i64 n, i64 key_bytes, i64 value_bytes, void* keys, void* values);
map new_map_noscan_key(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn);
map new_map_noscan_key_value(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn);
map new_map_noscan_value(i64 key_bytes, i64 value_bytes, _fn_ptr_1e8d64a3d95a0da1 hash_fn, _fn_ptr_c95f092653bee64 key_eq_fn, _fn_ptr_1a3da2026b1489ea clone_fn, _fn_ptr_5373f7edc7b60e26 free_fn);
map new_map_update_init(map* update, i64 n, i64 key_bytes, i64 value_bytes, void* keys, void* values);
mapnode* new_node(void);
SortedMap new_sorted_map(i64 n, i64 value_bytes);
SortedMap new_sorted_map_init(i64 n, i64 value_bytes, string* keys, void* values);
string none__str(Optional _0);
void panic_debug(i64 line_no, string file, string mod, string fn_name, string s);
void panic_error_number(string basestr, i64 errnum);
void panic_lasterr(string base);
void panic_n(string s, i64 number1);
void panic_n2(string s, i64 number1, i64 number2);
void panic_n3(string s, i64 number1, i64 number2, i64 number3);
void panic_on_negative_cap(i64 cap);
void panic_on_negative_len(i64 len);
void panic_option_not_set(string s);
void panic_result_not_set(string s);
u8* prealloc_calloc(ptrdiff_t n);
u8* prealloc_malloc(ptrdiff_t n);
u8* prealloc_malloc_align(ptrdiff_t n, ptrdiff_t align);
u8* prealloc_realloc(u8* old_data, ptrdiff_t old_size, ptrdiff_t new_size);
bool prealloc_recyclable_block_size(ptrdiff_t size);
void prealloc_recycle_cache_free(VPreallocBlockCache* cache);
i64 prealloc_recycle_cache_limit(void);
void prealloc_scope_abandon(void* scope_ptr);
void prealloc_scope_add_block(VPreallocScope* scope, VMemoryBlock* block);
void* prealloc_scope_begin(void);
void prealloc_scope_checkpoint(char* label);
void prealloc_scope_detach_current(VPreallocScope* scope);
void prealloc_scope_end(void* scope_ptr);
void prealloc_scope_finish_if_ready(VPreallocScope* scope);
void prealloc_scope_free_after(void* scope_ptr);
void prealloc_scope_free_blocks(VPreallocScope* scope);
void prealloc_scope_leave(void* scope_ptr);
bool prealloc_scope_owns(void* scope_ptr, void* ptr);
void prealloc_scope_release(void* scope_ptr);
void prealloc_scope_request_free(VPreallocScope* scope, bool abandoned);
void prealloc_scope_resume(void* scope_ptr, void* state);
void* prealloc_scope_retain_current(void);
void* prealloc_scope_suspend(void* scope_ptr);
PreallocStats prealloc_stats_snapshot(void);
void prealloc_thread_cleanup(void);
void prealloc_trace_scope(char* action, VPreallocScope* scope);
void prealloc_vcleanup(void);
void prealloc_vinit(void);
void print(string s);
void print_backtrace(void);
bool print_backtrace_skipping_top_frames(i64 xskipframes);
bool print_backtrace_skipping_top_frames_bsd(i64 skipframes);
bool print_backtrace_skipping_top_frames_linux(i64 skipframes);
i64 print_character(u8 ch);
void print_libbacktrace(i64 frames_to_skip);
void println(string s);
string ptr_str(void* ptr);
u8* realloc_data(u8* old_data, i64 old_size, i64 new_size);
string reuse_data_as_string(Array buffer);
Array reuse_string_as_data(string s);
Array rune__bytes(u32 c);
string rune__hex(u32 r);
i64 rune__length_in_bytes(u32 c);
u32 rune__map_to(u32 c, int mode);
string rune__repeat(u32 c, i64 count);
string rune__str(u32 c);
u32 rune__to_lower(u32 c);
u32 rune__to_title(u32 c);
u32 rune__to_upper(u32 c);
void set_stream_unbuffered(FILE* stream);
bool should_break_grapheme(GraphemeState gs, u32 r, int prop);
Array split_generic_params(string s);
string str_intp(i64 data_len, StrIntpData* input_base);
string str_intp_g32(string in_str);
string str_intp_g64(string in_str);
string str_intp_rune(string in_str);
string str_intp_sq(string in_str);
string str_intp_sub(string base_str, string in_str);
string strconv__Dec32__get_string_32(strconv__Dec32 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
string strconv__Dec64__get_string_64(strconv__Dec64 d, bool neg, i64 i_n_digit, i64 i_pad_digit);
multi_return_u32_u32_u32 strconv__add96(u32 s2, u32 s1, u32 s0, u32 d2, u32 d1, u32 d0);
void strconv__assert1(bool t, string msg);
Optional_double strconv__atof64(string s, strconv__AtoF64Param param);
double strconv__atof_quick(string s);
Optional_i64 strconv__atoi(string s);
Optional_i16 strconv__atoi16(string s);
Optional_i32 strconv__atoi32(string s);
Optional_i64 strconv__atoi64(string s);
Optional_i8 strconv__atoi8(string s);
Optional_i64 strconv__atoi_common(string s, i64 type_min, i64 type_max);
Optional_multi_return_i64_i64 strconv__atoi_common_check(string s);
Optional_u32 strconv__atou(string s);
Optional_u16 strconv__atou16(string s);
Optional_u32 strconv__atou32(string s);
Optional_u64 strconv__atou64(string s);
Optional_u8 strconv__atou8(string s);
Optional_u64 strconv__atou_common(string s, u64 type_max);
Optional_i64 strconv__atou_common_check(string s);
i64 strconv__bool_to_int(bool b);
u32 strconv__bool_to_u32(bool b);
u64 strconv__bool_to_u64(bool b);
u8 strconv__byte_to_lower(u8 c);
Optional_i64 strconv__common_parse_int(string _s, i64 base, i64 _bit_size, bool error_on_non_digit, bool error_on_high_digit);
Optional_u64 strconv__common_parse_uint(string s, i64 _base, i64 _bit_size, bool error_on_non_digit, bool error_on_high_digit);
multi_return_u64_i64 strconv__common_parse_uint2(string s, i64 _base, i64 _bit_size);
u64 strconv__converter(strconv__PrepNumber* pn);
i64 strconv__dec_digits(u64 n);
strconv__Dec32 strconv__f32_to_decimal(u32 mant, u32 exp);
multi_return_strconv__Dec32_bool strconv__f32_to_decimal_exact_int(u32 i_mant, u32 exp);
string strconv__f32_to_str(float f, i64 n_digit);
string strconv__f32_to_str_l(float f);
string strconv__f32_to_str_l_with_dot(float f);
string strconv__f32_to_str_pad(float f, i64 n_digit);
strconv__Dec64 strconv__f64_to_decimal(u64 mant, u64 exp);
multi_return_strconv__Dec64_bool strconv__f64_to_decimal_exact_int(u64 i_mant, u64 exp);
string strconv__f64_to_str(double f, i64 n_digit);
string strconv__f64_to_str_l(double f);
string strconv__f64_to_str_l_with_dot(double f);
string strconv__f64_to_str_lnd1(double f, i64 dec_digit);
string strconv__f64_to_str_pad(double f, i64 n_digit);
double strconv__fabs(double x);
string strconv__format_dec_old(u64 d, strconv__BF_param p);
void strconv__format_dec_sb(u64 d, strconv__BF_param p, Array* res);
string strconv__format_es(double f, strconv__BF_param p);
string strconv__format_es_old(double f, strconv__BF_param p);
string strconv__format_fl(double f, strconv__BF_param p);
string strconv__format_fl_old(double f, strconv__BF_param p);
string strconv__format_int(i64 n, i64 radix);
string strconv__format_str(string s, strconv__BF_param p);
void strconv__format_str_sb(string s, strconv__BF_param p, Array* sb);
string strconv__format_uint(u64 n, i64 radix);
string strconv__ftoa_32(float f);
string strconv__ftoa_64(double f);
string strconv__ftoa_long_32(float f);
string strconv__ftoa_long_64(double f);
string strconv__fxx_to_str_l_parse(string s);
string strconv__fxx_to_str_l_parse_with_dot(string s);
string strconv__get_string_special(bool neg, bool expZero, bool mantZero);
bool strconv__is_digit(u8 x);
bool strconv__is_exp(u8 x);
bool strconv__is_space(u8 x);
u32 strconv__log10_pow2(i64 e);
u32 strconv__log10_pow5(i64 e);
multi_return_u32_u32_u32 strconv__lsl96(u32 s2, u32 s1, u32 s0);
multi_return_u32_u32_u32 strconv__lsr96(u32 s2, u32 s1, u32 s0);
u32 strconv__mul_pow5_div_pow2(u32 m, u32 i, i64 j);
u32 strconv__mul_pow5_invdiv_pow2(u32 m, u32 q, i64 j);
u32 strconv__mul_shift_32(u32 m, u64 mul, i64 ishift);
u64 strconv__mul_shift_64(u64 m, strconv__Uint128 mul, i64 shift);
bool strconv__multiple_of_power_of_five_32(u32 v, u32 p);
bool strconv__multiple_of_power_of_five_64(u64 v, u32 p);
bool strconv__multiple_of_power_of_two_32(u32 v, u32 p);
bool strconv__multiple_of_power_of_two_64(u64 v, u32 p);
Optional_i64 strconv__parse_int(string _s, i64 base, i64 _bit_size);
Optional_u64 strconv__parse_uint(string s, i64 _base, i64 _bit_size);
multi_return_int_strconv__PrepNumber strconv__parser(string s);
i64 strconv__pow5_bits(i64 e);
u32 strconv__pow5_factor_32(u32 i_v);
u32 strconv__pow5_factor_64(u64 v_i);
string strconv__remove_tail_zeros(string s);
string strconv__remove_tail_zeros_old(string s);
Optional_i64 strconv__safe_add_64bits(i64 a, i64 b);
Optional_i64 strconv__safe_mul10_64bits(i64 a);
u64 strconv__shift_right_128(strconv__Uint128 v, i64 shift);
multi_return_u32_u32_u32 strconv__sub96(u32 s2, u32 s1, u32 s0, u32 d2, u32 d1, u32 d0);
void strconv__v_printf(string str, Array pt);
string strconv__v_sprintf(string str, Array pt);
void strconv__v_sprintf_panic(i64 idx, i64 len);
i64 strconv__write_dec(i64 n, Array* buf);
i64 strconv__write_dec_u(u64 n, Array* buf);
void strconv__write_dec_u_digits(u64 n, Array* buf, i64 offset, i64 ndigits);
string string__after(string s, string sub);
string string__after_char(string s, u8 sub);
string string__all_after(string s, string sub);
string string__all_after_first(string s, string sub);
string string__all_after_last(string s, string sub);
string string__all_before(string s, string sub);
string string__all_before_last(string s, string sub);
u8 string__at(string s, i64 idx);
u8 string__at_i64(string s, i64 idx);
u8 string__at_ni(string s, i64 idx);
u8 string__at_u64(string s, u64 idx);
Optional_u8 string__at_with_check(string s, i64 idx);
Optional_u8 string__at_with_check_i64(string s, i64 idx);
Optional_u8 string__at_with_check_ni(string s, i64 idx);
Optional_u8 string__at_with_check_u64(string s, u64 idx);
string string__before(string s, string sub);
bool string__bool(string s);
Array string__bytes(string s);
string string__camel_to_snake(string s);
string string__capitalize(string s);
string string__clone(string a);
string string__clone_static(string a);
i64 string__compare(string s, string a);
bool string__contains(string s, string substr);
bool string__contains_any(string s, string chars);
bool string__contains_any_substr(string s, Array substrs);
bool string__contains_only(string s, string chars);
bool string__contains_u8(string s, u8 x);
i64 string__count(string s, string substr);
bool string__ends_with(string s, string p);
bool string__eq(string s, string a);
string string__expand_tabs(string s, i64 tab_len);
float string__f32(string s);
double string__f64(string s);
Array string__fields(string s);
string string__find_between(string s, string start, string end);
string string__format(string s, Array args);
void string__free(string* s);
Array string__graphemes(string s);
i64 string__hash(string s);
string string__hex(string s);
i16 string__i16(string s);
i32 string__i32(string s);
i64 string__i64(string s);
i8 string__i8(string s);
i64 string__indent_width(string s);
Optional_i64 string__index(string s, string p);
i64 string__index_(string s, string p);
Optional_i64 string__index_after(string s, string p, i64 start);
i64 string__index_after_(string s, string p, i64 start);
i64 string__index_any(string s, string chars);
i64 string__index_kmp(string s, string p);
i64 string__index_last_(string s, string p);
i64 string__index_u8(string s, u8 c);
i64 string__int(string s);
bool string__is_ascii(string s);
bool string__is_bin(string str);
bool string__is_blank(string s);
bool string__is_capital(string s);
bool string__is_hex(string str);
bool string__is_identifier(string s);
bool string__is_int(string str);
bool string__is_lower(string s);
bool string__is_oct(string str);
bool string__is_pure_ascii(string s);
bool string__is_title(string s);
bool string__is_upper(string s);
Optional_i64 string__last_index(string s, string needle);
i64 string__last_index_u8(string s, u8 c);
i64 string__len_utf8(string s);
string string__limit(string s, i64 max);
bool string__lt(string s, string a);
bool string__match_glob(string name, string pattern);
string string__normalize_tabs(string s, i64 tab_len);
Optional_string string__option_clone_static(string a);
Optional_i64 string__parse_int(string s, i64 _base, i64 _bit_size);
Optional_u64 string__parse_uint(string s, i64 _base, i64 _bit_size);
string string__plus(string s, string a);
string string__plus_two(string s, string a, string b);
string string__repeat(string s, i64 count);
string string__replace(string s, string rep, string with);
string string__replace_char(string s, u8 rep, u8 with, i64 repeat);
string string__replace_each(string s, Array vals);
string string__replace_once(string s, string rep, string with);
string string__reverse(string s);
Array string__rsplit(string s, string delim);
Array string__rsplit_any(string s, string delim);
Array string__rsplit_nth(string s, string delim, i64 nth);
Optional_multi_return_string_string string__rsplit_once(string s, string delim);
Array string__runes(string s);
RunesIterator string__runes_iterator(string s);
string string__snake_to_camel(string s);
Array string__split(string s, string delim);
Array string__split_any(string s, string delim);
Array string__split_by_space(string s);
Array string__split_into_lines(string s);
Array string__split_n(string s, string delim, i64 n);
Array string__split_nth(string s, string delim, i64 nth);
Optional_multi_return_string_string string__split_once(string s, string delim);
bool string__starts_with(string s, string p);
bool string__starts_with_capital(string s);
string string__str(string s);
string string__strip_margin(string s);
string string__strip_margin_custom(string s, u8 del);
string string__substr(string s, i64 start, i64 _end);
string string__substr_ni(string s, i64 _start, i64 _end);
string string__substr_or(string s, i64 start, i64 _end, string fallback);
string string__substr_unsafe(string s, i64 start, i64 _end);
Optional_string string__substr_with_check(string s, i64 start, i64 _end);
string string__title(string s);
string string__to_lower(string s);
string string__to_lower_ascii(string s);
string string__to_upper(string s);
string string__to_upper_ascii(string s);
u16* string__to_wide(string _str, ToWideConfig param);
string string__trim(string s, string cutset);
string string__trim_chars(string s, string cutset, int mode);
string string__trim_indent(string s);
multi_return_i64_i64 string__trim_indexes(string s, string cutset);
string string__trim_left(string s, string cutset);
string string__trim_right(string s, string cutset);
string string__trim_runes(string s, string cutset, int mode);
string string__trim_space(string s);
string string__trim_space_left(string s);
string string__trim_space_right(string s);
string string__trim_string_left(string s, string str);
string string__trim_string_right(string s, string str);
u16 string__u16(string s);
u32 string__u32(string s);
u64 string__u64(string s);
u8 string__u8(string s);
Array string__u8_array(string s);
string string__uncapitalize(string s);
i64 string__utf32_code(string _rune);
string string__wrap(string s, WrapConfig config);
string string_from_wide(u16* _wstr);
string string_from_wide2(u16* _wstr, i64 len);
Array string_graphemes_impl(string s);
string string_plus_many(i64 data_len, string* input_base);
Array string_to_ansi_not_null_terminated(string _str);
string strings__Builder__after(Array* b, i64 n);
u8 strings__Builder__byte_at(Array* b, i64 n);
string strings__Builder__cut_last(Array* b, i64 n);
string strings__Builder__cut_to(Array* b, i64 pos);
void strings__Builder__drain_builder(Array* b, Array* other, i64 other_new_cap);
void strings__Builder__ensure_cap(Array* b, i64 n);
void strings__Builder__free(Array* b);
void strings__Builder__go_back(Array* b, i64 n);
void strings__Builder__go_back_to(Array* b, i64 pos);
void strings__Builder__grow_len(Array* b, i64 n);
void strings__Builder__indent(Array* b, string s, strings__IndentParam param);
string strings__Builder__last_n(Array* b, i64 n);
Array strings__Builder__reuse_as_plain_u8_array(Array* b);
string strings__Builder__spart(Array* b, i64 start_pos, i64 n);
string strings__Builder__str(Array* b);
Optional_i64 strings__Builder__write(Array* b, Array data);
void strings__Builder__write_byte(Array* b, u8 data);
void strings__Builder__write_decimal(Array* b, i64 n);
void strings__Builder__write_ptr(Array* b, u8* ptr, i64 len);
void strings__Builder__write_repeated_rune(Array* b, u32 r, i64 count);
void strings__Builder__write_rune(Array* b, u32 r);
void strings__Builder__write_runes(Array* b, Array runes);
void strings__Builder__write_string(Array* b, string s);
void strings__Builder__write_string2(Array* b, string s1, string s2);
void strings__Builder__write_u8(Array* b, u8 data);
void strings__Builder__write_u_decimal(Array* b, u64 n);
void strings__Builder__writeln(Array* b, string s);
void strings__Builder__writeln2(Array* b, string s1, string s2);
i64 strings__abs2(i64 a, i64 b);
float strings__dice_coefficient(string s1, string s2);
string strings__find_between_pair_rune(string input, u32 start, u32 end);
string strings__find_between_pair_string(string input, string start, string end);
string strings__find_between_pair_u8(string input, u8 start, u8 end);
i64 strings__hamming_distance(string a, string b);
float strings__hamming_similarity(string a, string b);
double strings__jaro_similarity(string a, string b);
double strings__jaro_winkler_similarity(string a, string b);
i64 strings__levenshtein_distance(string a, string b);
float strings__levenshtein_distance_percentage(string a, string b);
i64 strings__max2(i64 a, i64 b);
i64 strings__min(i64 a, i64 b, i64 c);
i64 strings__min2(i64 a, i64 b);
Array strings__new_builder(i64 initial_size);
string strings__repeat(u8 c, i64 n);
string strings__repeat_string(string s, i64 n);
Array strings__split_capital(string s);
string tos(u8* s, i64 len);
string tos2(u8* s);
string tos3(char* s);
string tos4(u8* s);
string tos5(char* s);
string tos_clone(u8* const_s);
void trace_error(string x);
string u16__hex(u16 nn);
string u16__hex_full(u16 nn);
string u16__str(u16 n);
string u32__hex(u32 nn);
string u32__hex_full(u32 nn);
string u32__str(u32 nn);
string u64__hex(u64 nn);
string u64__hex_full(u64 nn);
string u64__str(u64 nn);
string u64_to_hex(u64 nn, u8 len);
string u64_to_hex_no_leading_zeros(u64 nn, u8 len);
string u8__ascii_str(u8 b);
void u8__free(u8* data);
string u8__hex(u8 nn);
string u8__hex_full(u8 nn);
bool u8__is_alnum(u8 c);
bool u8__is_bin_digit(u8 c);
bool u8__is_capital(u8 c);
bool u8__is_digit(u8 c);
bool u8__is_hex_digit(u8 c);
bool u8__is_letter(u8 c);
bool u8__is_oct_digit(u8 c);
bool u8__is_space(u8 c);
string u8__repeat(u8 b, i64 count);
string u8__str(u8 b);
string u8__str_escaped(u8 b);
string u8__vstring(u8* bp);
string u8__vstring_literal(u8* bp);
string u8__vstring_literal_with_len(u8* bp, i64 len);
string u8__vstring_with_len(u8* bp, i64 len);
void unbuffer_stdout(void);
string usize__str(size_t x);
i64 utf32_decode_to_buffer(u32 code, u8** buf);
string utf32_to_str(u32 code);
string utf32_to_str_no_malloc(u32 code, u8** buf);
i64 utf8_char_len(u8 b);
multi_return_u32_i64 utf8_decode_rune(u8* _bytes, i64 available_len);
i64 utf8_grapheme_visible_length(string s);
bool utf8_is_continuation(u8 b);
i64 utf8_rune_visible_width(u32 r, int prop);
i64 utf8_str_visible_length(string s);
void v_exit(i64 code);
i64 v_fixed_index(i64 i, i64 len);
i64 v_fixed_index_i64(i64 i, i64 len);
i64 v_fixed_index_ni(i64 i, i64 len);
i64 v_fixed_index_u64(u64 i, i64 len);
void v_free(void* ptr);
u64 v_getpid(void);
u64 v_gettid(void);
u8* v_malloc(ptrdiff_t n);
i64 v_ni_index(i64 i, i64 len);
void v_panic(string s);
u8* v_realloc(u8* b, ptrdiff_t n);
void v_segmentation_fault_handler(i32 signal_number);
i64 v_slice_index_i64(i64 i);
i64 v_slice_index_u64(u64 i);
u8* vcalloc(ptrdiff_t n);
u8* vcalloc_noscan(ptrdiff_t n);
string vcurrent_hash(void);
void* vgc_calloc(size_t n);
void vgc_free(void* ptr);
multi_return_size_t_size_t_size_t_size_t_size_t vgc_heap_usage(void);
void* vgc_malloc(size_t n);
void* vgc_malloc_noscan(size_t n);
void* vgc_malloc_noscan_opts(size_t n, bool zero_fill);
void* vgc_malloc_typed_opts(size_t n, u64 ptrmap, u8 ptr_words, bool zero_fill);
void* vgc_memdup(void* src, ptrdiff_t n);
void* vgc_memdup_noscan(void* src, ptrdiff_t n);
size_t vgc_memory_use(void);
void* vgc_realloc(void* old_ptr, size_t new_size);
i64 vmemcmp(void* const_s1, void* const_s2, ptrdiff_t n);
void* vmemcpy(void* dest, void* const_src, ptrdiff_t n);
void* vmemmove(void* dest, void* const_src, ptrdiff_t n);
void vmemory_abort_on_nil(void* p, ptrdiff_t bytes);
u8* vmemory_align_up(u8* ptr, ptrdiff_t align);
VMemoryBlock* vmemory_block_current_or_new(void);
void vmemory_block_free(VMemoryBlock* mb);
void vmemory_block_free_after(VMemoryBlock* marker);
void vmemory_block_free_chain(VMemoryBlock* first);
u8* vmemory_block_malloc(ptrdiff_t n, ptrdiff_t align);
VMemoryBlock* vmemory_block_new(VMemoryBlock* prev, ptrdiff_t at_least, ptrdiff_t align);
VMemoryBlock* vmemory_block_new_sized(VMemoryBlock* prev, ptrdiff_t at_least, ptrdiff_t align, ptrdiff_t min_block_size);
i64 vmemory_block_size(VMemoryBlock* mb);
i64 vmemory_block_used(VMemoryBlock* mb);
ptrdiff_t vmemory_effective_align(ptrdiff_t align);
void* vmemset(void* s, i64 c, ptrdiff_t n);
string voidptr__hex_full(void* nn);
string voidptr__str(void* nn);
Array voidptr__vbytes(void* data, i64 len);
void vqsort(void* base, size_t nmemb, size_t size, _fn_ptr_ed95774d3a4e97ab sort_cb);
void* vsort_ptr_at(void* base, size_t v_index, size_t size);
void vstable_sort_merge(void* source, void* dest, size_t left, size_t mid, size_t right, size_t size, _fn_ptr_ed95774d3a4e97ab sort_cb);
i64 vstrlen(u8* s);
i64 vstrlen_char(char* s);
Array wide_to_ansi(u16* _wstr);
bool write_buf_to_console(i64 fd, u8* buf, i64 buf_len);
bool write_buf_to_fd_kernel32(i64 fd, u8* buf, i64 buf_len);
void write_buf_to_fd_kernel32_or_exit(i64 fd, u8* buf, i64 buf_len);
void write_buf_to_fd_windows_non_minimal(i64 fd, u8* buf, i64 buf_len);
string wtf8_from_wide(u16* value, i64 len);
u16* wtf8_to_wide(string value);

string IError__msg(IError* i);
string Error__msg(Error _recv);
string MessageError__msg(MessageError _recv);
i64 IError__code(IError* i);
i64 Error__code(Error _recv);
i64 MessageError__code(MessageError _recv);
Array hash__Hash__sum(hash__Hash* i, Array _a0);
i64 hash__Hash__size(hash__Hash* i);
i64 hash__Hash__block_size(hash__Hash* i);
void hash__Hash__free(hash__Hash* i);
void hash__Hash__reset(hash__Hash* i);
Optional_i64 hash__Hash__write(hash__Hash* i, Array _a0);
u32 hash__Hash32er__sum32(hash__Hash32er* i);
u64 hash__Hash64er__sum64(hash__Hash64er* i);

static const string _v3_lit_0_14650fb0739d0383 = {"", 0, 1};
static const string _v3_lit_1_44bd31d473cd01cb = {"\n", 1, 1};
static const string _v3_lit_18_c76639494a2ef036 = {" }, 0, 0, 0},{_S(\"", 18, 1};
static const string _v3_lit_15_c23d46ff12b6690c = {" }, 0, 0, 0}}))", 15, 1};
static const string _v3_lit_4_42ca449b60800bd2 = {"\"), ", 4, 1};
static const string _v3_lit_23_3741aa05dc09a04c = {"\"), 0, {0}, 0, 0, 0}}))", 23, 1};
static const string _v3_lit_64_a9cee17b2bafb334 = {"% conversion specifiers number mismatch (expected %, given args)", 64, 1};
static const string _v3_lit_2_9ae02a00c5ae0675 = {"%%", 2, 1};
static const string _v3_lit_12_77dde251e7b557a0 = {"***ERROR!***", 12, 1};
static const string _v3_lit_1_44bd50d473cd3678 = {"+", 1, 1};
static const string _v3_lit_4_e8d6bcd39f7348a3 = {"+INF", 4, 1};
static const string _v3_lit_4_d33abcd302174483 = {"+inf", 4, 1};
static const string _v3_lit_2_9afebb00c5c7fa67 = {", ", 2, 1};
static const string _v3_lit_10_acdfc69f923b1745 = {", {.d_s = ", 10, 1};
static const string _v3_lit_1_44bd56d473cd40aa = {"-", 1, 1};
static const string _v3_lit_2_9afb2500c5c4c5ae = {"-0", 2, 1};
static const string _v3_lit_4_fefe81081a03fee9 = {"-INF", 4, 1};
static const string _v3_lit_4_e88841077bedea49 = {"-inf", 4, 1};
static const string _v3_lit_1_44bd5bd473cd4929 = {"0", 1, 1};
static const string _v3_lit_416_816732e56ffe16ec = {"00000000090000000b0000000c0000000e0000001f0000007f0000009f000000ad000000ad0000001c0600001c0600000e1800000e1800000b2000000b2000000e2000000f200000282000002820000029200000292000002a2000002e20000060200000642000006520000065200000662000006f200000fffe0000fffe0000f0ff0000f8ff0000f9ff0000fbff00003034010038340100a0bc0100a3bc010073d101007ad1010000000e0000000e0001000e0001000e0002000e001f000e0080000e00ff000e00f0010e00ff0f0e00", 416, 1};
static const string _v3_lit_3072_29c376e9b95f4fd8 = {"000300006f0300008304000087040000880400008904000091050000bd050000bf050000bf050000c1050000c2050000c4050000c5050000c7050000c7050000100600001a0600004b0600005f0600007006000070060000d6060000dc060000df060000e4060000e7060000e8060000ea060000ed0600001107000011070000300700004a070000a6070000b0070000eb070000f3070000fd070000fd07000016080000190800001b080000230800002508000027080000290800002d080000590800005b080000d3080000e1080000e3080000020900003a0900003a0900003c0900003c09000041090000480900004d0900004d090000510900005709000062090000630900008109000081090000bc090000bc090000be090000be090000c1090000c4090000cd090000cd090000d7090000d7090000e2090000e3090000fe090000fe090000010a0000020a00003c0a00003c0a0000410a0000420a0000470a0000480a00004b0a00004d0a0000510a0000510a0000700a0000710a0000750a0000750a0000810a0000820a0000bc0a0000bc0a0000c10a0000c50a0000c70a0000c80a0000cd0a0000cd0a0000e20a0000e30a0000fa0a0000ff0a0000010b0000010b00003c0b00003c0b00003e0b00003e0b00003f0b00003f0b0000410b0000440b00004d0b00004d0b0000550b0000560b0000570b0000570b0000620b0000630b0000820b0000820b0000be0b0000be0b0000c00b0000c00b0000cd0b0000cd0b0000d70b0000d70b0000000c0000000c0000040c0000040c00003e0c0000400c0000460c0000480c00004a0c00004d0c0000550c0000560c0000620c0000630c0000810c0000810c0000bc0c0000bc0c0000bf0c0000bf0c0000c20c0000c20c0000c60c0000c60c0000cc0c0000cd0c0000d50c0000d60c0000e20c0000e30c0000000d0000010d00003b0d00003c0d00003e0d00003e0d0000410d0000440d00004d0d00004d0d0000570d0000570d0000620d0000630d0000810d0000810d0000ca0d0000ca0d0000cf0d0000cf0d0000d20d0000d40d0000d60d0000d60d0000df0d0000df0d0000310e0000310e0000340e00003a0e0000470e00004e0e0000b10e0000b10e0000b40e0000bc0e0000c80e0000cd0e0000180f0000190f0000350f0000350f0000370f0000370f0000390f0000390f0000710f00007e0f0000800f0000840f0000860f0000870f00008d0f0000970f0000990f0000bc0f0000c60f0000c60f00002d100000301000003210000037100000391000003a1000003d1000003e10000058100000591000005e100000601000007110000074100000821000008210000085100000861000008d1000008d1000009d1000009d1000005d1300005f1300001217000014170000321700003417000052170000531700007217000073170000b4170000b5170000b7170000bd170000c6170000c6170000c9170000d3170000dd170000dd1700000b1800000d1800008518000086180000a9180000a9180000201900002219000027190000281900003219000032190000391900003b190000171a0000181a00001b1a00001b1a0000561a0000561a0000581a00005e1a0000601a0000601a0000621a0000621a0000651a00006c1a0000731a00007c1a00007f1a00007f1a0000b01a0000bd1a0000be1a0000be1a0000bf1a0000c01a0000001b0000031b0000341b0000341b0000351b0000351b0000361b00003a1b00003c1b00003c1b0000421b0000421b00006b1b0000731b0000801b0000811b0000a21b0000a51b0000a81b0000a91b0000ab1b0000ad1b0000e61b0000e61b0000e81b0000e91b0000ed1b0000ed1b0000ef1b0000f11b00002c1c0000331c0000361c0000371c0000d01c0000d21c0000d41c0000e01c0000e21c0000e81c0000ed1c0000ed1c0000f41c0000f41c0000f81c0000f91c0000c01d0000f91d0000fb1d0000ff1d00000c2000000c200000d0200000dc200000dd200000e0200000e1200000e1200000e2200000e4200000e5200000f0200000ef2c0000f12c00007f2d00007f2d0000e02d0000ff2d00002a3000002d3000002e3000002f300000993000009a3000006fa600006fa60000", 3072, 1};
static const string _v3_lit_5728_1d08d12712a95cef = {"000300006f0300008304000087040000880400008904000091050000bd050000bf050000bf050000c1050000c2050000c4050000c5050000c7050000c7050000100600001a0600004b0600005f0600007006000070060000d6060000dc060000df060000e4060000e7060000e8060000ea060000ed0600001107000011070000300700004a070000a6070000b0070000eb070000f3070000fd070000fd07000016080000190800001b080000230800002508000027080000290800002d080000590800005b080000d3080000e1080000e3080000020900003a0900003a0900003c0900003c09000041090000480900004d0900004d090000510900005709000062090000630900008109000081090000bc090000bc090000be090000be090000c1090000c4090000cd090000cd090000d7090000d7090000e2090000e3090000fe090000fe090000010a0000020a00003c0a00003c0a0000410a0000420a0000470a0000480a00004b0a00004d0a0000510a0000510a0000700a0000710a0000750a0000750a0000810a0000820a0000bc0a0000bc0a0000c10a0000c50a0000c70a0000c80a0000cd0a0000cd0a0000e20a0000e30a0000fa0a0000ff0a0000010b0000010b00003c0b00003c0b00003e0b00003e0b00003f0b00003f0b0000410b0000440b00004d0b00004d0b0000550b0000560b0000570b0000570b0000620b0000630b0000820b0000820b0000be0b0000be0b0000c00b0000c00b0000cd0b0000cd0b0000d70b0000d70b0000000c0000000c0000040c0000040c00003e0c0000400c0000460c0000480c00004a0c00004d0c0000550c0000560c0000620c0000630c0000810c0000810c0000bc0c0000bc0c0000bf0c0000bf0c0000c20c0000c20c0000c60c0000c60c0000cc0c0000cd0c0000d50c0000d60c0000e20c0000e30c0000000d0000010d00003b0d00003c0d00003e0d00003e0d0000410d0000440d00004d0d00004d0d0000570d0000570d0000620d0000630d0000810d0000810d0000ca0d0000ca0d0000cf0d0000cf0d0000d20d0000d40d0000d60d0000d60d0000df0d0000df0d0000310e0000310e0000340e00003a0e0000470e00004e0e0000b10e0000b10e0000b40e0000bc0e0000c80e0000cd0e0000180f0000190f0000350f0000350f0000370f0000370f0000390f0000390f0000710f00007e0f0000800f0000840f0000860f0000870f00008d0f0000970f0000990f0000bc0f0000c60f0000c60f00002d100000301000003210000037100000391000003a1000003d1000003e10000058100000591000005e100000601000007110000074100000821000008210000085100000861000008d1000008d1000009d1000009d1000005d1300005f1300001217000014170000321700003417000052170000531700007217000073170000b4170000b5170000b7170000bd170000c6170000c6170000c9170000d3170000dd170000dd1700000b1800000d1800008518000086180000a9180000a9180000201900002219000027190000281900003219000032190000391900003b190000171a0000181a00001b1a00001b1a0000561a0000561a0000581a00005e1a0000601a0000601a0000621a0000621a0000651a00006c1a0000731a00007c1a00007f1a00007f1a0000b01a0000bd1a0000be1a0000be1a0000bf1a0000c01a0000001b0000031b0000341b0000341b0000351b0000351b0000361b00003a1b00003c1b00003c1b0000421b0000421b00006b1b0000731b0000801b0000811b0000a21b0000a51b0000a81b0000a91b0000ab1b0000ad1b0000e61b0000e61b0000e81b0000e91b0000ed1b0000ed1b0000ef1b0000f11b00002c1c0000331c0000361c0000371c0000d01c0000d21c0000d41c0000e01c0000e21c0000e81c0000ed1c0000ed1c0000f41c0000f41c0000f81c0000f91c0000c01d0000f91d0000fb1d0000ff1d00000c2000000c200000d0200000dc200000dd200000e0200000e1200000e1200000e2200000e4200000e5200000f0200000ef2c0000f12c00007f2d00007f2d0000e02d0000ff2d00002a3000002d3000002e3000002f300000993000009a3000006fa600006fa6000070a6000072a6000074a600007da600009ea600009fa60000f0a60000f1a6000002a8000002a8000006a8000006a800000ba800000ba8000025a8000026a800002ca800002ca80000c4a80000c5a80000e0a80000f1a80000ffa80000ffa8000026a900002da9000047a9000051a9000080a9000082a90000b3a90000b3a90000b6a90000b9a90000bca90000bda90000e5a90000e5a9000029aa00002eaa000031aa000032aa000035aa000036aa000043aa000043aa00004caa00004caa00007caa00007caa0000b0aa0000b0aa0000b2aa0000b4aa0000b7aa0000b8aa0000beaa0000bfaa0000c1aa0000c1aa0000ecaa0000edaa0000f6aa0000f6aa0000e5ab0000e5ab0000e8ab0000e8ab0000edab0000edab00001efb00001efb000000fe00000ffe000020fe00002ffe00009eff00009fff0000fd010100fd010100e0020100e0020100760301007a030100010a0100030a0100050a0100060a01000c0a01000f0a0100380a01003a0a01003f0a01003f0a0100e50a0100e60a0100240d0100270d0100ab0e0100ac0e0100460f0100500f0100011001000110010038100100461001007f10010081100100b3100100b6100100b9100100ba1001000011010002110100271101002b1101002d1101003411010073110100731101008011010081110100b6110100be110100c9110100cc110100cf110100cf1101002f12010031120100341201003412010036120100371201003e1201003e120100df120100df120100e3120100ea12010000130100011301003b1301003c1301003e1301003e13010040130100401301005713010057130100661301006c1301007013010074130100381401003f140100421401004414010046140100461401005e1401005e140100b0140100b0140100b3140100b8140100ba140100ba140100bd140100bd140100bf140100c0140100c2140100c3140100af150100af150100b2150100b5150100bc150100bd150100bf150100c0150100dc150100dd150100331601003a1601003d1601003d1601003f16010040160100ab160100ab160100ad160100ad160100b0160100b5160100b7160100b71601001d1701001f1701002217010025170100271701002b1701002f18010037180100391801003a18010030190100301901003b1901003c1901003e1901003e1901004319010043190100d4190100d7190100da190100db190100e0190100e0190100011a01000a1a0100331a0100381a01003b1a01003e1a0100471a0100471a0100511a0100561a0100591a01005b1a01008a1a0100961a0100981a0100991a0100301c0100361c0100381c01003d1c01003f1c01003f1c0100921c0100a71c0100aa1c0100b01c0100b21c0100b31c0100b51c0100b61c0100311d0100361d01003a1d01003a1d01003c1d01003d1d01003f1d0100451d0100471d0100471d0100901d0100911d0100951d0100951d0100971d0100971d0100f31e0100f41e0100f06a0100f46a0100306b0100366b01004f6f01004f6f01008f6f0100926f0100e46f0100e46f01009dbc01009ebc010065d1010065d1010067d1010069d101006ed1010072d101007bd1010082d1010085d101008bd10100aad10100add1010042d2010044d2010000da010036da01003bda01006cda010075da010075da010084da010084da01009bda01009fda0100a1da0100afda010000e0010006e0010008e0010018e001001be0010021e0010023e0010024e0010026e001002ae0010030e1010036e10100ece20100efe20100d0e80100d6e8010044e901004ae90100fbf30100fff3010020000e007f000e0000010e00ef010e00", 5728, 1};
static const string _v3_lit_208_8adb69c5acbfab70 = {"0006000005060000dd060000dd0600000f0700000f070000e2080000e20800004e0d00004e0d0000bd100100bd100100cd100100cd100100c2110100c31101003f1901003f19010041190100411901003a1a01003a1a0100841a0100891a0100461d0100461d0100", 208, 1};
static const string _v3_lit_200_af696b582994c7c7 = {"00102030405060708090011121314151617181910212223242526272829203132333435363738393041424344454647484940515253545556575859506162636465666768696071727374757677787970818283848586878889809192939495969798999", 200, 1};
static const string _v3_lit_36_4a3292e485d00bc3 = {"0123456789abcdefghijklmnopqrstuvwxyz", 36, 1};
static const string _v3_lit_2544_7b580310d2f36df = {"03090000030900003b0900003b0900003e09000040090000490900004c0900004e0900004f0900008209000083090000bf090000c0090000c7090000c8090000cb090000cc090000030a0000030a00003e0a0000400a0000830a0000830a0000be0a0000c00a0000c90a0000c90a0000cb0a0000cc0a0000020b0000030b0000400b0000400b0000470b0000480b00004b0b00004c0b0000bf0b0000bf0b0000c10b0000c20b0000c60b0000c80b0000ca0b0000cc0b0000010c0000030c0000410c0000440c0000820c0000830c0000be0c0000be0c0000c00c0000c10c0000c30c0000c40c0000c70c0000c80c0000ca0c0000cb0c0000020d0000030d00003f0d0000400d0000460d0000480d00004a0d00004c0d0000820d0000830d0000d00d0000d10d0000d80d0000de0d0000f20d0000f30d0000330e0000330e0000b30e0000b30e00003e0f00003f0f00007f0f00007f0f000031100000311000003b1000003c10000056100000571000008410000084100000b6170000b6170000be170000c5170000c7170000c81700002319000026190000291900002b19000030190000311900003319000038190000191a00001a1a0000551a0000551a0000571a0000571a00006d1a0000721a0000041b0000041b00003b1b00003b1b00003d1b0000411b0000431b0000441b0000821b0000821b0000a11b0000a11b0000a61b0000a71b0000aa1b0000aa1b0000e71b0000e71b0000ea1b0000ec1b0000ee1b0000ee1b0000f21b0000f31b0000241c00002b1c0000341c0000351c0000e11c0000e11c0000f71c0000f71c000023a8000024a8000027a8000027a8000080a8000081a80000b4a80000c3a8000052a9000053a9000083a9000083a90000b4a90000b5a90000baa90000bba90000bea90000c0a900002faa000030aa000033aa000034aa00004daa00004daa0000ebaa0000ebaa0000eeaa0000efaa0000f5aa0000f5aa0000e3ab0000e4ab0000e6ab0000e7ab0000e9ab0000eaab0000ecab0000ecab0000001001000010010002100100021001008210010082100100b0100100b2100100b7100100b81001002c1101002c11010045110100461101008211010082110100b3110100b5110100bf110100c0110100ce110100ce1101002c1201002e12010032120100331201003512010035120100e0120100e212010002130100031301003f1301003f130100411301004413010047130100481301004b1301004d1301006213010063130100351401003714010040140100411401004514010045140100b1140100b2140100b9140100b9140100bb140100bc140100be140100be140100c1140100c1140100b0150100b1150100b8150100bb150100be150100be15010030160100321601003b1601003c1601003e1601003e160100ac160100ac160100ae160100af160100b6160100b6160100201701002117010026170100261701002c1801002e1801003818010038180100311901003519010037190100381901003d1901003d19010040190100401901004219010042190100d1190100d3190100dc190100df190100e4190100e4190100391a0100391a0100571a0100581a0100971a0100971a01002f1c01002f1c01003e1c01003e1c0100a91c0100a91c0100b11c0100b11c0100b41c0100b41c01008a1d01008e1d0100931d0100941d0100961d0100961d0100f51e0100f61e0100516f0100876f0100f06f0100f16f010066d1010066d101006dd101006dd10100", 2544, 1};
static const string _v3_lit_2_9b0c5b00c5d394a3 = {"0x", 2, 1};
static const string _v3_lit_6_e20ee5a7ed2ad7ed = {"0xfe0e", 6, 1};
static const string _v3_lit_6_e20ee2a7ed2ad2d4 = {"0xfe0f", 6, 1};
static const string _v3_lit_6_e21216a7ed2d6107 = {"0xfe10", 6, 1};
static const string _v3_lit_3072_ebdd93c2e961fa3e = {"21f3010021f3010022f3010023f3010024f301002cf301002df301002ff3010030f3010031f3010032f3010033f3010034f3010035f3010036f3010036f3010037f301004af301004bf301004bf301004cf301004ff3010050f3010050f3010051f301007bf301007cf301007cf301007df301007df301007ef301007ff3010080f3010093f3010094f3010095f3010096f3010097f3010098f3010098f3010099f301009bf301009cf301009df301009ef301009ff30100a0f30100c4f30100c5f30100c5f30100c6f30100c6f30100c7f30100c7f30100c8f30100c8f30100c9f30100c9f30100caf30100caf30100cbf30100cef30100cff30100d3f30100d4f30100dff30100e0f30100e3f30100e4f30100e4f30100e5f30100f0f30100f1f30100f2f30100f3f30100f3f30100f4f30100f4f30100f5f30100f5f30100f6f30100f6f30100f7f30100f7f30100f8f30100faf3010000f4010007f4010008f4010008f4010009f401000bf401000cf401000ef401000ff4010010f4010011f4010012f4010013f4010013f4010014f4010014f4010015f4010015f4010016f4010016f4010017f4010029f401002af401002af401002bf401003ef401003ff401003ff4010040f4010040f4010041f4010041f4010042f4010064f4010065f4010065f4010066f401006bf401006cf401006df401006ef40100acf40100adf40100adf40100aef40100b5f40100b6f40100b7f40100b8f40100ebf40100ecf40100edf40100eef40100eef40100eff40100eff40100f0f40100f4f40100f5f40100f5f40100f6f40100f7f40100f8f40100f8f40100f9f40100fcf40100fdf40100fdf40100fef40100fef40100fff4010002f5010003f5010003f5010004f5010007f5010008f5010008f5010009f5010009f501000af5010014f5010015f5010015f5010016f501002bf501002cf501002df501002ef501003df5010046f5010048f5010049f501004af501004bf501004ef501004ff501004ff5010050f501005bf501005cf5010067f5010068f501006ef501006ff5010070f5010071f5010072f5010073f5010079f501007af501007af501007bf5010086f5010087f5010087f5010088f5010089f501008af501008df501008ef501008ff5010090f5010090f5010091f5010094f5010095f5010096f5010097f50100a3f50100a4f50100a4f50100a5f50100a5f50100a6f50100a7f50100a8f50100a8f50100a9f50100b0f50100b1f50100b2f50100b3f50100bbf50100bcf50100bcf50100bdf50100c1f50100c2f50100c4f50100c5f50100d0f50100d1f50100d3f50100d4f50100dbf50100dcf50100def50100dff50100e0f50100e1f50100e1f50100e2f50100e2f50100e3f50100e3f50100e4f50100e7f50100e8f50100e8f50100e9f50100eef50100eff50100eff50100f0f50100f2f50100f3f50100f3f50100f4f50100f9f50100faf50100faf50100fbf50100fff5010000f6010000f6010001f6010006f6010007f6010008f6010009f601000df601000ef601000ef601000ff601000ff6010010f6010010f6010011f6010011f6010012f6010014f6010015f6010015f6010016f6010016f6010017f6010017f6010018f6010018f6010019f6010019f601001af601001af601001bf601001bf601001cf601001ef601001ff601001ff6010020f6010025f6010026f6010027f6010028f601002bf601002cf601002cf601002df601002df601002ef601002ff6010030f6010033f6010034f6010034f6010035f6010035f6010036f6010036f6010037f6010040f6010041f6010044f6010045f601004ff6010080f6010080f6010081f6010082f6010083f6010085f6010086f6010086f6010087f6010087f6010088f6010088f6010089f6010089f601008af601008bf601008cf601008cf601008df601008df601008ef601008ef601008ff601008ff6010090f6010090f6010091f6010093f6010094f6010094f6010095f6010095f6010096f6010096f6010097f6010097f6010098f6010098f6010099f601009af601009bf60100a1f60100a2f60100a2f60100a3f60100a3f60100a4f60100a5f60100a6f60100a6f60100a7f60100adf60100", 3072, 1};
static const string _v3_lit_2656_a0151aeea66cf5b4 = {"70a6000072a6000074a600007da600009ea600009fa60000f0a60000f1a6000002a8000002a8000006a8000006a800000ba800000ba8000025a8000026a800002ca800002ca80000c4a80000c5a80000e0a80000f1a80000ffa80000ffa8000026a900002da9000047a9000051a9000080a9000082a90000b3a90000b3a90000b6a90000b9a90000bca90000bda90000e5a90000e5a9000029aa00002eaa000031aa000032aa000035aa000036aa000043aa000043aa00004caa00004caa00007caa00007caa0000b0aa0000b0aa0000b2aa0000b4aa0000b7aa0000b8aa0000beaa0000bfaa0000c1aa0000c1aa0000ecaa0000edaa0000f6aa0000f6aa0000e5ab0000e5ab0000e8ab0000e8ab0000edab0000edab00001efb00001efb000000fe00000ffe000020fe00002ffe00009eff00009fff0000fd010100fd010100e0020100e0020100760301007a030100010a0100030a0100050a0100060a01000c0a01000f0a0100380a01003a0a01003f0a01003f0a0100e50a0100e60a0100240d0100270d0100ab0e0100ac0e0100460f0100500f0100011001000110010038100100461001007f10010081100100b3100100b6100100b9100100ba1001000011010002110100271101002b1101002d1101003411010073110100731101008011010081110100b6110100be110100c9110100cc110100cf110100cf1101002f12010031120100341201003412010036120100371201003e1201003e120100df120100df120100e3120100ea12010000130100011301003b1301003c1301003e1301003e13010040130100401301005713010057130100661301006c1301007013010074130100381401003f140100421401004414010046140100461401005e1401005e140100b0140100b0140100b3140100b8140100ba140100ba140100bd140100bd140100bf140100c0140100c2140100c3140100af150100af150100b2150100b5150100bc150100bd150100bf150100c0150100dc150100dd150100331601003a1601003d1601003d1601003f16010040160100ab160100ab160100ad160100ad160100b0160100b5160100b7160100b71601001d1701001f1701002217010025170100271701002b1701002f18010037180100391801003a18010030190100301901003b1901003c1901003e1901003e1901004319010043190100d4190100d7190100da190100db190100e0190100e0190100011a01000a1a0100331a0100381a01003b1a01003e1a0100471a0100471a0100511a0100561a0100591a01005b1a01008a1a0100961a0100981a0100991a0100301c0100361c0100381c01003d1c01003f1c01003f1c0100921c0100a71c0100aa1c0100b01c0100b21c0100b31c0100b51c0100b61c0100311d0100361d01003a1d01003a1d01003c1d01003d1d01003f1d0100451d0100471d0100471d0100901d0100911d0100951d0100951d0100971d0100971d0100f31e0100f41e0100f06a0100f46a0100306b0100366b01004f6f01004f6f01008f6f0100926f0100e46f0100e46f01009dbc01009ebc010065d1010065d1010067d1010069d101006ed1010072d101007bd1010082d1010085d101008bd10100aad10100add1010042d2010044d2010000da010036da01003bda01006cda010075da010075da010084da010084da01009bda01009fda0100a1da0100afda010000e0010006e0010008e0010018e001001be0010021e0010023e0010024e0010026e001002ae0010030e1010036e10100ece20100efe20100d0e80100d6e8010044e901004ae90100fbf30100fff3010020000e007f000e0000010e00ef010e00", 2656, 1};
static const string _v3_lit_20_5531c37e223a4eed = {"Divide by Zero Error", 20, 1};
static const string _v3_lit_24_f4bba39b2c23a7d0 = {"Hello, World! from VLang", 24, 1};
static const string _v3_lit_37_88d8f63cec77379d = {"No string interpolation %% parameters", 37, 1};
static const string _v3_lit_14_5f5997e332de83fb = {"Overflow Error", 14, 1};
static const string _v3_lit_26_c6d3361bedf33505 = {"[Float conversion error!!]", 26, 1};
static const string _v3_lit_4_acac2dc1b2d6a927 = {"`\\0`", 4, 1};
static const string _v3_lit_4_adb927c1b3bb9c4e = {"`\\a`", 4, 1};
static const string _v3_lit_4_adb501c1b3b772e5 = {"`\\b`", 4, 1};
static const string _v3_lit_4_adab0fc1b3af362a = {"`\\e`", 4, 1};
static const string _v3_lit_4_ada829c1b3ad2c81 = {"`\\f`", 4, 1};
static const string _v3_lit_4_ad8cf9c1b3961339 = {"`\\n`", 4, 1};
static const string _v3_lit_4_ad7f21c1b38a19d5 = {"`\\r`", 4, 1};
static const string _v3_lit_4_ad7815c1b383e6c3 = {"`\\t`", 4, 1};
static const string _v3_lit_4_ad7109c1b37db3b1 = {"`\\v`", 4, 1};
static const string _v3_lit_3072_70027c1664ad55b = {"a9000000a9000000ae000000ae0000003c2000003c2000004920000049200000222100002221000039210000392100009421000099210000a9210000aa2100001a2300001b23000028230000282300008823000088230000cf230000cf230000e9230000ec230000ed230000ee230000ef230000ef230000f0230000f0230000f1230000f2230000f3230000f3230000f8230000fa230000c2240000c2240000aa250000ab250000b6250000b6250000c0250000c0250000fb250000fe2500000026000001260000022600000326000004260000042600000526000005260000072600000d2600000e2600000e2600000f2600001026000011260000112600001226000012260000142600001526000016260000172600001826000018260000192600001c2600001d2600001d2600001e2600001f2600002026000020260000212600002126000022260000232600002426000025260000262600002626000027260000292600002a2600002a2600002b2600002d2600002e2600002e2600002f2600002f260000302600003726000038260000392600003a2600003a2600003b2600003f26000040260000402600004126000041260000422600004226000043260000472600004826000053260000542600005e2600005f2600005f2600006026000060260000612600006226000063260000632600006426000064260000652600006626000067260000672600006826000068260000692600007a2600007b2600007b2600007c2600007d2600007e2600007e2600007f2600007f2600008026000085260000902600009126000092260000922600009326000093260000942600009426000095260000952600009626000097260000982600009826000099260000992600009a2600009a2600009b2600009c2600009d2600009f260000a0260000a1260000a2260000a6260000a7260000a7260000a8260000a9260000aa260000ab260000ac260000af260000b0260000b1260000b2260000bc260000bd260000be260000bf260000c3260000c4260000c5260000c6260000c7260000c8260000c8260000c9260000cd260000ce260000ce260000cf260000cf260000d0260000d0260000d1260000d1260000d2260000d2260000d3260000d3260000d4260000d4260000d5260000e8260000e9260000e9260000ea260000ea260000eb260000ef260000f0260000f1260000f2260000f3260000f4260000f4260000f5260000f5260000f6260000f6260000f7260000f9260000fa260000fa260000fb260000fc260000fd260000fd260000fe26000001270000022700000227000003270000042700000527000005270000082700000c2700000d2700000d2700000e2700000e2700000f2700000f27000010270000112700001227000012270000142700001427000016270000162700001d2700001d270000212700002127000028270000282700003327000034270000442700004427000047270000472700004c2700004c2700004e2700004e270000532700005527000057270000572700006327000063270000642700006427000065270000672700009527000097270000a1270000a1270000b0270000b0270000bf270000bf2700003429000035290000052b0000072b00001b2b00001c2b0000502b0000502b0000552b0000552b000030300000303000003d3000003d3000009732000097320000993200009932000000f0010003f0010004f0010004f0010005f00100cef00100cff00100cff00100d0f00100fff001000df101000ff101002ff101002ff101006cf101006ff1010070f1010071f101007ef101007ff101008ef101008ef1010091f101009af10100adf10100e5f1010001f2010002f2010003f201000ff201001af201001af201002ff201002ff2010032f201003af201003cf201003ff2010049f201004ff2010050f2010051f2010052f20100fff2010000f301000cf301000df301000ef301000ff301000ff3010010f3010010f3010011f3010011f3010012f3010012f3010013f3010015f3010016f3010018f3010019f3010019f301001af301001af301001bf301001bf301001cf301001cf301001df301001ef301001ff3010020f30100", 3072, 1};
static const string _v3_lit_6144_e8e5d269df71b4f6 = {"a9000000a9000000ae000000ae0000003c2000003c2000004920000049200000222100002221000039210000392100009421000099210000a9210000aa2100001a2300001b23000028230000282300008823000088230000cf230000cf230000e9230000ec230000ed230000ee230000ef230000ef230000f0230000f0230000f1230000f2230000f3230000f3230000f8230000fa230000c2240000c2240000aa250000ab250000b6250000b6250000c0250000c0250000fb250000fe2500000026000001260000022600000326000004260000042600000526000005260000072600000d2600000e2600000e2600000f2600001026000011260000112600001226000012260000142600001526000016260000172600001826000018260000192600001c2600001d2600001d2600001e2600001f2600002026000020260000212600002126000022260000232600002426000025260000262600002626000027260000292600002a2600002a2600002b2600002d2600002e2600002e2600002f2600002f260000302600003726000038260000392600003a2600003a2600003b2600003f26000040260000402600004126000041260000422600004226000043260000472600004826000053260000542600005e2600005f2600005f2600006026000060260000612600006226000063260000632600006426000064260000652600006626000067260000672600006826000068260000692600007a2600007b2600007b2600007c2600007d2600007e2600007e2600007f2600007f2600008026000085260000902600009126000092260000922600009326000093260000942600009426000095260000952600009626000097260000982600009826000099260000992600009a2600009a2600009b2600009c2600009d2600009f260000a0260000a1260000a2260000a6260000a7260000a7260000a8260000a9260000aa260000ab260000ac260000af260000b0260000b1260000b2260000bc260000bd260000be260000bf260000c3260000c4260000c5260000c6260000c7260000c8260000c8260000c9260000cd260000ce260000ce260000cf260000cf260000d0260000d0260000d1260000d1260000d2260000d2260000d3260000d3260000d4260000d4260000d5260000e8260000e9260000e9260000ea260000ea260000eb260000ef260000f0260000f1260000f2260000f3260000f4260000f4260000f5260000f5260000f6260000f6260000f7260000f9260000fa260000fa260000fb260000fc260000fd260000fd260000fe26000001270000022700000227000003270000042700000527000005270000082700000c2700000d2700000d2700000e2700000e2700000f2700000f27000010270000112700001227000012270000142700001427000016270000162700001d2700001d270000212700002127000028270000282700003327000034270000442700004427000047270000472700004c2700004c2700004e2700004e270000532700005527000057270000572700006327000063270000642700006427000065270000672700009527000097270000a1270000a1270000b0270000b0270000bf270000bf2700003429000035290000052b0000072b00001b2b00001c2b0000502b0000502b0000552b0000552b000030300000303000003d3000003d3000009732000097320000993200009932000000f0010003f0010004f0010004f0010005f00100cef00100cff00100cff00100d0f00100fff001000df101000ff101002ff101002ff101006cf101006ff1010070f1010071f101007ef101007ff101008ef101008ef1010091f101009af10100adf10100e5f1010001f2010002f2010003f201000ff201001af201001af201002ff201002ff2010032f201003af201003cf201003ff2010049f201004ff2010050f2010051f2010052f20100fff2010000f301000cf301000df301000ef301000ff301000ff3010010f3010010f3010011f3010011f3010012f3010012f3010013f3010015f3010016f3010018f3010019f3010019f301001af301001af301001bf301001bf301001cf301001cf301001df301001ef301001ff3010020f3010021f3010021f3010022f3010023f3010024f301002cf301002df301002ff3010030f3010031f3010032f3010033f3010034f3010035f3010036f3010036f3010037f301004af301004bf301004bf301004cf301004ff3010050f3010050f3010051f301007bf301007cf301007cf301007df301007df301007ef301007ff3010080f3010093f3010094f3010095f3010096f3010097f3010098f3010098f3010099f301009bf301009cf301009df301009ef301009ff30100a0f30100c4f30100c5f30100c5f30100c6f30100c6f30100c7f30100c7f30100c8f30100c8f30100c9f30100c9f30100caf30100caf30100cbf30100cef30100cff30100d3f30100d4f30100dff30100e0f30100e3f30100e4f30100e4f30100e5f30100f0f30100f1f30100f2f30100f3f30100f3f30100f4f30100f4f30100f5f30100f5f30100f6f30100f6f30100f7f30100f7f30100f8f30100faf3010000f4010007f4010008f4010008f4010009f401000bf401000cf401000ef401000ff4010010f4010011f4010012f4010013f4010013f4010014f4010014f4010015f4010015f4010016f4010016f4010017f4010029f401002af401002af401002bf401003ef401003ff401003ff4010040f4010040f4010041f4010041f4010042f4010064f4010065f4010065f4010066f401006bf401006cf401006df401006ef40100acf40100adf40100adf40100aef40100b5f40100b6f40100b7f40100b8f40100ebf40100ecf40100edf40100eef40100eef40100eff40100eff40100f0f40100f4f40100f5f40100f5f40100f6f40100f7f40100f8f40100f8f40100f9f40100fcf40100fdf40100fdf40100fef40100fef40100fff4010002f5010003f5010003f5010004f5010007f5010008f5010008f5010009f5010009f501000af5010014f5010015f5010015f5010016f501002bf501002cf501002df501002ef501003df5010046f5010048f5010049f501004af501004bf501004ef501004ff501004ff5010050f501005bf501005cf5010067f5010068f501006ef501006ff5010070f5010071f5010072f5010073f5010079f501007af501007af501007bf5010086f5010087f5010087f5010088f5010089f501008af501008df501008ef501008ff5010090f5010090f5010091f5010094f5010095f5010096f5010097f50100a3f50100a4f50100a4f50100a5f50100a5f50100a6f50100a7f50100a8f50100a8f50100a9f50100b0f50100b1f50100b2f50100b3f50100bbf50100bcf50100bcf50100bdf50100c1f50100c2f50100c4f50100c5f50100d0f50100d1f50100d3f50100d4f50100dbf50100dcf50100def50100dff50100e0f50100e1f50100e1f50100e2f50100e2f50100e3f50100e3f50100e4f50100e7f50100e8f50100e8f50100e9f50100eef50100eff50100eff50100f0f50100f2f50100f3f50100f3f50100f4f50100f9f50100faf50100faf50100fbf50100fff5010000f6010000f6010001f6010006f6010007f6010008f6010009f601000df601000ef601000ef601000ff601000ff6010010f6010010f6010011f6010011f6010012f6010014f6010015f6010015f6010016f6010016f6010017f6010017f6010018f6010018f6010019f6010019f601001af601001af601001bf601001bf601001cf601001ef601001ff601001ff6010020f6010025f6010026f6010027f6010028f601002bf601002cf601002cf601002df601002df601002ef601002ff6010030f6010033f6010034f6010034f6010035f6010035f6010036f6010036f6010037f6010040f6010041f6010044f6010045f601004ff6010080f6010080f6010081f6010082f6010083f6010085f6010086f6010086f6010087f6010087f6010088f6010088f6010089f6010089f601008af601008bf601008cf601008cf601008df601008df601008ef601008ef601008ff601008ff6010090f6010090f6010091f6010093f6010094f6010094f6010095f6010095f6010096f6010096f6010097f6010097f6010098f6010098f6010099f601009af601009bf60100a1f60100a2f60100a2f60100a3f60100a3f60100a4f60100a5f60100a6f60100a6f60100a7f60100adf60100", 6144, 1};
static const string _v3_lit_7856_48062fd16215ac6b = {"a9000000a9000000ae000000ae0000003c2000003c2000004920000049200000222100002221000039210000392100009421000099210000a9210000aa2100001a2300001b23000028230000282300008823000088230000cf230000cf230000e9230000ec230000ed230000ee230000ef230000ef230000f0230000f0230000f1230000f2230000f3230000f3230000f8230000fa230000c2240000c2240000aa250000ab250000b6250000b6250000c0250000c0250000fb250000fe2500000026000001260000022600000326000004260000042600000526000005260000072600000d2600000e2600000e2600000f2600001026000011260000112600001226000012260000142600001526000016260000172600001826000018260000192600001c2600001d2600001d2600001e2600001f2600002026000020260000212600002126000022260000232600002426000025260000262600002626000027260000292600002a2600002a2600002b2600002d2600002e2600002e2600002f2600002f260000302600003726000038260000392600003a2600003a2600003b2600003f26000040260000402600004126000041260000422600004226000043260000472600004826000053260000542600005e2600005f2600005f2600006026000060260000612600006226000063260000632600006426000064260000652600006626000067260000672600006826000068260000692600007a2600007b2600007b2600007c2600007d2600007e2600007e2600007f2600007f2600008026000085260000902600009126000092260000922600009326000093260000942600009426000095260000952600009626000097260000982600009826000099260000992600009a2600009a2600009b2600009c2600009d2600009f260000a0260000a1260000a2260000a6260000a7260000a7260000a8260000a9260000aa260000ab260000ac260000af260000b0260000b1260000b2260000bc260000bd260000be260000bf260000c3260000c4260000c5260000c6260000c7260000c8260000c8260000c9260000cd260000ce260000ce260000cf260000cf260000d0260000d0260000d1260000d1260000d2260000d2260000d3260000d3260000d4260000d4260000d5260000e8260000e9260000e9260000ea260000ea260000eb260000ef260000f0260000f1260000f2260000f3260000f4260000f4260000f5260000f5260000f6260000f6260000f7260000f9260000fa260000fa260000fb260000fc260000fd260000fd260000fe26000001270000022700000227000003270000042700000527000005270000082700000c2700000d2700000d2700000e2700000e2700000f2700000f27000010270000112700001227000012270000142700001427000016270000162700001d2700001d270000212700002127000028270000282700003327000034270000442700004427000047270000472700004c2700004c2700004e2700004e270000532700005527000057270000572700006327000063270000642700006427000065270000672700009527000097270000a1270000a1270000b0270000b0270000bf270000bf2700003429000035290000052b0000072b00001b2b00001c2b0000502b0000502b0000552b0000552b000030300000303000003d3000003d3000009732000097320000993200009932000000f0010003f0010004f0010004f0010005f00100cef00100cff00100cff00100d0f00100fff001000df101000ff101002ff101002ff101006cf101006ff1010070f1010071f101007ef101007ff101008ef101008ef1010091f101009af10100adf10100e5f1010001f2010002f2010003f201000ff201001af201001af201002ff201002ff2010032f201003af201003cf201003ff2010049f201004ff2010050f2010051f2010052f20100fff2010000f301000cf301000df301000ef301000ff301000ff3010010f3010010f3010011f3010011f3010012f3010012f3010013f3010015f3010016f3010018f3010019f3010019f301001af301001af301001bf301001bf301001cf301001cf301001df301001ef301001ff3010020f3010021f3010021f3010022f3010023f3010024f301002cf301002df301002ff3010030f3010031f3010032f3010033f3010034f3010035f3010036f3010036f3010037f301004af301004bf301004bf301004cf301004ff3010050f3010050f3010051f301007bf301007cf301007cf301007df301007df301007ef301007ff3010080f3010093f3010094f3010095f3010096f3010097f3010098f3010098f3010099f301009bf301009cf301009df301009ef301009ff30100a0f30100c4f30100c5f30100c5f30100c6f30100c6f30100c7f30100c7f30100c8f30100c8f30100c9f30100c9f30100caf30100caf30100cbf30100cef30100cff30100d3f30100d4f30100dff30100e0f30100e3f30100e4f30100e4f30100e5f30100f0f30100f1f30100f2f30100f3f30100f3f30100f4f30100f4f30100f5f30100f5f30100f6f30100f6f30100f7f30100f7f30100f8f30100faf3010000f4010007f4010008f4010008f4010009f401000bf401000cf401000ef401000ff4010010f4010011f4010012f4010013f4010013f4010014f4010014f4010015f4010015f4010016f4010016f4010017f4010029f401002af401002af401002bf401003ef401003ff401003ff4010040f4010040f4010041f4010041f4010042f4010064f4010065f4010065f4010066f401006bf401006cf401006df401006ef40100acf40100adf40100adf40100aef40100b5f40100b6f40100b7f40100b8f40100ebf40100ecf40100edf40100eef40100eef40100eff40100eff40100f0f40100f4f40100f5f40100f5f40100f6f40100f7f40100f8f40100f8f40100f9f40100fcf40100fdf40100fdf40100fef40100fef40100fff4010002f5010003f5010003f5010004f5010007f5010008f5010008f5010009f5010009f501000af5010014f5010015f5010015f5010016f501002bf501002cf501002df501002ef501003df5010046f5010048f5010049f501004af501004bf501004ef501004ff501004ff5010050f501005bf501005cf5010067f5010068f501006ef501006ff5010070f5010071f5010072f5010073f5010079f501007af501007af501007bf5010086f5010087f5010087f5010088f5010089f501008af501008df501008ef501008ff5010090f5010090f5010091f5010094f5010095f5010096f5010097f50100a3f50100a4f50100a4f50100a5f50100a5f50100a6f50100a7f50100a8f50100a8f50100a9f50100b0f50100b1f50100b2f50100b3f50100bbf50100bcf50100bcf50100bdf50100c1f50100c2f50100c4f50100c5f50100d0f50100d1f50100d3f50100d4f50100dbf50100dcf50100def50100dff50100e0f50100e1f50100e1f50100e2f50100e2f50100e3f50100e3f50100e4f50100e7f50100e8f50100e8f50100e9f50100eef50100eff50100eff50100f0f50100f2f50100f3f50100f3f50100f4f50100f9f50100faf50100faf50100fbf50100fff5010000f6010000f6010001f6010006f6010007f6010008f6010009f601000df601000ef601000ef601000ff601000ff6010010f6010010f6010011f6010011f6010012f6010014f6010015f6010015f6010016f6010016f6010017f6010017f6010018f6010018f6010019f6010019f601001af601001af601001bf601001bf601001cf601001ef601001ff601001ff6010020f6010025f6010026f6010027f6010028f601002bf601002cf601002cf601002df601002df601002ef601002ff6010030f6010033f6010034f6010034f6010035f6010035f6010036f6010036f6010037f6010040f6010041f6010044f6010045f601004ff6010080f6010080f6010081f6010082f6010083f6010085f6010086f6010086f6010087f6010087f6010088f6010088f6010089f6010089f601008af601008bf601008cf601008cf601008df601008df601008ef601008ef601008ff601008ff6010090f6010090f6010091f6010093f6010094f6010094f6010095f6010095f6010096f6010096f6010097f6010097f6010098f6010098f6010099f601009af601009bf60100a1f60100a2f60100a2f60100a3f60100a3f60100a4f60100a5f60100a6f60100a6f60100a7f60100adf60100aef60100b1f60100b2f60100b2f60100b3f60100b5f60100b6f60100b6f60100b7f60100b8f60100b9f60100bef60100bff60100bff60100c0f60100c0f60100c1f60100c5f60100c6f60100caf60100cbf60100cbf60100ccf60100ccf60100cdf60100cff60100d0f60100d0f60100d1f60100d2f60100d3f60100d4f60100d5f60100d5f60100d6f60100d7f60100d8f60100dff60100e0f60100e5f60100e6f60100e8f60100e9f60100e9f60100eaf60100eaf60100ebf60100ecf60100edf60100eff60100f0f60100f0f60100f1f60100f2f60100f3f60100f3f60100f4f60100f6f60100f7f60100f8f60100f9f60100f9f60100faf60100faf60100fbf60100fcf60100fdf60100fff6010074f701007ff70100d5f70100dff70100e0f70100ebf70100ecf70100fff701000cf801000ff8010048f801004ff801005af801005ff8010088f801008ff80100aef80100fff801000cf901000cf901000df901000ff9010010f9010018f9010019f901001ef901001ff901001ff9010020f9010027f9010028f901002ff9010030f9010030f9010031f9010032f9010033f901003af901003cf901003ef901003ff901003ff9010040f9010045f9010047f901004bf901004cf901004cf901004df901004ff9010050f901005ef901005ff901006bf901006cf9010070f9010071f9010071f9010072f9010072f9010073f9010076f9010077f9010078f9010079f9010079f901007af901007af901007bf901007bf901007cf901007ff9010080f9010084f9010085f9010091f9010092f9010097f9010098f90100a2f90100a3f90100a4f90100a5f90100aaf90100abf90100adf90100aef90100aff90100b0f90100b9f90100baf90100bff90100c0f90100c0f90100c1f90100c2f90100c3f90100caf90100cbf90100cbf90100ccf90100ccf90100cdf90100cff90100d0f90100e6f90100e7f90100fff9010000fa01006ffa010070fa010073fa010074fa010074fa010075fa010077fa010078fa01007afa01007bfa01007ffa010080fa010082fa010083fa010086fa010087fa01008ffa010090fa010095fa010096fa0100a8fa0100a9fa0100affa0100b0fa0100b6fa0100b7fa0100bffa0100c0fa0100c2fa0100c3fa0100cffa0100d0fa0100d6fa0100d7fa0100fffa010000fc0100fdff0100", 7856, 1};
static const string _v3_lit_1712_24ca5b740ac82336 = {"aef60100b1f60100b2f60100b2f60100b3f60100b5f60100b6f60100b6f60100b7f60100b8f60100b9f60100bef60100bff60100bff60100c0f60100c0f60100c1f60100c5f60100c6f60100caf60100cbf60100cbf60100ccf60100ccf60100cdf60100cff60100d0f60100d0f60100d1f60100d2f60100d3f60100d4f60100d5f60100d5f60100d6f60100d7f60100d8f60100dff60100e0f60100e5f60100e6f60100e8f60100e9f60100e9f60100eaf60100eaf60100ebf60100ecf60100edf60100eff60100f0f60100f0f60100f1f60100f2f60100f3f60100f3f60100f4f60100f6f60100f7f60100f8f60100f9f60100f9f60100faf60100faf60100fbf60100fcf60100fdf60100fff6010074f701007ff70100d5f70100dff70100e0f70100ebf70100ecf70100fff701000cf801000ff8010048f801004ff801005af801005ff8010088f801008ff80100aef80100fff801000cf901000cf901000df901000ff9010010f9010018f9010019f901001ef901001ff901001ff9010020f9010027f9010028f901002ff9010030f9010030f9010031f9010032f9010033f901003af901003cf901003ef901003ff901003ff9010040f9010045f9010047f901004bf901004cf901004cf901004df901004ff9010050f901005ef901005ff901006bf901006cf9010070f9010071f9010071f9010072f9010072f9010073f9010076f9010077f9010078f9010079f9010079f901007af901007af901007bf901007bf901007cf901007ff9010080f9010084f9010085f9010091f9010092f9010097f9010098f90100a2f90100a3f90100a4f90100a5f90100aaf90100abf90100adf90100aef90100aff90100b0f90100b9f90100baf90100bff90100c0f90100c0f90100c1f90100c2f90100c3f90100caf90100cbf90100cbf90100ccf90100ccf90100cdf90100cff90100d0f90100e6f90100e7f90100fff9010000fa01006ffa010070fa010073fa010074fa010074fa010075fa010077fa010078fa01007afa01007bfa01007ffa010080fa010082fa010083fa010086fa010087fa01008ffa010090fa010095fa010096fa0100a8fa0100a9fa0100affa0100b0fa0100b6fa0100b7fa0100bffa0100c0fa0100c2fa0100c3fa0100cffa0100d0fa0100d6fa0100d7fa0100fffa010000fc0100fdff0100", 1712, 1};
static const string _v3_lit_74_82fc39ccb1421152 = {"attempted to decode too many bytes, utf-8 is limited to four bytes maximum", 74, 1};
static const string _v3_lit_47_1f7788b2d2b7fc94 = {"builtin__str_intp(1, _MOV((StrIntpData[]){{_S(\"", 47, 1};
static const string _v3_lit_47_3f2e1d05be76b5e9 = {"builtin__str_intp(2, _MOV((StrIntpData[]){{_S(\"", 47, 1};
static const string _v3_lit_5_7abebb90e73faeeb = {"error", 5, 1};
static const string _v3_lit_44_7e766e4cc095bb70 = {"interface method IError.code not implemented", 44, 1};
static const string _v3_lit_43_9edf8799b50a549c = {"interface method IError.msg not implemented", 43, 1};
static const string _v3_lit_54_503bb76740bf2bb9 = {"interface method hash__Hash.block_size not implemented", 54, 1};
static const string _v3_lit_48_fb91f183b903b558 = {"interface method hash__Hash.free not implemented", 48, 1};
static const string _v3_lit_49_eb073e2877ead767 = {"interface method hash__Hash.reset not implemented", 49, 1};
static const string _v3_lit_48_e55a586fc0c6b73f = {"interface method hash__Hash.size not implemented", 48, 1};
static const string _v3_lit_47_67a5effad7253ea3 = {"interface method hash__Hash.sum not implemented", 47, 1};
static const string _v3_lit_49_2678ade7cd32896b = {"interface method hash__Hash.write not implemented", 49, 1};
static const string _v3_lit_53_95bddd17dfe45e44 = {"interface method hash__Hash32er.sum32 not implemented", 53, 1};
static const string _v3_lit_53_5f2d8f78123176b0 = {"interface method hash__Hash64er.sum64 not implemented", 53, 1};
static const string _v3_lit_51_b1d08b2859beebd5 = {"invalid radix, it should be => 2 and <= 36, actual:", 51, 1};

#define bits__de_bruijn32 (((u32)(0x077CB531)))
u8 bits__de_bruijn32tab[32];
#define bits__de_bruijn64 (((u64)(0x03f79d71b4ca8b09)))
u8 bits__de_bruijn64tab[64];
#define bits__m0 (((u64)(0x5555555555555555)))
#define bits__m1 (((u64)(0x3333333333333333)))
#define bits__m2 (((u64)(0x0f0f0f0f0f0f0f0f)))
#define bits__m3 (((u64)(0x00ff00ff00ff00ff)))
#define bits__m4 (((u64)(0x0000ffff0000ffff)))
static const u8 bits__n8 = ((u8)(8));
#define bits__n16 (((u16)(16)))
#define bits__n32 (((u32)(32)))
#define bits__n64 (((u64)(64)))
#define bits__two32 (((u64)(0x100000000)))
#define bits__mask32 ((((u64)(0x100000000))) - (1))
string bits__overflow_error = (string){"Overflow Error", 14, 1};
string bits__divide_error = (string){"Divide by Zero Error", 20, 1};
u8 bits__ntz_8_tab[256];
u8 bits__pop_8_tab[256];
u8 bits__rev_8_tab[256];
u8 bits__len_8_tab[256];
#define strconv__int_size (32)
#define strconv__i64_min_int32 ((((i64)(-(2147483647)))) - (1))
#define strconv__i64_max_int32 ((((i64)(2147483646))) + (1))
u64 strconv__ten_pow_table_64[20];
#define strconv__mantbits64 (((u32)(52)))
#define strconv__expbits64 (((u32)(11)))
#define strconv__bias64 (1023)
#define strconv__maxexp64 (2047)
double strconv__dec_round[36];
#define strconv__pow5_num_bits_32 (61)
#define strconv__pow5_inv_num_bits_32 (59)
#define strconv__pow5_num_bits_64 (121)
#define strconv__pow5_inv_num_bits_64 (122)
u64 strconv__powers_of_10[18];
u64 strconv__pow5_split_32[47];
u64 strconv__pow5_inv_split_32[31];
u64 strconv__pow5_split_64_x[652];
u64 strconv__pow5_inv_split_64_x[584];
#define strconv__single_plus_zero (((u32)(0x00000000)))
#define strconv__single_minus_zero (((u32)(0x80000000)))
#define strconv__single_plus_infinity (((u32)(0x7F800000)))
#define strconv__single_minus_infinity (((u32)(0xFF800000)))
#define strconv__digits (18)
#define strconv__double_plus_zero (((u64)(0x0000000000000000)))
#define strconv__double_minus_zero (((u64)(0x8000000000000000)))
#define strconv__double_plus_infinity (((u64)(0x7FF0000000000000)))
#define strconv__double_minus_infinity (((u64)(0xFFF0000000000000)))
#define strconv__c_dpoint ('.')
#define strconv__c_plus ('+')
#define strconv__c_minus ('-')
#define strconv__c_zero ('0')
#define strconv__c_nine ('9')
#define strconv__c_ten (((u32)(10)))
u64 strconv__pos_exp[309];
u64 strconv__neg_exp[324];
u32 strconv__ten_pow_table_32[10];
#define strconv__mantbits32 (((u32)(23)))
#define strconv__expbits32 (((u32)(8)))
#define strconv__bias32 (127)
#define strconv__maxexp32 (255)
#define strconv__max_size_f64_char (512)
string strconv__digit_pairs = (string){"00102030405060708090011121314151617181910212223242526272829203132333435363738393041424344454647484940515253545556575859506162636465666768696071727374757677787970818283848586878889809192939495969798999", 200, 1};
string strconv__base_digits = (string){"0123456789abcdefghijklmnopqrstuvwxyz", 36, 1};
#define hash__wyp0 (((u64)(0x2d358dccaa6c78a5)))
#define hash__wyp1 (((u64)(0x8bb84b93962eacc9)))
#define hash__wyp2 (((u64)(0x4b33a62ed433d4a3)))
#define hash__wyp3 (((u64)(0x4d5a2da51de1aa47)))
#define builtin__autostr_type_stack_max_depth (64)
MessageError builtin__error_sentinel__object = {.msg = {"error", 5, 1}};
IError builtin__error_sentinel = {._typ = 71273906, ._object = &builtin__error_sentinel__object, .message = {"error", 5, 1}, .code = 0};
IError builtin__none__;
string builtin__grapheme_control_ranges = (string){"00000000090000000b0000000c0000000e0000001f0000007f0000009f000000ad000000ad0000001c0600001c0600000e1800000e1800000b2000000b2000000e2000000f200000282000002820000029200000292000002a2000002e20000060200000642000006520000065200000662000006f200000fffe0000fffe0000f0ff0000f8ff0000f9ff0000fbff00003034010038340100a0bc0100a3bc010073d101007ad1010000000e0000000e0001000e0001000e0002000e001f000e0080000e00ff000e00f0010e00ff0f0e00", 416, 1};
string builtin__grapheme_extend_ranges = (string){"000300006f0300008304000087040000880400008904000091050000bd050000bf050000bf050000c1050000c2050000c4050000c5050000c7050000c7050000100600001a0600004b0600005f0600007006000070060000d6060000dc060000df060000e4060000e7060000e8060000ea060000ed0600001107000011070000300700004a070000a6070000b0070000eb070000f3070000fd070000fd07000016080000190800001b080000230800002508000027080000290800002d080000590800005b080000d3080000e1080000e3080000020900003a0900003a0900003c0900003c09000041090000480900004d0900004d090000510900005709000062090000630900008109000081090000bc090000bc090000be090000be090000c1090000c4090000cd090000cd090000d7090000d7090000e2090000e3090000fe090000fe090000010a0000020a00003c0a00003c0a0000410a0000420a0000470a0000480a00004b0a00004d0a0000510a0000510a0000700a0000710a0000750a0000750a0000810a0000820a0000bc0a0000bc0a0000c10a0000c50a0000c70a0000c80a0000cd0a0000cd0a0000e20a0000e30a0000fa0a0000ff0a0000010b0000010b00003c0b00003c0b00003e0b00003e0b00003f0b00003f0b0000410b0000440b00004d0b00004d0b0000550b0000560b0000570b0000570b0000620b0000630b0000820b0000820b0000be0b0000be0b0000c00b0000c00b0000cd0b0000cd0b0000d70b0000d70b0000000c0000000c0000040c0000040c00003e0c0000400c0000460c0000480c00004a0c00004d0c0000550c0000560c0000620c0000630c0000810c0000810c0000bc0c0000bc0c0000bf0c0000bf0c0000c20c0000c20c0000c60c0000c60c0000cc0c0000cd0c0000d50c0000d60c0000e20c0000e30c0000000d0000010d00003b0d00003c0d00003e0d00003e0d0000410d0000440d00004d0d00004d0d0000570d0000570d0000620d0000630d0000810d0000810d0000ca0d0000ca0d0000cf0d0000cf0d0000d20d0000d40d0000d60d0000d60d0000df0d0000df0d0000310e0000310e0000340e00003a0e0000470e00004e0e0000b10e0000b10e0000b40e0000bc0e0000c80e0000cd0e0000180f0000190f0000350f0000350f0000370f0000370f0000390f0000390f0000710f00007e0f0000800f0000840f0000860f0000870f00008d0f0000970f0000990f0000bc0f0000c60f0000c60f00002d100000301000003210000037100000391000003a1000003d1000003e10000058100000591000005e100000601000007110000074100000821000008210000085100000861000008d1000008d1000009d1000009d1000005d1300005f1300001217000014170000321700003417000052170000531700007217000073170000b4170000b5170000b7170000bd170000c6170000c6170000c9170000d3170000dd170000dd1700000b1800000d1800008518000086180000a9180000a9180000201900002219000027190000281900003219000032190000391900003b190000171a0000181a00001b1a00001b1a0000561a0000561a0000581a00005e1a0000601a0000601a0000621a0000621a0000651a00006c1a0000731a00007c1a00007f1a00007f1a0000b01a0000bd1a0000be1a0000be1a0000bf1a0000c01a0000001b0000031b0000341b0000341b0000351b0000351b0000361b00003a1b00003c1b00003c1b0000421b0000421b00006b1b0000731b0000801b0000811b0000a21b0000a51b0000a81b0000a91b0000ab1b0000ad1b0000e61b0000e61b0000e81b0000e91b0000ed1b0000ed1b0000ef1b0000f11b00002c1c0000331c0000361c0000371c0000d01c0000d21c0000d41c0000e01c0000e21c0000e81c0000ed1c0000ed1c0000f41c0000f41c0000f81c0000f91c0000c01d0000f91d0000fb1d0000ff1d00000c2000000c200000d0200000dc200000dd200000e0200000e1200000e1200000e2200000e4200000e5200000f0200000ef2c0000f12c00007f2d00007f2d0000e02d0000ff2d00002a3000002d3000002e3000002f300000993000009a3000006fa600006fa6000070a6000072a6000074a600007da600009ea600009fa60000f0a60000f1a6000002a8000002a8000006a8000006a800000ba800000ba8000025a8000026a800002ca800002ca80000c4a80000c5a80000e0a80000f1a80000ffa80000ffa8000026a900002da9000047a9000051a9000080a9000082a90000b3a90000b3a90000b6a90000b9a90000bca90000bda90000e5a90000e5a9000029aa00002eaa000031aa000032aa000035aa000036aa000043aa000043aa00004caa00004caa00007caa00007caa0000b0aa0000b0aa0000b2aa0000b4aa0000b7aa0000b8aa0000beaa0000bfaa0000c1aa0000c1aa0000ecaa0000edaa0000f6aa0000f6aa0000e5ab0000e5ab0000e8ab0000e8ab0000edab0000edab00001efb00001efb000000fe00000ffe000020fe00002ffe00009eff00009fff0000fd010100fd010100e0020100e0020100760301007a030100010a0100030a0100050a0100060a01000c0a01000f0a0100380a01003a0a01003f0a01003f0a0100e50a0100e60a0100240d0100270d0100ab0e0100ac0e0100460f0100500f0100011001000110010038100100461001007f10010081100100b3100100b6100100b9100100ba1001000011010002110100271101002b1101002d1101003411010073110100731101008011010081110100b6110100be110100c9110100cc110100cf110100cf1101002f12010031120100341201003412010036120100371201003e1201003e120100df120100df120100e3120100ea12010000130100011301003b1301003c1301003e1301003e13010040130100401301005713010057130100661301006c1301007013010074130100381401003f140100421401004414010046140100461401005e1401005e140100b0140100b0140100b3140100b8140100ba140100ba140100bd140100bd140100bf140100c0140100c2140100c3140100af150100af150100b2150100b5150100bc150100bd150100bf150100c0150100dc150100dd150100331601003a1601003d1601003d1601003f16010040160100ab160100ab160100ad160100ad160100b0160100b5160100b7160100b71601001d1701001f1701002217010025170100271701002b1701002f18010037180100391801003a18010030190100301901003b1901003c1901003e1901003e1901004319010043190100d4190100d7190100da190100db190100e0190100e0190100011a01000a1a0100331a0100381a01003b1a01003e1a0100471a0100471a0100511a0100561a0100591a01005b1a01008a1a0100961a0100981a0100991a0100301c0100361c0100381c01003d1c01003f1c01003f1c0100921c0100a71c0100aa1c0100b01c0100b21c0100b31c0100b51c0100b61c0100311d0100361d01003a1d01003a1d01003c1d01003d1d01003f1d0100451d0100471d0100471d0100901d0100911d0100951d0100951d0100971d0100971d0100f31e0100f41e0100f06a0100f46a0100306b0100366b01004f6f01004f6f01008f6f0100926f0100e46f0100e46f01009dbc01009ebc010065d1010065d1010067d1010069d101006ed1010072d101007bd1010082d1010085d101008bd10100aad10100add1010042d2010044d2010000da010036da01003bda01006cda010075da010075da010084da010084da01009bda01009fda0100a1da0100afda010000e0010006e0010008e0010018e001001be0010021e0010023e0010024e0010026e001002ae0010030e1010036e10100ece20100efe20100d0e80100d6e8010044e901004ae90100fbf30100fff3010020000e007f000e0000010e00ef010e00", 5728, 1};
string builtin__grapheme_spacing_mark_ranges = (string){"03090000030900003b0900003b0900003e09000040090000490900004c0900004e0900004f0900008209000083090000bf090000c0090000c7090000c8090000cb090000cc090000030a0000030a00003e0a0000400a0000830a0000830a0000be0a0000c00a0000c90a0000c90a0000cb0a0000cc0a0000020b0000030b0000400b0000400b0000470b0000480b00004b0b00004c0b0000bf0b0000bf0b0000c10b0000c20b0000c60b0000c80b0000ca0b0000cc0b0000010c0000030c0000410c0000440c0000820c0000830c0000be0c0000be0c0000c00c0000c10c0000c30c0000c40c0000c70c0000c80c0000ca0c0000cb0c0000020d0000030d00003f0d0000400d0000460d0000480d00004a0d00004c0d0000820d0000830d0000d00d0000d10d0000d80d0000de0d0000f20d0000f30d0000330e0000330e0000b30e0000b30e00003e0f00003f0f00007f0f00007f0f000031100000311000003b1000003c10000056100000571000008410000084100000b6170000b6170000be170000c5170000c7170000c81700002319000026190000291900002b19000030190000311900003319000038190000191a00001a1a0000551a0000551a0000571a0000571a00006d1a0000721a0000041b0000041b00003b1b00003b1b00003d1b0000411b0000431b0000441b0000821b0000821b0000a11b0000a11b0000a61b0000a71b0000aa1b0000aa1b0000e71b0000e71b0000ea1b0000ec1b0000ee1b0000ee1b0000f21b0000f31b0000241c00002b1c0000341c0000351c0000e11c0000e11c0000f71c0000f71c000023a8000024a8000027a8000027a8000080a8000081a80000b4a80000c3a8000052a9000053a9000083a9000083a90000b4a90000b5a90000baa90000bba90000bea90000c0a900002faa000030aa000033aa000034aa00004daa00004daa0000ebaa0000ebaa0000eeaa0000efaa0000f5aa0000f5aa0000e3ab0000e4ab0000e6ab0000e7ab0000e9ab0000eaab0000ecab0000ecab0000001001000010010002100100021001008210010082100100b0100100b2100100b7100100b81001002c1101002c11010045110100461101008211010082110100b3110100b5110100bf110100c0110100ce110100ce1101002c1201002e12010032120100331201003512010035120100e0120100e212010002130100031301003f1301003f130100411301004413010047130100481301004b1301004d1301006213010063130100351401003714010040140100411401004514010045140100b1140100b2140100b9140100b9140100bb140100bc140100be140100be140100c1140100c1140100b0150100b1150100b8150100bb150100be150100be15010030160100321601003b1601003c1601003e1601003e160100ac160100ac160100ae160100af160100b6160100b6160100201701002117010026170100261701002c1801002e1801003818010038180100311901003519010037190100381901003d1901003d19010040190100401901004219010042190100d1190100d3190100dc190100df190100e4190100e4190100391a0100391a0100571a0100581a0100971a0100971a01002f1c01002f1c01003e1c01003e1c0100a91c0100a91c0100b11c0100b11c0100b41c0100b41c01008a1d01008e1d0100931d0100941d0100961d0100961d0100f51e0100f61e0100516f0100876f0100f06f0100f16f010066d1010066d101006dd101006dd10100", 2544, 1};
string builtin__grapheme_prepend_ranges = (string){"0006000005060000dd060000dd0600000f0700000f070000e2080000e20800004e0d00004e0d0000bd100100bd100100cd100100cd100100c2110100c31101003f1901003f19010041190100411901003a1a01003a1a0100841a0100891a0100461d0100461d0100", 208, 1};
string builtin__grapheme_extended_pictographic_ranges = (string){"a9000000a9000000ae000000ae0000003c2000003c2000004920000049200000222100002221000039210000392100009421000099210000a9210000aa2100001a2300001b23000028230000282300008823000088230000cf230000cf230000e9230000ec230000ed230000ee230000ef230000ef230000f0230000f0230000f1230000f2230000f3230000f3230000f8230000fa230000c2240000c2240000aa250000ab250000b6250000b6250000c0250000c0250000fb250000fe2500000026000001260000022600000326000004260000042600000526000005260000072600000d2600000e2600000e2600000f2600001026000011260000112600001226000012260000142600001526000016260000172600001826000018260000192600001c2600001d2600001d2600001e2600001f2600002026000020260000212600002126000022260000232600002426000025260000262600002626000027260000292600002a2600002a2600002b2600002d2600002e2600002e2600002f2600002f260000302600003726000038260000392600003a2600003a2600003b2600003f26000040260000402600004126000041260000422600004226000043260000472600004826000053260000542600005e2600005f2600005f2600006026000060260000612600006226000063260000632600006426000064260000652600006626000067260000672600006826000068260000692600007a2600007b2600007b2600007c2600007d2600007e2600007e2600007f2600007f2600008026000085260000902600009126000092260000922600009326000093260000942600009426000095260000952600009626000097260000982600009826000099260000992600009a2600009a2600009b2600009c2600009d2600009f260000a0260000a1260000a2260000a6260000a7260000a7260000a8260000a9260000aa260000ab260000ac260000af260000b0260000b1260000b2260000bc260000bd260000be260000bf260000c3260000c4260000c5260000c6260000c7260000c8260000c8260000c9260000cd260000ce260000ce260000cf260000cf260000d0260000d0260000d1260000d1260000d2260000d2260000d3260000d3260000d4260000d4260000d5260000e8260000e9260000e9260000ea260000ea260000eb260000ef260000f0260000f1260000f2260000f3260000f4260000f4260000f5260000f5260000f6260000f6260000f7260000f9260000fa260000fa260000fb260000fc260000fd260000fd260000fe26000001270000022700000227000003270000042700000527000005270000082700000c2700000d2700000d2700000e2700000e2700000f2700000f27000010270000112700001227000012270000142700001427000016270000162700001d2700001d270000212700002127000028270000282700003327000034270000442700004427000047270000472700004c2700004c2700004e2700004e270000532700005527000057270000572700006327000063270000642700006427000065270000672700009527000097270000a1270000a1270000b0270000b0270000bf270000bf2700003429000035290000052b0000072b00001b2b00001c2b0000502b0000502b0000552b0000552b000030300000303000003d3000003d3000009732000097320000993200009932000000f0010003f0010004f0010004f0010005f00100cef00100cff00100cff00100d0f00100fff001000df101000ff101002ff101002ff101006cf101006ff1010070f1010071f101007ef101007ff101008ef101008ef1010091f101009af10100adf10100e5f1010001f2010002f2010003f201000ff201001af201001af201002ff201002ff2010032f201003af201003cf201003ff2010049f201004ff2010050f2010051f2010052f20100fff2010000f301000cf301000df301000ef301000ff301000ff3010010f3010010f3010011f3010011f3010012f3010012f3010013f3010015f3010016f3010018f3010019f3010019f301001af301001af301001bf301001bf301001cf301001cf301001df301001ef301001ff3010020f3010021f3010021f3010022f3010023f3010024f301002cf301002df301002ff3010030f3010031f3010032f3010033f3010034f3010035f3010036f3010036f3010037f301004af301004bf301004bf301004cf301004ff3010050f3010050f3010051f301007bf301007cf301007cf301007df301007df301007ef301007ff3010080f3010093f3010094f3010095f3010096f3010097f3010098f3010098f3010099f301009bf301009cf301009df301009ef301009ff30100a0f30100c4f30100c5f30100c5f30100c6f30100c6f30100c7f30100c7f30100c8f30100c8f30100c9f30100c9f30100caf30100caf30100cbf30100cef30100cff30100d3f30100d4f30100dff30100e0f30100e3f30100e4f30100e4f30100e5f30100f0f30100f1f30100f2f30100f3f30100f3f30100f4f30100f4f30100f5f30100f5f30100f6f30100f6f30100f7f30100f7f30100f8f30100faf3010000f4010007f4010008f4010008f4010009f401000bf401000cf401000ef401000ff4010010f4010011f4010012f4010013f4010013f4010014f4010014f4010015f4010015f4010016f4010016f4010017f4010029f401002af401002af401002bf401003ef401003ff401003ff4010040f4010040f4010041f4010041f4010042f4010064f4010065f4010065f4010066f401006bf401006cf401006df401006ef40100acf40100adf40100adf40100aef40100b5f40100b6f40100b7f40100b8f40100ebf40100ecf40100edf40100eef40100eef40100eff40100eff40100f0f40100f4f40100f5f40100f5f40100f6f40100f7f40100f8f40100f8f40100f9f40100fcf40100fdf40100fdf40100fef40100fef40100fff4010002f5010003f5010003f5010004f5010007f5010008f5010008f5010009f5010009f501000af5010014f5010015f5010015f5010016f501002bf501002cf501002df501002ef501003df5010046f5010048f5010049f501004af501004bf501004ef501004ff501004ff5010050f501005bf501005cf5010067f5010068f501006ef501006ff5010070f5010071f5010072f5010073f5010079f501007af501007af501007bf5010086f5010087f5010087f5010088f5010089f501008af501008df501008ef501008ff5010090f5010090f5010091f5010094f5010095f5010096f5010097f50100a3f50100a4f50100a4f50100a5f50100a5f50100a6f50100a7f50100a8f50100a8f50100a9f50100b0f50100b1f50100b2f50100b3f50100bbf50100bcf50100bcf50100bdf50100c1f50100c2f50100c4f50100c5f50100d0f50100d1f50100d3f50100d4f50100dbf50100dcf50100def50100dff50100e0f50100e1f50100e1f50100e2f50100e2f50100e3f50100e3f50100e4f50100e7f50100e8f50100e8f50100e9f50100eef50100eff50100eff50100f0f50100f2f50100f3f50100f3f50100f4f50100f9f50100faf50100faf50100fbf50100fff5010000f6010000f6010001f6010006f6010007f6010008f6010009f601000df601000ef601000ef601000ff601000ff6010010f6010010f6010011f6010011f6010012f6010014f6010015f6010015f6010016f6010016f6010017f6010017f6010018f6010018f6010019f6010019f601001af601001af601001bf601001bf601001cf601001ef601001ff601001ff6010020f6010025f6010026f6010027f6010028f601002bf601002cf601002cf601002df601002df601002ef601002ff6010030f6010033f6010034f6010034f6010035f6010035f6010036f6010036f6010037f6010040f6010041f6010044f6010045f601004ff6010080f6010080f6010081f6010082f6010083f6010085f6010086f6010086f6010087f6010087f6010088f6010088f6010089f6010089f601008af601008bf601008cf601008cf601008df601008df601008ef601008ef601008ff601008ff6010090f6010090f6010091f6010093f6010094f6010094f6010095f6010095f6010096f6010096f6010097f6010097f6010098f6010098f6010099f601009af601009bf60100a1f60100a2f60100a2f60100a3f60100a3f60100a4f60100a5f60100a6f60100a6f60100a7f60100adf60100aef60100b1f60100b2f60100b2f60100b3f60100b5f60100b6f60100b6f60100b7f60100b8f60100b9f60100bef60100bff60100bff60100c0f60100c0f60100c1f60100c5f60100c6f60100caf60100cbf60100cbf60100ccf60100ccf60100cdf60100cff60100d0f60100d0f60100d1f60100d2f60100d3f60100d4f60100d5f60100d5f60100d6f60100d7f60100d8f60100dff60100e0f60100e5f60100e6f60100e8f60100e9f60100e9f60100eaf60100eaf60100ebf60100ecf60100edf60100eff60100f0f60100f0f60100f1f60100f2f60100f3f60100f3f60100f4f60100f6f60100f7f60100f8f60100f9f60100f9f60100faf60100faf60100fbf60100fcf60100fdf60100fff6010074f701007ff70100d5f70100dff70100e0f70100ebf70100ecf70100fff701000cf801000ff8010048f801004ff801005af801005ff8010088f801008ff80100aef80100fff801000cf901000cf901000df901000ff9010010f9010018f9010019f901001ef901001ff901001ff9010020f9010027f9010028f901002ff9010030f9010030f9010031f9010032f9010033f901003af901003cf901003ef901003ff901003ff9010040f9010045f9010047f901004bf901004cf901004cf901004df901004ff9010050f901005ef901005ff901006bf901006cf9010070f9010071f9010071f9010072f9010072f9010073f9010076f9010077f9010078f9010079f9010079f901007af901007af901007bf901007bf901007cf901007ff9010080f9010084f9010085f9010091f9010092f9010097f9010098f90100a2f90100a3f90100a4f90100a5f90100aaf90100abf90100adf90100aef90100aff90100b0f90100b9f90100baf90100bff90100c0f90100c0f90100c1f90100c2f90100c3f90100caf90100cbf90100cbf90100ccf90100ccf90100cdf90100cff90100d0f90100e6f90100e7f90100fff9010000fa01006ffa010070fa010073fa010074fa010074fa010075fa010077fa010078fa01007afa01007bfa01007ffa010080fa010082fa010083fa010086fa010087fa01008ffa010090fa010095fa010096fa0100a8fa0100a9fa0100affa0100b0fa0100b6fa0100b7fa0100bffa0100c0fa0100c2fa0100c3fa0100cffa0100d0fa0100d6fa0100d7fa0100fffa010000fc0100fdff0100", 7856, 1};
string builtin__digit_pairs = (string){"00102030405060708090011121314151617181910212223242526272829203132333435363738393041424344454647484940515253545556575859506162636465666768696071727374757677787970818283848586878889809192939495969798999", 200, 1};
#define builtin__min_i8 (((i8)(-(128))))
#define builtin__max_i8 (((i8)(127)))
#define builtin__min_i16 (((i16)(-(32768))))
#define builtin__max_i16 (((i16)(32767)))
#define builtin__min_i32 (((i32)(-(2147483648))))
#define builtin__max_i32 (((i32)(2147483647)))
#define builtin__min_i64 (((i64)((-(9223372036854775807)) - (1))))
#define builtin__max_i64 (((i64)(9223372036854775807)))
#define builtin__min_int (((i64)(((i64)((-(9223372036854775807)) - (1))))))
#define builtin__max_int (((i64)(((i64)(9223372036854775807)))))
static const u8 builtin__min_u8 = ((u8)(0));
static const u8 builtin__max_u8 = ((u8)(255));
#define builtin__min_u16 (((u16)(0)))
#define builtin__max_u16 (((u16)(65535)))
#define builtin__min_u32 (((u32)(0)))
#define builtin__max_u32 (((u32)(4294967295)))
#define builtin__min_u64 (((u64)(0)))
#define builtin__max_u64 (((u64)(18446744073709551615)))
#define builtin__hashbits (24)
#define builtin__max_cached_hashbits (16)
#define builtin__init_log_capicity (5)
#define builtin__init_capicity ((1) << (5))
#define builtin__max_load_factor (0.8)
#define builtin__init_even_index (((1) << (5)) - (2))
#define builtin__extra_metas_inc (4)
#define builtin__hash_mask (((u32)(0x00FFFFFF)))
#define builtin__probe_inc (((u32)(0x01000000)))
#define builtin__rune_maps_columns_in_row (4)
#define builtin__rune_maps_ul (-(3))
#define builtin__rune_maps_utl (-(2))
i32 builtin__rune_maps[1264];
#define builtin__degree (6)
#define builtin__mid_index ((6) - (1))
#define builtin__max_len (((2) * (6)) - (1))
#define builtin__children_bytes ((sizeof(void*)) * (((((2) * (6)) - (1)) + (1))))
#define builtin__replace_stack_buffer_size (10)
#define builtin__kmp_stack_buffer_size (20)
static const u8 builtin__str_intp_has_dynamic_width = ((u8)(1));
static const u8 builtin__str_intp_has_dynamic_precision = ((u8)((1) << (1)));
string builtin__si_s_code = (string){"0xfe10", 6, 1};
string builtin__si_g32_code = (string){"0xfe0e", 6, 1};
string builtin__si_g64_code = (string){"0xfe0f", 6, 1};
#define builtin__utf8_replacement_rune (((u32)(0xfffd)))
#define builtin__prealloc_block_size (((16) * (1024)) * (1024))
#define builtin__prealloc_scope_block_size ((256) * (1024))
#define builtin__prealloc_recycle_cache_slots (512)
#define builtin__prealloc_default_align ((sizeof(void*)) * (2))
#define builtin__cp_acp (0)
#define builtin__cp_utf8 (65001)

/* V3CACHE_BODY_BEGIN */
/* V3CACHE_MODULE __v3_program_support */
void _vinit() {
	memmove(bits__de_bruijn32tab, (u8[32]){((u8)(0)), 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9}, sizeof(bits__de_bruijn32tab));
	memmove(bits__de_bruijn64tab, (u8[64]){((u8)(0)), 1, 56, 2, 57, 49, 28, 3, 61, 58, 42, 50, 38, 29, 17, 4, 62, 47, 59, 36, 45, 43, 51, 22, 53, 39, 33, 30, 24, 18, 12, 5, 63, 55, 48, 27, 60, 41, 37, 16, 46, 35, 44, 21, 52, 32, 23, 11, 54, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19, 9, 13, 8, 7, 6}, sizeof(bits__de_bruijn64tab));
	memmove(bits__ntz_8_tab, (u8[256]){((u8)(0x08)), 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x07, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00}, sizeof(bits__ntz_8_tab));
	memmove(bits__pop_8_tab, (u8[256]){((u8)(0x00)), 0x01, 0x01, 0x02, 0x01, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x04, 0x01, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x04, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x01, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x04, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x01, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x04, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x04, 0x05, 0x05, 0x06, 0x05, 0x06, 0x06, 0x07, 0x01, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x04, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x04, 0x05, 0x05, 0x06, 0x05, 0x06, 0x06, 0x07, 0x02, 0x03, 0x03, 0x04, 0x03, 0x04, 0x04, 0x05, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x04, 0x05, 0x05, 0x06, 0x05, 0x06, 0x06, 0x07, 0x03, 0x04, 0x04, 0x05, 0x04, 0x05, 0x05, 0x06, 0x04, 0x05, 0x05, 0x06, 0x05, 0x06, 0x06, 0x07, 0x04, 0x05, 0x05, 0x06, 0x05, 0x06, 0x06, 0x07, 0x05, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x08}, sizeof(bits__pop_8_tab));
	memmove(bits__rev_8_tab, (u8[256]){((u8)(0x00)), 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, 0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc, 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, 0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, 0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6, 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1, 0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9, 0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd, 0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, 0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7, 0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff}, sizeof(bits__rev_8_tab));
	memmove(bits__len_8_tab, (u8[256]){((u8)(0x00)), 0x01, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08}, sizeof(bits__len_8_tab));
	memmove(strconv__ten_pow_table_64, (u64[20]){((u64)(1)), ((u64)(10)), ((u64)(100)), ((u64)(1000)), ((u64)(10000)), ((u64)(100000)), ((u64)(1000000)), ((u64)(10000000)), ((u64)(100000000)), ((u64)(1000000000)), ((u64)(10000000000)), ((u64)(100000000000)), ((u64)(1000000000000)), ((u64)(10000000000000)), ((u64)(100000000000000)), ((u64)(1000000000000000)), ((u64)(10000000000000000)), ((u64)(100000000000000000)), ((u64)(1000000000000000000)), ((u64)(10000000000000000000))}, sizeof(strconv__ten_pow_table_64));
	memmove(strconv__dec_round, (double[36]){((double)(0.5)), 0.05, 0.005, 0.0005, 0.00005, 0.000005, 0.0000005, 0.00000005, 0.000000005, 0.0000000005, 0.00000000005, 0.000000000005, 0.0000000000005, 0.00000000000005, 0.000000000000005, 0.0000000000000005, 0.00000000000000005, 0.000000000000000005, 0.0000000000000000005, 0.00000000000000000005, 0.000000000000000000005, 0.0000000000000000000005, 0.00000000000000000000005, 0.000000000000000000000005, 0.0000000000000000000000005, 0.00000000000000000000000005, 0.000000000000000000000000005, 0.0000000000000000000000000005, 0.00000000000000000000000000005, 0.000000000000000000000000000005, 0.0000000000000000000000000000005, 0.00000000000000000000000000000005, 0.000000000000000000000000000000005, 0.0000000000000000000000000000000005, 0.00000000000000000000000000000000005, 0.000000000000000000000000000000000005}, sizeof(strconv__dec_round));
	memmove(strconv__powers_of_10, (u64[18]){((u64)(1e0)), ((u64)(1e1)), ((u64)(1e2)), ((u64)(1e3)), ((u64)(1e4)), ((u64)(1e5)), ((u64)(1e6)), ((u64)(1e7)), ((u64)(1e8)), ((u64)(1e9)), ((u64)(1e10)), ((u64)(1e11)), ((u64)(1e12)), ((u64)(1e13)), ((u64)(1e14)), ((u64)(1e15)), ((u64)(1e16)), ((u64)(1e17))}, sizeof(strconv__powers_of_10));
	memmove(strconv__pow5_split_32, (u64[47]){((u64)(1152921504606846976)), ((u64)(1441151880758558720)), ((u64)(1801439850948198400)), ((u64)(2251799813685248000)), ((u64)(1407374883553280000)), ((u64)(1759218604441600000)), ((u64)(2199023255552000000)), ((u64)(1374389534720000000)), ((u64)(1717986918400000000)), ((u64)(2147483648000000000)), ((u64)(1342177280000000000)), ((u64)(1677721600000000000)), ((u64)(2097152000000000000)), ((u64)(1310720000000000000)), ((u64)(1638400000000000000)), ((u64)(2048000000000000000)), ((u64)(1280000000000000000)), ((u64)(1600000000000000000)), ((u64)(2000000000000000000)), ((u64)(1250000000000000000)), ((u64)(1562500000000000000)), ((u64)(1953125000000000000)), ((u64)(1220703125000000000)), ((u64)(1525878906250000000)), ((u64)(1907348632812500000)), ((u64)(1192092895507812500)), ((u64)(1490116119384765625)), ((u64)(1862645149230957031)), ((u64)(1164153218269348144)), ((u64)(1455191522836685180)), ((u64)(1818989403545856475)), ((u64)(2273736754432320594)), ((u64)(1421085471520200371)), ((u64)(1776356839400250464)), ((u64)(2220446049250313080)), ((u64)(1387778780781445675)), ((u64)(1734723475976807094)), ((u64)(2168404344971008868)), ((u64)(1355252715606880542)), ((u64)(1694065894508600678)), ((u64)(2117582368135750847)), ((u64)(1323488980084844279)), ((u64)(1654361225106055349)), ((u64)(2067951531382569187)), ((u64)(1292469707114105741)), ((u64)(1615587133892632177)), ((u64)(2019483917365790221))}, sizeof(strconv__pow5_split_32));
	memmove(strconv__pow5_inv_split_32, (u64[31]){((u64)(576460752303423489)), ((u64)(461168601842738791)), ((u64)(368934881474191033)), ((u64)(295147905179352826)), ((u64)(472236648286964522)), ((u64)(377789318629571618)), ((u64)(302231454903657294)), ((u64)(483570327845851670)), ((u64)(386856262276681336)), ((u64)(309485009821345069)), ((u64)(495176015714152110)), ((u64)(396140812571321688)), ((u64)(316912650057057351)), ((u64)(507060240091291761)), ((u64)(405648192073033409)), ((u64)(324518553658426727)), ((u64)(519229685853482763)), ((u64)(415383748682786211)), ((u64)(332306998946228969)), ((u64)(531691198313966350)), ((u64)(425352958651173080)), ((u64)(340282366920938464)), ((u64)(544451787073501542)), ((u64)(435561429658801234)), ((u64)(348449143727040987)), ((u64)(557518629963265579)), ((u64)(446014903970612463)), ((u64)(356811923176489971)), ((u64)(570899077082383953)), ((u64)(456719261665907162)), ((u64)(365375409332725730))}, sizeof(strconv__pow5_inv_split_32));
	memmove(strconv__pow5_split_64_x, (u64[652]){((u64)(0x0000000000000000)), ((u64)(0x0100000000000000)), ((u64)(0x0000000000000000)), ((u64)(0x0140000000000000)), ((u64)(0x0000000000000000)), ((u64)(0x0190000000000000)), ((u64)(0x0000000000000000)), ((u64)(0x01f4000000000000)), ((u64)(0x0000000000000000)), ((u64)(0x0138800000000000)), ((u64)(0x0000000000000000)), ((u64)(0x0186a00000000000)), ((u64)(0x0000000000000000)), ((u64)(0x01e8480000000000)), ((u64)(0x0000000000000000)), ((u64)(0x01312d0000000000)), ((u64)(0x0000000000000000)), ((u64)(0x017d784000000000)), ((u64)(0x0000000000000000)), ((u64)(0x01dcd65000000000)), ((u64)(0x0000000000000000)), ((u64)(0x012a05f200000000)), ((u64)(0x0000000000000000)), ((u64)(0x0174876e80000000)), ((u64)(0x0000000000000000)), ((u64)(0x01d1a94a20000000)), ((u64)(0x0000000000000000)), ((u64)(0x012309ce54000000)), ((u64)(0x0000000000000000)), ((u64)(0x016bcc41e9000000)), ((u64)(0x0000000000000000)), ((u64)(0x01c6bf5263400000)), ((u64)(0x0000000000000000)), ((u64)(0x011c37937e080000)), ((u64)(0x0000000000000000)), ((u64)(0x016345785d8a0000)), ((u64)(0x0000000000000000)), ((u64)(0x01bc16d674ec8000)), ((u64)(0x0000000000000000)), ((u64)(0x01158e460913d000)), ((u64)(0x0000000000000000)), ((u64)(0x015af1d78b58c400)), ((u64)(0x0000000000000000)), ((u64)(0x01b1ae4d6e2ef500)), ((u64)(0x0000000000000000)), ((u64)(0x010f0cf064dd5920)), ((u64)(0x0000000000000000)), ((u64)(0x0152d02c7e14af68)), ((u64)(0x0000000000000000)), ((u64)(0x01a784379d99db42)), ((u64)(0x4000000000000000)), ((u64)(0x0108b2a2c2802909)), ((u64)(0x9000000000000000)), ((u64)(0x014adf4b7320334b)), ((u64)(0x7400000000000000)), ((u64)(0x019d971e4fe8401e)), ((u64)(0x0880000000000000)), ((u64)(0x01027e72f1f12813)), ((u64)(0xcaa0000000000000)), ((u64)(0x01431e0fae6d7217)), ((u64)(0xbd48000000000000)), ((u64)(0x0193e5939a08ce9d)), ((u64)(0x2c9a000000000000)), ((u64)(0x01f8def8808b0245)), ((u64)(0x3be0400000000000)), ((u64)(0x013b8b5b5056e16b)), ((u64)(0x0ad8500000000000)), ((u64)(0x018a6e32246c99c6)), ((u64)(0x8d8e640000000000)), ((u64)(0x01ed09bead87c037)), ((u64)(0xb878fe8000000000)), ((u64)(0x013426172c74d822)), ((u64)(0x66973e2000000000)), ((u64)(0x01812f9cf7920e2b)), ((u64)(0x403d0da800000000)), ((u64)(0x01e17b84357691b6)), ((u64)(0xe826288900000000)), ((u64)(0x012ced32a16a1b11)), ((u64)(0x622fb2ab40000000)), ((u64)(0x0178287f49c4a1d6)), ((u64)(0xfabb9f5610000000)), ((u64)(0x01d6329f1c35ca4b)), ((u64)(0x7cb54395ca000000)), ((u64)(0x0125dfa371a19e6f)), ((u64)(0x5be2947b3c800000)), ((u64)(0x016f578c4e0a060b)), ((u64)(0x32db399a0ba00000)), ((u64)(0x01cb2d6f618c878e)), ((u64)(0xdfc9040047440000)), ((u64)(0x011efc659cf7d4b8)), ((u64)(0x17bb450059150000)), ((u64)(0x0166bb7f0435c9e7)), ((u64)(0xddaa16406f5a4000)), ((u64)(0x01c06a5ec5433c60)), ((u64)(0x8a8a4de845986800)), ((u64)(0x0118427b3b4a05bc)), ((u64)(0xad2ce16256fe8200)), ((u64)(0x015e531a0a1c872b)), ((u64)(0x987819baecbe2280)), ((u64)(0x01b5e7e08ca3a8f6)), ((u64)(0x1f4b1014d3f6d590)), ((u64)(0x0111b0ec57e6499a)), ((u64)(0xa71dd41a08f48af4)), ((u64)(0x01561d276ddfdc00)), ((u64)(0xd0e549208b31adb1)), ((u64)(0x01aba4714957d300)), ((u64)(0x828f4db456ff0c8e)), ((u64)(0x010b46c6cdd6e3e0)), ((u64)(0xa33321216cbecfb2)), ((u64)(0x014e1878814c9cd8)), ((u64)(0xcbffe969c7ee839e)), ((u64)(0x01a19e96a19fc40e)), ((u64)(0x3f7ff1e21cf51243)), ((u64)(0x0105031e2503da89)), ((u64)(0x8f5fee5aa43256d4)), ((u64)(0x014643e5ae44d12b)), ((u64)(0x7337e9f14d3eec89)), ((u64)(0x0197d4df19d60576)), ((u64)(0x1005e46da08ea7ab)), ((u64)(0x01fdca16e04b86d4)), ((u64)(0x8a03aec4845928cb)), ((u64)(0x013e9e4e4c2f3444)), ((u64)(0xac849a75a56f72fd)), ((u64)(0x018e45e1df3b0155)), ((u64)(0x17a5c1130ecb4fbd)), ((u64)(0x01f1d75a5709c1ab)), ((u64)(0xeec798abe93f11d6)), ((u64)(0x013726987666190a)), ((u64)(0xaa797ed6e38ed64b)), ((u64)(0x0184f03e93ff9f4d)), ((u64)(0x1517de8c9c728bde)), ((u64)(0x01e62c4e38ff8721)), ((u64)(0xad2eeb17e1c7976b)), ((u64)(0x012fdbb0e39fb474)), ((u64)(0xd87aa5ddda397d46)), ((u64)(0x017bd29d1c87a191)), ((u64)(0x4e994f5550c7dc97)), ((u64)(0x01dac74463a989f6)), ((u64)(0xf11fd195527ce9de)), ((u64)(0x0128bc8abe49f639)), ((u64)(0x6d67c5faa71c2456)), ((u64)(0x0172ebad6ddc73c8)), ((u64)(0x88c1b77950e32d6c)), ((u64)(0x01cfa698c95390ba)), ((u64)(0x957912abd28dfc63)), ((u64)(0x0121c81f7dd43a74)), ((u64)(0xbad75756c7317b7c)), ((u64)(0x016a3a275d494911)), ((u64)(0x298d2d2c78fdda5b)), ((u64)(0x01c4c8b1349b9b56)), ((u64)(0xd9f83c3bcb9ea879)), ((u64)(0x011afd6ec0e14115)), ((u64)(0x50764b4abe865297)), ((u64)(0x0161bcca7119915b)), ((u64)(0x2493de1d6e27e73d)), ((u64)(0x01ba2bfd0d5ff5b2)), ((u64)(0x56dc6ad264d8f086)), ((u64)(0x01145b7e285bf98f)), ((u64)(0x2c938586fe0f2ca8)), ((u64)(0x0159725db272f7f3)), ((u64)(0xf7b866e8bd92f7d2)), ((u64)(0x01afcef51f0fb5ef)), ((u64)(0xfad34051767bdae3)), ((u64)(0x010de1593369d1b5)), ((u64)(0x79881065d41ad19c)), ((u64)(0x015159af80444623)), ((u64)(0x57ea147f49218603)), ((u64)(0x01a5b01b605557ac)), ((u64)(0xb6f24ccf8db4f3c1)), ((u64)(0x01078e111c3556cb)), ((u64)(0xa4aee003712230b2)), ((u64)(0x014971956342ac7e)), ((u64)(0x4dda98044d6abcdf)), ((u64)(0x019bcdfabc13579e)), ((u64)(0xf0a89f02b062b60b)), ((u64)(0x010160bcb58c16c2)), ((u64)(0xacd2c6c35c7b638e)), ((u64)(0x0141b8ebe2ef1c73)), ((u64)(0x98077874339a3c71)), ((u64)(0x01922726dbaae390)), ((u64)(0xbe0956914080cb8e)), ((u64)(0x01f6b0f092959c74)), ((u64)(0xf6c5d61ac8507f38)), ((u64)(0x013a2e965b9d81c8)), ((u64)(0x34774ba17a649f07)), ((u64)(0x0188ba3bf284e23b)), ((u64)(0x01951e89d8fdc6c8)), ((u64)(0x01eae8caef261aca)), ((u64)(0x40fd3316279e9c3d)), ((u64)(0x0132d17ed577d0be)), ((u64)(0xd13c7fdbb186434c)), ((u64)(0x017f85de8ad5c4ed)), ((u64)(0x458b9fd29de7d420)), ((u64)(0x01df67562d8b3629)), ((u64)(0xcb7743e3a2b0e494)), ((u64)(0x012ba095dc7701d9)), ((u64)(0x3e5514dc8b5d1db9)), ((u64)(0x017688bb5394c250)), ((u64)(0x4dea5a13ae346527)), ((u64)(0x01d42aea2879f2e4)), ((u64)(0xb0b2784c4ce0bf38)), ((u64)(0x01249ad2594c37ce)), ((u64)(0x5cdf165f6018ef06)), ((u64)(0x016dc186ef9f45c2)), ((u64)(0xf416dbf7381f2ac8)), ((u64)(0x01c931e8ab871732)), ((u64)(0xd88e497a83137abd)), ((u64)(0x011dbf316b346e7f)), ((u64)(0xceb1dbd923d8596c)), ((u64)(0x01652efdc6018a1f)), ((u64)(0xc25e52cf6cce6fc7)), ((u64)(0x01be7abd3781eca7)), ((u64)(0xd97af3c1a40105dc)), ((u64)(0x01170cb642b133e8)), ((u64)(0x0fd9b0b20d014754)), ((u64)(0x015ccfe3d35d80e3)), ((u64)(0xd3d01cde90419929)), ((u64)(0x01b403dcc834e11b)), ((u64)(0x6462120b1a28ffb9)), ((u64)(0x01108269fd210cb1)), ((u64)(0xbd7a968de0b33fa8)), ((u64)(0x0154a3047c694fdd)), ((u64)(0x2cd93c3158e00f92)), ((u64)(0x01a9cbc59b83a3d5)), ((u64)(0x3c07c59ed78c09bb)), ((u64)(0x010a1f5b81324665)), ((u64)(0x8b09b7068d6f0c2a)), ((u64)(0x014ca732617ed7fe)), ((u64)(0x2dcc24c830cacf34)), ((u64)(0x019fd0fef9de8dfe)), ((u64)(0xdc9f96fd1e7ec180)), ((u64)(0x0103e29f5c2b18be)), ((u64)(0x93c77cbc661e71e1)), ((u64)(0x0144db473335deee)), ((u64)(0x38b95beb7fa60e59)), ((u64)(0x01961219000356aa)), ((u64)(0xc6e7b2e65f8f91ef)), ((u64)(0x01fb969f40042c54)), ((u64)(0xfc50cfcffbb9bb35)), ((u64)(0x013d3e2388029bb4)), ((u64)(0x3b6503c3faa82a03)), ((u64)(0x018c8dac6a0342a2)), ((u64)(0xca3e44b4f9523484)), ((u64)(0x01efb1178484134a)), ((u64)(0xbe66eaf11bd360d2)), ((u64)(0x0135ceaeb2d28c0e)), ((u64)(0x6e00a5ad62c83907)), ((u64)(0x0183425a5f872f12)), ((u64)(0x0980cf18bb7a4749)), ((u64)(0x01e412f0f768fad7)), ((u64)(0x65f0816f752c6c8d)), ((u64)(0x012e8bd69aa19cc6)), ((u64)(0xff6ca1cb527787b1)), ((u64)(0x017a2ecc414a03f7)), ((u64)(0xff47ca3e2715699d)), ((u64)(0x01d8ba7f519c84f5)), ((u64)(0xbf8cde66d86d6202)), ((u64)(0x0127748f9301d319)), ((u64)(0x2f7016008e88ba83)), ((u64)(0x017151b377c247e0)), ((u64)(0x3b4c1b80b22ae923)), ((u64)(0x01cda62055b2d9d8)), ((u64)(0x250f91306f5ad1b6)), ((u64)(0x012087d4358fc827)), ((u64)(0xee53757c8b318623)), ((u64)(0x0168a9c942f3ba30)), ((u64)(0x29e852dbadfde7ac)), ((u64)(0x01c2d43b93b0a8bd)), ((u64)(0x3a3133c94cbeb0cc)), ((u64)(0x0119c4a53c4e6976)), ((u64)(0xc8bd80bb9fee5cff)), ((u64)(0x016035ce8b6203d3)), ((u64)(0xbaece0ea87e9f43e)), ((u64)(0x01b843422e3a84c8)), ((u64)(0x74d40c9294f238a7)), ((u64)(0x01132a095ce492fd)), ((u64)(0xd2090fb73a2ec6d1)), ((u64)(0x0157f48bb41db7bc)), ((u64)(0x068b53a508ba7885)), ((u64)(0x01adf1aea12525ac)), ((u64)(0x8417144725748b53)), ((u64)(0x010cb70d24b7378b)), ((u64)(0x651cd958eed1ae28)), ((u64)(0x014fe4d06de5056e)), ((u64)(0xfe640faf2a8619b2)), ((u64)(0x01a3de04895e46c9)), ((u64)(0x3efe89cd7a93d00f)), ((u64)(0x01066ac2d5daec3e)), ((u64)(0xcebe2c40d938c413)), ((u64)(0x014805738b51a74d)), ((u64)(0x426db7510f86f518)), ((u64)(0x019a06d06e261121)), ((u64)(0xc9849292a9b4592f)), ((u64)(0x0100444244d7cab4)), ((u64)(0xfbe5b73754216f7a)), ((u64)(0x01405552d60dbd61)), ((u64)(0x7adf25052929cb59)), ((u64)(0x01906aa78b912cba)), ((u64)(0x1996ee4673743e2f)), ((u64)(0x01f485516e7577e9)), ((u64)(0xaffe54ec0828a6dd)), ((u64)(0x0138d352e5096af1)), ((u64)(0x1bfdea270a32d095)), ((u64)(0x018708279e4bc5ae)), ((u64)(0xa2fd64b0ccbf84ba)), ((u64)(0x01e8ca3185deb719)), ((u64)(0x05de5eee7ff7b2f4)), ((u64)(0x01317e5ef3ab3270)), ((u64)(0x0755f6aa1ff59fb1)), ((u64)(0x017dddf6b095ff0c)), ((u64)(0x092b7454a7f3079e)), ((u64)(0x01dd55745cbb7ecf)), ((u64)(0x65bb28b4e8f7e4c3)), ((u64)(0x012a5568b9f52f41)), ((u64)(0xbf29f2e22335ddf3)), ((u64)(0x0174eac2e8727b11)), ((u64)(0x2ef46f9aac035570)), ((u64)(0x01d22573a28f19d6)), ((u64)(0xdd58c5c0ab821566)), ((u64)(0x0123576845997025)), ((u64)(0x54aef730d6629ac0)), ((u64)(0x016c2d4256ffcc2f)), ((u64)(0x29dab4fd0bfb4170)), ((u64)(0x01c73892ecbfbf3b)), ((u64)(0xfa28b11e277d08e6)), ((u64)(0x011c835bd3f7d784)), ((u64)(0x38b2dd65b15c4b1f)), ((u64)(0x0163a432c8f5cd66)), ((u64)(0xc6df94bf1db35de7)), ((u64)(0x01bc8d3f7b3340bf)), ((u64)(0xdc4bbcf772901ab0)), ((u64)(0x0115d847ad000877)), ((u64)(0xd35eac354f34215c)), ((u64)(0x015b4e5998400a95)), ((u64)(0x48365742a30129b4)), ((u64)(0x01b221effe500d3b)), ((u64)(0x0d21f689a5e0ba10)), ((u64)(0x010f5535fef20845)), ((u64)(0x506a742c0f58e894)), ((u64)(0x01532a837eae8a56)), ((u64)(0xe4851137132f22b9)), ((u64)(0x01a7f5245e5a2ceb)), ((u64)(0x6ed32ac26bfd75b4)), ((u64)(0x0108f936baf85c13)), ((u64)(0x4a87f57306fcd321)), ((u64)(0x014b378469b67318)), ((u64)(0x5d29f2cfc8bc07e9)), ((u64)(0x019e056584240fde)), ((u64)(0xfa3a37c1dd7584f1)), ((u64)(0x0102c35f729689ea)), ((u64)(0xb8c8c5b254d2e62e)), ((u64)(0x014374374f3c2c65)), ((u64)(0x26faf71eea079fb9)), ((u64)(0x01945145230b377f)), ((u64)(0xf0b9b4e6a48987a8)), ((u64)(0x01f965966bce055e)), ((u64)(0x5674111026d5f4c9)), ((u64)(0x013bdf7e0360c35b)), ((u64)(0x2c111554308b71fb)), ((u64)(0x018ad75d8438f432)), ((u64)(0xb7155aa93cae4e7a)), ((u64)(0x01ed8d34e547313e)), ((u64)(0x326d58a9c5ecf10c)), ((u64)(0x013478410f4c7ec7)), ((u64)(0xff08aed437682d4f)), ((u64)(0x01819651531f9e78)), ((u64)(0x3ecada89454238a3)), ((u64)(0x01e1fbe5a7e78617)), ((u64)(0x873ec895cb496366)), ((u64)(0x012d3d6f88f0b3ce)), ((u64)(0x290e7abb3e1bbc3f)), ((u64)(0x01788ccb6b2ce0c2)), ((u64)(0xb352196a0da2ab4f)), ((u64)(0x01d6affe45f818f2)), ((u64)(0xb0134fe24885ab11)), ((u64)(0x01262dfeebbb0f97)), ((u64)(0x9c1823dadaa715d6)), ((u64)(0x016fb97ea6a9d37d)), ((u64)(0x031e2cd19150db4b)), ((u64)(0x01cba7de5054485d)), ((u64)(0x21f2dc02fad2890f)), ((u64)(0x011f48eaf234ad3a)), ((u64)(0xaa6f9303b9872b53)), ((u64)(0x01671b25aec1d888)), ((u64)(0xd50b77c4a7e8f628)), ((u64)(0x01c0e1ef1a724eaa)), ((u64)(0xc5272adae8f199d9)), ((u64)(0x01188d357087712a)), ((u64)(0x7670f591a32e004f)), ((u64)(0x015eb082cca94d75)), ((u64)(0xd40d32f60bf98063)), ((u64)(0x01b65ca37fd3a0d2)), ((u64)(0xc4883fd9c77bf03e)), ((u64)(0x0111f9e62fe44483)), ((u64)(0xb5aa4fd0395aec4d)), ((u64)(0x0156785fbbdd55a4)), ((u64)(0xe314e3c447b1a760)), ((u64)(0x01ac1677aad4ab0d)), ((u64)(0xaded0e5aaccf089c)), ((u64)(0x010b8e0acac4eae8)), ((u64)(0xd96851f15802cac3)), ((u64)(0x014e718d7d7625a2)), ((u64)(0x8fc2666dae037d74)), ((u64)(0x01a20df0dcd3af0b)), ((u64)(0x39d980048cc22e68)), ((u64)(0x010548b68a044d67)), ((u64)(0x084fe005aff2ba03)), ((u64)(0x01469ae42c8560c1)), ((u64)(0x4a63d8071bef6883)), ((u64)(0x0198419d37a6b8f1)), ((u64)(0x9cfcce08e2eb42a4)), ((u64)(0x01fe52048590672d)), ((u64)(0x821e00c58dd309a7)), ((u64)(0x013ef342d37a407c)), ((u64)(0xa2a580f6f147cc10)), ((u64)(0x018eb0138858d09b)), ((u64)(0x8b4ee134ad99bf15)), ((u64)(0x01f25c186a6f04c2)), ((u64)(0x97114cc0ec80176d)), ((u64)(0x0137798f428562f9)), ((u64)(0xfcd59ff127a01d48)), ((u64)(0x018557f31326bbb7)), ((u64)(0xfc0b07ed7188249a)), ((u64)(0x01e6adefd7f06aa5)), ((u64)(0xbd86e4f466f516e0)), ((u64)(0x01302cb5e6f642a7)), ((u64)(0xace89e3180b25c98)), ((u64)(0x017c37e360b3d351)), ((u64)(0x1822c5bde0def3be)), ((u64)(0x01db45dc38e0c826)), ((u64)(0xcf15bb96ac8b5857)), ((u64)(0x01290ba9a38c7d17)), ((u64)(0xc2db2a7c57ae2e6d)), ((u64)(0x01734e940c6f9c5d)), ((u64)(0x3391f51b6d99ba08)), ((u64)(0x01d022390f8b8375)), ((u64)(0x403b393124801445)), ((u64)(0x01221563a9b73229)), ((u64)(0x904a077d6da01956)), ((u64)(0x016a9abc9424feb3)), ((u64)(0x745c895cc9081fac)), ((u64)(0x01c5416bb92e3e60)), ((u64)(0x48b9d5d9fda513cb)), ((u64)(0x011b48e353bce6fc)), ((u64)(0x5ae84b507d0e58be)), ((u64)(0x01621b1c28ac20bb)), ((u64)(0x31a25e249c51eeee)), ((u64)(0x01baa1e332d728ea)), ((u64)(0x5f057ad6e1b33554)), ((u64)(0x0114a52dffc67992)), ((u64)(0xf6c6d98c9a2002aa)), ((u64)(0x0159ce797fb817f6)), ((u64)(0xb4788fefc0a80354)), ((u64)(0x01b04217dfa61df4)), ((u64)(0xf0cb59f5d8690214)), ((u64)(0x010e294eebc7d2b8)), ((u64)(0x2cfe30734e83429a)), ((u64)(0x0151b3a2a6b9c767)), ((u64)(0xf83dbc9022241340)), ((u64)(0x01a6208b50683940)), ((u64)(0x9b2695da15568c08)), ((u64)(0x0107d457124123c8)), ((u64)(0xc1f03b509aac2f0a)), ((u64)(0x0149c96cd6d16cba)), ((u64)(0x726c4a24c1573acd)), ((u64)(0x019c3bc80c85c7e9)), ((u64)(0xe783ae56f8d684c0)), ((u64)(0x0101a55d07d39cf1)), ((u64)(0x616499ecb70c25f0)), ((u64)(0x01420eb449c8842e)), ((u64)(0xf9bdc067e4cf2f6c)), ((u64)(0x019292615c3aa539)), ((u64)(0x782d3081de02fb47)), ((u64)(0x01f736f9b3494e88)), ((u64)(0x4b1c3e512ac1dd0c)), ((u64)(0x013a825c100dd115)), ((u64)(0x9de34de57572544f)), ((u64)(0x018922f31411455a)), ((u64)(0x455c215ed2cee963)), ((u64)(0x01eb6bafd91596b1)), ((u64)(0xcb5994db43c151de)), ((u64)(0x0133234de7ad7e2e)), ((u64)(0x7e2ffa1214b1a655)), ((u64)(0x017fec216198ddba)), ((u64)(0x1dbbf89699de0feb)), ((u64)(0x01dfe729b9ff1529)), ((u64)(0xb2957b5e202ac9f3)), ((u64)(0x012bf07a143f6d39)), ((u64)(0x1f3ada35a8357c6f)), ((u64)(0x0176ec98994f4888)), ((u64)(0x270990c31242db8b)), ((u64)(0x01d4a7bebfa31aaa)), ((u64)(0x5865fa79eb69c937)), ((u64)(0x0124e8d737c5f0aa)), ((u64)(0xee7f791866443b85)), ((u64)(0x016e230d05b76cd4)), ((u64)(0x2a1f575e7fd54a66)), ((u64)(0x01c9abd04725480a)), ((u64)(0x5a53969b0fe54e80)), ((u64)(0x011e0b622c774d06)), ((u64)(0xf0e87c41d3dea220)), ((u64)(0x01658e3ab7952047)), ((u64)(0xed229b5248d64aa8)), ((u64)(0x01bef1c9657a6859)), ((u64)(0x3435a1136d85eea9)), ((u64)(0x0117571ddf6c8138)), ((u64)(0x4143095848e76a53)), ((u64)(0x015d2ce55747a186)), ((u64)(0xd193cbae5b2144e8)), ((u64)(0x01b4781ead1989e7)), ((u64)(0xe2fc5f4cf8f4cb11)), ((u64)(0x0110cb132c2ff630)), ((u64)(0x1bbb77203731fdd5)), ((u64)(0x0154fdd7f73bf3bd)), ((u64)(0x62aa54e844fe7d4a)), ((u64)(0x01aa3d4df50af0ac)), ((u64)(0xbdaa75112b1f0e4e)), ((u64)(0x010a6650b926d66b)), ((u64)(0xad15125575e6d1e2)), ((u64)(0x014cffe4e7708c06)), ((u64)(0x585a56ead360865b)), ((u64)(0x01a03fde214caf08)), ((u64)(0x37387652c41c53f8)), ((u64)(0x010427ead4cfed65)), ((u64)(0x850693e7752368f7)), ((u64)(0x014531e58a03e8be)), ((u64)(0x264838e1526c4334)), ((u64)(0x01967e5eec84e2ee)), ((u64)(0xafda4719a7075402)), ((u64)(0x01fc1df6a7a61ba9)), ((u64)(0x0de86c7008649481)), ((u64)(0x013d92ba28c7d14a)), ((u64)(0x9162878c0a7db9a1)), ((u64)(0x018cf768b2f9c59c)), ((u64)(0xb5bb296f0d1d280a)), ((u64)(0x01f03542dfb83703)), ((u64)(0x5194f9e568323906)), ((u64)(0x01362149cbd32262)), ((u64)(0xe5fa385ec23ec747)), ((u64)(0x0183a99c3ec7eafa)), ((u64)(0x9f78c67672ce7919)), ((u64)(0x01e494034e79e5b9)), ((u64)(0x03ab7c0a07c10bb0)), ((u64)(0x012edc82110c2f94)), ((u64)(0x04965b0c89b14e9c)), ((u64)(0x017a93a2954f3b79)), ((u64)(0x45bbf1cfac1da243)), ((u64)(0x01d9388b3aa30a57)), ((u64)(0x8b957721cb92856a)), ((u64)(0x0127c35704a5e676)), ((u64)(0x2e7ad4ea3e7726c4)), ((u64)(0x0171b42cc5cf6014)), ((u64)(0x3a198a24ce14f075)), ((u64)(0x01ce2137f7433819)), ((u64)(0xc44ff65700cd1649)), ((u64)(0x0120d4c2fa8a030f)), ((u64)(0xb563f3ecc1005bdb)), ((u64)(0x016909f3b92c83d3)), ((u64)(0xa2bcf0e7f14072d2)), ((u64)(0x01c34c70a777a4c8)), ((u64)(0x65b61690f6c847c3)), ((u64)(0x011a0fc668aac6fd)), ((u64)(0xbf239c35347a59b4)), ((u64)(0x016093b802d578bc)), ((u64)(0xeeec83428198f021)), ((u64)(0x01b8b8a6038ad6eb)), ((u64)(0x7553d20990ff9615)), ((u64)(0x01137367c236c653)), ((u64)(0x52a8c68bf53f7b9a)), ((u64)(0x01585041b2c477e8)), ((u64)(0x6752f82ef28f5a81)), ((u64)(0x01ae64521f7595e2)), ((u64)(0x8093db1d57999890)), ((u64)(0x010cfeb353a97dad)), ((u64)(0xe0b8d1e4ad7ffeb4)), ((u64)(0x01503e602893dd18)), ((u64)(0x18e7065dd8dffe62)), ((u64)(0x01a44df832b8d45f)), ((u64)(0x6f9063faa78bfefd)), ((u64)(0x0106b0bb1fb384bb)), ((u64)(0x4b747cf9516efebc)), ((u64)(0x01485ce9e7a065ea)), ((u64)(0xde519c37a5cabe6b)), ((u64)(0x019a742461887f64)), ((u64)(0x0af301a2c79eb703)), ((u64)(0x01008896bcf54f9f)), ((u64)(0xcdafc20b798664c4)), ((u64)(0x0140aabc6c32a386)), ((u64)(0x811bb28e57e7fdf5)), ((u64)(0x0190d56b873f4c68)), ((u64)(0xa1629f31ede1fd72)), ((u64)(0x01f50ac6690f1f82)), ((u64)(0xa4dda37f34ad3e67)), ((u64)(0x013926bc01a973b1)), ((u64)(0x0e150c5f01d88e01)), ((u64)(0x0187706b0213d09e)), ((u64)(0x919a4f76c24eb181)), ((u64)(0x01e94c85c298c4c5)), ((u64)(0x7b0071aa39712ef1)), ((u64)(0x0131cfd3999f7afb)), ((u64)(0x59c08e14c7cd7aad)), ((u64)(0x017e43c8800759ba)), ((u64)(0xf030b199f9c0d958)), ((u64)(0x01ddd4baa0093028)), ((u64)(0x961e6f003c1887d7)), ((u64)(0x012aa4f4a405be19)), ((u64)(0xfba60ac04b1ea9cd)), ((u64)(0x01754e31cd072d9f)), ((u64)(0xfa8f8d705de65440)), ((u64)(0x01d2a1be4048f907)), ((u64)(0xfc99b8663aaff4a8)), ((u64)(0x0123a516e82d9ba4)), ((u64)(0x3bc0267fc95bf1d2)), ((u64)(0x016c8e5ca239028e)), ((u64)(0xcab0301fbbb2ee47)), ((u64)(0x01c7b1f3cac74331)), ((u64)(0x1eae1e13d54fd4ec)), ((u64)(0x011ccf385ebc89ff)), ((u64)(0xe659a598caa3ca27)), ((u64)(0x01640306766bac7e)), ((u64)(0x9ff00efefd4cbcb1)), ((u64)(0x01bd03c81406979e)), ((u64)(0x23f6095f5e4ff5ef)), ((u64)(0x0116225d0c841ec3)), ((u64)(0xecf38bb735e3f36a)), ((u64)(0x015baaf44fa52673)), ((u64)(0xe8306ea5035cf045)), ((u64)(0x01b295b1638e7010)), ((u64)(0x911e4527221a162b)), ((u64)(0x010f9d8ede39060a)), ((u64)(0x3565d670eaa09bb6)), ((u64)(0x015384f295c7478d)), ((u64)(0x82bf4c0d2548c2a3)), ((u64)(0x01a8662f3b391970)), ((u64)(0x51b78f88374d79a6)), ((u64)(0x01093fdd8503afe6)), ((u64)(0xe625736a4520d810)), ((u64)(0x014b8fd4e6449bdf)), ((u64)(0xdfaed044d6690e14)), ((u64)(0x019e73ca1fd5c2d7)), ((u64)(0xebcd422b0601a8cc)), ((u64)(0x0103085e53e599c6)), ((u64)(0xa6c092b5c78212ff)), ((u64)(0x0143ca75e8df0038)), ((u64)(0xd070b763396297bf)), ((u64)(0x0194bd136316c046)), ((u64)(0x848ce53c07bb3daf)), ((u64)(0x01f9ec583bdc7058)), ((u64)(0x52d80f4584d5068d)), ((u64)(0x013c33b72569c637)), ((u64)(0x278e1316e60a4831)), ((u64)(0x018b40a4eec437c5))}, sizeof(strconv__pow5_split_64_x));
	memmove(strconv__pow5_inv_split_64_x, (u64[584]){((u64)(0x0000000000000001)), ((u64)(0x0400000000000000)), ((u64)(0x3333333333333334)), ((u64)(0x0333333333333333)), ((u64)(0x28f5c28f5c28f5c3)), ((u64)(0x028f5c28f5c28f5c)), ((u64)(0xed916872b020c49c)), ((u64)(0x020c49ba5e353f7c)), ((u64)(0xaf4f0d844d013a93)), ((u64)(0x0346dc5d63886594)), ((u64)(0x8c3f3e0370cdc876)), ((u64)(0x029f16b11c6d1e10)), ((u64)(0xd698fe69270b06c5)), ((u64)(0x0218def416bdb1a6)), ((u64)(0xf0f4ca41d811a46e)), ((u64)(0x035afe535795e90a)), ((u64)(0xf3f70834acdae9f1)), ((u64)(0x02af31dc4611873b)), ((u64)(0x5cc5a02a23e254c1)), ((u64)(0x0225c17d04dad296)), ((u64)(0xfad5cd10396a2135)), ((u64)(0x036f9bfb3af7b756)), ((u64)(0xfbde3da69454e75e)), ((u64)(0x02bfaffc2f2c92ab)), ((u64)(0x2fe4fe1edd10b918)), ((u64)(0x0232f33025bd4223)), ((u64)(0x4ca19697c81ac1bf)), ((u64)(0x0384b84d092ed038)), ((u64)(0x3d4e1213067bce33)), ((u64)(0x02d09370d4257360)), ((u64)(0x643e74dc052fd829)), ((u64)(0x024075f3dceac2b3)), ((u64)(0x6d30baf9a1e626a7)), ((u64)(0x039a5652fb113785)), ((u64)(0x2426fbfae7eb5220)), ((u64)(0x02e1dea8c8da92d1)), ((u64)(0x1cebfcc8b9890e80)), ((u64)(0x024e4bba3a487574)), ((u64)(0x94acc7a78f41b0cc)), ((u64)(0x03b07929f6da5586)), ((u64)(0xaa23d2ec729af3d7)), ((u64)(0x02f394219248446b)), ((u64)(0xbb4fdbf05baf2979)), ((u64)(0x025c768141d369ef)), ((u64)(0xc54c931a2c4b758d)), ((u64)(0x03c7240202ebdcb2)), ((u64)(0x9dd6dc14f03c5e0b)), ((u64)(0x0305b66802564a28)), ((u64)(0x4b1249aa59c9e4d6)), ((u64)(0x026af8533511d4ed)), ((u64)(0x44ea0f76f60fd489)), ((u64)(0x03de5a1ebb4fbb15)), ((u64)(0x6a54d92bf80caa07)), ((u64)(0x0318481895d96277)), ((u64)(0x21dd7a89933d54d2)), ((u64)(0x0279d346de4781f9)), ((u64)(0x362f2a75b8622150)), ((u64)(0x03f61ed7ca0c0328)), ((u64)(0xf825bb91604e810d)), ((u64)(0x032b4bdfd4d668ec)), ((u64)(0xc684960de6a5340b)), ((u64)(0x0289097fdd7853f0)), ((u64)(0xd203ab3e521dc33c)), ((u64)(0x02073accb12d0ff3)), ((u64)(0xe99f7863b696052c)), ((u64)(0x033ec47ab514e652)), ((u64)(0x87b2c6b62bab3757)), ((u64)(0x02989d2ef743eb75)), ((u64)(0xd2f56bc4efbc2c45)), ((u64)(0x0213b0f25f69892a)), ((u64)(0x1e55793b192d13a2)), ((u64)(0x0352b4b6ff0f41de)), ((u64)(0x4b77942f475742e8)), ((u64)(0x02a8909265a5ce4b)), ((u64)(0xd5f9435905df68ba)), ((u64)(0x022073a8515171d5)), ((u64)(0x565b9ef4d6324129)), ((u64)(0x03671f73b54f1c89)), ((u64)(0xdeafb25d78283421)), ((u64)(0x02b8e5f62aa5b06d)), ((u64)(0x188c8eb12cecf681)), ((u64)(0x022d84c4eeeaf38b)), ((u64)(0x8dadb11b7b14bd9b)), ((u64)(0x037c07a17e44b8de)), ((u64)(0x7157c0e2c8dd647c)), ((u64)(0x02c99fb46503c718)), ((u64)(0x8ddfcd823a4ab6ca)), ((u64)(0x023ae629ea696c13)), ((u64)(0x1632e269f6ddf142)), ((u64)(0x0391704310a8acec)), ((u64)(0x44f581ee5f17f435)), ((u64)(0x02dac035a6ed5723)), ((u64)(0x372ace584c1329c4)), ((u64)(0x024899c4858aac1c)), ((u64)(0xbeaae3c079b842d3)), ((u64)(0x03a75c6da27779c6)), ((u64)(0x6555830061603576)), ((u64)(0x02ec49f14ec5fb05)), ((u64)(0xb7779c004de6912b)), ((u64)(0x0256a18dd89e626a)), ((u64)(0xf258f99a163db512)), ((u64)(0x03bdcf495a9703dd)), ((u64)(0x5b7a614811caf741)), ((u64)(0x02fe3f6de212697e)), ((u64)(0xaf951aa00e3bf901)), ((u64)(0x0264ff8b1b41edfe)), ((u64)(0x7f54f7667d2cc19b)), ((u64)(0x03d4cc11c5364997)), ((u64)(0x32aa5f8530f09ae3)), ((u64)(0x0310a3416a91d479)), ((u64)(0xf55519375a5a1582)), ((u64)(0x0273b5cdeedb1060)), ((u64)(0xbbbb5b8bc3c3559d)), ((u64)(0x03ec56164af81a34)), ((u64)(0x2fc916096969114a)), ((u64)(0x03237811d593482a)), ((u64)(0x596dab3ababa743c)), ((u64)(0x0282c674aadc39bb)), ((u64)(0x478aef622efb9030)), ((u64)(0x0202385d557cfafc)), ((u64)(0xd8de4bd04b2c19e6)), ((u64)(0x0336c0955594c4c6)), ((u64)(0xad7ea30d08f014b8)), ((u64)(0x029233aaaadd6a38)), ((u64)(0x24654f3da0c01093)), ((u64)(0x020e8fbbbbe454fa)), ((u64)(0x3a3bb1fc346680eb)), ((u64)(0x034a7f92c63a2190)), ((u64)(0x94fc8e635d1ecd89)), ((u64)(0x02a1ffa89e94e7a6)), ((u64)(0xaa63a51c4a7f0ad4)), ((u64)(0x021b32ed4baa52eb)), ((u64)(0xdd6c3b607731aaed)), ((u64)(0x035eb7e212aa1e45)), ((u64)(0x1789c919f8f488bd)), ((u64)(0x02b22cb4dbbb4b6b)), ((u64)(0xac6e3a7b2d906d64)), ((u64)(0x022823c3e2fc3c55)), ((u64)(0x13e390c515b3e23a)), ((u64)(0x03736c6c9e606089)), ((u64)(0xdcb60d6a77c31b62)), ((u64)(0x02c2bd23b1e6b3a0)), ((u64)(0x7d5e7121f968e2b5)), ((u64)(0x0235641c8e52294d)), ((u64)(0xc8971b698f0e3787)), ((u64)(0x0388a02db0837548)), ((u64)(0xa078e2bad8d82c6c)), ((u64)(0x02d3b357c0692aa0)), ((u64)(0xe6c71bc8ad79bd24)), ((u64)(0x0242f5dfcd20eee6)), ((u64)(0x0ad82c7448c2c839)), ((u64)(0x039e5632e1ce4b0b)), ((u64)(0x3be023903a356cfa)), ((u64)(0x02e511c24e3ea26f)), ((u64)(0x2fe682d9c82abd95)), ((u64)(0x0250db01d8321b8c)), ((u64)(0x4ca4048fa6aac8ee)), ((u64)(0x03b4919c8d1cf8e0)), ((u64)(0x3d5003a61eef0725)), ((u64)(0x02f6dae3a4172d80)), ((u64)(0x9773361e7f259f51)), ((u64)(0x025f1582e9ac2466)), ((u64)(0x8beb89ca6508fee8)), ((u64)(0x03cb559e42ad070a)), ((u64)(0x6fefa16eb73a6586)), ((u64)(0x0309114b688a6c08)), ((u64)(0xf3261abef8fb846b)), ((u64)(0x026da76f86d52339)), ((u64)(0x51d691318e5f3a45)), ((u64)(0x03e2a57f3e21d1f6)), ((u64)(0x0e4540f471e5c837)), ((u64)(0x031bb798fe8174c5)), ((u64)(0xd8376729f4b7d360)), ((u64)(0x027c92e0cb9ac3d0)), ((u64)(0xf38bd84321261eff)), ((u64)(0x03fa849adf5e061a)), ((u64)(0x293cad0280eb4bff)), ((u64)(0x032ed07be5e4d1af)), ((u64)(0xedca240200bc3ccc)), ((u64)(0x028bd9fcb7ea4158)), ((u64)(0xbe3b50019a3030a4)), ((u64)(0x02097b309321cde0)), ((u64)(0xc9f88002904d1a9f)), ((u64)(0x03425eb41e9c7c9a)), ((u64)(0x3b2d3335403daee6)), ((u64)(0x029b7ef67ee396e2)), ((u64)(0x95bdc291003158b8)), ((u64)(0x0215ff2b98b6124e)), ((u64)(0x892f9db4cd1bc126)), ((u64)(0x035665128df01d4a)), ((u64)(0x07594af70a7c9a85)), ((u64)(0x02ab840ed7f34aa2)), ((u64)(0x6c476f2c0863aed1)), ((u64)(0x0222d00bdff5d54e)), ((u64)(0x13a57eacda3917b4)), ((u64)(0x036ae67966562217)), ((u64)(0x0fb7988a482dac90)), ((u64)(0x02bbeb9451de81ac)), ((u64)(0xd95fad3b6cf156da)), ((u64)(0x022fefa9db1867bc)), ((u64)(0xf565e1f8ae4ef15c)), ((u64)(0x037fe5dc91c0a5fa)), ((u64)(0x911e4e608b725ab0)), ((u64)(0x02ccb7e3a7cd5195)), ((u64)(0xda7ea51a0928488d)), ((u64)(0x023d5fe9530aa7aa)), ((u64)(0xf7310829a8407415)), ((u64)(0x039566421e7772aa)), ((u64)(0x2c2739baed005cde)), ((u64)(0x02ddeb68185f8eef)), ((u64)(0xbcec2e2f24004a4b)), ((u64)(0x024b22b9ad193f25)), ((u64)(0x94ad16b1d333aa11)), ((u64)(0x03ab6ac2ae8ecb6f)), ((u64)(0xaa241227dc2954db)), ((u64)(0x02ef889bbed8a2bf)), ((u64)(0x54e9a81fe35443e2)), ((u64)(0x02593a163246e899)), ((u64)(0x2175d9cc9eed396a)), ((u64)(0x03c1f689ea0b0dc2)), ((u64)(0xe7917b0a18bdc788)), ((u64)(0x03019207ee6f3e34)), ((u64)(0xb9412f3b46fe393a)), ((u64)(0x0267a8065858fe90)), ((u64)(0xf535185ed7fd285c)), ((u64)(0x03d90cd6f3c1974d)), ((u64)(0xc42a79e57997537d)), ((u64)(0x03140a458fce12a4)), ((u64)(0x03552e512e12a931)), ((u64)(0x02766e9e0ca4dbb7)), ((u64)(0x9eeeb081e3510eb4)), ((u64)(0x03f0b0fce107c5f1)), ((u64)(0x4bf226ce4f740bc3)), ((u64)(0x0326f3fd80d304c1)), ((u64)(0xa3281f0b72c33c9c)), ((u64)(0x02858ffe00a8d09a)), ((u64)(0x1c2018d5f568fd4a)), ((u64)(0x020473319a20a6e2)), ((u64)(0xf9ccf48988a7fba9)), ((u64)(0x033a51e8f69aa49c)), ((u64)(0xfb0a5d3ad3b99621)), ((u64)(0x02950e53f87bb6e3)), ((u64)(0x2f3b7dc8a96144e7)), ((u64)(0x0210d8432d2fc583)), ((u64)(0xe52bfc7442353b0c)), ((u64)(0x034e26d1e1e608d1)), ((u64)(0xb756639034f76270)), ((u64)(0x02a4ebdb1b1e6d74)), ((u64)(0x2c451c735d92b526)), ((u64)(0x021d897c15b1f12a)), ((u64)(0x13a1c71efc1deea3)), ((u64)(0x0362759355e981dd)), ((u64)(0x761b05b2634b2550)), ((u64)(0x02b52adc44bace4a)), ((u64)(0x91af37c1e908eaa6)), ((u64)(0x022a88b036fbd83b)), ((u64)(0x82b1f2cfdb417770)), ((u64)(0x03774119f192f392)), ((u64)(0xcef4c23fe29ac5f3)), ((u64)(0x02c5cdae5adbf60e)), ((u64)(0x3f2a34ffe87bd190)), ((u64)(0x0237d7beaf165e72)), ((u64)(0x984387ffda5fb5b2)), ((u64)(0x038c8c644b56fd83)), ((u64)(0xe0360666484c915b)), ((u64)(0x02d6d6b6a2abfe02)), ((u64)(0x802b3851d3707449)), ((u64)(0x024578921bbccb35)), ((u64)(0x99dec082ebe72075)), ((u64)(0x03a25a835f947855)), ((u64)(0xae4bcd358985b391)), ((u64)(0x02e8486919439377)), ((u64)(0xbea30a913ad15c74)), ((u64)(0x02536d20e102dc5f)), ((u64)(0xfdd1aa81f7b560b9)), ((u64)(0x03b8ae9b019e2d65)), ((u64)(0x97daeece5fc44d61)), ((u64)(0x02fa2548ce182451)), ((u64)(0xdfe258a51969d781)), ((u64)(0x0261b76d71ace9da)), ((u64)(0x996a276e8f0fbf34)), ((u64)(0x03cf8be24f7b0fc4)), ((u64)(0xe121b9253f3fcc2a)), ((u64)(0x030c6fe83f95a636)), ((u64)(0xb41afa8432997022)), ((u64)(0x02705986994484f8)), ((u64)(0xecf7f739ea8f19cf)), ((u64)(0x03e6f5a4286da18d)), ((u64)(0x23f99294bba5ae40)), ((u64)(0x031f2ae9b9f14e0b)), ((u64)(0x4ffadbaa2fb7be99)), ((u64)(0x027f5587c7f43e6f)), ((u64)(0x7ff7c5dd1925fdc2)), ((u64)(0x03feef3fa6539718)), ((u64)(0xccc637e4141e649b)), ((u64)(0x033258ffb842df46)), ((u64)(0xd704f983434b83af)), ((u64)(0x028ead9960357f6b)), ((u64)(0x126a6135cf6f9c8c)), ((u64)(0x020bbe144cf79923)), ((u64)(0x83dd685618b29414)), ((u64)(0x0345fced47f28e9e)), ((u64)(0x9cb12044e08edcdd)), ((u64)(0x029e63f1065ba54b)), ((u64)(0x16f419d0b3a57d7d)), ((u64)(0x02184ff405161dd6)), ((u64)(0x8b20294dec3bfbfb)), ((u64)(0x035a19866e89c956)), ((u64)(0x3c19baa4bcfcc996)), ((u64)(0x02ae7ad1f207d445)), ((u64)(0xc9ae2eea30ca3adf)), ((u64)(0x02252f0e5b39769d)), ((u64)(0x0f7d17dd1add2afd)), ((u64)(0x036eb1b091f58a96)), ((u64)(0x3f97464a7be42264)), ((u64)(0x02bef48d41913bab)), ((u64)(0xcc790508631ce850)), ((u64)(0x02325d3dce0dc955)), ((u64)(0xe0c1a1a704fb0d4d)), ((u64)(0x0383c862e3494222)), ((u64)(0x4d67b4859d95a43e)), ((u64)(0x02cfd3824f6dce82)), ((u64)(0x711fc39e17aae9cb)), ((u64)(0x023fdc683f8b0b9b)), ((u64)(0xe832d2968c44a945)), ((u64)(0x039960a6cc11ac2b)), ((u64)(0xecf575453d03ba9e)), ((u64)(0x02e11a1f09a7bcef)), ((u64)(0x572ac4376402fbb1)), ((u64)(0x024dae7f3aec9726)), ((u64)(0x58446d256cd192b5)), ((u64)(0x03af7d985e47583d)), ((u64)(0x79d0575123dadbc4)), ((u64)(0x02f2cae04b6c4697)), ((u64)(0x94a6ac40e97be303)), ((u64)(0x025bd5803c569edf)), ((u64)(0x8771139b0f2c9e6c)), ((u64)(0x03c62266c6f0fe32)), ((u64)(0x9f8da948d8f07ebd)), ((u64)(0x0304e85238c0cb5b)), ((u64)(0xe60aedd3e0c06564)), ((u64)(0x026a5374fa33d5e2)), ((u64)(0xa344afb9679a3bd2)), ((u64)(0x03dd5254c3862304)), ((u64)(0xe903bfc78614fca8)), ((u64)(0x031775109c6b4f36)), ((u64)(0xba6966393810ca20)), ((u64)(0x02792a73b055d8f8)), ((u64)(0x2a423d2859b4769a)), ((u64)(0x03f510b91a22f4c1)), ((u64)(0xee9b642047c39215)), ((u64)(0x032a73c7481bf700)), ((u64)(0xbee2b680396941aa)), ((u64)(0x02885c9f6ce32c00)), ((u64)(0xff1bc53361210155)), ((u64)(0x0206b07f8a4f5666)), ((u64)(0x31c6085235019bbb)), ((u64)(0x033de73276e5570b)), ((u64)(0x27d1a041c4014963)), ((u64)(0x0297ec285f1ddf3c)), ((u64)(0xeca7b367d0010782)), ((u64)(0x021323537f4b18fc)), ((u64)(0xadd91f0c8001a59d)), ((u64)(0x0351d21f3211c194)), ((u64)(0xf17a7f3d3334847e)), ((u64)(0x02a7db4c280e3476)), ((u64)(0x279532975c2a0398)), ((u64)(0x021fe2a3533e905f)), ((u64)(0xd8eeb75893766c26)), ((u64)(0x0366376bb8641a31)), ((u64)(0x7a5892ad42c52352)), ((u64)(0x02b82c562d1ce1c1)), ((u64)(0xfb7a0ef102374f75)), ((u64)(0x022cf044f0e3e7cd)), ((u64)(0xc59017e8038bb254)), ((u64)(0x037b1a07e7d30c7c)), ((u64)(0x37a67986693c8eaa)), ((u64)(0x02c8e19feca8d6ca)), ((u64)(0xf951fad1edca0bbb)), ((u64)(0x023a4e198a20abd4)), ((u64)(0x28832ae97c76792b)), ((u64)(0x03907cf5a9cddfbb)), ((u64)(0x2068ef21305ec756)), ((u64)(0x02d9fd9154a4b2fc)), ((u64)(0x19ed8c1a8d189f78)), ((u64)(0x0247fe0ddd508f30)), ((u64)(0x5caf4690e1c0ff26)), ((u64)(0x03a66349621a7eb3)), ((u64)(0x4a25d20d81673285)), ((u64)(0x02eb82a11b48655c)), ((u64)(0x3b5174d79ab8f537)), ((u64)(0x0256021a7c39eab0)), ((u64)(0x921bee25c45b21f1)), ((u64)(0x03bcd02a605caab3)), ((u64)(0xdb498b5169e2818e)), ((u64)(0x02fd735519e3bbc2)), ((u64)(0x15d46f7454b53472)), ((u64)(0x02645c4414b62fcf)), ((u64)(0xefba4bed545520b6)), ((u64)(0x03d3c6d35456b2e4)), ((u64)(0xf2fb6ff110441a2b)), ((u64)(0x030fd242a9def583)), ((u64)(0x8f2f8cc0d9d014ef)), ((u64)(0x02730e9bbb18c469)), ((u64)(0xb1e5ae015c80217f)), ((u64)(0x03eb4a92c4f46d75)), ((u64)(0xc1848b344a001acc)), ((u64)(0x0322a20f03f6bdf7)), ((u64)(0xce03a2903b3348a3)), ((u64)(0x02821b3f365efe5f)), ((u64)(0xd802e873628f6d4f)), ((u64)(0x0201af65c518cb7f)), ((u64)(0x599e40b89db2487f)), ((u64)(0x0335e56fa1c14599)), ((u64)(0xe14b66fa17c1d399)), ((u64)(0x029184594e3437ad)), ((u64)(0x81091f2e7967dc7a)), ((u64)(0x020e037aa4f692f1)), ((u64)(0x9b41cb7d8f0c93f6)), ((u64)(0x03499f2aa18a84b5)), ((u64)(0xaf67d5fe0c0a0ff8)), ((u64)(0x02a14c221ad536f7)), ((u64)(0xf2b977fe70080cc7)), ((u64)(0x021aa34e7bddc592)), ((u64)(0x1df58cca4cd9ae0b)), ((u64)(0x035dd2172c9608eb)), ((u64)(0xe4c470a1d7148b3c)), ((u64)(0x02b174df56de6d88)), ((u64)(0x83d05a1b1276d5ca)), ((u64)(0x022790b2abe5246d)), ((u64)(0x9fb3c35e83f1560f)), ((u64)(0x0372811ddfd50715)), ((u64)(0xb2f635e5365aab3f)), ((u64)(0x02c200e4b310d277)), ((u64)(0xf591c4b75eaeef66)), ((u64)(0x0234cd83c273db92)), ((u64)(0xef4fa125644b18a3)), ((u64)(0x0387af39371fc5b7)), ((u64)(0x8c3fb41de9d5ad4f)), ((u64)(0x02d2f2942c196af9)), ((u64)(0x3cffc34b2177bdd9)), ((u64)(0x02425ba9bce12261)), ((u64)(0x94cc6bab68bf9628)), ((u64)(0x039d5f75fb01d09b)), ((u64)(0x10a38955ed6611b9)), ((u64)(0x02e44c5e6267da16)), ((u64)(0xda1c6dde5784dafb)), ((u64)(0x02503d184eb97b44)), ((u64)(0xf693e2fd58d49191)), ((u64)(0x03b394f3b128c53a)), ((u64)(0xc5431bfde0aa0e0e)), ((u64)(0x02f610c2f4209dc8)), ((u64)(0x6a9c1664b3bb3e72)), ((u64)(0x025e73cf29b3b16d)), ((u64)(0x10f9bd6dec5eca4f)), ((u64)(0x03ca52e50f85e8af)), ((u64)(0xda616457f04bd50c)), ((u64)(0x03084250d937ed58)), ((u64)(0xe1e783798d09773d)), ((u64)(0x026d01da475ff113)), ((u64)(0x030c058f480f252e)), ((u64)(0x03e19c9072331b53)), ((u64)(0x68d66ad906728425)), ((u64)(0x031ae3a6c1c27c42)), ((u64)(0x8711ef14052869b7)), ((u64)(0x027be952349b969b)), ((u64)(0x0b4fe4ecd50d75f2)), ((u64)(0x03f97550542c242c)), ((u64)(0xa2a650bd773df7f5)), ((u64)(0x032df7737689b689)), ((u64)(0xb551da312c31932a)), ((u64)(0x028b2c5c5ed49207)), ((u64)(0x5ddb14f4235adc22)), ((u64)(0x0208f049e576db39)), ((u64)(0x2fc4ee536bc49369)), ((u64)(0x034180763bf15ec2)), ((u64)(0xbfd0bea92303a921)), ((u64)(0x029acd2b63277f01)), ((u64)(0x9973cbba8269541a)), ((u64)(0x021570ef8285ff34)), ((u64)(0x5bec792a6a42202a)), ((u64)(0x0355817f373ccb87)), ((u64)(0xe3239421ee9b4cef)), ((u64)(0x02aacdff5f63d605)), ((u64)(0xb5b6101b25490a59)), ((u64)(0x02223e65e5e97804)), ((u64)(0x22bce691d541aa27)), ((u64)(0x0369fd6fd64259a1)), ((u64)(0xb563eba7ddce21b9)), ((u64)(0x02bb31264501e14d)), ((u64)(0xf78322ecb171b494)), ((u64)(0x022f5a850401810a)), ((u64)(0x259e9e47824f8753)), ((u64)(0x037ef73b399c01ab)), ((u64)(0x1e187e9f9b72d2a9)), ((u64)(0x02cbf8fc2e1667bc)), ((u64)(0x4b46cbb2e2c24221)), ((u64)(0x023cc73024deb963)), ((u64)(0x120adf849e039d01)), ((u64)(0x039471e6a1645bd2)), ((u64)(0xdb3be603b19c7d9a)), ((u64)(0x02dd27ebb4504974)), ((u64)(0x7c2feb3627b0647c)), ((u64)(0x024a865629d9d45d)), ((u64)(0x2d197856a5e7072c)), ((u64)(0x03aa7089dc8fba2f)), ((u64)(0x8a7ac6abb7ec05bd)), ((u64)(0x02eec06e4a0c94f2)), ((u64)(0xd52f05562cbcd164)), ((u64)(0x025899f1d4d6dd8e)), ((u64)(0x21e4d556adfae8a0)), ((u64)(0x03c0f64fbaf1627e)), ((u64)(0xe7ea444557fbed4d)), ((u64)(0x0300c50c958de864)), ((u64)(0xecbb69d1132ff10a)), ((u64)(0x0267040a113e5383)), ((u64)(0xadf8a94e851981aa)), ((u64)(0x03d8067681fd526c)), ((u64)(0x8b2d543ed0e13488)), ((u64)(0x0313385ece6441f0)), ((u64)(0xd5bddcff0d80f6d3)), ((u64)(0x0275c6b23eb69b26)), ((u64)(0x892fc7fe7c018aeb)), ((u64)(0x03efa45064575ea4)), ((u64)(0x3a8c9ffec99ad589)), ((u64)(0x03261d0d1d12b21d)), ((u64)(0xc8707fff07af113b)), ((u64)(0x0284e40a7da88e7d)), ((u64)(0x39f39998d2f2742f)), ((u64)(0x0203e9a1fe2071fe)), ((u64)(0x8fec28f484b7204b)), ((u64)(0x033975cffd00b663)), ((u64)(0xd989ba5d36f8e6a2)), ((u64)(0x02945e3ffd9a2b82)), ((u64)(0x47a161e42bfa521c)), ((u64)(0x02104b66647b5602)), ((u64)(0x0c35696d132a1cf9)), ((u64)(0x034d4570a0c5566a)), ((u64)(0x09c454574288172d)), ((u64)(0x02a4378d4d6aab88)), ((u64)(0xa169dd129ba0128b)), ((u64)(0x021cf93dd7888939)), ((u64)(0x0242fb50f9001dab)), ((u64)(0x03618ec958da7529)), ((u64)(0x9b68c90d940017bc)), ((u64)(0x02b4723aad7b90ed)), ((u64)(0x4920a0d7a999ac96)), ((u64)(0x0229f4fbbdfc73f1)), ((u64)(0x750101590f5c4757)), ((u64)(0x037654c5fcc71fe8)), ((u64)(0x2a6734473f7d05df)), ((u64)(0x02c5109e63d27fed)), ((u64)(0xeeb8f69f65fd9e4c)), ((u64)(0x0237407eb641fff0)), ((u64)(0xe45b24323cc8fd46)), ((u64)(0x038b9a6456cfffe7)), ((u64)(0xb6af502830a0ca9f)), ((u64)(0x02d6151d123fffec)), ((u64)(0xf88c402026e7087f)), ((u64)(0x0244ddb0db666656)), ((u64)(0x2746cd003e3e73fe)), ((u64)(0x03a162b4923d708b)), ((u64)(0x1f6bd73364fec332)), ((u64)(0x02e7822a0e978d3c)), ((u64)(0xe5efdf5c50cbcf5b)), ((u64)(0x0252ce880bac70fc)), ((u64)(0x3cb2fefa1adfb22b)), ((u64)(0x03b7b0d9ac471b2e)), ((u64)(0x308f3261af195b56)), ((u64)(0x02f95a47bd05af58)), ((u64)(0x5a0c284e25ade2ab)), ((u64)(0x0261150630d15913)), ((u64)(0x29ad0d49d5e30445)), ((u64)(0x03ce8809e7b55b52)), ((u64)(0x548a7107de4f369d)), ((u64)(0x030ba007ec9115db)), ((u64)(0xdd3b8d9fe50c2bb1)), ((u64)(0x026fb3398a0dab15)), ((u64)(0x952c15cca1ad12b5)), ((u64)(0x03e5eb8f434911bc)), ((u64)(0x775677d6e7bda891)), ((u64)(0x031e560c35d40e30)), ((u64)(0xc5dec645863153a7)), ((u64)(0x027eab3cf7dcd826))}, sizeof(strconv__pow5_inv_split_64_x));
	memmove(strconv__pos_exp, (u64[309]){((u64)(0x3ff0000000000000)), ((u64)(0x4024000000000000)), ((u64)(0x4059000000000000)), ((u64)(0x408f400000000000)), ((u64)(0x40c3880000000000)), ((u64)(0x40f86a0000000000)), ((u64)(0x412e848000000000)), ((u64)(0x416312d000000000)), ((u64)(0x4197d78400000000)), ((u64)(0x41cdcd6500000000)), ((u64)(0x4202a05f20000000)), ((u64)(0x42374876e8000000)), ((u64)(0x426d1a94a2000000)), ((u64)(0x42a2309ce5400000)), ((u64)(0x42d6bcc41e900000)), ((u64)(0x430c6bf526340000)), ((u64)(0x4341c37937e08000)), ((u64)(0x4376345785d8a000)), ((u64)(0x43abc16d674ec800)), ((u64)(0x43e158e460913d00)), ((u64)(0x4415af1d78b58c40)), ((u64)(0x444b1ae4d6e2ef50)), ((u64)(0x4480f0cf064dd592)), ((u64)(0x44b52d02c7e14af6)), ((u64)(0x44ea784379d99db4)), ((u64)(0x45208b2a2c280291)), ((u64)(0x4554adf4b7320335)), ((u64)(0x4589d971e4fe8402)), ((u64)(0x45c027e72f1f1281)), ((u64)(0x45f431e0fae6d721)), ((u64)(0x46293e5939a08cea)), ((u64)(0x465f8def8808b024)), ((u64)(0x4693b8b5b5056e17)), ((u64)(0x46c8a6e32246c99c)), ((u64)(0x46fed09bead87c03)), ((u64)(0x4733426172c74d82)), ((u64)(0x476812f9cf7920e3)), ((u64)(0x479e17b84357691b)), ((u64)(0x47d2ced32a16a1b1)), ((u64)(0x48078287f49c4a1d)), ((u64)(0x483d6329f1c35ca5)), ((u64)(0x48725dfa371a19e7)), ((u64)(0x48a6f578c4e0a061)), ((u64)(0x48dcb2d6f618c879)), ((u64)(0x4911efc659cf7d4c)), ((u64)(0x49466bb7f0435c9e)), ((u64)(0x497c06a5ec5433c6)), ((u64)(0x49b18427b3b4a05c)), ((u64)(0x49e5e531a0a1c873)), ((u64)(0x4a1b5e7e08ca3a8f)), ((u64)(0x4a511b0ec57e649a)), ((u64)(0x4a8561d276ddfdc0)), ((u64)(0x4ababa4714957d30)), ((u64)(0x4af0b46c6cdd6e3e)), ((u64)(0x4b24e1878814c9ce)), ((u64)(0x4b5a19e96a19fc41)), ((u64)(0x4b905031e2503da9)), ((u64)(0x4bc4643e5ae44d13)), ((u64)(0x4bf97d4df19d6057)), ((u64)(0x4c2fdca16e04b86d)), ((u64)(0x4c63e9e4e4c2f344)), ((u64)(0x4c98e45e1df3b015)), ((u64)(0x4ccf1d75a5709c1b)), ((u64)(0x4d03726987666191)), ((u64)(0x4d384f03e93ff9f5)), ((u64)(0x4d6e62c4e38ff872)), ((u64)(0x4da2fdbb0e39fb47)), ((u64)(0x4dd7bd29d1c87a19)), ((u64)(0x4e0dac74463a989f)), ((u64)(0x4e428bc8abe49f64)), ((u64)(0x4e772ebad6ddc73d)), ((u64)(0x4eacfa698c95390c)), ((u64)(0x4ee21c81f7dd43a7)), ((u64)(0x4f16a3a275d49491)), ((u64)(0x4f4c4c8b1349b9b5)), ((u64)(0x4f81afd6ec0e1411)), ((u64)(0x4fb61bcca7119916)), ((u64)(0x4feba2bfd0d5ff5b)), ((u64)(0x502145b7e285bf99)), ((u64)(0x50559725db272f7f)), ((u64)(0x508afcef51f0fb5f)), ((u64)(0x50c0de1593369d1b)), ((u64)(0x50f5159af8044462)), ((u64)(0x512a5b01b605557b)), ((u64)(0x516078e111c3556d)), ((u64)(0x5194971956342ac8)), ((u64)(0x51c9bcdfabc1357a)), ((u64)(0x5200160bcb58c16c)), ((u64)(0x52341b8ebe2ef1c7)), ((u64)(0x526922726dbaae39)), ((u64)(0x529f6b0f092959c7)), ((u64)(0x52d3a2e965b9d81d)), ((u64)(0x53088ba3bf284e24)), ((u64)(0x533eae8caef261ad)), ((u64)(0x53732d17ed577d0c)), ((u64)(0x53a7f85de8ad5c4f)), ((u64)(0x53ddf67562d8b363)), ((u64)(0x5412ba095dc7701e)), ((u64)(0x5447688bb5394c25)), ((u64)(0x547d42aea2879f2e)), ((u64)(0x54b249ad2594c37d)), ((u64)(0x54e6dc186ef9f45c)), ((u64)(0x551c931e8ab87173)), ((u64)(0x5551dbf316b346e8)), ((u64)(0x558652efdc6018a2)), ((u64)(0x55bbe7abd3781eca)), ((u64)(0x55f170cb642b133f)), ((u64)(0x5625ccfe3d35d80e)), ((u64)(0x565b403dcc834e12)), ((u64)(0x569108269fd210cb)), ((u64)(0x56c54a3047c694fe)), ((u64)(0x56fa9cbc59b83a3d)), ((u64)(0x5730a1f5b8132466)), ((u64)(0x5764ca732617ed80)), ((u64)(0x5799fd0fef9de8e0)), ((u64)(0x57d03e29f5c2b18c)), ((u64)(0x58044db473335def)), ((u64)(0x583961219000356b)), ((u64)(0x586fb969f40042c5)), ((u64)(0x58a3d3e2388029bb)), ((u64)(0x58d8c8dac6a0342a)), ((u64)(0x590efb1178484135)), ((u64)(0x59435ceaeb2d28c1)), ((u64)(0x59783425a5f872f1)), ((u64)(0x59ae412f0f768fad)), ((u64)(0x59e2e8bd69aa19cc)), ((u64)(0x5a17a2ecc414a03f)), ((u64)(0x5a4d8ba7f519c84f)), ((u64)(0x5a827748f9301d32)), ((u64)(0x5ab7151b377c247e)), ((u64)(0x5aecda62055b2d9e)), ((u64)(0x5b22087d4358fc82)), ((u64)(0x5b568a9c942f3ba3)), ((u64)(0x5b8c2d43b93b0a8c)), ((u64)(0x5bc19c4a53c4e697)), ((u64)(0x5bf6035ce8b6203d)), ((u64)(0x5c2b843422e3a84d)), ((u64)(0x5c6132a095ce4930)), ((u64)(0x5c957f48bb41db7c)), ((u64)(0x5ccadf1aea12525b)), ((u64)(0x5d00cb70d24b7379)), ((u64)(0x5d34fe4d06de5057)), ((u64)(0x5d6a3de04895e46d)), ((u64)(0x5da066ac2d5daec4)), ((u64)(0x5dd4805738b51a75)), ((u64)(0x5e09a06d06e26112)), ((u64)(0x5e400444244d7cab)), ((u64)(0x5e7405552d60dbd6)), ((u64)(0x5ea906aa78b912cc)), ((u64)(0x5edf485516e7577f)), ((u64)(0x5f138d352e5096af)), ((u64)(0x5f48708279e4bc5b)), ((u64)(0x5f7e8ca3185deb72)), ((u64)(0x5fb317e5ef3ab327)), ((u64)(0x5fe7dddf6b095ff1)), ((u64)(0x601dd55745cbb7ed)), ((u64)(0x6052a5568b9f52f4)), ((u64)(0x60874eac2e8727b1)), ((u64)(0x60bd22573a28f19d)), ((u64)(0x60f2357684599702)), ((u64)(0x6126c2d4256ffcc3)), ((u64)(0x615c73892ecbfbf4)), ((u64)(0x6191c835bd3f7d78)), ((u64)(0x61c63a432c8f5cd6)), ((u64)(0x61fbc8d3f7b3340c)), ((u64)(0x62315d847ad00087)), ((u64)(0x6265b4e5998400a9)), ((u64)(0x629b221effe500d4)), ((u64)(0x62d0f5535fef2084)), ((u64)(0x630532a837eae8a5)), ((u64)(0x633a7f5245e5a2cf)), ((u64)(0x63708f936baf85c1)), ((u64)(0x63a4b378469b6732)), ((u64)(0x63d9e056584240fe)), ((u64)(0x64102c35f729689f)), ((u64)(0x6444374374f3c2c6)), ((u64)(0x647945145230b378)), ((u64)(0x64af965966bce056)), ((u64)(0x64e3bdf7e0360c36)), ((u64)(0x6518ad75d8438f43)), ((u64)(0x654ed8d34e547314)), ((u64)(0x6583478410f4c7ec)), ((u64)(0x65b819651531f9e8)), ((u64)(0x65ee1fbe5a7e7861)), ((u64)(0x6622d3d6f88f0b3d)), ((u64)(0x665788ccb6b2ce0c)), ((u64)(0x668d6affe45f818f)), ((u64)(0x66c262dfeebbb0f9)), ((u64)(0x66f6fb97ea6a9d38)), ((u64)(0x672cba7de5054486)), ((u64)(0x6761f48eaf234ad4)), ((u64)(0x679671b25aec1d89)), ((u64)(0x67cc0e1ef1a724eb)), ((u64)(0x680188d357087713)), ((u64)(0x6835eb082cca94d7)), ((u64)(0x686b65ca37fd3a0d)), ((u64)(0x68a11f9e62fe4448)), ((u64)(0x68d56785fbbdd55a)), ((u64)(0x690ac1677aad4ab1)), ((u64)(0x6940b8e0acac4eaf)), ((u64)(0x6974e718d7d7625a)), ((u64)(0x69aa20df0dcd3af1)), ((u64)(0x69e0548b68a044d6)), ((u64)(0x6a1469ae42c8560c)), ((u64)(0x6a498419d37a6b8f)), ((u64)(0x6a7fe52048590673)), ((u64)(0x6ab3ef342d37a408)), ((u64)(0x6ae8eb0138858d0a)), ((u64)(0x6b1f25c186a6f04c)), ((u64)(0x6b537798f4285630)), ((u64)(0x6b88557f31326bbb)), ((u64)(0x6bbe6adefd7f06aa)), ((u64)(0x6bf302cb5e6f642a)), ((u64)(0x6c27c37e360b3d35)), ((u64)(0x6c5db45dc38e0c82)), ((u64)(0x6c9290ba9a38c7d1)), ((u64)(0x6cc734e940c6f9c6)), ((u64)(0x6cfd022390f8b837)), ((u64)(0x6d3221563a9b7323)), ((u64)(0x6d66a9abc9424feb)), ((u64)(0x6d9c5416bb92e3e6)), ((u64)(0x6dd1b48e353bce70)), ((u64)(0x6e0621b1c28ac20c)), ((u64)(0x6e3baa1e332d728f)), ((u64)(0x6e714a52dffc6799)), ((u64)(0x6ea59ce797fb817f)), ((u64)(0x6edb04217dfa61df)), ((u64)(0x6f10e294eebc7d2c)), ((u64)(0x6f451b3a2a6b9c76)), ((u64)(0x6f7a6208b5068394)), ((u64)(0x6fb07d457124123d)), ((u64)(0x6fe49c96cd6d16cc)), ((u64)(0x7019c3bc80c85c7f)), ((u64)(0x70501a55d07d39cf)), ((u64)(0x708420eb449c8843)), ((u64)(0x70b9292615c3aa54)), ((u64)(0x70ef736f9b3494e9)), ((u64)(0x7123a825c100dd11)), ((u64)(0x7158922f31411456)), ((u64)(0x718eb6bafd91596b)), ((u64)(0x71c33234de7ad7e3)), ((u64)(0x71f7fec216198ddc)), ((u64)(0x722dfe729b9ff153)), ((u64)(0x7262bf07a143f6d4)), ((u64)(0x72976ec98994f489)), ((u64)(0x72cd4a7bebfa31ab)), ((u64)(0x73024e8d737c5f0b)), ((u64)(0x7336e230d05b76cd)), ((u64)(0x736c9abd04725481)), ((u64)(0x73a1e0b622c774d0)), ((u64)(0x73d658e3ab795204)), ((u64)(0x740bef1c9657a686)), ((u64)(0x74417571ddf6c814)), ((u64)(0x7475d2ce55747a18)), ((u64)(0x74ab4781ead1989e)), ((u64)(0x74e10cb132c2ff63)), ((u64)(0x75154fdd7f73bf3c)), ((u64)(0x754aa3d4df50af0b)), ((u64)(0x7580a6650b926d67)), ((u64)(0x75b4cffe4e7708c0)), ((u64)(0x75ea03fde214caf1)), ((u64)(0x7620427ead4cfed6)), ((u64)(0x7654531e58a03e8c)), ((u64)(0x768967e5eec84e2f)), ((u64)(0x76bfc1df6a7a61bb)), ((u64)(0x76f3d92ba28c7d15)), ((u64)(0x7728cf768b2f9c5a)), ((u64)(0x775f03542dfb8370)), ((u64)(0x779362149cbd3226)), ((u64)(0x77c83a99c3ec7eb0)), ((u64)(0x77fe494034e79e5c)), ((u64)(0x7832edc82110c2f9)), ((u64)(0x7867a93a2954f3b8)), ((u64)(0x789d9388b3aa30a5)), ((u64)(0x78d27c35704a5e67)), ((u64)(0x79071b42cc5cf601)), ((u64)(0x793ce2137f743382)), ((u64)(0x79720d4c2fa8a031)), ((u64)(0x79a6909f3b92c83d)), ((u64)(0x79dc34c70a777a4d)), ((u64)(0x7a11a0fc668aac70)), ((u64)(0x7a46093b802d578c)), ((u64)(0x7a7b8b8a6038ad6f)), ((u64)(0x7ab137367c236c65)), ((u64)(0x7ae585041b2c477f)), ((u64)(0x7b1ae64521f7595e)), ((u64)(0x7b50cfeb353a97db)), ((u64)(0x7b8503e602893dd2)), ((u64)(0x7bba44df832b8d46)), ((u64)(0x7bf06b0bb1fb384c)), ((u64)(0x7c2485ce9e7a065f)), ((u64)(0x7c59a742461887f6)), ((u64)(0x7c9008896bcf54fa)), ((u64)(0x7cc40aabc6c32a38)), ((u64)(0x7cf90d56b873f4c7)), ((u64)(0x7d2f50ac6690f1f8)), ((u64)(0x7d63926bc01a973b)), ((u64)(0x7d987706b0213d0a)), ((u64)(0x7dce94c85c298c4c)), ((u64)(0x7e031cfd3999f7b0)), ((u64)(0x7e37e43c8800759c)), ((u64)(0x7e6ddd4baa009303)), ((u64)(0x7ea2aa4f4a405be2)), ((u64)(0x7ed754e31cd072da)), ((u64)(0x7f0d2a1be4048f90)), ((u64)(0x7f423a516e82d9ba)), ((u64)(0x7f76c8e5ca239029)), ((u64)(0x7fac7b1f3cac7433)), ((u64)(0x7fe1ccf385ebc8a0))}, sizeof(strconv__pos_exp));
	memmove(strconv__neg_exp, (u64[324]){((u64)(0x3ff0000000000000)), ((u64)(0x3fb999999999999a)), ((u64)(0x3f847ae147ae147b)), ((u64)(0x3f50624dd2f1a9fc)), ((u64)(0x3f1a36e2eb1c432d)), ((u64)(0x3ee4f8b588e368f1)), ((u64)(0x3eb0c6f7a0b5ed8d)), ((u64)(0x3e7ad7f29abcaf48)), ((u64)(0x3e45798ee2308c3a)), ((u64)(0x3e112e0be826d695)), ((u64)(0x3ddb7cdfd9d7bdbb)), ((u64)(0x3da5fd7fe1796495)), ((u64)(0x3d719799812dea11)), ((u64)(0x3d3c25c268497682)), ((u64)(0x3d06849b86a12b9b)), ((u64)(0x3cd203af9ee75616)), ((u64)(0x3c9cd2b297d889bc)), ((u64)(0x3c670ef54646d497)), ((u64)(0x3c32725dd1d243ac)), ((u64)(0x3bfd83c94fb6d2ac)), ((u64)(0x3bc79ca10c924223)), ((u64)(0x3b92e3b40a0e9b4f)), ((u64)(0x3b5e392010175ee6)), ((u64)(0x3b282db34012b251)), ((u64)(0x3af357c299a88ea7)), ((u64)(0x3abef2d0f5da7dd9)), ((u64)(0x3a88c240c4aecb14)), ((u64)(0x3a53ce9a36f23c10)), ((u64)(0x3a1fb0f6be506019)), ((u64)(0x39e95a5efea6b347)), ((u64)(0x39b4484bfeebc2a0)), ((u64)(0x398039d665896880)), ((u64)(0x3949f623d5a8a733)), ((u64)(0x3914c4e977ba1f5c)), ((u64)(0x38e09d8792fb4c49)), ((u64)(0x38aa95a5b7f87a0f)), ((u64)(0x38754484932d2e72)), ((u64)(0x3841039d428a8b8f)), ((u64)(0x380b38fb9daa78e4)), ((u64)(0x37d5c72fb1552d83)), ((u64)(0x37a16c262777579c)), ((u64)(0x376be03d0bf225c7)), ((u64)(0x37364cfda3281e39)), ((u64)(0x3701d7314f534b61)), ((u64)(0x36cc8b8218854567)), ((u64)(0x3696d601ad376ab9)), ((u64)(0x366244ce242c5561)), ((u64)(0x362d3ae36d13bbce)), ((u64)(0x35f7624f8a762fd8)), ((u64)(0x35c2b50c6ec4f313)), ((u64)(0x358dee7a4ad4b81f)), ((u64)(0x3557f1fb6f10934c)), ((u64)(0x352327fc58da0f70)), ((u64)(0x34eea6608e29b24d)), ((u64)(0x34b8851a0b548ea4)), ((u64)(0x34839dae6f76d883)), ((u64)(0x344f62b0b257c0d2)), ((u64)(0x34191bc08eac9a41)), ((u64)(0x33e41633a556e1ce)), ((u64)(0x33b011c2eaabe7d8)), ((u64)(0x3379b604aaaca626)), ((u64)(0x3344919d5556eb52)), ((u64)(0x3310747ddddf22a8)), ((u64)(0x32da53fc9631d10d)), ((u64)(0x32a50ffd44f4a73d)), ((u64)(0x3270d9976a5d5297)), ((u64)(0x323af5bf109550f2)), ((u64)(0x32059165a6ddda5b)), ((u64)(0x31d1411e1f17e1e3)), ((u64)(0x319b9b6364f30304)), ((u64)(0x316615e91d8f359d)), ((u64)(0x3131ab20e472914a)), ((u64)(0x30fc45016d841baa)), ((u64)(0x30c69d9abe034955)), ((u64)(0x309217aefe690777)), ((u64)(0x305cf2b1970e7258)), ((u64)(0x3027288e1271f513)), ((u64)(0x2ff286d80ec190dc)), ((u64)(0x2fbda48ce468e7c7)), ((u64)(0x2f87b6d71d20b96c)), ((u64)(0x2f52f8ac174d6123)), ((u64)(0x2f1e5aacf2156838)), ((u64)(0x2ee8488a5b445360)), ((u64)(0x2eb36d3b7c36a91a)), ((u64)(0x2e7f152bf9f10e90)), ((u64)(0x2e48ddbcc7f40ba6)), ((u64)(0x2e13e497065cd61f)), ((u64)(0x2ddfd424d6faf031)), ((u64)(0x2da97683df2f268d)), ((u64)(0x2d745ecfe5bf520b)), ((u64)(0x2d404bd984990e6f)), ((u64)(0x2d0a12f5a0f4e3e5)), ((u64)(0x2cd4dbf7b3f71cb7)), ((u64)(0x2ca0aff95cc5b092)), ((u64)(0x2c6ab328946f80ea)), ((u64)(0x2c355c2076bf9a55)), ((u64)(0x2c0116805effaeaa)), ((u64)(0x2bcb5733cb32b111)), ((u64)(0x2b95df5ca28ef40d)), ((u64)(0x2b617f7d4ed8c33e)), ((u64)(0x2b2bff2ee48e0530)), ((u64)(0x2af665bf1d3e6a8d)), ((u64)(0x2ac1eaff4a98553d)), ((u64)(0x2a8cab3210f3bb95)), ((u64)(0x2a56ef5b40c2fc77)), ((u64)(0x2a225915cd68c9f9)), ((u64)(0x29ed5b561574765b)), ((u64)(0x29b77c44ddf6c516)), ((u64)(0x2982c9d0b1923745)), ((u64)(0x294e0fb44f50586e)), ((u64)(0x29180c903f7379f2)), ((u64)(0x28e33d4032c2c7f5)), ((u64)(0x28aec866b79e0cba)), ((u64)(0x2878a0522c7e7095)), ((u64)(0x2843b374f06526de)), ((u64)(0x280f8587e7083e30)), ((u64)(0x27d9379fec069826)), ((u64)(0x27a42c7ff0054685)), ((u64)(0x277023998cd10537)), ((u64)(0x2739d28f47b4d525)), ((u64)(0x2704a8729fc3ddb7)), ((u64)(0x26d086c219697e2c)), ((u64)(0x269a71368f0f3047)), ((u64)(0x2665275ed8d8f36c)), ((u64)(0x2630ec4be0ad8f89)), ((u64)(0x25fb13ac9aaf4c0f)), ((u64)(0x25c5a956e225d672)), ((u64)(0x2591544581b7dec2)), ((u64)(0x255bba08cf8c979d)), ((u64)(0x25262e6d72d6dfb0)), ((u64)(0x24f1bebdf578b2f4)), ((u64)(0x24bc6463225ab7ec)), ((u64)(0x2486b6b5b5155ff0)), ((u64)(0x24522bc490dde65a)), ((u64)(0x241d12d41afca3c3)), ((u64)(0x23e7424348ca1c9c)), ((u64)(0x23b29b69070816e3)), ((u64)(0x237dc574d80cf16b)), ((u64)(0x2347d12a4670c123)), ((u64)(0x23130dbb6b8d674f)), ((u64)(0x22de7c5f127bd87e)), ((u64)(0x22a8637f41fcad32)), ((u64)(0x227382cc34ca2428)), ((u64)(0x223f37ad21436d0c)), ((u64)(0x2208f9574dcf8a70)), ((u64)(0x21d3faac3e3fa1f3)), ((u64)(0x219ff779fd329cb9)), ((u64)(0x216992c7fdc216fa)), ((u64)(0x2134756ccb01abfb)), ((u64)(0x21005df0a267bcc9)), ((u64)(0x20ca2fe76a3f9475)), ((u64)(0x2094f31f8832dd2a)), ((u64)(0x2060c27fa028b0ef)), ((u64)(0x202ad0cc33744e4b)), ((u64)(0x1ff573d68f903ea2)), ((u64)(0x1fc1297872d9cbb5)), ((u64)(0x1f8b758d848fac55)), ((u64)(0x1f55f7a46a0c89dd)), ((u64)(0x1f2192e9ee706e4b)), ((u64)(0x1eec1e43171a4a11)), ((u64)(0x1eb67e9c127b6e74)), ((u64)(0x1e81fee341fc585d)), ((u64)(0x1e4ccb0536608d61)), ((u64)(0x1e1708d0f84d3de7)), ((u64)(0x1de26d73f9d764b9)), ((u64)(0x1dad7becc2f23ac2)), ((u64)(0x1d779657025b6235)), ((u64)(0x1d42deac01e2b4f7)), ((u64)(0x1d0e3113363787f2)), ((u64)(0x1cd8274291c6065b)), ((u64)(0x1ca3529ba7d19eaf)), ((u64)(0x1c6eea92a61c3118)), ((u64)(0x1c38bba884e35a7a)), ((u64)(0x1c03c9539d82aec8)), ((u64)(0x1bcfa885c8d117a6)), ((u64)(0x1b99539e3a40dfb8)), ((u64)(0x1b6442e4fb671960)), ((u64)(0x1b303583fc527ab3)), ((u64)(0x1af9ef3993b72ab8)), ((u64)(0x1ac4bf6142f8eefa)), ((u64)(0x1a90991a9bfa58c8)), ((u64)(0x1a5a8e90f9908e0d)), ((u64)(0x1a253eda614071a4)), ((u64)(0x19f0ff151a99f483)), ((u64)(0x19bb31bb5dc320d2)), ((u64)(0x1985c162b168e70e)), ((u64)(0x1951678227871f3e)), ((u64)(0x191bd8d03f3e9864)), ((u64)(0x18e6470cff6546b6)), ((u64)(0x18b1d270cc51055f)), ((u64)(0x187c83e7ad4e6efe)), ((u64)(0x1846cfec8aa52598)), ((u64)(0x18123ff06eea847a)), ((u64)(0x17dd331a4b10d3f6)), ((u64)(0x17a75c1508da432b)), ((u64)(0x1772b010d3e1cf56)), ((u64)(0x173de6815302e556)), ((u64)(0x1707eb9aa8cf1dde)), ((u64)(0x16d322e220a5b17e)), ((u64)(0x169e9e369aa2b597)), ((u64)(0x16687e92154ef7ac)), ((u64)(0x16339874ddd8c623)), ((u64)(0x15ff5a549627a36c)), ((u64)(0x15c91510781fb5f0)), ((u64)(0x159410d9f9b2f7f3)), ((u64)(0x15600d7b2e28c65c)), ((u64)(0x1529af2b7d0e0a2d)), ((u64)(0x14f48c22ca71a1bd)), ((u64)(0x14c0701bd527b498)), ((u64)(0x148a4cf9550c5426)), ((u64)(0x14550a6110d6a9b8)), ((u64)(0x1420d51a73deee2d)), ((u64)(0x13eaee90b964b047)), ((u64)(0x13b58ba6fab6f36c)), ((u64)(0x13813c85955f2923)), ((u64)(0x134b9408eefea839)), ((u64)(0x1316100725988694)), ((u64)(0x12e1a66c1e139edd)), ((u64)(0x12ac3d79c9b8fe2e)), ((u64)(0x12769794a160cb58)), ((u64)(0x124212dd4de70913)), ((u64)(0x120ceafbafd80e85)), ((u64)(0x11d72262f3133ed1)), ((u64)(0x11a281e8c275cbda)), ((u64)(0x116d9ca79d89462a)), ((u64)(0x1137b08617a104ee)), ((u64)(0x1102f39e794d9d8b)), ((u64)(0x10ce5297287c2f45)), ((u64)(0x1098421286c9bf6b)), ((u64)(0x1063680ed23aff89)), ((u64)(0x102f0ce4839198db)), ((u64)(0x0ff8d71d360e13e2)), ((u64)(0x0fc3df4a91a4dcb5)), ((u64)(0x0f8fcbaa82a16121)), ((u64)(0x0f596fbb9bb44db4)), ((u64)(0x0f245962e2f6a490)), ((u64)(0x0ef047824f2bb6da)), ((u64)(0x0eba0c03b1df8af6)), ((u64)(0x0e84d6695b193bf8)), ((u64)(0x0e50ab877c142ffa)), ((u64)(0x0e1aac0bf9b9e65c)), ((u64)(0x0de5566ffafb1eb0)), ((u64)(0x0db111f32f2f4bc0)), ((u64)(0x0d7b4feb7eb212cd)), ((u64)(0x0d45d98932280f0a)), ((u64)(0x0d117ad428200c08)), ((u64)(0x0cdbf7b9d9cce00d)), ((u64)(0x0ca65fc7e170b33e)), ((u64)(0x0c71e6398126f5cb)), ((u64)(0x0c3ca38f350b22df)), ((u64)(0x0c06e93f5da2824c)), ((u64)(0x0bd25432b14ecea3)), ((u64)(0x0b9d53844ee47dd1)), ((u64)(0x0b677603725064a8)), ((u64)(0x0b32c4cf8ea6b6ec)), ((u64)(0x0afe07b27dd78b14)), ((u64)(0x0ac8062864ac6f43)), ((u64)(0x0a9338205089f29c)), ((u64)(0x0a5ec033b40fea93)), ((u64)(0x0a2899c2f6732210)), ((u64)(0x09f3ae3591f5b4d9)), ((u64)(0x09bf7d228322baf5)), ((u64)(0x098930e868e89591)), ((u64)(0x0954272053ed4474)), ((u64)(0x09201f4d0ff10390)), ((u64)(0x08e9cbae7fe805b3)), ((u64)(0x08b4a2f1ffecd15c)), ((u64)(0x0880825b3323dab0)), ((u64)(0x084a6a2b85062ab3)), ((u64)(0x081521bc6a6b555c)), ((u64)(0x07e0e7c9eebc444a)), ((u64)(0x07ab0c764ac6d3a9)), ((u64)(0x0775a391d56bdc87)), ((u64)(0x07414fa7ddefe3a0)), ((u64)(0x070bb2a62fe638ff)), ((u64)(0x06d62884f31e93ff)), ((u64)(0x06a1ba03f5b21000)), ((u64)(0x066c5cd322b67fff)), ((u64)(0x0636b0a8e891ffff)), ((u64)(0x060226ed86db3333)), ((u64)(0x05cd0b15a491eb84)), ((u64)(0x05973c115074bc6a)), ((u64)(0x05629674405d6388)), ((u64)(0x052dbd86cd6238d9)), ((u64)(0x04f7cad23de82d7b)), ((u64)(0x04c308a831868ac9)), ((u64)(0x048e74404f3daadb)), ((u64)(0x04585d003f6488af)), ((u64)(0x04237d99cc506d59)), ((u64)(0x03ef2f5c7a1a488e)), ((u64)(0x03b8f2b061aea072)), ((u64)(0x0383f559e7bee6c1)), ((u64)(0x034feef63f97d79c)), ((u64)(0x03198bf832dfdfb0)), ((u64)(0x02e46ff9c24cb2f3)), ((u64)(0x02b059949b708f29)), ((u64)(0x027a28edc580e50e)), ((u64)(0x0244ed8b04671da5)), ((u64)(0x0210be08d0527e1d)), ((u64)(0x01dac9a7b3b7302f)), ((u64)(0x01a56e1fc2f8f359)), ((u64)(0x017124e63593f5e1)), ((u64)(0x013b6e3d22865634)), ((u64)(0x0105f1ca820511c3)), ((u64)(0x00d18e3b9b374169)), ((u64)(0x009c16c5c5253575)), ((u64)(0x0066789e3750f791)), ((u64)(0x0031fa182c40c60d)), ((u64)(0x000730d67819e8d2)), ((u64)(0x0000b8157268fdaf)), ((u64)(0x000012688b70e62b)), ((u64)(0x000001d74124e3d1)), ((u64)(0x0000002f201d49fb)), ((u64)(0x00000004b6695433)), ((u64)(0x0000000078a42205)), ((u64)(0x000000000c1069cd)), ((u64)(0x000000000134d761)), ((u64)(0x00000000001ee257)), ((u64)(0x00000000000316a2)), ((u64)(0x0000000000004f10)), ((u64)(0x00000000000007e8)), ((u64)(0x00000000000000ca)), ((u64)(0x0000000000000014)), ((u64)(0x0000000000000002))}, sizeof(strconv__neg_exp));
	memmove(strconv__ten_pow_table_32, (u32[10]){((u32)(1)), ((u32)(10)), ((u32)(100)), ((u32)(1000)), ((u32)(10000)), ((u32)(100000)), ((u32)(1000000)), ((u32)(10000000)), ((u32)(100000000)), ((u32)(1000000000))}, sizeof(strconv__ten_pow_table_32));
	builtin__none__ = (IError){._typ = 2065246729, ._object = (None__*)memdup(&(None__){0}, sizeof(None__)), ._object_is_boxed = true, .message = _v3_lit_0_14650fb0739d0383, .code = 0};
	memmove(builtin__rune_maps, (i32[1264]){((i32)(0xB5)), 0xB5, 743, 0, 0xC0, 0xD6, 0, 32, 0xD8, 0xDE, 0, 32, 0xE0, 0xF6, -(32), 0, 0xF8, 0xFE, -(32), 0, 0xFF, 0xFF, 121, 0, 0x100, 0x12F, -(3), -(3), 0x130, 0x130, 0, -(199), 0x131, 0x131, -(232), 0, 0x132, 0x137, -(3), -(3), 0x139, 0x148, -(3), -(3), 0x14A, 0x177, -(3), -(3), 0x178, 0x178, 0, -(121), 0x179, 0x17E, -(3), -(3), 0x17F, 0x17F, -(300), 0, 0x180, 0x180, 195, 0, 0x181, 0x181, 0, 210, 0x182, 0x185, -(3), -(3), 0x186, 0x186, 0, 206, 0x187, 0x188, -(3), -(3), 0x189, 0x18A, 0, 205, 0x18B, 0x18C, -(3), -(3), 0x18E, 0x18E, 0, 79, 0x18F, 0x18F, 0, 202, 0x190, 0x190, 0, 203, 0x191, 0x192, -(3), -(3), 0x193, 0x193, 0, 205, 0x194, 0x194, 0, 207, 0x195, 0x195, 97, 0, 0x196, 0x196, 0, 211, 0x197, 0x197, 0, 209, 0x198, 0x199, -(3), -(3), 0x19A, 0x19A, 163, 0, 0x19C, 0x19C, 0, 211, 0x19D, 0x19D, 0, 213, 0x19E, 0x19E, 130, 0, 0x19F, 0x19F, 0, 214, 0x1A0, 0x1A5, -(3), -(3), 0x1A6, 0x1A6, 0, 218, 0x1A7, 0x1A8, -(3), -(3), 0x1A9, 0x1A9, 0, 218, 0x1AC, 0x1AD, -(3), -(3), 0x1AE, 0x1AE, 0, 218, 0x1AF, 0x1B0, -(3), -(3), 0x1B1, 0x1B2, 0, 217, 0x1B3, 0x1B6, -(3), -(3), 0x1B7, 0x1B7, 0, 219, 0x1B8, 0x1B9, -(3), -(3), 0x1BC, 0x1BD, -(3), -(3), 0x1BF, 0x1BF, 56, 0, 0x1C4, 0x1CC, -(2), -(2), 0x1CD, 0x1DC, -(3), -(3), 0x1DD, 0x1DD, -(79), 0, 0x1DE, 0x1EF, -(3), -(3), 0x1F1, 0x1F3, -(2), -(2), 0x1F4, 0x1F5, -(3), -(3), 0x1F6, 0x1F6, 0, -(97), 0x1F7, 0x1F7, 0, -(56), 0x1F8, 0x21F, -(3), -(3), 0x220, 0x220, 0, -(130), 0x222, 0x233, -(3), -(3), 0x23A, 0x23A, 0, 10795, 0x23B, 0x23C, -(3), -(3), 0x23D, 0x23D, 0, -(163), 0x23E, 0x23E, 0, 10792, 0x23F, 0x240, 10815, 0, 0x241, 0x242, -(3), -(3), 0x243, 0x243, 0, -(195), 0x244, 0x244, 0, 69, 0x245, 0x245, 0, 71, 0x246, 0x24F, -(3), -(3), 0x250, 0x250, 10783, 0, 0x251, 0x251, 10780, 0, 0x252, 0x252, 10782, 0, 0x253, 0x253, -(210), 0, 0x254, 0x254, -(206), 0, 0x256, 0x257, -(205), 0, 0x259, 0x259, -(202), 0, 0x25B, 0x25B, -(203), 0, 0x25C, 0x25C, 42319, 0, 0x260, 0x260, -(205), 0, 0x261, 0x261, 42315, 0, 0x263, 0x263, -(207), 0, 0x265, 0x265, 42280, 0, 0x266, 0x266, 42308, 0, 0x268, 0x268, -(209), 0, 0x269, 0x269, -(211), 0, 0x26A, 0x26A, 42308, 0, 0x26B, 0x26B, 10743, 0, 0x26C, 0x26C, 42305, 0, 0x26F, 0x26F, -(211), 0, 0x271, 0x271, 10749, 0, 0x272, 0x272, -(213), 0, 0x275, 0x275, -(214), 0, 0x27D, 0x27D, 10727, 0, 0x280, 0x280, -(218), 0, 0x282, 0x282, 42307, 0, 0x283, 0x283, -(218), 0, 0x287, 0x287, 42282, 0, 0x288, 0x288, -(218), 0, 0x289, 0x289, -(69), 0, 0x28A, 0x28B, -(217), 0, 0x28C, 0x28C, -(71), 0, 0x292, 0x292, -(219), 0, 0x29D, 0x29D, 42261, 0, 0x29E, 0x29E, 42258, 0, 0x345, 0x345, 84, 0, 0x370, 0x373, -(3), -(3), 0x376, 0x377, -(3), -(3), 0x37B, 0x37D, 130, 0, 0x37F, 0x37F, 0, 116, 0x386, 0x386, 0, 38, 0x388, 0x38A, 0, 37, 0x38C, 0x38C, 0, 64, 0x38E, 0x38F, 0, 63, 0x391, 0x3A1, 0, 32, 0x3A3, 0x3AB, 0, 32, 0x3AC, 0x3AC, -(38), 0, 0x3AD, 0x3AF, -(37), 0, 0x3B1, 0x3C1, -(32), 0, 0x3C2, 0x3C2, -(31), 0, 0x3C3, 0x3CB, -(32), 0, 0x3CC, 0x3CC, -(64), 0, 0x3CD, 0x3CE, -(63), 0, 0x3CF, 0x3CF, 0, 8, 0x3D0, 0x3D0, -(62), 0, 0x3D1, 0x3D1, -(57), 0, 0x3D5, 0x3D5, -(47), 0, 0x3D6, 0x3D6, -(54), 0, 0x3D7, 0x3D7, -(8), 0, 0x3D8, 0x3EF, -(3), -(3), 0x3F0, 0x3F0, -(86), 0, 0x3F1, 0x3F1, -(80), 0, 0x3F2, 0x3F2, 7, 0, 0x3F3, 0x3F3, -(116), 0, 0x3F4, 0x3F4, 0, -(60), 0x3F5, 0x3F5, -(96), 0, 0x3F7, 0x3F8, -(3), -(3), 0x3F9, 0x3F9, 0, -(7), 0x3FA, 0x3FB, -(3), -(3), 0x3FD, 0x3FF, 0, -(130), 0x400, 0x40F, 0, 80, 0x410, 0x42F, 0, 32, 0x430, 0x44F, -(32), 0, 0x450, 0x45F, -(80), 0, 0x460, 0x481, -(3), -(3), 0x48A, 0x4BF, -(3), -(3), 0x4C0, 0x4C0, 0, 15, 0x4C1, 0x4CE, -(3), -(3), 0x4CF, 0x4CF, -(15), 0, 0x4D0, 0x52F, -(3), -(3), 0x531, 0x556, 0, 48, 0x561, 0x586, -(48), 0, 0x10A0, 0x10C5, 0, 7264, 0x10C7, 0x10C7, 0, 7264, 0x10CD, 0x10CD, 0, 7264, 0x10D0, 0x10FA, 3008, 0, 0x10FD, 0x10FF, 3008, 0, 0x13A0, 0x13EF, 0, 38864, 0x13F0, 0x13F5, 0, 8, 0x13F8, 0x13FD, -(8), 0, 0x1C80, 0x1C80, -(6254), 0, 0x1C81, 0x1C81, -(6253), 0, 0x1C82, 0x1C82, -(6244), 0, 0x1C83, 0x1C84, -(6242), 0, 0x1C85, 0x1C85, -(6243), 0, 0x1C86, 0x1C86, -(6236), 0, 0x1C87, 0x1C87, -(6181), 0, 0x1C88, 0x1C88, 35266, 0, 0x1C90, 0x1CBA, 0, -(3008), 0x1CBD, 0x1CBF, 0, -(3008), 0x1D79, 0x1D79, 35332, 0, 0x1D7D, 0x1D7D, 3814, 0, 0x1D8E, 0x1D8E, 35384, 0, 0x1E00, 0x1E95, -(3), -(3), 0x1E9B, 0x1E9B, -(59), 0, 0x1E9E, 0x1E9E, 0, -(7615), 0x1EA0, 0x1EFF, -(3), -(3), 0x1F00, 0x1F07, 8, 0, 0x1F08, 0x1F0F, 0, -(8), 0x1F10, 0x1F15, 8, 0, 0x1F18, 0x1F1D, 0, -(8), 0x1F20, 0x1F27, 8, 0, 0x1F28, 0x1F2F, 0, -(8), 0x1F30, 0x1F37, 8, 0, 0x1F38, 0x1F3F, 0, -(8), 0x1F40, 0x1F45, 8, 0, 0x1F48, 0x1F4D, 0, -(8), 0x1F51, 0x1F51, 8, 0, 0x1F53, 0x1F53, 8, 0, 0x1F55, 0x1F55, 8, 0, 0x1F57, 0x1F57, 8, 0, 0x1F59, 0x1F59, 0, -(8), 0x1F5B, 0x1F5B, 0, -(8), 0x1F5D, 0x1F5D, 0, -(8), 0x1F5F, 0x1F5F, 0, -(8), 0x1F60, 0x1F67, 8, 0, 0x1F68, 0x1F6F, 0, -(8), 0x1F70, 0x1F71, 74, 0, 0x1F72, 0x1F75, 86, 0, 0x1F76, 0x1F77, 100, 0, 0x1F78, 0x1F79, 128, 0, 0x1F7A, 0x1F7B, 112, 0, 0x1F7C, 0x1F7D, 126, 0, 0x1F80, 0x1F87, 8, 0, 0x1F88, 0x1F8F, 0, -(8), 0x1F90, 0x1F97, 8, 0, 0x1F98, 0x1F9F, 0, -(8), 0x1FA0, 0x1FA7, 8, 0, 0x1FA8, 0x1FAF, 0, -(8), 0x1FB0, 0x1FB1, 8, 0, 0x1FB3, 0x1FB3, 9, 0, 0x1FB8, 0x1FB9, 0, -(8), 0x1FBA, 0x1FBB, 0, -(74), 0x1FBC, 0x1FBC, 0, -(9), 0x1FBE, 0x1FBE, -(7205), 0, 0x1FC3, 0x1FC3, 9, 0, 0x1FC8, 0x1FCB, 0, -(86), 0x1FCC, 0x1FCC, 0, -(9), 0x1FD0, 0x1FD1, 8, 0, 0x1FD8, 0x1FD9, 0, -(8), 0x1FDA, 0x1FDB, 0, -(100), 0x1FE0, 0x1FE1, 8, 0, 0x1FE5, 0x1FE5, 7, 0, 0x1FE8, 0x1FE9, 0, -(8), 0x1FEA, 0x1FEB, 0, -(112), 0x1FEC, 0x1FEC, 0, -(7), 0x1FF3, 0x1FF3, 9, 0, 0x1FF8, 0x1FF9, 0, -(128), 0x1FFA, 0x1FFB, 0, -(126), 0x1FFC, 0x1FFC, 0, -(9), 0x2126, 0x2126, 0, -(7517), 0x212A, 0x212A, 0, -(8383), 0x212B, 0x212B, 0, -(8262), 0x2132, 0x2132, 0, 28, 0x214E, 0x214E, -(28), 0, 0x2160, 0x216F, 0, 16, 0x2170, 0x217F, -(16), 0, 0x2183, 0x2184, -(3), -(3), 0x24B6, 0x24CF, 0, 26, 0x24D0, 0x24E9, -(26), 0, 0x2C00, 0x2C2F, 0, 48, 0x2C30, 0x2C5F, -(48), 0, 0x2C60, 0x2C61, -(3), -(3), 0x2C62, 0x2C62, 0, -(10743), 0x2C63, 0x2C63, 0, -(3814), 0x2C64, 0x2C64, 0, -(10727), 0x2C65, 0x2C65, -(10795), 0, 0x2C66, 0x2C66, -(10792), 0, 0x2C67, 0x2C6C, -(3), -(3), 0x2C6D, 0x2C6D, 0, -(10780), 0x2C6E, 0x2C6E, 0, -(10749), 0x2C6F, 0x2C6F, 0, -(10783), 0x2C70, 0x2C70, 0, -(10782), 0x2C72, 0x2C73, -(3), -(3), 0x2C75, 0x2C76, -(3), -(3), 0x2C7E, 0x2C7F, 0, -(10815), 0x2C80, 0x2CE3, -(3), -(3), 0x2CEB, 0x2CEE, -(3), -(3), 0x2CF2, 0x2CF3, -(3), -(3), 0x2D00, 0x2D25, -(7264), 0, 0x2D27, 0x2D27, -(7264), 0, 0x2D2D, 0x2D2D, -(7264), 0, 0xA640, 0xA66D, -(3), -(3), 0xA680, 0xA69B, -(3), -(3), 0xA722, 0xA72F, -(3), -(3), 0xA732, 0xA76F, -(3), -(3), 0xA779, 0xA77C, -(3), -(3), 0xA77D, 0xA77D, 0, -(35332), 0xA77E, 0xA787, -(3), -(3), 0xA78B, 0xA78C, -(3), -(3), 0xA78D, 0xA78D, 0, -(42280), 0xA790, 0xA793, -(3), -(3), 0xA794, 0xA794, 48, 0, 0xA796, 0xA7A9, -(3), -(3), 0xA7AA, 0xA7AA, 0, -(42308), 0xA7AB, 0xA7AB, 0, -(42319), 0xA7AC, 0xA7AC, 0, -(42315), 0xA7AD, 0xA7AD, 0, -(42305), 0xA7AE, 0xA7AE, 0, -(42308), 0xA7B0, 0xA7B0, 0, -(42258), 0xA7B1, 0xA7B1, 0, -(42282), 0xA7B2, 0xA7B2, 0, -(42261), 0xA7B3, 0xA7B3, 0, 928, 0xA7B4, 0xA7C3, -(3), -(3), 0xA7C4, 0xA7C4, 0, -(48), 0xA7C5, 0xA7C5, 0, -(42307), 0xA7C6, 0xA7C6, 0, -(35384), 0xA7C7, 0xA7CA, -(3), -(3), 0xA7D0, 0xA7D1, -(3), -(3), 0xA7D6, 0xA7D9, -(3), -(3), 0xA7F5, 0xA7F6, -(3), -(3), 0xAB53, 0xAB53, -(928), 0, 0xAB70, 0xABBF, -(38864), 0, 0xFF21, 0xFF3A, 0, 32, 0xFF41, 0xFF5A, -(32), 0, 0x10400, 0x10427, 0, 40, 0x10428, 0x1044F, -(40), 0, 0x104B0, 0x104D3, 0, 40, 0x104D8, 0x104FB, -(40), 0, 0x10570, 0x1057A, 0, 39, 0x1057C, 0x1058A, 0, 39, 0x1058C, 0x10592, 0, 39, 0x10594, 0x10595, 0, 39, 0x10597, 0x105A1, -(39), 0, 0x105A3, 0x105B1, -(39), 0, 0x105B3, 0x105B9, -(39), 0, 0x105BB, 0x105BC, -(39), 0, 0x10C80, 0x10CB2, 0, 64, 0x10CC0, 0x10CF2, -(64), 0, 0x118A0, 0x118BF, 0, 32, 0x118C0, 0x118DF, -(32), 0, 0x16E40, 0x16E5F, 0, 32, 0x16E60, 0x16E7F, -(32), 0, 0x1E900, 0x1E921, 0, 34, 0x1E922, 0x1E943, -(34), 0}, sizeof(builtin__rune_maps));
	memmove(g_autostr_type_stack, (i64[64]){0}, sizeof(g_autostr_type_stack));
	g_autostr_type_stack_len = 0;
	g_autostr_addr_state = (AutostrAddrStackState){0};
	as_cast_type_indexes = array_new(sizeof(VCastTypeIndexName), 0, 0);
	v_memory_panic = false;
	total_m = (i64)(0);
	builtin_init();
}

/* V3CACHE_MODULE main */
string IError__msg(IError* i) {
	if (i->_typ == 1938660593) return Error__msg(*(Error*)i->_object);
	if (i->_typ == 71273906) return MessageError__msg(*(MessageError*)i->_object);
	if (i->_typ == 2065246729) return Error__msg(((None__*)i->_object)->Error);
	return i->message;
}
/* V3CACHE_MODULE main */
i64 IError__code(IError* i) {
	if (i->_typ == 1938660593) return Error__code(*(Error*)i->_object);
	if (i->_typ == 71273906) return MessageError__code(*(MessageError*)i->_object);
	if (i->_typ == 2065246729) return Error__code(((None__*)i->_object)->Error);
	return i->code;
}
/* V3CACHE_MODULE main */
Array hash__Hash__sum(hash__Hash* i, Array _a0) {
	v_panic(_v3_lit_47_67a5effad7253ea3);
	return (Array){0};
}
/* V3CACHE_MODULE main */
i64 hash__Hash__size(hash__Hash* i) {
	v_panic(_v3_lit_48_e55a586fc0c6b73f);
	return (i64){0};
}
/* V3CACHE_MODULE main */
i64 hash__Hash__block_size(hash__Hash* i) {
	v_panic(_v3_lit_54_503bb76740bf2bb9);
	return (i64){0};
}
/* V3CACHE_MODULE main */
void hash__Hash__free(hash__Hash* i) {
	v_panic(_v3_lit_48_fb91f183b903b558);
}
/* V3CACHE_MODULE main */
void hash__Hash__reset(hash__Hash* i) {
	v_panic(_v3_lit_49_eb073e2877ead767);
}
/* V3CACHE_MODULE main */
Optional_i64 hash__Hash__write(hash__Hash* i, Array _a0) {
	v_panic(_v3_lit_49_2678ade7cd32896b);
	return (Optional_i64){0};
}
/* V3CACHE_MODULE main */
u32 hash__Hash32er__sum32(hash__Hash32er* i) {
	v_panic(_v3_lit_53_95bddd17dfe45e44);
	return (u32){0};
}
/* V3CACHE_MODULE main */
u64 hash__Hash64er__sum64(hash__Hash64er* i) {
	v_panic(_v3_lit_53_5f2d8f78123176b0);
	return (u64){0};
}

/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c17509efbc8ba5ce */
string Array_rune__string(Array ra) {
	Array sb = strings__new_builder(ra.len);
	strings__Builder__write_runes(&sb, ra);
	string res = strings__Builder__str(&sb);
	{
		strings__Builder__free(&sb);
	}
	return res;
}

/* V3CACHE_FN_END c17509efbc8ba5ce */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fee2dcab305043c6 */
void Array_string__free(Array* a) {
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < a->len; __for_idx_0++) {
			string* s = (string*)(array_get(*a, __for_idx_0));
			{
				string__free(s);
			}
		}
	}
	array* arr = (array*)(a);
	{
		array__free(arr);
	}
}

/* V3CACHE_FN_END fee2dcab305043c6 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e295cbef402768e0 */
string Array_string__join(Array a, string sep) {
	if (a.len == 0) {
		return _v3_lit_0_14650fb0739d0383;
	}
	i64 len = 0;
	{
		i64 __for_idx_0 = 0;
		for (; __for_idx_0 < a.len; __for_idx_0++) {
			string val = *(string*)(array_get(a, __for_idx_0));
			len += val.len + sep.len;
		}
	}
	len -= sep.len;
	string res = (string){.str = malloc_noscan(len + 1), .len = len};
	i64 idx = 0;
	{
		i64 i = 0;
		for (; i < a.len; i++) {
			string val = *(string*)(array_get(a, i));
			{
				vmemcpy((void*)(res.str + idx), (void*)(val.str), val.len);
				idx += val.len;
			}
			if (i != (a.len - 1)) {
				{
					vmemcpy((void*)(res.str + idx), (void*)(sep.str), sep.len);
					idx += sep.len;
				}
			}
		}
	}
	{
		(res.str)[res.len] = 0;
	}
	return res;
}

/* V3CACHE_FN_END e295cbef402768e0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7ea1967a0f9cb9c */
string Array_string__join_lines(Array s) {
	return Array_string__join(s, _v3_lit_1_44bd31d473cd01cb);
}

/* V3CACHE_FN_END 7ea1967a0f9cb9c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 132ff31646261ece */
void Array_string__sort_by_len(Array* s) {
	{
		i64 __sort_n_0 = s->len;
		Array __sort_buf_1 = array_new(		sizeof(string), __sort_n_0, __sort_n_0);
		{
			i64 __sort_w_2 = 1;
			for (; __sort_w_2 < __sort_n_0; __sort_w_2 = (i64)(((i64)(			__sort_w_2)) << (1))) {
				{
					i64 __sort_lo_3 = 0;
					for (; __sort_lo_3 < __sort_n_0; ) {
						i64 __sort_mid_4 = __sort_lo_3 + __sort_w_2;
						if (__sort_mid_4 > __sort_n_0) {
							__sort_mid_4 = __sort_n_0;
						}
						i64 __sort_hi_5 = __sort_mid_4 + __sort_w_2;
						if (__sort_hi_5 > __sort_n_0) {
							__sort_hi_5 = __sort_n_0;
						}
						i64 __sort_i_6 = __sort_lo_3;
						i64 __sort_j_7 = __sort_mid_4;
						{
							i64 __sort_k_8 = __sort_lo_3;
							for (; __sort_k_8 < __sort_hi_5; __sort_k_8++) {
								if ((__sort_j_7 >= __sort_hi_5) || ((__sort_i_6 < __sort_mid_4) && !(compare_strings_by_len(&(*(string*)array_get(*s, __sort_j_7)), &(*(string*)array_get(*s, __sort_i_6))) < 0))) {
									{ Array* _a0 = &__sort_buf_1; int _i0 = __sort_k_8; array__set(_a0, _i0, &(string[]){(*(string*)array_get(*s, __sort_i_6))}); }
									__sort_i_6 = __sort_i_6 + 1;
								} else {
									{ Array* _a1 = &__sort_buf_1; int _i1 = __sort_k_8; array__set(_a1, _i1, &(string[]){(*(string*)array_get(*s, __sort_j_7))}); }
									__sort_j_7 = __sort_j_7 + 1;
								}
							}
						}
						__sort_lo_3 = __sort_hi_5;
					}
				}
				{
					i64 __sort_c_9 = 0;
					for (; __sort_c_9 < __sort_n_0; __sort_c_9++) {
						{ Array* _a2 = s; int _i2 = __sort_c_9; array__set(_a2, _i2, &(string[]){(*(string*)array_get(__sort_buf_1, __sort_c_9))}); }
					}
				}
			}
		}
		array__free(&__sort_buf_1);
	}
	0;
}

/* V3CACHE_FN_END 132ff31646261ece */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b6fe12a7ffabf454 */
void Array_string__sort_ignore_case(Array* s) {
	{
		i64 __sort_n_0 = s->len;
		Array __sort_buf_1 = array_new(		sizeof(string), __sort_n_0, __sort_n_0);
		{
			i64 __sort_w_2 = 1;
			for (; __sort_w_2 < __sort_n_0; __sort_w_2 = (i64)(((i64)(			__sort_w_2)) << (1))) {
				{
					i64 __sort_lo_3 = 0;
					for (; __sort_lo_3 < __sort_n_0; ) {
						i64 __sort_mid_4 = __sort_lo_3 + __sort_w_2;
						if (__sort_mid_4 > __sort_n_0) {
							__sort_mid_4 = __sort_n_0;
						}
						i64 __sort_hi_5 = __sort_mid_4 + __sort_w_2;
						if (__sort_hi_5 > __sort_n_0) {
							__sort_hi_5 = __sort_n_0;
						}
						i64 __sort_i_6 = __sort_lo_3;
						i64 __sort_j_7 = __sort_mid_4;
						{
							i64 __sort_k_8 = __sort_lo_3;
							for (; __sort_k_8 < __sort_hi_5; __sort_k_8++) {
								if ((__sort_j_7 >= __sort_hi_5) || ((__sort_i_6 < __sort_mid_4) && !(compare_lower_strings(&(*(string*)array_get(*s, __sort_j_7)), &(*(string*)array_get(*s, __sort_i_6))) < 0))) {
									{ Array* _a0 = &__sort_buf_1; int _i0 = __sort_k_8; array__set(_a0, _i0, &(string[]){(*(string*)array_get(*s, __sort_i_6))}); }
									__sort_i_6 = __sort_i_6 + 1;
								} else {
									{ Array* _a1 = &__sort_buf_1; int _i1 = __sort_k_8; array__set(_a1, _i1, &(string[]){(*(string*)array_get(*s, __sort_j_7))}); }
									__sort_j_7 = __sort_j_7 + 1;
								}
							}
						}
						__sort_lo_3 = __sort_hi_5;
					}
				}
				{
					i64 __sort_c_9 = 0;
					for (; __sort_c_9 < __sort_n_0; __sort_c_9++) {
						{ Array* _a2 = s; int _i2 = __sort_c_9; array__set(_a2, _i2, &(string[]){(*(string*)array_get(__sort_buf_1, __sort_c_9))}); }
					}
				}
			}
		}
		array__free(&__sort_buf_1);
	}
	0;
}

/* V3CACHE_FN_END b6fe12a7ffabf454 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 331d2b29b44b95b */
string Array_string__str(Array a) {
	i64 sb_len = 4;
	if (a.len > 0) {
		sb_len += ((*((string*)((a).data) + (0)))).len;
		sb_len *= a.len;
	}
	sb_len += 2;
	Array sb = strings__new_builder(sb_len);
	strings__Builder__write_u8(&sb, '[');
	{
		i64 i = 0;
		for (; i < a.len; i++) {
			string val = (*((string*)((a).data) + (i)));
			strings__Builder__write_u8(&sb, '\'');
			strings__Builder__write_string(&sb, val);
			strings__Builder__write_u8(&sb, '\'');
			if (i < (a.len - 1)) {
				strings__Builder__write_string(&sb, _v3_lit_2_9afebb00c5c7fa67);
			}
		}
	}
	strings__Builder__write_u8(&sb, ']');
	string res = strings__Builder__str(&sb);
	{
		strings__Builder__free(&sb);
	}
	return res;
}

/* V3CACHE_FN_END 331d2b29b44b95b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8da254e43e3eb812 */
Optional_u32 Array_u8__byterune(Array b) {
	Optional_u32 __or_opt_0 = Array_u8__utf8_to_utf32(b);
	u32 __or_val_1 = 0;
	if (__or_opt_0.ok) {
		__or_val_1 = __or_opt_0.value;
	} else {
		return (Optional_u32){.ok = false, .err = __or_opt_0.err};
	}
	u32 r = __or_val_1;
	return (Optional_u32){.ok = true, .value = (u32)(r)};
	return (Optional_u32){.ok = true};
}

/* V3CACHE_FN_END 8da254e43e3eb812 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b289211594a3fd01 */
string Array_u8__bytestr(Array b) {
	{
		u8* buf = malloc_noscan(b.len + 1);
		vmemcpy((void*)(buf), b.data, b.len);
		(buf)[b.len] = 0;
		return tos(buf, b.len);
	}
}

/* V3CACHE_FN_END b289211594a3fd01 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7a7116623bd34021 */
string Array_u8__hex(Array b) {
	if (b.len == 0) {
		return _v3_lit_0_14650fb0739d0383;
	}
	return data_to_hex_string((u8*)(b.data), b.len);
}

/* V3CACHE_FN_END 7a7116623bd34021 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e271161e7077ecc8 */
Optional_u32 Array_u8__utf8_to_utf32(Array _bytes) {
	if (_bytes.len > 4) {
		return (Optional_u32){.ok = false, .err = (IError){._typ = 71273906, ._object = (MessageError*)memdup(&(MessageError){.msg = _v3_lit_74_82fc39ccb1421152, .code = 0}, sizeof(MessageError)), ._object_is_boxed = true, .message = _v3_lit_0_14650fb0739d0383, .code = 0}};
	}
	return (Optional_u32){.ok = true, .value = impl_utf8_to_utf32((u8*)(_bytes.data), _bytes.len)};
	return (Optional_u32){.ok = true};
}

/* V3CACHE_FN_END e271161e7077ecc8 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN cc2f401f8f659dbc */
string Error__msg(Error err) {
}

/* V3CACHE_FN_END cc2f401f8f659dbc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6427e6cfe549f430 */
void IError__free(IError* ie) {
}

/* V3CACHE_FN_END 6427e6cfe549f430 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6b159bfe6bdcdc19 */
string IError__str(IError err) {
}

/* V3CACHE_FN_END 6b159bfe6bdcdc19 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 3d00f5342785d48 */
void MessageError__free(MessageError* err) {
	{
		string__free(&err->msg);
	}
}

/* V3CACHE_FN_END 3d00f5342785d48 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1d906e3818edefa3 */
string MessageError__msg(MessageError err) {
}

/* V3CACHE_FN_END 1d906e3818edefa3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 66c38e17936c4bfe */
void SortedMap__free(SortedMap* m) {
}

/* V3CACHE_FN_END 66c38e17936c4bfe */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fb06abf1921ce233 */
void StrIntpData__process_str_intp_data(StrIntpData* data, Array* sb) {
	u32 x = data->fmt;
	int typ = (int)(x & 0x1F);
	i64 align = (i64)(((u32)(((u32)(	x)) >> (5))) & 0x01);
	bool upper_case = (((u32)(((u32)(	x)) >> (7))) & 0x01) > 0;
	i64 sign = (i64)(((u32)(((u32)(	x)) >> (8))) & 0x01);
	i64 precision = (i64)(((u32)(((u32)(	x)) >> (9))) & 0x7F);
	bool tail_zeros = (((u32)(((u32)(	x)) >> (16))) & 0x01) > 0;
	i64 width = (i64)((i16)(((u32)(((u32)(	x)) >> (17))) & 0x3FF));
	i64 base = (i64)((u32)(((u32)(	x)) >> (27))) & 0xF;
	u8 fmt_pad_ch = (u8)(((u32)(((u32)(	x)) >> (31))) & 0xFF);
	bool has_dynamic_width = (data->dyn_flags & builtin__str_intp_has_dynamic_width) != 0;
	bool has_dynamic_precision = (data->dyn_flags & builtin__str_intp_has_dynamic_precision) != 0;
	if (typ == StrIntpType__si_no_str) {
		return;
	}
	if (base > 0) {
		base += 2;
	}
	if (has_dynamic_width) {
		width = data->dyn_width;
		if (width < 0) {
			width = -width;
			align = 0;
		} else if (width > 0) {
			align = 1;
		}
	}
	if (has_dynamic_precision) {
		precision = data->dyn_precision;
	}
	u8 pad_ch = (u8)(' ');
	if (fmt_pad_ch > 0) {
		pad_ch = '0';
	}
	i64 __if_val_0 = 0;
	if (width > 0) {
		__if_val_0 = width;
	} else {
		__if_val_0 = -1;
	}
	i64 len0_set = __if_val_0;
	i64 __if_val_1 = 0;
	if (has_dynamic_precision) {
		i64 __if_val_2 = 0;
		if (precision >= 0) {
			__if_val_2 = precision;
		} else {
			__if_val_2 = -1;
		}
		__if_val_1 = __if_val_2;
	} else {
		if (precision == 0x7F) {
			__if_val_1 = -1;
		} else {
			__if_val_1 = precision;
		}
	}
	i64 len1_set = __if_val_1;
	bool sign_set = sign == 1;
	strconv__BF_param bf = (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0_set, .len1 = len1_set, .positive = true, .sign_flag = sign_set, .align = strconv__Align_text__left, .rm_tail_zero = tail_zeros};
	if ((fmt_pad_ch == 0) || (pad_ch == '0')) {
		if (align == 0) {
			bf.align = strconv__Align_text__left;
		} else if (align == 1) {
			bf.align = strconv__Align_text__right;
		} else {
			bf.align = strconv__Align_text__left;
		}
	} else {
		bf.align = strconv__Align_text__right;
	}
	{
		if (typ == StrIntpType__si_s) {
			if (upper_case) {
				string s = string__to_upper(data->d.d_s);
				if (width == 0) {
					strings__Builder__write_string(sb, s);
				} else {
					strconv__format_str_sb(s, bf, sb);
				}
				string__free(&s);
			} else {
				if (width == 0) {
					strings__Builder__write_string(sb, data->d.d_s);
				} else {
					strconv__format_str_sb(data->d.d_s, bf, sb);
				}
			}
			return;
		}
		if (typ == StrIntpType__si_r) {
			if (width > 0) {
				if (upper_case) {
					string s = string__to_upper(data->d.d_s);
					i64 __if_val_3 = 0;
					if (width > 0) {
						__if_val_3 = width;
					} else {
						__if_val_3 = 0;
					}
					i64 __in_lhs_4 = (1 + (__if_val_3));
					{
						i64 __discard_1_64440_64441 = 1;
						for (; __discard_1_64440_64441 < __in_lhs_4; __discard_1_64440_64441++) {
							strings__Builder__write_string(sb, s);
						}
					}
					string__free(&s);
				} else {
					i64 __if_val_5 = 0;
					if (width > 0) {
						__if_val_5 = width;
					} else {
						__if_val_5 = 0;
					}
					i64 __in_lhs_6 = (1 + (__if_val_5));
					{
						i64 __discard_1_64584_64585 = 1;
						for (; __discard_1_64584_64585 < __in_lhs_6; __discard_1_64584_64585++) {
							strings__Builder__write_string(sb, data->d.d_s);
						}
					}
				}
			}
			return;
		}
		if ((typ == StrIntpType__si_i8) || (typ == StrIntpType__si_i16) || (typ == StrIntpType__si_i32) || (typ == StrIntpType__si_i64)) {
			i64 d = data->d.d_i64;
			if (typ == StrIntpType__si_i8) {
				d = (i64)(data->d.d_i8);
			} else if (typ == StrIntpType__si_i16) {
				d = (i64)(data->d.d_i16);
			} else if (typ == StrIntpType__si_i32) {
				d = (i64)(data->d.d_i32);
			}
			if (base == 0) {
				if (d < 0) {
					bf.positive = false;
				}
				strconv__format_dec_sb(abs64(d), bf, sb);
			} else {
				if (base == 3) {
					base = 2;
				}
				i64 absd = d;
				bool write_minus = false;
				if ((d < 0) && (pad_ch != ' ')) {
					absd = -d;
					write_minus = true;
				}
				string hx = strconv__format_int(absd, base);
				if (upper_case) {
					string tmp = hx;
					hx = string__to_upper(hx);
					string__free(&tmp);
				}
				if (write_minus) {
					strings__Builder__write_u8(sb, '-');
					bf.len0--;
				}
				if (width == 0) {
					strings__Builder__write_string(sb, hx);
				} else {
					strconv__format_str_sb(hx, bf, sb);
				}
				string__free(&hx);
			}
			return;
		}
		if ((typ == StrIntpType__si_u8) || (typ == StrIntpType__si_u16) || (typ == StrIntpType__si_u32) || (typ == StrIntpType__si_u64)) {
			u64 d = data->d.d_u64;
			if (typ == StrIntpType__si_u8) {
				d = (u64)(data->d.d_u8);
			} else if (typ == StrIntpType__si_u16) {
				d = (u64)(data->d.d_u16);
			} else if (typ == StrIntpType__si_u32) {
				d = (u64)(data->d.d_u32);
			}
			if (base == 0) {
				strconv__format_dec_sb(d, bf, sb);
			} else {
				if (base == 3) {
					base = 2;
				}
				string hx = strconv__format_uint(d, base);
				if (upper_case) {
					string tmp = hx;
					hx = string__to_upper(hx);
					string__free(&tmp);
				}
				if (width == 0) {
					strings__Builder__write_string(sb, hx);
				} else {
					strconv__format_str_sb(hx, bf, sb);
				}
				string__free(&hx);
			}
			return;
		}
		if (typ == StrIntpType__si_p) {
			u64 d = (u64)(data->d.d_p);
			base = 16;
			if (base == 0) {
				if (width == 0) {
					string d_str = u64__str(d);
					strings__Builder__write_string(sb, d_str);
					string__free(&d_str);
					return;
				}
				strconv__format_dec_sb(d, bf, sb);
			} else {
				string hx = strconv__format_uint(d, base);
				if (upper_case) {
					string tmp = hx;
					hx = string__to_upper(hx);
					string__free(&tmp);
				}
				if (width == 0) {
					strings__Builder__write_string(sb, hx);
				} else {
					strconv__format_str_sb(hx, bf, sb);
				}
				string__free(&hx);
			}
			return;
		}
		bool use_default_str = false;
		if ((width == 0) && (precision == 0x7F)) {
			bf.len1 = 3;
			use_default_str = true;
		}
		if (bf.len1 < 0) {
			bf.len1 = 3;
		}
		if (typ == StrIntpType__si_f32) {
			{
				if (use_default_str) {
					string f = f32__str(data->d.d_f32);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				} else {
					if (data->d.d_f32 < 0) {
						bf.positive = false;
					}
					string f = strconv__format_fl(data->d.d_f32, bf);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				}
			}
		} else if (typ == StrIntpType__si_f64) {
			{
				if (use_default_str) {
					string f = f64__str(data->d.d_f64);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				} else {
					if (data->d.d_f64 < 0) {
						bf.positive = false;
					}
					strconv__Float64u f_union = (strconv__Float64u){.f = data->d.d_f64};
					if (f_union.u == strconv__double_minus_zero) {
						bf.positive = false;
					}
					string f = strconv__format_fl(data->d.d_f64, bf);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				}
			}
		} else if (typ == StrIntpType__si_g32) {
			if (use_default_str) {
				{
					string f = f32__strg(data->d.d_f32);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				}
			} else {
				if (data->d.d_f32 == strconv__single_plus_zero) {
					string tmp_str = _v3_lit_1_44bd5bd473cd4929;
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
					return;
				}
				if (data->d.d_f32 == strconv__single_minus_zero) {
					string tmp_str = _v3_lit_2_9afb2500c5c4c5ae;
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
					return;
				}
				if (data->d.d_f32 == strconv__single_plus_infinity) {
					string tmp_str = _v3_lit_4_d33abcd302174483;
					if (upper_case) {
						tmp_str = _v3_lit_4_e8d6bcd39f7348a3;
					}
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
				}
				if (data->d.d_f32 == strconv__single_minus_infinity) {
					string tmp_str = _v3_lit_4_e88841077bedea49;
					if (upper_case) {
						tmp_str = _v3_lit_4_fefe81081a03fee9;
					}
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
				}
				if (data->d.d_f32 < 0) {
					bf.positive = false;
				}
				float d = fabs32(data->d.d_f32);
				if ((d < (float)(999999.0)) && (d >= (float)(0.00001))) {
					string f = strconv__format_fl(data->d.d_f32, bf);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
					return;
				}
				bf.len1--;
				string f = strconv__format_es(data->d.d_f32, bf);
				if (upper_case) {
					string tmp = f;
					f = string__to_upper(f);
					string__free(&tmp);
				}
				strings__Builder__write_string(sb, f);
				string__free(&f);
			}
		} else if (typ == StrIntpType__si_g64) {
			if (use_default_str) {
				{
					string f = f64__strg(data->d.d_f64);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				}
			} else {
				if (data->d.d_f64 == strconv__double_plus_zero) {
					string tmp_str = _v3_lit_1_44bd5bd473cd4929;
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
					return;
				}
				if (data->d.d_f64 == strconv__double_minus_zero) {
					string tmp_str = _v3_lit_2_9afb2500c5c4c5ae;
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
					return;
				}
				if (data->d.d_f64 == strconv__double_plus_infinity) {
					string tmp_str = _v3_lit_4_d33abcd302174483;
					if (upper_case) {
						tmp_str = _v3_lit_4_e8d6bcd39f7348a3;
					}
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
				}
				if (data->d.d_f64 == strconv__double_minus_infinity) {
					string tmp_str = _v3_lit_4_e88841077bedea49;
					if (upper_case) {
						tmp_str = _v3_lit_4_fefe81081a03fee9;
					}
					strconv__format_str_sb(tmp_str, bf, sb);
					string__free(&tmp_str);
				}
				if (data->d.d_f64 < 0) {
					bf.positive = false;
				}
				double d = fabs64(data->d.d_f64);
				if ((d < 999999.0) && (d >= 0.00001)) {
					string f = strconv__format_fl(data->d.d_f64, bf);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
					return;
				}
				bf.len1--;
				string f = strconv__format_es(data->d.d_f64, bf);
				if (upper_case) {
					string tmp = f;
					f = string__to_upper(f);
					string__free(&tmp);
				}
				strings__Builder__write_string(sb, f);
				string__free(&f);
			}
		} else if (typ == StrIntpType__si_e32) {
			{
				if (use_default_str) {
					string f = f32__str(data->d.d_f32);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				} else {
					if (data->d.d_f32 < 0) {
						bf.positive = false;
					}
					string f = strconv__format_es(data->d.d_f32, bf);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				}
			}
		} else if (typ == StrIntpType__si_e64) {
			{
				if (use_default_str) {
					string f = f64__str(data->d.d_f64);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				} else {
					if (data->d.d_f64 < 0) {
						bf.positive = false;
					}
					string f = strconv__format_es(data->d.d_f64, bf);
					if (upper_case) {
						string tmp = f;
						f = string__to_upper(f);
						string__free(&tmp);
					}
					strings__Builder__write_string(sb, f);
					string__free(&f);
				}
			}
		} else if (typ == StrIntpType__si_c) {
			string ss = utf32_to_str(data->d.d_c);
			strings__Builder__write_string(sb, ss);
			string__free(&ss);
		} else if (typ == StrIntpType__si_vp) {
			string ss = u64__hex((u64)(data->d.d_vp));
			strings__Builder__write_string(sb, ss);
			string__free(&ss);
		} else {
			strings__Builder__write_string(sb, _v3_lit_12_77dde251e7b557a0);
		}
	}
}

/* V3CACHE_FN_END fb06abf1921ce233 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1e7d831a65bfde2a */
void VAssertMetaInfo__free(VAssertMetaInfo* ami) {
	{
		string__free(&ami->fpath);
		string__free(&ami->fn_name);
		string__free(&ami->src);
		string__free(&ami->op);
		string__free(&ami->llabel);
		string__free(&ami->rlabel);
		string__free(&ami->lvalue);
		string__free(&ami->rvalue);
		string__free(&ami->message);
	}
}

/* V3CACHE_FN_END 1e7d831a65bfde2a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 98cdee6820bddbd */
array __new_array(i64 mylen, i64 cap, i64 elm_size) {
}

/* V3CACHE_FN_END 98cdee6820bddbd */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d51613806ec31e53 */
void _result_ok_markused(void) {
}

/* V3CACHE_FN_END d51613806ec31e53 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 54eb104242c087f9 */
u64 abs64(i64 x) {
}

/* V3CACHE_FN_END 54eb104242c087f9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d37345df1f1ae931 */
array array__clone(array* a) {
}

/* V3CACHE_FN_END d37345df1f1ae931 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ad5dded93ba5e0e1 */
void array__delete(array* a, i64 i) {
}

/* V3CACHE_FN_END ad5dded93ba5e0e1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 890142f5b6fba79e */
void array__delete_last(array* a) {
}

/* V3CACHE_FN_END 890142f5b6fba79e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c9e9dc16aeec0f73 */
void array__ensure_cap(array* a, i64 required) {
}

/* V3CACHE_FN_END c9e9dc16aeec0f73 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6b28bf95b11f329e */
void array__free(array* a) {
}

/* V3CACHE_FN_END 6b28bf95b11f329e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1d74773ef206193a */
void* array__get(array a, i64 i) {
}

/* V3CACHE_FN_END 1d74773ef206193a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e3560fe70e9ac20c */
void* array__get_i64(array a, i64 i) {
}

/* V3CACHE_FN_END e3560fe70e9ac20c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 44dc06f4c8d92290 */
void* array__get_ni(array a, i64 i) {
}

/* V3CACHE_FN_END 44dc06f4c8d92290 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 33d68fc62bf6b3e0 */
void* array__get_u64(array a, u64 i) {
}

/* V3CACHE_FN_END 33d68fc62bf6b3e0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 3f38b961c7761f90 */
void* array__get_with_check_i64(array a, i64 i) {
}

/* V3CACHE_FN_END 3f38b961c7761f90 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 33ee4a1837eb33e4 */
void* array__get_with_check_ni(array a, i64 i) {
}

/* V3CACHE_FN_END 33ee4a1837eb33e4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c42b3876a8ab6cdc */
void* array__get_with_check_u64(array a, u64 i) {
}

/* V3CACHE_FN_END c42b3876a8ab6cdc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 32d7a67fffd84603 */
void array__insert(array* a, i64 i, void* val) {
}

/* V3CACHE_FN_END 32d7a67fffd84603 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2c922c3f29c5c7b9 */
void array__insert_many(array* a, i64 i, void* val, i64 size) {
}

/* V3CACHE_FN_END 2c922c3f29c5c7b9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 26cba1fe9af25b5b */
void* array__pop_left(array* a) {
}

/* V3CACHE_FN_END 26cba1fe9af25b5b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7ed8dcce1e6bb36e */
void array__prepend(array* a, void* val) {
}

/* V3CACHE_FN_END 7ed8dcce1e6bb36e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2f6e21d108e7f4b4 */
void array__push(array* a, void* val) {
}

/* V3CACHE_FN_END 2f6e21d108e7f4b4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e2827aab5de2548c */
void array__push_many(array* a, void* val, i64 size) {
}

/* V3CACHE_FN_END e2827aab5de2548c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 21e4cedf5b4d42a4 */
array array__reverse(array a) {
}

/* V3CACHE_FN_END 21e4cedf5b4d42a4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d5ebe6de6ce3f656 */
void array__set(array* a, i64 i, void* val) {
}

/* V3CACHE_FN_END d5ebe6de6ce3f656 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 67c87179c19fe370 */
void array__set_i64(array* a, i64 i, void* val) {
}

/* V3CACHE_FN_END 67c87179c19fe370 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ba89b46013b01d44 */
void array__set_ni(array* a, i64 i, void* val) {
}

/* V3CACHE_FN_END ba89b46013b01d44 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 432970911842b4bc */
void array__set_u64(array* a, u64 i, void* val) {
}

/* V3CACHE_FN_END 432970911842b4bc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN db1d0c4a068aece8 */
array array__slice(array a, i64 start, i64 _end) {
}

/* V3CACHE_FN_END db1d0c4a068aece8 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fe683321bc4713da */
array array__slice_ni(array a, i64 _start, i64 _end) {
}

/* V3CACHE_FN_END fe683321bc4713da */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4a02df1aadb14791 */
void array__sort_with_compare(array* a, _fn_ptr_ed95774d3a4e97ab callback) {
}

/* V3CACHE_FN_END 4a02df1aadb14791 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 429c8bf90651e5d4 */
bool autostr_addr_in_stack(void* addr) {
}

/* V3CACHE_FN_END 429c8bf90651e5d4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 58318520f3933f1f */
void autostr_addr_pop(void) {
}

/* V3CACHE_FN_END 58318520f3933f1f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c79515217fba3484 */
void autostr_addr_push(void* addr) {
}

/* V3CACHE_FN_END c79515217fba3484 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4c95e2845bb9b2a5 */
bool autostr_addr_type_in_stack(void* addr, i64 typ) {
}

/* V3CACHE_FN_END 4c95e2845bb9b2a5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bb49954eb5834621 */
void autostr_addr_type_push(void* addr, i64 typ) {
}

/* V3CACHE_FN_END bb49954eb5834621 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ed67aaa8d04b1603 */
string autostr_array_circular(i64 len) {
}

/* V3CACHE_FN_END ed67aaa8d04b1603 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e09049da78789b17 */
bool autostr_type_in_stack(i64 typ) {
}

/* V3CACHE_FN_END e09049da78789b17 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8168be8388839f6e */
void autostr_type_pop(void) {
}

/* V3CACHE_FN_END 8168be8388839f6e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ad7dcfd457a1a723 */
void autostr_type_push(i64 typ) {
}

/* V3CACHE_FN_END ad7dcfd457a1a723 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN efb6157c75b11190 */
string bool__str(bool b) {
}

/* V3CACHE_FN_END efb6157c75b11190 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 42b47ab371d21dc1 */
void builtin_init(void) {
}

/* V3CACHE_FN_END 42b47ab371d21dc1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 73746fd623a6ebf6 */
Array byteptr__vbytes(u8* data, i64 len) {
}

/* V3CACHE_FN_END 73746fd623a6ebf6 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ceb6025b5115b678 */
string byteptr__vstring(u8* bp) {
}

/* V3CACHE_FN_END ceb6025b5115b678 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 5e341e22961a8471 */
string byteptr__vstring_with_len(u8* bp, i64 len) {
}

/* V3CACHE_FN_END 5e341e22961a8471 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9c592329d37372ee */
string char__hex(char c) {
	return u8__hex((u8)(c));
}

/* V3CACHE_FN_END 9c592329d37372ee */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7d04e8ea9804d4be */
string charptr__vstring(char* cp) {
}

/* V3CACHE_FN_END 7d04e8ea9804d4be */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7da4126a5e8b03d3 */
string charptr__vstring_with_len(char* cp, i64 len) {
}

/* V3CACHE_FN_END 7da4126a5e8b03d3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f16c6ee86f14e483 */
i64 compare_lower_strings(string* a, string* b) {
}

/* V3CACHE_FN_END f16c6ee86f14e483 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 96ef12482fab8f95 */
i64 compare_strings_by_len(string* a, string* b) {
}

/* V3CACHE_FN_END 96ef12482fab8f95 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c7cdb207fffd2a3d */
string data_to_hex_string(u8* data, i64 len) {
}

/* V3CACHE_FN_END c7cdb207fffd2a3d */
/* V3CACHE_MODULE __v3_program_specializations */
/* V3CACHE_FN_BEGIN b62b0b4f9d3d6b89 */
void drop_owned_interface_T_IError(IError value) {
	({
		extern IError builtin__none__;
		extern IError builtin__error_sentinel;
		string__free(&((		value).message));
		if ((		value)._object_is_boxed && ((		value)._object) != NULL && ((		value)._object) != builtin__none__._object && ((		value)._object) != builtin__error_sentinel._object) {
			switch ((		value)._typ) {
			case 71273906:
				string__free(&(((MessageError*)((		value)._object))->msg));
				break;
			default: break;
			}
			free(((		value)._object));
			(		value)._object = NULL;
			(		value)._object_is_boxed = false;
		}
	});
}

/* V3CACHE_FN_END b62b0b4f9d3d6b89 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 42b9a9dbe12d86f */
void drop_owned_result_error(IError err) {
	OwnershipIErrorPayload* raw_err = (OwnershipIErrorPayload*)(&err);
	OwnershipIErrorPayload* none_err = (OwnershipIErrorPayload*)(&builtin__none__);
	OwnershipIErrorPayload* sentinel_err = (OwnershipIErrorPayload*)(&builtin__error_sentinel);
	if (raw_err->payload == NULL) {
		string message = IError__msg(&(err));
		{
			string__free(&message);
		}
		return;
	}
	if ((raw_err->payload == none_err->payload) || (raw_err->payload == sentinel_err->payload)) {
		return;
	}
	drop_owned_result_error_interface(err);
}

/* V3CACHE_FN_END 42b9a9dbe12d86f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b9190a3a522715a3 */
void drop_owned_result_error_interface(IError err) {
	IError owned = err;
	OwnershipV3InterfacePayload* raw_interface = (OwnershipV3InterfacePayload*)(&owned);
	if (raw_interface->is_boxed) {
		({
			extern IError builtin__none__;
			extern IError builtin__error_sentinel;
			string__free(&((			owned).message));
			if ((			owned)._object_is_boxed && ((			owned)._object) != NULL && ((			owned)._object) != builtin__none__._object && ((			owned)._object) != builtin__error_sentinel._object) {
				switch ((			owned)._typ) {
				case 71273906:
					string__free(&(((MessageError*)((			owned)._object))->msg));
					break;
				default: break;
				}
				free(((			owned)._object));
				(			owned)._object = NULL;
				(			owned)._object_is_boxed = false;
			}
		});
	}
}

/* V3CACHE_FN_END b9190a3a522715a3 */
/* V3CACHE_MODULE __v3_program_specializations */
/* V3CACHE_FN_BEGIN 21f8dc1c1b85d5fd */
void drop_owned_v3_interface_T_IError(IError value) {
	{
		IError owned = value;
		OwnershipV3InterfacePayload* raw_interface = (OwnershipV3InterfacePayload*)(&owned);
		if (raw_interface->is_boxed) {
			({
				extern IError builtin__none__;
				extern IError builtin__error_sentinel;
				string__free(&((				owned).message));
				if ((				owned)._object_is_boxed && ((				owned)._object) != NULL && ((				owned)._object) != builtin__none__._object && ((				owned)._object) != builtin__error_sentinel._object) {
					switch ((				owned)._typ) {
					case 71273906:
						string__free(&(((MessageError*)((				owned)._object))->msg));
						break;
					default: break;
					}
					free(((				owned)._object));
					(				owned)._object = NULL;
					(				owned)._object_is_boxed = false;
				}
			});
		}
	}
}

/* V3CACHE_FN_END 21f8dc1c1b85d5fd */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8ffe6707f18b9d9b */
void eprintln(string s) {
}

/* V3CACHE_FN_END 8ffe6707f18b9d9b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN eea323d85c2e6301 */
IError error(string message) {
}

/* V3CACHE_FN_END eea323d85c2e6301 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 631c23b74134a274 */
IError error_with_code(string message, i64 code) {
}

/* V3CACHE_FN_END 631c23b74134a274 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f94764e238d21d21 */
string f32__str(float x) {
}

/* V3CACHE_FN_END f94764e238d21d21 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 64684a668b4f6e92 */
string f32__strg(float x) {
}

/* V3CACHE_FN_END 64684a668b4f6e92 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 83469070871228f0 */
string f64__str(double x) {
}

/* V3CACHE_FN_END 83469070871228f0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 24a77e358534de45 */
string f64__strg(double x) {
}

/* V3CACHE_FN_END 24a77e358534de45 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f528beab445332fe */
float fabs32(float x) {
}

/* V3CACHE_FN_END f528beab445332fe */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c9c4f1ab2bb9e34b */
double fabs64(double x) {
}

/* V3CACHE_FN_END c9c4f1ab2bb9e34b */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4906e80de9a92e6a */
string i16__hex(i16 nn) {
}

/* V3CACHE_FN_END 4906e80de9a92e6a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6a2fa1680fb8e424 */
string i16__str(i16 n) {
}

/* V3CACHE_FN_END 6a2fa1680fb8e424 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6d2bfb0dc48823b2 */
string i32__str(i32 n) {
}

/* V3CACHE_FN_END 6d2bfb0dc48823b2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e2cfb9998eed7f03 */
string i64__str(i64 nn) {
}

/* V3CACHE_FN_END e2cfb9998eed7f03 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e032bda476a0be05 */
string i8__hex(i8 nn) {
}

/* V3CACHE_FN_END e032bda476a0be05 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bed2044a506012db */
string i8__str(i8 n) {
}

/* V3CACHE_FN_END bed2044a506012db */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 6f288629cc4ba652 */
u32 impl_utf8_to_utf32(u8* _bytes, i64 _bytes_len) {
}

/* V3CACHE_FN_END 6f288629cc4ba652 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 18edd4dd1872f295 */
string int__hex(i64 nn) {
}

/* V3CACHE_FN_END 18edd4dd1872f295 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 34bd3c8f8e76ebab */
string int__str(i64 n) {
}

/* V3CACHE_FN_END 34bd3c8f8e76ebab */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 282eea017aadf12a */
u8* malloc_noscan(ptrdiff_t n) {
}

/* V3CACHE_FN_END 282eea017aadf12a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e20edfa91a2acf58 */
void map__clear(map* m) {
}

/* V3CACHE_FN_END e20edfa91a2acf58 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 190ccc74cb115d94 */
map map__clone(map* m) {
}

/* V3CACHE_FN_END 190ccc74cb115d94 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 3cb0f2e8bd1e019a */
void map__delete(map* m, void* key) {
}

/* V3CACHE_FN_END 3cb0f2e8bd1e019a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 145bec171c556b43 */
bool map__exists(map* m, void* key) {
}

/* V3CACHE_FN_END 145bec171c556b43 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2a26cc4f314537c1 */
void map__free(map* m) {
}

/* V3CACHE_FN_END 2a26cc4f314537c1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 995966f84b0a8f47 */
void* map__get(map* m, void* key, void* zero) {
}

/* V3CACHE_FN_END 995966f84b0a8f47 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e59c67a9c518d0bc */
void* map__get_and_set(map* m, void* key, void* zero) {
}

/* V3CACHE_FN_END e59c67a9c518d0bc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 75a5985fa57149c2 */
void* map__get_check(map* m, void* key) {
}

/* V3CACHE_FN_END 75a5985fa57149c2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4bc63cb7baecdb8f */
array map__keys(map* m) {
}

/* V3CACHE_FN_END 4bc63cb7baecdb8f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fa03d7485b11b8ff */
void map__reserve(map* m, u32 n) {
}

/* V3CACHE_FN_END fa03d7485b11b8ff */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d31ad79edf8977b3 */
void map__set(map* m, void* key, void* value) {
}

/* V3CACHE_FN_END d31ad79edf8977b3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN a819ba10e3b2bb19 */
array map__values(map* m) {
}

/* V3CACHE_FN_END a819ba10e3b2bb19 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1db2d78b5fd26a65 */
void map_clone_int_1(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 1db2d78b5fd26a65 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1dbcd78b5fdabeea */
void map_clone_int_2(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 1dbcd78b5fdabeea */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1dc2d78b5fdf2a98 */
void map_clone_int_4(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 1dc2d78b5fdf2a98 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1d9ad78b5fbdd884 */
void map_clone_int_8(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 1d9ad78b5fbdd884 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 457e536d698cdeab */
void map_clone_string(void* dest, void* pkey) {
}

/* V3CACHE_FN_END 457e536d698cdeab */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 15f80314caa57e4a */
bool map_eq_int_1(void* a, void* b) {
}

/* V3CACHE_FN_END 15f80314caa57e4a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 15ee0314ca9d29c5 */
bool map_eq_int_2(void* a, void* b) {
}

/* V3CACHE_FN_END 15ee0314ca9d29c5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 16020314caadd2cf */
bool map_eq_int_4(void* a, void* b) {
}

/* V3CACHE_FN_END 16020314caadd2cf */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 15da0314ca8c80bb */
bool map_eq_int_8(void* a, void* b) {
}

/* V3CACHE_FN_END 15da0314ca8c80bb */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4f1037580447a032 */
bool map_eq_string(void* a, void* b) {
}

/* V3CACHE_FN_END 4f1037580447a032 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d7116abe859fd08e */
void map_free_nop(void* _0) {
}

/* V3CACHE_FN_END d7116abe859fd08e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8ef75d42480f8d9a */
void map_free_string(void* pkey) {
	{
		string__free(&(*(string*)(pkey)));
	}
}

/* V3CACHE_FN_END 8ef75d42480f8d9a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 373b9ffb5f313604 */
u64 map_hash_int_1(void* pkey) {
}

/* V3CACHE_FN_END 373b9ffb5f313604 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 373d9ffb5f31b8db */
u64 map_hash_int_2(void* pkey) {
}

/* V3CACHE_FN_END 373d9ffb5f31b8db */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 37459ffb5f398a89 */
u64 map_hash_int_4(void* pkey) {
}

/* V3CACHE_FN_END 37459ffb5f398a89 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 37519ffb5f4261e5 */
u64 map_hash_int_8(void* pkey) {
}

/* V3CACHE_FN_END 37519ffb5f4261e5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN ea13ceb11bf748b0 */
u64 map_hash_string(void* pkey) {
}

/* V3CACHE_FN_END ea13ceb11bf748b0 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 509960cb499c6ced */
bool map_map_eq(map a, map b) {
}

/* V3CACHE_FN_END 509960cb499c6ced */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 314e873f2d7ff795 */
void mapnode__free(mapnode* n) {
}

/* V3CACHE_FN_END 314e873f2d7ff795 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 88d31680a9c321c1 */
void* memdup(void* src, ptrdiff_t sz) {
}

/* V3CACHE_FN_END 88d31680a9c321c1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b395adad7c7bd500 */
array new_array_from_c_array(i64 len, i64 cap, i64 elm_size, void* c_array) {
}

/* V3CACHE_FN_END b395adad7c7bd500 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN cac6b38f80dcaebb */
array new_array_from_c_array_noscan(i64 len, i64 cap, i64 elm_size, void* c_array) {
}

/* V3CACHE_FN_END cac6b38f80dcaebb */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 48ac772a4b576419 */
VNORETURN void panic_n(string s, i64 number1) {
}

/* V3CACHE_FN_END 48ac772a4b576419 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN d72562de07cac74f */
VNORETURN void panic_n2(string s, i64 number1, i64 number2) {
}

/* V3CACHE_FN_END d72562de07cac74f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f7d60598ffe1fd10 */
void println(string s) {
}

/* V3CACHE_FN_END f7d60598ffe1fd10 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 5104678e1e5e8f41 */
string ptr_str(void* ptr) {
}

/* V3CACHE_FN_END 5104678e1e5e8f41 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9a223e42ab60ddd8 */
Array rune__bytes(u32 c) {
}

/* V3CACHE_FN_END 9a223e42ab60ddd8 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 80b703b124e7c8f4 */
string rune__str(u32 c) {
}

/* V3CACHE_FN_END 80b703b124e7c8f4 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 867678a31926433c */
u32 rune__to_lower(u32 c) {
}

/* V3CACHE_FN_END 867678a31926433c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 199d7c5524ab2601 */
string str_intp_sub(string base_str, string in_str) {
	Optional_i64 __or_opt_0 = string__index(base_str, _v3_lit_2_9ae02a00c5ae0675);
	i64 __or_val_1 = 0;
	if (__or_opt_0.ok) {
		__or_val_1 = __or_opt_0.value;
	} else {
		IError err = __or_opt_0.err;
		eprintln(_v3_lit_37_88d8f63cec77379d);
		v_exit(1);
	}
	i64 v_index = __or_val_1;
	{
		string st_str = string__substr(		base_str, 0, 		v_index);
		if ((v_index + 2) < base_str.len) {
			string en_str = string__substr(			base_str, 			v_index + 2, (			base_str).len);
			string res_str = ({ string __str_plus_part_0_0 = _v3_lit_47_3f2e1d05be76b5e9; string __str_plus_part_0_1 = st_str; string __str_plus_part_0_2 = _v3_lit_4_42ca449b60800bd2; string __str_plus_part_0_3 = builtin__si_s_code; string __str_plus_part_0_4 = _v3_lit_10_acdfc69f923b1745; string __str_plus_part_0_5 = in_str; string __str_plus_part_0_6 = _v3_lit_18_c76639494a2ef036; string __str_plus_part_0_7 = en_str; string __str_plus_part_0_8 = _v3_lit_23_3741aa05dc09a04c; string __str_plus_acc_0_1 = string__plus(__str_plus_part_0_0, __str_plus_part_0_1); string __str_plus_acc_0_2 = string__plus(__str_plus_acc_0_1, __str_plus_part_0_2); string__free(&__str_plus_acc_0_1); string __str_plus_acc_0_3 = string__plus(__str_plus_acc_0_2, __str_plus_part_0_3); string__free(&__str_plus_acc_0_2); string __str_plus_acc_0_4 = string__plus(__str_plus_acc_0_3, __str_plus_part_0_4); string__free(&__str_plus_acc_0_3); string __str_plus_acc_0_5 = string__plus(__str_plus_acc_0_4, __str_plus_part_0_5); string__free(&__str_plus_acc_0_4); string __str_plus_acc_0_6 = string__plus(__str_plus_acc_0_5, __str_plus_part_0_6); string__free(&__str_plus_acc_0_5); string __str_plus_acc_0_7 = string__plus(__str_plus_acc_0_6, __str_plus_part_0_7); string__free(&__str_plus_acc_0_6); string __str_plus_acc_0_8 = string__plus(__str_plus_acc_0_7, __str_plus_part_0_8); string__free(&__str_plus_acc_0_7); __str_plus_acc_0_8; });
			string__free(&st_str);
			string__free(&en_str);
			return res_str;
		}
		string res2_str = ({ string __str_plus_part_1_0 = _v3_lit_47_1f7788b2d2b7fc94; string __str_plus_part_1_1 = st_str; string __str_plus_part_1_2 = _v3_lit_4_42ca449b60800bd2; string __str_plus_part_1_3 = builtin__si_s_code; string __str_plus_part_1_4 = _v3_lit_10_acdfc69f923b1745; string __str_plus_part_1_5 = in_str; string __str_plus_part_1_6 = _v3_lit_15_c23d46ff12b6690c; string __str_plus_acc_1_1 = string__plus(__str_plus_part_1_0, __str_plus_part_1_1); string __str_plus_acc_1_2 = string__plus(__str_plus_acc_1_1, __str_plus_part_1_2); string__free(&__str_plus_acc_1_1); string __str_plus_acc_1_3 = string__plus(__str_plus_acc_1_2, __str_plus_part_1_3); string__free(&__str_plus_acc_1_2); string __str_plus_acc_1_4 = string__plus(__str_plus_acc_1_3, __str_plus_part_1_4); string__free(&__str_plus_acc_1_3); string __str_plus_acc_1_5 = string__plus(__str_plus_acc_1_4, __str_plus_part_1_5); string__free(&__str_plus_acc_1_4); string __str_plus_acc_1_6 = string__plus(__str_plus_acc_1_5, __str_plus_part_1_6); string__free(&__str_plus_acc_1_5); __str_plus_acc_1_6; });
		string__free(&st_str);
		return res2_str;
	}
}

/* V3CACHE_FN_END 199d7c5524ab2601 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 3f87442a46373f84 */
string strconv__Dec32__get_string_32(strconv__Dec32 d, bool neg, i64 i_n_digit, i64 i_pad_digit) {
}

/* V3CACHE_FN_END 3f87442a46373f84 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 2ca719b0fc66f540 */
string strconv__Dec64__get_string_64(strconv__Dec64 d, bool neg, i64 i_n_digit, i64 i_pad_digit) {
}

/* V3CACHE_FN_END 2ca719b0fc66f540 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 39ef235687138a4a */
string strconv__f32_to_str(float f, i64 n_digit) {
}

/* V3CACHE_FN_END 39ef235687138a4a */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN c3170fc733a49717 */
string strconv__f32_to_str_l(float f) {
	string s = strconv__f32_to_str(f, 8);
	string res = strconv__fxx_to_str_l_parse(s);
	{
		string__free(&s);
	}
	return res;
}

/* V3CACHE_FN_END c3170fc733a49717 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 3bf333e59e14cf78 */
string strconv__f32_to_str_l_with_dot(float f) {
	string s = strconv__f32_to_str(f, 8);
	string res = strconv__fxx_to_str_l_parse_with_dot(s);
	{
		string__free(&s);
	}
	return res;
}

/* V3CACHE_FN_END 3bf333e59e14cf78 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 6f4323a6234553e1 */
string strconv__f64_to_str(double f, i64 n_digit) {
}

/* V3CACHE_FN_END 6f4323a6234553e1 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN a65fec6fd800c798 */
string strconv__f64_to_str_l(double f) {
	string s = strconv__f64_to_str(f, 18);
	string res = strconv__fxx_to_str_l_parse(s);
	{
		string__free(&s);
	}
	return res;
}

/* V3CACHE_FN_END a65fec6fd800c798 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 83fa0fd399ffdf85 */
string strconv__f64_to_str_l_with_dot(double f) {
	string s = strconv__f64_to_str(f, 18);
	string res = strconv__fxx_to_str_l_parse_with_dot(s);
	{
		string__free(&s);
	}
	return res;
}

/* V3CACHE_FN_END 83fa0fd399ffdf85 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN ca0d288f99950fd1 */
string strconv__f64_to_str_lnd1(double f, i64 dec_digit) {
	{
		i64 __if_val_0 = 0;
		if (dec_digit >= 36) {
			__if_val_0 = 36 - 1;
		} else {
			__if_val_0 = dec_digit;
		}
		i64 clamped_dec = __if_val_0;
		string s = strconv__f64_to_str(f + strconv__dec_round[clamped_dec], 18);
		if ((s.len > 2) && (((s).str[0] == 'n') || ((s).str[1] == 'i'))) {
			return s;
		}
		bool m_sgn_flag = false;
		i64 sgn = 1;
		u8 b[26];
		memmove(b, (u8[26]){0}, sizeof(b));
		i64 d_pos = 1;
		i64 i = 0;
		i64 i1 = 0;
		i64 exp = 0;
		i64 exp_sgn = 1;
		i64 dot_res_sp = -1;
		{
			i64 __for_idx_1 = 0;
			for (; __for_idx_1 < s.len; __for_idx_1++) {
				u8 c = (s).str[__for_idx_1];
				if (c == '-') {
					sgn = -1;
					i++;
				} else if (c == '+') {
					sgn = 1;
					i++;
				} else if ((c >= '0') && (c <= '9')) {
					b[i1] = c;
					i1++;
					i++;
				} else if (c == '.') {
					if (sgn > 0) {
						d_pos = i;
					} else {
						d_pos = i - 1;
					}
					i++;
				} else if (c == 'e') {
					i++;
					break;
				} else {
					string__free(&s);
					return _v3_lit_26_c6d3361bedf33505;
				}
			}
		}
		b[i1] = 0;
		if ((s).str[i] == '-') {
			exp_sgn = -1;
			i++;
		} else if ((s).str[i] == '+') {
			exp_sgn = 1;
			i++;
		}
		i64 c = i;
		while (c < s.len) {
			exp = (exp * 10) + (i64)((s).str[c] - '0');
			c++;
		}
		i64 __if_val_2 = 0;
		if (dec_digit > 0) {
			__if_val_2 = dec_digit;
		} else {
			__if_val_2 = 0;
		}
		i64 extra_frac_digits = __if_val_2;
		i64 __if_val_3 = 0;
		if (sgn < 0) {
			__if_val_3 = 1;
		} else {
			__if_val_3 = 0;
		}
		i64 sign_len = __if_val_3;
		Array __arr_init_4 = array_new(		sizeof(u8), (((sign_len + i1) + exp) + extra_frac_digits) + 4, 0);
		{
			i64 __arr_idx_5 = 0;
			for (; __arr_idx_5 < __arr_init_4.len; __arr_idx_5++) {
				i64 v_index = __arr_idx_5;
				{ Array* _a0 = &__arr_init_4; int _i0 = __arr_idx_5; array__set(_a0, _i0, &(u8[]){0}); }
			}
		}
		Array res = __arr_init_4;
		i64 r_i = 0;
		string__free(&s);
		if (sgn == 1) {
			if (m_sgn_flag) {
				{ Array* _a1 = &res; int _i1 = r_i; array__set(_a1, _i1, &(u8[]){'+'}); }
				r_i++;
			}
		} else {
			{ Array* _a2 = &res; int _i2 = r_i; array__set(_a2, _i2, &(u8[]){'-'}); }
			r_i++;
		}
		i = 0;
		if (exp_sgn >= 0) {
			while (b[i] != 0) {
				{ Array* _a3 = &res; int _i3 = r_i; array__set(_a3, _i3, &(u8[]){b[i]}); }
				r_i++;
				i++;
				if ((i >= d_pos) && (exp >= 0)) {
					if (exp == 0) {
						dot_res_sp = r_i;
						{ Array* _a4 = &res; int _i4 = r_i; array__set(_a4, _i4, &(u8[]){'.'}); }
						r_i++;
					}
					exp--;
				}
			}
			while (exp >= 0) {
				{ Array* _a5 = &res; int _i5 = r_i; array__set(_a5, _i5, &(u8[]){'0'}); }
				r_i++;
				exp--;
			}
		} else {
			bool dot_p = true;
			while (exp > 0) {
				{ Array* _a6 = &res; int _i6 = r_i; array__set(_a6, _i6, &(u8[]){'0'}); }
				r_i++;
				exp--;
				if (dot_p) {
					dot_res_sp = r_i;
					{ Array* _a7 = &res; int _i7 = r_i; array__set(_a7, _i7, &(u8[]){'.'}); }
					r_i++;
					dot_p = false;
				}
			}
			while (b[i] != 0) {
				{ Array* _a8 = &res; int _i8 = r_i; array__set(_a8, _i8, &(u8[]){b[i]}); }
				r_i++;
				i++;
			}
		}
		if (dec_digit <= 0) {
			if (dot_res_sp < 0) {
				dot_res_sp = i + 1;
			}
			string tmp_res = string__clone(tos((u8*)(res.data), dot_res_sp));
			array__free(&res);
			return tmp_res;
		}
		if (dot_res_sp >= 0) {
			r_i = (dot_res_sp + dec_digit) + 1;
			{ Array* _a9 = &res; int _i9 = r_i; array__set(_a9, _i9, &(u8[]){0}); }
			i64 __in_lhs_6 = dec_digit + 1;
			{
				i64 c1 = 1;
				for (; c1 < __in_lhs_6; c1++) {
					if ((*((u8*)((res).data) + (r_i - c1))) == 0) {
						{ Array* _a10 = &res; int _i10 = r_i - c1; array__set(_a10, _i10, &(u8[]){'0'}); }
					}
				}
			}
			string tmp_res = string__clone(tos((u8*)(res.data), r_i));
			array__free(&res);
			return tmp_res;
		} else {
			if (dec_digit > 0) {
				i64 c1 = 0;
				{ Array* _a11 = &res; int _i11 = r_i; array__set(_a11, _i11, &(u8[]){'.'}); }
				r_i++;
				while (c1 < dec_digit) {
					{ Array* _a12 = &res; int _i12 = r_i; array__set(_a12, _i12, &(u8[]){'0'}); }
					r_i++;
					c1++;
				}
				{ Array* _a13 = &res; int _i13 = r_i; array__set(_a13, _i13, &(u8[]){0}); }
			}
			string tmp_res = string__clone(tos((u8*)(res.data), r_i));
			array__free(&res);
			return tmp_res;
		}
	}
}

/* V3CACHE_FN_END ca0d288f99950fd1 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN ab030f992368bddb */
string strconv__f64_to_str_pad(double f, i64 n_digit) {
}

/* V3CACHE_FN_END ab030f992368bddb */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 8d5873f457a063a3 */
double strconv__fabs(double x) {
}

/* V3CACHE_FN_END 8d5873f457a063a3 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN cf85d8b69b227aaf */
string strconv__format_dec_old(u64 d, strconv__BF_param p) {
	string s = _v3_lit_0_14650fb0739d0383;
	Array res = strings__new_builder(20);
	i64 sign_len_diff = 0;
	if (p.pad_ch == '0') {
		if (p.positive) {
			if (p.sign_flag) {
				strings__Builder__write_u8(&res, '+');
				sign_len_diff = -1;
			}
		} else {
			strings__Builder__write_u8(&res, '-');
			sign_len_diff = -1;
		}
		string tmp = s;
		s = u64__str(d);
		{
			string__free(&tmp);
		}
	} else {
		if (p.positive) {
			if (p.sign_flag) {
				string tmp = s;
				s = string__plus(_v3_lit_1_44bd50d473cd3678, u64__str(d));
				{
					string__free(&tmp);
				}
			} else {
				string tmp = s;
				s = u64__str(d);
				{
					string__free(&tmp);
				}
			}
		} else {
			string tmp = s;
			s = string__plus(_v3_lit_1_44bd56d473cd40aa, u64__str(d));
			{
				string__free(&tmp);
			}
		}
	}
	i64 dif = (p.len0 - s.len) + sign_len_diff;
	if (p.align == strconv__Align_text__right) {
		{
			i64 i1 = 0;
			for (; i1 < dif; i1++) {
				strings__Builder__write_u8(&res, p.pad_ch);
			}
		}
	}
	strings__Builder__write_string(&res, s);
	if (p.align == strconv__Align_text__left) {
		{
			i64 i1 = 0;
			for (; i1 < dif; i1++) {
				strings__Builder__write_u8(&res, p.pad_ch);
			}
		}
	}
	string _t1 = 	strings__Builder__str(&res);
	{
		{
			strings__Builder__free(&res);
		}
		{
			string__free(&s);
		}
	}
	return _t1;
	{
		{
			strings__Builder__free(&res);
		}
		{
			string__free(&s);
		}
	}
}

/* V3CACHE_FN_END cf85d8b69b227aaf */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 7b6e097fe51a5b91 */
void strconv__format_dec_sb(u64 d, strconv__BF_param p, Array* res) {
}

/* V3CACHE_FN_END 7b6e097fe51a5b91 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN f1f1df1d7b7e6645 */
string strconv__format_es(double f, strconv__BF_param p) {
	{
		double __if_val_0 = 0.0;
		if (f > 0) {
			__if_val_0 = f;
		} else {
			__if_val_0 = -f;
		}
		string fs = strconv__f64_to_str_pad(__if_val_0, p.len1);
		if (p.rm_tail_zero) {
			string tmp = fs;
			fs = strconv__remove_tail_zeros(fs);
			string__free(&tmp);
		}
		u8 buf[512];
		memmove(buf, (u8[512]){0}, sizeof(buf));
		u8 out[512];
		memmove(out, (u8[512]){0}, sizeof(out));
		i64 buf_i = 0;
		i64 out_i = 0;
		i64 sign_len_diff = 0;
		if (p.pad_ch == '0') {
			if (p.positive) {
				if (p.sign_flag) {
					out[out_i] = '+';
					out_i++;
					sign_len_diff = -1;
				}
			} else {
				out[out_i] = '-';
				out_i++;
				sign_len_diff = -1;
			}
		} else {
			if (p.positive) {
				if (p.sign_flag) {
					buf[buf_i] = '+';
					buf_i++;
				}
			} else {
				buf[buf_i] = '-';
				buf_i++;
			}
		}
		vmemcpy((void*)(&buf[buf_i]), (void*)(fs.str), fs.len);
		buf_i += fs.len;
		i64 dif = (p.len0 - buf_i) + sign_len_diff;
		if (p.align == strconv__Align_text__right) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					out[out_i] = p.pad_ch;
					out_i++;
				}
			}
		}
		vmemcpy((void*)(&out[out_i]), (void*)(&buf[0]), buf_i);
		out_i += buf_i;
		if (p.align == strconv__Align_text__left) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					out[out_i] = p.pad_ch;
					out_i++;
				}
			}
		}
		out[out_i] = 0;
		string tmp = fs;
		fs = tos_clone(&out[0]);
		string__free(&tmp);
		return fs;
	}
}

/* V3CACHE_FN_END f1f1df1d7b7e6645 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 82adfc0867d2f00b */
string strconv__format_es_old(double f, strconv__BF_param p) {
	{
		string s = _v3_lit_0_14650fb0739d0383;
		double __if_val_0 = 0.0;
		if (f > 0) {
			__if_val_0 = f;
		} else {
			__if_val_0 = -f;
		}
		string fs = strconv__f64_to_str_pad(__if_val_0, p.len1);
		if (p.rm_tail_zero) {
			string tmp = fs;
			fs = strconv__remove_tail_zeros_old(fs);
			string__free(&tmp);
		}
		i64 __if_val_1 = 0;
		if (p.len0 > fs.len) {
			__if_val_1 = p.len0;
		} else {
			__if_val_1 = fs.len;
		}
		Array res = strings__new_builder(__if_val_1);
		i64 sign_len_diff = 0;
		if (p.pad_ch == '0') {
			if (p.positive) {
				if (p.sign_flag) {
					strings__Builder__write_u8(&res, '+');
					sign_len_diff = -1;
				}
			} else {
				strings__Builder__write_u8(&res, '-');
				sign_len_diff = -1;
			}
			string tmp = s;
			s = string__clone(fs);
			string__free(&tmp);
		} else {
			if (p.positive) {
				if (p.sign_flag) {
					string tmp = s;
					s = string__plus(_v3_lit_1_44bd50d473cd3678, fs);
					string__free(&tmp);
				} else {
					string tmp = s;
					s = string__clone(fs);
					string__free(&tmp);
				}
			} else {
				string tmp = s;
				s = string__plus(_v3_lit_1_44bd56d473cd40aa, fs);
				string__free(&tmp);
			}
		}
		i64 dif = (p.len0 - s.len) + sign_len_diff;
		if (p.align == strconv__Align_text__right) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					strings__Builder__write_u8(&res, p.pad_ch);
				}
			}
		}
		strings__Builder__write_string(&res, s);
		if (p.align == strconv__Align_text__left) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					strings__Builder__write_u8(&res, p.pad_ch);
				}
			}
		}
		string _t1 = 		strings__Builder__str(&res);
		{
			strings__Builder__free(&res);
			string__free(&fs);
			string__free(&s);
		}
		return _t1;
		{
			strings__Builder__free(&res);
			string__free(&fs);
			string__free(&s);
		}
	}
}

/* V3CACHE_FN_END 82adfc0867d2f00b */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN f901081d7f0a89fb */
string strconv__format_fl(double f, strconv__BF_param p) {
	{
		double __if_val_0 = 0.0;
		if (f >= 0.0) {
			__if_val_0 = f;
		} else {
			__if_val_0 = -f;
		}
		string fs = strconv__f64_to_str_lnd1(__if_val_0, p.len1);
		if ((fs).str[0] == '[') {
			return fs;
		}
		if (p.rm_tail_zero) {
			string tmp = fs;
			fs = strconv__remove_tail_zeros(fs);
			string__free(&tmp);
		}
		u8 buf[512];
		memmove(buf, (u8[512]){0}, sizeof(buf));
		u8 out[512];
		memmove(out, (u8[512]){0}, sizeof(out));
		i64 buf_i = 0;
		i64 out_i = 0;
		i64 sign_len_diff = 0;
		if (p.pad_ch == '0') {
			if (p.positive) {
				if (p.sign_flag) {
					out[out_i] = '+';
					out_i++;
					sign_len_diff = -1;
				}
			} else {
				out[out_i] = '-';
				out_i++;
				sign_len_diff = -1;
			}
		} else {
			if (p.positive) {
				if (p.sign_flag) {
					buf[buf_i] = '+';
					buf_i++;
				}
			} else {
				buf[buf_i] = '-';
				buf_i++;
			}
		}
		vmemcpy((void*)(&buf[buf_i]), (void*)(fs.str), fs.len);
		buf_i += fs.len;
		i64 dif = (p.len0 - buf_i) + sign_len_diff;
		if (p.align == strconv__Align_text__right) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					out[out_i] = p.pad_ch;
					out_i++;
				}
			}
		}
		vmemcpy((void*)(&out[out_i]), (void*)(&buf[0]), buf_i);
		out_i += buf_i;
		if (p.align == strconv__Align_text__left) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					out[out_i] = p.pad_ch;
					out_i++;
				}
			}
		}
		out[out_i] = 0;
		string tmp = fs;
		fs = tos_clone(&out[0]);
		string__free(&tmp);
		return fs;
	}
}

/* V3CACHE_FN_END f901081d7f0a89fb */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 76e9232c9e8e24b9 */
string strconv__format_fl_old(double f, strconv__BF_param p) {
	{
		string s = _v3_lit_0_14650fb0739d0383;
		double __if_val_0 = 0.0;
		if (f >= 0.0) {
			__if_val_0 = f;
		} else {
			__if_val_0 = -f;
		}
		string fs = strconv__f64_to_str_lnd1(__if_val_0, p.len1);
		if ((fs).str[0] == '[') {
			string__free(&s);
			return fs;
		}
		if (p.rm_tail_zero) {
			string tmp = fs;
			fs = strconv__remove_tail_zeros_old(fs);
			string__free(&tmp);
		}
		i64 __if_val_1 = 0;
		if (p.len0 > fs.len) {
			__if_val_1 = p.len0;
		} else {
			__if_val_1 = fs.len;
		}
		Array res = strings__new_builder(__if_val_1);
		i64 sign_len_diff = 0;
		if (p.pad_ch == '0') {
			if (p.positive) {
				if (p.sign_flag) {
					strings__Builder__write_u8(&res, '+');
					sign_len_diff = -1;
				}
			} else {
				strings__Builder__write_u8(&res, '-');
				sign_len_diff = -1;
			}
			string tmp = s;
			s = string__clone(fs);
			string__free(&tmp);
		} else {
			if (p.positive) {
				if (p.sign_flag) {
					string tmp = s;
					s = string__plus(_v3_lit_1_44bd50d473cd3678, fs);
					string__free(&tmp);
				} else {
					string tmp = s;
					s = string__clone(fs);
					string__free(&tmp);
				}
			} else {
				string tmp = s;
				s = string__plus(_v3_lit_1_44bd56d473cd40aa, fs);
				string__free(&tmp);
			}
		}
		i64 dif = (p.len0 - s.len) + sign_len_diff;
		if (p.align == strconv__Align_text__right) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					strings__Builder__write_u8(&res, p.pad_ch);
				}
			}
		}
		strings__Builder__write_string(&res, s);
		if (p.align == strconv__Align_text__left) {
			{
				i64 i1 = 0;
				for (; i1 < dif; i1++) {
					strings__Builder__write_u8(&res, p.pad_ch);
				}
			}
		}
		string__free(&s);
		string__free(&fs);
		string _t1 = 		strings__Builder__str(&res);
		{
			strings__Builder__free(&res);
		}
		return _t1;
		{
			strings__Builder__free(&res);
		}
	}
}

/* V3CACHE_FN_END 76e9232c9e8e24b9 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN f5a8cdf525b1c7ee */
string strconv__format_int(i64 n, i64 radix) {
	{
		if ((radix < 2) || (radix > 36)) {
			panic_n(_v3_lit_51_b1d08b2859beebd5, radix);
		}
		if (n == 0) {
			return _v3_lit_1_44bd5bd473cd4929;
		}
		i64 n_copy = n;
		bool have_minus = false;
		if (n < 0) {
			have_minus = true;
			n_copy = -n_copy;
		}
		string res = _v3_lit_0_14650fb0739d0383;
		while (n_copy != 0) {
			string tmp_0 = res;
			i64 bdx = (i64)(({ i64 _t1 = (i64)(n_copy); i64 _t2 = (i64)(radix); if (_t2 == 0) v_panic(_S("modulo by zero")); (i64)(_t1 % _t2); }));
			string tmp_1 = u8__ascii_str((strconv__base_digits).str[bdx]);
			res = string__plus(tmp_1, res);
			string__free(&tmp_0);
			string__free(&tmp_1);
			n_copy /= radix;
		}
		if (have_minus) {
			string final_res = string__plus(_v3_lit_1_44bd56d473cd40aa, res);
			string__free(&res);
			return final_res;
		}
		return res;
	}
}

/* V3CACHE_FN_END f5a8cdf525b1c7ee */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 57c053c578046b6c */
string strconv__format_str(string s, strconv__BF_param p) {
}

/* V3CACHE_FN_END 57c053c578046b6c */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 6e9e30727e4698c6 */
void strconv__format_str_sb(string s, strconv__BF_param p, Array* sb) {
}

/* V3CACHE_FN_END 6e9e30727e4698c6 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 4837acfd047940a1 */
string strconv__format_uint(u64 n, i64 radix) {
	{
		if ((radix < 2) || (radix > 36)) {
			panic_n(_v3_lit_51_b1d08b2859beebd5, radix);
		}
		if (n == 0) {
			return _v3_lit_1_44bd5bd473cd4929;
		}
		u64 n_copy = n;
		string res = _v3_lit_0_14650fb0739d0383;
		u64 uradix = (u64)(radix);
		while (n_copy != 0) {
			string tmp_0 = res;
			string tmp_1 = u8__ascii_str((strconv__base_digits).str[(i64)(({ u64 _t1 = (u64)(n_copy); u64 _t2 = (u64)(uradix); if (_t2 == 0) v_panic(_S("modulo by zero")); (u64)(_t1 % _t2); }))]);
			res = string__plus(tmp_1, res);
			string__free(&tmp_0);
			string__free(&tmp_1);
			n_copy /= uradix;
		}
		return res;
	}
}

/* V3CACHE_FN_END 4837acfd047940a1 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 3efbc057a987bfea */
string strconv__fxx_to_str_l_parse(string s) {
}

/* V3CACHE_FN_END 3efbc057a987bfea */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN d6302932c623e75b */
string strconv__fxx_to_str_l_parse_with_dot(string s) {
}

/* V3CACHE_FN_END d6302932c623e75b */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 1bb131c15dc17de8 */
string strconv__remove_tail_zeros(string s) {
}

/* V3CACHE_FN_END 1bb131c15dc17de8 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 8e38d80419656fe6 */
string strconv__remove_tail_zeros_old(string s) {
}

/* V3CACHE_FN_END 8e38d80419656fe6 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN e0238a4d85050930 */
string strconv__v_sprintf(string str, Array pt) {
	Array res = strings__new_builder(pt.len * 16);
	i64 i = 0;
	i64 p_index = 0;
	bool sign = false;
	int align = strconv__Align_text__right;
	i64 len0 = -1;
	i64 len1 = -1;
	i64 def_len1 = 6;
	u8 pad_ch = (u8)(' ');
	u32 ch1 = '0';
	u32 ch2 = '0';
	int status = strconv__Char_parse_state__norm_char;
	while (i < str.len) {
		if (status == strconv__Char_parse_state__reset_params) {
			sign = false;
			align = strconv__Align_text__right;
			len0 = -1;
			len1 = -1;
			pad_ch = ' ';
			status = strconv__Char_parse_state__norm_char;
			ch1 = '0';
			ch2 = '0';
			continue;
		}
		u8 ch = (str).str[i];
		if ((ch != '%') && (status == strconv__Char_parse_state__norm_char)) {
			strings__Builder__write_u8(&res, ch);
			i++;
			continue;
		}
		if ((ch == '%') && (status == strconv__Char_parse_state__field_char)) {
			status = strconv__Char_parse_state__norm_char;
			strings__Builder__write_u8(&res, ch);
			i++;
			continue;
		}
		if ((ch == '%') && (status == strconv__Char_parse_state__norm_char)) {
			status = strconv__Char_parse_state__field_char;
			i++;
			continue;
		}
		if ((ch == 'c') && (status == strconv__Char_parse_state__field_char)) {
			strconv__v_sprintf_panic(p_index, pt.len);
			u8 d1 = (u8)(*((i64*)((*((void**)((pt).data) + (p_index))))));
			strings__Builder__write_u8(&res, d1);
			status = strconv__Char_parse_state__reset_params;
			p_index++;
			i++;
			continue;
		}
		if ((ch == 'p') && (status == strconv__Char_parse_state__field_char)) {
			strconv__v_sprintf_panic(p_index, pt.len);
			strings__Builder__write_string(&res, _v3_lit_2_9b0c5b00c5d394a3);
			strings__Builder__write_string(&res, ptr_str((*((void**)((pt).data) + (p_index)))));
			status = strconv__Char_parse_state__reset_params;
			p_index++;
			i++;
			continue;
		}
		if (status == strconv__Char_parse_state__field_char) {
			u32 fc_ch1 = '0';
			u32 fc_ch2 = '0';
			if ((i + 1) < str.len) {
				fc_ch1 = (str).str[i + 1];
				if ((i + 2) < str.len) {
					fc_ch2 = (str).str[i + 2];
				}
			}
			if (ch == '+') {
				sign = true;
				i++;
				continue;
			} else if (ch == '-') {
				align = strconv__Align_text__left;
				i++;
				continue;
			} else if ((ch == '0') || (ch == ' ')) {
				if (align == strconv__Align_text__right) {
					pad_ch = ch;
				}
				i++;
				continue;
			} else if (ch == '\'') {
				i++;
				continue;
			} else if ((ch == '.') && (fc_ch1 >= '1') && (fc_ch1 <= '9')) {
				status = strconv__Char_parse_state__check_float;
				i++;
				continue;
			} else if ((ch == '.') && (fc_ch1 == '*') && (fc_ch2 == 's')) {
				strconv__v_sprintf_panic(p_index, pt.len);
				i64 len = *((i64*)((*((void**)((pt).data) + (p_index)))));
				p_index++;
				strconv__v_sprintf_panic(p_index, pt.len);
				string s = *((string*)((*((void**)((pt).data) + (p_index)))));
				s = string__substr(				s, 0, 				len);
				p_index++;
				strings__Builder__write_string(&res, s);
				status = strconv__Char_parse_state__reset_params;
				i += 3;
				continue;
			}
			status = strconv__Char_parse_state__len_set_start;
			continue;
		}
		if (status == strconv__Char_parse_state__len_set_start) {
			if ((ch >= '1') && (ch <= '9')) {
				len0 = (i64)(ch - '0');
				status = strconv__Char_parse_state__len_set_in;
				i++;
				continue;
			}
			if (ch == '.') {
				status = strconv__Char_parse_state__check_float;
				i++;
				continue;
			}
			status = strconv__Char_parse_state__check_type;
			continue;
		}
		if (status == strconv__Char_parse_state__len_set_in) {
			if ((ch >= '0') && (ch <= '9')) {
				len0 *= 10;
				len0 += (i64)(ch - '0');
				i++;
				continue;
			}
			if (ch == '.') {
				status = strconv__Char_parse_state__check_float;
				i++;
				continue;
			}
			status = strconv__Char_parse_state__check_type;
			continue;
		}
		if (status == strconv__Char_parse_state__check_float) {
			if ((ch >= '0') && (ch <= '9')) {
				len1 = (i64)(ch - '0');
				status = strconv__Char_parse_state__check_float_in;
				i++;
				continue;
			}
			status = strconv__Char_parse_state__check_type;
			continue;
		}
		if (status == strconv__Char_parse_state__check_float_in) {
			if ((ch >= '0') && (ch <= '9')) {
				len1 *= 10;
				len1 += (i64)(ch - '0');
				i++;
				continue;
			}
			status = strconv__Char_parse_state__check_type;
			continue;
		}
		if (status == strconv__Char_parse_state__check_type) {
			if (ch == 'l') {
				if (ch1 == '0') {
					ch1 = 'l';
					i++;
					continue;
				} else {
					ch2 = 'l';
					i++;
					continue;
				}
			} else if (ch == 'h') {
				if (ch1 == '0') {
					ch1 = 'h';
					i++;
					continue;
				} else {
					ch2 = 'h';
					i++;
					continue;
				}
			} else if ((ch == 'd') || (ch == 'i')) {
				u64 d1 = (u64)(0);
				bool positive = true;
				if (ch1 == 'h') {
					strconv__v_sprintf_panic(p_index, pt.len);
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					if (ch2 == 'h') {
						i8 sx = (i8)(x);
						bool __if_val_0 = false;
						if (sx >= 0) {
							__if_val_0 = true;
						} else {
							__if_val_0 = false;
						}
						positive = __if_val_0;
						u64 __if_val_1 = 0;
						if (positive) {
							__if_val_1 = (u64)(sx);
						} else {
							__if_val_1 = (u64)(-sx);
						}
						d1 = __if_val_1;
					} else {
						i16 sx = (i16)(x);
						bool __if_val_2 = false;
						if (sx >= 0) {
							__if_val_2 = true;
						} else {
							__if_val_2 = false;
						}
						positive = __if_val_2;
						u64 __if_val_3 = 0;
						if (positive) {
							__if_val_3 = (u64)(sx);
						} else {
							__if_val_3 = (u64)(-sx);
						}
						d1 = __if_val_3;
					}
				} else if (ch1 == 'l') {
					strconv__v_sprintf_panic(p_index, pt.len);
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					bool __if_val_4 = false;
					if (x >= 0) {
						__if_val_4 = true;
					} else {
						__if_val_4 = false;
					}
					positive = __if_val_4;
					u64 __if_val_5 = 0;
					if (positive) {
						__if_val_5 = (u64)(x);
					} else {
						__if_val_5 = (u64)(-x);
					}
					d1 = __if_val_5;
				} else {
					strconv__v_sprintf_panic(p_index, pt.len);
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					bool __if_val_6 = false;
					if (x >= 0) {
						__if_val_6 = true;
					} else {
						__if_val_6 = false;
					}
					positive = __if_val_6;
					u64 __if_val_7 = 0;
					if (positive) {
						__if_val_7 = (u64)(x);
					} else {
						__if_val_7 = (u64)(-x);
					}
					d1 = __if_val_7;
				}
				string tmp = strconv__format_dec_old(d1, (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = 0, .positive = positive, .sign_flag = sign, .align = align});
				strings__Builder__write_string(&res, tmp);
				{
					string__free(&tmp);
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				ch1 = '0';
				ch2 = '0';
				continue;
			} else if (ch == 'u') {
				u64 d1 = (u64)(0);
				bool positive = true;
				strconv__v_sprintf_panic(p_index, pt.len);
				if (ch1 == 'h') {
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					if (ch2 == 'h') {
						d1 = (u64)((u8)(x));
					} else {
						d1 = (u64)((u16)(x));
					}
				} else if (ch1 == 'l') {
					d1 = (u64)(*((u64*)((*((void**)((pt).data) + (p_index))))));
				} else {
					d1 = (u64)((u32)(*((i64*)((*((void**)((pt).data) + (p_index)))))));
				}
				string tmp = strconv__format_dec_old(d1, (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = 0, .positive = positive, .sign_flag = sign, .align = align});
				strings__Builder__write_string(&res, tmp);
				{
					string__free(&tmp);
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				continue;
			} else if ((ch == 'x') || (ch == 'X')) {
				strconv__v_sprintf_panic(p_index, pt.len);
				string s = _v3_lit_0_14650fb0739d0383;
				if (ch1 == 'h') {
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					if (ch2 == 'h') {
						s = i8__hex((i8)(x));
					} else {
						s = i16__hex((i16)(x));
					}
				} else if (ch1 == 'l') {
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					s = i64__hex(x);
				} else {
					i64 x = *((i64*)((*((void**)((pt).data) + (p_index)))));
					s = int__hex(x);
				}
				if (ch == 'X') {
					string tmp = s;
					s = string__to_upper(s);
					{
						string__free(&tmp);
					}
				}
				string tmp = strconv__format_str(s, (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = 0, .positive = true, .sign_flag = false, .align = align});
				strings__Builder__write_string(&res, tmp);
				{
					string__free(&tmp);
				}
				{
					string__free(&s);
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				continue;
			}
			if ((ch == 'f') || (ch == 'F')) {
				{
					strconv__v_sprintf_panic(p_index, pt.len);
					double x = *((double*)((*((void**)((pt).data) + (p_index)))));
					bool positive = x >= (double)(0.0);
					i64 __if_val_8 = 0;
					if (len1 >= 0) {
						__if_val_8 = len1;
					} else {
						__if_val_8 = def_len1;
					}
					len1 = __if_val_8;
					string s = strconv__format_fl_old((double)(x), (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = len1, .positive = positive, .sign_flag = sign, .align = align});
					if (ch == 'F') {
						string tmp = string__to_upper(s);
						strings__Builder__write_string(&res, tmp);
						{
							string__free(&tmp);
						}
					} else {
						strings__Builder__write_string(&res, s);
					}
					{
						string__free(&s);
					}
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				continue;
			} else if ((ch == 'e') || (ch == 'E')) {
				{
					strconv__v_sprintf_panic(p_index, pt.len);
					double x = *((double*)((*((void**)((pt).data) + (p_index)))));
					bool positive = x >= (double)(0.0);
					i64 __if_val_9 = 0;
					if (len1 >= 0) {
						__if_val_9 = len1;
					} else {
						__if_val_9 = def_len1;
					}
					len1 = __if_val_9;
					string s = strconv__format_es_old((double)(x), (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = len1, .positive = positive, .sign_flag = sign, .align = align});
					if (ch == 'E') {
						string tmp = string__to_upper(s);
						strings__Builder__write_string(&res, tmp);
						{
							string__free(&tmp);
						}
					} else {
						strings__Builder__write_string(&res, s);
					}
					{
						string__free(&s);
					}
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				continue;
			} else if ((ch == 'g') || (ch == 'G')) {
				{
					strconv__v_sprintf_panic(p_index, pt.len);
					double x = *((double*)((*((void**)((pt).data) + (p_index)))));
					bool positive = x >= (double)(0.0);
					string s = _v3_lit_0_14650fb0739d0383;
					double tx = strconv__fabs(x);
					if ((tx < 999999.0) && (tx >= 0.00001)) {
						i64 __if_val_10 = 0;
						if (len1 >= 0) {
							__if_val_10 = len1 + 1;
						} else {
							__if_val_10 = def_len1;
						}
						len1 = __if_val_10;
						string tmp = s;
						s = strconv__format_fl_old(x, (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = len1, .positive = positive, .sign_flag = sign, .align = align, .rm_tail_zero = true});
						{
							string__free(&tmp);
						}
					} else {
						i64 __if_val_11 = 0;
						if (len1 >= 0) {
							__if_val_11 = len1 + 1;
						} else {
							__if_val_11 = def_len1;
						}
						len1 = __if_val_11;
						string tmp = s;
						s = strconv__format_es_old(x, (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = len1, .positive = positive, .sign_flag = sign, .align = align, .rm_tail_zero = true});
						{
							string__free(&tmp);
						}
					}
					if (ch == 'G') {
						string tmp = string__to_upper(s);
						strings__Builder__write_string(&res, tmp);
						{
							string__free(&tmp);
						}
					} else {
						strings__Builder__write_string(&res, s);
					}
					{
						string__free(&s);
					}
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				continue;
			} else if (ch == 's') {
				strconv__v_sprintf_panic(p_index, pt.len);
				string s1 = *((string*)((*((void**)((pt).data) + (p_index)))));
				pad_ch = ' ';
				string tmp = strconv__format_str(s1, (strconv__BF_param){.pad_ch = pad_ch, .len0 = len0, .len1 = 0, .positive = true, .sign_flag = false, .align = align});
				strings__Builder__write_string(&res, tmp);
				{
					string__free(&tmp);
				}
				status = strconv__Char_parse_state__reset_params;
				p_index++;
				i++;
				continue;
			}
		}
		status = strconv__Char_parse_state__reset_params;
		p_index++;
		i++;
	}
	if (p_index != pt.len) {
		panic_n2(_v3_lit_64_a9cee17b2bafb334, p_index, pt.len);
	}
	string _t1 = 	strings__Builder__str(&res);
	{
		{
			strings__Builder__free(&res);
		}
	}
	return _t1;
	{
		{
			strings__Builder__free(&res);
		}
	}
}

/* V3CACHE_FN_END e0238a4d85050930 */
/* V3CACHE_MODULE strconv */
/* V3CACHE_FN_BEGIN 3f7372cdd03e739c */
void strconv__v_sprintf_panic(i64 idx, i64 len) {
}

/* V3CACHE_FN_END 3f7372cdd03e739c */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fa94a3b07bfd7418 */
string string__all_after(string s, string sub) {
}

/* V3CACHE_FN_END fa94a3b07bfd7418 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9117c8a2e70d52e5 */
string string__all_after_last(string s, string sub) {
}

/* V3CACHE_FN_END 9117c8a2e70d52e5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 996a88569af6eb95 */
string string__all_before(string s, string sub) {
}

/* V3CACHE_FN_END 996a88569af6eb95 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN fb0b22ce9942abe2 */
string string__all_before_last(string s, string sub) {
}

/* V3CACHE_FN_END fb0b22ce9942abe2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 22cf6f54d2220be5 */
u8 string__at_i64(string s, i64 idx) {
}

/* V3CACHE_FN_END 22cf6f54d2220be5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8bc697baa6f42513 */
u8 string__at_ni(string s, i64 idx) {
}

/* V3CACHE_FN_END 8bc697baa6f42513 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 47d6fef002bdb061 */
u8 string__at_u64(string s, u64 idx) {
}

/* V3CACHE_FN_END 47d6fef002bdb061 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN acc03807c95cd3 */
Optional_u8 string__at_with_check_i64(string s, i64 idx) {
	return (Optional_u8){.ok = true};
}

/* V3CACHE_FN_END acc03807c95cd3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 97dfa31c5a48bbcd */
Optional_u8 string__at_with_check_ni(string s, i64 idx) {
	return (Optional_u8){.ok = true};
}

/* V3CACHE_FN_END 97dfa31c5a48bbcd */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 9c61bfd2eaf85c9f */
Optional_u8 string__at_with_check_u64(string s, u64 idx) {
	return (Optional_u8){.ok = true};
}

/* V3CACHE_FN_END 9c61bfd2eaf85c9f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b59c585264183109 */
string string__clone(string a) {
}

/* V3CACHE_FN_END b59c585264183109 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 25d3f24eb88e2aca */
bool string__eq(string s, string a) {
}

/* V3CACHE_FN_END 25d3f24eb88e2aca */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN eab9e73c4e93bfd6 */
void string__free(string* s) {
}

/* V3CACHE_FN_END eab9e73c4e93bfd6 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c264a59e2f82fa1e */
Optional_i64 string__index(string s, string p) {
	return (Optional_i64){.ok = true};
}

/* V3CACHE_FN_END c264a59e2f82fa1e */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN a22dfeb65490f2b9 */
bool string__is_capital(string s) {
}

/* V3CACHE_FN_END a22dfeb65490f2b9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f4baadc09f54c122 */
bool string__lt(string s, string a) {
}

/* V3CACHE_FN_END f4baadc09f54c122 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f488adc09f2b1a89 */
string string__plus(string s, string a) {
}

/* V3CACHE_FN_END f488adc09f2b1a89 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b7183a12f0e4109f */
string string__substr(string s, i64 start, i64 _end) {
}

/* V3CACHE_FN_END b7183a12f0e4109f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 290b1ed759344173 */
string string__substr_ni(string s, i64 _start, i64 _end) {
}

/* V3CACHE_FN_END 290b1ed759344173 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8d1040e0e6bacad1 */
string string__to_lower_ascii(string s) {
}

/* V3CACHE_FN_END 8d1040e0e6bacad1 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 5b43a74e9c4c03a2 */
string string__to_upper(string s) {
}

/* V3CACHE_FN_END 5b43a74e9c4c03a2 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2131a48e6b68202b */
string string_plus_many(i64 data_len, string* input_base) {
}

/* V3CACHE_FN_END 2131a48e6b68202b */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 3462fc9409cb8197 */
void strings__Builder__free(Array* b) {
}

/* V3CACHE_FN_END 3462fc9409cb8197 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN b3dc37eb1861a70c */
string strings__Builder__str(Array* b) {
}

/* V3CACHE_FN_END b3dc37eb1861a70c */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 3abdba1f99d22db */
void strings__Builder__write_ptr(Array* b, u8* ptr, i64 len) {
}

/* V3CACHE_FN_END 3abdba1f99d22db */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN a570b0c0e87268ae */
void strings__Builder__write_runes(Array* b, Array runes) {
}

/* V3CACHE_FN_END a570b0c0e87268ae */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN cc9d25a71b9d5ee6 */
void strings__Builder__write_string(Array* b, string s) {
}

/* V3CACHE_FN_END cc9d25a71b9d5ee6 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN b906f5b87064782 */
void strings__Builder__write_u8(Array* b, u8 data) {
}

/* V3CACHE_FN_END b906f5b87064782 */
/* V3CACHE_MODULE strings */
/* V3CACHE_FN_BEGIN 2a5662290af5cccc */
Array strings__new_builder(i64 initial_size) {
}

/* V3CACHE_FN_END 2a5662290af5cccc */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN db41ffe36f3991c9 */
string tos(u8* s, i64 len) {
}

/* V3CACHE_FN_END db41ffe36f3991c9 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b56c7c26e73be4d3 */
string tos_clone(u8* const_s) {
}

/* V3CACHE_FN_END b56c7c26e73be4d3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 29d04a289ab11651 */
string u64__hex(u64 nn) {
}

/* V3CACHE_FN_END 29d04a289ab11651 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1e78b0cf12297787 */
string u64__str(u64 nn) {
}

/* V3CACHE_FN_END 1e78b0cf12297787 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 33535e41b39b8253 */
string u8__ascii_str(u8 b) {
}

/* V3CACHE_FN_END 33535e41b39b8253 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 945dad114bf84fda */
void u8__free(u8* data) {
}

/* V3CACHE_FN_END 945dad114bf84fda */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN f360817c35f7c971 */
string u8__hex(u8 nn) {
}

/* V3CACHE_FN_END f360817c35f7c971 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 4fc4d19d011d7a6d */
bool u8__is_capital(u8 c) {
}

/* V3CACHE_FN_END 4fc4d19d011d7a6d */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 838c8b26014ff66d */
bool u8__is_letter(u8 c) {
}

/* V3CACHE_FN_END 838c8b26014ff66d */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 697c2407f5e98261 */
string u8__str_escaped(u8 b) {
	string __match_val_0 = _v3_lit_0_14650fb0739d0383;
	if (b == 0) {
		__match_val_0 = _v3_lit_4_acac2dc1b2d6a927;
	} else if (b == 7) {
		__match_val_0 = _v3_lit_4_adb927c1b3bb9c4e;
	} else if (b == 8) {
		__match_val_0 = _v3_lit_4_adb501c1b3b772e5;
	} else if (b == 9) {
		__match_val_0 = _v3_lit_4_ad7815c1b383e6c3;
	} else if (b == 10) {
		__match_val_0 = _v3_lit_4_ad8cf9c1b3961339;
	} else if (b == 11) {
		__match_val_0 = _v3_lit_4_ad7109c1b37db3b1;
	} else if (b == 12) {
		__match_val_0 = _v3_lit_4_ada829c1b3ad2c81;
	} else if (b == 13) {
		__match_val_0 = _v3_lit_4_ad7f21c1b38a19d5;
	} else if (b == 27) {
		__match_val_0 = _v3_lit_4_adab0fc1b3af362a;
	} else if ((b >= 32) && (b <= 126)) {
		__match_val_0 = u8__ascii_str(b);
	} else {
		string xx = u8__hex(b);
		string yy = string__plus(_v3_lit_2_9b0c5b00c5d394a3, xx);
		{
			string__free(&xx);
		}
		__match_val_0 = yy;
	}
	string str = __match_val_0;
	return str;
}

/* V3CACHE_FN_END 697c2407f5e98261 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 19bc3f2fee82a7e7 */
string u8__vstring(u8* bp) {
}

/* V3CACHE_FN_END 19bc3f2fee82a7e7 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7e9bc809c6cdbdd8 */
string u8__vstring_with_len(u8* bp, i64 len) {
}

/* V3CACHE_FN_END 7e9bc809c6cdbdd8 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 8541069f854b4673 */
string utf32_to_str(u32 code) {
}

/* V3CACHE_FN_END 8541069f854b4673 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN b8d7bc63139b5a3f */
VNORETURN void v_exit(i64 code) {
}

/* V3CACHE_FN_END b8d7bc63139b5a3f */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN bb3d5e568e06b905 */
i64 v_fixed_index_i64(i64 i, i64 len) {
}

/* V3CACHE_FN_END bb3d5e568e06b905 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 216125e34356f2b3 */
i64 v_fixed_index_ni(i64 i, i64 len) {
}

/* V3CACHE_FN_END 216125e34356f2b3 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e1f6edf1c0123f01 */
i64 v_fixed_index_u64(u64 i, i64 len) {
}

/* V3CACHE_FN_END e1f6edf1c0123f01 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN c0c7a4c71a7a78a5 */
void v_free(void* ptr) {
}

/* V3CACHE_FN_END c0c7a4c71a7a78a5 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 7b1944a43c39c95a */
VNORETURN void v_panic(string s) {
}

/* V3CACHE_FN_END 7b1944a43c39c95a */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN e5230ad52a83f915 */
i64 v_slice_index_i64(i64 i) {
}

/* V3CACHE_FN_END e5230ad52a83f915 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 34b79b7c5c8e5e71 */
i64 v_slice_index_u64(u64 i) {
}

/* V3CACHE_FN_END 34b79b7c5c8e5e71 */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 1cbf6ecc7f41e9be */
void* vmemcpy(void* dest, void* const_src, ptrdiff_t n) {
}

/* V3CACHE_FN_END 1cbf6ecc7f41e9be */
/* V3CACHE_MODULE builtin */
/* V3CACHE_FN_BEGIN 2f27c139db238bf2 */
Array voidptr__vbytes(void* data, i64 len) {
}

/* V3CACHE_FN_END 2f27c139db238bf2 */
/* V3CACHE_MODULE main */
int main(int argc, char** argv) {
	g_main_argc = argc;
	g_main_argv = argv;
	_vinit();
	println(_v3_lit_24_f4bba39b2c23a7d0);
	return 0;
}

// THE END.
/* V3CACHE_BODY_END */

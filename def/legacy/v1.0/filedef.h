/*
	These are some definitions to ease application development on legacy Windows systems.

	config.h is the macro configuration file.
	globldef.h is the global definition file. It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#ifndef FILEDEF_H
#define FILEDEF_H

#include "globldef.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef __FILE64
typedef LONG64 __offset;
#else
typedef LONG __offset;
#endif

#ifdef __NTWIN

#define __O_RDONLY _O_RDONLY
#define __O_WRONLY _O_WRONLY
#define __O_RDWR _O_RDWR

#ifdef __FILE64
#define __LSEEK(fd, offset, whence) _lseeki64(fd, offset, whence)
#else
#define __LSEEK(fd, offset, whence) _lseek(fd, offset, whence)
#endif

#ifdef __USE_UTF16
#define __STDCREATE(file_dir) _wopen(file_dir, (_O_WRONLY | _O_CREAT | _O_TRUNC), (_S_IREAD | _S_IWRITE))
#define __STDOPEN(file_dir, flags) _wopen(file_dir, flags)
#else
#define __STDCREATE(file_dir) _open(file_dir, (_O_WRONLY | _O_CREAT | _O_TRUNC), (_S_IREAD | _S_IWRITE))
#define __STDOPEN(file_dir, flags) _open(file_dir, flags)
#endif

#define __CLOSE(fd) _close(fd)
#define __READ(fd, buffer, length) _read(fd, buffer, length)
#define __WRITE(fd, buffer, length) _write(fd, buffer, length)

#endif

#ifdef __DOSWIN

#define __O_RDONLY OF_READ
#define __O_WRONLY OF_WRITE
#define __O_RDWR OF_READWRITE

#define __LSEEK(fd, offset, whence) _llseek(fd, offset, whence)

#define __STDCREATE(file_dir) _lcreat(file_dir, 0)
#define __STDOPEN(file_dir, flags) _lopen(file_dir, flags)

#define __CLOSE(fd) _lclose(fd)
#define __READ(fd, buffer, length) _lread(fd, buffer, length)
#define __WRITE(fd, buffer, length) _lwrite(fd, buffer, length)

#endif

#endif //FILEDEF_H

/*
 * newlib_x.c
 *
 *  Created on: Jul 12, 2010
 *      Author: andrew
 *
 *  Updated on: Oct 17, 2010
 *      Author: gary
 *
 *      - consolidated mutliple stub sources into one source file
 *      - added a utimes() NOOP stub to avoid modifying SQLite sources
 *      - included the <sys/time.h> to disable undeclared timeval warning
 */

/* This is file NEWLIB_X.C */

/*
 * Copyright (C) 1993 DJ Delorie
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms is permitted
 * provided that the above copyright notice and following paragraph are
 * duplicated in all such forms.
 *
 * This file is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

//
// access
//
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int access(const char *fn, int flags)
{
  struct stat s;
  if (stat(fn, &s))
    return -1;

  if (s.st_mode & S_IFDIR)
    return 0;

  if (flags & W_OK)
  {
    if (s.st_mode & S_IWRITE)
      return 0;

    return -1;
  }

  return 0;
}

//
// cntl
//
#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#undef errno
int errno;

int _DEFUN(_fcntl, (fildes, cmd), int fildes _AND int cmd _DOTS)
{
      (void)fildes;
      (void)cmd;

      //errno = ENOSYS;
      //return -1;

      errno = 0;
      return 0;
}

//
// fsync
//
#include <unistd.h>

int fsync(int fd)
{
      return 0;
}

//
// sleep
//
#include <sys/types.h>
#include <sys/signal.h>

unsigned sleep(unsigned secs)
{
      maWait(secs * 1000);
      return 0;
}

//
// utimes
//
#include <sys/time.h>

int utimes(const char *filename, const struct timeval times[2])
{
	// Upon successful completion, 0 shall be returned. Otherwise,
	// -1 shall be returned and errno shall be set to indicate the error,
	// and the file times shall not be affected.

	return 0;
}

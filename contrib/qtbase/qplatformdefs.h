/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the qmake spec of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the qmake spec of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORMDEFS_H
#define QPLATFORMDEFS_H

// Get Qt defines/settings

#include "qglobal.h"

// Set any POSIX/XOPEN defines at the top of this file to turn on specific APIs

// 1) need to reset default environment if _BSD_SOURCE is defined
// 2) need to specify POSIX thread interfaces explicitly in glibc 2.0
// 3) it seems older glibc need this to include the X/Open stuff
#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#include <unistd.h>


// We are hot - unistd.h should have turned on the specific APIs we requested

#include <features.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#ifndef QT_NO_IPV6IFNAME
#include <net/if.h>
#endif

#define QT_USE_XOPEN_LFS_EXTENSIONS


#undef QT_SOCKLEN_T

#if defined(__GLIBC__) && (__GLIBC__ >= 2)
#define QT_SOCKLEN_T            socklen_t
#else
#define QT_SOCKLEN_T            int
#endif

#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)
#define QT_SNPRINTF		::snprintf
#define QT_VSNPRINTF		::vsnprintf
#endif

#endif // QPLATFORMDEFS_H
/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the qmake spec of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef Q_POSIX_QPLATFORMDEFS_H
#define Q_POSIX_QPLATFORMDEFS_H

#include <signal.h>

#include <sys/types.h>
#ifndef QT_NO_SOCKET_H
#  include <sys/socket.h>
#endif
#include <sys/stat.h>

#if defined(QT_USE_XOPEN_LFS_EXTENSIONS) && defined(QT_LARGEFILE_SUPPORT)

#define QT_STATBUF              struct stat64
#define QT_FPOS_T               fpos64_t
#define QT_OFF_T                off64_t

#define QT_STAT                 ::stat64
#define QT_LSTAT                ::lstat64
#define QT_TRUNCATE             ::truncate64

// File I/O
#define QT_OPEN                 ::open64
#define QT_LSEEK                ::lseek64
#define QT_FSTAT                ::fstat64
#define QT_FTRUNCATE            ::ftruncate64

// Standard C89
#define QT_FOPEN                ::fopen64
#define QT_FSEEK                ::fseeko64
#define QT_FTELL                ::ftello64
#define QT_FGETPOS              ::fgetpos64
#define QT_FSETPOS              ::fsetpos64

#define QT_MMAP                 ::mmap64

#else // !defined(QT_USE_XOPEN_LFS_EXTENSIONS) || !defined(QT_LARGEFILE_SUPPORT)



#define QT_STATBUF              struct stat

#define QT_STAT                 ::stat
#define QT_LSTAT                ::lstat
#define QT_TRUNCATE             ::truncate

// File I/O
#define QT_OPEN                 ::open
#define QT_LSEEK                ::lseek
#define QT_FSTAT                ::fstat
#define QT_FTRUNCATE            ::ftruncate

// Posix extensions to C89
#if !defined(QT_USE_XOPEN_LFS_EXTENSIONS) && !defined(QT_NO_USE_FSEEKO)
#undef QT_OFF_T
#undef QT_FSEEK
#undef QT_FTELL

#define QT_OFF_T                off_t

#define QT_FSEEK                ::fseeko
#define QT_FTELL                ::ftello
#endif

#define QT_MMAP                 ::mmap

#endif // !defined (QT_USE_XOPEN_LFS_EXTENSIONS) || !defined(QT_LARGEFILE_SUPPORT)

#define QT_STAT_MASK            S_IFMT
#define QT_STAT_REG             S_IFREG
#define QT_STAT_DIR             S_IFDIR
#define QT_STAT_LNK             S_IFLNK

#define QT_ACCESS               ::access
#define QT_GETCWD               ::getcwd
#define QT_CHDIR                ::chdir
#define QT_MKDIR                ::mkdir
#define QT_RMDIR                ::rmdir

// File I/O
#define QT_CLOSE                ::close
#define QT_READ                 ::read
#define QT_WRITE                ::write

#define QT_OPEN_LARGEFILE       O_LARGEFILE
#define QT_OPEN_RDONLY          O_RDONLY
#define QT_OPEN_WRONLY          O_WRONLY
#define QT_OPEN_RDWR            O_RDWR
#define QT_OPEN_CREAT           O_CREAT
#define QT_OPEN_TRUNC           O_TRUNC
#define QT_OPEN_APPEND          O_APPEND

// Posix extensions to C89
#define QT_FILENO               fileno

// Directory iteration
#define QT_DIR                  DIR

#define QT_OPENDIR              ::opendir
#define QT_CLOSEDIR             ::closedir

#if defined(QT_LARGEFILE_SUPPORT) \
        && defined(QT_USE_XOPEN_LFS_EXTENSIONS) \
        && !defined(QT_NO_READDIR64)
#define QT_DIRENT               struct dirent64
#define QT_READDIR              ::readdir64
#define QT_READDIR_R            ::readdir64_r
#else
#define QT_DIRENT               struct dirent
#define QT_READDIR              ::readdir
#define QT_READDIR_R            ::readdir_r
#endif

#define QT_SOCKLEN_T            socklen_t

#define QT_SOCKET_CONNECT       ::connect
#define QT_SOCKET_BIND          ::bind

#define QT_SIGNAL_RETTYPE       void
#define QT_SIGNAL_ARGS          int
#define QT_SIGNAL_IGNORE        SIG_IGN

#endif // include guard
/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the qmake spec of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef Q_C89_QPLATFORMDEFS_H
#define Q_C89_QPLATFORMDEFS_H

// #include <stdio.h>

#define QT_FPOS_T               fpos_t
#define QT_OFF_T                long

#define QT_FOPEN                ::fopen
#define QT_FSEEK                ::fseek
#define QT_FTELL                ::ftell
#define QT_FGETPOS              ::fgetpos
#define QT_FSETPOS              ::fsetpos

#endif // include guard

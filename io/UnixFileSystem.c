//1. The .cc .cpp .cxx related header files
#include "UnixFileSystem.h"
//2. C system include files.
#include <assert.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include <limits.h>
#include <fcntl.h>

//3. C++ system include files.
//4. Other libraries' .h files.
//5. Your project's .h files.
#include "lang/System.h"
#include "lang/StringBuffer.h"

/*
 * Solaris/Linux implementation of the file system support functions.
 */
#define slash '/'

// +++++++++++++++++++++++++++++++++++++++++++++
// |   1. public members                       |
// +++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.6. constructors     |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.7. destructors      |
// +++++++++++++++++++++++++++

// +++++++++++++++++++++++++++
// |   1.8. member functions |
// +++++++++++++++++++++++++++
static bool statMode(const char* path, int* mode)
{
    struct stat sb;
    if (stat(path, &sb) == 0) {
        *mode = sb.st_mode;
        return true;
    }
    return false;
}

static char CLASS_METHOD()(UnixFileSystem, getSeparator)
{
    return '/';
}

static char CLASS_METHOD()(UnixFileSystem, getPathSeparator)
{
    return ':';
}

static String* CLASS_METHOD()(UnixFileSystem, normalize, String* pathname, int len, int off)
{
    if (len == 0) return CLONE(pathname);
    int n = len;
    while ((n > 0) && (_M(pathname, charAt, n - 1) == slash)) n--;
    if (n == 0) return NEW(String, "/");

    StringBuffer* sb = NEW(StringBuffer, _M(pathname, length)+1);
    const char* cstr = _M(pathname, getCString);
    if (off > 0) _M(sb, appendCString, cstr, 0, off);
    char prevChar = 0;
    for (int i = off; i < n; i++) {
        char c = _M(pathname, charAt, i);
        if ((prevChar == slash) && (c == slash)) continue;
        _M(sb, appendChar, c);
        prevChar = c;
    }

    String* str = _M(sb, toString);
    DELETE(sb);
    return str;
}

static String* CLASS_METHOD()(UnixFileSystem, normalize, String* pathname)
{
    int n = _M(pathname, length);
    char prevChar = 0;
    for (int i = 0; i < n; i++) {
        char c = _M(pathname, charAt, i);
        if ((prevChar == slash) && (c == slash))
            return self(normalize, pathname, n, i - 1);
        prevChar = c;
    }
    if (prevChar == slash) return self(normalize, pathname, n, n - 1);
    return CLONE(pathname);
}

static int CLASS_METHOD()(UnixFileSystem, prefixLength, String* path)
{
    if (_M(path, length) == 0) return 0;
    return (_M(path, charAt, 0) == slash) ? 1 : 0;
}

static bool CLASS_METHOD()(UnixFileSystem, isAbsolute, File* f)
{
    return _M(f, getPrefixLength) != 0;
}

static int CLASS_METHOD()(UnixFileSystem, getBoolAttributes, File* f)
{
    /*FileSystemAttributesEnum*/
    int rv = 0;
    String* path = _M(f, getPath);
    int mode;
    if (statMode(_M(path, getCString), &mode)) {
        int fmt = mode & S_IFMT;
        rv = BA_EXISTS
            | (fmt == S_IFREG ? BA_REGULAR : 0)
            | (fmt == S_IFDIR ? BA_DIRECTORY : 0);
    }
    return rv;
}

static bool CLASS_METHOD()(UnixFileSystem, checkAccess, File* f, int a)
{
    bool rv = false;
    int mode = 0;
    switch (a) {
    case ACCESS_READ:
        mode = R_OK;
        break;
    case ACCESS_WRITE:
        mode = W_OK;
        break;
    case ACCESS_EXECUTE:
        mode = X_OK;
        break;
    default: assert(0);
    }

    String* path = _M(f, getPath);
    if (access(_M(path, getCString), mode) == 0) {
        rv = true;
    }
    return rv;
}

static bool CLASS_METHOD()(UnixFileSystem, setPermission, File* f, int access/*FileSystemAccessEnum*/, bool enable, bool owneronly)
{
    bool rv = false;

    int amode = 0;
    int mode;
    switch (access) {
    case ACCESS_READ:
        if (owneronly)
            amode = S_IRUSR;
        else
            amode = S_IRUSR | S_IRGRP | S_IROTH;
        break;
    case ACCESS_WRITE:
        if (owneronly)
            amode = S_IWUSR;
        else
            amode = S_IWUSR | S_IWGRP | S_IWOTH;
        break;
    case ACCESS_EXECUTE:
        if (owneronly)
            amode = S_IXUSR;
        else
            amode = S_IXUSR | S_IXGRP | S_IXOTH;
        break;
    default:
        assert(0);
    }

    String* path = _M(f, getPath);
    const char* cpath = _M(path, getCString);
    if (statMode(cpath, &mode)) {
        if (enable)
            mode |= amode;
        else
            mode &= ~amode;
        if (chmod(cpath, mode) >= 0) {
            rv = true;
        }
    }
    return rv;
}

static long CLASS_METHOD()(UnixFileSystem, getLastModifiedTime, File* f)
{
    long rv = 0;

    struct stat sb;
    String* path = _M(f, getPath);
    if (stat(_M(path, getCString), &sb) == 0) {
        rv = 1000 * (long)sb.st_mtime;
    }
    return rv;
}

static long CLASS_METHOD()(UnixFileSystem, getLength, File* f)
{
    long rv = 0;

    struct stat sb;
    String* path = _M(f, getPath);
    if (stat(_M(path, getCString), &sb) == 0) {
        rv = sb.st_size;
    }
    return rv;
}

static bool CLASS_METHOD()(UnixFileSystem, createFileExclusively, String* pathname)
{
    bool rv = false;
    int fd;
    const char* path = _M(pathname, getCString);
    if (!strcmp (path, "/")) {
        fd = -1;    /* The root directory always exists */
    } else {
        fd = open(path, O_RDWR | O_CREAT | O_EXCL, 0666);
    }
    if (fd > 0) {
        close(fd);
    }
    return rv;
}

static bool CLASS_METHOD()(UnixFileSystem, createDirectory, File* f)
{
    bool rv = false;
    int fd;
    String* path = _M(f, getPath);
    if (mkdir(_M(path, getCString), 0777) == 0) {
        rv = true;
    }
    return rv;
}

static bool CLASS_METHOD()(UnixFileSystem, delete, File* f)
{
    bool rv = false;
    String* path = _M(f, getPath);
    if (remove(_M(path, getCString))) {
        rv = true;
    }
    return rv;
}

/**
 * Rename the file or directory denoted by the first abstract pathname to
 * the second abstract pathname, returning <code>true</code> if and only if
 * the operation succeeds.
 */
static bool CLASS_METHOD()(UnixFileSystem, rename, File* f1, File* f2)
{
    bool rv = false;
    String* fromPath = _M(f1, getPath);
    String* toPath = _M(f2, getPath);
    if (rename(_M(fromPath, getCString), _M(toPath, getCString))) {
        rv = true;
    }
    return rv;
}

/**
 * Set the last-modified time of the file or directory denoted by the
 * given abstract pathname, returning <code>true</code> if and only if the
 * operation succeeds.
 */
static bool CLASS_METHOD()(UnixFileSystem, setLastModifiedTime, File* f, long time)
{
    bool rv = false;
    struct stat sb;

    String* path = _M(f, getPath);
    const char* pathname = _M(path, getCString);
    if (stat(pathname, &sb) == 0) {
        struct timeval tv[2];

        /* Preserve access time */
        tv[0].tv_sec = sb.st_atime;
        tv[0].tv_usec = 0;

        /* Change last-modified time */
        tv[1].tv_sec = time / 1000;
        tv[1].tv_usec = (time % 1000) * 1000;

        if (utimes(pathname, tv) == 0)
            rv = true;
    }
    return rv;
}

static bool CLASS_METHOD()(UnixFileSystem, setReadOnly, File* f)
{
    bool rv = false;
    String* path = _M(f, getPath);
    const char* pathname = _M(path, getCString);
    int mode;
    if (statMode(pathname, &mode)) {
        if (chmod(pathname, mode & ~(S_IWUSR | S_IWGRP | S_IWOTH)) >= 0) {
            rv = true;
        }
    }
    return rv;
}

static long CLASS_METHOD()(UnixFileSystem, getSpace, File* f, int/*FileSystemSpaceEnum*/ t)
{
    long rv = 0L;
    String* path = _M(f, getPath);
    const char* pathname = _M(path, getCString);
    struct statvfs fsstat;
    memset(&fsstat, 0, sizeof(fsstat));
    if (statvfs(pathname, &fsstat) == 0) {
        switch(t) {
        case SPACE_TOTAL:
            rv = fsstat.f_frsize * fsstat.f_blocks;
            break;
        case SPACE_FREE:
            rv = fsstat.f_frsize * fsstat.f_bfree;
            break;
        case SPACE_USABLE:
            rv = fsstat.f_frsize * fsstat.f_bavail;
            break;
        default:
            assert(0);
        }
    }
    return rv;
}

static BUILD(global_const)(defaultParent, String, "/")
static String* CLASS_METHOD()(UnixFileSystem, getDefaultParent)
{
    return defaultParent;
}

static String* CLASS_METHOD()(UnixFileSystem, resolve, String* parent, String* child)
{
    String* rv = NULL;
    if (_M(child, equalsToCString, ""))
        return CLONE(parent);
    if (_M(child, charAt, 0) == slash) {
        if (_M(parent, equalsToCString, "/"))
            return CLONE(child);
        rv = CLONE(parent);
        _M(parent, concat, child);
        return rv;
    }
    if (_M(parent, equalsToCString, "/")) {
        rv = CLONE(parent);
        _M(parent, concat, child);
        return rv;
    }

    /* parent + '/' + child; */
    rv = CLONE(parent);
    _M(rv, concatChar, slash);
    _M(rv, concat, child);
    return rv;
}

static String* CLASS_METHOD()(UnixFileSystem, resolve, File* f)
{
    String* strPath = _M(f, getPath);
    if (self(isAbsolute, f)) return CLONE(strPath);
    String* strCwd = Class(System).getcwd();
    String* rv = self(resolve, strCwd, strPath);
    DELETE(strCwd);
    return rv;
}

/* Check the given name sequence to see if it can be further collapsed.
   Return zero if not, otherwise return the number of names in the sequence. */
static int collapsible(char *names)
{
    char *p = names;
    int dots = 0, n = 0;

    while (*p) {
        if ((p[0] == '.') && ((p[1] == '\0')
                              || (p[1] == '/')
                              || ((p[1] == '.') && ((p[2] == '\0')
                                                    || (p[2] == '/'))))) {
            dots = 1;
        }
        n++;
        while (*p) {
            if (*p == '/') {
                p++;
                break;
            }
            p++;
        }
    }
    return (dots ? n : 0);
}

/* Split the names in the given name sequence,
   replacing slashes with nulls and filling in the given index array */
static void splitNames(char *names, char **ix)
{
    char *p = names;
    int i = 0;

    while (*p) {
        ix[i++] = p++;
        while (*p) {
            if (*p == '/') {
                *p++ = '\0';
                break;
            }
            p++;
        }
    }
}

/* Join the names in the given name sequence, ignoring names whose index
   entries have been cleared and replacing nulls with slashes as needed */
static void joinNames(char *names, int nc, char **ix)
{
    int i;
    char *p;

    for (i = 0, p = names; i < nc; i++) {
        if (!ix[i]) continue;
        if (i > 0) {
            p[-1] = '/';
        }
        if (p == ix[i]) {
            p += strlen(p) + 1;
        } else {
            char *q = ix[i];
            while ((*p++ = *q++));
        }
    }
    *p = '\0';
}

/* Collapse "." and ".." names in the given path wherever possible.
   A "." name may always be eliminated; a ".." name may be eliminated if it
   follows a name that is neither "." nor "..".  This is a syntactic operation
   that performs no filesystem queries, so it should only be used to cleanup
   after invoking the realpath() procedure. */
static void collapse(char *path)
{
    char *names = (path[0] == '/') ? path + 1 : path; /* Preserve first '/' */
    int nc;
    char **ix;
    int i, j;
    char *p, *q;

    nc = collapsible(names);
    if (nc < 2) return;         /* Nothing to do */
    ix = (char **)alloca(nc * sizeof(char *));
    splitNames(names, ix);

    for (i = 0; i < nc; i++) {
        int dots = 0;

        /* Find next occurrence of "." or ".." */
        do {
            char *p = ix[i];
            if (p[0] == '.') {
                if (p[1] == '\0') {
                    dots = 1;
                    break;
                }
                if ((p[1] == '.') && (p[2] == '\0')) {
                    dots = 2;
                    break;
                }
            }
            i++;
        } while (i < nc);
        if (i >= nc) break;

        /* At this point i is the index of either a "." or a "..", so take the
           appropriate action and then continue the outer loop */
        if (dots == 1) {
            /* Remove this instance of "." */
            ix[i] = 0;
        } else {
            /* If there is a preceding name, remove both that name and this
               instance of ".."; otherwise, leave the ".." as is */
            for (j = i - 1; j >= 0; j--) {
                if (ix[j]) break;
            }
            if (j < 0) continue;
            ix[j] = 0;
            ix[i] = 0;
        }
        /* i will be incremented at the top of the loop */
    }

    joinNames(names, nc, ix);
}

/* Convert a pathname to canonical form.  The input path is assumed to contain
   no duplicate slashes.  On Solaris we can use realpath() to do most of the
   work, though once that's done we still must collapse any remaining "." and
   ".." names by hand. */
int canonicalize(const char *original, char *resolved, int len)
{
    if (len < PATH_MAX) {
        errno = EINVAL;
        return -1;
    }

    if (strlen(original) > PATH_MAX) {
        errno = ENAMETOOLONG;
        return -1;
    }

    /* First try realpath() on the entire path */
    if (realpath(original, resolved)) {
        /* That worked, so return it */
        collapse(resolved);
        return 0;
    } else {
        /* Something's bogus in the original path, so remove names from the end
           until either some subpath works or we run out of names */
        char *p, *end, *r = NULL;
        char path[PATH_MAX + 1];

        strncpy(path, original, sizeof(path));
        if (path[PATH_MAX] != '\0') {
            errno = ENAMETOOLONG;
            return -1;
        }
        end = path + strlen(path);

        for (p = end; p > path;) {

            /* Skip last element */
            while ((--p > path) && (*p != '/'));
            if (p == path) break;

            /* Try realpath() on this subpath */
            *p = '\0';
            r = realpath(path, resolved);
            *p = (p == end) ? '\0' : '/';

            if (r != NULL) {
                /* The subpath has a canonical path */
                break;
            }
            else if (errno == ENOENT || errno == ENOTDIR || errno == EACCES) {
                /* If the lookup of a particular subpath fails because the file
                   does not exist, because it is of the wrong type, or because
                   access is denied, then remove its last name and try again.
                   Other I/O problems cause an error return. */
                continue;
            }
            else {
                return -1;
            }
        }

        if (r != NULL) {
            /* Append unresolved subpath to resolved subpath */
            int rn = strlen(r);
            if (rn + (int)strlen(p) >= len) {
                /* Buffer overflow */
                errno = ENAMETOOLONG;
                return -1;
            }
            if ((rn > 0) && (r[rn - 1] == '/') && (*p == '/')) {
                /* Avoid duplicate slashes */
                p++;
            }
            strcpy(r + rn, p);
            collapse(r);
            return 0;
        } else {
            /* Nothing resolved, so just return the original path */
            strcpy(resolved, path);
            collapse(resolved);
            return 0;
        }
    }
}

static String* CLASS_METHOD()(UnixFileSystem, canonicalize, String* path)
{
    String* rv = NULL;
    char canonicalPath[PATH_MAX];
    if (canonicalize(_M(path, getCString), canonicalPath, PATH_MAX) < 0) {
        return rv;
    }
    rv = NEW(String, canonicalPath);
    return rv;
}

static BUILD(global)(fs, UnixFileSystem)

static FileSystem* getFileSystem()
{
    return (FileSystem*)&fs;
}

static void afterClassLoad()
{
    Class(FileSystem).getFileSystem = getFileSystem;
    Class(UnixFileSystem).getFileSystem = getFileSystem;
}

BEGIN_CLASS(UnixFileSystem, FileSystem)
    CLASS_METHOD(map)(UnixFileSystem, getSeparator)
    CLASS_METHOD(map)(UnixFileSystem, getPathSeparator)
    CLASS_METHOD(map)(UnixFileSystem, normalize, String* pathname)
    CLASS_METHOD(map)(UnixFileSystem, normalize, String* pathname, int len, int off)
    CLASS_METHOD(map)(UnixFileSystem, prefixLength, String* path)
    CLASS_METHOD(map)(UnixFileSystem, isAbsolute, File* f)
    CLASS_METHOD(map)(UnixFileSystem, getBoolAttributes, File* f)
    CLASS_METHOD(map)(UnixFileSystem, checkAccess, File* f, int access)
    CLASS_METHOD(map)(UnixFileSystem, setPermission, File* f, int access, bool enable, bool owneronly)
    CLASS_METHOD(map)(UnixFileSystem, getLastModifiedTime, File* f)
    CLASS_METHOD(map)(UnixFileSystem, getLength, File* f)
    CLASS_METHOD(map)(UnixFileSystem, createFileExclusively, String* pathname)
    CLASS_METHOD(map)(UnixFileSystem, delete, File* f)
    CLASS_METHOD(map)(UnixFileSystem, rename, File* f1, File* f2)
    CLASS_METHOD(map)(UnixFileSystem, setLastModifiedTime, File* f, long time)
    CLASS_METHOD(map)(UnixFileSystem, setReadOnly, File* f)
    CLASS_METHOD(map)(UnixFileSystem, getSpace, File* f, int t)
    CLASS_METHOD(map)(UnixFileSystem, getDefaultParent)
    CLASS_METHOD(map)(UnixFileSystem, canonicalize, String* path)
    CLASS_METHOD(map)(UnixFileSystem, resolve, File* f)
    CLASS_METHOD(map)(UnixFileSystem, resolve, String* parent, String* child)
    CLASS_METHOD(map)(UnixFileSystem, createDirectory, File* f)
    afterClassLoad();
END_CLASS

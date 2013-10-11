/*
 * ntfs-3g_embox_compat.h
 *
 *  Created on: 02 juillet 2013
 *      Author: fsulima
 */

#ifndef QPID_EMBOX_COMPAT_H_
#define QPID_EMBOX_COMPAT_H_


#ifdef linux
#undef linux
#endif

#ifdef __linux__
#undef __linux__
#endif

#include <stdio.h>
#include <string.h>

#if 1
#define DPRINT() printf(">>> qpid CALL %s\n", __FUNCTION__)
#else
#define DPRINT()
#endif

extern
int toupper(int c);

#include <pthread.h>

extern
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
extern
int pthread_rwlock_init(pthread_rwlock_t * rwlock,
	const pthread_rwlockattr_t * attr);
extern
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
extern
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
extern
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
extern
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
extern
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);

extern "C"
int alphasort(const struct dirent **a, const struct dirent **b);
extern "C"
int scandir(const char *dirp, struct dirent ***namelist,
              int (*filter)(const struct dirent *),
              int (*compar)(const struct dirent **, const struct dirent **));

#define O_NOFOLLOW 0
#define F_TLOCK 1
#define F_ULOCK 2
extern
int lockf(int fd, int cmd, off_t len);

using std::sysconf;
#define _SC_PAGE_SIZE _SC_PAGESIZE

#include <errno.h>

#define MAP_SHARED    0x00
//#define MAP_PRIVATE   0x01
//#define PROT_READ     0x10
#define PROT_WRITE    0x20
#define MAP_FAILED    ((void*)(-1))
static inline void  *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t off) {
	// ToDo: implement for InitFS files
	(void)addr;
	(void)len;
	(void)prot;
	(void)flags;
	(void)off;
	printf(">>> mmap(%i)\n",fd);
	errno = EPERM;
	return 0;
}

static inline int munmap(void *addr, size_t size) {
	(void)size;
	printf(">>> munmap(%p)\n",addr);
	errno = EPERM;
	return -1;
}

#define MS_ASYNC 1
static inline
int msync(void *addr, size_t length, int flags) {
	(void)addr;
	(void)length;
	(void)flags;
	printf(">>> msync(%p)\n",addr);
	errno = ENOMEM;
	return -1;
}

extern
int socketpair(int domain, int type, int protocol, int sv[2]);

#include <netinet/in.h>

struct addrinfo
{
  int ai_flags;			/* Input flags.  */
  int ai_family;		/* Protocol family for socket.  */
  int ai_socktype;		/* Socket type.  */
  int ai_protocol;		/* Protocol for socket.  */
  socklen_t ai_addrlen;		/* Length of socket address.  */
  struct sockaddr *ai_addr;	/* Socket address for socket.  */
  char *ai_canonname;		/* Canonical name for service location.  */
  struct addrinfo *ai_next;	/* Pointer to next in list.  */
};

/* Structure large enough to hold any socket address (with the historical
   exception of AF_UNIX).  We reserve 128 bytes.  */
#define __ss_aligntype	unsigned long int
#define _SS_SIZE	128
#define _SS_PADSIZE	(_SS_SIZE - (2 * sizeof (__ss_aligntype)))

#define	__SOCKADDR_COMMON(sa_prefix) \
  sa_family_t sa_prefix##family

#define __SOCKADDR_COMMON_SIZE	(sizeof (unsigned short int))

struct sockaddr_storage
  {
    __SOCKADDR_COMMON (ss_);	/* Address family, etc.  */
    __ss_aligntype __ss_align;	/* Force desired alignment.  */
    char __ss_padding[_SS_PADSIZE];
  };


#define IPV6_V6ONLY 0
#define TCP_NODELAY 0

#ifdef __cplusplus

#endif // __cplusplus

#endif /* QPID_EMBOX_COMPAT_H_ */
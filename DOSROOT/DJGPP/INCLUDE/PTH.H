/*
**  GNU Pth - The GNU Portable Threads
**  Copyright (c) 1999-2006 Ralf S. Engelschall <rse@engelschall.com>
**
**  This file is part of GNU Pth, a non-preemptive thread scheduling
**  library which can be found at http://www.gnu.org/software/pth/.
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
**  USA, or contact Ralf S. Engelschall <rse@engelschall.com>.
**
**  pth.h: Pth public API definitions
*/
                             /* ``What you see is all you get.''
                                          -- Brian Kernighan      */
#ifndef _PTH_H_
#define _PTH_H_

    /* the library version */
#ifndef PTH_VERSION_STR
#define PTH_VERSION_STR "2.0.7 (08-Jun-2006)"
#endif
#ifndef PTH_VERSION_HEX
#define PTH_VERSION_HEX 0x200207
#endif
#ifndef PTH_VERSION
#define PTH_VERSION PTH_VERSION_HEX
#endif

    /* essential headers */
#include <sys/types.h>     /* for ssize_t, off_t  */
#include <sys/wtime.h>     /* for struct timespec */
#include <sys/time.h>      /* for struct timeval  */
#include <sys/socket.h>    /* for sockaddr        */
#include <signal.h>        /* for sigset_t        */
#include <sys/select.h>

    /* fallbacks for essential typedefs */
#ifndef _PTHREAD_PRIVATE
/* typedef int pid_t; */
/* typedef unsigned int size_t; */
/* typedef unsigned int ssize_t; */
/*
 * CYGWIN pulls a trick on the preprocessor for the socklen_t type.
 * Until AC_CHECK_TYPEDEF macro in aclocal.m4 is aware of this, this
 * is a work-around to disable the warning
 */
#ifdef __CYGWIN__
#undef socklen_t
#endif
typedef int socklen_t;
/* typedef int off_t; */
/* typedef int sig_atomic_t; */
typedef unsigned int nfds_t;
#endif /* !_PTHREAD_PRIVATE */

    /* extra structure definitions */
struct timeval;
struct timespec;

    /* essential values */
#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
#ifndef NUL
#define NUL '\0'
#endif
#ifndef NULL
#define NULL (void *)0
#endif

    /* bitmask generation */
#define _BIT(n) (1<<(n))

    /* C++ support */
#ifdef __cplusplus
#define BEGIN_DECLARATION extern "C" {
#define END_DECLARATION   }
#else
#define BEGIN_DECLARATION /*nop*/
#define END_DECLARATION   /*nop*/
#endif

    /* check if the user requests a bigger FD_SETSIZE than we can handle */
#if defined(FD_SETSIZE)
#if FD_SETSIZE > 256
#error "FD_SETSIZE is larger than what GNU Pth can handle."
#endif
#endif

BEGIN_DECLARATION

    /* some global constants */
#define PTH_KEY_MAX                  256
#define PTH_ATFORK_MAX               128
#define PTH_DESTRUCTOR_ITERATIONS    4

    /* system call mapping support type (soft variant can be overridden) */
#define PTH_SYSCALL_HARD 0
#ifndef PTH_SYSCALL_SOFT
#define PTH_SYSCALL_SOFT 0
#endif

    /* queries for pth_ctrl() */
#define PTH_CTRL_GETAVLOAD            _BIT(1)
#define PTH_CTRL_GETPRIO              _BIT(2)
#define PTH_CTRL_GETNAME              _BIT(3)
#define PTH_CTRL_GETTHREADS_NEW       _BIT(4)
#define PTH_CTRL_GETTHREADS_READY     _BIT(5)
#define PTH_CTRL_GETTHREADS_RUNNING   _BIT(6)
#define PTH_CTRL_GETTHREADS_WAITING   _BIT(7)
#define PTH_CTRL_GETTHREADS_SUSPENDED _BIT(8)
#define PTH_CTRL_GETTHREADS_DEAD      _BIT(9)
#define PTH_CTRL_GETTHREADS           (PTH_CTRL_GETTHREADS_NEW|\
                                       PTH_CTRL_GETTHREADS_READY|\
                                       PTH_CTRL_GETTHREADS_RUNNING|\
                                       PTH_CTRL_GETTHREADS_WAITING|\
                                       PTH_CTRL_GETTHREADS_SUSPENDED|\
                                       PTH_CTRL_GETTHREADS_DEAD)
#define PTH_CTRL_DUMPSTATE            _BIT(10)
#define PTH_CTRL_FAVOURNEW            _BIT(11)

    /* the time value structure */
typedef struct timeval pth_time_t;

    /* the unique thread id/handle */
typedef struct pth_st *pth_t;
struct pth_st;

    /* thread states */
typedef enum pth_state_en {
    PTH_STATE_SCHEDULER = 0,         /* the special scheduler thread only       */
    PTH_STATE_NEW,                   /* spawned, but still not dispatched       */
    PTH_STATE_READY,                 /* ready, waiting to be dispatched         */
    PTH_STATE_WAITING,               /* suspended, waiting until event occurred */
    PTH_STATE_DEAD                   /* terminated, waiting to be joined        */
} pth_state_t;

    /* thread priority values */
#define PTH_PRIO_MAX                 +5
#define PTH_PRIO_STD                  0
#define PTH_PRIO_MIN                 -5

    /* the thread attribute structure */
typedef struct pth_attr_st *pth_attr_t;
struct pth_attr_st;

    /* attribute set/get commands for pth_attr_{get,set}() */
enum {
    PTH_ATTR_PRIO,           /* RW [int]               priority of thread                */
    PTH_ATTR_NAME,           /* RW [char *]            name of thread                    */
    PTH_ATTR_JOINABLE,       /* RW [int]               thread detachment type            */
    PTH_ATTR_CANCEL_STATE,   /* RW [unsigned int]      thread cancellation state         */
    PTH_ATTR_STACK_SIZE,     /* RW [unsigned int]      stack size                        */
    PTH_ATTR_STACK_ADDR,     /* RW [char *]            stack lower address               */
    PTH_ATTR_DISPATCHES,     /* RO [int]               total number of thread dispatches */
    PTH_ATTR_TIME_SPAWN,     /* RO [pth_time_t]        time thread was spawned           */
    PTH_ATTR_TIME_LAST,      /* RO [pth_time_t]        time thread was last dispatched   */
    PTH_ATTR_TIME_RAN,       /* RO [pth_time_t]        time thread was running           */
    PTH_ATTR_START_FUNC,     /* RO [void *(*)(void *)] thread start function             */
    PTH_ATTR_START_ARG,      /* RO [void *]            thread start argument             */
    PTH_ATTR_STATE,          /* RO [pth_state_t]       scheduling state                  */
    PTH_ATTR_EVENTS,         /* RO [pth_event_t]       events the thread is waiting for  */
    PTH_ATTR_BOUND           /* RO [int]               whether object is bound to thread */
};

    /* default thread attribute */
#define PTH_ATTR_DEFAULT (pth_attr_t)(0)

    /* the event structure */
typedef struct pth_event_st *pth_event_t;
struct pth_event_st;

    /* event subject classes */
#define PTH_EVENT_FD                 _BIT(1)
#define PTH_EVENT_SELECT             _BIT(2)
#define PTH_EVENT_SIGS               _BIT(3)
#define PTH_EVENT_TIME               _BIT(4)
#define PTH_EVENT_MSG                _BIT(5)
#define PTH_EVENT_MUTEX              _BIT(6)
#define PTH_EVENT_COND               _BIT(7)
#define PTH_EVENT_TID                _BIT(8)
#define PTH_EVENT_FUNC               _BIT(9)
#define PTH_EVENT_SEM                _BIT(10)

    /* event occurange restrictions */
#define PTH_UNTIL_OCCURRED           _BIT(11)
#define PTH_UNTIL_FD_READABLE        _BIT(12)
#define PTH_UNTIL_FD_WRITEABLE       _BIT(13)
#define PTH_UNTIL_FD_EXCEPTION       _BIT(14)
#define PTH_UNTIL_TID_NEW            _BIT(15)
#define PTH_UNTIL_TID_READY          _BIT(16)
#define PTH_UNTIL_TID_WAITING        _BIT(17)
#define PTH_UNTIL_TID_DEAD           _BIT(18)
#define PTH_UNTIL_DECREMENT          _BIT(19)
#define PTH_UNTIL_COUNT  	     _BIT(23)

    /* event structure handling modes */
#define PTH_MODE_REUSE               _BIT(20)
#define PTH_MODE_CHAIN               _BIT(21)
#define PTH_MODE_STATIC              _BIT(22)

    /* event deallocation types */
enum { PTH_FREE_THIS, PTH_FREE_ALL };

    /* event walking directions */
#define PTH_WALK_NEXT                _BIT(1)
#define PTH_WALK_PREV                _BIT(2)

    /* event status codes */
typedef enum {
    PTH_STATUS_PENDING,
    PTH_STATUS_OCCURRED,
    PTH_STATUS_FAILED
} pth_status_t;

    /* the key type and init value */
typedef int pth_key_t;
#define PTH_KEY_INIT (-1)

    /* the once structure and init value */
typedef int pth_once_t;
#define PTH_ONCE_INIT FALSE

    /* general ring structure */
typedef struct pth_ringnode_st pth_ringnode_t;
struct pth_ringnode_st {
    pth_ringnode_t *rn_next;
    pth_ringnode_t *rn_prev;
};
typedef struct pth_ring_st pth_ring_t;
struct pth_ring_st {
    pth_ringnode_t *r_hook;
    unsigned int    r_nodes;
};
#define PTH_RING_INIT { NULL }

    /* cancellation values */
#define PTH_CANCEL_ENABLE            _BIT(0)
#define PTH_CANCEL_DISABLE           _BIT(1)
#define PTH_CANCEL_ASYNCHRONOUS      _BIT(2)
#define PTH_CANCEL_DEFERRED          _BIT(3)
#define PTH_CANCEL_DEFAULT           (PTH_CANCEL_ENABLE|PTH_CANCEL_DEFERRED)
#define PTH_CANCELED                 ((void *)-1)

   /* mutex values */
#define PTH_MUTEX_INITIALIZED        _BIT(0)
#define PTH_MUTEX_LOCKED             _BIT(1)
#define PTH_MUTEX_INIT               { {NULL, NULL}, PTH_MUTEX_INITIALIZED, NULL, 0 }

   /* read-write lock values */
enum { PTH_RWLOCK_RD, PTH_RWLOCK_RW };
#define PTH_RWLOCK_INITIALIZED       _BIT(0)
#define PTH_RWLOCK_INIT              { PTH_RWLOCK_INITIALIZED, PTH_RWLOCK_RD, 0, \
                                       PTH_MUTEX_INIT, PTH_MUTEX_INIT }

   /* condition variable values */
#define PTH_COND_INITIALIZED         _BIT(0)
#define PTH_COND_SIGNALED            _BIT(1)
#define PTH_COND_BROADCAST           _BIT(2)
#define PTH_COND_HANDLED             _BIT(3)
#define PTH_COND_INIT                { PTH_COND_INITIALIZED, 0 }

   /* semaphore variable values */
#define PTH_SEM_INITIALIZED          _BIT(0)
#define PTH_SEM_INIT                 { PTH_SEM_INITIALIZED, 0 }

   /* barrier variable values */
#define PTH_BARRIER_INITIALIZED      _BIT(0)
#define PTH_BARRIER_INIT(threshold)  { PTH_BARRIER_INITIALIZED, \
                                       (threshold), (threshold), FALSE, \
                                       PTH_COND_INIT, PTH_MUTEX_INIT }
#define PTH_BARRIER_HEADLIGHT        (-1)
#define PTH_BARRIER_TAILLIGHT        (-2)

    /* the message port structure */
typedef struct pth_msgport_st *pth_msgport_t;
struct pth_msgport_st;

    /* the message structure */
typedef struct pth_message_st pth_message_t;
struct pth_message_st { /* not hidden to allow inclusion */
    pth_ringnode_t m_node;
    pth_msgport_t  m_replyport;
    unsigned int   m_size;
    void          *m_data;
};

    /* the mutex structure */
typedef struct pth_mutex_st pth_mutex_t;
struct pth_mutex_st { /* not hidden to avoid destructor */
    pth_ringnode_t mx_node;
    int            mx_state;
    pth_t          mx_owner;
    unsigned long  mx_count;
};

    /* the read-write lock structure */
typedef struct pth_rwlock_st pth_rwlock_t;
struct pth_rwlock_st { /* not hidden to avoid destructor */
    int            rw_state;
    unsigned int   rw_mode;
    unsigned long  rw_readers;
    pth_mutex_t    rw_mutex_rd;
    pth_mutex_t    rw_mutex_rw;
};

    /* the condition variable structure */
typedef struct pth_cond_st pth_cond_t;
struct pth_cond_st { /* not hidden to avoid destructor */
    unsigned long cn_state;
    unsigned int  cn_waiters;
};

    /* the semaphore variable structure */
typedef struct pth_sem_st pth_sem_t;
struct pth_sem_st { /* not hidden to avoid destructor */
    unsigned long sem_state;
    unsigned int  sem_count;
};

    /* the barrier variable structure */
typedef struct pth_barrier_st pth_barrier_t;
struct pth_barrier_st { /* not hidden to avoid destructor */
    unsigned long br_state;
    int           br_threshold;
    int           br_count;
    int           br_cycle;
    pth_cond_t    br_cond;
    pth_mutex_t   br_mutex;
};

    /* the user-space context structure */
typedef struct pth_uctx_st *pth_uctx_t;
struct pth_uctx_st;

    /* filedescriptor blocking modes */
enum {
    PTH_FDMODE_ERROR = -1,
    PTH_FDMODE_POLL  =  0,
    PTH_FDMODE_BLOCK,
    PTH_FDMODE_NONBLOCK
};

    /* optionally fake poll(2) data structure and options */
#ifndef _PTHREAD_PRIVATE
#define PTH_FAKE_POLL 1
#if !(PTH_FAKE_POLL)
/* use vendor poll(2) environment */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_set
#endif
#include <poll.h>
#ifdef _XOPEN_SOURCE_set
#undef _XOPEN_SOURCE_set
#undef _XOPEN_SOURCE
#endif
#ifndef POLLRDNORM
#define POLLRDNORM POLLIN
#endif
#ifndef POLLRDBAND
#define POLLRDBAND POLLIN
#endif
#ifndef POLLWRNORM
#define POLLWRNORM POLLOUT
#endif
#ifndef POLLWRBAND
#define POLLWRBAND POLLOUT
#endif
#ifndef INFTIM
#define INFTIM (-1)
#endif
#else
/* fake a poll(2) environment */
#define POLLIN      0x0001      /* any readable data available   */
#define POLLPRI     0x0002      /* OOB/Urgent readable data      */
#define POLLOUT     0x0004      /* file descriptor is writeable  */
#define POLLERR     0x0008      /* some poll error occurred      */
#define POLLHUP     0x0010      /* file descriptor was "hung up" */
#define POLLNVAL    0x0020      /* requested events "invalid"    */
#define POLLRDNORM  POLLIN
#define POLLRDBAND  POLLIN
#define POLLWRNORM  POLLOUT
#define POLLWRBAND  POLLOUT
#ifndef INFTIM
#define INFTIM      (-1)        /* poll infinite */
#endif
struct pollfd {
    int fd;                     /* which file descriptor to poll */
    short events;               /* events we are interested in   */
    short revents;              /* events found on return        */
};
#endif
#endif /* !_PTHREAD_PRIVATE */

    /* optionally fake readv(2)/writev(2) data structure and options */
#ifndef _PTHREAD_PRIVATE
#define PTH_FAKE_RWV 0
#define PTH_WATT_RWV 0
#if !(PTH_FAKE_RWV) && !(PTH_WATT_RWV)
/* use vendor readv(2)/writev(2) environment */
#include <sys/uio.h>
#ifndef UIO_MAXIOV
#define UIO_MAXIOV 1024
#endif
#elif (PTH_WATT_RWV)
/* use Watt-32 readv(2)/writev(2) environment */
#include <sys/wtypes.h>
#ifndef UIO_MAXIOV
#define UIO_MAXIOV 1024
#endif
#else
/* fake a readv(2)/writev(2) environment */
struct iovec {
    void  *iov_base;  /* memory base address */
    size_t iov_len;   /* memory chunk length */
};
#ifndef UIO_MAXIOV
#define UIO_MAXIOV 1024
#endif
#endif
#endif /* !_PTHREAD_PRIVATE */

    /* extension support */
#define PTH_EXT_SFIO 0

    /* Sfio extension support */
#if 0
#include <sfio.h>
#else
typedef void *Sfdisc_t;
#endif

    /* global functions */
extern int            pth_init(void);
extern int            pth_kill(void);
extern long           pth_ctrl(unsigned long, ...);
extern long           pth_version(void);

    /* thread attribute functions */
extern pth_attr_t     pth_attr_of(pth_t);
extern pth_attr_t     pth_attr_new(void);
extern int            pth_attr_init(pth_attr_t);
extern int            pth_attr_set(pth_attr_t, int, ...);
extern int            pth_attr_get(pth_attr_t, int, ...);
extern int            pth_attr_destroy(pth_attr_t);

    /* thread functions */
extern pth_t          pth_spawn(pth_attr_t, void *(*)(void *), void *);
extern int            pth_once(pth_once_t *, void (*)(void *), void *);
extern pth_t          pth_self(void);
extern int            pth_suspend(pth_t);
extern int            pth_resume(pth_t);
extern int            pth_yield(pth_t);
extern int            pth_nap(pth_time_t);
extern int            pth_wait(pth_event_t);
extern int            pth_cancel(pth_t);
extern int            pth_abort(pth_t);
extern int            pth_raise(pth_t, int);
extern int            pth_join(pth_t, void **);
extern void           pth_exit(void *);

    /* utility functions */
extern int            pth_fdmode(int, int);
extern pth_time_t     pth_time(long, long);
extern pth_time_t     pth_timeout(long, long);

    /* cancellation functions */
extern void           pth_cancel_state(int, int *);
extern void           pth_cancel_point(void);

    /* event functions */
extern pth_event_t    pth_event(unsigned long, ...);
extern unsigned long  pth_event_typeof(pth_event_t);
extern int            pth_event_extract(pth_event_t ev, ...);
extern pth_event_t    pth_event_concat(pth_event_t, ...);
extern pth_event_t    pth_event_isolate(pth_event_t);
extern pth_event_t    pth_event_walk(pth_event_t, unsigned int);
extern pth_status_t   pth_event_status(pth_event_t);
extern int            pth_event_free(pth_event_t, int);

    /* key-based storage functions */
extern int            pth_key_create(pth_key_t *, void (*)(void *));
extern int            pth_key_delete(pth_key_t);
extern int            pth_key_setdata(pth_key_t, const void *);
extern void          *pth_key_getdata(pth_key_t);

    /* message port functions */
extern pth_msgport_t  pth_msgport_create(const char *);
extern void           pth_msgport_destroy(pth_msgport_t);
extern pth_msgport_t  pth_msgport_find(const char *);
extern int            pth_msgport_pending(pth_msgport_t);
extern int            pth_msgport_put(pth_msgport_t, pth_message_t *);
extern pth_message_t *pth_msgport_get(pth_msgport_t);
extern int            pth_msgport_reply(pth_message_t *);

    /* cleanup handler functions */
extern int            pth_cleanup_push(void (*)(void *), void *);
extern int            pth_cleanup_pop(int);

    /* process forking functions */
extern int            pth_atfork_push(void (*)(void *), void (*)(void *), void (*)(void *), void *);
extern int            pth_atfork_pop(void);
extern pid_t          pth_fork(void);

    /* synchronization functions */
extern int            pth_mutex_init(pth_mutex_t *);
extern int            pth_mutex_acquire(pth_mutex_t *, int, pth_event_t);
extern int            pth_mutex_release(pth_mutex_t *);
extern int            pth_rwlock_init(pth_rwlock_t *);
extern int            pth_rwlock_acquire(pth_rwlock_t *, int, int, pth_event_t);
extern int            pth_rwlock_release(pth_rwlock_t *);
extern int            pth_cond_init(pth_cond_t *);
extern int            pth_cond_await(pth_cond_t *, pth_mutex_t *, pth_event_t);
extern int            pth_cond_notify(pth_cond_t *, int);
extern int            pth_barrier_init(pth_barrier_t *, int);
extern int            pth_barrier_reach(pth_barrier_t *);
extern int            pth_sem_init(pth_sem_t *);
extern int            pth_sem_dec(pth_sem_t *);
extern int            pth_sem_dec_value(pth_sem_t *, unsigned);
extern int            pth_sem_inc(pth_sem_t *, int);
extern int            pth_sem_inc_value(pth_sem_t *, unsigned, int);
extern int            pth_sem_set_value(pth_sem_t *, unsigned);
extern int            pth_sem_get_value(pth_sem_t *, unsigned *);

    /* user-space context functions */
extern int            pth_uctx_create(pth_uctx_t *);
extern int            pth_uctx_make(pth_uctx_t, char *, size_t, const sigset_t *, void (*)(void *), void *, pth_uctx_t);
extern int            pth_uctx_switch(pth_uctx_t, pth_uctx_t);
extern int            pth_uctx_destroy(pth_uctx_t);

    /* extension functions */
extern Sfdisc_t      *pth_sfiodisc(void);

    /* generalized variants of replacement functions */
extern int            pth_sigwait_ev(const sigset_t *, int *, pth_event_t);
extern int            pth_connect_ev(int, const struct sockaddr *, socklen_t, pth_event_t);
extern int            pth_accept_ev(int, struct sockaddr *, socklen_t *, pth_event_t);
extern int            pth_select_ev(int, fd_set *, fd_set *, fd_set *, struct timeval *, pth_event_t);
extern int            pth_poll_ev(struct pollfd *, nfds_t, int, pth_event_t);
extern ssize_t        pth_read_ev(int, void *, size_t, pth_event_t);
extern ssize_t        pth_write_ev(int, const void *, size_t, pth_event_t);
extern ssize_t        pth_readv_ev(int, const struct iovec *, int, pth_event_t);
extern ssize_t        pth_writev_ev(int, const struct iovec *, int, pth_event_t);
extern ssize_t        pth_recv_ev(int, void *, size_t, int, pth_event_t);
extern ssize_t        pth_send_ev(int, const void *, size_t, int, pth_event_t);
extern ssize_t        pth_recvfrom_ev(int, void *, size_t, int, struct sockaddr *, socklen_t *, pth_event_t);
extern ssize_t        pth_sendto_ev(int, const void *, size_t, int, const struct sockaddr *, socklen_t, pth_event_t);

    /* standard replacement functions */
extern int            pth_nanosleep(const struct timespec *, struct timespec *);
extern int            pth_usleep(unsigned int);
extern unsigned int   pth_sleep(unsigned int);
extern pid_t          pth_waitpid(pid_t, int *, int);
extern int            pth_system(const char *);
extern int            pth_sigmask(int, const sigset_t *, sigset_t *);
extern int            pth_sigwait(const sigset_t *, int *);
extern int            pth_connect(int, const struct sockaddr *, socklen_t);
extern int            pth_accept(int, struct sockaddr *, socklen_t *);
extern int            pth_select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
extern int            pth_pselect(int, fd_set *, fd_set *, fd_set *, const struct timespec *, const sigset_t *);
extern int            pth_poll(struct pollfd *, nfds_t, int);
extern ssize_t        pth_read(int, void *, size_t);
extern ssize_t        pth_write(int, const void *, size_t);
extern ssize_t        pth_readv(int, const struct iovec *, int);
extern ssize_t        pth_writev(int, const struct iovec *, int);
extern ssize_t        pth_recv(int, void *, size_t, int);
extern ssize_t        pth_send(int, const void *, size_t, int);
extern ssize_t        pth_recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
extern ssize_t        pth_sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
extern ssize_t        pth_pread(int, void *, size_t, off_t);
extern ssize_t        pth_pwrite(int, const void *, size_t, off_t);

END_DECLARATION

    /* soft system call mapping support */
#if PTH_SYSCALL_SOFT && !defined(_PTH_PRIVATE)
#define fork          pth_fork
#define waitpid       pth_waitpid
#define system        pth_system
#define nanosleep     pth_nanosleep
#define usleep        pth_usleep
#define sleep         pth_sleep
#define sigprocmask   pth_sigmask
#define sigwait       pth_sigwait
#define select        pth_select
#define pselect       pth_pselect
#define poll          pth_poll
#define connect       pth_connect
#define accept        pth_accept
#define read          pth_read
#define write         pth_write
#define readv         pth_readv
#define writev        pth_writev
#define recv          pth_recv
#define send          pth_send
#define recvfrom      pth_recvfrom
#define sendto        pth_sendto
#define pread         pth_pread
#define pwrite        pth_pwrite
#endif

    /* backward compatibility (Pth < 1.5.0) */
#define pth_event_occurred(ev) \
    (   pth_event_status(ev) == PTH_STATUS_OCCURRED \
     || pth_event_status(ev) == PTH_STATUS_FAILED   )

#endif /* _PTH_H_ */


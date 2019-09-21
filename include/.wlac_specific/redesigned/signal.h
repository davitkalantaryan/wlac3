// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

/*
 *	File: <strings.h> For WINDOWS MFC
 *
 *	Created on: Dec 22, 2015
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef __win_signal_new_h__
#define __win_signal_new_h__

#include <.wlac_specific/first_includes/wlac2_common_internal.h>

#pragma include_alias( <signal.h>, <signal.h> )
#pragma include_alias( "signal.h", "signal.h" )
#include <signal.h>

//#include <.wlac_specific/rfc2/windows_signal.h>
#include <pthread.h>
#include <.wlac_specific/redesigned/sys/types.h>
#include <time.h>

# define __SI_MAX_SIZE     128
# if __WORDSIZE == 64
#ifndef __SI_PAD_SIZE
#  define __SI_PAD_SIZE     ((__SI_MAX_SIZE / sizeof (int)) - 4)
#endif
# else
#ifndef __SI_PAD_SIZE
#  define __SI_PAD_SIZE     ((__SI_MAX_SIZE / sizeof (int)) - 3)
#endif
# endif

// http://man7.org/linux/man-pages/man7/signal.7.html
// SIGIO is different for different architectures
// for x86 and arm it is 29
#ifndef SIGIO
#define	SIGIO		29	/* I/O now possible (4.2 BSD).  */
#endif
#ifndef SIGALRM
#define	SIGALRM		14	/* I/O now possible (4.2 BSD).  */
#endif
#ifndef SIGPIPE
#define	SIGPIPE		13	/* I/O now possible (4.2 BSD).  */
#endif

# define SA_RESTART   0x10000000 /* Restart syscall on signal return.  */

/* Values for the HOW argument to `sigprocmask'.  */
#ifndef SIG_BLOCK
#define	SIG_BLOCK     0		 /* Block signals.  */
#endif
#ifndef SIG_UNBLOCK
#define	SIG_UNBLOCK   1		 /* Unblock signals.  */
#endif
#ifndef SIG_SETMASK
#define	SIG_SETMASK   2		 /* Set the set of blocked signals.  */
#endif

/* Type of a signal handler.  */
#if !defined(__sighandler_t_defined) && !defined(____sighandler_t_defined)
typedef void(*__sighandler_t) (int);
#define __sighandler_t_defined
#define ____sighandler_t_defined
#endif  // #if !defined(__sighandler_t_defined) && defined(____sighandler_t_defined)

/* A `sigset_t' has a bit for each signal.  */
# define _SIGSET_NWORDS	(1024 / (8 * sizeof (unsigned long int)))
typedef struct
{
	unsigned long int __val[_SIGSET_NWORDS];
} __sigset_t;


//#if defined __need_sigset_t || (defined _SIGNAL_H && defined __USE_POSIX)
#if !defined(__sigset_t_defined) && !defined(sigset_t_defined)
typedef __sigset_t sigset_t;
#  define __sigset_t_defined
#define sigset_t_defined
#endif  // #if !defined(__sigset_t_defined) && !defined(sigset_t_defined)

#if !defined(__pid_t_defined) && !defined(pid_t_defined)
typedef unsigned int pid_t;
#define __pid_t_defined
#define pid_t_defined
#endif

/* Type for data associated with a signal.  */
typedef union sigval
{
	int sival_int;
	void *sival_ptr;
} sigval_t;

typedef struct siginfo
{
	int si_signo;		/* Signal number.  */
	int si_errno;		/* If non-zero, an errno value associated with
						this signal, as defined in <errno.h>.  */
	int si_code;		/* Signal code.  */

	union
	{
		int _pad[__SI_PAD_SIZE];

		/* kill().  */
		struct
		{
			pid_t si_pid;	/* Sending process ID.  */
			uid_t si_uid;	/* Real user ID of sending process.  */
		} _kill;

		/* POSIX.1b timers.  */
		struct
		{
			int si_tid;		/* Timer ID.  */
			int si_overrun;	/* Overrun count.  */
			sigval_t si_sigval;	/* Signal value.  */
		} _timer;

		/* POSIX.1b signals.  */
		struct
		{
			pid_t si_pid;	/* Sending process ID.  */
			uid_t si_uid;	/* Real user ID of sending process.  */
			sigval_t si_sigval;	/* Signal value.  */
		} _rt;

		/* SIGCHLD.  */
		struct
		{
			pid_t si_pid;	/* Which child.  */
			uid_t si_uid;	/* Real user ID of sending process.  */
			int si_status;	/* Exit value or signal.  */
			clock_t si_utime;
			clock_t si_stime;
		} _sigchld;

		/* SIGILL, SIGFPE, SIGSEGV, SIGBUS.  */
		struct
		{
			void *si_addr;	/* Faulting insn/memory ref.  */
		} _sigfault;

		/* SIGPOLL.  */
		struct
		{
			long int si_band;	/* Band event for SIGPOLL.  */
			int si_fd;
		} _sigpoll;
	} _sifields;
} siginfo_t;

/* Structure describing the action to be taken when a signal arrives.  */
struct sigaction
{
	/* Signal handler.  */
#ifdef __USE_POSIX199309
	union
	{
		/* Used if SA_SIGINFO is not set.  */
		__sighandler_t sa_handler;
		/* Used if SA_SIGINFO is set.  */
		void(*sa_sigaction) (int, siginfo_t *, void *);
	}
	__sigaction_handler;
# define sa_handler	__sigaction_handler.sa_handler
# define sa_sigaction	__sigaction_handler.sa_sigaction
#else
	__sighandler_t sa_handler;
#endif

	/* Additional set of signals to be blocked.  */
	__sigset_t sa_mask;

	/* Special flags.  */
	int sa_flags;

	/* Restore handler.  */
	void(*sa_restorer) (void);
};

// #if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_poll_needed) || defined(poll_needed)

BEGIN_C_DECL2

/* Clear all signals from SET.  */
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigemptyset_needed)
WLAC_EXPORT int sigemptyset(sigset_t *__set) ;
#endif
/* Add SIGNO to SET.  */
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigaddset_needed)
WLAC_EXPORT int sigaddset(sigset_t *__set, int __signo) ;
#endif
/* Get and/or set the action for signal SIG.  */
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigaction_needed)
WLAC_EXPORT int sigaction(int sig, const struct sigaction * action, struct sigaction * oldAction) ;
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(pthread_sigmask_needed)
WLAC_EXPORT int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(pthread_kill_needed)
WLAC_EXPORT int pthread_kill(pthread_t thread, int sig);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigtimedwait_needed) || defined(sigwaitinfo_needed)
WLAC_EXPORT int sigtimedwait(const sigset_t * a_set, siginfo_t * a_info, const struct timespec * a_timeout);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigwait_needed)
WLAC_EXPORT int sigwait(const sigset_t *set, int *sig);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigfillset_needed)
WLAC_EXPORT int sigfillset(sigset_t *set);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(kill_needed)
WLAC_EXPORT int kill(pid_t pid, int sig);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigemptyset_needed)
WLAC_EXPORT int sigemptyset(sigset_t *set);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigaddset_needed)
WLAC_EXPORT int sigaddset(sigset_t *set, int signum);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigwaitinfo_needed)
#define sigwaitinfo(_set,_info)	sigtimedwait((_set),(_info),NEWNULLPTR2)
#endif
//#define signal	wlac_signal

END_C_DECL2



#endif  /* #ifndef __win_signal_new_h__ */

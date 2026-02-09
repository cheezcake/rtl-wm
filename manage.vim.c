# 1 "manage.c"
# 1 "<eingebaut>"
# 1 "<Kommandozeile>"
# 1 "manage.c"

static char sccs_id[] = "@(#)manage.c	5.7  9/1/88";
# 27 "manage.c"
# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 358 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 353 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 354 "/usr/include/sys/cdefs.h" 2 3 4
# 359 "/usr/include/features.h" 2 3 4
# 382 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4




# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 2 3 4
# 383 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 1 3 4
# 212 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 324 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 3 4
typedef int wchar_t;
# 34 "/usr/include/stdlib.h" 2 3 4








# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 43 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 65 "/usr/include/bits/waitstatus.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 38 "/usr/include/endian.h" 2 3 4
# 61 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 28 "/usr/include/bits/byteswap.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/byteswap.h" 2 3 4
# 62 "/usr/include/endian.h" 2 3 4
# 66 "/usr/include/bits/waitstatus.h" 2 3 4

union wait
  {
    int w_status;
    struct
      {

 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;







      } __wait_terminated;
    struct
      {

 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;






      } __wait_stopped;
  };
# 44 "/usr/include/stdlib.h" 2 3 4
# 68 "/usr/include/stdlib.h" 3 4
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));
# 96 "/usr/include/stdlib.h" 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;







__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


# 140 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__)) ;




extern double atof (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





__extension__ extern long long int atoll (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





extern double strtod (__const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern float strtof (__const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

extern long double strtold (__const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern long int strtol (__const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

extern unsigned long int strtoul (__const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;




__extension__
extern long long int strtoq (__const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





__extension__
extern long long int strtoll (__const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

# 311 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__)) ;


extern long int a64l (__const char *__s)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/sys/types.h" 1 3 4
# 28 "/usr/include/sys/types.h" 3 4


# 1 "/usr/include/bits/types.h" 1 3 4
# 28 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 131 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 132 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 31 "/usr/include/sys/types.h" 2 3 4



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 61 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 99 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 133 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 58 "/usr/include/time.h" 3 4


typedef __clock_t clock_t;



# 74 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 92 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 104 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 134 "/usr/include/sys/types.h" 2 3 4
# 147 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 1 3 4
# 148 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 195 "/usr/include/sys/types.h" 3 4
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 220 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/sys/select.h" 1 3 4
# 31 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 23 "/usr/include/bits/select.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/select.h" 2 3 4
# 32 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/sigset.h" 1 3 4
# 24 "/usr/include/bits/sigset.h" 3 4
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/include/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3 4
# 120 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 31 "/usr/include/bits/time.h" 3 4
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/include/sys/select.h" 2 3 4


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 67 "/usr/include/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 99 "/usr/include/sys/select.h" 3 4

# 109 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 121 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);



# 221 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 30 "/usr/include/sys/sysmacros.h" 3 4


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__));
# 64 "/usr/include/sys/sysmacros.h" 3 4

# 224 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 271 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4
# 50 "/usr/include/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


typedef union
{
  char __size[56];
  long int __align;
} pthread_attr_t;



typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 76 "/usr/include/bits/pthreadtypes.h" 3 4
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    int __spins;
    __pthread_list_t __list;
# 101 "/usr/include/bits/pthreadtypes.h" 3 4
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{

  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;
  } __data;
# 187 "/usr/include/bits/pthreadtypes.h" 3 4
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 272 "/usr/include/sys/types.h" 2 3 4



# 321 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));






extern int rand (void) __attribute__ ((__nothrow__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__));




extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__));







extern double drand48 (void) __attribute__ ((__nothrow__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));









extern void *malloc (size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;










extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__)) __attribute__ ((__warn_unused_result__));

extern void free (void *__ptr) __attribute__ ((__nothrow__));




extern void cfree (void *__ptr) __attribute__ ((__nothrow__));



# 1 "/usr/include/alloca.h" 1 3 4
# 25 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 1 3 4
# 26 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__));






# 498 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;




extern void abort (void) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 531 "/usr/include/stdlib.h" 3 4





extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern void exit (int __status) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
# 554 "/usr/include/stdlib.h" 3 4






extern void _Exit (int __status) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));






extern char *getenv (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;




extern char *__secure_getenv (__const char *__name)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern int putenv (char *__string) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (__const char *__name, __const char *__value, int __replace)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__));
# 606 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 620 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 642 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 663 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 712 "/usr/include/stdlib.h" 3 4





extern int system (__const char *__command) ;

# 734 "/usr/include/stdlib.h" 3 4
extern char *realpath (__const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__)) ;






typedef int (*__compar_fn_t) (__const void *, __const void *);
# 752 "/usr/include/stdlib.h" 3 4



extern void *bsearch (__const void *__key, __const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;



extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 771 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;



__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;







extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;




__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;

# 808 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));







extern int mblen (__const char *__s, size_t __n) __attribute__ ((__nothrow__)) ;


extern int mbtowc (wchar_t *__restrict __pwc,
     __const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__)) ;


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__)) ;



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   __const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__));

extern size_t wcstombs (char *__restrict __s,
   __const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__));








extern int rpmatch (__const char *__response) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 896 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *__const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 948 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 964 "/usr/include/stdlib.h" 3 4

# 28 "manage.c" 2
# 1 "copyright.h" 1
# 29 "copyright.h"
static char copyright[] = "";
# 29 "manage.c" 2

# 1 "basetype.h" 1
# 38 "basetype.h"
# 1 "std_defs.h" 1
# 42 "std_defs.h"
typedef int bool;

typedef char *pointer;
typedef void (*VoidFunc)();
# 121 "std_defs.h"
# 1 "/usr/include/X11/Xos.h" 1 3 4
# 36 "/usr/include/X11/Xos.h" 3 4
# 1 "/usr/include/X11/Xosdefs.h" 1 3 4
# 37 "/usr/include/X11/Xos.h" 2 3 4
# 62 "/usr/include/X11/Xos.h" 3 4
# 1 "/usr/include/string.h" 1 3 4
# 29 "/usr/include/string.h" 3 4





# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 1 3 4
# 35 "/usr/include/string.h" 2 3 4









extern void *memcpy (void *__restrict __dest,
       __const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, __const void *__src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, __const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 95 "/usr/include/string.h" 3 4
extern void *memchr (__const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 126 "/usr/include/string.h" 3 4


extern char *strcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));






# 1 "/usr/include/xlocale.h" 1 3 4
# 28 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 163 "/usr/include/string.h" 2 3 4


extern int strcoll_l (__const char *__s1, __const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, __const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (__const char *__s)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (__const char *__string, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 210 "/usr/include/string.h" 3 4

# 235 "/usr/include/string.h" 3 4
extern char *strchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 262 "/usr/include/string.h" 3 4
extern char *strrchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 281 "/usr/include/string.h" 3 4



extern size_t strcspn (__const char *__s, __const char *__reject)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (__const char *__s, __const char *__accept)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 314 "/usr/include/string.h" 3 4
extern char *strpbrk (__const char *__s, __const char *__accept)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 342 "/usr/include/string.h" 3 4
extern char *strstr (__const char *__haystack, __const char *__needle)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, __const char *__restrict __delim)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));




extern char *__strtok_r (char *__restrict __s,
    __const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, __const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3)));
# 397 "/usr/include/string.h" 3 4


extern size_t strlen (__const char *__s)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (__const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) __attribute__ ((__nothrow__));

# 427 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__))

                        __attribute__ ((__nonnull__ (2)));
# 445 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__));





extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern void bcopy (__const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 489 "/usr/include/string.h" 3 4
extern char *index (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 517 "/usr/include/string.h" 3 4
extern char *rindex (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern int ffs (int __i) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
# 536 "/usr/include/string.h" 3 4
extern int strcasecmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 559 "/usr/include/string.h" 3 4
extern char *strsep (char **__restrict __stringp,
       __const char *__restrict __delim)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__));


extern char *__stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 646 "/usr/include/string.h" 3 4

# 63 "/usr/include/X11/Xos.h" 2 3 4
# 88 "/usr/include/X11/Xos.h" 3 4
# 1 "/usr/include/fcntl.h" 1 3 4
# 30 "/usr/include/fcntl.h" 3 4




# 1 "/usr/include/bits/fcntl.h" 1 3 4
# 26 "/usr/include/bits/fcntl.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 27 "/usr/include/bits/fcntl.h" 2 3 4
# 168 "/usr/include/bits/fcntl.h" 3 4
struct flock
  {
    short int l_type;
    short int l_whence;

    __off_t l_start;
    __off_t l_len;




    __pid_t l_pid;
  };
# 266 "/usr/include/bits/fcntl.h" 3 4

# 340 "/usr/include/bits/fcntl.h" 3 4

# 35 "/usr/include/fcntl.h" 2 3 4





# 1 "/usr/include/time.h" 1 3 4
# 41 "/usr/include/fcntl.h" 2 3 4
# 1 "/usr/include/bits/stat.h" 1 3 4
# 46 "/usr/include/bits/stat.h" 3 4
struct stat
  {
    __dev_t st_dev;




    __ino_t st_ino;







    __nlink_t st_nlink;
    __mode_t st_mode;

    __uid_t st_uid;
    __gid_t st_gid;

    int __pad0;

    __dev_t st_rdev;




    __off_t st_size;



    __blksize_t st_blksize;

    __blkcnt_t st_blocks;
# 91 "/usr/include/bits/stat.h" 3 4
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
# 106 "/usr/include/bits/stat.h" 3 4
    long int __unused[3];
# 115 "/usr/include/bits/stat.h" 3 4
  };
# 42 "/usr/include/fcntl.h" 2 3 4
# 125 "/usr/include/fcntl.h" 3 4
extern int fcntl (int __fd, int __cmd, ...);
# 134 "/usr/include/fcntl.h" 3 4
extern int open (__const char *__file, int __oflag, ...) __attribute__ ((__nonnull__ (1)));
# 158 "/usr/include/fcntl.h" 3 4
extern int openat (int __fd, __const char *__file, int __oflag, ...)
     __attribute__ ((__nonnull__ (2)));
# 180 "/usr/include/fcntl.h" 3 4
extern int creat (__const char *__file, __mode_t __mode) __attribute__ ((__nonnull__ (1)));
# 209 "/usr/include/fcntl.h" 3 4
extern int lockf (int __fd, int __cmd, __off_t __len);
# 226 "/usr/include/fcntl.h" 3 4
extern int posix_fadvise (int __fd, __off_t __offset, __off_t __len,
     int __advise) __attribute__ ((__nothrow__));
# 248 "/usr/include/fcntl.h" 3 4
extern int posix_fallocate (int __fd, __off_t __offset, __off_t __len);
# 270 "/usr/include/fcntl.h" 3 4

# 89 "/usr/include/X11/Xos.h" 2 3 4
# 1 "/usr/include/unistd.h" 1 3 4
# 28 "/usr/include/unistd.h" 3 4

# 203 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/posix_opt.h" 1 3 4
# 204 "/usr/include/unistd.h" 2 3 4



# 1 "/usr/include/bits/environments.h" 1 3 4
# 23 "/usr/include/bits/environments.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/environments.h" 2 3 4
# 208 "/usr/include/unistd.h" 2 3 4
# 227 "/usr/include/unistd.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 1 3 4
# 228 "/usr/include/unistd.h" 2 3 4
# 256 "/usr/include/unistd.h" 3 4
typedef __useconds_t useconds_t;
# 268 "/usr/include/unistd.h" 3 4
typedef __intptr_t intptr_t;






typedef __socklen_t socklen_t;
# 288 "/usr/include/unistd.h" 3 4
extern int access (__const char *__name, int __type) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 305 "/usr/include/unistd.h" 3 4
extern int faccessat (int __fd, __const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2))) ;
# 331 "/usr/include/unistd.h" 3 4
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __attribute__ ((__nothrow__));
# 350 "/usr/include/unistd.h" 3 4
extern int close (int __fd);






extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;





extern ssize_t write (int __fd, __const void *__buf, size_t __n) ;
# 373 "/usr/include/unistd.h" 3 4
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset) ;






extern ssize_t pwrite (int __fd, __const void *__buf, size_t __n,
         __off_t __offset) ;
# 414 "/usr/include/unistd.h" 3 4
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__)) ;
# 429 "/usr/include/unistd.h" 3 4
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__));
# 441 "/usr/include/unistd.h" 3 4
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__));






extern int usleep (__useconds_t __useconds);
# 466 "/usr/include/unistd.h" 3 4
extern int pause (void);



extern int chown (__const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__)) ;




extern int lchown (__const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;






extern int fchownat (int __fd, __const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2))) ;



extern int chdir (__const char *__path) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchdir (int __fd) __attribute__ ((__nothrow__)) ;
# 508 "/usr/include/unistd.h" 3 4
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__)) ;
# 522 "/usr/include/unistd.h" 3 4
extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) ;




extern int dup (int __fd) __attribute__ ((__nothrow__)) ;


extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__));
# 540 "/usr/include/unistd.h" 3 4
extern char **__environ;







extern int execve (__const char *__path, char *__const __argv[],
     char *__const __envp[]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));




extern int fexecve (int __fd, char *__const __argv[], char *__const __envp[])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));




extern int execv (__const char *__path, char *__const __argv[])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execle (__const char *__path, __const char *__arg, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execl (__const char *__path, __const char *__arg, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execvp (__const char *__file, char *__const __argv[])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execlp (__const char *__file, __const char *__arg, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 595 "/usr/include/unistd.h" 3 4
extern int nice (int __inc) __attribute__ ((__nothrow__)) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/include/bits/confname.h" 1 3 4
# 26 "/usr/include/bits/confname.h" 3 4
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };
# 607 "/usr/include/unistd.h" 2 3 4


extern long int pathconf (__const char *__path, int __name)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__));


extern long int sysconf (int __name) __attribute__ ((__nothrow__));



extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__));




extern __pid_t getpid (void) __attribute__ ((__nothrow__));


extern __pid_t getppid (void) __attribute__ ((__nothrow__));




extern __pid_t getpgrp (void) __attribute__ ((__nothrow__));
# 643 "/usr/include/unistd.h" 3 4
extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__));

extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__));






extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__));
# 669 "/usr/include/unistd.h" 3 4
extern int setpgrp (void) __attribute__ ((__nothrow__));
# 686 "/usr/include/unistd.h" 3 4
extern __pid_t setsid (void) __attribute__ ((__nothrow__));



extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__));



extern __uid_t getuid (void) __attribute__ ((__nothrow__));


extern __uid_t geteuid (void) __attribute__ ((__nothrow__));


extern __gid_t getgid (void) __attribute__ ((__nothrow__));


extern __gid_t getegid (void) __attribute__ ((__nothrow__));




extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__)) ;
# 719 "/usr/include/unistd.h" 3 4
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__));




extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__));




extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__));






extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__));




extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__));




extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__));
# 775 "/usr/include/unistd.h" 3 4
extern __pid_t fork (void) __attribute__ ((__nothrow__));







extern __pid_t vfork (void) __attribute__ ((__nothrow__));





extern char *ttyname (int __fd) __attribute__ ((__nothrow__));



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2))) ;



extern int isatty (int __fd) __attribute__ ((__nothrow__));





extern int ttyslot (void) __attribute__ ((__nothrow__));




extern int link (__const char *__from, __const char *__to)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern int linkat (int __fromfd, __const char *__from, int __tofd,
     __const char *__to, int __flags)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4))) ;




extern int symlink (__const char *__from, __const char *__to)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern ssize_t readlink (__const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern int symlinkat (__const char *__from, int __tofd,
        __const char *__to) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3))) ;


extern ssize_t readlinkat (int __fd, __const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3))) ;



extern int unlink (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int unlinkat (int __fd, __const char *__name, int __flag)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));



extern int rmdir (__const char *__path) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__));


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__));






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));




extern int setlogin (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 890 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/getopt.h" 1 3 4
# 59 "/usr/include/getopt.h" 3 4
extern char *optarg;
# 73 "/usr/include/getopt.h" 3 4
extern int optind;




extern int opterr;



extern int optopt;
# 152 "/usr/include/getopt.h" 3 4
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__));
# 891 "/usr/include/unistd.h" 2 3 4







extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int sethostname (__const char *__name, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern int sethostid (long int __id) __attribute__ ((__nothrow__)) ;





extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
extern int setdomainname (__const char *__name, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern int vhangup (void) __attribute__ ((__nothrow__));


extern int revoke (__const char *__file) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int acct (__const char *__name) __attribute__ ((__nothrow__));



extern char *getusershell (void) __attribute__ ((__nothrow__));
extern void endusershell (void) __attribute__ ((__nothrow__));
extern void setusershell (void) __attribute__ ((__nothrow__));





extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__)) ;






extern int chroot (__const char *__path) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern char *getpass (__const char *__prompt) __attribute__ ((__nonnull__ (1)));
# 976 "/usr/include/unistd.h" 3 4
extern int fsync (int __fd);
# 990 "/usr/include/unistd.h" 3 4
extern long int gethostid (void);


extern void sync (void) __attribute__ ((__nothrow__));





extern int getpagesize (void) __attribute__ ((__nothrow__)) __attribute__ ((__const__));




extern int getdtablesize (void) __attribute__ ((__nothrow__));
# 1014 "/usr/include/unistd.h" 3 4
extern int truncate (__const char *__file, __off_t __length)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 1036 "/usr/include/unistd.h" 3 4
extern int ftruncate (int __fd, __off_t __length) __attribute__ ((__nothrow__)) ;
# 1057 "/usr/include/unistd.h" 3 4
extern int brk (void *__addr) __attribute__ ((__nothrow__)) ;





extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__));
# 1078 "/usr/include/unistd.h" 3 4
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__));
# 1132 "/usr/include/unistd.h" 3 4
extern int fdatasync (int __fildes);
# 1161 "/usr/include/unistd.h" 3 4
extern char *ctermid (char *__s) __attribute__ ((__nothrow__));
# 1170 "/usr/include/unistd.h" 3 4

# 90 "/usr/include/X11/Xos.h" 2 3 4
# 119 "/usr/include/X11/Xos.h" 3 4
# 1 "/usr/include/sys/time.h" 1 3 4
# 27 "/usr/include/sys/time.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 28 "/usr/include/sys/time.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 30 "/usr/include/sys/time.h" 2 3 4
# 39 "/usr/include/sys/time.h" 3 4

# 57 "/usr/include/sys/time.h" 3 4
struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };

typedef struct timezone *__restrict __timezone_ptr_t;
# 73 "/usr/include/sys/time.h" 3 4
extern int gettimeofday (struct timeval *__restrict __tv,
    __timezone_ptr_t __tz) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int settimeofday (__const struct timeval *__tv,
    __const struct timezone *__tz)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int adjtime (__const struct timeval *__delta,
      struct timeval *__olddelta) __attribute__ ((__nothrow__));




enum __itimer_which
  {

    ITIMER_REAL = 0,


    ITIMER_VIRTUAL = 1,



    ITIMER_PROF = 2

  };



struct itimerval
  {

    struct timeval it_interval;

    struct timeval it_value;
  };






typedef int __itimer_which_t;




extern int getitimer (__itimer_which_t __which,
        struct itimerval *__value) __attribute__ ((__nothrow__));




extern int setitimer (__itimer_which_t __which,
        __const struct itimerval *__restrict __new,
        struct itimerval *__restrict __old) __attribute__ ((__nothrow__));




extern int utimes (__const char *__file, __const struct timeval __tvp[2])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int lutimes (__const char *__file, __const struct timeval __tvp[2])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int futimes (int __fd, __const struct timeval __tvp[2]) __attribute__ ((__nothrow__));
# 191 "/usr/include/sys/time.h" 3 4

# 120 "/usr/include/X11/Xos.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 30 "/usr/include/time.h" 3 4








# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.6.2/include/stddef.h" 1 3 4
# 39 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/time.h" 1 3 4
# 43 "/usr/include/time.h" 2 3 4
# 131 "/usr/include/time.h" 3 4


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  __const char *tm_zone;




};








struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };


struct sigevent;
# 180 "/usr/include/time.h" 3 4



extern clock_t clock (void) __attribute__ ((__nothrow__));


extern time_t time (time_t *__timer) __attribute__ ((__nothrow__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__));





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   __const char *__restrict __format,
   __const struct tm *__restrict __tp) __attribute__ ((__nothrow__));

# 217 "/usr/include/time.h" 3 4
extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     __const char *__restrict __format,
     __const struct tm *__restrict __tp,
     __locale_t __loc) __attribute__ ((__nothrow__));
# 230 "/usr/include/time.h" 3 4



extern struct tm *gmtime (__const time_t *__timer) __attribute__ ((__nothrow__));



extern struct tm *localtime (__const time_t *__timer) __attribute__ ((__nothrow__));





extern struct tm *gmtime_r (__const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__));



extern struct tm *localtime_r (__const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__));





extern char *asctime (__const struct tm *__tp) __attribute__ ((__nothrow__));


extern char *ctime (__const time_t *__timer) __attribute__ ((__nothrow__));







extern char *asctime_r (__const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__));


extern char *ctime_r (__const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__));




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__));



extern int daylight;
extern long int timezone;





extern int stime (__const time_t *__when) __attribute__ ((__nothrow__));
# 313 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__));


extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__));


extern int dysize (int __year) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
# 328 "/usr/include/time.h" 3 4
extern int nanosleep (__const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__));


extern int clock_settime (clockid_t __clock_id, __const struct timespec *__tp)
     __attribute__ ((__nothrow__));






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       __const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__));


extern int timer_settime (timer_t __timerid, int __flags,
     __const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__));


extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__));
# 417 "/usr/include/time.h" 3 4

# 121 "/usr/include/X11/Xos.h" 2 3 4
# 146 "/usr/include/X11/Xos.h" 3 4
# 1 "/usr/include/X11/Xarch.h" 1 3 4
# 147 "/usr/include/X11/Xos.h" 2 3 4
# 122 "std_defs.h" 2
# 39 "basetype.h" 2


typedef int Basetype;

typedef struct
{
    Basetype width,
        height;
} Size;


typedef struct
{
    Basetype left_x,
        top_y,
        right_x,
        bottom_y;
} TWRectangle;


typedef enum
{
    Top, Bottom, Left, Right,
    Top_Left, Top_Right, Bottom_Left, Bottom_Right,
    NoSide
} Side;


typedef struct
{
    Basetype x, y;
} TWPoint;
# 31 "manage.c" 2

# 1 "userglobD.h" 1
# 34 "userglobD.h"
# 1 "uservalsP.h" 1
# 30 "uservalsP.h"
typedef enum
{
        Icon_None,
        Icon_Top, Icon_Bottom,
        Icon_Left, Icon_Right,
        Icon_Middle
} Icon_Position;


typedef enum {

    ABS_MIN_WIDTH,
    ABS_MIN_HEIGHT,

    RTL_LEFT_X,
    RTL_TOP_Y,

    FULL_WIDTH,
    FULL_HEIGHT,

    RTL_WIDTH,
    RTL_HEIGHT,

    ICON_AREA_TOP,
    ICON_AREA_BOTTOM,
    ICON_AREA_LEFT,
    ICON_AREA_RIGHT,

    BORDER_SIZE,
    OUTER_BORDER_LINEWIDTH,
    INNER_BORDER_LINEWIDTH,

    GADGET_WIDTH,

    GRAVITY,

    ICON_PLACEMENT,
    SECONDARY_ICON_PLACEMENT,

    NEIGHBORHOOD_SHRINK_FACTOR,

    LENGTH_USER_GLOBAL_VALUES
} User_Global_Values;
# 35 "userglobD.h" 2
# 1 "useroptsP.h" 1
# 29 "useroptsP.h"
typedef enum {

    ACCEPT_NON_LISTENER_IN_BODY,
    ACCEPT_NON_LISTENER_IN_BORDER,
    ACCEPT_NON_LISTENER_IN_GADGET,
    ACCEPT_NON_LISTENER_IN_HEADER,

    ALLOW_AGGRESSIVE_REPOPULATION,

    ALLOW_AUTO_SHRINK_ON_AUTO_REPOP,
    ALLOW_AUTO_SHRINK_ON_EXPL_REPOP,

    ALLOW_AUTO_SHRINK_ON_EXCHANGE,
    ALLOW_AUTO_CLOSE_ON_EXCHANGE,

    ALLOW_AUTOMATIC_SHRINK_BY_CLIENT,
    ALLOW_AUTOMATIC_CLOSE_BY_CLIENT,

    ALLOW_LISTENER_TO_CLOSE,
    ALLOW_LSNR_TO_CHANGE_BY_CLIENT,
    ALLOW_LSNR_TO_CLOSE_BY_CLIENT,

    ALLOW_SHRINK_ON_AUTO_OPEN,
    ALLOW_SHRINK_ON_CENTER_OPEN,
    ALLOW_SHRINK_ON_CORNER_OPEN,
    ALLOW_SHRINK_ON_RESIZE,

    AUTO_DESIRED_ENLARGE,

    AUTO_PLACE_ON_ICON_OPEN,
    AUTO_PLACE_ON_MENU_OPEN,
    AUTO_PLACE_ON_UNSIZED_OPEN,

    AUTO_PRORATE,
    AUTO_PRORATE_LOCALLY,

    AUTO_REPOPULATE_LAST,
    AUTO_REPOPULATE_ON_AUTO_UNZOOM,
    AUTO_REPOPULATE_ON_CLOSE,
    AUTO_REPOP_ON_DESKTOP_RESIZE,
    AUTO_REPOP_ON_EXPLICIT_UNZOOM,

    BIASED_AUTO_PRORATE,
    BIASED_EXPLICIT_PRORATE,

    BUTTON_MAKES_LISTENER_IN_BODY,
    BUTTON_MAKES_LISTENER_IN_HEADER,

    CENTER_CURSOR_ON_MOVE,
    CENTER_CURSOR_ON_RELOCATE,

    CLEAR_BODY_ON_REDRAW,

    CLOSE_IN_HEADER,
    CLOSE_IN_CORNER_BORDER,
    CLOSE_IN_SIDE_BORDER,
    CLOSE_IN_MOVE_GADGET,
    CLOSE_IN_ZOOM_GADGET,

    DESIRE_IN_HEADER,
    DESIRE_IN_CORNER_BORDER,
    DESIRE_IN_SIDE_BORDER,
    DESIRE_IN_MOVE_GADGET,
    DESIRE_IN_ZOOM_GADGET,

    DISTINGUISH_CORNER_BORDERS,
    DISTNGSH_CORNER_BORDERS_BY_INV,

    DRAW_X_ON_MOVE,
    DRAW_X_ON_OPEN,
    DRAW_X_ON_RESIZE,

    ENABLE_AUTO_REPOP_DURING_LAYOUT,
    ENABLE_AUTO_SIZING_DURING_LAYOUT,

    ENLARGE_IN_HEADER,
    ENLARGE_IN_CORNER_BORDER,
    ENLARGE_IN_SIDE_BORDER,
    ENLARGE_IN_MOVE_GADGET,
    ENLARGE_IN_ZOOM_GADGET,

    EXCHANGE_IN_HEADER,
    EXCHANGE_IN_ICON,
    EXCHANGE_IN_CORNER_BORDER,
    EXCHANGE_IN_SIDE_BORDER,
    EXCHANGE_IN_MOVE_GADGET,
    EXCHANGE_IN_ZOOM_GADGET,

    FULL_SCREEN,

    INCL_BGRND_MENU_IN_WINDOW_MENU,

    KEY_MAKES_LISTENER_IN_BODY,
    KEY_MAKES_LISTENER_IN_BORDER,
    KEY_MAKES_LISTENER_IN_GADGET,
    KEY_MAKES_LISTENER_IN_HEADER,

    FOCUS_FOLLOWS_CURSOR,

    MANAGER_MENU_IN_BODY,
    MANAGER_MENU_IN_CORNER_BORDER,
    MANAGER_MENU_IN_HEADER,
    MANAGER_MENU_IN_ICON,
    MANAGER_MENU_IN_SIDE_BORDER,
    MANAGER_MENU_IN_MOVE_GADGET,
    MANAGER_MENU_IN_ZOOM_GADGET,

    MIDDLE_MENU,

    MOVE_CURSOR_ON_CLIENT_OPEN,
    MOVE_CURSOR_ON_MANUAL_OPEN,
    MOVE_CURSOR_TO_ICON_ON_CLOSE,

    MOVE_IN_HEADER,
    MOVE_IN_ICON,
    MOVE_IN_CORNER_BORDER,
    MOVE_IN_SIDE_BORDER,
    MOVE_IN_MOVE_GADGET,
    MOVE_IN_ZOOM_GADGET,

    ONLY_REPOP_SINCE_ON_AUTO_UNZOOM,
    ONLY_REPOPULATE_SINCE_ON_CLOSE,
    ONLY_REPOP_SINCE_ON_EXPL_UNZOOM,

    PLACE_CSR_IN_BODY_NOT_BORDER,
    PLACE_CSR_IN_BODY_NOT_GADGET,

    PLACE_CSR_IN_BORDER_AFTER_RESIZE,

    PLACE_CSR_GDGT_AFT_CL_AUTO_OPEN,
    PLACE_CSR_GDGT_AFT_US_AUTO_OPEN,
    PLACE_CSR_IN_GADGET_AFT_MAN_OPEN,

    PLACE_CSR_IN_GADGET_AFT_EXCHANGE,
    PLACE_CSR_IN_GADGET_AFT_MOVE,

    PLACE_CSR_IN_ICON_AFTER_CLOSE,

    PLACE_CSR_BACK_AFTER_MENU_OP,
    PLACE_CSR_BACK_ON_CANCEL,

    PREFER_CL_TO_SHR_ON_AUTO_OPEN,
    PREFER_CL_TO_SHR_ON_CENTER_OPEN,
    PREFER_CL_TO_SHR_ON_CORNER_OPEN,
    PREFER_CL_TO_SHR_ON_EXCHANGE,
    PREFER_CL_TO_SHR_ON_RESIZE,

    PREFER_EXC_LOC_ON_ICONIZING,
    PREFER_EXCHANGED_LOC_ON_OPENING,

    PREFER_PREV_POS_ON_AUTO_REPOP,
    PREFER_PREV_POS_ON_EXPL_REPOP,

    PF_CTR_NBR_2_AUTO_CL_ON_OPEN,
    PF_CTR_NBR_2_AUTO_SHR_ON_OPEN,
    PF_CTR_NBR_2_SHRINK_ON_OPEN,
    PF_EDGE_NBR_2_AUTO_CL_ON_OPEN,
    PF_EDGE_NBR_2_AUTO_SHR_ON_OPEN,
    PF_EDGE_NBR_2_SHRINK_ON_OPEN,

    PF_DTOP_2_AUTO_CL_ON_AUTO_OPEN,
    PF_DTOP_2_AUTO_SHR_ON_AUTO_OPEN,
    PF_DTOP_2_SHRINK_ON_AUTO_OPEN,

    PREF_SLD_TO_AUTO_CL_ON_RESIZE,
    PREF_SLD_TO_AUTO_SHR_ON_RESIZE,
    PREF_SLD_TO_SHRINK_ON_RESIZE,
    PF_CTR_NBR_2_AUTO_CL_ON_RESIZE,
    PF_CTR_NBR_2_AUTO_SHR_ON_RESIZE,
    PF_CTR_NBR_2_SHRINK_ON_RESIZE,
    PF_EDGE_NBR_2_AUTO_CL_ON_RESIZE,
    PF_EDGE_NBR_2_AUTO_SHR_ON_RESIZE,
    PF_EDGE_NBR_2_SHRINK_ON_RESIZE,

    PREFER_UNZOOM_TO_CLOSE,

    PRORATE_LOCALLY,

    REDRAW_IN_HEADER,
    REDRAW_IN_ICON,
    REDRAW_IN_CORNER_BORDER,
    REDRAW_IN_SIDE_BORDER,
    REDRAW_IN_MOVE_GADGET,
    REDRAW_IN_ZOOM_GADGET,

    RELOCATE_IN_HEADER,
    RELOCATE_IN_CORNER_BORDER,
    RELOCATE_IN_SIDE_BORDER,
    RELOCATE_IN_MOVE_GADGET,
    RELOCATE_IN_ZOOM_GADGET,

    REPOPULATE_STRICTLY,
    REPOPULATE_AUTO_CLOSED_ONLY,

    REQUIRE_PREV_POS_ON_AUTO_REPOP,
    REQUIRE_PREV_POS_ON_EXPL_REPOP,

    RESET_MAX_ON_INCREASE,
    RESET_MAX_ON_SHRINK,

    RESET_MIN_ON_DECREASE,
    RESET_MIN_ON_ENLARGE,
    RESET_MIN_MAX_ON_UNSZD_MAN_OPEN,
    RESET_TIED_ZOOMED_MIN_ON_ENLARGE,

    RESET_ZOOM_MIN,
    RESET_ZOOM_MIN_ALLOWS_DECREASE,
    RESET_ZOOM_MIN_USES_DESIRE,

    RESIZE_IN_HEADER,
    RESIZE_IN_CORNER_BORDER,
    RESIZE_IN_SIDE_BORDER,
    RESIZE_IN_MOVE_GADGET,
    RESIZE_IN_ZOOM_GADGET,

    SHOW_LISTENER_IN_BORDERS,
    SHOW_LISTENER_IN_HEADER,
    SHOW_FOCUS_IN_BORDERS,
    SHOW_FOCUS_IN_HEADER,

    TREAT_MOVE_LIKE_RELOCATE,

    TRY_CTR_NBRHD_ON_EXCHANGE,

    TRY_CTR_NBRHD_ON_OPEN,
    TRY_EDGE_NEIGHBORHOOD_ON_OPEN,

    TRY_SLIDING_ON_RESIZE,
    TRY_CTR_NBRHD_ON_RESIZE,
    TRY_EDGE_NEIGHBORHOOD_ON_RESIZE,

    TRY_REPOP_AGAIN_AFT_AUTO_PRORATE,

    UNZOOM_TIED_LSNR_IF_NECESSARY,

    USE_CORNER_BORDERS,

    USE_ICON_AREA,
    USE_ICONS,
    USE_RTL_ICON,

    USER_MENU_IN_BODY,
    USER_MENU_IN_HEADER,
    USER_MENU_IN_SIDE_BORDER,
    USER_MENU_IN_CORNER_BORDER,
    USER_MENU_IN_ICON,
    USER_MENU_IN_MOVE_GADGET,
    USER_MENU_IN_ZOOM_GADGET,

    ZOOM_IN_HEADER,
    ZOOM_IN_CORNER_BORDER,
    ZOOM_IN_SIDE_BORDER,
    ZOOM_IN_MOVE_GADGET,
    ZOOM_IN_ZOOM_GADGET,

    ZOOM_ON_CREATE,

    LENGTH_USER_GLOBAL_OPTIONS
} User_Global_Options;
# 36 "userglobD.h" 2
# 1 "exploptsP.h" 1
# 29 "exploptsP.h"
typedef enum {

    EXPLICIT_AUTO_PRORATE,
    EXPLICIT_ALLOW_AUTOMATIC_CLOSE,

    LENGTH_EXPLICIT_GLOBAL_OPTIONS
} Explicit_Global_Options;
# 37 "userglobD.h" 2



extern bool user_global_options[];
# 50 "userglobD.h"
extern int user_global_values[];
# 65 "userglobD.h"
extern bool explicit[];
# 33 "manage.c" 2
# 1 "twin.h" 1
# 30 "twin.h"
# 1 "twinP.h" 1
# 39 "twinP.h"
# 1 "twinoptsP.h" 1
# 30 "twinoptsP.h"
typedef enum
{
        EXPENSIVE_TO_REDRAW,
 FIXED_COMPLETELY,
 FIXED_BOTTOM_EDGE,
 FIXED_TOP_EDGE,
 FIXED_LEFT_EDGE,
 FIXED_RIGHT_EDGE,
 FIXED_SIZE,
        FIXED_HEIGHT,
        FIXED_WIDTH,
 REQUIRE_MANUAL_CLOSE,
        SHRINK_BASED_ON_CURRENT_SIZE,
        WEIGHTED_SHRINK,
 LENGTH_WINDOW_OPTIONS
} Window_Options;
# 40 "twinP.h" 2

typedef long TimeStamp;
typedef int Priority;

typedef pointer Tilwinp;
# 31 "twin.h" 2


# 1 "state.h" 1
# 30 "state.h"
# 1 "stateP.h" 1
# 34 "stateP.h"
# 1 "twinI.h" 1
# 36 "twinI.h"
typedef struct str_window Tilwin;



struct str_window
{
 pointer id;
        pointer data;


 TWRectangle rect,
   prev_rect,
   modify_rect;

 Size min_size,
   max_size,
   size,

   modify_size,
   open_size,
   prev_size,

                        desired_size;

 Side modify_side;

 TWPoint center,
   prev_center;

        TWPoint position;

 bool options[ (int) LENGTH_WINDOW_OPTIONS ];

 bool Am_I_Open;
 bool prev_Am_I_Open;

 bool Was_Auto_Closed;

 long affect_stamp;
 long modify_stamp;

 long timestamp,
   prev_timestamp;

 long open_priority;
 long size_priority;

 pointer tilep;

 Tilwin *openp;
 Tilwin *closedp;

 Tilwin *justp;


 Tilwin *potentmp;
 Tilwin *potentcp;

        long height_stamp;
        long width_stamp;

};
# 35 "stateP.h" 2


typedef struct
{
    Tilwin *winp;
    int offset;
} WinpHandle;
# 31 "state.h" 2


extern int State_Transaction_Depth();

extern void State_Set_Window_Timestamp();


extern void State_Note_Use();


extern bool State_Was_Just_Modified();


extern void State_Act_Modified();


extern void State_Insert_Just_Modified();


extern void State_Start_Operation();

extern void State_Start_Transaction();
extern void State_Commit_Transaction();
extern void State_Abort_Transaction();
extern void State_Continue_Transaction();

extern void State_Create();


extern void State_Destroy();


extern void State_Manual_Close();


extern void State_Auto_Close();


extern void State_Open();


extern TimeStamp State_Get_Timestamp();

extern WinpHandle State_Gen_Open_Windows();

extern WinpHandle State_Gen_Closed_Windows();

extern WinpHandle State_Gen_Just_Opened_Windows();

extern WinpHandle State_Gen_Just_Modified_Windows();

extern WinpHandle State_Gen_Just_Closed_Windows();

extern void State_Next_Window();


extern void State_Undo();






extern void State_Potential_Clear();
extern WinpHandle State_Gen_Potentially_Modfd();
extern WinpHandle State_Gen_Potentially_Closed();
extern void State_Insert_Potentially_Modfd();
extern void State_Insert_Potentially_Closed();
extern void State_Remove_Potentially_Modfd();
extern void State_Remove_Potentially_Closed();
extern void State_Flip_Just_Lists();
extern bool State_Currently_Transacting();
extern void State_Swap();
# 34 "twin.h" 2



extern Size desktop_size;
extern TWRectangle desktop_rect;
extern TWPoint desktop_center;

extern Size absolute_mins;
extern int gravity;
# 53 "twin.h"
extern void Tilwin_Set_Desktop_Size();





extern Tilwinp Tilwin_Create_Window();

extern void Tilwin_Destroy_Window();


extern Tilwinp Tilwin_Locate();




extern bool Tilwin_Check_Center_Open();




extern bool Tilwin_Check_Corner_Open();







extern bool Tilwin_Check_Resize();
# 91 "twin.h"
extern bool Tilwin_Open();




extern void Tilwin_Close();


extern void Tilwin_Auto_Close();




extern bool Tilwin_Set();




extern bool Tilwin_Set_Size();





extern bool Tilwin_Is_Satisfied();




extern bool Tilwin_Resize();




extern bool Tilwin_Enlarge_Nearest();




extern bool Tilwin_Enlarge_Farthest();






extern void Tilwin_Enlarge_Nearest_In_Area();





extern void Tilwin_Enlarge_Farthest_In_Area();







extern bool Tilwin_Open_Nearest_In_Area();





extern bool Tilwin_Open_Farthest_In_Area();





extern bool Tilwin_Open_Best_In_Area();






extern void Tilwin_Prorate();



extern void Tilwin_Gen_Open_Windows();

extern void Tilwin_Gen_Closed_Windows();

extern void Tilwin_Gen_Just_Opened_Windows();

extern void Tilwin_Gen_Just_Modified_Windows();

extern void Tilwin_Gen_Just_Closed_Windows();

extern Tilwinp Tilwin_Next_Window();

extern void Tilwin_Modify_Covered_Windows();

extern bool Tilwin_Is_Covered();



extern void Tilwin_Undo();
extern void Tilwin_Abort_Transaction();
# 241 "twin.h"
extern bool Tilwin_Slide_Nearest();
extern bool Tilwin_Slide_Farthest();
extern bool Tilwin_Slide_Nearest_In_Area();
extern bool Tilwin_Slide_Farthest_In_Area();

extern void Tilwin_Slide_Horizly_Farthest();
extern void Tilwin_Slide_Vertly_Farthest();
extern void Tilwin_Slide_Horizly_Nearest();
extern void Tilwin_Slide_Vertly_Nearest();

extern Tilwinp Tilwin_Thread_Nearest();
extern Tilwinp Tilwin_Thread_Farthest();
extern Tilwinp Tilwin_Reverse_Thread();

extern Tilwinp Tilwin_Thread_Nearest_Position();

extern Tilwinp Tilwin_Thread_Vertly_Nearest();
extern Tilwinp Tilwin_Thread_Horizly_Nearest();
extern Tilwinp Tilwin_Thread_Vertly_Farthest();
extern Tilwinp Tilwin_Thread_Horizly_Farthest();



extern TWPoint Tilwin_Center_Of_Gravity();
extern TWPoint Tilwin_Position_Ctr_Of_Gravity();

extern Size Tilwin_Good_Size();
extern Size Tilwin_Checked_Size();
extern Size Tilwin_Checked_Previous_Size();
extern Size Tilwin_Checked_Min_Size();
extern Size Tilwin_Checked_Desired_Size();
extern Size Tilwin_Checked_Good_Desired_Size();
extern Size Tilwin_Checked_Max_Size();
extern Size Tilwin_Checked_Good_Max_Size();



extern Tilwinp Tilwin_Get_Latest_Height();
extern Tilwinp Tilwin_Get_Latest_Width();
# 34 "manage.c" 2


# 1 "twinD.h" 1
# 38 "twinD.h"
# 1 "tileoptsP.h" 1
# 30 "tileoptsP.h"
typedef enum {

    ADJUST_PLACEMENT_FAIRLY,
    ALLOW_AUTOMATIC_CLOSE,
    ALLOW_AUTO_CLOSE_MORE_RECENT,
    ALLOW_AUTOMATIC_SHRINK,
    ALLOW_AUTO_SHRINK_MORE_RECENT,
    BEST_FIT_IS_TIGHT,
    BREAK_MINIMUMS_FAIRLY,
    ENABLE_GRAVITY,
    ENFORCE_MAXIMUMS,
    ENFORCE_MINIMUMS,
    FIRST_FIT,
    PREFER_CLOSE_TO_SHRINK,
    PREFER_AUTOMATIC_CLOSE_TO_SEARCH,
    PREFER_AUTO_SHRINK_TO_SEARCH,
    PREFER_SHRINK_TO_SEARCH,
    PRORATE_VERTICALLY_FIRST,

    LENGTH_GLOBAL_OPTIONS
} Global_Options;
# 39 "twinD.h" 2
# 138 "twinD.h"
extern bool globals[];
# 37 "manage.c" 2



# 1 "uwinD.h" 1
# 31 "uwinD.h"
# 1 "uwinP.h" 1
# 35 "uwinP.h"
# 1 "regionP.h" 1
# 39 "regionP.h"
# 1 "bodyregP.h" 1
# 36 "bodyregP.h"
# 1 "listsP.h" 1
# 36 "listsP.h"
typedef struct node Node;

struct node
{
    struct node *prev, *next;
    pointer info;
    int id;

};




typedef struct {
                Node *head, *tail;
               }
          List;
# 37 "bodyregP.h" 2



# 1 "tilemenuP.h" 1
# 33 "tilemenuP.h"
typedef pointer TileMenu;
typedef pointer TileMenuItem;
# 41 "bodyregP.h" 2



# 1 "tilecrsrP.h" 1
# 33 "tilecrsrP.h"
typedef long TileCursor;
# 45 "bodyregP.h" 2


typedef struct {
               TileMenu menu;
               TileCursor cursor;
               } MenuAndCurs;


typedef struct bodyregion {
                 int regionid;
                 int menucursor_regionid;

                 struct bodyregion *menucursor_bodyregion;
   TWRectangle *rect;
                 TileMenu menu;
   TileCursor cursor;
                 char *regionname;
   } *BodyRegion;
# 40 "regionP.h" 2


typedef enum
{
    background,
    body, header,
    zoom_gadget, move_gadget,
    edge, corner,
    icon,
    rtl
} Region_Enum;

typedef union
{
    Side side;
    BodyRegion bodyregion;
} Region_Info;

typedef struct
{
    Region_Enum region_enum;
    Region_Info region_info;
} TWRegion;
# 36 "uwinP.h" 2






# 1 "uwinoptP.h" 1
# 29 "uwinoptP.h"
typedef enum {

    ACCEPT_BUTTON_IN_BODY,
    ACCEPT_BUTTON_IN_HEADER,
    ACCEPT_BUTTON_IN_ICON,

    ACCEPT_KEY_IN_BODY,
    ACCEPT_KEY_IN_HEADER,
    ACCEPT_KEY_IN_GADGET,
    ACCEPT_KEY_IN_BORDER,
    ACCEPT_KEY_IN_ICON,

    AGGRESSIVELY_REPOPULATE,

    ALLOW_SHRINK_ON_UNZOOM,
    ALLOW_SHRINK_ON_AUTO_UNZOOM,

    ALLOW_ZOOM_CLOSE,

    AUTO_OPEN_ON_CREATE,
    AUTO_OPEN_ON_WRITE,

    AUTO_PLACE_ON_CLIENT_OPEN,

    AUTO_RESATISFY_ON_RESET_MINMAX,

    CLIENT_DRAWS_ICON,
    CLIENT_PROVIDES_HEADER,

    CONSIDER_FOR_REPOPULATION,

    ENFORCE_CLIENT_MINIMUMS,
    ENFORCE_CLIENT_MAXIMUMS,

    LISTENER_TIED_TO_ZOOM,

    FORCE_SHRINK_ON_UNZOOM,
    FORCE_SHRINK_ON_AUTO_UNZOOM,

    GLASS_CLIENT,

    ICON_DRAWN_BY_CLIENT,

    IGNORE_INITIAL_POSITION_HINTS,
    IGNORE_INITIAL_SIZE_HINTS,
    IGNORE_POSITION_HINTS,
    IGNORE_SIZE_HINTS,

    INCLUDE_RES_CLASS_IN_TITLE,
    INCLUDE_RES_CLASS_IN_ICON_TITLE,
    INCLUDE_RES_NAME_IN_TITLE,
    INCLUDE_RES_NAME_IN_ICON_TITLE,
    INCLUDE_NAME_IN_TITLE,
    INCLUDE_NAME_IN_ICON_TITLE,
    INCLUDE_HOST_IN_TITLE,
    INCLUDE_HOST_IN_ICON_TITLE,

    INCLUDE_TITLE_IN_HEADER,
    INCLUDE_TITLE_IN_PIXMAP_ICON,
    INCLUDE_TITLE_IN_CLIENT_ICON,

    INVERT_ICON_WHEN_PENDING,

    NOTE_LISTENER,
    NOTE_LISTENER_INPUT,
    NOTE_CLOSED_INPUT,
    NOTE_OPEN_INPUT,
    NOTE_CLOSED_OUTPUT,
    NOTE_OPEN_OUTPUT,

    PREFER_PREVIOUS_ICON_POSITION,
    PREFER_PREV_POS,
    REQUIRE_PREVIOUS_ICON_POSITION,
    REQUIRE_PREV_POS,

    SAVE_IN_LAYOUT,

    SHOW_ICON,

    USE_BORDERS,
    USE_GADGETS,
    USE_HEADER,
    USE_MOVE_GADGET,

    ZOOM_FULL_EXPLICIT,
    ZOOM_FULL_HEIGHT,
    ZOOM_FULL_WIDTH,

    ZOOM_ON_OPEN,

    ZOOM_TIED_TO_DESIRE,

    LENGTH_USER_WINDOW_OPTIONS
 } User_Window_Options;
# 43 "uwinP.h" 2
# 1 "explwoptsP.h" 1
# 31 "explwoptsP.h"
typedef enum {

    EXPLICIT_LISTENER_TIED_TO_ZOOM,
    EXPLICIT_FIXED_COMPLETELY,
    EXPLICIT_FIXED_HEIGHT,
    EXPLICIT_FIXED_WIDTH,
    EXPLICIT_REQUIRE_MANUAL_CLOSE,
    EXPLICIT_ZOOM_TIED_TO_DESIRE,

    LENGTH_EXPLICIT_WINDOW_OPTIONS
 } Explicit_Window_Options;
# 44 "uwinP.h" 2

# 1 "platformP.h" 1
# 31 "platformP.h"
# 1 "/usr/include/X11/X.h" 1 3 4
# 66 "/usr/include/X11/X.h" 3 4
typedef unsigned long XID;



typedef unsigned long Mask;



typedef unsigned long Atom;

typedef unsigned long VisualID;
typedef unsigned long Time;
# 96 "/usr/include/X11/X.h" 3 4
typedef XID Window;
typedef XID Drawable;


typedef XID Font;

typedef XID Pixmap;
typedef XID Cursor;
typedef XID Colormap;
typedef XID GContext;
typedef XID KeySym;

typedef unsigned char KeyCode;
# 32 "platformP.h" 2


typedef struct
{
    Window parent;
    Window top_border;
    Window left_border;
    Window right_border;
    Window bottom_border;
    Window top_left;
    Window top_right;
    Window bottom_left;
    Window bottom_right;
    Window header;
    Window zoom_gadget;
    Window move_gadget;
    Window client;
    Window icon;
    Window client_icon;
    Window transient_for;
} XFrame;
# 46 "uwinP.h" 2

typedef struct str_userwin Userwin;



struct str_userwin {

    Tilwinp winp;
    Tilwinp iconp;

    Region_Enum current_type;

    int winnum;
    pointer data;

    char *hostname;
    char *res_class;
    char *res_name;
    char *wmname;
    char *iconname;
    char *command;
    char *identity;
    char *title;

    bool options[(int)LENGTH_USER_WINDOW_OPTIONS];
    bool explicit[(int)LENGTH_EXPLICIT_WINDOW_OPTIONS];

    bool prepared;
    bool layout;
    bool layout_found;
    bool positioned;
    bool ever_opened;
    bool sized;
    bool listener;
    bool regular_manual_close;

    bool icon_positioned;

    bool focus;
    int client_state;
    int wm_state;
    int startup_state;
    int group_state;

    TimeStamp open_stamp;
    TimeStamp zoom_stamp;
    bool zoomed;
    TWRectangle rezoom_rect;
    Size regular_min;
    Size regular_size;
    Size zoom_min;
    Size zoom_size;

    bool prev_positioned;
    bool prev_sized;
    bool prev_zoomed;
    int prev_group_state;
    TWRectangle prev_rezoom_rect;
    Size prev_min;
    Size prev_max;
    Size prev_desire;
    TimeStamp undo_stamp;

    Size body_min;
    Size body_max;

    Size client_min;
    Size client_max;

    int header_height;

    bool input_enabled;
    bool output_sent;
    bool saving_state;
    bool soft_kill;

    int connection;
    Userwin *group;
    long messages;

    TWRectangle icon_res_rect;
    TWRectangle icon_host_rect;
    TWRectangle icon_name_rect;
    TWRectangle icon_body_rect;

    bool initially_mapped;
    bool initially_icon_mapped;


    int border_width; Pixmap iconmask; Pixmap iconpix; Pixmap iconpix_pending; bool ignore_unmap; XFrame xframe;

};
# 32 "uwinD.h" 2
# 42 "uwinD.h"
# 1 "twin.h" 1
# 33 "twin.h"
# 1 "state.h" 1
# 33 "state.h"
extern int State_Transaction_Depth();

extern void State_Set_Window_Timestamp();


extern void State_Note_Use();


extern bool State_Was_Just_Modified();


extern void State_Act_Modified();


extern void State_Insert_Just_Modified();


extern void State_Start_Operation();

extern void State_Start_Transaction();
extern void State_Commit_Transaction();
extern void State_Abort_Transaction();
extern void State_Continue_Transaction();

extern void State_Create();


extern void State_Destroy();


extern void State_Manual_Close();


extern void State_Auto_Close();


extern void State_Open();


extern TimeStamp State_Get_Timestamp();

extern WinpHandle State_Gen_Open_Windows();

extern WinpHandle State_Gen_Closed_Windows();

extern WinpHandle State_Gen_Just_Opened_Windows();

extern WinpHandle State_Gen_Just_Modified_Windows();

extern WinpHandle State_Gen_Just_Closed_Windows();

extern void State_Next_Window();


extern void State_Undo();






extern void State_Potential_Clear();
extern WinpHandle State_Gen_Potentially_Modfd();
extern WinpHandle State_Gen_Potentially_Closed();
extern void State_Insert_Potentially_Modfd();
extern void State_Insert_Potentially_Closed();
extern void State_Remove_Potentially_Modfd();
extern void State_Remove_Potentially_Closed();
extern void State_Flip_Just_Lists();
extern bool State_Currently_Transacting();
extern void State_Swap();
# 34 "twin.h" 2



extern Size desktop_size;
extern TWRectangle desktop_rect;
extern TWPoint desktop_center;

extern Size absolute_mins;
extern int gravity;
# 53 "twin.h"
extern void Tilwin_Set_Desktop_Size();





extern Tilwinp Tilwin_Create_Window();

extern void Tilwin_Destroy_Window();


extern Tilwinp Tilwin_Locate();




extern bool Tilwin_Check_Center_Open();




extern bool Tilwin_Check_Corner_Open();







extern bool Tilwin_Check_Resize();
# 91 "twin.h"
extern bool Tilwin_Open();




extern void Tilwin_Close();


extern void Tilwin_Auto_Close();




extern bool Tilwin_Set();




extern bool Tilwin_Set_Size();





extern bool Tilwin_Is_Satisfied();




extern bool Tilwin_Resize();




extern bool Tilwin_Enlarge_Nearest();




extern bool Tilwin_Enlarge_Farthest();






extern void Tilwin_Enlarge_Nearest_In_Area();





extern void Tilwin_Enlarge_Farthest_In_Area();







extern bool Tilwin_Open_Nearest_In_Area();





extern bool Tilwin_Open_Farthest_In_Area();





extern bool Tilwin_Open_Best_In_Area();






extern void Tilwin_Prorate();



extern void Tilwin_Gen_Open_Windows();

extern void Tilwin_Gen_Closed_Windows();

extern void Tilwin_Gen_Just_Opened_Windows();

extern void Tilwin_Gen_Just_Modified_Windows();

extern void Tilwin_Gen_Just_Closed_Windows();

extern Tilwinp Tilwin_Next_Window();

extern void Tilwin_Modify_Covered_Windows();

extern bool Tilwin_Is_Covered();



extern void Tilwin_Undo();
extern void Tilwin_Abort_Transaction();
# 241 "twin.h"
extern bool Tilwin_Slide_Nearest();
extern bool Tilwin_Slide_Farthest();
extern bool Tilwin_Slide_Nearest_In_Area();
extern bool Tilwin_Slide_Farthest_In_Area();

extern void Tilwin_Slide_Horizly_Farthest();
extern void Tilwin_Slide_Vertly_Farthest();
extern void Tilwin_Slide_Horizly_Nearest();
extern void Tilwin_Slide_Vertly_Nearest();

extern Tilwinp Tilwin_Thread_Nearest();
extern Tilwinp Tilwin_Thread_Farthest();
extern Tilwinp Tilwin_Reverse_Thread();

extern Tilwinp Tilwin_Thread_Nearest_Position();

extern Tilwinp Tilwin_Thread_Vertly_Nearest();
extern Tilwinp Tilwin_Thread_Horizly_Nearest();
extern Tilwinp Tilwin_Thread_Vertly_Farthest();
extern Tilwinp Tilwin_Thread_Horizly_Farthest();



extern TWPoint Tilwin_Center_Of_Gravity();
extern TWPoint Tilwin_Position_Ctr_Of_Gravity();

extern Size Tilwin_Good_Size();
extern Size Tilwin_Checked_Size();
extern Size Tilwin_Checked_Previous_Size();
extern Size Tilwin_Checked_Min_Size();
extern Size Tilwin_Checked_Desired_Size();
extern Size Tilwin_Checked_Good_Desired_Size();
extern Size Tilwin_Checked_Max_Size();
extern Size Tilwin_Checked_Good_Max_Size();



extern Tilwinp Tilwin_Get_Latest_Height();
extern Tilwinp Tilwin_Get_Latest_Width();
# 43 "uwinD.h" 2
# 82 "uwinD.h"
extern Size abs_min_siz, abs_max_siz;
# 41 "manage.c" 2


# 1 "uwinL.h" 1
# 44 "manage.c" 2
# 1 "uwinvalP.h" 1
# 29 "uwinvalP.h"
typedef enum {

    HEADER_HEIGHT,

    ICON_WIDTH,
    ICON_HEIGHT,

    ICON_BODY_TOP,
    ICON_BODY_BOTTOM,
    ICON_BODY_LEFT,
    ICON_BODY_RIGHT,

    ICON_RES_TOP,
    ICON_RES_BOTTOM,
    ICON_RES_LEFT,
    ICON_RES_RIGHT,

    ICON_HOST_TOP,
    ICON_HOST_BOTTOM,
    ICON_HOST_LEFT,
    ICON_HOST_RIGHT,

    ICON_NAME_TOP,
    ICON_NAME_BOTTOM,
    ICON_NAME_LEFT,
    ICON_NAME_RIGHT,

    CLIENT_MIN_WIDTH,
    CLIENT_MIN_HEIGHT,
    CLIENT_MAX_WIDTH,
    CLIENT_MAX_HEIGHT,

    NORMAL_DESIRED_WIDTH,
    NORMAL_DESIRED_HEIGHT,
    ZOOM_DESIRED_WIDTH,
    ZOOM_DESIRED_HEIGHT,

    USER_NORMAL_MIN_WIDTH,
    USER_NORMAL_MIN_HEIGHT,
    USER_ZOOM_MIN_WIDTH,
    USER_ZOOM_MIN_HEIGHT,

    USER_MAX_WIDTH,
    USER_MAX_HEIGHT,

    LENGTH_USER_WINDOW_VALUES
} User_Window_Values;
# 45 "manage.c" 2

# 1 "client.h" 1
# 30 "client.h"
extern void Client_Enter();


extern void Client_Send_Mouse();


extern void Client_Send_Button();


extern void Client_Send_Key();


extern void Client_Ignore_Key();
extern void Client_Ignore_Button();

extern void Client_Send_String();




extern void Client_Menu_Button_Number();




extern void Client_Kill();


extern void Client_Redraw();


extern void Client_Window_Create();


extern void Client_Startup();


extern void Client_Take_Focus();


extern void Client_Bang();


extern void Client_Set_State();


extern void Client_Configure_Denied();


extern void Client_Window_Moved();


extern void Client_Delete_Window();


extern void Client_Icon_Notify();
# 47 "manage.c" 2
# 1 "closed.h" 1
# 37 "closed.h"
extern TileMenu Closed_Init();


extern void Closed_Retitle();


extern void Closed_Add();


extern void Closed_Remove();
# 48 "manage.c" 2
# 1 "draw.h" 1
# 30 "draw.h"
# 1 "drawP.h" 1
# 35 "drawP.h"
typedef pointer DrawRegion;
# 31 "draw.h" 2


extern void Draw_Init();

extern void Draw_Create();



extern void Draw_ConfigWin();





extern void Draw_Start();


extern void Draw_Finish();

extern void Draw_Flash();

extern void Draw_Line();


extern void Draw_Horizontal();


extern void Draw_Vertical();


extern void Draw_Xor_Line();


extern void Draw_Xor_Horizontal();


extern void Draw_Xor_Vertical();


extern void Draw_Clear_Rectangle();

extern void Draw_Background_Rectangle();

extern void Draw_Fill_Rectangle();

extern void Draw_Fill_Xor_Rectangle();


extern void Draw_Rectangle();


extern void Draw_Xor_Rectangle();


extern void Draw_Pixrect();


extern int Draw_Open();


extern int Draw_Font_Height();


extern int Draw_Num_Drawables();


extern void Draw_Centered_String();


extern void Draw_Vert_Centered_String();


extern int Draw_Get_Frame_Width();

extern int Draw_Get_Frame_Height();
# 49 "manage.c" 2
# 1 "drawicon.h" 1
# 34 "drawicon.h"
extern void DrawIcon_Init();

extern void DrawIcon_Flash();

extern void DrawIcon_Init_Rtl();


extern void DrawIcon_Initial_Size();


extern void DrawIcon_Create();


extern void DrawIcon_Destroy();


extern void DrawIcon_Close();


extern void DrawIcon_Open();


extern void DrawIcon_Move_Open();


extern void DrawIcon_Move_Close();


extern void DrawIcon_Redraw();


extern void DrawIcon_Draw();


extern void DrawIcon_Retitle();


extern void DrawIcon_Note_Output();


extern void DrawIcon_Good_Move_Box();


extern void DrawIcon_Bad_Move_Box();


extern void DrawIcon_Undo_Move_Box();

extern void DrawIcon_Show_Moving();


extern void DrawIcon_Unshow_Moving();


extern void DrawIcon_Show_Opening();


extern void DrawIcon_Unshow_Opening();
# 50 "manage.c" 2
# 1 "drawwin.h" 1
# 34 "drawwin.h"
extern void Drawwin_Init();

extern void Drawwin_Flash();

extern void Drawwin_Initial_Size();



extern void Drawwin_Start();

extern void Drawwin_Finish();

extern void Drawwin_Create();


extern void Drawwin_Prepare();


extern void Drawwin_Insert();


extern void Drawwin_Withdraw();


extern void Drawwin_Destroy();


extern void Drawwin_Draw_Background();


extern bool Drawwin_Redraw_All();


extern void Drawwin_Unmap();


extern void Drawwin_Close();


extern void Drawwin_Open();


extern void Drawwin_Move_Open();


extern void Drawwin_Move_Close();


extern void Drawwin_Listener_Move_Open();


extern void Drawwin_Listener_Move_Close();


extern void Drawwin_Redraw();


extern void Drawwin_Draw();


extern void Drawwin_Display_Focus();


extern void Drawwin_Display_Wrapping();


extern void Drawwin_Retitle();


extern void Drawwin_Show_Moving();


extern void Drawwin_Unshow_Moving();


extern void Drawwin_Good_Open_Box();


extern void Drawwin_Bad_Open_Box();


extern void Drawwin_Undo_Open_Box();

extern void Drawwin_Edge_Resize();


extern void Drawwin_Undo_Edge_Resize();

extern void Drawwin_Corner_Resize();


extern void Drawwin_Undo_Corner_Resize();

extern void Drawwin_Good_Move_Box();


extern void Drawwin_Bad_Move_Box();


extern void Drawwin_Undo_Move_Box();
# 51 "manage.c" 2
# 1 "layout.h" 1
# 30 "layout.h"
typedef pointer Layoutp;


extern bool Layout_Save();




extern int unmatched_layouts;







extern Layoutp Layout_Find();


extern void Layout_Set_Values();


extern void Layout_Set_Options();


extern char *Layout_Init();

extern void Layout_Read();

extern void Layout_Update();
# 52 "manage.c" 2
# 1 "profile.h" 1
# 30 "profile.h"
extern void Profile_Init();

extern void Profile_Create();


extern void Profile_Prepare();


extern void Profile_Update();


extern void Profile_Layout();


extern bool Profile_Supplies_User_Value();


extern bool Profile_Supplies_User_String();


extern bool Profile_Supplies_Pixmap();
# 53 "manage.c" 2
# 1 "region.h" 1
# 45 "region.h"
extern TWRegion back_region;

extern TWRegion header_region;
extern TWRegion body_region;

extern TWRegion left_region;
extern TWRegion right_region;
extern TWRegion top_region;
extern TWRegion bottom_region;

extern TWRegion top_left_region;
extern TWRegion top_right_region;
extern TWRegion bottom_left_region;
extern TWRegion bottom_right_region;

extern TWRegion zoom_gadget_region;
extern TWRegion move_gadget_region;

extern TWRegion rtl_region;
extern TWRegion icon_region;

extern void Region_Init();

extern Size Region_Minimum_Size();

extern TWPoint Region_Translate();





extern Size Region_Body_Size();


extern Size Region_Icon_Body_Size();


extern TWRectangle Region_Body_Rectangle();


extern TWRectangle Region_Adjust_Rectangle();




extern Size Region_Adjust_Size();




extern Size Region_Unadjust_Size();




extern TWRegion Region_Locate();




extern TWRegion Region_Make_Edge();




extern TWRegion Region_Make_Corner();




extern TWRectangle Region_Header_Rect();



extern TWPoint Region_Get_Header_Pos();




extern TWPoint Region_Gadget_Center();



extern TWPoint Region_Get_Edge_Pos();





extern TWPoint Region_Get_Corner_Pos();




extern TWRegion Region_Nearest_Border();




extern bool Region_Nearby();




extern bool Region_Equal();



extern TileCursor Region_Get_Cursor();



extern TileMenu Region_Get_Menu();
# 54 "manage.c" 2
# 266 "manage.c"
static void Manage_Do_Unzoom(Userwin *uwinp, bool explicit);
static void Manage_Start_Trying();
static void Manage_Finish_Trying(bool result);



TimeStamp last_stamp;

static int winnum = 0;

Userwin *focus = (Userwin *)((void *)0);
Userwin *listener = (Userwin *)((void *)0);
Userwin *sublistener = (Userwin *)((void *)0);
Userwin *switch_listener = (Userwin *)((void *)0);
Userwin *prev_listener = (Userwin *)((void *)0);
Userwin *last_zoom = (Userwin *)((void *)0);
Userwin *touch = (Userwin *)((void *)0);
Userwin *prev_touch = (Userwin *)((void *)0);

Userwin *rtl_uwinp;



void Manage_Init()
{
    Draw_Init();
    Region_Init();
    Drawwin_Init();
    DrawIcon_Init();

    last_stamp = 0;
}



static Userwin *Manage_Init_Window()
{
    Userwin *uwinp;
    uwinp = ( ( (Userwin *) malloc(sizeof(Userwin) * (1)) ) );

    uwinp->prepared = 0;
    uwinp->layout = 0;
    uwinp->layout_found = 0;
    uwinp->output_sent = 0;
    uwinp->ever_opened = 0;
    uwinp->soft_kill = 0;
    uwinp->saving_state = 0;
    uwinp->client_state = -1;
    uwinp->wm_state = -2;
    uwinp->group_state = -3;
    uwinp->current_type = body;

    uwinp->group = (Userwin *)((void *)0);
    uwinp->messages = 0;

    uwinp->hostname = ((void *)0);
    uwinp->res_class = ((void *)0);
    uwinp->res_name = ((void *)0);
    uwinp->wmname = ((void *)0);
    uwinp->iconname = ((void *)0);
    uwinp->command = ((void *)0);
    uwinp->identity = ((void *)0);
    uwinp->title = ((void *)0);

    uwinp->positioned = 0;
    uwinp->sized = 0;

    uwinp->focus = 0;
    uwinp->listener = 0;
    uwinp->zoomed = 0;

    uwinp->icon_positioned = 0;

    uwinp->winp = Tilwin_Create_Window( (pointer)uwinp );
    uwinp->iconp = Tilwin_Create_Window( (pointer)uwinp );

    uwinp->open_stamp = 0;
    uwinp->zoom_stamp = 0;

    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_LEFT_EDGE ] ) = (0);
    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_RIGHT_EDGE ] ) = (0);
    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_TOP_EDGE ] ) = (0);
    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_BOTTOM_EDGE ] ) = (0);

    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_SIZE ] ) = (1);
    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_COMPLETELY ] ) = (0);

    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) EXPENSIVE_TO_REDRAW ] ) = (0);

    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (1);

    Profile_Create( uwinp );

    return uwinp;
}



Userwin *Manage_Create_Window( )
{
    Userwin *uwinp;

    uwinp = Manage_Init_Window();

    uwinp->winnum = ++winnum;

    Drawwin_Create( uwinp );
    DrawIcon_Create( uwinp );

    return uwinp;
}



static void Manage_Untitle( uwinp )
    Userwin *uwinp;
{
    if ( (uwinp->hostname) != ((void *)0) )
        free( uwinp->hostname );
    if ( (uwinp->res_class) != ((void *)0) )
        free( uwinp->res_class );
    if ( (uwinp->res_name) != ((void *)0) )
        free( uwinp->res_name );
    if ( (uwinp->wmname) != ((void *)0) )
        free( uwinp->wmname );
    if ( (uwinp->iconname) != ((void *)0) )
        free( uwinp->iconname );
    if ( (uwinp->command) != ((void *)0) )
        free( uwinp->command );
    if ( (uwinp->identity) != ((void *)0) )
        free( uwinp->identity );
    if ( (uwinp->title) != ((void *)0) )
        free( uwinp->title );
}



static void Manage_Retitle( uwinp )
    Userwin *uwinp;
{
    int strsiz;
    bool has_class, has_name;

    if ( (uwinp->title) != ((void *)0) )
        free( uwinp->title );

    strsiz = 1;

    has_class = (uwinp->res_class != ((void *)0)) &&
        ( (uwinp)->options[(int)(INCLUDE_RES_CLASS_IN_TITLE)] );

    has_name = (uwinp->res_name != ((void *)0)) &&
        ( (uwinp)->options[(int)(INCLUDE_RES_NAME_IN_TITLE)] );

    if ( has_class || has_name )
    {
        strsiz +=1;

        if ( has_class )
            strsiz += strlen(uwinp->res_class);

        if ( has_class && has_name )
            strsiz +=1;

        if ( has_name )
            strsiz += strlen(uwinp->res_name);

        strsiz +=2;
    }

    if ( (uwinp->wmname != ((void *)0)) &&
         ( (uwinp)->options[(int)(INCLUDE_NAME_IN_TITLE)] ) )
        strsiz += strlen(uwinp->wmname);

    if ( (uwinp->hostname != ((void *)0)) &&
         ( (uwinp)->options[(int)(INCLUDE_HOST_IN_TITLE)] ) )
        strsiz += (3 + strlen(uwinp->hostname));

    uwinp->title = ( (char *) malloc(sizeof(char) * (strsiz)) );
    uwinp->title[0] = '\0';

    if ( has_class || has_name )
    {
        (void)strcat( uwinp->title, "[" );

        if ( has_class )
            (void)strcat( uwinp->title, uwinp->res_class );

        if ( has_class && has_name )
            (void)strcat( uwinp->title, ":" );

        if ( has_name )
            (void)strcat( uwinp->title, uwinp->res_name );

        (void)strcat( uwinp->title, "] " );
    }

    if ( (uwinp->wmname != ((void *)0)) &&
         ( (uwinp)->options[(int)(INCLUDE_NAME_IN_TITLE)] ) )
    {
        (void)strcat( uwinp->title, uwinp->wmname );
    }

    if ( (uwinp->hostname != ((void *)0)) &&
         ( (uwinp)->options[(int)(INCLUDE_HOST_IN_TITLE)] ) )
    {
        (void)strcat( uwinp->title, " (" );
        (void)strcat( uwinp->title, uwinp->hostname );
        (void)strcat( uwinp->title, ")" );
    }

    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
        Drawwin_Retitle( uwinp );
    else if ( uwinp->ever_opened )
    {
        Closed_Retitle( uwinp );
        if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
            DrawIcon_Retitle(uwinp);
    }
}



void Manage_Set_Class( uwinp, res_class, res_name )
    Userwin *uwinp;
    char *res_class;
    char *res_name;
{
    if ( ( ( ( (uwinp->res_class) == ((void *)0) ) || ( uwinp->res_class[0] == ((void *)0) ) ) ? ( ( (res_class) == ((void *)0) ) || ( res_class[0] == ((void *)0) ) ) : ( ( (res_class) != ((void *)0) ) && ( strcmp(uwinp->res_class,res_class) == 0 ) ) ) &&
         ( ( ( (uwinp->res_name) == ((void *)0) ) || ( uwinp->res_name[0] == ((void *)0) ) ) ? ( ( (res_name) == ((void *)0) ) || ( res_name[0] == ((void *)0) ) ) : ( ( (res_name) != ((void *)0) ) && ( strcmp(uwinp->res_name,res_name) == 0 ) ) ) )
        return;

    if ( (uwinp->res_class) != ((void *)0) )
        free( uwinp->res_class );

    if ( res_class == ((void *)0) )
        uwinp->res_class = ((void *)0);
    else
    {
        uwinp->res_class =
            ( (char *) malloc(sizeof(char) * (1 + strlen(res_class))) );
        (void)strcpy( uwinp->res_class, res_class );
    }

    if ( (uwinp->res_name) != ((void *)0) )
        free( uwinp->res_name );

    if ( res_name == ((void *)0) )
        uwinp->res_name = ((void *)0);
    else
    {
        uwinp->res_name =
            ( (char *) malloc(sizeof(char) * (1 + strlen(res_name))) );
        (void)strcpy( uwinp->res_name, res_name );
    }

    Profile_Prepare( uwinp );
    uwinp->prepared = 1;

    Manage_Retitle( uwinp );
}



void Manage_Set_Name( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( (uwinp->wmname) != ((void *)0) )
        free( uwinp->wmname );

    uwinp->wmname = ( (char *) malloc(sizeof(char) * (1 + strlen(str))) );
    (void)strcpy( uwinp->wmname, str );

    if ( uwinp->identity == ((void *)0) )
    {
        uwinp->identity = ( (char *) malloc(sizeof(char) * (1 + strlen(str))) );
        (void)strcpy( uwinp->identity, str );
    }

    Manage_Retitle( uwinp );
}



void Manage_Set_Icon_Name( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( (uwinp->iconname) != ((void *)0) )
        free( uwinp->iconname );

    uwinp->iconname = ( (char *) malloc(sizeof(char) * (1 + strlen(str))) );
    (void)strcpy( uwinp->iconname, str );
    Manage_Retitle( uwinp );
}



void Manage_Set_Hostname( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( (uwinp->hostname) != ((void *)0) )
        free( uwinp->hostname );

    uwinp->hostname = ( (char *) malloc(sizeof(char) * (1 + strlen(str))) );
    (void)strcpy( uwinp->hostname, str );
    Manage_Retitle( uwinp );
}



void Manage_Set_Command( uwinp, str )
    Userwin *uwinp;
    char *str;
{
    if ( uwinp->soft_kill )
    {
        extern void Manage_Client_Destroy();
        Manage_Client_Destroy( uwinp );
        return;
    }
    uwinp->saving_state = 0;

    if ( (uwinp->command) != ((void *)0) )
        free( uwinp->command );

    uwinp->command = ( (char *) malloc(sizeof(char) * (1 + strlen(str))) );
    (void)strcpy( uwinp->command, str );
    Manage_Retitle( uwinp );
}



static void Manage_Prepare( uwinp )
    Userwin *uwinp;
{
    if ( (uwinp->res_class == ((void *)0)) && (uwinp->res_name == ((void *)0)) &&
  (uwinp->wmname != ((void *)0)) )
        Manage_Set_Class( uwinp, uwinp->wmname, ((void *)0) );
}



void Manage_Layout( uwinp )
    Userwin *uwinp;
{
    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    Profile_Layout( uwinp );
    uwinp->layout = 1;
}



Userwin *Manage_Locate(pos)
    TWPoint pos;
{
    return ((Userwin *)(( ((Tilwin_Locate(pos)) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(Tilwin_Locate(pos)))->id) )));
}



void Manage_Set_Focus( uwinp )
    Userwin *uwinp;
{
    focus = uwinp;
    if (focus != (Userwin *)((void *)0))
    {
        focus->focus = 1;
        if ( (((Tilwin *)(focus->winp)) -> Am_I_Open) )
            Drawwin_Display_Focus( focus );
    }
}



void Manage_Unset_Focus()
{
    if (focus != (Userwin *)((void *)0))
    {
        focus->focus = 0;
        if ( (((Tilwin *)(focus->winp)) -> Am_I_Open) )
            Drawwin_Display_Focus( focus );
        focus = (Userwin *)((void *)0);
    }
}



void Manage_Switch_Focus( uwinp )
    Userwin *uwinp;
{
    if ( uwinp != focus )
    {
        Manage_Unset_Focus();
        Manage_Set_Focus( uwinp );
    }
}
# 714 "manage.c"
void Manage_Set_Sublistener( uwinp )
    Userwin *uwinp;
{
    sublistener = uwinp;

    if ( ( (sublistener)->options[(int)(NOTE_LISTENER)] ) )
        State_Note_Use(sublistener->winp);

    if (! ( user_global_options[(int)(ALLOW_LISTENER_TO_CLOSE)] ))
    {
        sublistener->regular_manual_close =
            ( ((Tilwin *)(sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] );
        ( ((Tilwin *)(sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (1);
    }
}



void Manage_Unset_Sublistener()
{
    if ( sublistener != (Userwin *)((void *)0) )
    {
        if ( ( listener != (Userwin *)((void *)0) ) &&
             ( (listener)->options[(int)(NOTE_LISTENER)] ) )
            State_Note_Use(listener->winp);

        if (! ( user_global_options[(int)(ALLOW_LISTENER_TO_CLOSE)] ))
            ( ((Tilwin *)(sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (sublistener->regular_manual_close)
                                                   ;

        sublistener = (Userwin *)((void *)0);
    }
}




void Manage_Switch_Sublistener( uwinp )
    Userwin *uwinp;
{
    if ( uwinp != sublistener )
    {
        Manage_Unset_Sublistener();
        if ( uwinp != (Userwin *)((void *)0) )
            Manage_Set_Sublistener( uwinp );
    }
}



static void Manage_Set_Listener( uwinp )
    Userwin *uwinp;
{
    listener = uwinp;

    if ( listener != (Userwin *)((void *)0) )
    {
        Manage_Unset_Sublistener();

        listener->listener = 1;
        State_Act_Modified(listener->winp);

        if ( ( (listener)->options[(int)(NOTE_LISTENER)] ) )
            State_Note_Use(listener->winp);

        if (! ( user_global_options[(int)(ALLOW_LISTENER_TO_CLOSE)] ))
        {
            listener->regular_manual_close =
                ( ((Tilwin *)(listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] );
            ( ((Tilwin *)(listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (1)
                                            ;
        }
    }
}



static void Manage_Unset_Listener()
{
    listener->listener = 0;
    State_Act_Modified(listener->winp);

    if (! ( user_global_options[(int)(ALLOW_LISTENER_TO_CLOSE)] ))
        ( ((Tilwin *)(listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (listener->regular_manual_close)
                                            ;

    listener = (Userwin *)((void *)0);
}



static void Manage_Unset( uwinp )
    Userwin *uwinp;
{
    extern void Manage_Do_Unzoom();

    if ( uwinp == focus )
        Manage_Unset_Focus();

    if ( uwinp == listener )
    {
        if ( ( (listener)->options[(int)(LISTENER_TIED_TO_ZOOM)] ) &&
             listener->zoomed )
            Manage_Do_Unzoom( listener, 0 );
        Manage_Unset_Listener();
    }
    else if ( uwinp == sublistener )
        Manage_Unset_Sublistener();
}



TWRectangle Manage_Neighborhood_Rectangle( nbhd, center, siz )
    float nbhd;
    TWPoint center;
    Size siz;
{
    TWRectangle rect;
    int horiz, vert;
    int dhoriz, dvert;
    int factor;

    factor = ( user_global_values[(int)(NEIGHBORHOOD_SHRINK_FACTOR)] );

    dhoriz = 100 * ( desktop_size ).width;
    dvert = 100 * ( desktop_size ).height;

    horiz = nbhd * siz.width * (dhoriz - (factor*siz.width)) / dhoriz;
    horiz += (siz.width/2);
    rect.left_x = center.x - horiz;
    rect.right_x = center.x + horiz;

    vert = nbhd * siz.height * (dvert - (factor*siz.height)) / dvert;
    vert += (siz.height/2);
    rect.top_y = center.y - vert;
    rect.bottom_y = center.y + vert;

    return rect;
}



static bool Manage_Neighborhood_Icon_Open( uwinp, center )
    Userwin *uwinp;
    TWPoint center;
{
    TWRectangle rect;
    Size siz;
    bool result;

    extern void Manage_Start_Trying();
    extern bool Manage_Can_Try_Listener_Unzoom();
    extern void Manage_Finish_Trying();

    siz = (((Tilwin *)(uwinp->iconp)) -> size);

    Manage_Start_Trying();
    { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && 0)); { result = Tilwin_Open( uwinp->iconp, center, siz ); if ( (! result) && Manage_Can_Try_Listener_Unzoom() ) result = Tilwin_Open( uwinp->iconp, center, siz ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }





    Manage_Finish_Trying( result );

    if ( result ) return 1;

    rect = Manage_Neighborhood_Rectangle( 0.75, center, siz );
    return Tilwin_Open_Nearest_In_Area( uwinp->iconp, rect, center, siz );
}



bool Manage_Icon_Open( uwinp )
    Userwin *uwinp;
{
    TWRectangle desk,iconarea, rect, area, bigger_area;
    TWPoint center;
    Size siz;
    bool first_none = 0;
    bool second_none = 0;
    bool icon_positioned;
    bool result;

    if ( ( uwinp->client_state == 4 ) ||
         ( uwinp->client_state == 5 ) ||
         ( ( (uwinp)->group_state != -3 ) &&
           ( uwinp->group != uwinp ) ) ||
         ( ! ( (uwinp)->options[(int)(SHOW_ICON)] ) ) )
        return 0;

    if ( (uwinp->icon_positioned) &&
         ( (uwinp)->options[(int)(REQUIRE_PREVIOUS_ICON_POSITION)] )
                                              )
    {
        if ( Manage_Neighborhood_Icon_Open( uwinp,
                 (((Tilwin *)(uwinp->iconp)) -> position) ) )
        return 1;
    }

    icon_positioned = (uwinp->icon_positioned) &&
         ( ( (uwinp)->options[(int)(PREFER_PREVIOUS_ICON_POSITION)] )
                                               ||
           ( (uwinp)->options[(int)(REQUIRE_PREVIOUS_ICON_POSITION)] )
                                                );

    siz = (((Tilwin *)(uwinp->iconp)) -> size);

    desk = ( desktop_rect );

    if ( ( user_global_options[(int)(USE_ICON_AREA)] ) )
    {
        iconarea.left_x = ( user_global_values[(int)(ICON_AREA_LEFT)] );
        iconarea.right_x = ( user_global_values[(int)(ICON_AREA_RIGHT)] );
        iconarea.top_y = ( user_global_values[(int)(ICON_AREA_TOP)] );
        iconarea.bottom_y = ( user_global_values[(int)(ICON_AREA_BOTTOM)] );
    }
    else
        iconarea = desk;

    bigger_area = area = rect = iconarea;

    switch ( (Icon_Position)( user_global_values[(int)(SECONDARY_ICON_PLACEMENT)] )
                                           )
    {
        case Icon_Top:
            rect.bottom_y = iconarea.top_y + siz.height - 1;
            break;
        case Icon_Bottom:
            rect.top_y = iconarea.bottom_y - siz.height + 1;
            break;
        case Icon_Left:
            rect.right_x = iconarea.left_x + siz.width - 1;
            break;
        case Icon_Right:
            rect.left_x = iconarea.right_x - siz.width + 1;
            break;
        case Icon_None:
            second_none = 1;
        case Icon_Middle:
        default:
            break;
    }

    switch ( (Icon_Position)( user_global_values[(int)(ICON_PLACEMENT)] ) )
    {
        case Icon_None:
            first_none = 1;
        default:
            break;
        case Icon_Top:
            rect.top_y = iconarea.top_y;
            rect.bottom_y = iconarea.top_y + siz.height - 1;
            area.bottom_y = iconarea.top_y + siz.height - 1;
            bigger_area.bottom_y = iconarea.top_y + (2* siz.height) - 1;
            break;
        case Icon_Bottom:
            rect.bottom_y = iconarea.bottom_y;
            rect.top_y = iconarea.bottom_y - siz.height + 1;
            area.top_y = iconarea.bottom_y - siz.height + 1;
            bigger_area.top_y = iconarea.bottom_y - (2*siz.height) + 1;
            break;
        case Icon_Left:
            rect.left_x = iconarea.left_x;
            rect.right_x = iconarea.left_x + siz.width - 1;
            area.right_x = iconarea.left_x + siz.width - 1;
            bigger_area.right_x = iconarea.left_x + (2*siz.width) - 1;
            break;
        case Icon_Right:
            rect.right_x = iconarea.right_x;
            rect.left_x = iconarea.right_x - siz.width + 1;
            area.left_x = iconarea.right_x - siz.width + 1;
            bigger_area.left_x = iconarea.right_x - (2*siz.width) + 1;
            break;
    }

    { ((center)).x = 1 + (((rect)).left_x + ((rect)).right_x) / 2; ((center)).y = 1 + (((rect)).top_y + ((rect)).bottom_y) / 2; };

    if ( icon_positioned )
    {
        center = (((Tilwin *)(uwinp->iconp)) -> position);
        if ( first_none )
            result = Manage_Neighborhood_Icon_Open( uwinp, center );
        else
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                    area, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                    iconarea, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                    desk, center, siz );

    }
    else if ( first_none )
    {
        result = Tilwin_Open_Best_In_Area( uwinp->iconp,
                iconarea, siz );
        if (! result)
            result = Tilwin_Open_Best_In_Area( uwinp->iconp,
                    desk, siz );
    }

    else if (second_none)
    {
        result = Tilwin_Open_Best_In_Area( uwinp->iconp,
                area, siz );
        if (! result)
            result = Tilwin_Open_Best_In_Area( uwinp->iconp,
                bigger_area, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                iconarea, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                desk, center, siz );
    }
    else
    {
        result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                area, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                bigger_area, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                iconarea, center, siz );
        if (! result)
            result = Tilwin_Open_Nearest_In_Area( uwinp->iconp,
                desk, center, siz );
    }

    if ( result && !uwinp->icon_positioned )
    {
        uwinp->icon_positioned = 1;
        (((Tilwin *)(uwinp->iconp)) -> position = ((((Tilwin *)(uwinp->iconp))->center)))
                                               ;
    }

    return result;
}



void Manage_Update_Icons()
{
    Tilwinp winp;
    Userwin *uwinp;
    bool keep_updating;

    if ( ( user_global_options[(int)(USE_ICONS)] ) )
    {
        Tilwin_Gen_Just_Opened_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( ( uwinp->winp == winp ) && (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
                Tilwin_Close( uwinp->iconp );
        }

        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( ( uwinp->winp == winp ) && (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
                Tilwin_Close( uwinp->iconp );
        }

        keep_updating = 1;
        while ( keep_updating )
        {
            keep_updating = 0;
            Tilwin_Gen_Closed_Windows();
            while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
            {
                uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
                if ( ( uwinp->iconp == winp )
                   && ( ! (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
                   && uwinp->ever_opened )
                    keep_updating |= Manage_Icon_Open( uwinp );
            }
        }
    }
}



static bool drawing = 0;
static bool redrawing = 0;



static void Manage_Update_Desktop()
{
    Tilwinp winp;
    Userwin *uwinp;

    Drawwin_Start();

    Tilwin_Gen_Just_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->current_type == body )
        {
            Manage_Unset( uwinp );
            Drawwin_Close( uwinp,
                (! Tilwin_Is_Covered(
                       (((Tilwin *)(winp)) -> prev_rect) ) ) );
            uwinp->output_sent = 0;
            if ( ( uwinp->client_state != 5 ) &&
                 ( uwinp->client_state != -2 ) )
                Closed_Add( uwinp );
        }
        else
        {
            DrawIcon_Close( uwinp );
        }

        if (! ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ||
                (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) ) )
        {
            if ( uwinp->client_state == 5 )
                uwinp->wm_state = 5;
            else
                uwinp->wm_state = 4;



            if ( uwinp->client_state != -2 )
                Client_Set_State( uwinp );
        }
    }

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( ( ! uwinp->positioned ) &&
             ( uwinp->current_type == body ) )
            (((Tilwin *)(winp)) -> position = ((((Tilwin *)(winp))->center)))
                                           ;
    }

    if ( drawing )
    {
        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( uwinp->current_type == body )
                Drawwin_Draw( uwinp );
            else
                DrawIcon_Draw( uwinp );
        }
    }
    else
    {
        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
            if ( (! ( ( (((Tilwin *)(winp))->rect).left_x == (((Tilwin *)(winp))->prev_rect).left_x ) && ( (((Tilwin *)(winp))->rect).right_x == (((Tilwin *)(winp))->prev_rect).right_x ) && ( (((Tilwin *)(winp))->rect).top_y == (((Tilwin *)(winp))->prev_rect).top_y ) && ( (((Tilwin *)(winp))->rect).bottom_y == (((Tilwin *)(winp))->prev_rect).bottom_y ) ) ) || redrawing )
            {
                uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
                if ( uwinp->current_type != body )
                    DrawIcon_Move_Close( uwinp );
                else if ( uwinp == switch_listener )
                    Drawwin_Listener_Move_Close( uwinp,
                        (! Tilwin_Is_Covered(
                            (((Tilwin *)(winp)) -> prev_rect) ) ) );
                else
                    Drawwin_Move_Close( uwinp,
                        (! Tilwin_Is_Covered(
                            (((Tilwin *)(winp)) -> prev_rect) ) ) );
            }

        Tilwin_Gen_Just_Modified_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( (! ( ( (((Tilwin *)(winp))->rect).left_x == (((Tilwin *)(winp))->prev_rect).left_x ) && ( (((Tilwin *)(winp))->rect).right_x == (((Tilwin *)(winp))->prev_rect).right_x ) && ( (((Tilwin *)(winp))->rect).top_y == (((Tilwin *)(winp))->prev_rect).top_y ) && ( (((Tilwin *)(winp))->rect).bottom_y == (((Tilwin *)(winp))->prev_rect).bottom_y ) ) ) || redrawing )
            {
                if ( uwinp->current_type != body )
                {
                    DrawIcon_Move_Open( uwinp );
                    if ( redrawing )
                        DrawIcon_Redraw( uwinp );
                }
                else if ( uwinp == switch_listener )
                    Drawwin_Listener_Move_Open( uwinp );
                else
                {
                    Drawwin_Move_Open( uwinp );
      if ( redrawing )
                        Drawwin_Retitle( uwinp );
  }
            }
        }

        if ( listener != prev_listener )
        {
            if ( ( listener != (Userwin *)((void *)0) ) &&
                 State_Was_Just_Modified(listener->winp) &&
                 (! (! ( ( (((Tilwin *)(listener->winp))->rect).left_x == (((Tilwin *)(listener->winp))->prev_rect).left_x ) && ( (((Tilwin *)(listener->winp))->rect).right_x == (((Tilwin *)(listener->winp))->prev_rect).right_x ) && ( (((Tilwin *)(listener->winp))->rect).top_y == (((Tilwin *)(listener->winp))->prev_rect).top_y ) && ( (((Tilwin *)(listener->winp))->rect).bottom_y == (((Tilwin *)(listener->winp))->prev_rect).bottom_y ) ) )) &&
                 ( listener->current_type == body ) )
                Drawwin_Display_Wrapping( listener );

            if ( ( prev_listener != (Userwin *)((void *)0) ) &&
                 State_Was_Just_Modified(prev_listener->winp) &&
                 (! (! ( ( (((Tilwin *)(prev_listener->winp))->rect).left_x == (((Tilwin *)(prev_listener->winp))->prev_rect).left_x ) && ( (((Tilwin *)(prev_listener->winp))->rect).right_x == (((Tilwin *)(prev_listener->winp))->prev_rect).right_x ) && ( (((Tilwin *)(prev_listener->winp))->rect).top_y == (((Tilwin *)(prev_listener->winp))->prev_rect).top_y ) && ( (((Tilwin *)(prev_listener->winp))->rect).bottom_y == (((Tilwin *)(prev_listener->winp))->prev_rect).bottom_y ) ) )) &&
                 ( prev_listener->current_type == body ) )
                Drawwin_Display_Wrapping( prev_listener );
        }
        else
        {
            if ( ( touch != (Userwin *)((void *)0) ) &&
                 State_Was_Just_Modified(touch->winp) &&
                 (! (! ( ( (((Tilwin *)(touch->winp))->rect).left_x == (((Tilwin *)(touch->winp))->prev_rect).left_x ) && ( (((Tilwin *)(touch->winp))->rect).right_x == (((Tilwin *)(touch->winp))->prev_rect).right_x ) && ( (((Tilwin *)(touch->winp))->rect).top_y == (((Tilwin *)(touch->winp))->prev_rect).top_y ) && ( (((Tilwin *)(touch->winp))->rect).bottom_y == (((Tilwin *)(touch->winp))->prev_rect).bottom_y ) ) )) &&
                 ( touch->current_type == body ) )
                Drawwin_Display_Wrapping( touch );
        }
    }

    Tilwin_Gen_Just_Opened_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( winp == uwinp->winp )
        {
            uwinp->current_type = body;
            uwinp->sized = 1;
            if ( ! uwinp->positioned )
                (((Tilwin *)(winp)) -> position = ((((Tilwin *)(winp))->center)))
                                               ;
            Drawwin_Open( uwinp );
            Closed_Remove( uwinp );
            uwinp->wm_state = 1;
        }
        else
        {
            if ( uwinp != rtl_uwinp )
                uwinp->current_type = icon;
            DrawIcon_Open( uwinp );
            if ( ( (uwinp)->options[(int)(CLIENT_DRAWS_ICON)] ) )
                uwinp->wm_state = 2;
            else
                uwinp->wm_state = 3;
        }
        if ( uwinp->current_type != rtl )
            Client_Set_State( uwinp );
    }

    if (! drawing )
    {
        Tilwin_Gen_Just_Closed_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( uwinp->winp == winp )
                Drawwin_Unmap( uwinp );
        }
    }

    Drawwin_Finish();

    switch_listener = (Userwin *)((void *)0);
    prev_touch = touch;
    touch = (Userwin *)((void *)0);
}



void Manage_Save_State( uwinp )
    Userwin *uwinp;
{
    uwinp->undo_stamp = State_Get_Timestamp();

    uwinp->prev_positioned = uwinp->positioned;
    uwinp->prev_sized = uwinp->sized;
    uwinp->prev_zoomed = uwinp->zoomed;

    uwinp->prev_group_state = uwinp->group_state;

    uwinp->prev_desire = (((Tilwin *)(uwinp->winp)) -> desired_size);
    uwinp->prev_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    uwinp->prev_max = (((Tilwin *)(uwinp->winp)) -> max_size);

    uwinp->prev_rezoom_rect = uwinp->rezoom_rect;
}



static void Manage_Exchange_State( uwinp )
    Userwin *uwinp;
{
    Size temp_size;

    if ( last_stamp != uwinp->undo_stamp )
        return;

    { bool temp; temp = uwinp->prev_positioned; uwinp->prev_positioned = uwinp->positioned; uwinp->positioned = temp; }
    { bool temp; temp = uwinp->prev_sized; uwinp->prev_sized = uwinp->sized; uwinp->sized = temp; }
    { bool temp; temp = uwinp->prev_zoomed; uwinp->prev_zoomed = uwinp->zoomed; uwinp->zoomed = temp; }

    { int temp; temp = uwinp->prev_group_state; uwinp->prev_group_state = uwinp->group_state; uwinp->group_state = temp; }

    { TWRectangle temp; temp = uwinp->prev_rezoom_rect; uwinp->prev_rezoom_rect = uwinp->rezoom_rect; uwinp->rezoom_rect = temp; }

    temp_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
    { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->prev_desire).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->prev_desire).width ) & (~1); };
    uwinp->prev_desire = temp_size;

    temp_size = (((Tilwin *)(uwinp->winp)) -> min_size);
    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->prev_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->prev_min).width ) & (~1); };
    uwinp->prev_min = temp_size;

    temp_size = (((Tilwin *)(uwinp->winp)) -> max_size);
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (uwinp->prev_max).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (uwinp->prev_max).width ) & (~1); };
    uwinp->prev_max = temp_size;
}



static void Manage_Cant_Undo()
{
    prev_listener = listener;
    State_Start_Transaction();
    State_Commit_Transaction();
    last_stamp = State_Get_Timestamp();
}



void Manage_Start()
{
    if ( State_Transaction_Depth() == 0 )
        prev_listener = listener;
    State_Start_Transaction();
}



static void Manage_Restart()
{
    Tilwin_Abort_Transaction();
    State_Start_Transaction();
}



extern bool Manage_Repopulate_Since();
extern bool Manage_Aggressive_Repopulation();



static bool Manage_Unzoom_Repopulation()
{
    TimeStamp repop_since;
    Tilwinp winp;
    Userwin *uwinp;
    bool result = 0;

    repop_since = last_stamp;

    Tilwin_Gen_Just_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( ( uwinp->current_type == body ) &&
             ( ( uwinp->zoomed ) ||
               ( ( uwinp->undo_stamp == last_stamp ) &&
                 ( uwinp->prev_zoomed ) ) ) )
        {
            if (! ( user_global_options[(int)(ONLY_REPOP_SINCE_ON_AUTO_UNZOOM)] )
                                                       )
                repop_since = (TimeStamp)0;
            else if ( uwinp->zoom_stamp < repop_since )
                repop_since = uwinp->zoom_stamp;
        }
    }

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( ( uwinp->current_type == body ) &&
             (! uwinp->zoomed ) &&
             ( uwinp->undo_stamp == last_stamp ) &&
             ( uwinp->prev_zoomed ) )
        {
            if (! ( user_global_options[(int)(ONLY_REPOP_SINCE_ON_AUTO_UNZOOM)] )
                                                       )
                repop_since = (TimeStamp)0;
            else if ( uwinp->zoom_stamp < repop_since )
                repop_since = uwinp->zoom_stamp;
        }
    }

    if ( repop_since < last_stamp )
    {
        { bool temp_val; temp_val = ( user_global_options[(int)(REQUIRE_PREV_POS_ON_AUTO_REPOP)] ); user_global_options[(int)(REQUIRE_PREV_POS_ON_AUTO_REPOP)] = ((temp_val || 1)); { if ( Manage_Repopulate_Since( repop_since, 0, 0, 1 ) ) result = 1; }; user_global_options[(int)(REQUIRE_PREV_POS_ON_AUTO_REPOP)] = (temp_val); }






        if ( Manage_Repopulate_Since(
                 repop_since, 0, 0, 1 ) )
            result = 1;
    }

    return result;
}



static bool Manage_Finish_Repopulation()
{
    bool result;

    result = 0;

    if ( ( user_global_options[(int)(AUTO_REPOPULATE_LAST)] ) )
        if ( Manage_Repopulate_Since(
            last_stamp, 0, 0, 1 ) )
            result = 1;

    if ( ( user_global_options[(int)(ALLOW_AGGRESSIVE_REPOPULATION)] ) )
        if ( Manage_Aggressive_Repopulation() )
            result = 1;

    if ( ( user_global_options[(int)(AUTO_REPOPULATE_ON_AUTO_UNZOOM)] )
                                             )
        { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (0); { if ( Manage_Unzoom_Repopulation() ) result = 1; }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }






    return result;
}



extern void Manage_Auto_Prorate();
extern void Manage_Ordered_Desire();

void Manage_Finish( result )
    bool result;
{
    extern void Manage_Ordered_Desire();
    bool allow_repop_shrink, can_repop, can_size;

    if ( State_Transaction_Depth() > 1 )
        State_Commit_Transaction();

    else if (! result)
    {
        Tilwin_Abort_Transaction();
        Draw_Flash();
    }

    else
    {
        last_stamp = State_Get_Timestamp();

        allow_repop_shrink =
             ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ) &&
             ( globals[(int)(ALLOW_AUTO_SHRINK_MORE_RECENT)] ) &&
             ( user_global_options[(int)(ALLOW_AUTO_SHRINK_ON_AUTO_REPOP)] )
                                                 ;

        can_repop = ( unmatched_layouts <= 0 ) ||
                     ( user_global_options[(int)(ENABLE_AUTO_REPOP_DURING_LAYOUT)] );

        can_size = ( unmatched_layouts <= 0 ) ||
                    ( user_global_options[(int)(ENABLE_AUTO_SIZING_DURING_LAYOUT)] );

        Manage_Update_Icons();

        if ( allow_repop_shrink && can_size &&
             ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) )
            Manage_Ordered_Desire();

        if ( can_repop && Manage_Finish_Repopulation() )
            Manage_Update_Icons();

        if ( can_size &&
             ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) )
            Manage_Ordered_Desire();

        if ( can_size &&
             ( user_global_options[(int)(AUTO_PRORATE)] ) )
            while ( 1 )
            {
                Manage_Auto_Prorate();

                if ( can_size &&
                     ( user_global_options[(int)(TRY_REPOP_AGAIN_AFT_AUTO_PRORATE)] )
                                                           &&
                     Manage_Finish_Repopulation() )
                    Manage_Update_Icons();
                else
                    break;
            }

        Manage_Update_Desktop();
        State_Commit_Transaction();
    }

}



bool Manage_Finish_Fixed_Completely( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != (Userwin *)((void *)0) ) )
      window_excursion

    else
        Manage_Finish( result );
    return result;
}



bool Manage_Finish_Fixed_Size( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != (Userwin *)((void *)0) ) )
      window_excursion

    else
        Manage_Finish( result );
    return result;
}



bool Manage_Finish_Locked( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != (Userwin *)((void *)0) ) )
      window_excursion

    else
        Manage_Finish( result );
    return result;
}



bool Manage_Finish_Minned( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result && ( uwinp != (Userwin *)((void *)0) ) )
        { Size temp_min; temp_min = (((Tilwin *)(uwinp->winp)) -> min_size); { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ ((((Tilwin *)(uwinp->winp)) -> size)).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ ((((Tilwin *)(uwinp->winp)) -> size)).width ) & (~1); };
          window_excursion
# 1576 "manage.c"
        ; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_min).width ) & (~1); }; }


    else
        Manage_Finish( result );
    return result;
}
# 1595 "manage.c"
static void Manage_Undo_Start()
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Undo();

    Tilwin_Gen_Just_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->winp == winp )
            Manage_Exchange_State( uwinp );
    }

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->winp == winp )
            Manage_Exchange_State( uwinp );
    }

    Tilwin_Gen_Just_Opened_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->winp == winp )
            Manage_Exchange_State( uwinp );
    }

    State_Continue_Transaction();

    if ( listener != prev_listener )
    {
        if ( listener != (Userwin *)((void *)0) )
        {
            listener->listener = 0;
            State_Act_Modified(listener->winp);
        }

        { Userwin *temp; temp = listener; listener = prev_listener; prev_listener = temp; }

        touch = prev_touch;

        if ( listener != (Userwin *)((void *)0) )
        {
            listener->listener = 1;
            State_Act_Modified(listener->winp);
        }
    }

}



void Manage_Undo()
{
    Tilwinp winp;
    Userwin *uwinp;

    Manage_Undo_Start();

    if ( ( user_global_options[(int)(USE_ICONS)] ) )
    {
        Tilwin_Gen_Just_Closed_Windows();
        while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if (! ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ||
                    (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) ) )
                Manage_Icon_Open( uwinp );
        }
    }

    { bool temp_val; temp_val = ( user_global_options[(int)(AUTO_PRORATE)] ); user_global_options[(int)(AUTO_PRORATE)] = (0); { bool temp_val; temp_val = ( user_global_options[(int)(AUTO_REPOPULATE_LAST)] ); user_global_options[(int)(AUTO_REPOPULATE_LAST)] = (0); { bool temp_val; temp_val = ( user_global_options[(int)(ALLOW_AGGRESSIVE_REPOPULATION)] ); user_global_options[(int)(ALLOW_AGGRESSIVE_REPOPULATION)] = (0); Manage_Finish( 1 ); user_global_options[(int)(ALLOW_AGGRESSIVE_REPOPULATION)] = (temp_val); }; user_global_options[(int)(AUTO_REPOPULATE_LAST)] = (temp_val); }; user_global_options[(int)(AUTO_PRORATE)] = (temp_val); }




}



void Manage_Redraw( uwinp )
    Userwin *uwinp;
{
    if ( uwinp->current_type == body )
        Drawwin_Redraw(uwinp);
    else
        DrawIcon_Redraw(uwinp);
}



void Manage_Redraw_All()
{
    Tilwinp winp;

    if ( Drawwin_Redraw_All( ( desktop_rect ) ) )
        return;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
        Manage_Redraw( ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) ))) );
}



void Manage_Finish_Layout()
{
    Manage_Start();
    ( unmatched_layouts = 0 );
    Manage_Finish( 1 );
}



void Manage_Initial_Icon_Open( uwinp )
    Userwin *uwinp;
{
    Manage_Start();
    State_Note_Use(uwinp->winp);
    if ( uwinp->client_state != 5 )
    {
        Closed_Add( uwinp );
        if ( ( user_global_options[(int)(USE_ICONS)] ) )
        {
            if (! uwinp->layout_found )
                Manage_Icon_Open( uwinp );
            else
                { bool temp_val; temp_val = ( globals[(int)(ENABLE_GRAVITY)] ); globals[(int)(ENABLE_GRAVITY)] = (0); { bool temp_val; temp_val = ( (uwinp)->options[(int)(REQUIRE_PREVIOUS_ICON_POSITION)] ); ((uwinp)->options[(int)(REQUIRE_PREVIOUS_ICON_POSITION)]) = (1); Manage_Icon_Open( uwinp ); ((uwinp)->options[(int)(REQUIRE_PREVIOUS_ICON_POSITION)]) = (temp_val); }; globals[(int)(ENABLE_GRAVITY)] = (temp_val); }



        }
    }
    Manage_Finish( 1 );
}



void Manage_Prepare_Open( uwinp )
    Userwin *uwinp;
{
    if (! uwinp->layout)
        Manage_Layout( uwinp );

    (((Tilwin *)(uwinp->winp)) -> position = ((((Tilwin *)(uwinp->winp))->center)))
                                          ;

    (((Tilwin *)(uwinp->iconp)) -> position = ((((Tilwin *)(uwinp->iconp))->center)))
                                           ;

    Drawwin_Insert( uwinp );
}



void Manage_Note_Output( uwinp )
    Userwin *uwinp;
{
    if (! uwinp->layout)
        Manage_Layout( uwinp );

    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
    {
        if ( ( (uwinp)->options[(int)(NOTE_OPEN_OUTPUT)] ) )
            State_Note_Use(uwinp->winp);
    }
    else if ( ( (uwinp)->options[(int)(NOTE_CLOSED_OUTPUT)] ) )
        State_Note_Use(uwinp->winp);

    if (! uwinp->output_sent)
    {
        uwinp->output_sent = 1;
        if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
            DrawIcon_Note_Output( uwinp );
    }
}



void Manage_Note_Input( uwinp )
    Userwin *uwinp;
{
    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
    {
        if ( ( (uwinp)->options[(int)(NOTE_OPEN_INPUT)] ) )
            State_Note_Use(uwinp->winp);
        else if ( ( uwinp == listener ) &&
                  ( (uwinp)->options[(int)(NOTE_LISTENER_INPUT)] ) )
            State_Note_Use(uwinp->winp);
    }
    else if ( ( (uwinp)->options[(int)(NOTE_CLOSED_INPUT)] ) )
        State_Note_Use(uwinp->winp);
}



void Manage_Init_Rtl()
{
    Userwin *uwinp;

    Manage_Start();
    uwinp = Manage_Init_Window();
    rtl_uwinp = uwinp;

    uwinp->winnum = 0;
    uwinp->connection = -1;

    uwinp->client_state = -2;
    uwinp->current_type = rtl;
    uwinp->layout = 1;
    uwinp->layout_found = 1;

    ((uwinp)->options[(int)(SHOW_ICON)]) = (( user_global_options[(int)(USE_RTL_ICON)] ))
                                              ;

    ( ((Tilwin *)(uwinp->iconp)) -> options[ (int) FIXED_SIZE ] ) = (1);

    ((uwinp)->options[(int)(SAVE_IN_LAYOUT)]) = (0);
    ((uwinp)->options[(int)(CONSIDER_FOR_REPOPULATION)]) = (0);

    DrawIcon_Init_Rtl( uwinp );

    if ( ( user_global_options[(int)(USE_ICONS)] ) )
        Manage_Icon_Open( uwinp );

    Manage_Finish( 1 );
}



void Manage_Start_Repaint()
{
    State_Start_Transaction();
}



void Manage_Repaint_Rect( rect )
    TWRectangle rect;
{
    Tilwin_Modify_Covered_Windows( rect );
    Drawwin_Draw_Background( rect );
}



void Manage_Finish_Repaint()
{
    Tilwinp winp;
    State_Commit_Transaction();

    Tilwin_Gen_Just_Modified_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        Manage_Redraw( ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) ))) );
    }

    Manage_Cant_Undo();
}



void Manage_Set_Desktop_Size( desksiz )
    Size desksiz;
{
    Tilwin_Set_Desktop_Size( desksiz );
    Drawwin_Draw_Background( ( desktop_rect ) );
}



static void Manage_Reorganize_Desktop( desksiz )
    Size desksiz;
{
    Tilwinp winp, head, middle, tail;
    Userwin *uwinp;
    TWPoint center;
    TWPoint pos;
    TWRectangle rect;
    Size siz;
    Size old_desksiz;
    TWRectangle old_deskrect, deskrect;

    head = middle = tail = (Tilwinp)((void *)0);

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->current_type != body )
        {
            if ( ( user_global_options[(int)(USE_ICONS)] ) &&
                 ( uwinp != rtl_uwinp ) )
            {
                if ( tail == (Tilwinp)((void *)0) ) tail = winp;
                if ( middle == (Tilwinp)((void *)0) ) middle = winp;
                (((Tilwin *)(winp))->data) = (pointer)(head);
                head = winp;
            }
        }
        else if ( ( ((Tilwin *)(winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) )
        {
            if ( middle == (Tilwinp)((void *)0) )
            {
                if ( tail == (Tilwinp)((void *)0) ) tail = winp;
                (((Tilwin *)(winp))->data) = (pointer)(head);
                head = winp;
                middle = winp;
            }
            else if ( middle == tail )
            {
                (((Tilwin *)(tail))->data) = (pointer)(winp);
                (((Tilwin *)(winp))->data) = (pointer)((Tilwinp)((void *)0));
                tail = winp;
                middle = winp;
            }
            else
            {
                (((Tilwin *)(winp))->data) = (pointer)((((Tilwin *)(middle))->data));
                (((Tilwin *)(middle))->data) = (pointer)(winp);
                middle = winp;
            }
        }
        else
        {
            if ( head == (Tilwinp)((void *)0) )
                head = winp;
            else
                (((Tilwin *)(tail))->data) = (pointer)(winp);
            (((Tilwin *)(winp))->data) = (pointer)((Tilwinp)((void *)0));
            tail = winp;
        }

        Tilwin_Auto_Close( winp );
    }

    old_desksiz = ( desktop_size );
    old_deskrect = ( desktop_rect );
    Tilwin_Set_Desktop_Size( desksiz );
    desksiz = ( desktop_size );
    deskrect = ( desktop_rect );

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));

        if ( uwinp->winp == winp )
            Manage_Retitle( uwinp );

        center = (((Tilwin *)(winp))->center);
        pos = (((Tilwin *)(winp)) -> position);
        rect = (((Tilwin *)(winp)) -> rect);

        siz = (((Tilwin *)(winp)) -> size);

        if ( desksiz.width < old_desksiz.width )
        {
            siz.width = ( siz.width * desksiz.width ) /
                old_desksiz.width;
            center.x = ( center.x * desksiz.width ) /
                old_desksiz.width;
            pos.x = ( pos.x * desksiz.width ) /
                old_desksiz.width;
        }
        else if ( rect.right_x == old_deskrect.right_x )
        {
            center.x += ( desksiz.width - old_desksiz.width );
            pos.x += ( desksiz.width - old_desksiz.width );
        }
        else if ( rect.left_x != 0 )
        {
            center.x = ( center.x * desksiz.width ) /
                old_desksiz.width;
            pos.x = ( pos.x * desksiz.width ) /
                old_desksiz.width;
        }

        if ( desksiz.height < old_desksiz.height )
        {
            siz.height = ( siz.height * desksiz.height ) /
                old_desksiz.height;
            center.y = ( center.y * desksiz.height ) /
                old_desksiz.height;
            pos.y = ( pos.y * desksiz.height ) /
                old_desksiz.height;
        }
        else if ( rect.bottom_y == old_deskrect.bottom_y )
        {
            center.y += ( desksiz.height - old_desksiz.height );
            pos.y += ( desksiz.height - old_desksiz.height );
        }
        else if ( rect.top_y != 0 )
        {
            center.y = ( center.y * desksiz.height ) /
                old_desksiz.height;
            pos.y = ( pos.y * desksiz.height ) /
                old_desksiz.height;
        }

        { if ((siz).width < ((((Tilwin *)(winp)) -> max_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(winp)) -> max_size)).width; if ((siz).height < ((((Tilwin *)(winp)) -> max_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(winp)) -> max_size)).height; }
        { if ((siz).width > ((((Tilwin *)(winp)) -> min_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(winp)) -> min_size)).width; if ((siz).height > ((((Tilwin *)(winp)) -> min_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(winp)) -> min_size)).height; }

        Tilwin_Set( winp, center, siz );
        (((Tilwin *)(winp)) -> position = (pos));
    }

    if ( ( user_global_options[(int)(USE_ICONS)] ) )
        Manage_Icon_Open( rtl_uwinp );

    for ( winp = head; winp != (Tilwinp)((void *)0);
          winp = (Tilwinp)(((Tilwin *)(winp))->data) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->current_type == body )
            Tilwin_Open_Nearest_In_Area( winp, deskrect,
                (((Tilwin *)(winp))->center), (((Tilwin *)(winp)) -> size) );
        else if ( ( user_global_options[(int)(USE_ICONS)] ) )
            Manage_Icon_Open( uwinp );
    }

    if ( ( user_global_options[(int)(AUTO_REPOP_ON_DESKTOP_RESIZE)] ) )
        Manage_Repopulate_Since( (TimeStamp)0, 1, 0, 1 );

}



void Manage_Resize_Desktop( desksiz )
    Size desksiz;
{
    drawing = 1;
    Manage_Start();
    Manage_Reorganize_Desktop( desksiz );
    Drawwin_Draw_Background( ( desktop_rect ) );
    Manage_Finish( 1 );
    drawing = 0;
    Manage_Cant_Undo();
}



void Manage_Profile( filnam )
    char *filnam;
{
    int primary, secondary;
    Userwin *uwinp;
    Tilwinp winp;

    Manage_Start();

    secondary = ( user_global_values[(int)(SECONDARY_ICON_PLACEMENT)] );
    primary = ( user_global_values[(int)(ICON_PLACEMENT)] );

    if (! ( user_global_options[(int)(ALLOW_LISTENER_TO_CLOSE)] ))
    {
        if ( listener != (Userwin *)((void *)0) )
            ( ((Tilwin *)(listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (listener->regular_manual_close)
                                                                      ;
        if ( sublistener != (Userwin *)((void *)0) )
            ( ((Tilwin *)(sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (sublistener->regular_manual_close)
                                                                         ;
    }

    Profile_Update( filnam );

    ((rtl_uwinp)->options[(int)(SHOW_ICON)]) = (( user_global_options[(int)(USE_RTL_ICON)] ))
                                              ;

    Manage_Reorganize_Desktop( ( desktop_size ) );

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->iconp == winp )
        {
            if ( ( secondary !=
                   ( user_global_values[(int)(SECONDARY_ICON_PLACEMENT)] ) ) ||
                 ( primary !=
                   ( user_global_values[(int)(ICON_PLACEMENT)] ) ) )
                (((Tilwin *)(winp)) -> position = ((((Tilwin *)(winp))->center)));
        }
    }

    if (! ( user_global_options[(int)(ALLOW_LISTENER_TO_CLOSE)] ))
    {
        if ( listener != (Userwin *)((void *)0) )
            ( ((Tilwin *)(listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (1)
                                            ;
        if ( sublistener != (Userwin *)((void *)0) )
            ( ((Tilwin *)(sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (1)
                                            ;
    }

    redrawing = 1;
    Manage_Finish( 1 );
    redrawing = 0;
}
# 2137 "manage.c"
static bool Manage_Rezoom( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    bool result;

    { if ( (((Tilwin *)(uwinp->winp)) -> rect).top_y == 0 ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).bottom_y == ( ( desktop_size ).height - 1 ) ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).top_y == uwinp->rezoom_rect.top_y ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).bottom_y == uwinp->rezoom_rect.bottom_y ) window_excursion else { if ( (((Tilwin *)(uwinp->winp)) -> rect).left_x == 0 ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).right_x == ( ( desktop_size ).width - 1 ) ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).left_x == uwinp->rezoom_rect.left_x ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).right_x == uwinp->rezoom_rect.right_x ) window_excursion else result = Tilwin_Set_Size( uwinp->winp, siz ); }; }

                                                            ;
    return result;
}



static bool Manage_Rezoom_In_Area( uwinp, rect, pt, siz )
    Userwin *uwinp;
    TWRectangle rect;
    TWPoint pt;
    Size siz;
{
    bool result;

    { if ( (((Tilwin *)(uwinp->winp)) -> rect).top_y == 0 ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).bottom_y == ( ( desktop_size ).height - 1 ) ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).top_y == uwinp->rezoom_rect.top_y ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).bottom_y == uwinp->rezoom_rect.bottom_y ) window_excursion else { if ( (((Tilwin *)(uwinp->winp)) -> rect).left_x == 0 ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).right_x == ( ( desktop_size ).width - 1 ) ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).left_x == uwinp->rezoom_rect.left_x ) window_excursion else if ( (((Tilwin *)(uwinp->winp)) -> rect).right_x == uwinp->rezoom_rect.right_x ) window_excursion else result = Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, pt, siz ); }; }


                                                ;
    return result;
}



static bool Manage_Neighborhood_Rezoom( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    TWRectangle rect;
    TWPoint pt;
    bool result;

    pt = (((Tilwin *)(uwinp->winp))->center);
    rect = Manage_Neighborhood_Rectangle( 0.5, pt, siz );

    { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (0); { window_excursion }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }





           ;

    if (! result)
        result = Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, pt, siz );

    return result;
}



static bool Manage_Neighborhood_Unzoom_Open( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    TWRectangle rect;
    TWPoint pt;
    bool result;

    pt = (((Tilwin *)(uwinp->winp))->center);
    rect = (((Tilwin *)(uwinp->winp)) -> rect);

    result = Manage_Rezoom_In_Area( uwinp, rect, pt, siz );

    if (! result)
        result = Tilwin_Open_Nearest_In_Area(
            uwinp->winp, rect, pt, siz );

    if ( (! result) &&
         (! ( (uwinp)->options[(int)(REQUIRE_PREV_POS)] )
                                       ) )
        result = Tilwin_Open_Nearest_In_Area(
            uwinp->winp,
            ( desktop_rect ),
            pt, siz );

    return result;
}



static void Manage_Setup_Zoom( uwinp, full )
    Userwin *uwinp;
    bool full;
{
    Size siz;

    Manage_Save_State( uwinp );

    uwinp->zoomed = 1;

    uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    uwinp->regular_size = (((Tilwin *)(uwinp->winp)) -> desired_size);

    if ( full )
    {
        if ( ( (uwinp)->options[(int)(ZOOM_FULL_HEIGHT)] ) )
            uwinp->zoom_size.height = ( desktop_size ).height;
        if ( ( (uwinp)->options[(int)(ZOOM_FULL_WIDTH)] ) )
            uwinp->zoom_size.width = ( desktop_size ).width;
    }

    if ( ( user_global_options[(int)(RESET_ZOOM_MIN)] ) )
    {
        if ( ( user_global_options[(int)(RESET_ZOOM_MIN_USES_DESIRE)] ) )
            { if ((uwinp->regular_size).width < ((((Tilwin *)(uwinp->winp)) -> size)).width) (siz).width = (uwinp->regular_size).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> size)).width; if ((uwinp->regular_size).height < ((((Tilwin *)(uwinp->winp)) -> size)).height) (siz).height = (uwinp->regular_size).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> size)).height; }

        else
            siz = (((Tilwin *)(uwinp->winp)) -> size);

        if ( ( user_global_options[(int)(RESET_ZOOM_MIN_ALLOWS_DECREASE)] ) )
            uwinp->zoom_min = siz;
        else
            { if ((uwinp->zoom_min).width > (siz).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (siz).width; if ((uwinp->zoom_min).height > (siz).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (siz).height; }
    }

    if ( ( (uwinp)->options[(int)(ZOOM_TIED_TO_DESIRE)] ) )
    {
        uwinp->zoom_min = uwinp->zoom_size = uwinp->regular_size;
    }

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
    {
        { if ((uwinp->zoom_min).width > (uwinp->client_min).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->client_min).width; if ((uwinp->zoom_min).height > (uwinp->client_min).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->client_min).height; }

        { if ((uwinp->zoom_size).width > (uwinp->client_min).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->client_min).width; if ((uwinp->zoom_size).height > (uwinp->client_min).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->client_min).height; }

    }

    { if ((uwinp->zoom_min).width > (uwinp->regular_min).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->regular_min).width; if ((uwinp->zoom_min).height > (uwinp->regular_min).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->regular_min).height; }

    { if ((uwinp->zoom_size).width > (uwinp->regular_size).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->regular_size).width; if ((uwinp->zoom_size).height > (uwinp->regular_size).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->regular_size).height; }


    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
    {
        { if ((uwinp->zoom_min).width < (uwinp->client_max).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->client_max).width; if ((uwinp->zoom_min).height < (uwinp->client_max).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->client_max).height; }

        { if ((uwinp->zoom_size).width < (uwinp->client_max).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->client_max).width; if ((uwinp->zoom_size).height < (uwinp->client_max).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->client_max).height; }

    }

    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
    { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };

}



static void Manage_Setup_Unzoom( uwinp )
    Userwin *uwinp;
{
    Manage_Save_State( uwinp );

    uwinp->zoomed = 0;

    uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    uwinp->zoom_size = (((Tilwin *)(uwinp->winp)) -> desired_size);

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
    {
        { if ((uwinp->regular_min).width < (uwinp->client_max).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->client_max).width; if ((uwinp->regular_min).height < (uwinp->client_max).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->client_max).height; }

        { if ((uwinp->regular_size).width < (uwinp->client_max).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->client_max).width; if ((uwinp->regular_size).height < (uwinp->client_max).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->client_max).height; }

    }

    { if ((uwinp->regular_min).width < (uwinp->zoom_min).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->zoom_min).width; if ((uwinp->regular_min).height < (uwinp->zoom_min).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->zoom_min).height; }

    { if ((uwinp->regular_size).width < (uwinp->zoom_size).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->zoom_size).width; if ((uwinp->regular_size).height < (uwinp->zoom_size).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->zoom_size).height; }


    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
    {
        { if ((uwinp->regular_min).width > (uwinp->client_min).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->client_min).width; if ((uwinp->regular_min).height > (uwinp->client_min).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->client_min).height; }

        { if ((uwinp->regular_size).width > (uwinp->client_min).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->client_min).width; if ((uwinp->regular_size).height > (uwinp->client_min).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->client_min).height; }

    }

    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
    { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
}



static Size Manage_Get_Zoom_Size( uwinp )
    Userwin *uwinp;
{
    Size cursiz, siz;

    cursiz = (((Tilwin *)(uwinp->winp)) -> size);

    { if ((uwinp->zoom_size).width > (uwinp->zoom_min).width) (siz).width = (uwinp->zoom_size).width; else (siz).width = (uwinp->zoom_min).width; if ((uwinp->zoom_size).height > (uwinp->zoom_min).height) (siz).height = (uwinp->zoom_size).height; else (siz).height = (uwinp->zoom_min).height; }

    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) &&
         ( siz.width < cursiz.width ) &&
         ( siz.height < cursiz.height ) )
        siz = cursiz;

    return Tilwin_Checked_Size( uwinp->winp, siz );
}



static Size Manage_Get_Unzoom_Open_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    { if ((uwinp->zoom_size).width > (uwinp->regular_min).width) (siz).width = (uwinp->zoom_size).width; else (siz).width = (uwinp->regular_min).width; if ((uwinp->zoom_size).height > (uwinp->regular_min).height) (siz).height = (uwinp->zoom_size).height; else (siz).height = (uwinp->regular_min).height; }

    return Tilwin_Checked_Size( uwinp->winp, siz );
}



static Size Manage_Get_Closed_Unzoom_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    { if ((uwinp->regular_size).width > (uwinp->regular_min).width) (siz).width = (uwinp->regular_size).width; else (siz).width = (uwinp->regular_min).width; if ((uwinp->regular_size).height > (uwinp->regular_min).height) (siz).height = (uwinp->regular_size).height; else (siz).height = (uwinp->regular_min).height; }
    { if ((siz).width < ((((Tilwin *)(uwinp->winp)) -> size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> size)).width; if ((siz).height < ((((Tilwin *)(uwinp->winp)) -> size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> size)).height; }

    return Tilwin_Checked_Size( uwinp->winp, siz );
}



static Size Manage_Get_Open_Unzoom_Size( uwinp )
    Userwin *uwinp;
{
    Size siz;

    { (siz).width = (uwinp->rezoom_rect).right_x - (uwinp->rezoom_rect).left_x + 1; (siz).height = (uwinp->rezoom_rect).bottom_y - (uwinp->rezoom_rect).top_y + 1; };
    { if ((siz).width < (uwinp->regular_size).width) (siz).width = (siz).width; else (siz).width = (uwinp->regular_size).width; if ((siz).height < (uwinp->regular_size).height) (siz).height = (siz).height; else (siz).height = (uwinp->regular_size).height; }
    { if ((siz).width < ((((Tilwin *)(uwinp->winp)) -> size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> size)).width; if ((siz).height < ((((Tilwin *)(uwinp->winp)) -> size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> size)).height; }
    { if ((siz).width > (uwinp->regular_min).width) (siz).width = (siz).width; else (siz).width = (uwinp->regular_min).width; if ((siz).height > (uwinp->regular_min).height) (siz).height = (siz).height; else (siz).height = (uwinp->regular_min).height; }

    return Tilwin_Checked_Size( uwinp->winp, siz );
}



static bool Manage_Followup_Zoom( uwinp )
    Userwin *uwinp;
{
    Size siz;
    bool result;

    siz = Manage_Get_Zoom_Size( uwinp );

    if ( ( siz.width < uwinp->zoom_min.width ) ||
         ( siz.height < uwinp->zoom_min.height ) )
        result = 0;
    else
        { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( (uwinp)->options[(int)(ALLOW_ZOOM_CLOSE)] ))); { result = Manage_Neighborhood_Rezoom( uwinp, siz ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }





    if ( result )
    {
        { if ((siz).width > ((((Tilwin *)(uwinp->winp)) -> prev_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> prev_size)).width; if ((siz).height > ((((Tilwin *)(uwinp->winp)) -> prev_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> prev_size)).height; }
                                                               ;

        { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && 0)); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && 0)); Tilwin_Enlarge_Nearest( uwinp->winp, (((Tilwin *)(uwinp->winp)) -> prev_center), siz ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }





        State_Act_Modified(uwinp->winp);
        uwinp->zoom_stamp = State_Get_Timestamp();
        uwinp->rezoom_rect = (((Tilwin *)(uwinp->winp)) -> prev_rect);
    }
    else
        Manage_Setup_Unzoom( uwinp );

    return result;
}



static void Manage_Followup_Unzoom( uwinp, explicit )
    Userwin *uwinp;
    bool explicit;
{
    bool force_repop;
    bool force_shrink;
    bool allow_shrink;
    TimeStamp repop_since;
    TWPoint pt;
    Size siz;

    if (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
        Manage_Rezoom( uwinp, Manage_Get_Closed_Unzoom_Size( uwinp ) );
    else
    {
        State_Act_Modified(uwinp->winp);

        if ( explicit )
        {
            allow_shrink =
                ( (uwinp)->options[(int)(ALLOW_SHRINK_ON_UNZOOM)] );
            force_shrink =
                ( (uwinp)->options[(int)(FORCE_SHRINK_ON_UNZOOM)] );
            force_repop = ( user_global_options[(int)(AUTO_REPOP_ON_EXPLICIT_UNZOOM)] )
                                                             ;
            if ( ( user_global_options[(int)(ONLY_REPOP_SINCE_ON_EXPL_UNZOOM)] )
                                                      )
                repop_since = uwinp->zoom_stamp;
            else
                repop_since = (TimeStamp)0;
        }
        else
        {
            allow_shrink =
                ( (uwinp)->options[(int)(ALLOW_SHRINK_ON_UNZOOM)] ) &&
                ( (uwinp)->options[(int)(ALLOW_SHRINK_ON_AUTO_UNZOOM)] );
            force_shrink =
                ( (uwinp)->options[(int)(FORCE_SHRINK_ON_UNZOOM)] ) &&
                ( (uwinp)->options[(int)(FORCE_SHRINK_ON_AUTO_UNZOOM)] );
            force_repop = ( user_global_options[(int)(AUTO_REPOPULATE_ON_AUTO_UNZOOM)] )
                                                              ;
            if ( ( user_global_options[(int)(ONLY_REPOP_SINCE_ON_AUTO_UNZOOM)] )
                                                      )
                repop_since = uwinp->zoom_stamp;
            else
                repop_since = (TimeStamp)0;
        }

        if ( allow_shrink || force_shrink )
        {
            { ((pt)).x = 1 + (((uwinp->rezoom_rect)).left_x + ((uwinp->rezoom_rect)).right_x) / 2; ((pt)).y = 1 + (((uwinp->rezoom_rect)).top_y + ((uwinp->rezoom_rect)).bottom_y) / 2; };
            siz = Manage_Get_Open_Unzoom_Size( uwinp );
            { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (0); { if ( Tilwin_Set( uwinp->winp, pt, siz ) ) (((Tilwin *)(uwinp->winp)) -> position = (pt)); else Manage_Rezoom( uwinp, siz ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }






        }

        if ( force_repop )
        {
            { bool temp_val; temp_val = ( user_global_options[(int)(REQUIRE_PREV_POS_ON_AUTO_REPOP)] ); user_global_options[(int)(REQUIRE_PREV_POS_ON_AUTO_REPOP)] = (1); Manage_Repopulate_Since( repop_since, 0, 0, 1 ); user_global_options[(int)(REQUIRE_PREV_POS_ON_AUTO_REPOP)] = (temp_val); }

                                                                            ;
        }

        if ( ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) )
     window_excursion;


        if ( allow_shrink && (! force_shrink) )
            { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (0); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (0); { if ( ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) ) Tilwin_Enlarge_Nearest( uwinp->winp, (((Tilwin *)(uwinp->winp)) -> prev_center), (((Tilwin *)(uwinp->winp)) -> prev_size) ); else Tilwin_Open_Nearest_In_Area( uwinp->winp, (((Tilwin *)(uwinp->winp)) -> prev_rect), (((Tilwin *)(uwinp->winp)) -> prev_center), (((Tilwin *)(uwinp->winp)) -> prev_size) ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }
# 2517 "manage.c"
        if ( force_repop )
        {
            Manage_Repopulate_Since( repop_since,
                0, 0, 1 );
        }
    }

    uwinp->rezoom_rect = (((Tilwin *)(uwinp->winp)) -> prev_rect);
}



static bool Manage_Followup_Unzoom_Open( uwinp )
    Userwin *uwinp;
{
    bool result;

    result = Manage_Neighborhood_Unzoom_Open( uwinp,
                 Manage_Get_Unzoom_Open_Size( uwinp ) );
    if ( result )
        uwinp->rezoom_rect = (((Tilwin *)(uwinp->winp)) -> prev_rect);
    else
        Manage_Setup_Zoom( uwinp, 0 );

    return result;
}



static bool Manage_Do_Zoom( uwinp, explicit )
    Userwin *uwinp;
    bool explicit;
{
    bool full;

    full =
        (
            ( ( (uwinp)->options[(int)(ZOOM_FULL_EXPLICIT)] ) &&
              explicit )
        &&
            (
                ( (uwinp)->options[(int)(ZOOM_FULL_WIDTH)] )
            ||
                ( (uwinp)->options[(int)(ZOOM_FULL_HEIGHT)] )
            )
        );

    Manage_Setup_Zoom( uwinp, full );
    return Manage_Followup_Zoom( uwinp );
}



static void Manage_Do_Unzoom( uwinp, explicit )
    Userwin *uwinp;
    bool explicit;
{
    Manage_Setup_Unzoom( uwinp );
    Manage_Followup_Unzoom( uwinp, explicit );
}



static Userwin *unzoomed_listener;



static void Manage_Start_Trying()
{
    unzoomed_listener = (Userwin *)((void *)0);
}



bool Manage_Can_Try_Listener_Unzoom()
{
    if ( ( user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] ) &&
         ( listener != (Userwin *)((void *)0) ) &&
         ( (listener)->options[(int)(LISTENER_TIED_TO_ZOOM)] ) &&
         listener->zoomed )
    {
        Manage_Setup_Unzoom( listener );
        unzoomed_listener = listener;
        return 1;
    }
    else
        return 0;
}



static void Manage_Finish_Trying( result )
    bool result;
{
    if ( unzoomed_listener != (Userwin *)((void *)0) )
    {
        if ( result )
            Manage_Followup_Unzoom( unzoomed_listener, 0 );
        else
            Manage_Setup_Zoom( unzoomed_listener, 0 );
    }
}



bool Manage_Unzoom_Open( uwinp )
    Userwin *uwinp;
{
    bool iconized;
    bool result;

    iconized = (((Tilwin *)(uwinp->iconp)) -> Am_I_Open);
    if ( iconized )
        Tilwin_Close( uwinp->iconp );

    Manage_Setup_Unzoom( uwinp );
    result = Manage_Followup_Unzoom_Open( uwinp );
    if ( (! result) && iconized )
        Tilwin_Open( uwinp->iconp,
                     (((Tilwin *)(uwinp->iconp))->center),
                     (((Tilwin *)(uwinp->iconp)) -> size) );

    return result;
}



void Manage_Zoom( uwinp )
    Userwin *uwinp;
{
    bool result;

    Manage_Start();
    Manage_Start_Trying();
    result = Manage_Do_Zoom( uwinp, 1 );
    if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
        result = Manage_Do_Zoom( uwinp, 1 );
    Manage_Finish_Trying( result );
    ((Tilwin *)(uwinp->winp))->width_stamp = State_Get_Timestamp();
    ((Tilwin *)(uwinp->winp))->height_stamp = State_Get_Timestamp();
    last_zoom = uwinp;
    touch = uwinp;
    Manage_Finish_Minned( uwinp, result );
}



void Manage_Unzoom( uwinp )
    Userwin *uwinp;
{
    if ( ( uwinp == last_zoom ) &&
         ( uwinp->zoom_stamp == last_stamp ) )
        Manage_Undo_Start();
    else
    {
        Manage_Start();
        Manage_Do_Unzoom( uwinp, 1 );
    }
    touch = uwinp;
    Manage_Finish( 1 );
}



void Manage_Toggle_Zoom( uwinp )
    Userwin *uwinp;
{
    if ( uwinp->zoomed )
        Manage_Unzoom( uwinp );
    else
        Manage_Zoom( uwinp );
}



void Manage_Toggle_Zoom_Lock( uwinp )
    Userwin *uwinp;
{
    if ( ( ( (uwinp)->options[(int)(LISTENER_TIED_TO_ZOOM)] ) ) )
    {
        { ((uwinp)->options[(int)(LISTENER_TIED_TO_ZOOM)]) = (0); ((uwinp)->explicit[(int)(EXPLICIT_LISTENER_TIED_TO_ZOOM)]) = 1; };
        Manage_Start();
        State_Act_Modified(uwinp->winp);
        touch = uwinp;
        Manage_Finish( 1 );
    }
    else
    {
        { ((uwinp)->options[(int)(LISTENER_TIED_TO_ZOOM)]) = (1); ((uwinp)->explicit[(int)(EXPLICIT_LISTENER_TIED_TO_ZOOM)]) = 1; };
        if ( ( uwinp == listener ) && (! uwinp->zoomed) )
            Manage_Zoom( uwinp );
        else if ( ( uwinp != listener ) && ( uwinp->zoomed ) )
            Manage_Unzoom( uwinp );
        else
        {
            Manage_Start();
            State_Act_Modified(uwinp->winp);
            touch = uwinp;
            Manage_Finish( 1 );
        }
    }
}



void Manage_Switch_Listener( uwinp )
    Userwin *uwinp;
{
    Userwin *old_listener;
    bool unzoom_old;
    bool zoom_new;
    bool listener_zooming;
    bool transact;
    TimeStamp zoom_stamp = (TimeStamp)0;

    switch_listener = uwinp;

    unzoom_old = (listener != (Userwin *)((void *)0)) && (listener->zoomed) &&
                 ( (listener)->options[(int)(LISTENER_TIED_TO_ZOOM)] );

    zoom_new = (uwinp != (Userwin *)((void *)0)) && (!uwinp->zoomed) &&
               ( (uwinp)->options[(int)(LISTENER_TIED_TO_ZOOM)] );

    listener_zooming = unzoom_old || zoom_new;

    transact = listener_zooming ||
               ( ( user_global_options[(int)(AUTO_PRORATE)] ) &&
                 ( user_global_options[(int)(BIASED_AUTO_PRORATE)] ) );

    old_listener = listener;

    if ( unzoom_old )
        zoom_stamp = listener->zoom_stamp;

    if ( unzoom_old &&
         ( user_global_options[(int)(AUTO_REPOPULATE_ON_AUTO_UNZOOM)] ) &&
         ( listener == last_zoom ) &&
         ( zoom_stamp == last_stamp ) )
    {
        Manage_Undo_Start();
        unzoom_old = 0;
        if ( zoom_new )
            last_zoom = (Userwin *)((void *)0);
    }
    else if ( listener_zooming )
    {
        Manage_Start();
        if (! unzoom_old)
            last_zoom = uwinp;
    }
    else if ( transact )
        Manage_Start();

    if ( listener != (Userwin *)((void *)0) )
    {
        Manage_Unset_Listener();
        if ( unzoom_old )
            Manage_Setup_Unzoom( old_listener );
        else if (! transact)
            Drawwin_Display_Wrapping( old_listener );
    }

    Manage_Set_Listener(uwinp);

    if ( listener != (Userwin *)((void *)0) )
    {
        if ( zoom_new )
        {
            if ( Manage_Do_Zoom( listener, 0 ) &&
                 ( zoom_stamp != (TimeStamp)0 ) )
                listener->zoom_stamp = zoom_stamp;
        }
        else if (! transact)
            Drawwin_Display_Wrapping( listener );
    }

    if ( unzoom_old )
    {
        if ( listener == (Userwin *)((void *)0) )
            Manage_Followup_Unzoom( old_listener, 0 );
        else
            { Size temp_min; temp_min = (((Tilwin *)(listener->winp)) -> min_size); { (((Tilwin *)(listener->winp)) -> min_size).height = (1+ ((((Tilwin *)(listener->winp)) -> size)).height ) & (~1); (((Tilwin *)(listener->winp)) -> min_size).width = (1+ ((((Tilwin *)(listener->winp)) -> size)).width ) & (~1); }; Manage_Followup_Unzoom( old_listener, 0 ); { (((Tilwin *)(listener->winp)) -> min_size).height = (1+ (temp_min).height ) & (~1); (((Tilwin *)(listener->winp)) -> min_size).width = (1+ (temp_min).width ) & (~1); }; }

    }

    if ( transact )
        Manage_Finish_Minned( listener, 1 );
}



static bool Manage_Resatisfy( uwinp )
    Userwin *uwinp;
{
    bool result;
    Size siz;

    Manage_Save_State( uwinp );
    result = Tilwin_Is_Satisfied( uwinp->winp );
    if (! result )
    {
        siz = (((Tilwin *)(uwinp->winp)) -> size);
        { if ((siz).width > ((((Tilwin *)(uwinp->winp)) -> min_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; if ((siz).height > ((((Tilwin *)(uwinp->winp)) -> min_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; }
        { if ((siz).width < ((((Tilwin *)(uwinp->winp)) -> max_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; if ((siz).height < ((((Tilwin *)(uwinp->winp)) -> max_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; }
        if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
            result = Manage_Neighborhood_Rezoom( uwinp, siz );
        else
            result = Manage_Rezoom( uwinp, siz );
    }
    return result;
}



void Manage_Client_Reset_Min_Max( uwinp, min_size, max_size )
    Userwin *uwinp;
    Size min_size;
    Size max_size;
{
    Size siz;
    bool has_min, has_max, result;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    has_max = ( max_size.width > 0 ) && ( max_size.height > 0 );
    has_min = ( min_size.width >= 0 ) && ( min_size.height >= 0 );

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_WIDTH ) )
        max_size.width = uwinp->body_max.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_HEIGHT ) )
        max_size.height = uwinp->body_max.height;

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_WIDTH ) )
        min_size.width = uwinp->body_min.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_HEIGHT ) )
        min_size.height = uwinp->body_min.height;

    if ( has_min )
        { if ((max_size).width > (min_size).width) (max_size).width = (max_size).width; else (max_size).width = (min_size).width; if ((max_size).height > (min_size).height) (max_size).height = (max_size).height; else (max_size).height = (min_size).height; }

    if ( has_max )
    {
        uwinp->body_max = max_size;
        uwinp->client_max = Region_Adjust_Size( uwinp, max_size );
        if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        {
            { if (((((Tilwin *)(uwinp->winp)) -> max_size)).width < (uwinp->client_max).width) (siz).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; else (siz).width = (uwinp->client_max).width; if (((((Tilwin *)(uwinp->winp)) -> max_size)).height < (uwinp->client_max).height) (siz).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; else (siz).height = (uwinp->client_max).height; }

            { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (siz).width ) & (~1); };
            { if ((siz).width < ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((siz).height < ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }
            { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (siz).width ) & (~1); };
        }
    }

    if ( has_min )
    {
        uwinp->body_min = min_size;
        uwinp->client_min = Region_Adjust_Size( uwinp, min_size );
        if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        {
            { if (((((Tilwin *)(uwinp->winp)) -> min_size)).width > (uwinp->client_min).width) (siz).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; else (siz).width = (uwinp->client_min).width; if (((((Tilwin *)(uwinp->winp)) -> min_size)).height > (uwinp->client_min).height) (siz).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; else (siz).height = (uwinp->client_min).height; }

            { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (siz).width ) & (~1); };
            { if ((siz).width > ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((siz).height > ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }
            { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (siz).width ) & (~1); };
        }
    }

    if ( ( ( ((((Tilwin *)(uwinp->winp)) -> min_size)).width == ((((Tilwin *)(uwinp->winp)) -> max_size)).width ) && ( ((((Tilwin *)(uwinp->winp)) -> min_size)).height == ((((Tilwin *)(uwinp->winp)) -> max_size)).height ) )
                                                  )
        uwinp->sized = 1;

    if (! uwinp->ever_opened)
        return;

    if (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open))
        Manage_Resatisfy( uwinp );
    else if ( ( (uwinp)->options[(int)(AUTO_RESATISFY_ON_RESET_MINMAX)] ) )
    {
        Manage_Start();
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_Resatisfy( uwinp ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_Resatisfy( uwinp ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_Resatisfy( uwinp ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_Resatisfy( uwinp ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }



        Manage_Finish_Minned( uwinp, result );
        Manage_Cant_Undo();
    }
}



static Size Manage_Calc_Size( siz, rect, side, pos )
    Size siz;
    TWRectangle rect;
    Side side;
    TWPoint pos;
{

    switch (side)
    {
        case Top:
        case Top_Left:
        case Top_Right:
            siz.height = 1 + rect.bottom_y - pos.y;
            break;
        case Bottom:
        case Bottom_Left:
        case Bottom_Right:
            siz.height = 1 + pos.y - rect.top_y;
            break;
        default:
            break;
    }

    switch (side)
    {
        case Left:
        case Top_Left:
        case Bottom_Left:
            siz.width = 1 + rect.right_x - pos.x;
            break;
        case Right:
        case Top_Right:
        case Bottom_Right:
            siz.width = 1 + pos.x - rect.left_x;
            break;
        default:
            break;
    }

    return siz;
}



bool Manage_Set_Regular_Min_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = (((Tilwin *)(uwinp->winp)) -> rect);

    Manage_Start();

    if (! uwinp->zoomed)
        uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    uwinp->regular_min =
        Manage_Calc_Size( uwinp->regular_min, rect, side, pos );

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        { if ((uwinp->regular_min).width < (uwinp->client_max).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->client_max).width; if ((uwinp->regular_min).height < (uwinp->client_max).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->client_max).height; }


    { if ((uwinp->regular_min).width < ((((Tilwin *)(uwinp->winp)) -> max_size)).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; if ((uwinp->regular_min).height < ((((Tilwin *)(uwinp->winp)) -> max_size)).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; }


    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        { if ((uwinp->regular_min).width > (uwinp->client_min).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->client_min).width; if ((uwinp->regular_min).height > (uwinp->client_min).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->client_min).height; }


    max_size = (((Tilwin *)(uwinp->winp)) -> max_size);
    if ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) || force )
        { if ((max_size).width > (uwinp->regular_min).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->regular_min).width; if ((max_size).height > (uwinp->regular_min).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->regular_min).height; }
    else
        { if ((uwinp->regular_min).width < (max_size).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (max_size).width; if ((uwinp->regular_min).height < (max_size).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (max_size).height; }
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (max_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (max_size).width ) & (~1); };

    if (! uwinp->zoomed)
    {
        { if ((uwinp->regular_min).width > ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (uwinp->regular_size).width = (uwinp->regular_min).width; else (uwinp->regular_size).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((uwinp->regular_min).height > ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (uwinp->regular_size).height = (uwinp->regular_min).height; else (uwinp->regular_size).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
    }
    else
    {
        { if ((uwinp->regular_size).width > (uwinp->regular_min).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->regular_min).width; if ((uwinp->regular_size).height > (uwinp->regular_min).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->regular_min).height; }

        { if ((uwinp->regular_min).width > ((((Tilwin *)(uwinp->winp)) -> min_size)).width) (uwinp->zoom_min).width = (uwinp->regular_min).width; else (uwinp->zoom_min).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; if ((uwinp->regular_min).height > ((((Tilwin *)(uwinp->winp)) -> min_size)).height) (uwinp->zoom_min).height = (uwinp->regular_min).height; else (uwinp->zoom_min).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; }

        { if ((uwinp->zoom_min).width > ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (uwinp->zoom_size).width = (uwinp->zoom_min).width; else (uwinp->zoom_size).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((uwinp->zoom_min).height > ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (uwinp->zoom_size).height = (uwinp->zoom_min).height; else (uwinp->zoom_size).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
    }

    Manage_Resatisfy( uwinp );

    Manage_Finish( 1 );
    return 1;
}



bool Manage_Set_Zoom_Min_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = (((Tilwin *)(uwinp->winp)) -> rect);

    Manage_Start();

    if ( uwinp->zoomed )
        uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    uwinp->zoom_min =
        Manage_Calc_Size( uwinp->zoom_min, rect, side, pos );

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        { if ((uwinp->zoom_min).width < (uwinp->client_max).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->client_max).width; if ((uwinp->zoom_min).height < (uwinp->client_max).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->client_max).height; }


    { if ((uwinp->regular_min).width < ((((Tilwin *)(uwinp->winp)) -> max_size)).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; if ((uwinp->regular_min).height < ((((Tilwin *)(uwinp->winp)) -> max_size)).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; }


    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        { if ((uwinp->zoom_min).width > (uwinp->client_min).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->client_min).width; if ((uwinp->zoom_min).height > (uwinp->client_min).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->client_min).height; }


    max_size = (((Tilwin *)(uwinp->winp)) -> max_size);
    if ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) || force )
        { if ((max_size).width > (uwinp->zoom_min).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->zoom_min).width; if ((max_size).height > (uwinp->zoom_min).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->zoom_min).height; }
    else
        { if ((uwinp->zoom_min).width < (max_size).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (max_size).width; if ((uwinp->zoom_min).height < (max_size).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (max_size).height; }
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (max_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (max_size).width ) & (~1); };

    if ( uwinp->zoomed )
    {
        { if ((uwinp->zoom_min).width > ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (uwinp->zoom_size).width = (uwinp->zoom_min).width; else (uwinp->zoom_size).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((uwinp->zoom_min).height > ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (uwinp->zoom_size).height = (uwinp->zoom_min).height; else (uwinp->zoom_size).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
    }
    else
    {
        { if ((uwinp->zoom_size).width > (uwinp->zoom_min).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->zoom_min).width; if ((uwinp->zoom_size).height > (uwinp->zoom_min).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->zoom_min).height; }

        { if ((uwinp->zoom_min).width < ((((Tilwin *)(uwinp->winp)) -> min_size)).width) (uwinp->regular_min).width = (uwinp->zoom_min).width; else (uwinp->regular_min).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; if ((uwinp->zoom_min).height < ((((Tilwin *)(uwinp->winp)) -> min_size)).height) (uwinp->regular_min).height = (uwinp->zoom_min).height; else (uwinp->regular_min).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
    }

    Manage_Resatisfy( uwinp );

    Manage_Finish( 1 );
    return 1;
}



bool Manage_Set_Regular_Desired_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = (((Tilwin *)(uwinp->winp)) -> rect);

    Manage_Start();

    if (! uwinp->zoomed )
    {
        uwinp->regular_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
        uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    }
    else
        uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);

    uwinp->regular_size =
        Manage_Calc_Size( uwinp->regular_size, rect, side, pos );

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        { if ((uwinp->regular_size).width < (uwinp->client_max).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->client_max).width; if ((uwinp->regular_size).height < (uwinp->client_max).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->client_max).height; }


    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        { if ((uwinp->regular_size).width > (uwinp->client_min).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->client_min).width; if ((uwinp->regular_size).height > (uwinp->client_min).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->client_min).height; }


    max_size = (((Tilwin *)(uwinp->winp)) -> max_size);
    if ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) || force )
        { if ((max_size).width > (uwinp->regular_size).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->regular_size).width; if ((max_size).height > (uwinp->regular_size).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->regular_size).height; }
    else
        { if ((uwinp->regular_size).width < (max_size).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (max_size).width; if ((uwinp->regular_size).height < (max_size).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (max_size).height; }
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (max_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (max_size).width ) & (~1); };

    if ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) || force )
        { if ((uwinp->regular_min).width < (uwinp->regular_size).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->regular_size).width; if ((uwinp->regular_min).height < (uwinp->regular_size).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->regular_size).height; }

    else
        { if ((uwinp->regular_size).width > (uwinp->regular_min).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->regular_min).width; if ((uwinp->regular_size).height > (uwinp->regular_min).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->regular_min).height; }


    if (! uwinp->zoomed)
    {
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
    }
    else
    {
        { if ((uwinp->regular_size).width > ((((Tilwin *)(uwinp->winp)) -> size)).width) (uwinp->zoom_size).width = (uwinp->regular_size).width; else (uwinp->zoom_size).width = ((((Tilwin *)(uwinp->winp)) -> size)).width; if ((uwinp->regular_size).height > ((((Tilwin *)(uwinp->winp)) -> size)).height) (uwinp->zoom_size).height = (uwinp->regular_size).height; else (uwinp->zoom_size).height = ((((Tilwin *)(uwinp->winp)) -> size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
    }

    Manage_Finish( 1 );
    return 1;
}



bool Manage_Set_Zoom_Desired_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = (((Tilwin *)(uwinp->winp)) -> rect);

    Manage_Start();

    if ( uwinp->zoomed )
    {
        uwinp->zoom_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
        uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    }
    else
        uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);

    uwinp->zoom_size =
        Manage_Calc_Size( uwinp->zoom_size, rect, side, pos );

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        { if ((uwinp->zoom_size).width < (uwinp->client_max).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->client_max).width; if ((uwinp->zoom_size).height < (uwinp->client_max).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->client_max).height; }


    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        { if ((uwinp->zoom_size).width > (uwinp->client_min).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->client_min).width; if ((uwinp->zoom_size).height > (uwinp->client_min).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->client_min).height; }


    max_size = (((Tilwin *)(uwinp->winp)) -> max_size);
    if ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) || force )
        { if ((max_size).width > (uwinp->zoom_size).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->zoom_size).width; if ((max_size).height > (uwinp->zoom_size).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->zoom_size).height; }
    else
        { if ((uwinp->zoom_size).width < (max_size).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (max_size).width; if ((uwinp->zoom_size).height < (max_size).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (max_size).height; }
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (max_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (max_size).width ) & (~1); };

    if ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) || force )
        { if ((uwinp->zoom_min).width < (uwinp->zoom_size).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->zoom_size).width; if ((uwinp->zoom_min).height < (uwinp->zoom_size).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->zoom_size).height; }

    else
        { if ((uwinp->zoom_size).width > (uwinp->zoom_min).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->zoom_min).width; if ((uwinp->zoom_size).height > (uwinp->zoom_min).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->zoom_min).height; }


    if (uwinp->zoomed)
    {
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
    }
    else
    {
        if ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) || force )
        {
            { if ((uwinp->regular_min).width < (uwinp->zoom_size).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->zoom_size).width; if ((uwinp->regular_min).height < (uwinp->zoom_size).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->zoom_size).height; }

            { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
        }
        else
        {
            { if ((uwinp->zoom_size).width > (uwinp->regular_min).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->regular_min).width; if ((uwinp->zoom_size).height > (uwinp->regular_min).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->regular_min).height; }

        }
        { if ((uwinp->zoom_size).width < ((((Tilwin *)(uwinp->winp)) -> size)).width) (uwinp->regular_size).width = (uwinp->zoom_size).width; else (uwinp->regular_size).width = ((((Tilwin *)(uwinp->winp)) -> size)).width; if ((uwinp->zoom_size).height < ((((Tilwin *)(uwinp->winp)) -> size)).height) (uwinp->regular_size).height = (uwinp->zoom_size).height; else (uwinp->regular_size).height = ((((Tilwin *)(uwinp->winp)) -> size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
    }

    Manage_Finish( 1 );
    return 1;
}



bool Manage_Set_Max_Size( uwinp, pos, side, force, ctrl )
    Userwin *uwinp;
    TWPoint pos;
    Side side;
    bool force, ctrl;
{
    Size max_size;
    TWRectangle rect;
    rect = (((Tilwin *)(uwinp->winp)) -> rect);

    Manage_Start();

    max_size = Manage_Calc_Size(
        (((Tilwin *)(uwinp->winp)) -> max_size), rect, side, pos );

    if (uwinp->zoomed)
        uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);
    else
        uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        { if ((max_size).width < (uwinp->client_max).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->client_max).width; if ((max_size).height < (uwinp->client_max).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->client_max).height; }

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        { if ((max_size).width > (uwinp->client_min).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->client_min).width; if ((max_size).height > (uwinp->client_min).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->client_min).height; }

    if ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) || force )
    {
        { if ((uwinp->regular_min).width < (max_size).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (max_size).width; if ((uwinp->regular_min).height < (max_size).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (max_size).height; }

        { if ((uwinp->zoom_min).width < (max_size).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (max_size).width; if ((uwinp->zoom_min).height < (max_size).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (max_size).height; }

    }
    else
    {
        { if ((max_size).width > (uwinp->regular_min).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->regular_min).width; if ((max_size).height > (uwinp->regular_min).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->regular_min).height; }
        { if ((max_size).width > (uwinp->zoom_min).width) (max_size).width = (max_size).width; else (max_size).width = (uwinp->zoom_min).width; if ((max_size).height > (uwinp->zoom_min).height) (max_size).height = (max_size).height; else (max_size).height = (uwinp->zoom_min).height; }
    }
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (max_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (max_size).width ) & (~1); };

    if ( uwinp->zoomed )
    {
        { if ((max_size).width < ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (uwinp->zoom_size).width = (max_size).width; else (uwinp->zoom_size).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((max_size).height < ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (uwinp->zoom_size).height = (max_size).height; else (uwinp->zoom_size).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
        { if ((uwinp->regular_size).width < (max_size).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (max_size).width; if ((uwinp->regular_size).height < (max_size).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (max_size).height; }
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
    }
    else
    {
        { if ((max_size).width < ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (uwinp->regular_size).width = (max_size).width; else (uwinp->regular_size).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((max_size).height < ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (uwinp->regular_size).height = (max_size).height; else (uwinp->regular_size).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }

        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
        { if ((uwinp->zoom_size).width < (max_size).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (max_size).width; if ((uwinp->zoom_size).height < (max_size).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (max_size).height; }
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
    }

    Manage_Resatisfy( uwinp );

    Manage_Finish( 1 );
    return 1;
}



void Manage_Min_Max_Resizing( uwinp, siz1, siz2 )
    Userwin *uwinp;
    Size siz1, siz2;
{
    Size siz;

    { if ((siz1).width < (siz2).width) (siz).width = (siz1).width; else (siz).width = (siz2).width; if ((siz1).height < (siz2).height) (siz).height = (siz1).height; else (siz).height = (siz2).height; }
    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (siz).width ) & (~1); };
    { if ((siz1).width > (siz2).width) (siz).width = (siz1).width; else (siz).width = (siz2).width; if ((siz1).height > (siz2).height) (siz).height = (siz1).height; else (siz).height = (siz2).height; }
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (siz).width ) & (~1); };
}



void Manage_Cancel_Resizing( uwinp )
    Userwin *uwinp;
{
    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->prev_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->prev_min).width ) & (~1); };
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (uwinp->prev_max).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (uwinp->prev_max).width ) & (~1); };
}



void Manage_Finish_Resizing( uwinp, side, force, undesire )
    Userwin *uwinp;
    Side side;
    bool force, undesire;
{
    Size newmin, newmax;
    Size siz, prevsiz, desired;
    bool horiz, vert, enlarge;

    horiz = ( side != NoSide ) && ( side != Top ) && ( side != Bottom );
    vert = ( side != NoSide ) && ( side != Left ) && ( side != Right );

    newmin = uwinp->prev_min;
    newmax = uwinp->prev_max;

    if ( uwinp->sized )
        prevsiz = (((Tilwin *)(uwinp->winp)) -> prev_size);
    else
    {
        prevsiz = newmin;
        if ( ( user_global_options[(int)(RESET_MIN_MAX_ON_UNSZD_MAN_OPEN)] ) )
        {
            force = 1;
            horiz = 1;
            vert = 1;
        }
    }

    siz = (((Tilwin *)(uwinp->winp)) -> size);

    if (! undesire)
    {
        desired = (((Tilwin *)(uwinp->winp)) -> desired_size);

        enlarge = (desired.width > prevsiz.width) ||
                  (desired.height > prevsiz.height);

        if ( horiz )
        {
            if ( desired.width >= prevsiz.width )
            {
                if ( force || ( user_global_options[(int)(RESET_MIN_ON_ENLARGE)] ) ||
                     ( ( user_global_options[(int)(RESET_TIED_ZOOMED_MIN_ON_ENLARGE)] ) &&
                       (uwinp->zoomed) &&
                       ( (uwinp)->options[(int)(LISTENER_TIED_TO_ZOOM)] ) ) )
                    newmin.width = siz.width;
            }
            else
            {
                if ( (! enlarge) &&
                     ( force || ( user_global_options[(int)(RESET_MAX_ON_SHRINK)] ) ) )
                    newmax.width = siz.width;
            }
        }

        if ( vert )
        {
            if ( desired.height >= prevsiz.height )
            {
                if ( force || ( user_global_options[(int)(RESET_MIN_ON_ENLARGE)] ) ||
                     ( ( user_global_options[(int)(RESET_TIED_ZOOMED_MIN_ON_ENLARGE)] )
                                                             &&
                       (uwinp->zoomed) &&
                       ( (uwinp)->options[(int)(LISTENER_TIED_TO_ZOOM)] ) ) )
                    newmin.height = siz.height;
            }
            else
            {
                if ( (! enlarge) &&
                     ( force || ( user_global_options[(int)(RESET_MAX_ON_SHRINK)] ) ) )
                    newmax.height = siz.height;
            }
        }
    }

    if ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) || force )
        { if ((newmin).width < (siz).width) (newmin).width = (newmin).width; else (newmin).width = (siz).width; if ((newmin).height < (siz).height) (newmin).height = (newmin).height; else (newmin).height = (siz).height; }

    if ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) || force )
        { if ((newmax).width > (siz).width) (newmax).width = (newmax).width; else (newmax).width = (siz).width; if ((newmax).height > (siz).height) (newmax).height = (newmax).height; else (newmax).height = (siz).height; }

    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (newmin).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (newmin).width ) & (~1); };
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (newmax).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (newmax).width ) & (~1); };

    { if ((newmax).width < ((((Tilwin *)(uwinp->winp)) -> desired_size)).width) (siz).width = (newmax).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> desired_size)).width; if ((newmax).height < ((((Tilwin *)(uwinp->winp)) -> desired_size)).height) (siz).height = (newmax).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> desired_size)).height; }
    { if ((newmin).width > (siz).width) (siz).width = (newmin).width; else (siz).width = (siz).width; if ((newmin).height > (siz).height) (siz).height = (newmin).height; else (siz).height = (siz).height; }
    { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (siz).width ) & (~1); };

}



static bool Manage_Slide_Resize( uwinp, center, siz, side )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
    Side side;
{
    bool result;
    Size shrinksiz;
    Side shrinkside = NoSide;

    if (! ( user_global_options[(int)(TRY_SLIDING_ON_RESIZE)] ))
        return Tilwin_Resize( uwinp->winp, siz, side );

    { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && (! ( user_global_options[(int)(PREF_SLD_TO_AUTO_CL_ON_RESIZE)] )))); { { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && (! ( user_global_options[(int)(PREF_SLD_TO_AUTO_SHR_ON_RESIZE)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ); ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = ((temp_val || ( user_global_options[(int)(PREF_SLD_TO_SHRINK_ON_RESIZE)] ))); { result = Tilwin_Resize( uwinp->winp, siz, side ); }; ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }
# 3414 "manage.c"
               ;

    if ( result ) return 1;

    shrinksiz = (((Tilwin *)(uwinp->winp)) -> size);

    switch (side)
    {
        case Top:
        case Top_Left:
        case Top_Right:
            if ( siz.height < shrinksiz.height )
            {
                shrinkside = Top;
                shrinksiz.height = siz.height;
            }
            break;
        case Bottom:
        case Bottom_Left:
        case Bottom_Right:
            if ( siz.height < shrinksiz.height )
            {
                shrinkside = Bottom;
                shrinksiz.height = siz.height;
            }
            break;
        default:
            break;
    }

    switch (side)
    {
        case Left:
        case Top_Left:
        case Bottom_Left:
            if ( siz.width < shrinksiz.width )
            {
                shrinkside = Left;
                shrinksiz.width = siz.width;
            }
            break;
        case Right:
        case Top_Right:
        case Bottom_Right:
            if ( siz.width < shrinksiz.width )
            {
                shrinkside = Right;
                shrinksiz.width = siz.width;
            }
            break;
        default:
            break;
    }

    if ( shrinkside != NoSide )
        Tilwin_Resize( uwinp->winp, shrinksiz, shrinkside );

    return Tilwin_Enlarge_Nearest( uwinp->winp, center, siz );
}



static bool Manage_Cntr_Neighborhood_Rsz( uwinp, center, siz, side )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
    Side side;
{
    bool result;
    TWRectangle rect;

    if (! ( user_global_options[(int)(TRY_CTR_NBRHD_ON_RESIZE)] ))
        return Manage_Slide_Resize( uwinp, center, siz, side );

    { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && (! ( user_global_options[(int)(PF_CTR_NBR_2_AUTO_CL_ON_RESIZE)] ) ))); { { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && (! ( user_global_options[(int)(PF_CTR_NBR_2_AUTO_SHR_ON_RESIZE)] ) ))); { { bool temp_val; temp_val = ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ); ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = ((temp_val || ( user_global_options[(int)(PF_CTR_NBR_2_SHRINK_ON_RESIZE)] ))); { result = Manage_Slide_Resize( uwinp, center, siz, side ); }; ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }
# 3499 "manage.c"
               ;

    if ( result ) return 1;

    rect = Manage_Neighborhood_Rectangle( 0.5, center, siz );

    return Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, center, siz );
}



static bool Manage_Edge_Neighborhood_Resize( uwinp, center, siz, side )
    Userwin *uwinp;
    TWPoint center;
    Size siz;
    Side side;
{
    bool result;
    TWRectangle rect;

    if (! ( user_global_options[(int)(TRY_EDGE_NEIGHBORHOOD_ON_RESIZE)] ))
        return Manage_Cntr_Neighborhood_Rsz( uwinp, center, siz, side );

    { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && (! ( user_global_options[(int)(PF_EDGE_NBR_2_AUTO_CL_ON_RESIZE)] ) ))); { { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && (! ( user_global_options[(int)(PF_EDGE_NBR_2_AUTO_SHR_ON_RESIZE)] ) ))); { { bool temp_val; temp_val = ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ); ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = ((temp_val || ( user_global_options[(int)(PF_EDGE_NBR_2_SHRINK_ON_RESIZE)] ))); { result = Manage_Cntr_Neighborhood_Rsz( uwinp, center, siz, side ); }; ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }
# 3532 "manage.c"
               ;

    if ( result ) return 1;

    rect = Manage_Neighborhood_Rectangle( 1.0, center, siz );

    return Tilwin_Open_Nearest_In_Area( uwinp->winp, rect, center, siz );
}



bool Manage_Resize( uwinp, pos, side, force, undesire )
    Userwin *uwinp;
    Side side;
    TWPoint pos;
    bool force, undesire;
{
    Size siz, desired;
    TWPoint center;
    TWRectangle rect;
    bool result;

    siz = (((Tilwin *)(uwinp->winp)) -> size);
    rect = (((Tilwin *)(uwinp->winp)) -> rect);
    siz = Manage_Calc_Size( siz, rect, side, pos );

    if (! ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) || force ))
        { if ((siz).width > (uwinp->prev_min).width) (siz).width = (siz).width; else (siz).width = (uwinp->prev_min).width; if ((siz).height > (uwinp->prev_min).height) (siz).height = (siz).height; else (siz).height = (uwinp->prev_min).height; }
    if (! ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) || force ))
        { if ((siz).width < (uwinp->prev_max).width) (siz).width = (siz).width; else (siz).width = (uwinp->prev_max).width; if ((siz).height < (uwinp->prev_max).height) (siz).height = (siz).height; else (siz).height = (uwinp->prev_max).height; }

    desired = (((Tilwin *)(uwinp->winp)) -> desired_size);

    switch (side)
    {
        case Top:
        case Top_Left:
        case Top_Right:
            rect.top_y = rect.bottom_y - siz.height + 1;
            desired.height = siz.height;
            break;
        case Bottom:
        case Bottom_Left:
        case Bottom_Right:
            rect.bottom_y = rect.top_y + siz.height - 1;
            desired.height = siz.height;
            break;
        default:
            break;
    }

    switch (side)
    {
        case Left:
        case Top_Left:
        case Bottom_Left:
            rect.left_x = rect.right_x - siz.width + 1;
            desired.width = siz.width;
            break;
        case Right:
        case Top_Right:
        case Bottom_Right:
            rect.right_x = rect.left_x + siz.width - 1;
            desired.width = siz.width;
            break;
        default:
            break;
    }

    { ((center)).x = 1 + (((rect)).left_x + ((rect)).right_x) / 2; ((center)).y = 1 + (((rect)).top_y + ((rect)).bottom_y) / 2; };

    switch (side)
    {
        case Top:
        case Bottom:
            center.x = (((Tilwin *)(uwinp->winp)) -> position).x;
            break;
        case Left:
        case Right:
            center.y = (((Tilwin *)(uwinp->winp)) -> position).y;
            break;
        default:
            break;
    }

    Manage_Start();
    Manage_Save_State( uwinp );

    if (! undesire)
    {
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (desired).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (desired).width ) & (~1); };
        if ( ( side != Top ) && ( side != Bottom ) )
            ((Tilwin *)(uwinp->winp))->width_stamp = State_Get_Timestamp();
        if ( ( side != Left ) && ( side != Right ) )
            ((Tilwin *)(uwinp->winp))->height_stamp = State_Get_Timestamp();
        (((Tilwin *)(uwinp->winp)) -> position = (center));
        uwinp->positioned = 1;
    }

    Manage_Min_Max_Resizing( uwinp, siz, (((Tilwin *)(uwinp->winp)) -> size) );

    Manage_Start_Trying();
    { bool temp_val; temp_val = ( globals[(int)(PREFER_CLOSE_TO_SHRINK)] ); globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (( user_global_options[(int)(PREFER_CL_TO_SHR_ON_RESIZE)] )); { { bool temp_val; temp_val = ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ); ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = ((temp_val || ! ( user_global_options[(int)(ALLOW_SHRINK_ON_RESIZE)] ))); { result = ( ( ((((Tilwin *)(uwinp->winp)) -> size)).width == (siz).width ) && ( ((((Tilwin *)(uwinp->winp)) -> size)).height == (siz).height ) ) || ( Manage_Edge_Neighborhood_Resize( uwinp, center, siz, side ) && State_Was_Just_Modified(uwinp->winp) ); if ( (! result) && ( listener != uwinp ) && Manage_Can_Try_Listener_Unzoom() ) result = Manage_Edge_Neighborhood_Resize( uwinp, center, siz, side ) && State_Was_Just_Modified(uwinp->winp); }; ( ((Tilwin *)(uwinp->winp)) -> options[ (int) FIXED_SIZE ] ) = (temp_val); } }; globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (temp_val); }
# 3649 "manage.c"
    Manage_Finish_Trying( result );

    if ( result )
        Manage_Finish_Resizing( uwinp, side, force, undesire );
    else
        Manage_Cancel_Resizing( uwinp );

    { if ( (((Tilwin *)(uwinp->winp)) -> size).height < (((Tilwin *)(uwinp->winp)) -> prev_size).height ) { uwinp->winp; FIXED_HEIGHT; 1; { if ( (((Tilwin *)(uwinp->winp)) -> size).width < (((Tilwin *)(uwinp->winp)) -> prev_size).width ) window_excursion else { Size temp_min; temp_siz; temp_siz = temp_min = (((Tilwin *)(uwinp->winp)) -> min_size); temp_siz.width = (((Tilwin *)(uwinp->winp)) -> size).width; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_siz).width ) & (~1); }; window_excursion; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_min).width ) & (~1); }; } }; } else { Size temp_min, temp_siz; temp_siz = temp_min = (((Tilwin *)(uwinp->winp)) -> min_size); temp_siz.height = (((Tilwin *)(uwinp->winp)) -> size).height; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_siz).width ) & (~1); }; { if ( (((Tilwin *)(uwinp->winp)) -> size).width < (((Tilwin *)(uwinp->winp)) -> prev_size).width ) window_excursion else { Size temp_min, temp_siz; temp_siz = temp_min = (((Tilwin *)(uwinp->winp)) -> min_size); temp_siz.width = (((Tilwin *)(uwinp->winp)) -> size).width; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_siz).width ) & (~1); };

           window_excursion
# 3656 "manage.c"
    ; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_min).width ) & (~1); }; } }; { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (temp_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (temp_min).width ) & (~1); }; } }


                                    ;


    return result;
}



static bool zoom_forced;



void Manage_Start_Open( uwinp, force_zoom )
    Userwin *uwinp;
    bool force_zoom;
{
    Manage_Start();
    Manage_Start_Trying();
    Manage_Save_State( uwinp );

    zoom_forced = 0;
    if (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open))
    {
        if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
            Tilwin_Close( uwinp->iconp );
        if ( ( (uwinp)->options[(int)(ZOOM_ON_OPEN)] ) ||
             ( (! uwinp->ever_opened ) &&
               ( user_global_options[(int)(ZOOM_ON_CREATE)] ) ) )
            force_zoom = 1;
        if ( force_zoom && (! uwinp->zoomed) )
        {
            zoom_forced = 1;
            Manage_Do_Zoom( uwinp, 0 );
        }
    }
}



bool Manage_Can_Try_Self_Unzoom( uwinp )
    Userwin *uwinp;
{
    bool result;
    result = ( user_global_options[(int)(PREFER_UNZOOM_TO_CLOSE)] )
             && (uwinp->zoomed)
             && (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open) );
    if ( result )
    {
        zoom_forced = 0;
        Manage_Do_Unzoom( uwinp, 0 );
    }
    return result;
}



bool Manage_Finish_Unsized_Open( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result )
    {
        uwinp->open_stamp = State_Get_Timestamp();
        uwinp->ever_opened = 1;
    }
    else if ( zoom_forced )
        Manage_Do_Unzoom( uwinp, 0 );
    Manage_Finish_Trying( result );
    return Manage_Finish_Locked( uwinp, result );
}



bool Manage_Finish_Sized_Open( uwinp, result )
    Userwin *uwinp;
    bool result;
{
    if ( result )
    {
        uwinp->open_stamp = State_Get_Timestamp();
        uwinp->ever_opened = 1;
    }
    else if ( zoom_forced )
        Manage_Do_Unzoom( uwinp, 0 );
    Manage_Finish_Trying( result );
    return Manage_Finish_Minned( uwinp, result );
}



bool Manage_Move( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;

    Manage_Start();
    (((Tilwin *)(uwinp->winp)) -> position = (pos));
    uwinp->positioned = 1;
    if ( (! uwinp->ever_opened ) ||
         ( user_global_options[(int)(TREAT_MOVE_LIKE_RELOCATE)] ) )
    {
        uwinp->ever_opened = 1;
        return Manage_Finish_Minned( uwinp,
            Manage_Center_Open( uwinp, pos ) );
    }
    else
    {
        Manage_Start_Trying();
        result = Tilwin_Open( uwinp->winp, pos,
                    (((Tilwin *)(uwinp->winp)) -> size) );
        if ( (! result) && ( listener != uwinp )
             && Manage_Can_Try_Listener_Unzoom() )
            result = Tilwin_Open( uwinp->winp, pos,
                    (((Tilwin *)(uwinp->winp)) -> size) );
        Manage_Finish_Trying( result );
        return Manage_Finish_Fixed_Completely( uwinp, result );
    }
}



bool Manage_Icon_Move( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;

    Manage_Start();
    (((Tilwin *)(uwinp->iconp)) -> position = (pos));
    if ( ( user_global_options[(int)(TREAT_MOVE_LIKE_RELOCATE)] ) )
        result = Manage_Neighborhood_Icon_Open( uwinp, pos );
    else
    {
        Manage_Start_Trying();
        result = Tilwin_Open( uwinp->iconp, pos,
                    (((Tilwin *)(uwinp->iconp)) -> size) );
        if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
            result = Tilwin_Open( uwinp->iconp, pos,
                    (((Tilwin *)(uwinp->iconp)) -> size) );
        Manage_Finish_Trying( result );
    }
    if ( result )
        window_excursion

    else
        Manage_Finish( 0 );
    return result;
}
# 3827 "manage.c"
static void Manage_User_Open_Configure( uwinp, pos, siz,
        pos_act, siz_act )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
    bool pos_act, siz_act;
{
    bool result = 1;

    if ( pos_act && siz_act )
    {
        result = Manage_Center_Neighborhood_Open( uwinp, pos, siz );
    }

    else if ( pos_act )
    {
        result = Manage_Center_Neighborhood_Open( uwinp, pos,
            (((Tilwin *)(uwinp->winp)) -> desired_size) );
    }

    else if ( siz_act )
    {
        result = Manage_Center_Neighborhood_Open( uwinp,
            (((Tilwin *)(uwinp->winp))->center), siz );
    }

    if (! result)
        Draw_Flash();
}



void Manage_Client_Configure( uwinp, flags, top_left, bodsiz, detail )
    Userwin *uwinp;
    unsigned long flags;
    TWPoint top_left;
    Size bodsiz;
    int detail;
{
    TWPoint center;
    Size tempsiz, siz, desired;
    TWRectangle rect;

    Manage_Start();

    rect = Region_Body_Rectangle( uwinp );

    { (tempsiz).width = (rect).right_x - (rect).left_x + 1; (tempsiz).height = (rect).bottom_y - (rect).top_y + 1; };

    if ( ( ( (flags) & (1L << 2) ) != 0 ) )
        tempsiz.width = bodsiz.width;
    if ( ( ( (flags) & (1L << 3) ) != 0 ) )
        tempsiz.height = bodsiz.height;

    if ( ( ( (flags) & (1L << 0) ) != 0 ) )
        rect.left_x = top_left.x;
    if ( ( ( (flags) & (1L << 1) ) != 0 ) )
        rect.top_y = top_left.y;

    rect.right_x = rect.left_x + tempsiz.width - 1;
    rect.bottom_y = rect.top_y + tempsiz.height - 1;

    rect = Region_Adjust_Rectangle( uwinp, rect );

    { ((center)).x = 1 + (((rect)).left_x + ((rect)).right_x) / 2; ((center)).y = 1 + (((rect)).top_y + ((rect)).bottom_y) / 2; };
    { (siz).width = (rect).right_x - (rect).left_x + 1; (siz).height = (rect).bottom_y - (rect).top_y + 1; };

    if ( ( ( ( (flags) & (1L << 2) ) != 0 ) || ( ( (flags) & (1L << 3) ) != 0 ) ) )
 uwinp->sized = 1;
    if ( ( ( ( (flags) & (1L << 0) ) != 0 ) || ( ( (flags) & (1L << 1) ) != 0 ) ) )
    {
 uwinp->positioned = 1;
        (((Tilwin *)(uwinp->winp)) -> position = (center));
    }

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] )
                                       )
        { if ((siz).width > (uwinp->client_min).width) (siz).width = (siz).width; else (siz).width = (uwinp->client_min).width; if ((siz).height > (uwinp->client_min).height) (siz).height = (siz).height; else (siz).height = (uwinp->client_min).height; };

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] )
                                       )
        { if ((siz).width < (uwinp->client_max).width) (siz).width = (siz).width; else (siz).width = (uwinp->client_max).width; if ((siz).height < (uwinp->client_max).height) (siz).height = (siz).height; else (siz).height = (uwinp->client_max).height; };

    { if (((((Tilwin *)(uwinp->winp)) -> min_size)).width < (siz).width) (tempsiz).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; else (tempsiz).width = (siz).width; if (((((Tilwin *)(uwinp->winp)) -> min_size)).height < (siz).height) (tempsiz).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; else (tempsiz).height = (siz).height; }
                                            ;
    { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (tempsiz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (tempsiz).width ) & (~1); };
    { if (((((Tilwin *)(uwinp->winp)) -> max_size)).width > (siz).width) (tempsiz).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; else (tempsiz).width = (siz).width; if (((((Tilwin *)(uwinp->winp)) -> max_size)).height > (siz).height) (tempsiz).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; else (tempsiz).height = (siz).height; }
                                            ;
    { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (tempsiz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (tempsiz).width ) & (~1); };

    desired = (((Tilwin *)(uwinp->winp)) -> desired_size);
    if ( ( ( (flags) & (1L << 2) ) != 0 ) )
        desired.width = siz.width;
    if ( ( ( (flags) & (1L << 3) ) != 0 ) )
        desired.height = siz.height;
    { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (desired).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (desired).width ) & (~1); };

    if (! (! ( ( (((Tilwin *)(uwinp->winp))->rect).left_x == (((Tilwin *)(uwinp->winp))->prev_rect).left_x ) && ( (((Tilwin *)(uwinp->winp))->rect).right_x == (((Tilwin *)(uwinp->winp))->prev_rect).right_x ) && ( (((Tilwin *)(uwinp->winp))->rect).top_y == (((Tilwin *)(uwinp->winp))->prev_rect).top_y ) && ( (((Tilwin *)(uwinp->winp))->rect).bottom_y == (((Tilwin *)(uwinp->winp))->prev_rect).bottom_y ) ) ))
        Client_Configure_Denied( uwinp );

    if (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
    {
        Tilwin_Set( uwinp->winp, center, siz );
        Manage_Finish_Minned( uwinp, 1 );
        Manage_Cant_Undo();
    }
    else
    {
        Manage_User_Open_Configure( uwinp, center, siz,
            ( ( ( (flags) & (1L << 0) ) != 0 ) || ( ( (flags) & (1L << 1) ) != 0 ) ),
            ( ( ( (flags) & (1L << 2) ) != 0 ) || ( ( (flags) & (1L << 3) ) != 0 ) ) );
        Manage_Finish_Minned( uwinp, 1 );
    }
}



void Manage_Client_Set_Icon_Size( uwinp, siz )
    Userwin *uwinp;
    Size siz;
{
    { (((Tilwin *)(uwinp->iconp)) -> min_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->iconp)) -> min_size).width = (1+ (siz).width ) & (~1); };
    { (((Tilwin *)(uwinp->iconp)) -> max_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->iconp)) -> max_size).width = (1+ (siz).width ) & (~1); };
    { (((Tilwin *)(uwinp->iconp)) -> desired_size).height = ( (siz).height ) & (~1); (((Tilwin *)(uwinp->iconp)) -> desired_size).width = ( (siz).width ) & (~1); };

    if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
    {
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Tilwin_Set_Size( uwinp->iconp, siz ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Tilwin_Set_Size( uwinp->iconp, siz ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Tilwin_Set_Size( uwinp->iconp, siz ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Tilwin_Set_Size( uwinp->iconp, siz ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }





        Manage_Cant_Undo();
    }
    else
        Tilwin_Set_Size( uwinp->iconp, siz );
}



void Manage_Client_Set_Icon_Position( uwinp, pt )
    Userwin *uwinp;
    TWPoint pt;
{
    uwinp->icon_positioned = 1;
    (((Tilwin *)(uwinp->iconp)) -> position = (pt));

    if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
    {
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Manage_Icon_Open( uwinp ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Manage_Icon_Open( uwinp ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Manage_Icon_Open( uwinp ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Start(); Manage_Icon_Open( uwinp ); Manage_Finish( 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }





        Manage_Cant_Undo();
    }
    else
        Tilwin_Set( uwinp->iconp, pt, (((Tilwin *)(uwinp->iconp)) -> size) );
}
# 4026 "manage.c"
static void Manage_Act_Hints_Open( uwinp, pos, siz, pos_act, siz_act )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
    bool pos_act, siz_act;
{
    bool result;

    if ( pos_act )
            result = Manage_Center_Neighborhood_Open(
                         uwinp, pos, siz );

    else if ( siz_act )
        result = Manage_Center_Neighborhood_Open(
                         uwinp, (((Tilwin *)(uwinp->winp))->center), siz );

    if (! result)
        Draw_Flash();
}



static void Manage_Act_Hints_Closed( uwinp, pos, siz, pos_act, siz_act )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
    bool pos_act, siz_act;
{
    if ( pos_act && siz_act )
        Tilwin_Set( uwinp->winp, pos, siz );

    else if ( pos_act )
        Tilwin_Set( uwinp->winp, pos, (((Tilwin *)(uwinp->winp))->center) );

    else if ( siz_act )
        Tilwin_Set( uwinp->winp, (((Tilwin *)(uwinp->winp))->center), siz );
}



void Manage_Client_Set_Geometry_Hints( uwinp, flags,
                                       top_left, size )
    Userwin *uwinp;
    long flags;
    TWPoint top_left;
    Size size;
{
    Size siz;
    TWRectangle rect;
    TWPoint pos;
    bool pos_act, siz_act;
    bool by_user;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    Manage_Start();
    Manage_Save_State( uwinp );

    if ( uwinp->zoomed )
    {
        uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);
        uwinp->zoom_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
    }
    else
    {
        uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);
        uwinp->regular_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
    }

    by_user =
        ( ( ( (flags) & (1L << 0) ) != 0 ) ||
          ( ( (flags) & (1L << 1) ) != 0 ) );



    if (! ( ( ( (flags) & ((1L << 3) | (1L << 1)) ) != 0 ) && (! ( (uwinp)->options[(int)(IGNORE_SIZE_HINTS)] ) ) && ( uwinp->ever_opened || (! ( (uwinp)->options[(int)(IGNORE_INITIAL_SIZE_HINTS)] ) ) ) ) )
        size = Region_Unadjust_Size( uwinp, uwinp->regular_size );

    rect = Region_Body_Rectangle( uwinp );
    if ( ( ( ( (flags) & ((1L << 2) | (1L << 0)) ) != 0 ) && (! ( (uwinp)->options[(int)(IGNORE_POSITION_HINTS)] ) ) && ( uwinp->ever_opened || (! ( (uwinp)->options[(int)(IGNORE_INITIAL_POSITION_HINTS)] ) ) ) ) )
    {
        uwinp->positioned = 1;
        rect.top_y = top_left.y;
        rect.left_x = top_left.x;
    }
    rect.right_x = rect.left_x + size.width - 1;
    rect.bottom_y = rect.top_y + size.height - 1;

    rect = Region_Adjust_Rectangle( uwinp, rect );

    { ((pos)).x = 1 + (((rect)).left_x + ((rect)).right_x) / 2; ((pos)).y = 1 + (((rect)).top_y + ((rect)).bottom_y) / 2; };
    if ( ( ( ( (flags) & ((1L << 2) | (1L << 0)) ) != 0 ) && (! ( (uwinp)->options[(int)(IGNORE_POSITION_HINTS)] ) ) && ( uwinp->ever_opened || (! ( (uwinp)->options[(int)(IGNORE_INITIAL_POSITION_HINTS)] ) ) ) ) )
        (((Tilwin *)(uwinp->winp)) -> position = (pos));

    { (size).width = (rect).right_x - (rect).left_x + 1; (size).height = (rect).bottom_y - (rect).top_y + 1; };
    if ( ! uwinp->ever_opened )
    {
        if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_WIDTH ) )
            size.width = uwinp->regular_size.width;
        if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_HEIGHT ) )
            size.height = uwinp->regular_size.height;
    }



    siz_act = ( ( (flags) & (1L << 1) ) != 0 );

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] )
                                       )
        { if ((size).width > (uwinp->client_min).width) (size).width = (size).width; else (size).width = (uwinp->client_min).width; if ((size).height > (uwinp->client_min).height) (size).height = (size).height; else (size).height = (uwinp->client_min).height; };

    if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] )
                                       )
        { if ((size).width < (uwinp->client_max).width) (size).width = (size).width; else (size).width = (uwinp->client_max).width; if ((size).height < (uwinp->client_max).height) (size).height = (size).height; else (size).height = (uwinp->client_max).height; };

    if ( ( ( (flags) & (1L << 1) ) != 0 ) )
    {
        if ( ( user_global_options[(int)(RESET_MIN_ON_DECREASE)] ) )
            { if ((uwinp->regular_min).width < (size).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (size).width; if ((uwinp->regular_min).height < (size).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (size).height; }
        else
            { if ((size).width > (uwinp->regular_min).width) (size).width = (size).width; else (size).width = (uwinp->regular_min).width; if ((size).height > (uwinp->regular_min).height) (size).height = (size).height; else (size).height = (uwinp->regular_min).height; };

        if ( ( user_global_options[(int)(RESET_MAX_ON_INCREASE)] ) )
        {
            { if (((((Tilwin *)(uwinp->winp)) -> max_size)).width > (size).width) (siz).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; else (siz).width = (size).width; if (((((Tilwin *)(uwinp->winp)) -> max_size)).height > (size).height) (siz).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; else (siz).height = (size).height; };
            { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (siz).width ) & (~1); };
        }
        else
            { if ((size).width < ((((Tilwin *)(uwinp->winp)) -> max_size)).width) (size).width = (size).width; else (size).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; if ((size).height < ((((Tilwin *)(uwinp->winp)) -> max_size)).height) (size).height = (size).height; else (size).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; };
    }
    else
    {
        { if ((size).width < ((((Tilwin *)(uwinp->winp)) -> max_size)).width) (size).width = (size).width; else (size).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; if ((size).height < ((((Tilwin *)(uwinp->winp)) -> max_size)).height) (size).height = (size).height; else (size).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; };
        { if ((size).width > (uwinp->regular_min).width) (size).width = (size).width; else (size).width = (uwinp->regular_min).width; if ((size).height > (uwinp->regular_min).height) (size).height = (size).height; else (size).height = (uwinp->regular_min).height; };
    }

    if ( ( ( ( (flags) & ((1L << 3) | (1L << 1)) ) != 0 ) && (! ( (uwinp)->options[(int)(IGNORE_SIZE_HINTS)] ) ) && ( uwinp->ever_opened || (! ( (uwinp)->options[(int)(IGNORE_INITIAL_SIZE_HINTS)] ) ) ) ) )
    {
        uwinp->sized = 1;
        uwinp->regular_size = size;
    }
    else
        if ( uwinp->zoomed )
            siz_act = 0;



    pos_act = ( ( (flags) & (1L << 0) ) != 0 );

    { if ((uwinp->zoom_size).width > (uwinp->regular_size).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->regular_size).width; if ((uwinp->zoom_size).height > (uwinp->regular_size).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->regular_size).height; }
                                                         ;
    { if ((uwinp->zoom_min).width > (uwinp->regular_min).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->regular_min).width; if ((uwinp->zoom_min).height > (uwinp->regular_min).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->regular_min).height; }
                                                       ;

    if ( uwinp->zoomed )
    {
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
    }
    else
    {
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
    }

    if ( (! ( siz_act || pos_act ) ) ||
         ( (! uwinp->ever_opened) && uwinp->layout_found ) )
    {
        Manage_Finish( 1 );
        if (! by_user)
            Manage_Cant_Undo();
    }
    else if (! (((Tilwin *)((uwinp)->winp)) -> Am_I_Open) )
    {
        Manage_Act_Hints_Closed( uwinp, pos, size,
                                        pos_act, siz_act );
        Manage_Finish( 1 );
        Manage_Cant_Undo();
    }
    else if ( by_user )
    {
        Manage_Act_Hints_Open( uwinp, pos, size,
                                       pos_act, siz_act );
        Manage_Finish_Minned( uwinp, 1 );
    }
    else
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Act_Hints_Open( uwinp, pos, size, pos_act, siz_act ); Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Act_Hints_Open( uwinp, pos, size, pos_act, siz_act ); Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Act_Hints_Open( uwinp, pos, size, pos_act, siz_act ); Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { Manage_Act_Hints_Open( uwinp, pos, size, pos_act, siz_act ); Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }

                                                          ;
}



void Manage_Initial_Geometry( uwinp, top_left, bodsiz )
    Userwin *uwinp;
    TWPoint top_left;
    Size bodsiz;
{
    TWPoint center;
    Size siz;
    TWRectangle rect;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    rect.left_x = top_left.x;
    rect.top_y = top_left.y;

    rect.right_x = rect.left_x + bodsiz.width - 1;
    rect.bottom_y = rect.top_y + bodsiz.height - 1;

    rect = Region_Adjust_Rectangle( uwinp, rect );

    { ((center)).x = 1 + (((rect)).left_x + ((rect)).right_x) / 2; ((center)).y = 1 + (((rect)).top_y + ((rect)).bottom_y) / 2; };

    { (siz).width = (rect).right_x - (rect).left_x + 1; (siz).height = (rect).bottom_y - (rect).top_y + 1; };
    if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_WIDTH ) )
        siz.width = uwinp->regular_size.width;
    if ( Profile_Supplies_User_Value( uwinp, NORMAL_DESIRED_HEIGHT ) )
        siz.height = uwinp->regular_size.height;

    { if ((siz).width < ((((Tilwin *)(uwinp->winp)) -> max_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; if ((siz).height < ((((Tilwin *)(uwinp->winp)) -> max_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; };
    { if ((siz).width > ((((Tilwin *)(uwinp->winp)) -> min_size)).width) (siz).width = (siz).width; else (siz).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; if ((siz).height > ((((Tilwin *)(uwinp->winp)) -> min_size)).height) (siz).height = (siz).height; else (siz).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; };

    { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (siz).width ) & (~1); };
    Tilwin_Set( uwinp->winp, center, siz );
}



void Manage_Client_Set_Normal_Hints( uwinp, flags,
                            min_size, max_size, incr_size,
                            min_aspect, max_aspect, base_size )
    Userwin *uwinp;
    long flags;
    Size min_size, max_size, incr_size, base_size;
    TWPoint min_aspect, max_aspect;
{
    Size siz;
    bool act = 0;

    if (! uwinp->prepared)
        Manage_Prepare( uwinp );

    Manage_Start();
    Manage_Save_State( uwinp );

    if ( uwinp->zoomed )
    {
        uwinp->zoom_min = (((Tilwin *)(uwinp->winp)) -> min_size);
        uwinp->zoom_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
    }
    else
    {
        uwinp->regular_min = (((Tilwin *)(uwinp->winp)) -> min_size);
        uwinp->regular_size = (((Tilwin *)(uwinp->winp)) -> desired_size);
    }

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_WIDTH ) )
        max_size.width = uwinp->body_max.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MAX_HEIGHT ) )
        max_size.height = uwinp->body_max.height;

    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_WIDTH ) )
        min_size.width = uwinp->body_min.width;
    if ( Profile_Supplies_User_Value( uwinp, CLIENT_MIN_HEIGHT ) )
        min_size.height = uwinp->body_min.height;



    if ( ( ( (flags) & (1L << 5) ) != 0 ) )
    {
        if ( ( ( (flags) & (1L << 4) ) != 0 ) )
            { if ((max_size).width > (min_size).width) (max_size).width = (max_size).width; else (max_size).width = (min_size).width; if ((max_size).height > (min_size).height) (max_size).height = (max_size).height; else (max_size).height = (min_size).height; }
        else if ( ( ( (flags) & (1L << 8) ) != 0 ) )
        {
            min_size = base_size;
            { if ((max_size).width > (min_size).width) (max_size).width = (max_size).width; else (max_size).width = (min_size).width; if ((max_size).height > (min_size).height) (max_size).height = (max_size).height; else (max_size).height = (min_size).height; }
        }

        uwinp->client_max = Region_Adjust_Size( uwinp, max_size );
        if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MAXIMUMS)] ) )
        {
            if ( ( (uwinp)->options[(int)(AUTO_RESATISFY_ON_RESET_MINMAX)] )
                                                      )
                act = 1;

            { if (((((Tilwin *)(uwinp->winp)) -> max_size)).width < (uwinp->client_max).width) (siz).width = ((((Tilwin *)(uwinp->winp)) -> max_size)).width; else (siz).width = (uwinp->client_max).width; if (((((Tilwin *)(uwinp->winp)) -> max_size)).height < (uwinp->client_max).height) (siz).height = ((((Tilwin *)(uwinp->winp)) -> max_size)).height; else (siz).height = (uwinp->client_max).height; }

            { (((Tilwin *)(uwinp->winp)) -> max_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> max_size).width = (1+ (siz).width ) & (~1); };

            { if ((uwinp->regular_min).width < (uwinp->client_max).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->client_max).width; if ((uwinp->regular_min).height < (uwinp->client_max).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->client_max).height; }
                                                                 ;

            { if ((uwinp->regular_size).width < (uwinp->client_max).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->client_max).width; if ((uwinp->regular_size).height < (uwinp->client_max).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->client_max).height; }

        }
    }

    if ( ( ( (flags) & (1L << 4) ) != 0 ) || ( ( (flags) & (1L << 8) ) != 0 ) )
    {
        uwinp->body_min = min_size;
        uwinp->client_min = Region_Adjust_Size( uwinp, min_size );
        if ( ( (uwinp)->options[(int)(ENFORCE_CLIENT_MINIMUMS)] ) )
        {
            if ( ( (uwinp)->options[(int)(AUTO_RESATISFY_ON_RESET_MINMAX)] )
                                                      )
                act = 1;

            { if (((((Tilwin *)(uwinp->winp)) -> min_size)).width > (uwinp->client_min).width) (siz).width = ((((Tilwin *)(uwinp->winp)) -> min_size)).width; else (siz).width = (uwinp->client_min).width; if (((((Tilwin *)(uwinp->winp)) -> min_size)).height > (uwinp->client_min).height) (siz).height = ((((Tilwin *)(uwinp->winp)) -> min_size)).height; else (siz).height = (uwinp->client_min).height; }

            { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (siz).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (siz).width ) & (~1); };

            { if ((uwinp->regular_min).width > (uwinp->client_min).width) (uwinp->regular_min).width = (uwinp->regular_min).width; else (uwinp->regular_min).width = (uwinp->client_min).width; if ((uwinp->regular_min).height > (uwinp->client_min).height) (uwinp->regular_min).height = (uwinp->regular_min).height; else (uwinp->regular_min).height = (uwinp->client_min).height; }
                                                                 ;

            { if ((uwinp->regular_size).width > (uwinp->client_min).width) (uwinp->regular_size).width = (uwinp->regular_size).width; else (uwinp->regular_size).width = (uwinp->client_min).width; if ((uwinp->regular_size).height > (uwinp->client_min).height) (uwinp->regular_size).height = (uwinp->regular_size).height; else (uwinp->regular_size).height = (uwinp->client_min).height; }
                                                                  ;
        }
    }

    if ( ( ( ((((Tilwin *)(uwinp->winp)) -> min_size)).width == ((((Tilwin *)(uwinp->winp)) -> max_size)).width ) && ( ((((Tilwin *)(uwinp->winp)) -> min_size)).height == ((((Tilwin *)(uwinp->winp)) -> max_size)).height ) )
                                                  )
        uwinp->sized = 1;

    { if ((uwinp->zoom_size).width > (uwinp->regular_size).width) (uwinp->zoom_size).width = (uwinp->zoom_size).width; else (uwinp->zoom_size).width = (uwinp->regular_size).width; if ((uwinp->zoom_size).height > (uwinp->regular_size).height) (uwinp->zoom_size).height = (uwinp->zoom_size).height; else (uwinp->zoom_size).height = (uwinp->regular_size).height; }
                                                         ;
    { if ((uwinp->zoom_min).width > (uwinp->regular_min).width) (uwinp->zoom_min).width = (uwinp->zoom_min).width; else (uwinp->zoom_min).width = (uwinp->regular_min).width; if ((uwinp->zoom_min).height > (uwinp->regular_min).height) (uwinp->zoom_min).height = (uwinp->zoom_min).height; else (uwinp->zoom_min).height = (uwinp->regular_min).height; }
                                                       ;

    if ( uwinp->zoomed )
    {
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->zoom_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->zoom_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->zoom_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->zoom_size).width ) & (~1); };
    }
    else
    {
        { (((Tilwin *)(uwinp->winp)) -> min_size).height = (1+ (uwinp->regular_min).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> min_size).width = (1+ (uwinp->regular_min).width ) & (~1); };
        { (((Tilwin *)(uwinp->winp)) -> desired_size).height = ( (uwinp->regular_size).height ) & (~1); (((Tilwin *)(uwinp->winp)) -> desired_size).width = ( (uwinp->regular_size).width ) & (~1); };
    }

    if ( !act ||
         ( (! uwinp->ever_opened) && uwinp->layout_found ) )
    {
        Manage_Finish( 1 );
        Manage_Cant_Undo();
    }
    else if (! (((Tilwin *)((uwinp)->winp)) -> Am_I_Open) )
    {
        Manage_Resatisfy( uwinp );
        Manage_Finish( 1 );
        Manage_Cant_Undo();
    }
    else
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { { if( ! Manage_Resatisfy( uwinp ) ) Draw_Flash(); }; Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { { if( ! Manage_Resatisfy( uwinp ) ) Draw_Flash(); }; Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { { if( ! Manage_Resatisfy( uwinp ) ) Draw_Flash(); }; Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { { if( ! Manage_Resatisfy( uwinp ) ) Draw_Flash(); }; Manage_Finish_Minned( uwinp, 1 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }




}



extern bool Manage_Fixed_Open();
extern bool Manage_User_Open_Automatically();



bool Manage_Client_Open_Automatically( uwinp )
    Userwin *uwinp;
{
    bool result = 0;

    if ( ! uwinp->ever_opened )
    {
        Manage_Start();

        if ( uwinp->sized && uwinp->positioned )
            { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ENABLE_GRAVITY)] ); globals[(int)(ENABLE_GRAVITY)] = (0); { result = Manage_Fixed_Open( uwinp ); }; globals[(int)(ENABLE_GRAVITY)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ENABLE_GRAVITY)] ); globals[(int)(ENABLE_GRAVITY)] = (0); { result = Manage_Fixed_Open( uwinp ); }; globals[(int)(ENABLE_GRAVITY)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ENABLE_GRAVITY)] ); globals[(int)(ENABLE_GRAVITY)] = (0); { result = Manage_Fixed_Open( uwinp ); }; globals[(int)(ENABLE_GRAVITY)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ENABLE_GRAVITY)] ); globals[(int)(ENABLE_GRAVITY)] = (0); { result = Manage_Fixed_Open( uwinp ); }; globals[(int)(ENABLE_GRAVITY)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }





        if (! result)
            { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }





        if (! result)
            { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }
                                                   ;

        uwinp->ever_opened = 1;
        Manage_Finish( 1 );
    }
    else
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); { result = Manage_User_Open_Automatically( uwinp, 0, 0 ); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }





    return result;
}



static bool Manage_Exchange_Open( uwinp, pos, siz )
    Userwin *uwinp;
    TWPoint pos;
    Size siz;
{
    bool result;

    Manage_Start_Trying();

    result = Manage_Center_Neighborhood_Open( uwinp, pos, siz );
    if ( (! result) && Manage_Can_Try_Listener_Unzoom() )
        result = Manage_Center_Neighborhood_Open( uwinp, pos, siz );

    Manage_Finish_Trying( result );
    return result;
}



static bool Manage_Icon_Exchange_Open( uwinp, pos )
    Userwin *uwinp;
    TWPoint pos;
{
    bool result;

    result = Manage_Neighborhood_Icon_Open( uwinp, pos );
    if (! result)
        result = Manage_Icon_Open( uwinp );

    return result;
}



static bool Manage_Icon_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    bool result;
    TWPoint pt1, pt2;
    pt1 = (((Tilwin *)(uwinp1->iconp))->center);
    pt2 = (((Tilwin *)(uwinp2->iconp))->center);

    Tilwin_Close( uwinp1->iconp );

    { bool temp_val; temp_val = ( globals[(int)(PREFER_CLOSE_TO_SHRINK)] ); globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (( user_global_options[(int)(PREFER_CL_TO_SHR_ON_EXCHANGE)] )); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTO_CLOSE_ON_EXCHANGE)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTO_SHRINK_ON_EXCHANGE)] ))); { result = Manage_Icon_Exchange_Open( uwinp2, pt1 ); if ( result ) result = Manage_Icon_Exchange_Open( uwinp1, pt2 ); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (temp_val); }
# 4495 "manage.c"
    if ( result )
    {
        (((Tilwin *)(uwinp1->iconp)) -> position = (pt2));
        (((Tilwin *)(uwinp2->iconp)) -> position = (pt1));
    }

    return result;
}



static bool Manage_Open_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    TWPoint pt1, pt2;
    Size siz;
    bool result;

    Manage_Restart();

    pt1 = (((Tilwin *)(uwinp1->winp))->center);
    pt2 = (((Tilwin *)(uwinp2->winp))->center);

    Tilwin_Close( uwinp1->winp );

    { bool temp_val; temp_val = ( user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] ); user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] = ((temp_val && ( ( listener != uwinp1 ) && ( listener != uwinp2 ) ))); { bool temp_val; temp_val = ( globals[(int)(PREFER_CLOSE_TO_SHRINK)] ); globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (( user_global_options[(int)(PREFER_CL_TO_SHR_ON_EXCHANGE)] )); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTO_CLOSE_ON_EXCHANGE)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTO_SHRINK_ON_EXCHANGE)] ))); { siz = Tilwin_Checked_Desired_Size( uwinp2->winp ); result = Manage_Exchange_Open( uwinp2, pt1, siz ); if ( result ) window_excursion }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (temp_val); }; user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] = (temp_val); }
# 4542 "manage.c"
    if ( result )
    {
        (((Tilwin *)(uwinp1->winp)) -> position = (pt2));
        uwinp1->positioned = 1;
        (((Tilwin *)(uwinp2->winp)) -> position = (pt1));
        uwinp2->positioned = 1;
    }
    return result;
}



static bool Manage_Different_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    TWPoint pt1, pt2;
    Size siz;
    bool result;
    bool repos1 = 0;
    bool repos2 = 0;

    if ( uwinp2 == rtl_uwinp ) return 0;

    Manage_Restart();

    pt1 = (((Tilwin *)(uwinp1->winp))->center);
    pt2 = (((Tilwin *)(uwinp2->iconp))->center);

    Tilwin_Close( uwinp1->winp );
    Tilwin_Close( uwinp2->iconp );

    { bool temp_val; temp_val = ( user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] ); user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] = ((temp_val && ( listener != uwinp1 ))); { { bool temp_val; temp_val = ( globals[(int)(PREFER_CLOSE_TO_SHRINK)] ); globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (( user_global_options[(int)(PREFER_CL_TO_SHR_ON_EXCHANGE)] )); { { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTO_CLOSE_ON_EXCHANGE)] ))); { { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTO_SHRINK_ON_EXCHANGE)] ))); { siz = Tilwin_Checked_Desired_Size( uwinp2->winp ); if ( ( user_global_options[(int)(PREFER_EXCHANGED_LOC_ON_OPENING)] ) && (! ( uwinp2->positioned && ( (uwinp2)->options[(int)(REQUIRE_PREV_POS)] ) ) ) ) { result = Manage_Exchange_Open( uwinp2, pt1, siz ); if ( result ) repos2 = 1; } if (! result) result = Manage_Desktop_Open( uwinp2, siz ); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } }; globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); } }; globals[(int)(PREFER_CLOSE_TO_SHRINK)] = (temp_val); } }; user_global_options[(int)(UNZOOM_TIED_LSNR_IF_NECESSARY)] = (temp_val); }
# 4598 "manage.c"
    if (! result)
        return 0;
    window_excursion
# 4614 "manage.c"
    if ( repos1 )
        (((Tilwin *)(uwinp1->iconp)) -> position = (pt2));
    if ( repos2 )
    {
        (((Tilwin *)(uwinp2->winp)) -> position = (pt1));
        uwinp2->positioned = 1;
    }

    return 1;
}



bool Manage_Exchange( uwinp1, uwinp2 )
    Userwin *uwinp1, *uwinp2;
{
    bool open1, open2;
    bool result;

    Manage_Start();

    open1 = ( uwinp1->current_type == body );
    open2 = ( uwinp2->current_type == body );

    if ( open1 && (! open2) )
    {
        result = Manage_Different_Exchange( uwinp1, uwinp2 );
        Manage_Finish_Locked( uwinp2, result );
    }

    else if ( open2 && (! open1) )
    {
        result = Manage_Different_Exchange( uwinp2, uwinp1 );
        Manage_Finish_Locked( uwinp1, result );
    }

    else if ( (! open1) && (! open2) )
    {
        result = Manage_Icon_Exchange( uwinp1, uwinp2 );
        Manage_Finish( result );
    }

    else
    {
        result = 0;

        if ( ( user_global_options[(int)(TRY_CTR_NBRHD_ON_EXCHANGE)] )
                                            &&
             ( user_global_options[(int)(TRY_CTR_NBRHD_ON_OPEN)] )
                                        )
        {
            result = Manage_Open_Exchange( uwinp1, uwinp2 );
            if (! result)
                result = Manage_Open_Exchange( uwinp2, uwinp1 );
        }

        if (! result)
            { bool temp_val; temp_val = ( user_global_options[(int)(TRY_CTR_NBRHD_ON_OPEN)] ); user_global_options[(int)(TRY_CTR_NBRHD_ON_OPEN)] = (0); { result = Manage_Open_Exchange( uwinp1, uwinp2 ); if (! result) result = Manage_Open_Exchange( uwinp2, uwinp1 ); }; user_global_options[(int)(TRY_CTR_NBRHD_ON_OPEN)] = (temp_val); }







        window_excursion;



    }

    return result;
}



static void Manage_Remove_Window( uwinp )
    Userwin *uwinp;
{
    TimeStamp stamp;

    Manage_Start();

    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
    {
        Tilwin_Close( uwinp->winp );

        if ( ( user_global_options[(int)(AUTO_REPOPULATE_ON_CLOSE)] ) )
        {
            if ( ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) )
                Manage_Ordered_Desire();

            if ( ( user_global_options[(int)(ONLY_REPOPULATE_SINCE_ON_CLOSE)] ) )
                stamp = uwinp->open_stamp;
            else
                stamp = (TimeStamp)0;
            Manage_Repopulate_Since( stamp, 0, 0, 1 );
        }
    }

    Manage_Finish( 1 );
}



static void Manage_Remove( uwinp )
    Userwin *uwinp;
{
    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
        Tilwin_Close( uwinp->winp );
    else if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
        Tilwin_Close( uwinp->iconp );

    Closed_Remove( uwinp );
}



void Manage_Close( uwinp )
    Userwin *uwinp;
{
    extern void Manage_Contract();

    if ( uwinp->client_state != 2 )
        Manage_Remove_Window( uwinp );
    else if ( ( ( ((((Tilwin *)(uwinp->winp)) -> min_size)).width == ((((Tilwin *)(uwinp->winp)) -> size)).width ) && ( ((((Tilwin *)(uwinp->winp)) -> min_size)).height == ((((Tilwin *)(uwinp->winp)) -> size)).height ) )
                                                        )
        Manage_Remove_Window( uwinp );
    else
        Manage_Contract( uwinp );
}



void Manage_Client_Close( uwinp )
    Userwin *uwinp;
{
    { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } };
}



void Manage_Client_Open_Icon( uwinp )
    Userwin *uwinp;
{
    if ( uwinp->ever_opened )
        Manage_Client_Close( uwinp );
    else
    {
        uwinp->ever_opened = 1;
        { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Initial_Icon_Open( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }
    }
}



static void Manage_Close_Icon( uwinp )
    Userwin *uwinp;
{
    Manage_Start();
    if ( (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
        Tilwin_Close( uwinp->iconp );
    Manage_Finish( 1 );
}



static void Manage_Inactivate( uwinp )
    Userwin *uwinp;
{
    if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
        Manage_Remove_Window( uwinp );
    else
        Manage_Close_Icon( uwinp );
}



void Manage_Client_Close_Icon( uwinp )
    Userwin *uwinp;
{
    { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }
}



void Manage_Group_Close( uwinp )
    Userwin *uwinp;
{
    Tilwinp winp;
    Userwin *group;
    TimeStamp stamp;

    group = uwinp->group;
    if ( group == (Userwin *)((void *)0) )
    {
        Manage_Close( uwinp );
        return;
    }

    Manage_Start();

    group->group = group;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( (uwinp->group == group) &&
             (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open)) &&
             (! (((Tilwin *)(uwinp->iconp)) -> Am_I_Open)) )
        {
            Manage_Save_State( uwinp );
            Closed_Remove( uwinp );
            uwinp->group_state = uwinp->wm_state;
        }
    }

    stamp = last_stamp;

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( uwinp->group == group )
        {
            if ( uwinp->winp == winp )
                stamp = ( ( (stamp) < (uwinp->open_stamp) ) ? (stamp) : (uwinp->open_stamp) );

            Manage_Save_State( uwinp );
            Manage_Remove( uwinp );
            uwinp->group_state = uwinp->wm_state;
        }
    }

    if (! group->ever_opened)
        Manage_Prepare_Open( group );

    Closed_Add( uwinp );
    if ( ( user_global_options[(int)(USE_ICONS)] ) )
        Manage_Icon_Open( uwinp );

    if ( ( user_global_options[(int)(AUTO_REPOPULATE_ON_CLOSE)] ) )
    {
        if ( ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) )
            Manage_Ordered_Desire();

        if (! ( user_global_options[(int)(ONLY_REPOPULATE_SINCE_ON_CLOSE)] ) )
            stamp = (TimeStamp)0;
        Manage_Repopulate_Since( stamp, 0, 0, 1 );
    }

    Manage_Finish( 1 );
}



static void Manage_Group_Restore( uwinp )
    Userwin *uwinp;
{
    int state;

    state = uwinp->group_state;
    uwinp->group_state = -3;

    switch ( state )
    {
        case -2:
            break;

        case -1:
        case 0:
        case 1:
            Closed_Add( uwinp );
            Manage_User_Open_Automatically( uwinp, 0, 0 );
            break;

        case 2:
        case 3:
        case 4:
            Closed_Add( uwinp );
            if ( uwinp->client_state == 2 )
                Manage_User_Open_Automatically( uwinp, 0, 0 );
            else
                Manage_Icon_Open( uwinp );
            break;

        case 5:
            break;
    }
}



void Manage_Group_Open( group )
    Userwin *group;
{
    bool found = 1;
    Tilwinp winp;
    Userwin *uwinp;

    Manage_Start();

    Manage_Save_State( group );
    if ( (((Tilwin *)(group->iconp)) -> Am_I_Open) )
        Tilwin_Close( group->iconp );
    Closed_Remove( group );

    while (found)
    {
        found = 0;

        Tilwin_Gen_Closed_Windows();
        while ( (! found) &&
                ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) ) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( ( (uwinp)->group_state != -3 ) &&
                 (uwinp->group == group) )
            {
                found = 1;
                Manage_Group_Restore( uwinp );
            }
        }
    }

    Manage_Finish( 1 );
}



void Manage_Want_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    uwinp->group_state = state;
}



static void Manage_Set_Group( uwinp, group )
    Userwin *uwinp;
    Userwin *group;
{
    Manage_Start();

    uwinp->group = group;
    if (! ( (uwinp)->group_state != -3 ) )
    {
        if ( ( group != (Userwin *)((void *)0)) && ( (group)->group_state != -3 ) )
        {
            Manage_Save_State( uwinp );
            Manage_Remove( uwinp );
            uwinp->group_state = uwinp->wm_state;
        }
    }
    else if ( ( group == (Userwin *)((void *)0) ) ||
              (! ( (group)->group_state != -3 ) ) )
        Manage_Group_Restore( uwinp );

    Manage_Finish( 1 );
}



void Manage_Client_Set_Group( uwinp, group )
    Userwin *uwinp;
    Userwin *group;
{
    { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Set_Group( uwinp, group ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Set_Group( uwinp, group ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Set_Group( uwinp, group ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Set_Group( uwinp, group ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }
}



void Manage_Client_Set_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    uwinp->client_state = state;
}



void Manage_Client_Change_State( uwinp, state )
    Userwin *uwinp;
    int state;
{
    uwinp->client_state = state;

    if ( ( state != 5 ) &&
         ( uwinp->wm_state == 5 ) )
        Drawwin_Insert( uwinp );
    else if ( ( state == 5 ) &&
              ( uwinp->wm_state != 5 ) )
        Drawwin_Withdraw( uwinp );

    if ( ( (uwinp)->group_state != -3 ) )
    {
        if ( state == 5 )
        {
            if ( (uwinp->wm_state != 5) &&
                 (uwinp->group != uwinp) )
            {
                uwinp->wm_state = 5;
                Client_Set_State( uwinp );
            }
            uwinp->group_state = 5;
        }
        else
        {
            if ( uwinp->wm_state == 5 )
            {
                uwinp->wm_state = 4;
                uwinp->group_state = state;
                Client_Set_State( uwinp );
            }

            else if ( ( state != -1 ) && ( state != 0 ) )
                uwinp->group_state = state;
        }
    }
    else
    {
        switch ( state )
        {
            case -1:
            case 0:
                break;

            case 1:
            case 2:
                if (! (((Tilwin *)(uwinp->winp)) -> Am_I_Open) )
                    Manage_Client_Open_Automatically( uwinp );
                break;

            case 3:
                { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Remove_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } };
                break;

            case 4:
                if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ||
                     (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
                    { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }

                uwinp->wm_state = 4;
                Client_Set_State( uwinp );
                Closed_Add( uwinp );

                break;

            case 5:
                if ( (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ||
                     (((Tilwin *)(uwinp->iconp)) -> Am_I_Open) )
                    { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Inactivate( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } }

                uwinp->wm_state = 5;
                Client_Set_State( uwinp );

                Closed_Remove( uwinp );
                break;
        }
    }
}



void Manage_Repopulate_Last()
{
    Manage_Start();
    Manage_Repopulate_Since( last_stamp, 1, 0, 1 );
    Manage_Finish( 1 );
}



void Manage_Repopulate_All( strict, only_auto_close )
    bool strict;
    bool only_auto_close;
{
    Manage_Start();
    Manage_Repopulate_Since( (TimeStamp)0, 1, strict, only_auto_close );
    Manage_Finish( 1 );
}



static void Manage_Cleanup_Window( uwinp )
    Userwin *uwinp;
{
    if ( uwinp == prev_touch ) prev_touch = (Userwin *)((void *)0);
    if ( uwinp == prev_listener ) prev_listener = (Userwin *)((void *)0);
    Manage_Unset( uwinp );


    uwinp->client_state = -2;

    Manage_Remove( uwinp );
}



void Manage_Eliminate_Window( uwinp )
    Userwin *uwinp;
{
    Manage_Untitle( uwinp );

    Drawwin_Destroy( uwinp );
    DrawIcon_Destroy( uwinp );

    Tilwin_Destroy_Window( uwinp->winp );
    Tilwin_Destroy_Window( uwinp->iconp );

    free( uwinp );
}



static void Manage_Cleanup_Connection( connection )
    int connection;
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( (uwinp->connection == connection ) &&
             ( (winp == uwinp->winp) || (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ) )
        {
            Manage_Cleanup_Window( uwinp );
        }
    }
}



static void Manage_Eliminate_Connection( connection )
    int connection;
{
    Tilwinp winp;
    Userwin *uwinp;
    bool killed = 1;

    while (killed)
    {
        killed = 0;
        Tilwin_Gen_Closed_Windows();
        while ( (! killed) &&
                ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) ) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( (uwinp->connection == connection ) &&
                 ( (winp == uwinp->winp) || (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ) )
            {
                Manage_Eliminate_Window( uwinp );
                killed = 1;
            }
        }
    }
}



static void Manage_Destroy_Window( uwinp )
    Userwin *uwinp;
{
    bool zoomed;
    TimeStamp open_stamp, zoom_stamp;

    Manage_Start();

    if ( ( user_global_options[(int)(ONLY_REPOPULATE_SINCE_ON_CLOSE)] ) )
        open_stamp = uwinp->open_stamp;
    else
        open_stamp = (TimeStamp)0;

    zoomed = uwinp->zoomed;
    if ( ( user_global_options[(int)(ONLY_REPOP_SINCE_ON_AUTO_UNZOOM)] )
                                              ||
         ( user_global_options[(int)(ONLY_REPOP_SINCE_ON_EXPL_UNZOOM)] )
                                              )
        zoom_stamp = uwinp->zoom_stamp;
    else
        zoom_stamp = (TimeStamp)0;

    Manage_Cleanup_Window( uwinp );

    Manage_Update_Desktop();

    Manage_Eliminate_Window( uwinp );

    if ( ( user_global_options[(int)(AUTO_DESIRED_ENLARGE)] ) )
        Manage_Ordered_Desire();

    if ( ( user_global_options[(int)(AUTO_REPOPULATE_ON_CLOSE)] ) )
        Manage_Repopulate_Since( open_stamp, 0, 0, 1 );

    if ( zoomed &&
         ( user_global_options[(int)(AUTO_REPOP_ON_EXPLICIT_UNZOOM)] ) )
        Manage_Repopulate_Since( zoom_stamp, 0, 0, 1 );

    Manage_Finish( 1 );
}



void Manage_Client_Destroy( uwinp )
    Userwin *uwinp;
{
    Manage_Unset( uwinp );
    { Userwin *cur_listener; Userwin *cur_sublistener; cur_listener = listener; cur_sublistener = sublistener; if ( sublistener != (Userwin *)((void *)0) ) { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Destroy_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_sublistener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Destroy_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_sublistener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } } else { if ( listener != (Userwin *)((void *)0) ) { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = ((temp_val || (! ( user_global_options[(int)(ALLOW_LSNR_TO_CLOSE_BY_CLIENT)] )))); { { bool temp_val; temp_val = ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ); ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = ((temp_val || ( cur_listener->focus && (! ( user_global_options[(int)(ALLOW_LSNR_TO_CHANGE_BY_CLIENT)] ))))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Destroy_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) FIXED_COMPLETELY ] ) = (temp_val); } }; ( ((Tilwin *)(cur_listener->winp)) -> options[ (int) REQUIRE_MANUAL_CLOSE ] ) = (temp_val); } else { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_SHRINK)] ); globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_SHRINK_BY_CLIENT)] ))); { bool temp_val; temp_val = ( globals[(int)(ALLOW_AUTOMATIC_CLOSE)] ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = ((temp_val && ( user_global_options[(int)(ALLOW_AUTOMATIC_CLOSE_BY_CLIENT)] ))); Manage_Destroy_Window( uwinp ); globals[(int)(ALLOW_AUTOMATIC_CLOSE)] = (temp_val); }; globals[(int)(ALLOW_AUTOMATIC_SHRINK)] = (temp_val); } } };
}



void Manage_Hard_Kill( uwinp )
    Userwin *uwinp;
{
    Client_Kill( uwinp );
    Manage_Destroy_Window( uwinp );
}



void Manage_Notify( uwinp )
    Userwin *uwinp;
{
    if ( ( ( ((uwinp)->messages) & (1L << 2) ) != 0 ) )
    {
        uwinp->saving_state = 1;
        Client_Bang( uwinp );
    }
    else
        Draw_Flash();
}



void Manage_Soft_Kill( uwinp )
    Userwin *uwinp;
{
    if ( ( ( ((uwinp)->messages) & (1L << 2) ) != 0 ) )
    {
        uwinp->saving_state = 1;
        uwinp->soft_kill = 1;
        Client_Bang( uwinp );
    }
    else
    {
        Client_Kill( uwinp );
        Manage_Destroy_Window( uwinp );
    }
}



void Manage_Delete_Window( uwinp )
    Userwin *uwinp;
{
    if ( ( ( ((uwinp)->messages) & (1L << 4) ) != 0 ) )
        Client_Delete_Window( uwinp );
    else
        Manage_Soft_Kill( uwinp );
}



void Manage_Notify_All()
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( (uwinp != rtl_uwinp) &&
             ( (winp == uwinp->winp) || (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ) )
        {
            if ( ( ( ((uwinp)->messages) & (1L << 2) ) != 0 ) )
                Manage_Notify( uwinp );
        }
    }
}



void Manage_Soft_Kill_All()
{
    Tilwinp winp;
    Userwin *uwinp;
    bool killed = 1;

    while (killed)
    {
        killed = 0;
        Tilwin_Gen_Closed_Windows();
        while ( (! killed) &&
                ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) ) )
        {
            uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
            if ( (uwinp != rtl_uwinp) &&
                 ( (winp == uwinp->winp) || (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ) )
            {
                Manage_Soft_Kill( uwinp );
                killed = 1;
            }
        }
    }
}



void Manage_Exit()
{
    Tilwinp winp;
    Userwin *uwinp;

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != (Tilwinp)((void *)0) )
    {
        uwinp = ((Userwin *)(( ((winp) == (Tilwinp)((void *)0)) ? (pointer)((void *)0) : (((Tilwin *)(winp))->id) )));
        if ( (uwinp != rtl_uwinp) &&
             ( (winp == uwinp->winp) || (((Tilwin *)(uwinp->winp)) -> Am_I_Open) ) )
            Client_Kill( uwinp );
    }
}



void Manage_Client_Set_Messages( uwinp, messages )
    Userwin *uwinp;
    long messages;
{
    uwinp->messages = messages;
}

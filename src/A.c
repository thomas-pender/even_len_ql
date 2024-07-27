/**
 * @file A.c
 *
 * @brief Search for bracelets with real correlations and vanishing sum of
 * elements.
 *
 * String properties:<br>
 * - Vanishing sum of elements.
 * - Representatives of orbits under the action of D_N x {+1, i, -1, j}.
 * - Orbit representatives must have <b>(1)</b> real-valued correlations, and
 * <b>(2)</b> have bounded square norm of nonprincipal character sums (<= 2N+2).
 *
 * Executable usage: <b><tt>./A <length> 1> <out_file></tt></b> <br>
 * - <b><tt><length></tt></b> is a positive even integer denoting the length of
 * the strings to be generated.
 * - The generated bracelets are written to stdout. This can be redirected to
 * an output file  <b><tt><out_file></tt></b> as shown above.
 *
 * @author Thomas Pender
 */
# include <config.h>

/* std headers */
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <libgen.h>
# include <error.h>
# include <errno.h>

/* project headers */
# include <defs.h>
# include <legendre.h>

# if HAVE_PTHREAD
# include <pthread.h>
# endif

/**
 * @brief Holds data unique to each thread.
 */
typedef struct {
     unsigned N;           ///< string length
     unsigned nonreal;     ///< number of \sqrt{-1}s in strings
# if HAVE_PTHREAD
     pthread_mutex_t *mtx; ///< dynamic mutex guarding stdout
# endif
} thread_args_t;

/**
 * @brief Thread function to generate fixed content bracelets of a
 *        particular fixed type.
 *
 * Generates fixed content quaternary braceletes with real-valued periodic
 * auto-correlations. Braceletes must have bounded square norm <= 2N+2. The
 * sum of the entries must be 0.
 *
 * @param[in] _thread_args thread arguments (see thread_args_t)
 */
void *thread_func_A(void *_thread_args)
{
     thread_args_t thread_args=*((thread_args_t*)_thread_args);

     neck_t neck={.n=thread_args.N,.k=thread_args.nonreal==0 ? 2 : K,
          .arginit=arginit,.argfree=NULL,.seqprint=printseq};
     neck.num=(unsigned*)calloc(thread_args.nonreal==0 ? 3 : K+1,
                                sizeof(unsigned));

     args_t args={.n=thread_args.N,.l=thread_args.N>>1U,.realcorrs=false};
     args.corrs=(int*)calloc(args.l+1,sizeof(int));
     args.nummap=(unsigned*)calloc(neck.k+1,sizeof(unsigned));
     args.psdtable=Psdtable(args.n);

     /* initialize bracelet arguments and necklace parameters */
     if (thread_args.nonreal==0) { /* strongly restricted case */
          args.nummap[1]=0;
          args.nummap[2]=2;
          neck.num[1]=args.l;
          neck.num[2]=args.l;

          neck.ncheckfuncs=1;
          neck.checkfuncs=(check_t*)malloc(sizeof(check_t));
          neck.checkfuncs[0]=psdtest;
     }
     else { /* restricted cases (there are nonreal entries) */
          args.nummap[1]=1;
          args.nummap[2]=3;
          args.nummap[3]=0;
          args.nummap[4]=2;
          neck.num[1]=thread_args.nonreal;
          neck.num[2]=thread_args.nonreal;
          neck.num[3]=args.l-thread_args.nonreal;
          neck.num[4]=args.l-thread_args.nonreal;

          neck.ncheckfuncs=2;
          neck.checkfuncs=(check_t*)malloc(2*sizeof(check_t));
          neck.checkfuncs[0]=realcorrs;
          neck.checkfuncs[1]=psdtest;
     }

     FCBracelet(&neck,&args
# if HAVE_PTHREAD
                ,thread_args.mtx
# endif
          );

     Argfree(&args);
     Neckfree(&neck);

     return NULL;
}

/**
 * @brief driver
 * @param[in] N Length of strings to be generated. Required to be even.
 */
int main(int argc, char **argv)
{
     if (argc!=2)
          error_at_line(1,errno,basename(__FILE__),__LINE__,
                        "usage -- %s <length>",basename(argv[0]));

     int throw;
     unsigned i, N, NUM_THREADS;
     if (sscanf(argv[1],"%u",&N)==EOF) /* read in string length */
          error_at_line(1,errno,basename(__FILE__),__LINE__,"sscanf failed");
     if (N&1U) /* string length must be even */
          error_at_line(1,errno,basename(__FILE__),__LINE__,
                        "<length> must be even");
     NUM_THREADS=(N-(N&3U))/4 + 1; /* number of distinct contents */

# if HAVE_PTHREAD
     pthread_t threads[NUM_THREADS];
     thread_args_t thread_args[NUM_THREADS];

     /* dynamic mutex guarding stdout */
     pthread_mutex_t mtx;
     pthread_mutex_init(&mtx,NULL);

     /* initialize arguments for each thread */
     for (i=0; i<NUM_THREADS; i++) {
          thread_args[i].N=N;       /* string length */
          thread_args[i].nonreal=i; /* number of \sqrt{-1}s entries */
          thread_args[i].mtx=&mtx;  /* dynamic mutex guarding stdout */
     }
     for (i=0; i<NUM_THREADS; i++)
          if ( (throw=pthread_create(&threads[i],NULL,
                                     thread_func_A,&thread_args[i])) != 0)
               error_at_line(1,throw,basename(__FILE__),__LINE__,
                             "pthread_create failed");
     for (i=0; i<NUM_THREADS; i++)
          if ( (throw=pthread_join(threads[i],NULL)) != 0)
               error_at_line(1,throw,basename(__FILE__),__LINE__,
                             "pthread_join failed");

     pthread_mutex_destroy(&mtx);
# else
     thread_args_t thread_args;

     for (i=0; i<NUM_THREADS; i++) {
          thread_args.N=N;
          thread_args.nonreal=i;
          thread_func_A(&thread_args);
     }
# endif
     exit(0);
}

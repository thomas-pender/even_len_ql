/**
 * @file seq_funcs.c
 * @brief Auxilary sequence methods.
  * @author Thomas Pender
 */
# include <config.h>

/* std headers */
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

/* project headers */
# include <seq_funcs.h>
# include <defs.h>

# define MOD 3       ///< reduction modulo 4 (e.g., <b><tt>x & MOD</tt></b>)
# define ERR 0.00001 ///< floating point estimate
# define PI 3.14159265358979

/**
 * @brief Perform the group composition of {+1, i, -1, j}.
 *
 * String elements are {0, 1, 2, 3}, the exponents of the group elements
 * {+1, i, -1, j} with base i. The arithmetic is the modular addition of the
 * exponents.
 *
 * @param[in] a multiplicand exponent
 * @param[in] b multiplier exponent
 *
 * @retval product Return reduced exponent of i^{a+b}.
 */
static inline
unsigned quatmult(const unsigned a, const unsigned b)
{
     return (a + K - b) & MOD;
}

/**
 * @brief Periodic auto-correlation of sequence.
 *
 * @param[in] a sequence
 * @param[in] j periodic auto-correlation at shift \b j
 * @param[in,out] args user defined sequence arguments
 *
 * @retval correlation <b>j</b>-th periodic auto-correlation or length+1 if it is
 * nonreal.
 */
static
int corr(const unsigned *a, size_t j, args_t *args)
{
     int *vec=(int*)calloc(K,sizeof(int)), diff;
     for (size_t i=0,J; i<args->n; i++) {
          J=i+j;
          J=(J<args->n) ? J : (J-args->n);
          vec[quatmult(args->nummap[a[i+1]],
                       args->nummap[a[J+1]])]++;
     }
     if (vec[1]!=vec[3]) diff=(int)args->n+1;
     else diff=vec[0]-vec[2];
     free(vec);
     return diff;
}

/**
 * @brief Method to print sequence.
 *
 * @param[in] a sequence
 * @param[in] _args user defined sequence arguments
 */
void printseq(const unsigned *a, const void *_args)
{
     size_t i;
     args_t *args=(args_t*)_args;
     for (i=1; i<=args->n; i++) printf("%u",args->nummap[a[i]]);
     printf(" ");
     for (i=1; i<args->l; i++) printf("%d,",args->corrs[i]);
     printf("%d\n",args->corrs[args->l]);
}

/**
 * @brief Initialize auxilary data.
 *
 * Memory allocation for auxilary data structures to be used with user defined
 * functions to be called for each necklace/bracelet encountered during generation
 * of all fixed content necklaces/bracelets of given length and type.
 *
 * @param[in] a sequence
 * @param[in,out] _args user defined sequence arguments
 */
void arginit(const unsigned *a, void *_args)
{
     size_t i;
     args_t *args=(args_t*)_args;

     args->realcorrs=true;
     for (i=1; i<=args->l; i++)
          if ( (args->corrs[i]=corr(a,i,args))>(int)args->n ) {
               args->realcorrs=false;
               break;
          }
}

/**
 * @brief Free auxilary data.
 *
 * Memory deallocation for auxilary data structures to be used with user defined
 * functions to be called for each necklace/bracelet encountered during generation
 * of all fixed content necklaces/bracelets of given length and type.
 *
 * @param[in,out] _args user defined sequence arguments
 */
void argfree(void *_args)
{
     args_t *args=(args_t*)_args;
     if (args->corrs!=NULL) free(args->corrs);
}

/**
 * @brief Check if sequence periodic auto-correlations are real-valued.
 * @param[in] _args user defined sequence arguments.
 * @retval realcorrs Return whether the periodic auto-correlations are real-valued.
 */
bool realcorrs(const void *_args)
{
     args_t *args=(args_t*)_args;
     return args->realcorrs;
}

/**
 * @brief Power spectral density test (bounded square norms of nonprincipal
 * character sums).
 *
 * @param[in] _args user defined sequence arguments
 *
 * @retval square_norm_check Return whether the nonprincipal character sums of
 * the given sequence are bounded above by 2N+2 in order that it might form part of
 * a Legendre pair.
 */
bool psdtest(const void *_args)
{
     args_t *args=(args_t*)_args;
     double sum;
     size_t i,j;
     int N=2*(int)args->n+2;
     for (i=1; i<=args->l; i++) { /* i-th psd */
          sum=args->n;
          for (j=1; j<args->l; j++) sum+=args->corrs[j]*args->psdtable[i][j];
          sum+=args->corrs[args->l]*args->psdtable[i][args->l];
          if (sum-N>ERR) return false;
     }
     return true;
}

/**
 * @brief Table containing distinct square norms of nonprincipal character sums.
 * @param[in] n sequence length
 * @retval table Contains distinct square norms of nonprincipal character sums.
 */
double **Psdtable(unsigned n)
{
     size_t i,j;
     unsigned l=n>>1U;
     double **table=(double**)malloc((l+1)*sizeof(double*));
     table[0]=NULL;
     for (i=1; i<=l; i++) {
          table[i]=(double*)calloc(l+1,sizeof(double));
          table[i][0]=1;
          for (j=1; j<l; j++) {
               table[i][j]=2*creal(cexp(2*PI*I*i*j/n));
          }
          table[i][l]=creal(cexp(2*PI*I*i*l/n));
     }
     return table;
}

/**
 * @brief Free user defined sequence arguments.
 *
 * Free user defined sequence arguments.
 */
void Argfree(args_t *args)
{
     if (args->nummap!=NULL) free(args->nummap);
     if (args->corrs!=NULL) free(args->corrs);
     if (args->psdtable!=NULL) {
          for (size_t i=0; i<=args->l; i++)
               if (args->psdtable[i]!=NULL) free(args->psdtable[i]);
          free(args->psdtable);
     }
}

/**
 * @brief Free dynamic memory of necklace/bracelet data structure.
 *
 * Free dynamic memory of necklace/bracelet data structure.
 */
void Neckfree(neck_t *N)
{
     if (N->num!=NULL) free(N->num);
     if (N->checkfuncs!=NULL) free(N->checkfuncs);
}

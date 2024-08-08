/**
 * @file seq_funcs.h
 * @brief User defined function declarations and structure definition.
 * @author Thomas Pender
 */
# ifndef SEQ_FUNCS_H
# define SEQ_FUNCS_H

/* std headers */
# include <complex.h>
# include <stdbool.h>

/* project headers */
# include <defs.h>

/** @brief complex numbers */
typedef double complex comp;

/**
 * @brief User defined sequence parameters and functions.
 */
typedef struct {
  unsigned n; ///< string length
  unsigned l; ///< length / 2
  unsigned *nummap; ///< bijection between letters and logarithms of i
  int *corrs; ///< sequence periodic auto-correlations
  bool realcorrs; ///< whether the periodic auto-correlations are real-valued
  double **psdtable; ///< distinct square norms of nonprincipal character sums
} args_t;

/* functions for neck struct */
void printseq(const unsigned*, const void*);
void arginit(const unsigned*, void*);
void argfree(void*);
bool realcorrs(const void*);
bool psdtest(const void*);

/* additional functions */
double **Psdtable(unsigned);
void Argfree(args_t*);
void Neckfree(neck_t*);

# endif

/**
 * @file defs.h
 * @brief Typedefs and necklace structure defintion.
 * @author Thomas Pender
 */
# ifndef DEFS_H
# define DEFS_H

# include <stdbool.h>

# define K 4 ///< arity of strings

/** @brief Initializer for auxilary data structures. */
typedef void (*arg_init_t)(const unsigned*, void*);

/** @brief Deallocator for auxilary data structures. */
typedef void (*arg_free_t)(void*);

/** @brief Boolean check for encountered necklace/bracelet. */
typedef bool (*check_t)(const void*);

/** @brief Printing method for encountered necklace/bracelet. */
typedef void (*seq_print_t)(const unsigned*, const void*);

/**
 * @brief Contains structural parameters and user defined functions to be performed
 * for each encountered necklaces/bracelets.
 */
typedef struct {
     unsigned n;           ///< string length
     unsigned k;           ///< string arity
     unsigned *num;        ///< string content
     unsigned ncheckfuncs; ///< number of boolean checks (see check_t)
     arg_init_t arginit;   ///< memory allocation
     arg_free_t argfree;   ///< memory deallocation
     check_t *checkfuncs;  ///< boolean checks
     seq_print_t seqprint; ///< printing method
} neck_t;

# endif

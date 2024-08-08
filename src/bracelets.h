/**
 * @file braceletes.h
 * @brief Function declarations for fixed content necklace/bracelet generators.
 * @author Thomas Pender
 */
# ifndef BRACELETS_H
# define BRACELETS_H

/* project headers */
# include <defs.h>

# if HAVE_PTHREAD
# include <pthread.h>
# endif

void FCNecklace(neck_t*, void*
# if HAVE_PTHREAD
                ,pthread_mutex_t*
# endif
                );

void FCBracelet(neck_t*, void*
# if HAVE_PTHREAD
                ,pthread_mutex_t*
# endif
                );

# endif

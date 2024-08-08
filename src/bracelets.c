/**
 * @file bracelets.c
 * @brief Generation procedures for necklaces and bracelets.
 * @author Thomas Pender
 */
# include <config.h>

/* std headers */
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>

/* project headers */
# include <defs.h>
# include <bracelets.h>

# if HAVE_PTHREAD
# include <pthread.h>
# endif

/* general helpers */

/** @cond */

typedef struct {
  int prev, next;
} cell_t;

static inline
cell_t *cellinit(unsigned k)
{
  cell_t *avail=(cell_t*)malloc((k+2)*sizeof(cell_t));
  for (int j=(int)k+1; j>=0; j--) {
    avail[j].next=j-1;
    avail[j].prev=j+1;
  }
  return avail;
}

static inline
void cellremove(cell_t *avail, int i, int *head)
{
  int p,n;
  if (i==*head) *head=avail[i].next;
  p = avail[i].prev;
  n = avail[i].next;
  avail[p].next = n;
  avail[n].prev = p;
}

static inline
void celladd(cell_t *avail, unsigned k, int i, int *head)
{
  int p,n;
  p=avail[i].prev;
  n=avail[i].next;
  avail[n].prev=i;
  avail[p].next=i;
  if (avail[i].prev==(int)k+1) *head=i;
}

static inline
unsigned *strinit(neck_t *N)
{
  unsigned *a=(unsigned*)malloc((N->n+1)*sizeof(unsigned));
  a[0]=0; a[1]=1;
  for (size_t i=2; i<=N->n; i++) a[i]=N->k;
  return a;
}

static inline
void strprintstd(const unsigned *a, const neck_t *N)
{
  for (size_t i=1; i<=N->n; i++) printf("%u",a[i]-1);
  printf("\n");
  fflush(stdout);
}

static
void strprint(const unsigned *a, const neck_t *N, void *args
# if HAVE_PTHREAD
              ,pthread_mutex_t *mtx
# endif
              )
{
  bool flag=true;
  if (N->arginit!=NULL) N->arginit(a,args);
  if (N->ncheckfuncs>0) {
    for (size_t i=0; i<N->ncheckfuncs; i++)
      if ( (flag=N->checkfuncs[i](args))==false )
        break;
  }
  if (flag) {
# if HAVE_PTHREAD
    if (mtx!=NULL) pthread_mutex_lock(mtx);
# endif
    if (N->seqprint==NULL) strprintstd(a,N);
    else N->seqprint(a,args);
# if HAVE_PTHREAD
    if (mtx!=NULL) pthread_mutex_unlock(mtx);
# endif
  }
  if (N->argfree!=NULL) N->argfree(args);
  fflush(stdout);
}

/* necklaces with fixed content */

static
void FCNecklace_in(unsigned t, unsigned p, unsigned s,
                   neck_t *N,
                   unsigned *restrict a, unsigned *restrict run,
                   cell_t *avail, int *head, void *args
# if HAVE_PTHREAD
                   ,pthread_mutex_t *mtx
# endif
                   )
{
  int j;
  unsigned s2;

  if (N->num[N->k] == N->n-t+1) {
    if ((N->num[N->k]==run[t-p]) && (N->n%p == 0)) strprint(a,N,args
# if HAVE_PTHREAD
                                                            ,mtx
# endif
                                                            );
    else if (N->num[N->k]>run[t-p]) strprint(a,N,args
# if HAVE_PTHREAD
                                             ,mtx
# endif
                                             );
  }
  else if (N->num[1]!=N->n-t+1) {
    j=*head;
    s2=s;
    while(j>=(int)a[t-p]) {
      run[s]=t-s;
      a[t]=(unsigned)j;

      N->num[j]--;
      if (N->num[j]==0) cellremove(avail,j,head);

      if (j!=(int)(N->k))  s2=t+1;
      if (j==(int)a[t-p])
        FCNecklace_in(t+1,p,s2,N,a,run,avail,head,args
# if HAVE_PTHREAD
                      ,mtx
# endif
                      );
      else
        FCNecklace_in(t+1,t,s2,N,a,run,avail,head,args
# if HAVE_PTHREAD
                      ,mtx
# endif
                      );

      if (N->num[j]==0) celladd(avail,N->k,j,head);
      N->num[j]++;

      j=avail[j].next;
    }
    a[t]=N->k;
  }
}

/** @endcond */

/**
 * @brief Generate fixed content necklaces.
 *
 * Generates fixed content quaternary necklaces. The user includes boolean checks,
 * memory allocation and deallocation methods, and printing methods. These are
 * called for every generated necklace.
 *
 * @param[in] N string length
 * @param[in] args user provided methods to be called on generated necklaces
 * @param[in,out] mtx dynamic mtx guarding stdout
 */
void FCNecklace(neck_t *N, void *args
# if HAVE_PTHREAD
                ,pthread_mutex_t *mtx
# endif
                )
{
  int head=(int)N->k;
  unsigned *a=strinit(N);
  unsigned *run=(unsigned*)calloc(N->n+1,sizeof(unsigned));
  cell_t *avail=cellinit(N->k);

  N->num[1]--;
  if (N->num[1]==0) cellremove(avail,1,&head);
  FCNecklace_in(2,1,2,N,a,run,avail,&head,args
# if HAVE_PTHREAD
                ,mtx
# endif
                );

  free(avail);
  free(run);
  free(a);
}

/* bracelets with fixed content */

/** @cond */

typedef struct {
  unsigned s, v;
} elem_t;

typedef struct {
  unsigned nb;
  elem_t *elems;
} block_t;

static inline
void updaterunlength(unsigned v, block_t *B)
{
  if (B->elems[B->nb].s==v) B->elems[B->nb].v++;
  else {
    B->nb++;
    B->elems[B->nb].v=1;
    B->elems[B->nb].s=v;
  }
}

static inline
void restorerunlength(block_t *B)
{
  if (B->elems[B->nb].v==1) B->nb--;
  else B->elems[B->nb].v--;
}

static inline
block_t *blockinit(unsigned n)
{
  block_t *B=(block_t*)malloc(sizeof(block_t));
  B->elems=(elem_t*)calloc(n+1,sizeof(elem_t));
  B->nb=0;
  return B;
}

static inline
void blockfree(block_t *B)
{
  if (B->elems!=NULL) free(B->elems);
}

static
int checkrev(block_t *B)
{
  unsigned j=1;
  while (B->elems[j].v==B->elems[B->nb-j+1].v &&
         B->elems[j].s==B->elems[B->nb-j+1].s &&
         j<=B->nb/2) j++;
  if (j>B->nb/2) return 0;
  if (B->elems[j].s<B->elems[B->nb-j+1].s) return 1;
  if (B->elems[j].s>B->elems[B->nb-j+1].s) return -1;
  if (B->elems[j].v<B->elems[B->nb-j+1].v &&
      B->elems[j+1].s<B->elems[B->nb-j+1].s) return 1;
  if (B->elems[j].v>B->elems[B->nb-j+1].v &&
      B->elems[j].s<B->elems[B->nb-j].s) return 1;
  return -1;
}

static
void FCBracelet_in(unsigned t, unsigned p, unsigned r,
                   unsigned z, unsigned b, bool RS,
                   neck_t *N, void *args, unsigned *restrict a,
                   unsigned *restrict run, cell_t *avail,
                   int *head, block_t *B
# if HAVE_PTHREAD
                   ,pthread_mutex_t *mtx
# endif
                   )
{
  int j,c;
  unsigned z2,p2;

  if (t-1>(N->n-r)/2+r) {
    if (a[t-1]>a[N->n-t+2+r]) RS=false;
    else if (a[t-1]<a[N->n-t+2+r]) RS=true;
  }

  if (N->num[N->k]==N->n-t+1) {
    if (N->num[N->k]>run[t-p]) p=N->n;
    if (N->num[N->k]>0 &&
        t!=r+1 &&
        B->elems[b+1].s == N->k && B->elems[b+1].v > N->num[N->k])
      RS=true;
    if (N->num[N->k]>0 && t!=r+1 &&
        (B->elems[b+1].s != N->k || B->elems[b+1].v < N->num[N->k]))
      RS=false;
    if ((RS==false) && (N->n%p == 0)) strprint(a,N,args
# if HAVE_PTHREAD
                                               ,mtx
# endif
                                               );
  }
  else if (N->num[1]!=N->n-t+1) {
    j=*head;
    while(j>=(int)a[t-p]) {
      run[z] = t-z;
      updaterunlength((unsigned)j,B);
      N->num[j]--;
      if (N->num[j] == 0) cellremove(avail,j,head);
      a[t]=(unsigned)j;
      z2=z;
      if (j!=(int)N->k) z2=t+1;
      p2=p;
      if (j!=(int)a[t-p]) p2=t;
      c=checkrev(B);
      if (c==0) FCBracelet_in(t+1,p2,t,z2,B->nb,false,
                              N,args,a,run,avail,head,B
# if HAVE_PTHREAD
                              ,mtx
# endif
                              );
      if (c==1) FCBracelet_in(t+1,p2,r,z2,b,RS,
                              N,args,a,run,avail,head,B
# if HAVE_PTHREAD
                              ,mtx
# endif
                              );
      if (N->num[j]==0) celladd(avail,N->k,j,head);
      N->num[j]++;
      restorerunlength(B);
      j = avail[j].next;
    }
    a[t] = N->k;
  }
}

/** @endcond */

/**
 * @brief Generate fixed content bracelets.
 *
 * Generates fixed content quaternary bracelets. The user includes boolean checks,
 * memory allocation and deallocation methods, and printing methods. These are
 * called for every generated bracelet.
 *
 * @param[in] N string length
 * @param[in] args user provided methods to be called on generated bracelet
 * @param[in,out] mtx dynamic mtx guarding stdout
 */
void FCBracelet(neck_t *N, void *args
# if HAVE_PTHREAD
                ,pthread_mutex_t *mtx
# endif
                )
{
  int head=(int)N->k;
  unsigned *a=strinit(N);
  unsigned *run=(unsigned*)calloc(N->n+1,sizeof(unsigned));
  cell_t *avail=cellinit(N->k);
  block_t *B=blockinit(N->n);
  updaterunlength(1,B);

  N->num[1]--;
  if (N->num[1]==0) cellremove(avail,1,&head);
  FCBracelet_in(2,1,1,2,1,false,N,args,a,run,avail,&head,B
# if HAVE_PTHREAD
                ,mtx
# endif
                );

  blockfree(B);
  free(B);
  free(avail);
  free(run);
  free(a);
}

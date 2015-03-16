
#define MAX(x,y) (((x) > (y) ? (x) : (y)))
#define MIN(x,y) (((x) < (y) ? (x) : (y)))
#define SORT_NAME int
#define SORT_TYPE int
#define SORT_CMP(x, y) ((x) - (y))
#define SORT_CMP_A(a,b) SORT_CMP(*(a),*(b))

#ifndef CLZ
#ifdef __GNUC__
#define CLZ __builtin_clzll
#else

static int clzll(uint64_t);

/* adapted from Hacker's Delight */
static int clzll(uint64_t x) {
  int n;

  if (x == 0) {
    return 64;
  }

  n = 0;

  if (x <= 0x00000000FFFFFFFFL) {
    n = n + 32;
    x = x << 32;
  }

  if (x <= 0x0000FFFFFFFFFFFFL) {
    n = n + 16;
    x = x << 16;
  }

  if (x <= 0x00FFFFFFFFFFFFFFL) {
    n = n + 8;
    x = x << 8;
  }

  if (x <= 0x0FFFFFFFFFFFFFFFL) {
    n = n + 4;
    x = x << 4;
  }

  if (x <= 0x3FFFFFFFFFFFFFFFL) {
    n = n + 2;
    x = x << 2;
  }

  if (x <= 0x7FFFFFFFFFFFFFFFL) {
    n = n + 1;
  }

  return n;
}

#define CLZ clzll
#endif
#endif

static int compute_minrun(const uint64_t);

/* From http://oeis.org/classic/A102549 */
static const uint64_t shell_gaps[48] = {1, 4, 10, 23, 57, 132, 301, 701, 1750, 4376, 10941, 27353, 68383, 170958, 427396, 1068491, 2671228, 6678071, 16695178, 41737946, 104344866, 260862166, 652155416, 1630388541, 4075971353LL, 10189928383LL, 25474820958LL, 63687052396LL, 159217630991LL, 398044077478LL, 995110193696LL, 2487775484241LL, 6219438710603LL, 15548596776508LL, 38871491941271LL, 97178729853178LL, 242946824632946LL, 607367061582366LL, 1518417653955916LL, 3796044134889791LL, 9490110337224478LL, 23725275843061196LL, 59313189607652991LL, 148282974019132478LL, 370707435047831196LL, 926768587619577991LL, 2316921469048944978LL, 5792303672622362446LL};
static inline int compute_minrun(const uint64_t size) {
  const int top_bit = 64 - CLZ(size);
  const int shift = MAX(top_bit, 6) - 6;
  const int minrun = size >> shift;
  const uint64_t mask = (1ULL << shift) - 1;

  if (mask & size) {
    return minrun + 1;
  }

  return minrun;
}

static inline size_t rbnd(size_t len) {
  int k;

  if (len < 16) {
    return 2;
  }

  k = 62 - CLZ(len);
  return 1ULL << ((2 * k) / 3);
}

static __inline int compute_minrun(const uint64_t);
static __inline size_t rbnd(size_t); 
static void BINARY_INSERTION_SORT_START(SORT_TYPE *, const size_t, const size_t);
void BINARY_INSERTION_SORT(SORT_TYPE *, const size_t);
void SELECTION_SORT(SORT_TYPE *, const size_t);
void MERGE_SORT_IN_PLACE_ASWAP(SORT_TYPE *, SORT_TYPE *, size_t);
void MERGE_SORT_IN_PLACE_FRONTMERGE(SORT_TYPE *, size_t , SORT_TYPE *, size_t);
size_t MERGE_SORT_IN_PLACE_BACKMERGE(SORT_TYPE *, size_t, SORT_TYPE * , size_t);
static __inline void REVERSE_ELEMENTS(SORT_TYPE *, int64_t, int64_t);
static int64_t COUNT_RUN(SORT_TYPE *, const uint64_t, const size_t);
static int CHECK_INVARIANT(TIM_SORT_RUN_T *, const int);
static void TIM_SORT_RESIZE(TEMP_STORAGE_T *, const size_t);
static void TIM_SORT_MERGE(SORT_TYPE *, const TIM_SORT_RUN_T *, const int,
                           TEMP_STORAGE_T *)
static int TIM_SORT_COLLAPSE(SORT_TYPE *, TIM_SORT_RUN_T *, int,
                             TEMP_STORAGE_T *, const size_t);
static __inline int PUSH_NEXT(SORT_TYPE *dst,
                              const size_t,
                              TEMP_STORAGE_T *,
                              const uint64_t,
                              TIM_SORT_RUN_T *,
                              uint64_t *,
                              uint64_t *);
void TIM_SORT(SORT_TYPE *, const size_t);
static __inline void HEAP_SIFT_DOWN(SORT_TYPE *, const int64_t, const int64_t);
static __inline void HEAPIFY(SORT_TYPE *, const size_t) ;
void HEAP_SORT(SORT_TYPE *, const size_t);
static __inline void SQRT_SORT_SWAP_1(SORT_TYPE *, SORT_TYPE *);
static __inline void SQRT_SORT_SWAP_N(SORT_TYPE *, SORT_TYPE *, int);
static void SQRT_SORT_MERGE_RIGHT(SORT_TYPE *, int, int, int);
static void SQRT_SORT_MERGE_LEFT_WITH_X_BUF(SORT_TYPE *, int, int, int) ;
static void SQRT_SORT_MERGE_DOWN(SORT_TYPE *, SORT_TYPE *, int, int) ;
static void SQRT_SORT_SMART_MERGE_WITH_X_BUF(SORT_TYPE *, int *, int *, int,
					     int);
static void SQRT_SORT_MERGE_BUFFERS_LEFT_WITH_X_BUF(int *, int, SORT_TYPE *,
						    int, int, int, int);
static void SQRT_SORT_BUILD_BLOCKS(SORT_TYPE *, int , int );
static void SQRT_SORT_SORT_INS(SORT_TYPE *, int );
static void SQRT_SORT_COMBINE_BLOCKS(SORT_TYPE *, int, int, int, int *);
static void SQRT_SORT_COMMON_SORT(SORT_TYPE *, int, SORT_TYPE *, int *);
static void SQRT_SORT(SORT_TYPE *, int);

/* Binary insertion sort, but knowing that the first "start" entries are sorted.  Used in timsort. */
static void BINARY_INSERTION_SORT_START(SORT_TYPE *dst, const size_t start, const size_t size) {
  uint64_t i;

  for (i = start; i < size; i++) {
    int64_t j;
    SORT_TYPE x;
    int64_t location;

    /* If this entry is already correct, just move along */
    if (SORT_CMP(dst[i - 1], dst[i]) <= 0) {
      continue;
    }

    /* Else we need to find the right place, shift everything over, and squeeze in */
    x = dst[i];
    location = BINARY_INSERTION_FIND(dst, x, i);

    for (j = i - 1; j >= location; j--) {
      dst[j + 1] = dst[j];
    }

    dst[location] = x;
  }
}

/* Binary insertion sort */
void BINARY_INSERTION_SORT(SORT_TYPE *dst, const size_t size) {
  /* don't bother sorting an array of size 0 */
  if (size == 0) {
    return;
  }

  BINARY_INSERTION_SORT_START(dst, 1, size);
}

/* Selection sort */
void SELECTION_SORT(SORT_TYPE *dst, const size_t size) {
  /* don't bother sorting an array of size 0 */
  if (size == 0) {
    return;
  }

  uint64_t i;
  uint64_t j;

  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      if (SORT_CMP(dst[j], dst[i]) < 0) {
        SORT_SWAP(dst[i], dst[j]);
      }
    }
  }
}

/* In-place mergesort */
void MERGE_SORT_IN_PLACE_ASWAP(SORT_TYPE * dst1, SORT_TYPE * dst2, size_t len) {
  do {
    SORT_SWAP(*dst1, *dst2);
    dst1++;
    dst2++;
  } while (--len);
}

void MERGE_SORT_IN_PLACE_FRONTMERGE(SORT_TYPE *dst1, size_t l1, SORT_TYPE *dst2, size_t l2) {
  SORT_TYPE *dst0 = dst2 - l1;

  if (SORT_CMP(dst1[l1 - 1], dst2[0]) <= 0) {
    MERGE_SORT_IN_PLACE_ASWAP(dst1, dst0, l1);
    return;
  }

  do {
    while (SORT_CMP(*dst2, *dst1) > 0) {
      SORT_SWAP(*dst1, *dst0);
      dst1++;
      dst0++;

      if (--l1 == 0) {
        return;
      }
    }

    SORT_SWAP(*dst2, *dst0);
    dst2++;
    dst0++;
  } while (--l2);

  do {
    SORT_SWAP(*dst1, *dst0);
    dst1++;
    dst0++;
  } while (--l1);
}

size_t MERGE_SORT_IN_PLACE_BACKMERGE(SORT_TYPE * dst1, size_t l1, SORT_TYPE * dst2, size_t l2) {
  size_t res;
  SORT_TYPE *dst0 = dst2 + l1;

  if (SORT_CMP(dst1[1 - l1], dst2[0]) >= 0) {
    MERGE_SORT_IN_PLACE_ASWAP(dst1 - l1 + 1, dst0 - l1 + 1, l1);
    return l1;
  }

  do {
    while (SORT_CMP(*dst2, *dst1) < 0) {
      SORT_SWAP(*dst1, *dst0);
      dst1--;
      dst0--;

      if (--l1 == 0) {
        return 0;
      }
    }

    SORT_SWAP(*dst2, *dst0);
    dst2--;
    dst0--;
  } while (--l2);

  res = l1;

  do {
    SORT_SWAP(*dst1, *dst0);
    dst1--;
    dst0--;
  } while (--l1);

  return res;
}


/* timsort implementation, based on timsort.txt */

static __inline void REVERSE_ELEMENTS(SORT_TYPE *dst, int64_t start, int64_t end) {
  while (1) {
    if (start >= end) {
      return;
    }

    SORT_SWAP(dst[start], dst[end]);
    start++;
    end--;
  }
}

static int64_t COUNT_RUN(SORT_TYPE *dst, const uint64_t start, const size_t size) {
  uint64_t curr;

  if (size - start == 1) {
    return 1;
  }

  if (start >= size - 2) {
    if (SORT_CMP(dst[size - 2], dst[size - 1]) > 0) {
      SORT_SWAP(dst[size - 2], dst[size - 1]);
    }

    return 2;
  }

  curr = start + 2;

  if (SORT_CMP(dst[start], dst[start + 1]) <= 0) {
    /* increasing run */
    while (1) {
      if (curr == size - 1) {
        break;
      }

      if (SORT_CMP(dst[curr - 1], dst[curr]) > 0) {
        break;
      }

      curr++;
    }

    return curr - start;
  } else {
    /* decreasing run */
    while (1) {
      if (curr == size - 1) {
        break;
      }

      if (SORT_CMP(dst[curr - 1], dst[curr]) <= 0) {
        break;
      }

      curr++;
    }

    /* reverse in-place */
    REVERSE_ELEMENTS(dst, start, curr - 1);
    return curr - start;
  }
}

static int CHECK_INVARIANT(TIM_SORT_RUN_T *stack, const int stack_curr) {
  int64_t A, B, C;

  if (stack_curr < 2) {
    return 1;
  }

  if (stack_curr == 2) {
    const int64_t A1 = stack[stack_curr - 2].length;
    const int64_t B1 = stack[stack_curr - 1].length;

    if (A1 <= B1) {
      return 0;
    }

    return 1;
  }

  A = stack[stack_curr - 3].length;
  B = stack[stack_curr - 2].length;
  C = stack[stack_curr - 1].length;

  if ((A <= B + C) || (B <= C)) {
    return 0;
  }

  return 1;
}

typedef struct {
  size_t alloc;
  SORT_TYPE *storage;
} TEMP_STORAGE_T;

static void TIM_SORT_RESIZE(TEMP_STORAGE_T *store, const size_t new_size) {
  if (store->alloc < new_size) {
    SORT_TYPE *tempstore = (SORT_TYPE *)realloc(store->storage, new_size * sizeof(SORT_TYPE));

    if (tempstore == NULL) {
      fprintf(stderr, "Error allocating temporary storage for tim sort: need %lu bytes",
              sizeof(SORT_TYPE) * new_size);
      exit(1);
    }

    store->storage = tempstore;
    store->alloc = new_size;
  }
}

static void TIM_SORT_MERGE(SORT_TYPE *dst, const TIM_SORT_RUN_T *stack, const int stack_curr,
                           TEMP_STORAGE_T *store) {
  const int64_t A = stack[stack_curr - 2].length;
  const int64_t B = stack[stack_curr - 1].length;
  const int64_t curr = stack[stack_curr - 2].start;
  SORT_TYPE *storage;
  int64_t i, j, k;
  TIM_SORT_RESIZE(store, MIN(A, B));
  storage = store->storage;

  /* left merge */
  if (A < B) {
    memcpy(storage, &dst[curr], A * sizeof(SORT_TYPE));
    i = 0;
    j = curr + A;

    for (k = curr; k < curr + A + B; k++) {
      if ((i < A) && (j < curr + A + B)) {
        if (SORT_CMP(storage[i], dst[j]) <= 0) {
          dst[k] = storage[i++];
        } else {
          dst[k] = dst[j++];
        }
      } else if (i < A) {
        dst[k] = storage[i++];
      } else {
        dst[k] = dst[j++];
      }
    }
  } else {
    /* right merge */
    memcpy(storage, &dst[curr + A], B * sizeof(SORT_TYPE));
    i = B - 1;
    j = curr + A - 1;

    for (k = curr + A + B - 1; k >= curr; k--) {
      if ((i >= 0) && (j >= curr)) {
        if (SORT_CMP(dst[j], storage[i]) > 0) {
          dst[k] = dst[j--];
        } else {
          dst[k] = storage[i--];
        }
      } else if (i >= 0) {
        dst[k] = storage[i--];
      } else {
        dst[k] = dst[j--];
      }
    }
  }
}

static int TIM_SORT_COLLAPSE(SORT_TYPE *dst, TIM_SORT_RUN_T *stack, int stack_curr,
                             TEMP_STORAGE_T *store, const size_t size) {
  while (1) {
    int64_t A, B, C, D;
    int ABC, BCD, BD, CD;

    /* if the stack only has one thing on it, we are done with the collapse */
    if (stack_curr <= 1) {
      break;
    }

    /* if this is the last merge, just do it */
    if ((stack_curr == 2) && (stack[0].length + stack[1].length == size)) {
      TIM_SORT_MERGE(dst, stack, stack_curr, store);
      stack[0].length += stack[1].length;
      stack_curr--;
      break;
    }
    /* check if the invariant is off for a stack of 2 elements */
    else if ((stack_curr == 2) && (stack[0].length <= stack[1].length)) {
      TIM_SORT_MERGE(dst, stack, stack_curr, store);
      stack[0].length += stack[1].length;
      stack_curr--;
      break;
    } else if (stack_curr == 2) {
      break;
    }

    B = stack[stack_curr - 3].length;
    C = stack[stack_curr - 2].length;
    D = stack[stack_curr - 1].length;

    if (stack_curr >= 4) {
      A = stack[stack_curr - 4].length;
      ABC = (A <= B + C);
    } else {
      ABC = 0;
    }

    BCD = (B <= C + D) || ABC;
    CD = (C <= D);
    BD = (B < D);

    /* Both invariants are good */
    if (!BCD && !CD) {
      break;
    }

    /* left merge */
    if (BCD && !CD) {
      TIM_SORT_MERGE(dst, stack, stack_curr - 1, store);
      stack[stack_curr - 3].length += stack[stack_curr - 2].length;
      stack[stack_curr - 2] = stack[stack_curr - 1];
      stack_curr--;
    } else {
      /* right merge */
      TIM_SORT_MERGE(dst, stack, stack_curr, store);
      stack[stack_curr - 2].length += stack[stack_curr - 1].length;
      stack_curr--;
    }
  }

  return stack_curr;
}

static __inline int PUSH_NEXT(SORT_TYPE *dst,
                              const size_t size,
                              TEMP_STORAGE_T *store,
                              const uint64_t minrun,
                              TIM_SORT_RUN_T *run_stack,
                              uint64_t *stack_curr,
                              uint64_t *curr) {
  uint64_t len = COUNT_RUN(dst, *curr, size);
  uint64_t run = minrun;

  if (run < minrun) {
    run = minrun;
  }

  if (run > size - *curr) {
    run = size - *curr;
  }

  if (run > len) {
    BINARY_INSERTION_SORT_START(&dst[*curr], len, run);
    len = run;
  }

  run_stack[*stack_curr].start = *curr;
  run_stack[*stack_curr].length = len;
  (*stack_curr)++;
  *curr += len;

  if (*curr == size) {
    /* finish up */
    while (*stack_curr > 1) {
      TIM_SORT_MERGE(dst, run_stack, *stack_curr, store);
      run_stack[*stack_curr - 2].length += run_stack[*stack_curr - 1].length;
      (*stack_curr)--;
    }

    if (store->storage != NULL) {
      free(store->storage);
      store->storage = NULL;
    }

    return 0;
  }

  return 1;
}

void TIM_SORT(SORT_TYPE *dst, const size_t size) {
  /* don't bother sorting an array of size 0 */
  if (size == 0) {
    return;
  }

  uint64_t minrun;
  TEMP_STORAGE_T _store, *store;
  TIM_SORT_RUN_T run_stack[128];
  uint64_t stack_curr = 0;
  uint64_t curr = 0;

  if (size < 64) {
    BINARY_INSERTION_SORT(dst, size);
    return;
  }

  /* compute the minimum run length */
  minrun = compute_minrun(size);
  /* temporary storage for merges */
  store = &_store;
  store->alloc = 0;
  store->storage = NULL;

  if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
    return;
  }

  if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
    return;
  }

  if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
    return;
  }

  while (1) {
    if (!CHECK_INVARIANT(run_stack, stack_curr)) {
      stack_curr = TIM_SORT_COLLAPSE(dst, run_stack, stack_curr, store, size);
      continue;
    }

    if (!PUSH_NEXT(dst, size, store, minrun, run_stack, &stack_curr, &curr)) {
      return;
    }
  }
}

/* heap sort: based on wikipedia */

static __inline void HEAP_SIFT_DOWN(SORT_TYPE *dst, const int64_t start, const int64_t end) {
  int64_t root = start;

  while ((root << 1) <= end) {
    int64_t child = root << 1;

    if ((child < end) && (SORT_CMP(dst[child], dst[child + 1]) < 0)) {
      child++;
    }

    if (SORT_CMP(dst[root], dst[child]) < 0) {
      SORT_SWAP(dst[root], dst[child]);
      root = child;
    } else {
      return;
    }
  }
}

static __inline void HEAPIFY(SORT_TYPE *dst, const size_t size) {
  int64_t start = size >> 1;

  while (start >= 0) {
    HEAP_SIFT_DOWN(dst, start, size - 1);
    start--;
  }
}

void HEAP_SORT(SORT_TYPE *dst, const size_t size) {
  /* don't bother sorting an array of size 0 */
  if (size == 0) {
    return;
  }

  int64_t end = size - 1;
  HEAPIFY(dst, size);

  while (end > 0) {
    SORT_SWAP(dst[end], dst[0]);
    HEAP_SIFT_DOWN(dst, 0, end - 1);
    end--;
  }
}

/********* Sqrt sorting *********************************/
/*                                                       */
/* (c) 2014 by Andrey Astrelin                           */
/*                                                       */
/*                                                       */
/* Stable sorting that works in O(N*log(N)) worst time   */
/* and uses O(sqrt(N)) extra memory                      */
/*                                                       */
/* Define SORT_TYPE and SORT_CMP                         */
/* and then call SqrtSort() function                     */
/*                                                       */
/*********************************************************/

#define SORT_CMP_A(a,b) SORT_CMP(*(a),*(b))

static __inline void SQRT_SORT_SWAP_1(SORT_TYPE *a, SORT_TYPE *b) {
  SORT_TYPE c = *a;
  *a++ = *b;
  *b++ = c;
}

static __inline void SQRT_SORT_SWAP_N(SORT_TYPE *a, SORT_TYPE *b, int n) {
  while (n--) {
    SQRT_SORT_SWAP_1(a++, b++);
  }
}


static void SQRT_SORT_MERGE_RIGHT(SORT_TYPE *arr, int L1, int L2, int M) {
  int p0 = L1 + L2 + M - 1, p2 = L1 + L2 - 1, p1 = L1 - 1;

  while (p1 >= 0) {
    if (p2 < L1 || SORT_CMP_A(arr + p1, arr + p2) > 0) {
      arr[p0--] = arr[p1--];
    } else {
      arr[p0--] = arr[p2--];
    }
  }

  if (p2 != p0) while (p2 >= L1) {
      arr[p0--] = arr[p2--];
    }
}

/* arr[M..-1] - free, arr[0,L1-1]++arr[L1,L1+L2-1] -> arr[M,M+L1+L2-1] */
static void SQRT_SORT_MERGE_LEFT_WITH_X_BUF(SORT_TYPE *arr, int L1, int L2, int M) {
  int p0 = 0, p1 = L1;
  L2 += L1;

  while (p1 < L2) {
    if (p0 == L1 || SORT_CMP_A(arr + p0, arr + p1) > 0) {
      arr[M++] = arr[p1++];
    } else {
      arr[M++] = arr[p0++];
    }
  }

  if (M != p0) while (p0 < L1) {
      arr[M++] = arr[p0++];
    }
}

/* arr[0,L1-1] ++ arr2[0,L2-1] -> arr[-L1,L2-1],  arr2 is "before" arr1 */
static void SQRT_SORT_MERGE_DOWN(SORT_TYPE *arr, SORT_TYPE *arr2, int L1, int L2) {
  int p0 = 0, p1 = 0, M = -L2;

  while (p1 < L2) {
    if (p0 == L1 || SORT_CMP_A(arr + p0, arr2 + p1) >= 0) {
      arr[M++] = arr2[p1++];
    } else {
      arr[M++] = arr[p0++];
    }
  }

  if (M != p0) while (p0 < L1) {
      arr[M++] = arr[p0++];
    }
}

static void SQRT_SORT_SMART_MERGE_WITH_X_BUF(SORT_TYPE *arr, int *alen1, int *atype, int len2,
    int lkeys) {
  int p0 = -lkeys, p1 = 0, p2 = *alen1, q1 = p2, q2 = p2 + len2;
  int ftype = 1 - *atype; /* 1 if inverted */

  while (p1 < q1 && p2 < q2) {
    if (SORT_CMP_A(arr + p1, arr + p2) - ftype < 0) {
      arr[p0++] = arr[p1++];
    } else {
      arr[p0++] = arr[p2++];
    }
  }

  if (p1 < q1) {
    *alen1 = q1 - p1;

    while (p1 < q1) {
      arr[--q2] = arr[--q1];
    }
  } else {
    *alen1 = q2 - p2;
    *atype = ftype;
  }
}


/*
  arr - starting array. arr[-lblock..-1] - buffer (if havebuf).
  lblock - length of regular blocks. First nblocks are stable sorted by 1st elements and key-coded
  keys - arrays of keys, in same order as blocks. key<midkey means stream A
  nblock2 are regular blocks from stream A. llast is length of last (irregular) block from stream B, that should go before nblock2 blocks.
  llast=0 requires nblock2=0 (no irregular blocks). llast>0, nblock2=0 is possible.
*/
static void SQRT_SORT_MERGE_BUFFERS_LEFT_WITH_X_BUF(int *keys, int midkey, SORT_TYPE *arr,
    int nblock, int lblock, int nblock2, int llast) {
  int l, prest, lrest, frest, pidx, cidx, fnext, plast;

  if (nblock == 0) {
    l = nblock2 * lblock;
    SQRT_SORT_MERGE_LEFT_WITH_X_BUF(arr, l, llast, -lblock);
    return;
  }

  lrest = lblock;
  frest = keys[0] < midkey ? 0 : 1;
  pidx = lblock;

  for (cidx = 1; cidx < nblock; cidx++, pidx += lblock) {
    prest = pidx - lrest;
    fnext = keys[cidx] < midkey ? 0 : 1;

    if (fnext == frest) {
      memcpy(arr + prest - lblock, arr + prest, lrest * sizeof(SORT_TYPE));
      prest = pidx;
      lrest = lblock;
    } else {
      SQRT_SORT_SMART_MERGE_WITH_X_BUF(arr + prest, &lrest, &frest, lblock, lblock);
    }
  }

  prest = pidx - lrest;

  if (llast) {
    plast = pidx + lblock * nblock2;

    if (frest) {
      memcpy(arr + prest - lblock, arr + prest, lrest * sizeof(SORT_TYPE));
      prest = pidx;
      lrest = lblock * nblock2;
      frest = 0;
    } else {
      lrest += lblock * nblock2;
    }

    SQRT_SORT_MERGE_LEFT_WITH_X_BUF(arr + prest, lrest, llast, -lblock);
  } else {
    memcpy(arr + prest - lblock, arr + prest, lrest * sizeof(SORT_TYPE));
  }
}

/*
  build blocks of length K
  input: [-K,-1] elements are buffer
  output: first K elements are buffer, blocks 2*K and last subblock sorted
*/
static void SQRT_SORT_BUILD_BLOCKS(SORT_TYPE *arr, int L, int K) {
  int m, u, h, p0, p1, rest, restk, p;

  for (m = 1; m < L; m += 2) {
    u = 0;

    if (SORT_CMP_A(arr + (m - 1), arr + m) > 0) {
      u = 1;
    }

    arr[m - 3] = arr[m - 1 + u];
    arr[m - 2] = arr[m - u];
  }

  if (L % 2) {
    arr[L - 3] = arr[L - 1];
  }

  arr -= 2;

  for (h = 2; h < K; h *= 2) {
    p0 = 0;
    p1 = L - 2 * h;

    while (p0 <= p1) {
      SQRT_SORT_MERGE_LEFT_WITH_X_BUF(arr + p0, h, h, -h);
      p0 += 2 * h;
    }

    rest = L - p0;

    if (rest > h) {
      SQRT_SORT_MERGE_LEFT_WITH_X_BUF(arr + p0, h, rest - h, -h);
    } else {
      for (; p0 < L; p0++) {
        arr[p0 - h] = arr[p0];
      }
    }

    arr -= h;
  }

  restk = L % (2 * K);
  p = L - restk;

  if (restk <= K) {
    memcpy(arr + p + K, arr + p, restk * sizeof(SORT_TYPE));
  } else {
    SQRT_SORT_MERGE_RIGHT(arr + p, K, restk - K, K);
  }

  while (p > 0) {
    p -= 2 * K;
    SQRT_SORT_MERGE_RIGHT(arr + p, K, K, K);
  }
}


static void SQRT_SORT_SORT_INS(SORT_TYPE *arr, int len) {
  int i, j;

  for (i = 1; i < len; i++) {
    for (j = i - 1; j >= 0 && SORT_CMP_A(arr + (j + 1), arr + j) < 0; j--) {
      SQRT_SORT_SWAP_1(arr + j, arr + (j + 1));
    }
  }
}

/*
  keys are on the left of arr. Blocks of length LL combined. We'll combine them in pairs
  LL and nkeys are powers of 2. (2*LL/lblock) keys are guarantied
*/
static void SQRT_SORT_COMBINE_BLOCKS(SORT_TYPE *arr, int len, int LL, int lblock, int *tags) {
  int M, nkeys, b, NBlk, midkey, lrest, u, i, p, v, kc, nbl2, llast;
  SORT_TYPE *arr1;
  M = len / (2 * LL);
  lrest = len % (2 * LL);
  nkeys = (2 * LL) / lblock;

  if (M == 0) {
    nkeys = (M - 1) / lblock + 1;
  }

  if (lrest <= LL) {
    len -= lrest;
    lrest = 0;
  }

  for (b = 0; b <= M; b++) {
    if (b == M && lrest == 0) {
      break;
    }

    arr1 = arr + b * 2 * LL;
    NBlk = (b == M ? lrest : 2 * LL) / lblock;
    u = NBlk + (b == M ? 1 : 0);

    for (i = 0; i <= u; i++) {
      tags[i] = i;
    }

    midkey = LL / lblock;

    for (u = 1; u < NBlk; u++) {
      p = u - 1;

      for (v = u; v < NBlk; v++) {
        kc = SORT_CMP_A(arr1 + p * lblock, arr1 + v * lblock);

        if (kc > 0 || (kc == 0 && tags[p] > tags[v])) {
          p = v;
        }
      }

      if (p != u - 1) {
        SQRT_SORT_SWAP_N(arr1 + (u - 1)*lblock, arr1 + p * lblock, lblock);
        i = tags[u - 1];
        tags[u - 1] = tags[p];
        tags[p] = i;
      }
    }

    nbl2 = llast = 0;

    if (b == M) {
      llast = lrest % lblock;
    }

    if (llast != 0) {
      while (nbl2 < NBlk && SORT_CMP_A(arr1 + NBlk * lblock, arr1 + (NBlk - nbl2 - 1)*lblock) < 0) {
        nbl2++;
      }
    }

    SQRT_SORT_MERGE_BUFFERS_LEFT_WITH_X_BUF(tags, midkey, arr1, NBlk - nbl2, lblock, nbl2, llast);
  }

  for (p = len; --p >= 0;) {
    arr[p] = arr[p - lblock];
  }
}


static void SQRT_SORT_COMMON_SORT(SORT_TYPE *arr, int Len, SORT_TYPE *extbuf, int *Tags) {
  int lblock, cbuf;

  if (Len < 16) {
    SQRT_SORT_SORT_INS(arr, Len);
    return;
  }

  lblock = 1;

  while (lblock * lblock < Len) {
    lblock *= 2;
  }

  memcpy(extbuf, arr, lblock * sizeof(SORT_TYPE));
  SQRT_SORT_COMMON_SORT(extbuf, lblock, arr, Tags);
  SQRT_SORT_BUILD_BLOCKS(arr + lblock, Len - lblock, lblock);
  cbuf = lblock;

  while (Len > (cbuf *= 2)) {
    SQRT_SORT_COMBINE_BLOCKS(arr + lblock, Len - lblock, cbuf, lblock, Tags);
  }

  SQRT_SORT_MERGE_DOWN(arr + lblock, extbuf, Len - lblock, lblock);
}

static void SQRT_SORT(SORT_TYPE *arr, int Len) {
  int L = 1;
  SORT_TYPE *ExtBuf;
  int *Tags;

  while (L * L < Len) {
    L *= 2;
  }

  int NK = (Len - 1) / L + 2;
  ExtBuf = (SORT_TYPE*)malloc(L * sizeof(SORT_TYPE));

  if (ExtBuf == NULL) {
    return;  /* fail */
  }

  Tags = (int*)malloc(NK * sizeof(int));

  if (Tags == NULL) {
    return;
  }

  SQRT_SORT_COMMON_SORT(arr, Len, ExtBuf, Tags);
  free(Tags);
  free(ExtBuf);
}


#undef SORT_CONCAT
#undef SORT_MAKE_STR1
#undef SORT_MAKE_STR
#undef SORT_NAME
#undef SORT_TYPE
#undef SORT_CMP
#undef TEMP_STORAGE_T
#undef TIM_SORT_RUN_T
#undef PUSH_NEXT
#undef SORT_SWAP
#undef SORT_CONCAT
#undef SORT_MAKE_STR1
#undef SORT_MAKE_STR
#undef BINARY_INSERTION_FIND
#undef BINARY_INSERTION_SORT_START
#undef BINARY_INSERTION_SORT
#undef REVERSE_ELEMENTS
#undef COUNT_RUN
#undef TIM_SORT
#undef TIM_SORT_RESIZE
#undef TIM_SORT_COLLAPSE
#undef TIM_SORT_RUN_T
#undef TEMP_STORAGE_T
#undef MERGE_SORT
#undef MERGE_SORT_IN_PLACE
#undef MERGE_SORT_IN_PLACE_RMERGE
#undef MERGE_SORT_IN_PLACE_BACKMERGE
#undef MERGE_SORT_IN_PLACE_FRONTMERGE
#undef MERGE_SORT_IN_PLACE_ASWAP
#undef GRAIL_SWAP1
#undef REC_STABLE_SORT
#undef GRAIL_REC_MERGE
#undef GRAIL_SORT_DYN_BUFFER
#undef GRAIL_SORT_FIXED_BUFFER
#undef GRAIL_COMMON_SORT
#undef GRAIL_SORT
#undef GRAIL_COMBINE_BLOCKS
#undef GRAIL_LAZY_STABLE_SORT
#undef GRAIL_MERGE_WITHOUT_BUFFER
#undef GRAIL_ROTATE
#undef GRAIL_BIN_SEARCH_LEFT
#undef GRAIL_BUILD_BLOCKS
#undef GRAIL_FIND_KEYS
#undef GRAIL_MERGE_BUFFERS_LEFT_WITH_X_BUF
#undef GRAIL_BIN_SEARCH_RIGHT
#undef GRAIL_MERGE_BUFFERS_LEFT
#undef GRAIL_SMART_MERGE_WITH_X_BUF
#undef GRAIL_MERGE_LEFT_WITH_X_BUF
#undef GRAIL_SMART_MERGE_WITHOUT_BUFFER
#undef GRAIL_SMART_MERGE_WITH_BUFFER
#undef GRAIL_MERGE_RIGHT
#undef GRAIL_MERGE_LEFT
#undef GRAIL_SWAP_N
#undef SQRT_SORT
#undef SQRT_SORT_BUILD_BLOCKS
#undef SQRT_SORT_MERGE_BUFFERS_LEFT_WITH_X_BUF
#undef SQRT_SORT_MERGE_DOWN
#undef SQRT_SORT_MERGE_LEFT_WITH_X_BUF
#undef SQRT_SORT_MERGE_RIGHT
#undef SQRT_SORT_SWAP_N
#undef SQRT_SORT_SWAP_1
#undef SQRT_SORT_SMART_MERGE_WITH_X_BUF
#undef SQRT_SORT_SORT_INS
#undef SQRT_SORT_COMBINE_BLOCKS
#undef SQRT_SORT_COMMON_SORT
#undef SORT_CMP_A

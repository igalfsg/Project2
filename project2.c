#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#define SORT_TYPE int
#define SORT_NAME int
#ifndef SORT_COMMON_H
#define SORT_COMMON_H

#ifndef MAX
#define MAX(x,y) (((x) > (y) ? (x) : (y)))
#endif

#ifndef MIN
#define MIN(x,y) (((x) < (y) ? (x) : (y)))
#endif

static int compute_minrun(const uint64_t);

/* From http://oeis.org/classic/A102549 */
static const uint64_t shell_gaps[48] = {1, 4, 10, 23, 57, 132, 301, 701, 1750, 4376, 10941, 27353, 68383, 170958, 427396, 1068491, 2671228, 6678071, 16695178, 41737946, 104344866, 260862166, 652155416, 1630388541, 4075971353LL, 10189928383LL, 25474820958LL, 63687052396LL, 159217630991LL, 398044077478LL, 995110193696LL, 2487775484241LL, 6219438710603LL, 15548596776508LL, 38871491941271LL, 97178729853178LL, 242946824632946LL, 607367061582366LL, 1518417653955916LL, 3796044134889791LL, 9490110337224478LL, 23725275843061196LL, 59313189607652991LL, 148282974019132478LL, 370707435047831196LL, 926768587619577991LL, 2316921469048944978LL, 5792303672622362446LL};

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

static __inline int compute_minrun(const uint64_t size) {
  const int top_bit = 64 - CLZ(size);
  const int shift = MAX(top_bit, 6) - 6;
  const int minrun = size >> shift;
  const uint64_t mask = (1ULL << shift) - 1;

  if (mask & size) {
    return minrun + 1;
  }

  return minrun;
}

static __inline size_t rbnd(size_t len) {
  int k;

  if (len < 16) {
    return 2;
  }

  k = 62 - CLZ(len);
  return 1ULL << ((2 * k) / 3);
}

#endif /* SORT_COMMON_H */




#ifndef SORT_NAME
#error "Must declare SORT_NAME"
#endif
#ifndef SORT_TYPE
#error "Must declare SORT_TYPE"
#endif
#ifndef SORT_CMP
#define SORT_CMP(x, y) ((x) > (y) ? -1 : ((x) == (y) ? 0 : 1))
#endif
#define SORT_SWAP(x,y) {SORT_TYPE __SORT_SWAP_t = (x); (x) = (y); (y) = __SORT_SWAP_t;}
#define SORT_CONCAT(x, y) x ## _ ## y
#define SORT_MAKE_STR1(x, y) SORT_CONCAT(x,y)
#define SORT_MAKE_STR(x) SORT_MAKE_STR1(SORT_NAME,x)
#define BINARY_INSERTION_FIND SORT_MAKE_STR(binary_insertion_find)
#define BINARY_INSERTION_SORT_START SORT_MAKE_STR(binary_insertion_sort_start)
#define BINARY_INSERTION_SORT SORT_MAKE_STR(binary_insertion_sort)
#define REVERSE_ELEMENTS SORT_MAKE_STR(reverse_elements)
#define COUNT_RUN SORT_MAKE_STR(count_run)
#define CHECK_INVARIANT SORT_MAKE_STR(check_invariant)
#define TIM_SORT SORT_MAKE_STR(tim_sort)
#define TIM_SORT_RESIZE SORT_MAKE_STR(tim_sort_resize)
#define TIM_SORT_MERGE SORT_MAKE_STR(tim_sort_merge)
#define TIM_SORT_COLLAPSE SORT_MAKE_STR(tim_sort_collapse)
#define HEAP_SORT SORT_MAKE_STR(heap_sort)
#define QUICK_SORT SORT_MAKE_STR(quick_sort)
#define MERGE_SORT SORT_MAKE_STR(merge_sort)
#define MERGE_SORT_IN_PLACE SORT_MAKE_STR(merge_sort_in_place)
#define MERGE_SORT_IN_PLACE_RMERGE SORT_MAKE_STR(merge_sort_in_place_rmerge)
#define MERGE_SORT_IN_PLACE_BACKMERGE SORT_MAKE_STR(merge_sort_in_place_backmerge)
#define MERGE_SORT_IN_PLACE_FRONTMERGE SORT_MAKE_STR(merge_sort_in_place_frontmerge)
#define MERGE_SORT_IN_PLACE_ASWAP SORT_MAKE_STR(merge_sort_in_place_aswap)
#define SELECTION_SORT SORT_MAKE_STR(selection_sort)
#define SHELL_SORT SORT_MAKE_STR(shell_sort)
#define QUICK_SORT_PARTITION SORT_MAKE_STR(quick_sort_partition)
#define QUICK_SORT_RECURSIVE SORT_MAKE_STR(quick_sort_recursive)
#define HEAP_SIFT_DOWN SORT_MAKE_STR(heap_sift_down)
#define HEAPIFY SORT_MAKE_STR(heapify)
#define TIM_SORT_RUN_T SORT_MAKE_STR(tim_sort_run_t)
#define TEMP_STORAGE_T SORT_MAKE_STR(temp_storage_t)
#define PUSH_NEXT SORT_MAKE_STR(push_next)
#define GRAIL_SWAP1 SORT_MAKE_STR(grail_swap1)
#define REC_STABLE_SORT SORT_MAKE_STR(rec_stable_sort)
#define GRAIL_REC_MERGE SORT_MAKE_STR(grail_rec_merge)
#define GRAIL_SORT_DYN_BUFFER SORT_MAKE_STR(grail_sort_dyn_buffer)
#define GRAIL_SORT_FIXED_BUFFER SORT_MAKE_STR(grail_sort_fixed_buffer)
#define GRAIL_COMMON_SORT SORT_MAKE_STR(grail_common_sort)
#define GRAIL_SORT SORT_MAKE_STR(grail_sort)
#define GRAIL_COMBINE_BLOCKS SORT_MAKE_STR(grail_combine_blocks)
#define GRAIL_LAZY_STABLE_SORT SORT_MAKE_STR(grail_lazy_stable_sort)
#define GRAIL_MERGE_WITHOUT_BUFFER SORT_MAKE_STR(grail_merge_without_buffer)
#define GRAIL_ROTATE SORT_MAKE_STR(grail_rotate)
#define GRAIL_BIN_SEARCH_LEFT SORT_MAKE_STR(grail_bin_search_left)
#define GRAIL_BUILD_BLOCKS SORT_MAKE_STR(grail_build_blocks)
#define GRAIL_FIND_KEYS SORT_MAKE_STR(grail_find_keys)
#define GRAIL_MERGE_BUFFERS_LEFT_WITH_X_BUF SORT_MAKE_STR(grail_merge_buffers_left_with_x_buf)
#define GRAIL_BIN_SEARCH_RIGHT SORT_MAKE_STR(grail_bin_search_right)
#define GRAIL_MERGE_BUFFERS_LEFT SORT_MAKE_STR(grail_merge_buffers_left)
#define GRAIL_SMART_MERGE_WITH_X_BUF SORT_MAKE_STR(grail_smart_merge_with_x_buf)
#define GRAIL_MERGE_LEFT_WITH_X_BUF SORT_MAKE_STR(grail_merge_left_with_x_buf)
#define GRAIL_SMART_MERGE_WITHOUT_BUFFER SORT_MAKE_STR(grail_smart_merge_without_buffer)
#define GRAIL_SMART_MERGE_WITH_BUFFER SORT_MAKE_STR(grail_smart_merge_with_buffer)
#define GRAIL_MERGE_RIGHT SORT_MAKE_STR(grail_merge_right)
#define GRAIL_MERGE_LEFT SORT_MAKE_STR(grail_merge_left)
#define GRAIL_SWAP_N SORT_MAKE_STR(grail_swap_n)
#define SQRT_SORT SORT_MAKE_STR(sqrt_sort)
#define SQRT_SORT_BUILD_BLOCKS SORT_MAKE_STR(sqrt_sort_build_blocks)
#define SQRT_SORT_MERGE_BUFFERS_LEFT_WITH_X_BUF SORT_MAKE_STR(sqrt_sort_merge_buffers_left_with_x_buf)
#define SQRT_SORT_MERGE_DOWN SORT_MAKE_STR(sqrt_sort_merge_down)
#define SQRT_SORT_MERGE_LEFT_WITH_X_BUF SORT_MAKE_STR(sqrt_sort_merge_left_with_x_buf)
#define SQRT_SORT_MERGE_RIGHT SORT_MAKE_STR(sqrt_sort_merge_right)
#define SQRT_SORT_SWAP_N SORT_MAKE_STR(sqrt_sort_swap_n)
#define SQRT_SORT_SWAP_1 SORT_MAKE_STR(sqrt_sort_swap_1)
#define SQRT_SORT_SMART_MERGE_WITH_X_BUF SORT_MAKE_STR(sqrt_sort_smart_merge_with_x_buf)
#define SQRT_SORT_SORT_INS SORT_MAKE_STR(sqrt_sort_sort_ins)
#define SQRT_SORT_COMBINE_BLOCKS SORT_MAKE_STR(sqrt_sort_combine_blocks)
#define SQRT_SORT_COMMON_SORT SORT_MAKE_STR(sqrt_sort_common_sort)
#ifndef MAX
#define MAX(x,y) (((x) > (y) ? (x) : (y)))
#endif
#ifndef MIN
#define MIN(x,y) (((x) < (y) ? (x) : (y)))
#endif
typedef struct {
uint64_t start;
uint64_t length;
} TIM_SORT_RUN_T;
void SHELL_SORT(SORT_TYPE *dst, const size_t size);
void BINARY_INSERTION_SORT(SORT_TYPE *dst, const size_t size);
void HEAP_SORT(SORT_TYPE *dst, const size_t size);
void QUICK_SORT(SORT_TYPE *dst, const size_t size);
void MERGE_SORT(SORT_TYPE *dst, const size_t size);
void MERGE_SORT_IN_PLACE(SORT_TYPE *dst, const size_t size);
void SELECTION_SORT(SORT_TYPE *dst, const size_t size);
void TIM_SORT(SORT_TYPE *dst, const size_t size);

 int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
/* Shell sort implementation based on Wikipedia article
http://en.wikipedia.org/wiki/Shell_sort
*/
void SHELL_SORT(SORT_TYPE *dst, const size_t size) {
/* don't bother sorting an array of size 0 */
if (size == 0) {
return;
}
/* TODO: binary search to find first gap? */
int inci = 47;
uint64_t inc = shell_gaps[inci];
uint64_t i;
while (inc > (size >> 1)) {
inc = shell_gaps[--inci];
}
while (1) {
for (i = inc; i < size; i++) {
SORT_TYPE temp = dst[i];
uint64_t j = i;
while ((j >= inc) && (SORT_CMP(dst[j - inc], temp) > 0)) {
dst[j] = dst[j - inc];
j -= inc;
}
dst[j] = temp;
}
if (inc == 1) {
break;
}
inc = shell_gaps[--inci];
}
}
/* Function used to do a binary search for binary insertion sort */
static __inline int64_t BINARY_INSERTION_FIND(SORT_TYPE *dst, const SORT_TYPE x,
const size_t size) {
int64_t l, c, r;
SORT_TYPE cx;
l = 0;
r = size - 1;
c = r >> 1;
/* check for out of bounds at the beginning. */
if (SORT_CMP(x, dst[0]) < 0) {
return 0;
} else if (SORT_CMP(x, dst[r]) > 0) {
return r;
}
cx = dst[c];
while (1) {
const int val = SORT_CMP(x, cx);
if (val < 0) {
if (c - l <= 1) {
return c;
}
r = c;
} else { /* allow = for stability. The binary search favors the right. */
if (r - c <= 1) {
return c + 1;
}
l = c;
}
c = l + ((r - l) >> 1);
cx = dst[c];
}
}
/* Binary insertion sort, but knowing that the first "start" entries are sorted. Used in timsort. */
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
/* merge dst[p0..p1) by buffer dst[p1..p1+r) */
void MERGE_SORT_IN_PLACE_RMERGE(SORT_TYPE *dst, size_t len, size_t lp, size_t r) {
size_t i, lq;
int cv;
if (SORT_CMP(dst[lp], dst[lp - 1]) >= 0) {
return;
}
lq = lp;
for (i = 0; i < len; i += r) {
/* select smallest dst[p0+n*r] */
size_t q = i, j;
for (j = lp; j <= lq; j += r) {
cv = SORT_CMP(dst[j], dst[q]);
if (cv == 0) {
cv = SORT_CMP(dst[j + r - 1], dst[q + r - 1]);
}
if (cv < 0) {
q = j;
}
}
if (q != i) {
MERGE_SORT_IN_PLACE_ASWAP(dst + i, dst + q, r); /* swap it with current position */
if (q == lq && q < (len - r)) {
lq += r;
}
}
if (i != 0 && SORT_CMP(dst[i], dst[i - 1]) < 0) {
MERGE_SORT_IN_PLACE_ASWAP(dst + len, dst + i, r); /* swap current position with buffer */
MERGE_SORT_IN_PLACE_BACKMERGE(dst + (len + r - 1), r, dst + (i - 1),
r); /* buffer :merge: dst[i-r..i) -> dst[i-r..i+r) */
}
if (lp == i) {
lp += r;
}
}
}
/* In-place Merge Sort implementation. (c)2012, Andrey Astrelin, astrelin@tochka.ru */
void MERGE_SORT_IN_PLACE(SORT_TYPE *dst, const size_t len) {
/* don't bother sorting an array of size 0 */
if (len == 0) {
return;
}
size_t r = rbnd(len);
size_t lr = (len / r - 1) * r, p, m, q, q1, p0;
SORT_TYPE *dst1 = dst - 1;
if (len < 16) {
BINARY_INSERTION_SORT(dst, len);
return;
}
for (p = 2; p <= lr; p += 2) {
dst1 += 2;
if (SORT_CMP(dst1[0], dst1[-1]) < 0) {
SORT_SWAP(dst1[0], dst1[-1]);
}
if (p & 2) {
continue;
}
m = len - p;
q = 2;
while ((p & q) == 0) {
if (SORT_CMP(dst1[1 - q], dst1[-q]) < 0) {
break;
}
q *= 2;
}
if (p & q) {
continue;
}
if (q < m) {
p0 = len - q;
MERGE_SORT_IN_PLACE_ASWAP(dst + p - q, dst + p0, q);
for (;;) {
q1 = 2 * q;
if ((q1 > m) || (p & q1)) {
break;
}
p0 = len - q1;
MERGE_SORT_IN_PLACE_FRONTMERGE(dst + (p - q1), q, dst + p0 + q, q);
q = q1;
}
MERGE_SORT_IN_PLACE_BACKMERGE(dst + (len - 1), q, dst1 - q, q);
q *= 2;
}
q1 = q;
while (q1 > m) {
q1 /= 2;
}
while ((q & p) == 0) {
q *= 2;
MERGE_SORT_IN_PLACE_RMERGE(dst + (p - q), q, q / 2, q1);
}
}
q1 = 0;
for (q = r; q < lr; q *= 2) {
if ((lr & q) != 0) {
q1 += q;
if (q1 != q) {
MERGE_SORT_IN_PLACE_RMERGE(dst + (lr - q1), q1, q, r);
}
}
}
m = len - lr;
MERGE_SORT_IN_PLACE(dst + lr, m);
MERGE_SORT_IN_PLACE_ASWAP(dst, dst + lr, m);
m += MERGE_SORT_IN_PLACE_BACKMERGE(dst + (m - 1), m, dst + (lr - 1), lr - m);
MERGE_SORT_IN_PLACE(dst, m);
}
/* Standard merge sort */
void MERGE_SORT(SORT_TYPE *dst, const size_t size) {
SORT_TYPE *newdst;
const uint64_t middle = size / 2;
uint64_t out = 0;
uint64_t i = 0;
uint64_t j = middle;
/* don't bother sorting an array of size 0 */
if (size == 0) {
return;
}
if (size < 16) {
BINARY_INSERTION_SORT(dst, size);
return;
}
MERGE_SORT(dst, middle);
MERGE_SORT(&dst[middle], size - middle);
newdst = (SORT_TYPE *) malloc(size * sizeof(SORT_TYPE));
while (out != size) {
if (i < middle) {
if (j < size) {
if (SORT_CMP(dst[i], dst[j]) <= 0) {
newdst[out] = dst[i++];
} else {
newdst[out] = dst[j++];
}
} else {
newdst[out] = dst[i++];
}
} else {
newdst[out] = dst[j++];
}
out++;
}
memcpy(dst, newdst, size * sizeof(SORT_TYPE));
free(newdst);
}
/* Quick sort: based on wikipedia */
static __inline int64_t QUICK_SORT_PARTITION(SORT_TYPE *dst, const int64_t left,
const int64_t right, const int64_t pivot) {
SORT_TYPE value = dst[pivot];
int64_t index = left;
int64_t i;
int all_same = 1;
/* move the pivot to the right */
SORT_SWAP(dst[pivot], dst[right]);
for (i = left; i < right; i++) {
int cmp = SORT_CMP(dst[i], value);
/* check if everything is all the same */
if (cmp != 0) {
all_same &= 0;
}
if (cmp < 0) {
SORT_SWAP(dst[i], dst[index]);
index++;
}
}
SORT_SWAP(dst[right], dst[index]);
/* avoid degenerate case */
if (all_same) {
return -1;
}
return index;
}
static void QUICK_SORT_RECURSIVE(SORT_TYPE *dst, const int64_t left, const int64_t right) {
int64_t pivot;
int64_t new_pivot;
if (right <= left) {
return;
}
if ((right - left + 1) < 16) {
BINARY_INSERTION_SORT(&dst[left], right - left + 1);
return;
}
pivot = left + ((right - left) >> 1);
new_pivot = QUICK_SORT_PARTITION(dst, left, right, pivot);
/* check for partition all equal */
if (new_pivot < 0) {
return;
}
QUICK_SORT_RECURSIVE(dst, left, new_pivot - 1);
QUICK_SORT_RECURSIVE(dst, new_pivot + 1, right);
}
void QUICK_SORT(SORT_TYPE *dst, const size_t size) {
/* don't bother sorting an array of size 0 */
if (size == 0) {
return;
}
QUICK_SORT_RECURSIVE(dst, 0, size - 1);
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
void sort(int *, int );

void sort(int* list, int n){
  int i;
  int wrongs = 0;
  int tempo;
  for(i = 1; i < n; i++){
    if( list[i] < list[i - 1])
      wrongs++;
  }
  if (wrongs > (n - wrongs + 100))
    {
      for( i = 0; i < (n / 2); i++)
	{
	  tempo = list[i];
	  list[i] = list[n - i -1];
	  list[n - i -1] = tempo;
	}
      wrongs = n - wrongs - 1;
    }
  if (wrongs == 0)
      return;
  if (wrongs <(n / 4) ||(wrongs > (n - wrongs + 100) )){
    int_tim_sort(list, n);
         for( i = 0; i < (n / 2); i++)
	{
	  tempo = list[i];
	  list[i] = list[n - i -1];
	  list[n - i -1] = tempo;
	}
    return;
  }
  qsort(list, n, sizeof(int), cmpfunc);
}

void printArray(int * array, int size){
  
  int i;
  printf("[ ");
  for (i = 0; i < size; i++)
    printf("%d \n", array[i]);
  printf("]\n");
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
/* #undef GRAIL_REC_MERGE */
/* #undef GRAIL_SORT_DYN_BUFFER */
/* #undef GRAIL_SORT_FIXED_BUFFER */
/* #undef GRAIL_COMMON_SORT */
/* #undef GRAIL_SORT */
/* #undef GRAIL_COMBINE_BLOCKS */
/* #undef GRAIL_LAZY_STABLE_SORT */
/* #undef GRAIL_MERGE_WITHOUT_BUFFER */
/* #undef GRAIL_ROTATE */
/* #undef GRAIL_BIN_SEARCH_LEFT */
/* #undef GRAIL_BUILD_BLOCKS */
/* #undef GRAIL_FIND_KEYS */
/* #undef GRAIL_MERGE_BUFFERS_LEFT_WITH_X_BUF */
/* #undef GRAIL_BIN_SEARCH_RIGHT */
/* #undef GRAIL_MERGE_BUFFERS_LEFT */
/* #undef GRAIL_SMART_MERGE_WITH_X_BUF */
/* #undef GRAIL_MERGE_LEFT_WITH_X_BUF */
/* #undef GRAIL_SMART_MERGE_WITHOUT_BUFFER */
/* #undef GRAIL_SMART_MERGE_WITH_BUFFER */
/* #undef GRAIL_MERGE_RIGHT */
/* #undef GRAIL_MERGE_LEFT */
/* #undef GRAIL_SWAP_N */
/* #undef SQRT_SORT */
/* #undef SQRT_SORT_BUILD_BLOCKS */
/* #undef SQRT_SORT_MERGE_BUFFERS_LEFT_WITH_X_BUF */
/* #undef SQRT_SORT_MERGE_DOWN */
/* #undef SQRT_SORT_MERGE_LEFT_WITH_X_BUF */
/* #undef SQRT_SORT_MERGE_RIGHT */
/* #undef SQRT_SORT_SWAP_N */
/* #undef SQRT_SORT_SWAP_1 */
/* #undef SQRT_SORT_SMART_MERGE_WITH_X_BUF */
/* #undef SQRT_SORT_SORT_INS */
/* #undef SQRT_SORT_COMBINE_BLOCKS */
/* #undef SQRT_SORT_COMMON_SORT */
/* #undef SORT_CMP_A */




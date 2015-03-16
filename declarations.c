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

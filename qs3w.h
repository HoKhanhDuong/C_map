#ifndef	QUICK_SORT_3WAY
#define	QUICK_SORT_3WAY
int compare(void const *x, void const *y);
void swap(void *x, void *y, int size);
void qsort3way(void *a, int num, size_t size, int (*compare)(void const *, void const *));

#endif

/*
 * mm.c
 *
 * This is the only file you should modify.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/*
 * If NEXT_FIT defined use next fit search, else use first fit search 
 */
//#define NEXT_FIT

/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* word size (bytes) */  
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE (1<<12)  /* initial heap size (bytes) */
#define OVERHEAD 8       /* overhead of header and footer (bytes) */

//#define MINPAYLOAD 24
#define ALIGN_SIZE (ALIGN(sizeof(size_t)))
#define ALIGN_PTR(p)  ((size_t*)(((char*)(p)) - ALIGN_SIZE))

#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p */
/* NB: this code calls a 32-bit quantity a word */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))  

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)  
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE((char*)(bp) - WSIZE))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE((char*)(bp) - DSIZE))

#define NEXT_FREE_BLKP(bp) (*(char**)(bp + DSIZE))
#define PREV_FREE_BLKP(bp) (*(char**)(bp))

#define ALIGNMENT 8
#define ALIGN(size) (((size_t)(size) + (ALIGNMENT-1)) & ~0x7)
/* $end mallocmacros */

/* function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkblock(void *bp);
static void add_to_front(void *bp);
static void remove_from_list(void *bp);

/* Global variables */
static char* heap_listp = 0;  /* pointer to first block */  
static char* free_list_ptr = 0;  /* pointer to first free block */

/*
 * Initialize: return -1 on error, 0 on success.
 */
int mm_init(void) 
{
    if ((heap_listp = mem_sbrk(8 * WSIZE)) == NULL) {
        return -1;
    }
    
    PUT(heap_listp, 0);
    PUT(heap_listp+WSIZE, PACK(OVERHEAD, 1));  /* prologue header */ 
    PUT(heap_listp+DSIZE, PACK(OVERHEAD, 1));  /* prologue footer */ 
    PUT(heap_listp+WSIZE+DSIZE, PACK(0, 1));   /* epilogue header */
    heap_listp += DSIZE;
    free_list_ptr = heap_listp + DSIZE;

    if (extend_heap(CHUNKSIZE / WSIZE) == NULL) {
        return -1;
    }
    return 0;
}

/*
 * malloc
 */
void *mm_malloc (size_t size) {
    size_t asize;
    size_t extendsize;
    char* bp;
    asize = MAX(ALIGN(size) + DSIZE, WSIZE * 8);
    
    if (heap_listp == 0) {
        mm_init();
    }
    
    if (size <= 0) {
        return NULL;
    }
    
    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

/*
 * free
 */
void mm_free (void *ptr) {

    if (ptr == NULL) {
        return;
    }
    
    size_t size = GET_SIZE(HDRP(ptr));
    
    
    if (heap_listp == 0) {
        mm_init();
    }
    
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * realloc - you may want to look at mm-naive.c
 */
void *mm_realloc(void *oldptr, size_t size) {
    size_t oldsize;
    void *newptr;

    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(oldptr);
        return NULL;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(oldptr == NULL) {
        return mm_malloc(size);
    }
    newptr = mm_malloc(size);

    /* If realloc() fails the original block is left untouched  */
    if(!newptr) {
        return NULL;
    }

    /* Copy the old data. */
    oldsize = *ALIGN_PTR(oldptr);
    if(size < oldsize) oldsize = size;
    memcpy(newptr, oldptr, oldsize);

    /* Free the old block. */
    mm_free(oldptr);

    return newptr;
}

/*
 * calloc - you may want to look at mm-naive.c
 * This function is not tested by mdriver, but it is
 * needed to run the traces.
 */
void *mm_calloc (size_t nmemb, size_t size) {
    size_t bytes = nmemb * size;
    void *newptr;

    newptr = mm_malloc(bytes);
    memset(newptr, 0, bytes);

    return newptr;
}

/* 
 * checkheap - Minimal check of the heap for consistency 
 */
void mm_checkheap(int verbose)
{
    char *bp = heap_listp;

    if (verbose)
        printf("Heap (%p):\n", heap_listp);

    int s = GET_SIZE(HDRP(heap_listp));
    if (s != DSIZE)
     {
        printf("size: %d\n", s);
        printblock(bp);
        printf("Bad prologue header\n");
     }
    
    if (!GET_ALLOC(HDRP(heap_listp)))
    {
        printf("alloc\n");
        printblock(bp);
        printf("Bad prologue header\n");
     }
    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        printf("in heaplist\n");
        if (verbose) 
            printblock(bp);
        checkblock(bp);
    }

    if (verbose)
        printblock(bp);

    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
        printf("Bad epilogue header\n");
}


static void printblock(void *bp) 
{
    size_t hsize, halloc, fsize, falloc;
    //printf("problem\n");
    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp)); 
    //printf("problem\n");
    fsize = GET_SIZE(FTRP(bp));
    //printf("problem\n");
    falloc = GET_ALLOC(FTRP(bp));  
    //printf("problem\n");
    if (hsize == 0) {
        printf("%p: EOL\n", bp);
        return;
    }

    printf("%p: header: [%p:%c] footer: [%p:%c]\n", bp, 
      (void*) hsize, (halloc ? 'a' : 'f'), 
      (void*) fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
{
    if ((size_t)bp % 8)
        printf("Error: %p is not doubleword aligned\n", bp);
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
        printf("Error: header does not match footer\n");
}


static void *extend_heap(size_t words) 
{
    char *bp;
    size_t size;
    void *return_ptr;

  /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if (size < CHUNKSIZE) {
        size = CHUNKSIZE;
    }
    if ((long)(bp = mem_sbrk(size)) == -1) 
        return NULL;

  /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* new epilogue header */

  /* Coalesce if the previous block was free */
    return_ptr = coalesce(bp);
    //mm_checkheap(1);
    return return_ptr;
}


static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));   
    //printf("inside place (1)\n"); 
    /* Split */
    if ((csize - asize) >= (WSIZE * 8)) { 
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        remove_from_list(bp);
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
        coalesce(bp);
    } else { 
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
        remove_from_list(bp);
    }
}

/*
 * Find_Fit
 */
static void* find_fit(size_t asize) {
    void *bp;

    for (bp = free_list_ptr; GET_ALLOC(HDRP(bp)) == 0; bp = NEXT_FREE_BLKP(bp)) {
        if (asize <= GET_SIZE(HDRP(bp))) {
            //printf("found one!\n");
            return bp;
        }
    }
    
    return NULL;
}

/*
 * Add to free list
 */
static void add_to_front(void *bp) { 
    NEXT_FREE_BLKP(bp) = free_list_ptr;
    PREV_FREE_BLKP(free_list_ptr) = bp;
    PREV_FREE_BLKP(bp) = NULL;
    free_list_ptr = bp;
}

/*
 * Remove from free list
 */
static void remove_from_list(void *bp) {
    if (PREV_FREE_BLKP(bp)) {
        //printf("is it here?\n");
        NEXT_FREE_BLKP(PREV_FREE_BLKP(bp)) = NEXT_FREE_BLKP(bp);
        //printf("that worked?\n");
    } else {
        free_list_ptr = NEXT_FREE_BLKP(bp);
    }
    PREV_FREE_BLKP(NEXT_FREE_BLKP(bp)) = PREV_FREE_BLKP(bp);
}

/*
 * coalesce - boundary tag coalescing. Return ptr to coalesced block
 */
static void *coalesce(void *bp) 
{
    /* if prev block is allocated and prev block is itself, just take itself */
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))) || PREV_BLKP(bp) == bp;
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {
        add_to_front(bp);
        return bp;
    } else if (prev_alloc && !next_alloc) {      /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        // remove next free from LIFO
        remove_from_list(NEXT_BLKP(bp));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size,0));
        add_to_front(bp);
        return bp;
    } else if (!prev_alloc && next_alloc) {      /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        // remove prev free from LIFO
        bp = PREV_BLKP(bp);
        remove_from_list(bp);
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        add_to_front(bp);
        return bp;
    } else {                                     /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        // remove prev and next free from LIFO
        remove_from_list(PREV_BLKP(bp));
        remove_from_list(NEXT_BLKP(bp));
        bp = PREV_BLKP(bp);
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        add_to_front(bp);
        return bp;
    }
    // add bp to LIFO
    add_to_front(bp);
    return bp;
}

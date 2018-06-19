#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 
 * Declare line struct to hold the valid flag, tag bits, and time_stamp 
 * of each line of the cache.
 *
 * Using a time_stamp for LRU was an idea I got from Omar Salemohamed who took
 * this class Fall '16, and is currently working on a Data Visualization
 * project with me.
 */
typedef struct 
{
    int valid;
    int tag;
    int time_stamp;
} line;

/* 
 * Declare summ struct to hold the hits, misses, and evictions
 * of each line of the cache.
 */
typedef struct
{
    int hit_count;
    int miss_count;
    int eviction_count;
} summ;

/*
 * A cache has numerous sets with lines associated to the associativity
 * of the cache. Thus, this cache must be two dimensional, accounting for
 * the value of E.
 */
line** create_cache(int s, int E, int b) 
{
    int S = pow(2, s);
    line** cache = malloc(S * sizeof(line*));
    for (int i = 0; i < S; i++) {
        cache[i] = malloc(E * sizeof(line));
        for (int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].time_stamp = 0;
        }
    }
    return cache;
}

/*
 * Function to free cache at all the points that data has been malloc'd.
 */
void free_cache(line** cache, int s)
{
    int S = pow(2, s);
    for (int i = 0; i < S; i++) {
        free(cache[i]);
    }
    free(cache);
}

/*
 * Function to declare a summ.
 */
summ* create_summ() 
{
    summ* summary = malloc(sizeof(summ));
    summary->hit_count = 0;
    summary->miss_count = 0;
    summary->eviction_count = 0;
    return summary;
}

/*
 * Return the LRU index.
 */
int min_time_index(line* set, int E) {
    int min = set[0].time_stamp;
    int min_index = 0;
    for (int i = 0; i < E; i++) {
        if (set[i].time_stamp < min) {
            min = set[i].time_stamp;
            min_index = i;
        }
    }
    return min_index;
}

/*
 * Function to grab the set index bits of a given address.
 */

int fetch_set_bits(int b, int s, long long int addr) {
    int mask = 1;
    for (int i = 0; i < (s - 1); i++) {
        mask = (mask << 1) + 1;
    }
    mask = mask << b;
    return (addr & mask) >> b;
}

/*
 * Function to grab the tag bits of a given address.
 */
int fetch_tag_bits(int b, int s, long long int addr) {
    int mask = 1;
    for (int i = 0; i < (b + s) - 1; i++) {
        mask = (mask << 1) + 1;
    }
    mask = mask << (b + s);
    return (addr & mask) >> (b + s);
}

/*
 * Update cache with a new input.
 */
void update_cache(line*** cache, int* clock, summ** summary, 
                 int address, int s, int E, int b) {
    // Increment Timer
    (*clock)++;

     // Local Variables
    long int set_bits = fetch_set_bits(b, s, address);
    long int tag_bits = fetch_tag_bits(b, s, address);

    line* set = (*cache)[set_bits];
    int hit_flag = 0;

     // Check for hit
    for (int i = 0; i < E; i++) {
         // If line is valid and has the same tag, its a hit
        if (set[i].tag == tag_bits && set[i].valid == 1) {
            hit_flag = 1;
            (*summary)->hit_count++;
            set[i].time_stamp = *clock;
            break;
        }
    }
              
    // If not a hit
    if (hit_flag == 0) {
        // If it's not a hit, it's a miss
        (*summary)->miss_count++;
        // If a line is open, place in the line
        int is_full = 1;
        for (int i = 0; i < E; i++) {
            if (set[i].valid == 0) {
                is_full = 0;
                set[i].valid = 1;
                set[i].tag = tag_bits;
                set[i].time_stamp = *clock;
                break;
            }
        }
        // If lines are all valid, there must be an eviction
        // Evict LRU line
        if (is_full) {
            (*summary)->eviction_count++;
            int min_index = min_time_index(set, E);
            set[min_index].tag = tag_bits;
            set[min_index].time_stamp = *clock;
        }
    } 
}

/*
 * How I figured out how to read line-by-line.
 * https://gsamaras.wordpress.com/code/read-file-line-by-line-in-c-and-c/
 */
int main(int argc, char* argv[])
{
    summ* summary = create_summ();
    int clock = 0;

    int s = 0;
    int E = 0;
    int b = 0;
    char* file_name = NULL;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                switch(argv[i][1]) {
                    case 's':
                        s = atoi(argv[i + 1]);
                        break;
                    case 'E':
                        E = atoi(argv[i + 1]);
                        break;
                    case 'b':
                        b = atoi(argv[i + 1]);
                        break;
                    case 't':
                        file_name = argv[i + 1];
                        break;
                    default:
                        break;
                }
            }
        }
    }
    
    line** cache = create_cache(s, E, b);    
    FILE* f = fopen(file_name, "r");
    char buf[20];
    while (fgets(buf, sizeof(buf), f) != NULL) {
        // Parsing Lines
        buf[strlen(buf) - 1] = '\0';
    
        char operation;
        long long int address;
        int size;
        sscanf(buf, " %c %llx,%d", &operation, &address, &size);
       
        // As per piazza, store, load, and modify work roughly the same way
        // Ignoring 'I' (instruction load) calls
        switch (operation) {
            case 'I':
                continue;
                break;
            case 'M':
                summary->hit_count++;
                break;
            default:
                break;
        }
        
        // Update the cache
        update_cache(&cache, &clock, &summary, address, s, E, b); 
    }
    fclose(f);
    free_cache(cache, s);
    printSummary(summary->hit_count, 
                 summary->miss_count, 
                 summary->eviction_count);
    return 0;
}

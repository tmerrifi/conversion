#ifndef ARRAY_CACHE_H
#define ARRAY_CACHE_H

#define CACHE_SIZE 32
#define CACHE_DEAD_ENTRY 0xDEADDEADUL

struct array_entry{
    void * ptr;
    unsigned long index;
};

struct array_cache{
    struct array_entry * array;
    size_t count;
    size_t size;
    int sets;
    int set_associativity;
};

static inline void array_cache_init(struct array_cache * cache, size_t size, int set_associativity){
    int i;
    cache->array = kmalloc(size * sizeof(struct array_entry), GFP_KERNEL);
    for (i=0;i<size;i++) {
	cache->array[i].ptr=NULL;
	cache->array[i].index=CACHE_DEAD_ENTRY;
    }
    cache->count = 0;
    cache->size=size;
    BUG_ON(set_associativity>cache->size);
    BUG_ON(cache->size%set_associativity!=0);
    cache->sets=size/set_associativity;
    cache->set_associativity=set_associativity;
}

static inline int __get_set_start_index(struct array_cache * cache, unsigned long index){
    return ((((index * 1099511628211UL) >> 16) % cache->sets) * cache->set_associativity);
}

static inline void * __array_cache_lookup(struct array_cache * cache, unsigned long index, int * available_index){
    int i;
    int start_index=__get_set_start_index(cache,index);
    for (i=start_index;i<start_index+cache->set_associativity;i++) {
	if (cache->array[i].index == index) {
	    return cache->array[i].ptr;
	}
	else if (cache->array[i].index == CACHE_DEAD_ENTRY && available_index && *available_index == -1) {
	    //its available, set the available_index in case the caller cares
	    *available_index = i;
	}
    }
    return NULL;
}

static inline void * array_cache_lookup(struct array_cache *cache, unsigned long index) {
    return __array_cache_lookup(cache, index, NULL);
}

static inline void * array_cache_delete(struct array_cache * cache, unsigned long index){
    int i;
    int start_index=__get_set_start_index(cache,index);

    for (i=start_index;i<start_index+cache->set_associativity;i++) {
	if (cache->array[i].index == index) {
	    void * returnPtr;
	    returnPtr=cache->array[i].ptr;
	    cache->array[i].ptr=NULL;
	    cache->array[i].index = CACHE_DEAD_ENTRY;
	    cache->count--;
//	    printk(KERN_INFO "delete .....%d %lu\n", 
	//	   i, cache->array[i].index);
	    return returnPtr;
	}
    }
    return NULL;
}

static inline int array_cache_insert(struct array_cache * cache, unsigned long index, void * ptr){

    int available_index = -1;
    int return_val = 0;

    //printk(KERN_INFO " get start index... %d, index %lu\n", __get_set_start_index(cache, index), index);

    if (__array_cache_lookup(cache, index, &available_index) == NULL && available_index >=0) {
	return_val = 1;
	cache->array[available_index].index = index;
	cache->array[available_index].ptr=ptr;
	cache->count++;  
    }
    else {
	available_index = CACHE_DEAD_ENTRY;
    }
    
    return return_val;
}

#endif
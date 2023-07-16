#include "./hw4-library/memlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "./hw4-library/mm.h"

struct memory_region{
  size_t * start;
  size_t * end;
};

struct memory_region global_mem;
struct memory_region stack_mem;

void walk_region_and_mark(void* start, void* end);

// PROVIDED BY US (DO NOT CHANGE)
// ------------------------------
// grabbing the address and size of the global memory region from proc 
void init_global_range(){
  int next = 0;
  char file[100];
  char * line=NULL;
  size_t n=0;
  size_t read_bytes=0;
  size_t start, end;


  sprintf(file, "/proc/%d/maps", getpid());
  FILE * mapfile  = fopen(file, "r");
  if (mapfile==NULL){
    perror("opening maps file failed\n");
    exit(-1);
  }

  int counter=0;
  while ((read_bytes = getline(&line, &n, mapfile)) != -1) {
    // .data of hw4 executable
    if (strstr(line, "hw4") != NULL && strstr(line,"rw-p")){
      sscanf(line, "%lx-%lx", &start, &end);
      global_mem.start = (void*) start;
      global_mem.end = (void*) end;
      break;
    }

  }
  fclose(mapfile);
}

// marking related operations

int is_marked(unsigned int * chunk) {
  return ((*chunk) & 0x2) > 0;
}

void mark(unsigned int * chunk) {
  (*chunk)|=0x2;
}

void clear_mark(unsigned int * chunk) {
  (*chunk)&=(~0x2);
}

// chunk related operations

#define chunk_size(c)  ((*((unsigned int *)c))& ~(unsigned int)7 ) 
void* next_chunk(void* c) { 
  if(chunk_size(c) == 0) {
    fprintf(stderr,"Panic, chunk is of zero size.\n");
  }
  if((c+chunk_size(c)) < mem_heap_hi())
    return ((void*)c+chunk_size(c));
  else
    return 0;
}

int in_use(void *c) { 
  return *(unsigned int *)(c) & 0x1;
}

// FOR YOU TO IMPLEMENT
// --------------------
// the actual collection code
void sweep() {
  void * chunk = mem_heap_lo();
  // TODO
  // check chunk size and if chunk less than heap high
  while( chunk < mem_heap_hi() && chunk_size(chunk) ){
    if(is_marked(chunk)){
      // if it's marked, unmark chunk
      clear_mark(chunk);
    } else if(in_use(chunk)){
      // if its in use, free the memory
      mm_free(chunk + 4);
    }
    chunk = next_chunk(chunk);
  }
  return;
}

// determine if what "looks" like a pointer actually points to an 
// in use block in the heap. if so, return a pointer to its header 
void * is_pointer(void * ptr) {

  // Here's a helpful print statement that shows some available memory operations and working with pointers
  //printf("checking for pointeryness of %p between %p and %p\n",ptr, mem_heap_lo(), mem_heap_hi());
  // TODO

  // transvers chunks from mem_heap_lo() to mem_heap_hi()
  // initially check if pointer is within range
  if( ( ptr <= mem_heap_hi() ) && ( ptr >= mem_heap_lo() ) ) {
    void *i = mem_heap_lo();
    // assign variable to not change global 
    while( chunk_size(i) ) {
      if( ( in_use(i) ) && ( ptr < i + chunk_size(i) ) ){
        // if chunk size valid and chunk in use, return header
        return i;
      }
      i = next_chunk(i);
    }
  }
  // if pointer not in use or chunk size not valid return NULL
  return NULL;
}

// walk through memory specified by function arguments and mark
// each chunk
void walk_region_and_mark(void* start, void* end) {
  
  //fprintf(stderr, "walking %p - %p\n", start, end);
  
  // tranverse from start address till end
  while( start < end ){
    // assign variable with suitable indicator to dereference by type
    void *temp = is_pointer(*(void**) start);
    // if pointer is NULL skip and go to next heap memory slot, continue while loop
    if ( temp == NULL ) {
      // next heap (byte size 8)
      start += 8;
      continue;
    }
    // if pointer is not marked, mark it
    if ( !is_marked( temp ) ) {
      mark( temp );
      // recursion on next memory in the stack + end depending on different chunk size
      walk_region_and_mark( temp + 4, temp + chunk_size( temp ) );
    }
    // in case temp is not NULL and it is marked, just go to next memory in heap
    start += 8;
  }
}

// PROVIDED BY US (DO NOT CHANGE)
// ------------------------------
// standard initialization 

void init_gc() {
  size_t stack_var;
  init_global_range();
  // since the heap grows down, the end is found first
  stack_mem.end=(size_t *)&stack_var;
}

void gc() {
  size_t stack_var;
  // grows down, so start is a lower address
  stack_mem.start=(size_t *)&stack_var;
  // walk memory regions
  walk_region_and_mark(global_mem.start,global_mem.end);
  walk_region_and_mark(stack_mem.start,stack_mem.end);
  sweep();
}

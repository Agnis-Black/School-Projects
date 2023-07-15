#include<stdio.h>

typedef int data_t;
typedef struct {
	long len; 
	data_t *data; 
} vec_rec, *vec_ptr;
 
/* Return length of vector */ 
long vec_length(vec_ptr v) { 
	return v->len; 
}

int get_vec_element(vec_ptr v, long index, data_t *dest){ 
	if (index < 0 || index >= v->len) 
		return 0; 
	*dest = v->data[index]; 
	return 1;
}

/*Return pointer to start of vector data*/ 
data_t *get_vec_start(vec_ptr v) { 
	return v->data; 
}

// Adding main function so it would run on putty
int main(){
	/* unoptimized - Assume vec_ptr u, v, p are all of equal length */ 
	void hw8_func(vec_ptr u, vec_ptr v, vec_ptr p, data_t *dest) { 
		long i; 
		data_t udata; 
		data_t vdata; 
		data_t pdata;

		// Creating stable variables for concatenation and loop condition 
		data_t total;
		long size = vec_length(u);

		// Unrolling 6 times
		long limit = (size/6)*6;
		for (i = 0; i < limit; i=i+6){

	        	udata += u->data[i];
        		vdata += v->data[i];
        		pdata += p->data[i];
        
        		udata += u->data[i+1];
        		vdata += v->data[i+1];
        		pdata += p->data[i+1];
        
       			udata += u->data[i+2];
        		vdata += v->data[i+2];
        		pdata += p->data[i+2];
        
        		udata += u->data[i+3];
        		vdata += v->data[i+3];
        		pdata += p->data[i+3];
        
        		udata += u->data[i+4];
        		vdata += v->data[i+4];
        		pdata += p->data[i+4];
        
        		udata += u->data[i+5];
        		vdata += v->data[i+5];
        		pdata += p->data[i+5];

			total = total + udata + vdata + pdata;
		}

		// this is handling the leftovers; 
    		for (i = limit; i < size; i++){
        		udata += u->data[i];
        		vdata += v->data[i];
        		pdata += p->data[i];
			total = total + udata + vdata + pdata;
		}		
		// code motion
		*dest = total;
	}
	return 0;
}
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>



typedef struct {
    int i;
    int** src1;
    int** src2;
    int** dst;
    int len;
}matmul_arg_t;

double wtime()
{

	static int sec =-1;
	struct timeval tv;
	gettimeofday(&tv , NULL);
	if(sec<0) sec = tv.tv_sec;

	return (tv.tv_sec - sec) + 1.0e-6*tv.tv_usec;

}


void *mat_mul_th_kernel(void *arg)
{
   int 		j,k, result;
   matmul_arg_t	*parg = (matmul_arg_t*)arg;
   int 		i=parg->i;
   int		**src1 = parg->src1;
   int		**src2 = parg->src2;
   int		**dst = parg->dst;
   int  	len = parg->len;
 
   for (j=0; j<len; j++){
	result = 0;
	for(k=0; k <len;k++){
		result  += src1[i][k] * src2[k][j];
	}
	dst[i][j]=result;  
    }
}

void *mat_add_th_kernel(void *arg)
{
   int 		j,k, result;
   matmul_arg_t	*parg = (matmul_arg_t*)arg;
   int 		i=parg->i;
   int		**src1 = parg->src1;
   int		**src2 = parg->src2;
   int		**dst = parg->dst;
   int 		len = parg->len; 
	for (j=0; j<len; j++){
		dst[i][j] = src1[i][j] + src2[i][j];
}
}

void *mat_sub_th_kernel(void *arg)
{
   int 		j,k, result;
   matmul_arg_t	*parg = (matmul_arg_t*)arg;
   int 		i=parg->i;
   int		**src1 = parg->src1;
   int		**src2 = parg->src2;
   int		**dst = parg->dst;
   int 		len = parg->len; 
	for (j=0; j<len; j++){
		dst[i][j] = src1[i][j] - src2[i][j];
}
}

int mat_mul_th(int **src1, int** src2, int** dst, int len)
{
	int 			i,j,k,res;
	matmul_arg_t		*arg;
	pthread_t		*a_thread;
	void 			*thread_result;

	a_thread = (pthread_t*)malloc(sizeof(pthread_t) * len);

	
	for(i=0; i<len; i++){
		arg= (matmul_arg_t*)malloc(sizeof(matmul_arg_t));
		arg->i = i;
		arg->src1= src1;
		arg->src2 = src2;
		arg->dst = dst;
		arg->len = len;
		
		res = pthread_create(a_thread+i, NULL, mat_mul_th_kernel, (void*)arg);

		if(res!=0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);			

		}
	}

	for( i=0; i <len; i++){
		res= pthread_join(a_thread[i], &thread_result);
		if(res!=0){
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	return 0;

}

int mat_add_th(int **src1, int** src2, int** dst, int len)
{
	int 			i,j,k,res;
	matmul_arg_t		*arg;
	pthread_t		*a_thread;
	void 			*thread_result;

	a_thread = (pthread_t*)malloc(sizeof(pthread_t) * len);

	
	for(i=0; i<len; i++){
		arg= (matmul_arg_t*)malloc(sizeof(matmul_arg_t));
		arg->i = i;
		arg->src1= src1;
		arg->src2 = src2;
		arg->dst = dst;
		arg->len = len;
		
		res = pthread_create(a_thread+i, NULL, mat_add_th_kernel, (void*)arg);

		if(res!=0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);			

		}
	}

	for( i=0; i <len; i++){
		res= pthread_join(a_thread[i], &thread_result);
		if(res!=0){
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	return 0;

}


int mat_sub_th(int **src1, int** src2, int** dst, int len)
{
	int 			i,j,k,res;
	matmul_arg_t		*arg;
	pthread_t		*a_thread;
	void 			*thread_result;

	a_thread = (pthread_t*)malloc(sizeof(pthread_t) * len);

	
	for(i=0; i<len; i++){
		arg= (matmul_arg_t*)malloc(sizeof(matmul_arg_t));
		arg->i = i;
		arg->src1= src1;
		arg->src2 = src2;
		arg->dst = dst;
		arg->len = len;
		
		res = pthread_create(a_thread+i, NULL, mat_sub_th_kernel, (void*)arg);

		if(res!=0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);			

		}
	}

	for( i=0; i <len; i++){
		res= pthread_join(a_thread[i], &thread_result);
		if(res!=0){
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	return 0;

}

int mat_mul(int **, int **, int **, int);
int mat_add(int **, int **, int **, int);
int mat_sub(int **, int **, int **, int);
void print_matrix(int **, char*, int);

int main(int argc, char** argv)
{
int **a;
int **b;
int **c;
int i, j, k;
int len;
//clock_t start, stop;
double start, stop;

if(argc ==2){
	len = atoi(argv[1]);
} else{
	len = 10;
}

a = (int**)malloc(len * sizeof(int*));
b = (int**)malloc(len * sizeof(int*));
c = (int**)malloc(len * sizeof(int*));

for(i = 0; i<len; i++){
	a[i] = (int*)malloc(len * sizeof(int));
	b[i] = (int*)malloc(len * sizeof(int));
	c[i] = (int*)malloc(len * sizeof(int));
}


srandom((unsigned int)time(NULL));
for(i = 0; i<len; i++){	// i (Row)
	for( j = 0; j<len; j++){	// j (Column)
		a[i][j] = random()%10;
		b[i][j] = random()%10;
	}
}
/*
//1. ADD
start = wtime();
mat_add(a, b, c, len);
stop = wtime();
printf("[ADD] Processing time: %f\n", stop-start);


start = wtime();
mat_add_th(a, b, c, len);
stop = wtime();
printf("[ADD with Thread] Processing time: %f\n", stop-start);


//print_matrix(c, "C", len);

//2. SUB
start = wtime();
mat_sub(a, b, c, len);
stop = wtime();
printf("[SUB] Processing time: %f\n", stop-start);


start = wtime();
mat_sub_th(a, b, c, len);
stop = wtime();
printf("[SUB with Thread] Processing time: %f\n", stop-start);


*/


//3. MULTI
start = wtime();
mat_mul(a, b, c, len);
stop = wtime();
printf("[MUL] Processing time: %f\n", stop-start);

start = wtime();
mat_mul_th(a, b, c, len);
stop = wtime();
printf("[MUL with Thread] Processing time: %f\n", stop-start);

//print_matrix(c, "C", len);

return 0;

}

int mat_mul(int** src1, int** src2, int** dst, int len){

int i, j, k;

for(i = 0; i<len; i++){
	for(j = 0; j<len; j++){
		//c[i][j] = a[i][j] + b[i][j] //add matrix
		dst[i][j]= 0;
		for(k = 0; k<len; k++){
			dst[i][j] += src1[i][k] * src2[k][j];
		}
	}
}
}

int mat_add(int** src1, int** src2, int** dst, int len){

int i, j ,k;

for(i = 0; i<len; i++){
	for(j =0; j<len; j++){
		dst[i][j] = src1[i][j] + src2[i][j];
	}
}
}

int mat_sub(int** src1, int** src2, int** dst, int len){

int i, j , k;

for(i = 0; i<len; i++){
	for(j = 0; j<len; j++){
		dst[i][j] = src1[i][j] - src2[i][j];
	}
}
}
void print_matrix(int** matrix, char* name, int len){

printf("==%s matrix ==========\n",name);
for(int i = 0; i<len; i++){
	for(int j = 0; j<len; j++){
		printf("%d ", matrix[i][j]);
	}
printf("\n");
}
}

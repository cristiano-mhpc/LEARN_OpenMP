#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double f(double);

void Trap(double a, double b, int n, double* global_result_p); /*thread function*/

int main(int argc, char* argv[]){

	/*WE'll store our result in a global_result: */

	double global_result = 0.0;
	double  a,b;    /*left and right endpoints*/
	int     n;      /*total number of trapezoids*/

	int     thread_count; 

	thread_count  = strtol(arg[1], NULL, 10); 
	printf("Enter a, b, and n \n");
	scanf("%lf %lf %d" , &a, &b, &n);

#	pragma omp parallel num_threads(thread_count)
	Trap(a, b, n &global_result);


	printf("With n = %d trapezoids, our estimate \n", n);
	printf("of the integral from %f to %f = %. 14e \n", a,b, global_result);


	return 0; 
}/*main*/


void Trap(double a, double b, int n, double* global_result_p){
	double h, x, my_result;
	double local_a, local_b;
	int i, local_n;
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	h = (b-a)/n;
	local_n = n/thread_count;
	local_a = a + my_rank*local_n*h;
	local_b = local_a + my_rank*local_n*h;
	my_result = (f(local_a) + f(local_b))/2.0; 

	for(i = 1; i < n ; i++){
		x = local_a + i*h;
		myresult += f(x);
	}

	my_result = my_result*h;

#	pragma omp critical 
	*global_result_p += my_result; 

}/*Trap*/

double f(double x){
	return x*x + 4; 
}



/*In this version, I am using parallel for directive instead of explicit parallezation.*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double Trap(double a, double d, int n ); /*thread function*/

double f(double);

int main(int argc, char* argv[]){

	if (argc != 5){
		printf("argument count must be equal to 5!");
		exit(1);
	}

	/*Get number of threads from command line*/ 
	int thread_count = strtol(argv[1], NULL, 10);
	int n = strtol(argv[2], NULL, 10);
	double a = strtol(argv[3], NULL, 10);
        double b = strtol(argv[4], NULL, 10);
	
	if (n%thread_count != 0){
		printf("thread_count started is not a multiple of total number of trapezoid\n");
		exit(1);
	}
	double h  = (b-a)/n;

	double approx = (f(a)+f(b))/2.0;//a variable with a shared scope; 

#	pragma omp parallel for num_threads(thread_count) reduction(+: approx)
	for (int i = 1; i < n; i++){
		approx += f(a + i*h);
	}
	
	approx = h*approx;

	printf("With n = %d trapezoids, our estimate\n", n);
	printf("of the integral from %f to %f = %.14e\n", a, b, approx);


	return 0; 

}/*main*/


double f(double x){
       	return x*x + 4.0;
}

double Trap(double a, double b, int n){
	
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	double my_result, x;

	double h = (b-a)/n;

	int local_n = n/thread_count;//we assume n is a multiple of thread_count

	double local_a = a + my_rank*h*local_n;
	double local_b = local_a + local_n*h;

	my_result = (f(local_a) + f(local_b))/2.0;

	//each tread will perform a trap_sum in its own domain
	for (int i = 1; i < local_n; ++i ){
		x = local_a + i*h;
		my_result += f(x);
	}

	my_result = h*my_result;

	return my_result;
	
}/*Trap*/

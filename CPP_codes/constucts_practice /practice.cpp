#include <iostream>
#include <stdlib>

void init(){
#	pragma omp single copyprivate(x,y)
	{
		scanf("%f %f", &x, &y);
	}


int main(){

	float x, y;

#	pragma omp threadprivate(x,y)

	init();

	return 0;

}




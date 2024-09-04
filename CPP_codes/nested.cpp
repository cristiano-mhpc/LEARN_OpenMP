//file nested.cpp
/*Here we test the */

#include <iostream>
#include <stdlib.h>
#include <omp.h> 

using namespace std;

void testPar(int curLvl, int maxLvl)
{
	if (curLvl == maxLvl)
		return;
	else
	{
#		pragma omp parallel 
		{	/*We use the default numthreads = 4 = available cores.*/
#			pragma omp single
			{  
				/*To be executed by a single thread*/
				cout << "Parallel at lvl " << curLvl << " with thread team of " << omp_get_num_threads() << endl;
				testPar(curLvl + 1, maxLvl);
			}
		}
	}

}



int main(int argc, char** argv)
{
	int nestedLvl = atoi (argv[1]); //read the parameter to use in omp_set_max_active_levels from command line

	//sets the maximum number of active nested parallel regions
	omp_set_max_active_levels (nestedLvl);

	testPar(0, nestedLvl + 1);  // recursive execution for a nestedLvl + 1 depth 

	return 0;
}

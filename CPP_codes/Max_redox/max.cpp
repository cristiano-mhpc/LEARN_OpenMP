#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv)
{
	
	int num_elem = atoi(argv[1]);

	int N = omp_get_max_threads();

	num_elem = (num_elem/N) * N;

	vector<int>  data(num_elem);

	for (int i = 0; i < num_elem; i++ )
	{
		data[i] = rand() % 10000;
	}

	int max_value = data[0];
#	pragma omp parallel reduction(max: max_value)
	{
		for (int i = 1; i < num_elem; i++)
		{
			if (max_value < data[i])
			{
				max_value = data[i];
			}

		}

	}

	cout << "Maximum is: " << max_value << endl; 

	cout << "Using max_element function : " << *max_element(data.begin(), data.end()) << endl;


	return 0;

}

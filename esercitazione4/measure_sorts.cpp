#include "randfiller.hpp"
#include "timecounter.h"
#include "sort_function.hpp"
#include <iostream>
#include <vector>
#include <algorithm>




int main() {
	/* inizializzo la variabile sorted perche voglio controllare che ogni algoritmo abbia funzionato */
	bool sorted=true;
	randfiller rf; /* instantiate a randfiller */
	/* vettori in cui salvo i tempi per dimensione */
	std::vector<double> time4dim_bs;
	time4dim_bs.resize(12);
	std::vector<double> time4dim_is;
	time4dim_is.resize(12);
	std::vector<double> time4dim_ss;
	time4dim_ss.resize(12);
	std::vector<double> time4dim_sort;
	time4dim_sort.resize(12);
	/* creo il vettore con le dimensioni richieste */
	std::vector<int> vi_dimtest;
	vi_dimtest.resize(12);
	vi_dimtest[0]=4;
	for (int i=1; i<vi_dimtest.size();i++) {
		vi_dimtest[i]=vi_dimtest[i-1]*2;
	}
	/* valuto tutti i tempi di ogni algoritmo */
	timecounter tc;
	for (int i=0; i<vi_dimtest.size();i++) {
		int dimension=vi_dimtest[i];
		std::vector<int> vi_test;
		vi_test.resize(dimension);
		rf.fill(vi_test, -10000,10000);
		/* tempo di bubblesort */
		std::vector<int> vi_test_bs=vi_test;
		tc.tic();
		bubblesort(vi_test_bs);
		double secs_bs=tc.toc();
		time4dim_bs[i]=secs_bs;
		if (not is_sorted(vi_test_bs)){
			sorted=false;
			}
		/* tempo di insertionsort */
		std::vector<int> vi_test_is=vi_test;
		tc.tic();
		bubblesort(vi_test_is);
		double secs_is=tc.toc();
		time4dim_is[i]=secs_is;
		if (not is_sorted(vi_test_is)){
			sorted=false;
			}
		/* tempo di selectionsort */
		std::vector<int> vi_test_ss=vi_test;
		tc.tic();
		bubblesort(vi_test_ss);
		double secs_ss=tc.toc();
		time4dim_ss[i]=secs_ss;
		if (not is_sorted(vi_test_ss)){
			sorted=false;
			}
		/* tempo di libreria sort */
		std::vector<int> vi_test_sort=vi_test;
		tc.tic();
		std::sort( vi_test_sort.begin(), vi_test_sort.end() );
		double secs_sort=tc.toc();
		time4dim_sort[i]=secs_sort;
		if (not is_sorted(vi_test_sort)){
			sorted=false;
			}
		/* se tutti gli algoritmi hanno ordinato stampo i tempi */
		if (sorted) {
			std::cout << "Elapsed time to order a random vector of dimension " << dimension << "\n";
			std::cout << "Bubblesort: " << secs_bs << " secs\n";
			std::cout << "Insertionsort: " << secs_is << " secs\n"; 
			std::cout << "Selectionsort: " << secs_ss << " secs\n";
			std::cout << "Sort(libreria): " << secs_sort << " secs\n\n";
		}
	}
	for (int j=0;j<time4dim_bs.size();j++) {
		std::cout << vi_dimtest[j] << " bubblesort: " << time4dim_bs[j] << "; ";
		std::cout << vi_dimtest[j] << " insertionsort: " << time4dim_is[j] << "; ";
		std::cout << vi_dimtest[j] << " selectionsort: " << time4dim_ss[j] << "; ";
		std::cout << vi_dimtest[j] << " sort library: " << time4dim_sort[j] << "\n";
	}
}
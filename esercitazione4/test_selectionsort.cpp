/* test selectionsort */
#include "sort_function.hpp"
#include "randfiller.hpp"
#include "timecounter.h"
#include <iostream>
#include <vector>
#include <string>


int main(void)
{		
	bool sorted=true;
    randfiller rf; /* instantiate a randfiller */
    std::vector<int> vi_dim;
    vi_dim.resize(100); /* ho iniziato con 10 e poi aumento a 100 */
    rf.fill(vi_dim, 1, 1000); /* use it on vectors */
	for (int i=0; i<vi_dim.size();i++) {
		int dimension=vi_dim[i];
		for (int j=0; j<100; j++) {
			std::vector<int> vi_test;
			vi_test.resize(dimension);
			rf.fill(vi_test, -10000,10000);
			selectionsort(vi_test);
			if (not is_sorted(vi_test)){
				sorted=false;
			}
		}
	
	}
	
	
	/* verifico se funziona anche con le stringhe */
	std::vector<std::string> vi_string;
	bool string_sorted = false;
	vi_string = {"ciao", "sono cosimo", "voglio testare se", "l'algoritmo funziona anche", "con", "le stringhe", "questa qua sarà", "quindi", "la mia", "stringa di prova"};
    bubblesort(vi_string);
	if (is_sorted(vi_string)) {
		string_sorted = true;
		std::cout << "Ha ordinato anche la stringa\n";
		for (int i=0; i<vi_string.size(); i++) {
			std::cout << vi_string[i] << "\n";
		}
	}
	
	
	/* controllo se l'algoritmo ha funzionato */
    if (sorted && string_sorted) {
		std::cout << "L'algoritmo selectionsort ha funzionato" << "\n";
		return EXIT_SUCCESS;
	}
    else {
		std::cout << "L'algoritmo selectionsort non ha funzionato \n";
		return EXIT_FAILURE;
	}
}
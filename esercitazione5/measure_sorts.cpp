#include "randfiller.hpp"
#include "timecounter.h"
#include "sort_function.hpp"
#include <iostream>
#include <vector>
#include <algorithm>




int main() {
	// IN QUESTA PARTE DI CODICE TRATTO LA RICERCA DELLA DIM N PER CUI QUICKSORT DIVENTI PIU VELOCE DI INSERTIONSORT
	
	// Questa parte è anche stata testata in modalità release, misurando tempi su vettori di dimensione fino a 300, 
	// ho poi nuovamente reinserito 100 per un run piu veloce del codice, ho commentato laddove 100-->300 
	
	randfiller rf; /* instantiate a randfiller */
	/* vettori in cui salvo i tempi per dimensione */
	/* tutti questi 300 */
	std::vector<double> time4dim_bs;
	time4dim_bs.resize(100);
	std::vector<double> time4dim_is;
	time4dim_is.resize(100);
	std::vector<double> time4dim_ss;
	time4dim_ss.resize(100);
	std::vector<double> time4dim_sort;
	time4dim_sort.resize(100);
	std::vector<double> time4dim_mergesort;
	time4dim_mergesort.resize(100);
	std::vector<double> time4dim_quicksort;
	time4dim_quicksort.resize(100);
	std::vector<double> time4dim_my_quicksort;
	time4dim_my_quicksort.resize(100);
	
	
	
	/* creo il vettore con dimensioni da 1 a 100 richieste */
	std::vector<int> vi_dimtest;
	/* questo 300 */
	vi_dimtest.resize(100);
	vi_dimtest[0]=2;
	for (int i=1; i<vi_dimtest.size();i++) {
		vi_dimtest[i]=vi_dimtest[i-1]+1;
	}
	/* creo 100 vettori per ognuna delle 100 dimensioni(da 2 a 101) e le metto in un vettore di vettori */
	/* quello che creo è una matrice contenente vettori (vettore di vettore di vettori) */
	std::vector<std::vector<std::vector<int>>> vecvec_test;
	/* questo 300 */
	vecvec_test.resize(100);
	for (int i=0; i<vi_dimtest.size();i++) {
		int dimension=vi_dimtest[i];
		vecvec_test[i].resize(100);
		for (int j=0; j<100; j++) {
			std::vector<int> vi_test;
			vi_test.resize(dimension);
			rf.fill(vi_test, -10000,10000);
			vecvec_test[i][j]=vi_test;
			}
	}
			
			
	/* valuto tutti i tempi di ogni algoritmo */
	timecounter tc;
	for (int i=0; i<vi_dimtest.size();i++) {
		int dimension=vi_dimtest[i];
		/* tempo di bubblesort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_bs=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			bubblesort(vecvec_test_bs[i][j]);
		}
		double secs_bs=tc.toc();
		time4dim_bs[i]=secs_bs/100;
		/* tempo di insertionsort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_is=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			insertionsort(vecvec_test_is[i][j]);
		}
		double secs_is=tc.toc();
		time4dim_is[i]=secs_is/100;
		/* tempo di selectionsort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_ss=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			selectionsort(vecvec_test_ss[i][j]);
		}
		double secs_ss=tc.toc();
		time4dim_ss[i]=secs_ss/100;
		
		/* tempo di libereria mergesort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_mergesort=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			mergesort(vecvec_test_mergesort[i][j],0, dimension-1);
		}
		double secs_mergesort=tc.toc();
		time4dim_mergesort[i]=secs_mergesort/100;
		
		/* tempo di libereria quicksort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_quicksort=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			quicksort(vecvec_test_quicksort[i][j],0, dimension-1);
		}
		double secs_quicksort=tc.toc();
		time4dim_quicksort[i]=secs_quicksort/100;
		
		/* tempo di libreria sort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_sort=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			std::sort(vecvec_test_sort[i][j].begin(), vecvec_test_sort[i][j].end());
		}
		double secs_sort=tc.toc();
		time4dim_sort[i]=secs_sort/100;
		
		/* tempo di libreria my_quicksort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_my_quicksort=vecvec_test;
		tc.tic();
		for (int j=0; j<100; j++) {
			my_quicksort(vecvec_test_quicksort[i][j],0, dimension-1);
		}
		double secs_my_quicksort=tc.toc();
		time4dim_my_quicksort[i]=secs_my_quicksort/100;
	}
	
	/* Questo controllo viene fatto solo su quicksort perche dal grafico dei tempi ho constatato che mergesort diventa più veloce dei quadratici per dimensioni superiori a 100 */
	/* controllo quando quicksort è piu veloce degli algoritmi quadratici */
	bool svolta=false;
	int k=0;
	int counter=0;
	int n_star;
	/* questo 300 */
	while (svolta==false && counter<=100) {
		std::cout << std::fixed << std::setprecision(10);
		std::cout << "N: " <<counter+2 << "\n";
		std::cout << "quicksort: " << time4dim_quicksort[counter]<< "  BS " << time4dim_bs[counter] << " IS " << time4dim_is[counter] << " SS " << time4dim_ss[counter] << "\n";
		std::cout << "mergesort: " << time4dim_mergesort[counter]<< "  BS " << time4dim_bs[counter] << " IS " << time4dim_is[counter] << " SS " << time4dim_ss[counter] << "\n";
		
		/* se quicksort è più veloce dei quadratici allora aumento k) */
		if (time4dim_quicksort[counter]<time4dim_bs[counter] && time4dim_quicksort[counter]<time4dim_is[counter] && time4dim_quicksort[counter]<time4dim_ss[counter] /*&&  time4dim_mergesort[i]<time4dim_bs[i] && time4dim_mergesort[i]<time4dim_is[i] && time4dim_mergesort[i]<time4dim_ss[i]*/) {
			std::cout << "vale per: " << counter+2 << "\n\n";
			if (k==0) {
				n_star=counter+2;
			}
			k+=1;
			if (k==5) {
				svolta=true;
			}
		}
		else {
			k=0;
		}
		counter++;
	}
	if (svolta==true) {
		std::cout << "RISPOSTA FINALE: L'algoritmo quicksort diventa più veloce di BS, SS, IS dalla dimensione " << n_star << "\n";
	}
	else {
		std::cout << "Non è stata trovata una dimensione inferiore a 100 per cui quicksort risulta più veloci di BS, SS, IS.\n";
	}
	
	
	// IN QUESTA PARTE DI CODICE INVECE MISURO I TEMPI DI CIASCUN ALGORITMO SU DIM DA 4 A 8192 PER POI FARNE IL GRAFICO
	
	
	/* vettori in cui salvo i tempi per dimensione */
	std::cout << "\n\n\n\n" << "Adesso stampo i tempi di ordinamento di dimensioni che vanno da 2^2 a 2^13" << "\n\n";
	std::vector<double> time4dim_bs_2;
	time4dim_bs_2.resize(12);
	std::vector<double> time4dim_is_2;
	time4dim_is_2.resize(12);
	std::vector<double> time4dim_ss_2;
	time4dim_ss_2.resize(12);
	std::vector<double> time4dim_sort_2;
	time4dim_sort_2.resize(12);
	std::vector<double> time4dim_mergesort_2;
	time4dim_mergesort_2.resize(12);
	std::vector<double> time4dim_quicksort_2;
	time4dim_quicksort_2.resize(12);
	std::vector<double> time4dim_my_quicksort_2;
	time4dim_my_quicksort_2.resize(12);
	
	
	
	/* creo il vettore con le dimensioni richieste */
	std::vector<int> vi_dimtest_2;
	vi_dimtest_2.resize(12);
	vi_dimtest_2[0]=4;
	for (int i=1; i<vi_dimtest_2.size();i++) {
		vi_dimtest_2[i]=vi_dimtest_2[i-1]*2;
	}
	/* creo 100 vettori per ognuna delle 12 dimensioni e le metto in un vettore di vettori */
	std::vector<std::vector<std::vector<int>>> vecvec_test_2;
	vecvec_test_2.resize(12);
	for (int i=0; i<vi_dimtest_2.size();i++) {
		int dimension=vi_dimtest_2[i];
		vecvec_test_2[i].resize(100);
		for (int j=0; j<100; j++) {
			std::vector<int> vi_test;
			vi_test.resize(dimension);
			rf.fill(vi_test, -10000,10000);
			vecvec_test_2[i][j]=vi_test;
			}
	}
			
			
	/* valuto tutti i tempi di ogni algoritmo */
	for (int i=0; i<vi_dimtest_2.size();i++) {
		int dimension=vi_dimtest_2[i];
		/* tempo di bubblesort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_bs=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			bubblesort(vecvec_test_2_bs[i][j]);
		}
		double secs_bs=tc.toc();
		time4dim_bs_2[i]=secs_bs/100;
		/* tempo di insertionsort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_is=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			insertionsort(vecvec_test_2_is[i][j]);
		}
		double secs_is=tc.toc();
		time4dim_is_2[i]=secs_is/100;
		/* tempo di selectionsort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_ss=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			selectionsort(vecvec_test_2_ss[i][j]);
		}
		double secs_ss=tc.toc();
		time4dim_ss_2[i]=secs_ss/100;
		
		/* tempo di libereria mergesort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_mergesort=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			mergesort(vecvec_test_2_mergesort[i][j],0, dimension-1);
		}
		double secs_mergesort=tc.toc();
		time4dim_mergesort_2[i]=secs_mergesort/100;
		
		/* tempo di libereria quicksort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_quicksort=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			quicksort(vecvec_test_2_quicksort[i][j],0, dimension-1);
		}
		double secs_quicksort=tc.toc();
		time4dim_quicksort_2[i]=secs_quicksort/100;
		
		/* tempo di libreria sort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_sort=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			std::sort(vecvec_test_2_sort[i][j].begin(), vecvec_test_2_sort[i][j].end());
		}
		double secs_sort=tc.toc();
		time4dim_sort_2[i]=secs_sort/100;
		
		/* tempo di libreria my_quicksort */
		std::vector<std::vector<std::vector<int>>> vecvec_test_2_my_quicksort=vecvec_test_2;
		tc.tic();
		for (int j=0; j<100; j++) {
			my_quicksort(vecvec_test_2_my_quicksort[i][j],0, dimension-1);
		}
		double secs_my_quicksort=tc.toc();
		time4dim_my_quicksort_2[i]=secs_my_quicksort/100;
		
		/* stampo i tempi */
		std::cout << "Elapsed time to order 100 random vector of dimension " << dimension << "\n";
		std::cout << "Bubblesort: " << secs_bs << " secs\n";
		std::cout << "Insertionsort: " << secs_is << " secs\n"; 
		std::cout << "Selectionsort: " << secs_ss << " secs\n";
		std::cout << "Mergesort: " << secs_mergesort << " secs\n";
		std::cout << "Quicksort: " << secs_quicksort << " secs\n";
		std::cout << "Sort(libreria): " << secs_sort << " secs\n";
		std::cout << "My_quicksort: " << secs_my_quicksort << " secs\n\n";
		
		}
	for (int j=0;j<time4dim_bs_2.size();j++) {
		std::cout << "Dimensione: " << std::setw(4) << vi_dimtest_2[j] << "  BS: " << time4dim_bs_2[j] << ";   ";
		std::cout << " IS: " << time4dim_is_2[j] << ";   ";
		std::cout << " SS: " << time4dim_ss_2[j] << ";   ";
		std::cout << " MS: " << time4dim_mergesort_2[j] << ";   ";
		std::cout << " QS: " << time4dim_quicksort_2[j] << ";   ";
		std::cout << " Sort Lib: " << time4dim_sort_2[j] << ";   ";
		std::cout << " My_quicksort: " << time4dim_my_quicksort_2[j] << "\n";
	}
	return 0;
}
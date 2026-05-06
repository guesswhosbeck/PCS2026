#include <vector>
#include <optional>
#include <string>

// implementazione algoritmo bubblesort
template<typename T>
void bubblesort(std::vector<T>& vec) 
{
for (int i=0; i<vec.size()-1; i++)
{
for (int j=vec.size()-1; j>=i+1; j--) 
{
	if (vec[j]<vec[j-1])
	{
	T swap=vec[j];
	vec[j]=vec[j-1];
	vec[j-1]=swap;
	}
}
}
} 

// implementazione algoritmo insertionsort
template<typename T>
void insertionsort(std::vector<T>& vec) 
{
for (int j=1; j<vec.size(); j++)
{
	T key=vec[j];
	int i;
	i=j-1;	
while (i>=0 &&  vec[i]>key) 
{
	vec[i+1] = vec[i];
	i-=1;
}
vec[i+1]=key;
}
} 

// implementazione algoritmo my_insertionsort che prende vettore e indice di inizio e fine ordinamento
template<typename T>
void my_insertionsort(std::vector<T>& vec, int p, int r) 
{
for (int j=p+1; j<=r; j++)
{
	T key=vec[j];
	int i;
	i=j-1;	
while (i>=p &&  vec[i]>key) 
{
	vec[i+1] = vec[i];
	i-=1;
}
vec[i+1]=key;
}
} 

// implementazione algoritmo selectionsort
template<typename T>
void selectionsort(std::vector<T>& vec) 
{
for (int i=0; i<vec.size()-1; i++)
{
	int min=i;
for (int j=i+1; j<vec.size(); j++) 
{
	if (vec[j]<vec[min])
	{
	min=j;
	}
}
	T swap=vec[min];
	vec[min]=vec[i];
	vec[i]=swap;	
}
}

// implemenetazione algoritmo merge sort
template<typename T>
void merge(std::vector<T>& A, int p, int q, int r) 
{
	int n1=q-p+1;
	int n2=r-q;
	std::vector<T> L;
	std::vector<T> R;
	L.resize(n1);
	R.resize(n2);
	for (int i=0; i<n1; i++)
	{
		L[i]=A[p+i];
	}
	for (int j=0; j<n2; j++) 
	{
		R[j]=A[q+j+1];
		}
	/* modifica allo pseudo codice per trovare una alternativa a 'inf' */
	int i=0;
	int j=0;
	bool L_done=false;
	bool R_done=false;
	for (int k=p; k<=r;k++)
	{ 
		if ((L[i]<=R[j] && L_done==false) || R_done==true) 
		{
			A[k]=L[i];
			/* aumento la i solo se ha senso */
			if (i<L.size()-1) {
			i+=1;	
			}
			else {
				L_done=true;
			}
		}
		else 
		{
			A[k]=R[j];
			/* aumento la j solo se ha senso */
			if (j<R.size()-1) {
			j=j+1;
			}
			else {
				R_done=true;
			}
		}
	}
}
			
			
					
			
template<typename T>
void mergesort(std::vector<T>& A, int p, int r)
{
	if (p<r) 
	{
		int q=(p+r)/2;
		mergesort(A,p,q);
		mergesort(A,q+1,r);
		merge(A,p,q,r);
	}
}


template<typename T>
int partition(std::vector<T>& A, int p, int r)
{
	T x=A[r];
	int i=p-1;
	for (int j=p;j<r;j++) 
	{
		if (A[j]<=x) 
		{
			i+=1;
			T to_swap=A[i];
			A[i]=A[j];
			A[j]=to_swap;
		}
	}
	T to_swap=A[i+1];
	A[i+1]=A[r];
	A[r]=to_swap;
	return i+1;
}


template<typename T>
void quicksort(std::vector<T>& A, int p, int r)
{
	if (p<r) {
		int q = partition(A,p,r);
		quicksort(A,p,q-1);
		quicksort(A,q+1,r);
	}
}
		

/* la mia versione modificata di quicksort, quando i vettori hanno dimensione inferiore a 40 sarà chiamato insertionsort */
template<typename T>
void my_quicksort(std::vector<T>& A, int p, int r)
{
	if (p<r) {
		if (r-p>40) {
			int q = partition(A,p,r);
			my_quicksort(A,p,q-1);
			my_quicksort(A,q+1,r);
		}
		else {
		my_insertionsort(A,p,r);
		}
	}
}	


template<typename T>
/* std::optional */
bool is_sorted(const std::vector<T>& vec)
{
	bool sorted= true;
	for (int i=0; i<vec.size()-1;i++)
	{
		if (vec[i]>vec[i+1])
			sorted=false;
	}
	return sorted;
}
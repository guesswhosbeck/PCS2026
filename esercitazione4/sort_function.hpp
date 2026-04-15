#include <vector>
#include <optional>

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
#include <iostream>
#include <cmath>

int main()
{
static const int N = 10;
double arr[N]={2.1, 3.7, 0.6, 8.9, 1.7, 0.9, 2.1, 2.8, 9.3, 4.4};
double min=arr[0];
double max=arr[0];
double somma = arr[0];
for (int i=1; i<10; i++) 
{
	somma += arr[i];
	min = std::min(min, arr[i]);
	max = std::max(max, arr[i]);
}
double media = somma/10.0;
double somma_dev = (arr[0]-media)*(arr[0]-media);
for (int i=1; i<10; i++) 
{
	somma_dev += (arr[i]-media)*(arr[i]-media);
}
double dev_stand = std::sqrt(somma_dev/10.0);
std::cout << "Il min dei valori è: " << min << "\n" << "Il max dei valori è: " << max << "\n";
std::cout << "La media dei valori è: " << media << "\n";
std::cout << "La deviazione standard dei valori è: " << dev_stand << "\n";


// implementazione algoritmo bubblesort
bool ordered = false;
while (ordered==false)
{
	int cambi_eff=0;
for (int i=0; i<9; i++) 
{
	if (arr[i]>arr[i+1])
	{
	double cambio = arr[i+1];
	arr[i+1]=arr[i];
	arr[i]=cambio;
	cambi_eff+=1;
	}
}
if (cambi_eff==0){
	ordered = true;
}
}
std::cout << "L'array ordinato è: ";
for (int i=0; i<10; i++){
	std::cout << arr[i] << " ";
} 
std::cout << "\n";
return 0;
}


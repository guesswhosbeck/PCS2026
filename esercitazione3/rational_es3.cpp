#include <iostream>
#include "rational.hpp"
#include <concepts>    /* serve per accettare I interi */
using namespace::std;  

int main()
{
	rational<int> a(27,-9);
	rational<int> b(1,0);
	std::cout << "a: " << a << " " << "b: " << b << "\n";
	std::cout << "numeratore di a : " << a.num() << " " << "denominatore di a: " <<  a.den() << "\n";
	
	std::cout << "a: " << a << " " << "b: " << b << "\n";
	rational<int> c=a+b;
	std::cout << "somma a+b --> " << c << "\n";
	
	rational<int> d=a-b;
	std::cout << "differenza a-b --> " << d << "\n";
	
	rational<int> e=a*b;
	std::cout << "prodotto a*b -->" << e << "\n";
	
	rational<int> f=a/b;
	std::cout << "rapporto a/b -->" << f << "\n";
	return 0;
}

/* a+=b;
std::cout << "incremento a+=b -->" << a << "\n";
a-=b;
std::cout << "decremento a-=b -->" << a << "\n";
a*=b;
std::cout << "prodotto a*=b -->" << a << "\n";
a/=b;
std::cout << "rapporto a/=b -->" << a << "\n"; */



#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(int argc, const char *argv[]) {
	if (argc!=2)
	{cout << "Deve essere inserito esattamente un nome di file \n";
	return 1;
	}
	else
	{string nome_file=argv[1];
	ifstream ifs(nome_file);
		if (ifs.is_open())
			{while (!ifs.eof()) {
			string city;
			double temp1, temp2, temp3, temp4;
			ifs >> city >> temp1 >> temp2 >> temp3 >> temp4;
			cout << city << ' ' << (temp1+temp2+temp3+temp4)/4.0 << '\n';
		}
		}
		else {
			cout << "Il file non si è aperto correttamente \n";
			return 1;
			}
}
return 0;
}
#include "grad_con.hpp"


int main() {
	bool risolto = true;
	/* provo con matrice di dimensioni da 2 a 100, vettore soluzione = 1 e vettore inziale = 100*/
	for (int n=2; n<=100; n++) {
		bool mal_cond=false;
		Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
		if (std::abs(B.determinant())<1e-15) {
			mal_cond=true;
		}
		// proseguo con il test solo se la matrice non è mal condizionata
		if (!mal_cond) { 
			Eigen::MatrixXd A = B.transpose() * B;
			Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
			Eigen::VectorXd b = A * x_ex;
			Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
			str_grad_ris grad_ris = gradiente_coniugato(A,b,x0);
			if (!grad_ris.risultato) {
				risolto = false;
			}
		}
	}
	
	/* provo con matrice di dimensioni da 2 a 100, vettore soluzione = -5 e vettore iniziale = 100*/
	for (int n=2; n<=100; n++) {
		bool mal_cond=false;
		Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
		if (std::abs(B.determinant())<1e-15) {
			mal_cond=true;
		}
		// proseguo con il test solo se la matrice non è mal condizionata
		if (!mal_cond) { 
			Eigen::MatrixXd A = B.transpose() * B;
			Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n)*(-5);
			Eigen::VectorXd b = A * x_ex;
			Eigen::VectorXd x0 = Eigen::VectorXd::Ones(n)*100;
			str_grad_ris grad_ris = gradiente_coniugato(A,b,x0);
			if (!grad_ris.risultato) {
				risolto = false;
			}
		}
	}
	
	/* provo con matrice di dimensioni potenze di 2, da 2^2 a 2^10 a 100,  vettore soluzione = 1 e vettore inziale = 100*/
	std::vector vettore_dim(10,0);
	vettore_dim[0]=2;
	for (int i=1; i<=9; i++) {
		vettore_dim[i]=vettore_dim[i-1]*2;
		int n = vettore_dim[i];
		bool mal_cond=false;
		Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
		if (std::abs(B.determinant())<1e-15) {
			mal_cond=true;
		}
		// proseguo con il test solo se la matrice non è mal condizionata
		if (!mal_cond) { 
			Eigen::MatrixXd A = B.transpose() * B;
			Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
			Eigen::VectorXd b = A * x_ex;
			Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
			str_grad_ris grad_ris = gradiente_coniugato(A,b,x0);
			if (!grad_ris.risultato) {
				risolto = false;
			}
		}
	}
		
	if (risolto) {
		std::cout << "Il metodo è risultato convergente per tutte le dim da 2 a 100 e per le dim da 2^2 a 2^10\n";
		return EXIT_SUCCESS;		
	}
	else {
		std::cout << "Il metodo non è risultato convergente per tutte le dimensioni da 2 a 100";
		return EXIT_FAILURE;
	}
	
}
#include "grad_con.hpp"

// g++ -std=c++20 -I /usr/include/eigen3 -o prova main_gradiente.cpp(comando per runnare da terminale) 
 

int main() {
	int n=10;
	Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
	if (std::abs(B.determinant())<1e-15) {
		return 1;
	}
	Eigen::MatrixXd A = B.transpose() * B;
	Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
	Eigen::VectorXd b = A * x_ex;
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
	str_grad_ris grad_ris = gradiente_coniugato(A,b,x0);
	std::cout << "Il metodo è riuscito: " << grad_ris.risultato << "\n" << "iterazioni: " << grad_ris.n_iter << "\nresiduo:\n" << grad_ris.res << "\nvettore finale:\n" << grad_ris.x;
	
}


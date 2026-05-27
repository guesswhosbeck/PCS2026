#include "eigen3/Eigen/Eigen"
#include <iostream>

struct str_grad_ris {
	Eigen::VectorXd x;
	bool risultato;
	int n_iter;
	Eigen::VectorXd res;
};


str_grad_ris gradiente_coniugato(const Eigen::MatrixXd& A,const Eigen::VectorXd& b, Eigen::VectorXd& x0,const double& res_tol=1.0e-15) {
	Eigen::VectorXd r0= b-A*x0;
	Eigen::VectorXd p0=r0;
	int k=0;
	Eigen::VectorXd res_0 = r0;
	while (r0.norm()>(res_tol * res_0.norm()) && k<10000) {
		double ak=((p0.transpose()*r0)/(p0.transpose()*A*p0)).value();
		x0+=ak*p0;
		r0=b-A*x0;
		double betak=((p0.transpose()*A*r0)/(p0.transpose()*A*p0)).value();
		p0=r0-betak*p0;
		k+=1;
	}
	bool risultato = false;
	if (k!=10000) {
		risultato = true;
		std::cout << "il metodo ha raggiunto la convergenza richiesta in " << k << " iterazioni\n";
	}
	else {
		std::cout << "Non ha raggiunto convergenza " << x0.size() << "\n";
	}
	str_grad_ris grad_ris;
	grad_ris.x = x0;
	grad_ris.risultato = risultato;
	grad_ris.n_iter = k;
	grad_ris.res = r0;
	
	return grad_ris;
}
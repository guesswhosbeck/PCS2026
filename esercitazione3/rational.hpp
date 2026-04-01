#include <iostream>
#include <concepts>  /* serve per accettare I interi */
#include <numeric>   /* serve per calcolo gcd */

template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
	
	void simplify()
	{
		if (den_==0) {
			// defining Nan
			if (num_==0) {
				num_=0;
				den_=0;
			}
			// defining inf
			else {
				if (num_>0) {
					num_=1;
				}
				else {
					num_=-1;
				}
			}
		}
		else {
			/* porto il meno a numeratore */
			if (den_ <0) {
				den_ = -den_;
				num_ = -num_;
			}
			I gcd_;
			gcd_ = std::gcd(num_, den_);
			num_/=gcd_;
			den_/=gcd_;
		}
	}
		
	
public:
	/* Costruttore di default */
	rational()
		: num_(I{3}), den_(I{4})
	{}

	/* Costruttore user-defined */
	rational(const I& num, const I& den)
	: num_(num), den_(den)
	{
		simplify();
	}

	/* Restituiscono i valori di num e den */
	I num() const { return num_; }
	I den() const { return den_; }
	
	
	/* Implementazione canonica dell'incremento */
		rational& operator+=(const rational& other) {
		/* return NAN */
		if ((*this).is_nan() || other.is_nan() || ((*this).is_inf() && other.is_inf() && num_*other.num()==-1)) { 
			num_=0;
			den_=0;
		}
		/* return +inf */
		else if (((*this).is_inf() && other.is_inf() && num_+other.num()==2) || (((*this).is_inf() && num_==1 && not other.is_inf()) || (other.is_inf() && other.num()==1 && not (*this).is_inf()))) {
			num_=1;
			den_=0;
		}
		/* return -inf */
		else if (((*this).is_inf() && other.is_inf() && num_+other.num()==-2) || (((*this).is_inf() && num_==-1 && not other.is_inf()) || (other.is_inf() && other.num()==-1 && not (*this).is_inf()))) {
			num_=-1;
			den_=0;
		}
		else {
			I lcm_;
			lcm_ = std::lcm(den_, other.den());
			num_= (lcm_/den_)*num_+(lcm_/other.den())*other.num();
			den_=lcm_;
			simplify();
		}
		return *this;
	}
	
	/* Implementazione canonica della somma */
	rational operator+(const rational& other) const {
		rational ret = *this;
        ret += other;
        return ret;
	}
	
	/* Implementazione canonica del decremento */
	rational& operator-=(const rational& other) {
		/* return NAN */
		if ((*this).is_nan() || other.is_nan() || ((*this).is_inf() && other.is_inf() && num_*other.num()==1)) { 
			num_=0;
			den_=0;
		}
		/* return +inf */
		else if (((*this).is_inf() && other.is_inf() && num_*other.num()==-1 && num_==1) || (((*this).is_inf() && num_==1 && not other.is_inf()) || (other.is_inf() && other.num()==-1 && not (*this).is_inf()))) {
			num_=1;
			den_=0;
		}
		/* return -inf */
		else if (((*this).is_inf() && other.is_inf() && num_*other.num()==-1 && num_==-1) || (((*this).is_inf() && num_==-1 && not other.is_inf()) || (other.is_inf() && other.num()==1 && not (*this).is_inf()))) {
			num_=-1;
			den_=0;
		}
		else {
			I lcm_;
			lcm_ = std::lcm(den_, other.den());
			num_= (lcm_/den_)*num_-(lcm_/other.den())*other.num();
			den_=lcm_;
			simplify();
		}
		return *this;
	}
	
	/* Implementazione canonica della differenza */
	rational operator-(const rational& other) const {
		rational ret = *this;
        ret -= other;
        return ret;
	}
	
	/* Implementazione canonica di *= */
	rational& operator*=(const rational& other) {
		/* return NAN */
		if ((*this).is_nan() || other.is_nan()) { 
			num_=0;
			den_=0;
		}
		/* return +inf */
		else if ((((*this).is_inf() || other.is_inf()) && num_*other.num()>0)) {
			num_=1;
			den_=0;
		}
		/* return -inf */
		else if ((((*this).is_inf() || other.is_inf()) && num_*other.num()<0)) {
			num_=-1;
			den_=0;
		}
		else {
			num_ *= other.num();
			den_ *= other.den();
			simplify();
		}
		return *this;
	}
	
	/* Implementazione canonica del prodotto */
	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
	
	/* Implementazione canonica di /= */
	rational& operator/=(const rational& other) {
		/* return NAN */
		if (((*this).is_nan() || other.is_nan()) || ((*this).is_inf() && other.is_inf())) { 
			num_=0;
			den_=0;
		}
		/* return +inf */
		else if ((((*this).is_inf() && not other.is_inf()) && num_*other.num()>0)) {
			num_=1;
			den_=0;
		}
		/* return -inf */
		else if ((((*this).is_inf() && not other.is_inf()) && num_*other.num()<0)) {
			num_=-1;
			den_=0;
		}
		/* return 0 */
		else if (not (*this).is_inf() && other.is_inf()){
			num_=0;
			den_=1;
			
		}
		else {
			num_ *= other.den();
			den_ *= other.num();
			simplify();
		}
		return *this;
	}
	
	/* Implementazione canonica della differenza */
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
	
	/* funzioni per check inf e nan */
	bool is_inf() const {
		return (num_!=0 && den_==0);
	}
	bool is_nan() const {
		return (num_==0 && den_==0);
	}
};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r)
{
	if (r.is_nan()) {
		os << "Nan";
	}
	else if (r.is_inf()) {
		if (r.num()==1) {
			os << "+Inf";
		}
		else {
			os << "-Inf";
		}
	}
	else if (r.num()==0) {
		os << "0";
	}
    else {
		os << r.num() << "/" << r.den();
	}
    return os;
}
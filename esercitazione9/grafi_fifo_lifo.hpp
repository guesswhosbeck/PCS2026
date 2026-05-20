#include <iostream>
#include <concepts>  /* serve per accettare I interi */
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm> /* serve per stampa set (for_each) */
#include <optional> /* serve per casi in cui le funzioni dichiarate possono aver problemi se chiamate */

// template <typename I> fa si che I possa essere qualsiasi cosa, con il requires impongo che I sia un intero
template<typename I> requires std::integral<I>
class undirected_edge
{
	I from_;
	I to_;
	
	void simplify()
	{
		if (from_>to_)
		{
			std::swap(from_,to_);
		}
	}
	public:
	/* Costruttore di default */
	undirected_edge()
		: from_(I{1}), to_(I{2})
	{}

	/* Costruttore user-defined */
	undirected_edge(const I& from, const I& to)
		: from_(from), to_(to)
	{
		simplify();
	}
	
	/* Restituiscono i valori di from e to */
	I from() const { return from_; }
	I to() const { return to_; }
	
	/* operatore minore per un arco */
	bool operator<(const undirected_edge& other) const {
		if (from_<other.from() || (from_==other.from() && to_<other.to()))
		{
			return true;
		}
		else {
			return false;
		}
	}
	
	/* operatore uguale per un arco */
	bool operator==(const undirected_edge& other) const {
		if (from_==other.from() && to_==other.to())
		{
			return true;
		}
		else {
			return false;
		}
	}
	
};



// costruirò un grafo di 10 nodi attraverso una mappa con chiave nodi e valore la lista di adiacenza del nodo chiave
template<typename I> requires std::integral<I>
class undirected_graph
{
	std::map<I,std::set<I>> mappa_adiacenza;	/* mappa di adiacenza, nodo-->lista adiacenza*/
	std::vector<undirected_edge<I>> vettore_archi;; /* vettore in cui mi salvo gli archi del grafo */
	// ho deciso di usare un vettore perchè ho supposto che sia molto piu richiesto di trovare l'indice di un arco, veloce con il vettore, rispetto all'aggiunta di arco, e conseguente ordinamento e rimozione duplicati, che sarebbe stato invece immediato con la lista.
	
	public:
	/* Costruttore di default */
	undirected_graph()
		: mappa_adiacenza()
	// posso anche iniziallizzarla vuota?
	{}
	
	/* Costruttore user-defined con mappa*/
	// questo è per poter passare una mappa e trattarla come grafo
	undirected_graph(const std::map<I, std::set<I>>& mappa) 
	: mappa_adiacenza(mappa) 
	{
		// appena creo la mappa mi creo anche la lista di archi
		for (auto it = mappa_adiacenza.begin(); it != mappa_adiacenza.end(); ++it) {
			I from_=(it->first);
			/* definisco la variabile che contiene la mia iterata : su cosa itero */
			for (const I& x : it->second) {
					undirected_edge<I> arco(from_, x);
			 		vettore_archi.push_back(std::move(arco)); 
				}
			}
			// ordino per eliminare gli archi doppi
			std::sort(vettore_archi.begin(), vettore_archi.end());
			auto pos_elimina = std::unique(vettore_archi.begin(), vettore_archi.end());
			vettore_archi.erase(pos_elimina,vettore_archi.end());				
	}
	// potrei fare anche un costruttore user-defined che, dati una lista di nodi e una lista di archi si crea il grafo 
	
	/* Costruttore di copia se passato un grafo*/
	// la copia è automatizzata grazie all'utilizzo di map e set
	undirected_graph(const undirected_graph& other) 
	: mappa_adiacenza(other.mappa_adiacenza), vettore_archi(other.vettore_archi)
	
	{}
	
	/* restituzione di neighbours */
	// uso optional per gestire il caso in cui il nodo richiesto non appartenga al grafo
	// qua non uso std::optional perche non è un problema se mi viene restituito un set vuoto nel caso in cui il nodo richiesto non appartenga al grafo
	std::set<I> neighbours(const I& nodo) const {
		auto iter=mappa_adiacenza.find(nodo);
		if (iter!=mappa_adiacenza.end()) {
			return iter->second;
		}
		else {
			return {};
		}
	}
		
	/* aggiunta di arco */
	undirected_graph& add_edge(const undirected_edge<I>& arco) {
	  if (mappa_adiacenza.contains(arco.from()) && mappa_adiacenza.contains(arco.to())) {
		  // faccio questo processo solo se l'arco non esisteva già
		  auto trovato=std::find(vettore_archi.begin(), vettore_archi.end(), arco);
		  if (trovato==vettore_archi.end()) {
		  	mappa_adiacenza[arco.from()].insert(arco.to());
		  	mappa_adiacenza[arco.to()].insert(arco.from());
		  	vettore_archi.push_back(arco);
		  	// riordino per tenere l'enumerazione delgi archi, non faccio unique e erase perche ho aggiunto l'arco solo se non già presente
		  	std::sort(vettore_archi.begin(), vettore_archi.end());
		  }
	  }
	  return *this;
	}
	
	/* restituzione di tutti gli archi */
	const std::vector<undirected_edge<I>>& all_edges() const {
		return vettore_archi; }
	
	/* restituzione di tutti i nodi */ 
	const std::list<I> all_nodes() const {
		std::list<I> lista_nodi;
		for (auto it = mappa_adiacenza.begin(); it != mappa_adiacenza.end(); ++it) {
			lista_nodi.push_back(it->first);
		}
		return lista_nodi; }
		
	/* restituzione numero arco all'interno di un grafo */
	// uso optional per gestire il caso in cui il nodo richiesto non appartenga al grafo
	std::optional<int> edge_number (const undirected_edge<I>& arco) const {
		// uso lower bound perchè il mio arco è ordinato quindi mi permette meno iterazioni
		auto trovato=std::lower_bound(vettore_archi.begin(), vettore_archi.end(), arco);
		if (trovato!=vettore_archi.end()) {
			int indice = std::distance(vettore_archi.begin(), trovato);
			return indice;
		}
		else {
			return std::nullopt;
		}
	}
	
	/* restituzione oggetto arco */
	std::optional<undirected_edge<I>> edge_at(const size_t pos) const {
		// controllo che la posizione sia minore del numero di archi che ho
		if (pos<vettore_archi.size()) {
			return vettore_archi[pos];
		}
		else {
			return std::nullopt;
		}
	}
	
	/* operatore remove_edge */
	undirected_graph& remove_edge(const undirected_edge<I>& arco) {
	  if (mappa_adiacenza.contains(arco.from()) && mappa_adiacenza.contains(arco.to())) {
		  // faccio questo processo solo se l'arco esisteva già
		  auto trovato=std::find(vettore_archi.begin(), vettore_archi.end(), arco);
		  if (trovato!=vettore_archi.end()) {
			  // ottengo la pos dell'arco, so essere presente perchè è stato trovato nel vettore
			  auto indice = (*this).edge_number(arco);
			  // lo elimino dal vettore, gli elementi rimangono ordinati
			  vettore_archi.erase(vettore_archi.begin() + (*indice));
			  // lo elimino anche dalla mappa di adiacenza
			  mappa_adiacenza[arco.from()].erase(arco.to());
			  mappa_adiacenza[arco.to()].erase(arco.from());
		  }
	  }
	  return *this;
	}
	
	/* operatore - */ 
	std::optional<undirected_graph> operator-(const undirected_graph& u_g) {
		// faccio questo solo se i grafi hanno lo stesso numero di nodi
		if (mappa_adiacenza.size()==u_g.mappa_adiacenza.size()) {
			undirected_graph nuovo_grafo(*this);
			// elimino dalla copia del grafo gli archi presenti anche nel precedente
			for (const undirected_edge<I>& u_e : u_g.vettore_archi) {
				nuovo_grafo.remove_edge(u_e);
			} 
			return nuovo_grafo;
		}
		else {
			return std::nullopt;
		}
	}
};


template<typename T>
class fifo
{
	std::list<T> lista_fifo;
	
	public:
	fifo()
	: lista_fifo()
	{}
	
	void put(const T& oggetto) {
		lista_fifo.push_back(oggetto);
	}
	
	std::optional<T> get() {
		if (lista_fifo.empty()) {
			return std::nullopt;
		}
		else {
			T x = lista_fifo.front();
			lista_fifo.pop_front();
			return x;
		}
	}
	
	bool empty() const {
		return lista_fifo.empty();
	}
};


template<typename T>
class lifo
{
	std::list<T> lista_lifo;
	
	public:
	lifo()
	: lista_lifo()
	{}
	
	void put(const T& oggetto) {
		lista_lifo.push_front(oggetto);
	}
	
	std::optional<T> get() {
		if (lista_lifo.empty()) {
			return std::nullopt;
		}
		else {
			T x = lista_lifo.front();
			lista_lifo.pop_front();
			return x;
		}
	}
	
	bool empty() const {
		return lista_lifo.empty();
	}
};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const undirected_edge<I>& u_e)
{
	os << u_e.from() << "<-->" << u_e.to();
	return os;
}

template<typename I> 
std::ostream&
operator<<(std::ostream& os, const undirected_graph<I>& grafo)
{
	std::list<int> lista_nodi;
	lista_nodi = grafo.all_nodes();
	os << "Nodi: ";
	for (const int nodo : lista_nodi) {
		os << nodo << ", ";
	}
	std::vector<undirected_edge<int>> vettore_archi;
	vettore_archi = grafo.all_edges();
	os << "  Archi:  ";
	for (const undirected_edge<int> u_e : vettore_archi) {
		os << u_e << "; ";
	}
	os << "\n";
	return os;
}


// scrittura operatore stampa per un set, presa da cppreference std::set
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& set)
{
    if (set.empty())
        return out << "{}";
    out << "{ " << *set.begin();
    std::for_each(std::next(set.begin()), set.end(), [&out](const T& element)
    {
        out << ", " << element;
    });
    return out << " }";
}
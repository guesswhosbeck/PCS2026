#include "grafi_fifo_lifo.hpp"
#include <fstream>
#include <queue>
template<typename T>
undirected_graph<T> graph_visit(const undirected_graph<T>& grafo, const T sorgente, auto contenitore) {
	// devo prima creare la mappa adiacenza con i nodi perchè il mio grafo può essere definito se gli viene passata una mappa di adiacenza
	std::map<T, std::set<T>> mappa_adiacenza_ris;
	std::list<T> lista_nodi = grafo.all_nodes();
	for (const T& nodo : lista_nodi) {
		mappa_adiacenza_ris[nodo];
	}
	undirected_graph<T> grafo_risultato(mappa_adiacenza_ris);
	// creo il set reached in cui inserisco i nodi già visitati
	std::set<T> reached;
	contenitore.put(sorgente);
	reached.insert(sorgente);
	while (!contenitore.empty()) {
		auto u_iniziale = contenitore.get();
		if (u_iniziale!=std::nullopt) {
			T u = *u_iniziale;
			std::set<T> la = grafo.neighbours(u);
			for (const T& vicino : la) {
				if (!reached.contains(vicino)) {
					contenitore.put(vicino);
					grafo_risultato.add_edge(undirected_edge(u,vicino));
					reached.insert(vicino);
				}
			}
		}
	}
	return grafo_risultato;
};


// stessa logica del dfs, in questo caso però i nodi NON saranno necessariamente connessi al primo nodo che li scopre, questo perchè la ricorsione va a cammini successivi prima della fine del ciclo sul nodo considerato
template<typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& grafo, const T sorgente) {
	std::map<T, std::set<T>> mappa_adiacenza_ris;
	std::set<T> reached={};
	std::list<T> lista_nodi = grafo.all_nodes();
	for (const T& nodo : lista_nodi) {
	    mappa_adiacenza_ris[nodo];
	}
	undirected_graph<T> grafo_risultato(mappa_adiacenza_ris);
	grafo_risultato = dfs(grafo, sorgente, reached, grafo_risultato);
	return grafo_risultato;
}

template<typename T>
undirected_graph<T>& dfs(const undirected_graph<T>& grafo, const T sorgente, std::set<T>& reached, undirected_graph<T>& grafo_risultato) {
	// metto la sorgente in reached come nodo visitato e faccio il procedimento per i suoi vicini
	reached .insert(sorgente);
	std::set<T> la = grafo.neighbours(sorgente);
	for (auto it=la.rbegin(); it!=la.rend(); it++) {
		T nodo = *it;
		if (!reached.contains(nodo)) {
			grafo_risultato.add_edge(undirected_edge(sorgente, nodo));
			// questo è il motivo per cui il grafo viene diverso, chiamando la ricorsione qua vado prima a controllare cammini relativi ai nodi successivi
			dfs(grafo, nodo, reached, grafo_risultato);
		}
	}
	return grafo_risultato;
}

template<typename T>
struct str_res_dijkstra {
	std::map<T, T> mappa_predecessori;
	std::map<T, int> mappa_distanze;
	undirected_graph<T> grafo_dj;
};


template<typename T>
str_res_dijkstra<T> dijkstra(const undirected_graph<T>& grafo, const T sorgente) {
	std::list<T> lista_nodi = grafo.all_nodes();
	size_t n_nodi = lista_nodi.size();
	str_res_dijkstra<T> res_dj;
	// uso set distanze di pair, in cui il primo valore di pair è la distanza (su cui viene effettuato l'ordinamento), il secondo il nodo, per far si che siano ordinati da distanza minore a distanza maggiore
	std::set<std::pair<int,T>> set_distanze;
	// inizializzo la distanza sorg = 0, le altre = n_nodi(come se fosse inf, il cammino minimo più lungo per un grafo è sempre minore del numero dei nodi) e ogni nodo come predecessore di se stesso
	for (const auto& nodo : lista_nodi) {
		std::pair<int, T> distanza;
		if (nodo==sorgente) {
			distanza={0, nodo};
			res_dj.mappa_distanze[nodo] = 0;
		}
		else {
			distanza={n_nodi, nodo};
			res_dj.mappa_distanze[nodo] = n_nodi;
		}
		set_distanze.insert(distanza);
		res_dj.mappa_predecessori.insert({nodo, nodo});
	}
	while (!set_distanze.empty()) {
		std::pair<int, T> coppia = *set_distanze.begin();
		// chiamo u il nodo della coppia che sto considerando in questa iterazione
		auto u = coppia.second;
		set_distanze.erase(set_distanze.begin());
		std::set<T> la = grafo.neighbours(u); 
		for (const auto& vicino : la) {
			if (res_dj.mappa_distanze[vicino] > (res_dj.mappa_distanze[u]+1)) {
				int distanza_old=res_dj.mappa_distanze[vicino];
				int distanza_new=res_dj.mappa_distanze[u]+1;
				// aggiorno la nuova distanza e il predecessore
				res_dj.mappa_distanze[vicino]=distanza_new;
				res_dj.mappa_predecessori[vicino]=u;
				// elimino la vecchia coppia nel set, e inserisco la nuova
				set_distanze.erase({distanza_old, vicino});
				std::pair<int, T> coppia_dist={distanza_new, vicino};
				set_distanze.insert(coppia_dist);
			}
		}
	}
	// creo la mia mappa adiacenza per poter inizializzare il grafo
	std::map<T, std::set<T>> mappa_adiacenza_ris;
	for (const auto& nodo : lista_nodi) {
		mappa_adiacenza_ris[nodo];
	}
	// inizializzo il grafo e ci aggiungo gli archi trovati
	res_dj.grafo_dj = undirected_graph<T>(mappa_adiacenza_ris);
	for (const auto& [nodo_f, nodo_to ] : res_dj.mappa_predecessori) {
		res_dj.grafo_dj.add_edge(undirected_edge(nodo_f, nodo_to));
	}
	return res_dj;
}	


// funzione per fare immagine grafo con GRAPHVIZ

template<typename T>
void grafo_dot(const undirected_graph<T>& grafo, const std::string& filename) {
	std::ofstream os(filename);
	os << "graph G {\n";
	for (const undirected_edge<T>& arco : grafo.all_edges()) {
		os << "  " << arco.from() << " -- " << arco.to() << ";\n";
	} 
	os << "}\n";
}


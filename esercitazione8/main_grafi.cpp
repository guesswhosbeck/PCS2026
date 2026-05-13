#include "grafi.hpp"

int main() {
	undirected_edge<int> arco;
	undirected_edge<int> arco2(5,7);
	undirected_edge<int> arco3(5,90);
	undirected_edge<int> arco4(5,90);
	undirected_edge<int> arco5(5,6);
	undirected_edge<int> arco6(6,8);
	
	std::cout << "CONTROLLO SUI NODI E LE LORO OPERAZIONI:\n";
	std::cout << "Un arco è rappresentato così: " << arco2 << "\n";
	std::cout << "arco.from()= " << arco2.from() << "; arco.to()= " << arco2.to() << "\n";
	std::cout << "arco 2: " << arco2 << " è minore di: " << "arco 3: " << arco3 << " " << (arco2<arco3) << "\n";
	std::cout << "arco 2: " << arco2 << " è uguale a: " << "arco 3: " << arco3 << " " << (arco2==arco3) << "\n";
	std::cout << "arco 3: " << arco3 << " è uguale a: " << "arco 4: " << arco4 << " " << (arco3==arco4) << "\n";
	std::cout << "arco 2: " << arco2 << " è minore di: " << "arco 5: " << arco5 << " " << (arco2<arco5) << "\n";
	std::cout << "arco 2: " << arco2 << " è minore di : " << "arco 6: " << arco6 << " " << (arco2<arco6)<< "\n";
	std::cout << "\n\n";
	
	undirected_graph<int> mappa_adiacenza;
	undirected_graph<int> mappa_adiacenza1({{1, {2, 8}},{2, {1, 3}},{3, {2, 4}},{4, {3, 5}},{5, {4, 6}},{6, {5, 7}},{7, {6}},{8, {1}}});
	undirected_graph<int> mappa_adiacenza2({{1, {2, 8, 5}},{2, {1, 3}},{3, {2, 4}},{4, {3, 5}},{5, {1, 4, 6}},{6, {5, 7}},{7, {6, 8}},{8, {1, 7}}});
	undirected_graph<int> mappa_adiacenza3(mappa_adiacenza2);
	
	// stampo gli archi del mio grafo su cui farò le operazioni: 
	std::vector<undirected_edge<int>> vettore_archi;
	vettore_archi = mappa_adiacenza2.all_edges();
	std::cout << "GLi archi del GRAFO2 sono: \n";
	for (const undirected_edge<int> u_e : vettore_archi) {
		std::cout << u_e << "; ";
	}
	std::cout << "\n";
	
	// per poter stampare i nodi adiacenti devo prima controllare che il nodo sia effettivamente parte del grafo, ovvero che non mi sia stato restituito std::nullopt 
	auto set_vicini1 = mappa_adiacenza2.neighbours(1);
	if (set_vicini1!=std::nullopt) {
		// il * è perche ho gestito l'oggetto optional
		std::cout << "Vicini del nodo 1: " << *set_vicini1 << "\n";
	}
	std::cout << "Aggiungo l'arco " << arco6 << "\n";
	mappa_adiacenza2.add_edge(arco6);
	auto set_vicini6 = mappa_adiacenza2.neighbours(6);
	auto set_vicini8 = mappa_adiacenza2.neighbours(8);
	if (set_vicini6!=std::nullopt && set_vicini8!=std::nullopt) {
		std::cout << "Vicini del nodo 6: " << *set_vicini6 << "\n";
		std::cout << "Vicini del nodo 8: " << *set_vicini8 << "\n";
		
	}
	undirected_edge<int> arco7(1,1);
	std::cout << "Aggiungo l'arco " << arco7 << "\n";	
	mappa_adiacenza2.add_edge(arco7);
	set_vicini1 = mappa_adiacenza2.neighbours(1);
	if (set_vicini1!=std::nullopt) {
		std::cout << "Vicini del nodo 1: " << *set_vicini1 << "\n";
	}
	vettore_archi = mappa_adiacenza2.all_edges();
	std::cout << "GLi archi del GRAFO2 adesso sono: \n";
	for (const undirected_edge<int> u_e : vettore_archi) {
		std::cout << u_e << "; ";
	}
	std::list<int> lista_nodi;
	lista_nodi = mappa_adiacenza2.all_nodes();
	std::cout << "  e nodi: ";
	for (const int nodo : lista_nodi) {
		std::cout << nodo << ", ";
	}
	std::cout << "\n\n";
	std::cout << "GRAFO1: ";
	std::list<int> lista_nodi1;
	lista_nodi1 = mappa_adiacenza1.all_nodes();
	std::cout << "Nodi: ";
	for (const int nodo : lista_nodi1) {
		std::cout << nodo << ", ";
	}
	std::vector<undirected_edge<int>> vettore_archi1;
	vettore_archi1 = mappa_adiacenza1.all_edges();
	std::cout << "  Archi:  ";
	for (const undirected_edge<int> u_e : vettore_archi1) {
		std::cout << u_e << "; ";
	}

	std::cout << "\n";
	
	auto pos_arco = mappa_adiacenza2.edge_number(arco6);
	if (pos_arco!=std::nullopt) {
		std::cout << "L'arco :" << arco6 << " si trova alla pos: " << *pos_arco << " per il GRAFO2\n";
	}
	auto ogg_arco = mappa_adiacenza2.edge_at(9);
	if (ogg_arco!=std::nullopt) {
		std::cout << "Alla posizione 9 del GRAFO2 si trova l'arco: " << *ogg_arco << "\n";
	}
	auto grafo_differenza = mappa_adiacenza2-mappa_adiacenza1;
	if (grafo_differenza != std::nullopt) {
		std::cout << "La differenza tra grafo2 e grafo1 è un grafo di nodi: ";
		std::list lista_nodi_diff=(*grafo_differenza).all_nodes();
		for (const int nodo : lista_nodi_diff) {
			std::cout << nodo << ", ";
		}
		std::cout << "\ne archi:  ";
		auto vec_archi_diff = (*grafo_differenza).all_edges();
		for (const undirected_edge<int> u_e : vec_archi_diff) {
			std::cout << u_e << "; ";
		} 
	}
	std::cout << "\n";
	
}

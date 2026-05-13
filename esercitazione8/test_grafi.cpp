#include "grafi.hpp"

int main() {
	undirected_edge<int> arco1(5,6);
	undirected_edge<int> arco2(6,6);
	undirected_edge<int> arco3(5,7);
	undirected_edge<int> arco4(6,8);
	undirected_edge<int> arco5(5,6);
	
	
	//Controllo sui nodi e le loro operazioni
	bool oper_corretto = false;
	/*é operazione <  e operazione = */
	if (arco1==arco5 && arco1<arco2 && arco1<arco3 && arco1<arco4) {
		oper_corretto = true;
	}
	
	/* automatizzazione from<to */
	undirected_edge<int> arco6(8,5);
	if (arco6.from()>arco6.to()) {
		oper_corretto = false;
	}
	
	//se corretto==true allora: '=='; '<' e automatizzazione from_<to_ funziona;
	
	
	// controllo sulle operazioni sui grafi, prendo come esempio 2 grafi con 8 nodi
	bool grafo_corretto = true;
	undirected_graph<int> mappa_adiacenza1({{1, {2, 8}},{2, {1, 3}},{3, {2, 4}},{4, {3, 5}},{5, {4, 6}},{6, {5, 7}},{7, {6}},{8, {1}}});
	undirected_graph<int> mappa_adiacenza2({{1, {2, 5, 8}},{2, {1, 3}},{3, {2, 4}},{4, {3, 5}},{5, {1, 4, 6}},{6, {5, 7}},{7, {6, 8}},{8, {1, 7}}});
	 
	/* controllo sull'operatore neighbours */
	auto set_vicini1 = mappa_adiacenza2.neighbours(1); 
	auto set_vicini2 = mappa_adiacenza2.neighbours(2);
	auto set_vicini3 = mappa_adiacenza2.neighbours(3);
	auto set_vicini4 = mappa_adiacenza2.neighbours(4);
	auto set_vicini5 = mappa_adiacenza2.neighbours(5);
	auto set_vicini6 = mappa_adiacenza2.neighbours(6);
	auto set_vicini7 = mappa_adiacenza2.neighbours(7);
	auto set_vicini8 = mappa_adiacenza2.neighbours(8);
	if (*set_vicini1 != std::set<int> {2, 5, 8} || *set_vicini2 != std::set<int> {1, 3} || *set_vicini3 != std::set<int> {2, 4} || *set_vicini4 != std::set<int> {3, 5} || *set_vicini5 != std::set<int> {1, 4, 6} || *set_vicini6 != std::set<int> {5, 7} || *set_vicini7 != std::set<int> {6, 8} || *set_vicini8 != std::set<int> {1, 7}) {
		grafo_corretto= false;
	}
	
	/* controllo su add_edge */
	undirected_edge<int> arco7(1,1);
	mappa_adiacenza2.add_edge(arco7);
	undirected_edge<int> arco8(2,8);
	mappa_adiacenza2.add_edge(arco8);
	set_vicini1 = mappa_adiacenza2.neighbours(1);
	set_vicini2 = mappa_adiacenza2.neighbours(2);
	set_vicini8 = mappa_adiacenza2.neighbours(8);
	if (*set_vicini1!=std::set<int> {1, 2, 5, 8} || *set_vicini2!=std::set<int> {1, 3, 8} ||*set_vicini8!=std::set<int> {1, 2, 7}) {
		grafo_corretto = false;
	}
	
	/* controllo su all_edges */
	std::vector<undirected_edge<int>> vettore_archi;
	vettore_archi = mappa_adiacenza1.all_edges();
	if (vettore_archi != std::vector<undirected_edge<int>> {{1,2}, {1,8}, {2,3}, {3,4}, {4,5}, {5,6}, {6,7}}) {
		grafo_corretto=false;
	}
	
	 /* controllo su all_nodes */
	std::list<int> lista_nodi;
	lista_nodi = mappa_adiacenza2.all_nodes();
	if (lista_nodi != std::list{1, 2, 3, 4, 5, 6, 7, 8}) {
		grafo_corretto=false;
	}
	
	/* controllo su edge_number */
	auto pos_arco = mappa_adiacenza2.edge_number(arco7);
	if (*pos_arco!=0) {
		grafo_corretto=false;
	}
	
	/* controllo su edge_at */
	auto ogg_arco = mappa_adiacenza2.edge_at(0);
	if (ogg_arco!=arco7) {
		grafo_corretto=false;
	}
	
	/* controllo su operatore - */
	undirected_graph<int> grafo_differenza_true({{1, {1, 5}},{2, {8}},{3, {}},{4, {}},{5, {}},{6, {}},{7, {8}},{8, {2, 7}}});
	auto grafo_differenza = mappa_adiacenza2-mappa_adiacenza1;
	auto grafo_diff = *grafo_differenza;
	auto nodi_diff = grafo_diff.all_nodes();
	auto nodi_diff_true = grafo_differenza_true.all_nodes();
	auto archi_diff = grafo_diff.all_edges();
	auto archi_diff_true = grafo_differenza_true.all_edges();
	if (nodi_diff != nodi_diff_true || archi_diff != archi_diff_true) {
		grafo_corretto= false;

	}
		
	/* ritorno l'esito del test */
	if (oper_corretto && grafo_corretto) {
		std::cout << "Le classi undirected_edge e undirected_graph e i loro metodi funzionano! \n";
		return EXIT_SUCCESS;
	}
	else {
		std::cout << "ATTENZIONE: le classi undirected_edge e undirected_graph e i loro metodi NON funzionano! \n";
		return EXIT_FAILURE;
	}
	
}

#include "graph_visit.hpp"


int main() {
	lifo<int> l;
	fifo<int> f;
	undirected_graph<int> grafo_start({{1, {2, 3, 4, 6}},{2, {1, 5, 7}},{3, {1, 6}},{4, {1, 6, 7}},{5, {2, 7}},{6, {1, 3, 4, 7, 8}},{7, {4, 5, 6, 9}},{8, {6, 9}}, {9, {7, 8}}});
	std::cout << "GRAFO PARTENZA:\n" << grafo_start << "\n\n";
	// grafo bfs effettuato con container fifo
	undirected_graph<int> grafo_fifo = graph_visit(grafo_start, 1, f);
	std::cout << "GRAFO FIFO: ";
	std::cout << grafo_fifo;
	grafo_dot(grafo_fifo, "grafo_fifo.dot");
	
	// grafo dfs effettuato con container lifo
	undirected_graph<int> grafo_lifo = graph_visit(grafo_start, 1, l);
	std::cout << "GRAFO LIFO: ";
	std::cout << grafo_lifo;
	grafo_dot(grafo_lifo, "grafo_lifo.dot");


	undirected_graph<int> grafo_dfs_rico = recursive_dfs(grafo_start, 1);
	std::cout << "GRAFO DFS RICORSIVO: ";
	std::cout << grafo_dfs_rico;
	grafo_dot(grafo_dfs_rico, "grafo_dfs_rico.dot");
	
	int sorgente = 1;
	str_res_dijkstra<int> res_dj = dijkstra(grafo_start, sorgente);
	std::cout << "\nALGORITMO DIJKSTRA:\n";
	for (const auto& [nodo, nodo_pred] : res_dj.mappa_predecessori ) {
		std::cout << "il predecessore di " << nodo << " è il nodo : " << nodo_pred << "\n";
	}
	for (const auto& [nodo, valore] : res_dj.mappa_distanze ) {
		std::cout << "il nodo: " << nodo << " dista " << valore << " dal nodo sorgente " << sorgente << "\n";
	}
	std::cout << "GRAFO DIJKSTRA:\n" << res_dj.grafo_dj;
	
	
	// una seconda prova con un nuovo grafo, funziona ma evito la stampa
//	undirected_graph<int> grafo_start2({{1, {2}},{2, {1,3}},{3, {2,4}},{4, {3}}});
//	int sorgente2 = 4;
//	str_res_dijkstra<int> res_dj2 = dijkstra(grafo_start2, sorgente2);
//	for (const auto& [nodo, nodo_pred] : res_dj2.mappa_predecessori ) {
//		std::cout << "il predecessore di " << nodo << " è il nodo : " << nodo_pred << "\n";
//	}
//	for (const auto& [nodo, valore] : res_dj2.mappa_distanze ) {
//		std::cout << "il nodo: " << nodo << " dista " << valore << " dal nodo sorgente " << sorgente2 << "\n";
//	}
	
}
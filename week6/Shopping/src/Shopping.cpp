//============================================================================
// Name        : Coin.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
						property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

class EdgeAdder {
	Graph &G;
	EdgeCapacityMap &capacitymap;
	ReverseEdgeMap &revedgemap;

public:
	EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap,
			ReverseEdgeMap& revedgemap) :
			G(G), capacitymap(capacitymap), revedgemap(revedgemap) {
	}

	void addEdge(int from, int to, long capacity) {
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};

void do_case() {
	long n, m,s;
	cin >> n >> m >> s;
	Graph G(n ); // n vertices

	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	Vertex sink = add_vertex(G);
	for (int i = 0; i  < s ; i ++){
		int shop ;
		cin >> shop;
		eaG.addEdge(shop,sink,1);
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		eaG.addEdge(a,b,1);
		eaG.addEdge(b,a,1);
	}
	long flow = push_relabel_max_flow(G,0,sink);
//	long flow = edmonds_karp_max_flow(G, 0, sink);
//	cout << final_flow << flow;
	if (s == flow)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}


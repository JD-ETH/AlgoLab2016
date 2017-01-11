//============================================================================
// Name        : stage.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef Delaunay::Edge_circulator Edge_circulator;
using namespace std;

static long h;
bool test_intersection(Delaunay& T, vector<long>& vec) {
	K::Point_2 pt(vec[0], vec[1]);
	Delaunay::Vertex_handle v = T.nearest_vertex(pt);
	K::FT dis = CGAL::squared_distance(v->point(),pt);
	return dis<((vec[2]+h)*(vec[2]+h)); // violated
}

void do_case() {
	// Read;
	int m, n;
	cin >> m >> n;
	vector<vector<long> > players(m, vector< long>(3, -1));
	for (int i = 0; i < m; i++) {
		cin >> players[i][0] >> players[i][1] >> players[i][2];
	}
	cin >> h;
	vector<K::Point_2> lights(n);
	for (int i = 0; i < n; i++) {
		cin >> lights[i];
	}
	Delaunay T;
	T.insert(lights.begin(), lights.end());
	// For every player, Delaunay and test neighbors
	bool Solution_Flag = false;
	for (int i = 0; i < m; i++) {
		if(!test_intersection(T, players[i])) {
			cout << i << " ";
			Solution_Flag = true;
		}
	}

	if (!Solution_Flag){ // Incase no solution found
		int lights_min = 0;
		int lights_max = n-1;
		while(lights_min != lights_max){
			int lights_curr = (lights_min + lights_max+1) /2;
			Delaunay T;
			T.insert(lights.begin(), lights.begin()+lights_curr+1);
			bool Solution_Flag = false;
			for (int i = 0; i < m; i++) {
				if(!test_intersection(T, players[i])) {
					Solution_Flag = true;
				}
			}
			if (Solution_Flag) {lights_min = lights_curr;}
			else {lights_max = lights_curr-1;}
			//cout << "max:" << lights_max<< "min: "<< lights_min << endl;
		}
		Delaunay T;
		T.insert(lights.begin(), lights.begin()+lights_max+1);
		for (int i = 0; i < m; i++) {
			if(!test_intersection(T, players[i])) {
				cout << i << " ";
			}
		}
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		do_case();
		cout << endl;
	}
	return 0;
}

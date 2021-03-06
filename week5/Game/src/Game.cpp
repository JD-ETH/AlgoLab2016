//============================================================================
// Name        : Game.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

static vector<vector<int> > trans;
static vector<int> choices;
static vector<vector<int> > memo;
static int n;
int solve(int p, int opt) {
	if (p == n) return 0;
	if (memo[p][opt] == -1) {
		int result;
		if (opt) {   // if 1, do maximization
			result = 0;
			for (int i = 0; i < choices[p]; i++)
				result = max(result, solve(trans[p][i], 0));

		} else {   // if 0, do minimization
			result = 50001;
			for (int i = 0; i < choices[p]; i++)
				result = min(result, solve(trans[p][i], 1));
		}
		result++;
		memo[p][opt] = result;
		return result;
	} else
		return memo[p][opt];
}

void do_case() {
	int m;
	cin >> n >> m;
	int r_start, b_start;
	cin >> r_start >> b_start;
	trans.clear();
	trans.resize(n + 1);
	choices.clear();
	choices.resize(n + 1);
	memo.clear();
	memo.resize(n + 1);
	while (m--) {
		int u, v;
		cin >> u >> v;
		trans[u].push_back(v);
	}
	for (int i = 0; i < n + 1; i++) {
		sort(trans[i].begin(), trans[i].end());
		choices[i] = trans[i].size();
		memo[i] = vector<int>(2, -1);
	}
	int min_Hol = solve(r_start, 0);
	int min_Mar = solve(b_start, 0);
//	cout << "Step number for Hol and Mar " << min_Hol << " " << min_Mar << endl;
	if (min_Hol == min_Mar)
		cout << ((min_Hol+1) % 2) << endl;
	else
		cout << (min_Hol > min_Mar) << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}

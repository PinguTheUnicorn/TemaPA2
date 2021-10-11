#include <bits/stdc++.h>

#define INF ((int)1e9)  // valoare de infinit

using namespace std;

int N, K, T;  // datele de intrare
int max_count = 0;  // cea mai lunga subsecventa
vector<int> global_solution;  // solutia

// functia este preluata din laboratorul 3
// programare dinamica 1
vector<int> coin_change(int S, vector<int> v, int n) {
	vector<int> dp(S + 1, INF);
	dp[0] = 0;
	for(int i = 1; i <= S; i++) {
		for(int j = 0; j < n; j++) {
			if (v[j] <= i) {
				dp[i] = min(dp[i], dp[i - v[j]] + 1);
			}
		}
	}

	// fata de laborator, intorc tot vectorul
	return dp;
}

void verificare_secvente(vector<int> dp, vector<int> v) {
	int count = 0;

	// se cauta secventa maxima posibila pentru acest set de date
	for(int i = 1; i < dp.size(); i++) {
		// daca suma actuala se poate forma cu mai maxim T piese
		// secventa nu s-a spart si se numara
		if (dp[i] <= T) {
			count++;
		} else {
			// altfel, s-a ajuns la finalul secventei
			// se verifica daca este mai mare decat secventa maxima actuala
			// se se salveaza in caz afirmativ
			if (count > max_count) {
				max_count = count;
				global_solution.clear();
				for(int j = 0; j < v.size(); j++) {
					global_solution.push_back(v[j]);
				}
			}

			// se reseteaza lungimea secventei
			count = 0;
		}
	}

	// se face verificarea secventei inca odata pentru
	// ultima secventa gasita(in caz ca a tine pana la finalul vectorului)
	if (count > max_count) {
		max_count = count;
		global_solution.clear();
		for(int j = 0; j < v.size(); j++) {
			global_solution.push_back(v[j]);
		}
	}
}

// se cauta o solutie pentru un set de date valid
void findSeq(vector<int> &solution, vector<int> &domain, int stop) {
	vector<int> v;

	// sunt selectate valorile pentru setul de date
	for(int i = 0; i < stop; i++) {
		v.push_back(domain[solution[i]]);
	}

	// se genereaza vectorul cu numarul de elemente pentru fiecare suma
	vector<int> dp = coin_change(T * v[stop - 1], v, stop);

	// se cauta daca exista secvente de lungime mai mare decat cea maxima
	verificare_secvente(dp, v);
}

// functia de generat combinari dintr-un domeniu dat
// preluata din laborator
void back(int step, int stop, vector<int> &domain, vector<int> &solution) {
	if (step == stop) {
		findSeq(solution, domain, stop);
		return;
	}

	for(int i = solution[step - 1] + 1; i < domain.size(); i++) {
		solution[step] = i;
		back(step + 1, stop, domain, solution);
	}
}

int main() {
	// se citesc datele de intrare
	ifstream fin("lego.in");
	fin >> N >> K >> T;
	fin.close();

	vector<int> solution(K);
	solution[0] = 0;
	vector<int> domain(N);

	// se initializeaza domeniul
	for(int i = 0; i < N; i++) {
		domain[i] = i + 1;
	}

	// se incepe cautarea solutiilor
	back(1, K, domain, solution);

	// afisare raspuns
	ofstream fout("lego.out");
	fout << max_count << "\n";
	for(int i = 0; i < global_solution.size(); i++) {
		fout << global_solution[i] << " ";
	}
	fout.close();
	return 0;
}

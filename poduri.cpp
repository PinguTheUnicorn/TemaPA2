#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, M;  // dimensiunile hartii
	int X, Y;  // coordonatele lui Gigel

	// se citesc datele
	ifstream fin("poduri.in");

	fin >> N >> M;
	fin >> X >> Y;
	vector<vector<char>> harta(N, vector<char>(M));

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			fin >> harta[i][j];
		}
	}

	fin.close();

	// se aplica algoritmul bfs
	// se retin coordonatele de start si nivelul de cautare
	pair<int, int> coordonate_start(X - 1, Y - 1);
	pair<pair<int, int>, int> p(coordonate_start, 1);

	queue<pair<pair<int, int>, int>> q;
	q.push(p);

	ofstream fout("poduri.out");

	// se incepe cautarea
	while (!q.empty()) {
		// se ia punctul curent din matrice
		pair<pair<int, int>, int> p_q = q.front();
		q.pop();
		int x = p_q.first.first;
		int y = p_q.first.second;
		int nivel = p_q.second;

		// daca se afla pe prima sau ultima linie
		// si poate sa mearga in directia respectiva
		if ((harta[x][y] == 'V' || harta[x][y] == 'D') && (x == 0 || x == N - 1)) {
			// s-a gasit prima iesire, se afiseaza si se iese din program
			fout << nivel;
			fout.close();
			return 0;
		}

		// daca se afla pe prima sau ultima coloana
		// si poate sa mearga in directia respectiva
		if ((harta[x][y] == 'O' || harta[x][y] == 'D') && (y == 0 || y == M - 1)) {
			// s-a gasit prima iesire, se afiseaza si se iese din program
			fout << nivel;
			fout.close();
			return 0;
		}

		// daca se poate duce sus
		// se adauga punctul in coada
		if (harta[x][y] == 'V' || harta[x][y] == 'D') {
			if (harta[x-1][y] != '.') {
				pair<int, int> p1(x-1, y);
				pair<pair<int, int>, int> p2(p1, nivel + 1);
				q.push(p2);
			}
		}

		// daca se poate duce jos
		// se adauga punctul in coada
		if (harta[x][y] == 'V' || harta[x][y] == 'D') {
			if (harta[x+1][y] != '.') {
				pair<int, int> p1(x+1, y);
				pair<pair<int, int>, int> p2(p1, nivel + 1);
				q.push(p2);
			}
		}

		// daca se poate duce in stanga
		// se adauga punctul in coada
		if (harta[x][y] == 'O' || harta[x][y] == 'D') {
			if (harta[x][y-1] != '.') {
				pair<int, int> p1(x, y-1);
				pair<pair<int, int>, int> p2(p1, nivel + 1);
				q.push(p2);
			}
		}

		// daca se poate duce in dreapta
		// se adauga punctul in coada
		if (harta[x][y] == 'O' || harta[x][y] == 'D') {
			if (harta[x][y+1] != '.') {
				pair<int, int> p1(x, y+1);
				pair<pair<int, int>, int> p2(p1, nivel + 1);
				q.push(p2);
			}
		}

		// se marcheaza coordonata actuala ca fiind
		// vizitata prin modificarea valorii in "."
		harta[x][y] = '.';
	}

	// daca nu s-a gasit nicio iesire, se afiseaza -1
	fout << -1;
	fout.close();

	return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define INF 10000000

class Graph {
private:
	int n;
	int** mat;
public:
	Graph(int n) {
		this->n = n;
		int** mat = new int* [n];
		for (int i = 0; i < n; i++) mat[i] = new int[n];
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) mat[i][j] = 0;
		this->mat = mat;
		this->enter_elem();
	}
	~Graph() {
		for (int i = 0; i < n; i++) delete[] mat[i];
		delete[] mat;
	}
	void enter_elem() {
		cout << "\nEnter matrix of dist:\t\t(use space between elements and use only numbers)\nPlease note that you are entering the mirror part of the matrix along the main diagonal\n\n";
		for (int i = 0; i < this->n; i++) {
			string space(i * 2, ' ');
			cout << i + 1 << " vertex distances (" << n - i <<" values):" + space;
			for (int j = i; j < n; j++) {
				cin >> this->mat[i][j];
				if (this->mat[i][j] == 0) this->mat[i][j] = INF;
				this->mat[i][j] = this->mat[j][i];
			}
		}
	}
	void print_mat() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (mat[i][j] == INF) cout << 0 << ' ';
				else cout << mat[i][j] << ' ';
			}
			cout << endl;
		}
	}
	void prim_kras() {
		int i, j, i1, j1, len = 0, k = 0, dist_min;
		int* col = new int[n];
		int* res1 = new int[n-1];
		int* res2 = new int[n-1];
		for (i = 0; i < n; i++) col[i] = i;
		while (k < n - 1) {
			dist_min = INT_MAX;
			for (i1 = 0; i1 < n - 1; i1++) {
				for (j1 = i1 + 1; j1 < n; j1++) {
					if (mat[i1][j1] < dist_min and col[i1] != col[j1]) {
						dist_min = mat[i1][j1];
						i = i1; j = j1;
					}
				}
			}

			len += dist_min;
			res1[k] = i;
			res2[k] = j;
			j1 = col[j];

			for (int m = 0; m < n; m++)
				if (col[m] == j1) col[m] = col[i];
			k++;
		}
		cout << "\nEages of minimum dist: ";
		for (i = 0; i < n - 1; i++) cout <<" (" << res1[i] + 1 << ", " << res2[i] + 1 <<')';
		cout << "\nLength = " << len;
	}
	void dijkstra() {
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (mat[i][j] == INF) mat[i][j] = 0;
		int start;
		cout << "\nEnter start vertex: ";
		cin >> start;
		int* distance = new int[n];
		int index, m=start - 1;
		bool* visited = new bool[n];
		for (int i = 0; i < n; i++) {
			distance[i] = INT_MAX; visited[i] = 0;
		}
		distance[m] = 0;
		for (int c = 0; c < n - 1; c++) {
			int min = INT_MAX;
			for (int i = 0; i < n; i++)
				if (!visited[i] && distance[i] < min) { min = distance[i]; index = i; }
			visited[index] = 1;
			for (int i = 0; i < n; i++)
				if (!visited[i] && mat[index][i] && distance[index] != INT_MAX && distance[index] + mat[index][i] < distance[i])
					distance[i] = distance[index] + mat[index][i];
		}
		cout << "\nLength of the path from the start vertex to the rest:\t\n";
		for (int i = 0; i < n; i++) if (distance[i] != INT_MAX)
			cout << start << " > " << i + 1 << " = " << distance[i] << endl;
		else cout << start  << " > " << i + 1 << " = " << "There is no way" << endl;
	}

};


int main() {
	cout << "Welcome.\n\n";

	int n;
	cout << "Enter number of vertex: ";
	cin >> n;

	Graph graph(n);
	int option;
	link:cout << "\n\nEnter the algorithm:\n1 - Dijkstra\n2 - Primo-Kraskal\n3 - View your weigth matrix\n0 - Exit\n\nEnter number: ";
	cin >> option;
	switch (option) {
		case 0: 
			break;
		case 1: 
			graph.dijkstra();
			goto link;
			break;
		case 2: graph.prim_kras();
			goto link;
			break;
		case 3:
			cout << "\n\n";
			graph.print_mat();
			cout << "\n\n";
		default: 
			"\nError entery!";
			goto link;
			break;
	}
}

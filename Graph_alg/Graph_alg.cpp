// connecting libraries
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// creating a graph class
class Graph {
private:
	int n; // number of vertices
	int** mat; // weight matrix
public:
	// class constructor
	Graph(int n) {
		this->n = n;
		int** mat = new int* [n];
		for (int i = 0; i < n; i++) mat[i] = new int[n];
		// filling the weight matrix with zeros
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) mat[i][j] = 0;
		this->mat = mat;
	}
	// class destroyer
	~Graph() {
		for (int i = 0; i < n; i++) delete[] mat[i];
		delete[] mat;
	}
	// method for entering elements into a weight matrix
	void enter_elem() {
		link1: cout << "\nEnter matrix of dist:\t(use space between elements and use only numbers and if row is end push enter)\nPlease note that you are entering the mirror part of the matrix along the main diagonal\n\n";
		for (int i = 0; i < n; i++) {
			string space(i * 2, ' ');
			cout << i + 1 << " vertex distances (" << n - i <<" values):" + space;
			for (int j = i; j < n; j++) {
				cin >> mat[i][j];
				// checking the entered value
				if (!cin) {
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "\nInput Error\n";
					goto link1;
				}
				// the matrix is ​​entered in a mirror way, that is, the graph is undirected
				mat[j][i] = mat[i][j];
			}
		}
	}
	// method for displaying the weight matrix on the screen
	void print_mat() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cout << mat[i][j] << ' ';
			cout << endl;
		}
	}
	// method implementing Prim Kruskal's algorithm
	void prim_kras() {
		int i, j, i1, j1, len = 0, k = 0, dist_min;
		bool check = 0;
		int* col = new int[n];
		int* res1 = new int[n-1];
		int* res2 = new int[n-1];
		for (i = 0; i < n; i++) col[i] = i;
		while (k < n - 1) {
			dist_min = INT_MAX;
			for (i1 = 0; i1 < n - 1; i1++) {
				for (j1 = i1 + 1; j1 < n; j1++) {
					if (mat[i1][j1] < dist_min and col[i1] != col[j1] and mat[i1][j1] != 0) {
						dist_min = mat[i1][j1];
						i = i1; j = j1;
					}
				}
			}
			
			res1[k] = i;
			res2[k] = j;

			for (int p = 0; p < k; p++) if (res1[p] == res1[k] and res2[i] == res2[k]) check = 1;
			if(!check)
				len += dist_min;
			check = 0;

			j1 = col[j];

			for (int m = 1; m <= n; m++)
				if (col[m] == j1) col[m] = col[i];
			k++;
		}
		cout << "\nEages of minimum dist: ";
		for (i = 0; i < n - 1; i++) cout <<" (" << res1[i] + 1 << ", " << res2[i] + 1 <<')';
		cout << "\nLength = " << len;
	}
	// method implementing Dijkstra's algorithm
	void dijkstra() {
		int start; // vertex from
		link3:cout << "\nEnter start vertex: ";
		cin >> start;
		// checking the entered value
		if (!cin or start > n + 1 or start <=0) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "\nInput Error";
			goto link3;
		}
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
				if (!visited[i] && mat[index][i] != 0 && distance[index] != INT_MAX && distance[index] + mat[index][i] < distance[i])
					distance[i] = distance[index] + mat[index][i];
		}
		cout << "\nLength of the path from the start vertex to the rest:\t\n";
		for (int i = 0; i < n; i++) if (distance[i] != INT_MAX)
			cout << " Length of vertex " << start << " to vertex " << i + 1 << ": " << distance[i] << endl;
		else cout << " Length of vertex " << start << " to vertex " << i + 1 << ": There is no way\n";
	}

};


int main() {
	cout << "Welcome.\n";

	int n;
	link2:cout << "\n\nEnter number of vertex: ";
	cin >> n;
	// checking the entered value
	if (!cin) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nInput Error";
		goto link2;
	}

	Graph graph(n);

	int option;
	link:cout << "\n\nEnter the option:\n1 - Input of weight matrix \n2 - Dijkstra's alghoritm\n3 - Prim Kruskal's algorithm\n4 - View your weigth matrix\n0 - Exit\n\nEnter number: ";
	cin >> option;
	// checking the entered value
	if (!cin) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nInput Error";
		goto link;
	}
	// calling a method depending on the selected item
	switch (option) {
		case 0: 
			delete &graph;
			break;
		case 1:
			graph.enter_elem();
			goto link;
			break;
		case 2: 
			graph.dijkstra();
			goto link;
			break;
		case 3:
			graph.prim_kras();
			goto link;
			break;
		case 4:
			cout << "\n\n";
			graph.print_mat();
			cout << "\n\n";
		default: 
			cout << "\nYou entered a number that is not included in the instructions!";
			goto link;
			break;
	}
}
// end of code

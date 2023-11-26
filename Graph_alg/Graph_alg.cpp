#include <iostream>
#include <string>
using namespace std;

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
				this->mat[j][i] = mat[i][j];
			}
		}
	}
	void print_mat() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << this->mat[i][j] << ' ';
			cout << endl;
		}
	}
	void prim_kras() {
	}

};


int main() {
	cout << "Welcome.\n\n";

	int n;
	cout << "Enter number of vertex: ";
	cin >> n;

	Graph graph(n);
	graph.enter_elem();
	graph.print_mat();
}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool is_int(const string& s) {
	return s.find_first_not_of("0123456789") == string::npos;
}

int* array_from_string(string s, int n) {
	int* arr = new int[n];
	int wall = 0;
	int ind = 0;
	for (int i = 0; i < s.length() - 1; i++) {
		if (s[i] == ' ') {
			if (!is_int(s.substr(wall, i - wall)))
				arr[ind++] = 0;
			else
				arr[ind++] = stoi(s.substr(wall, i - wall));
			wall = i;
		}
	}
	return arr;
}

void prim_kras() {
	int n;
	cout << "Enter number of vertex: ";
	cin >> n;

	int** distmat = new int* [n];
	for (int i = 0; i < n; i++) distmat[i] = new int[n];
	for (int i = 0; i < n; i++)for (int j = 0; j < n; j++) distmat[i][j] = 0;

	cout << "Enter matrix of dist:\n";
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		distmat[i] = array_from_string(s, n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << distmat[i][j] << ' ';
		cout << endl;
	}
}

int main() {
	cout << "Welcome.\n\n";
	prim_kras();
}

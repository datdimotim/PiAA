#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int bestNum = 0;

class Field
{
	int size;
	int **field;
	int number;
	int scale;
	bool even;

public:
	Field(int s) : field(nullptr), number(0), scale(s), even(true) {
		if (size == 0) {
			field = 0;
			//cout << "empty" << endl;
		}
		if (s % 2 == 0) {
			size = 2;
			scale = scale / 2;
		}
		else if (s % 3 == 0) {
			size = 3;
			scale = scale / 3;
		}
		else if (s % 5 == 0) {
			size = 5;
			scale = scale / 5;
		}
		else if (s % 2 == 1) {
			even = false;
			size = s;
		}
		field = new int*[size];
		//field[0] = new int[size*size];
		for (size_t i = 0; i != size; ++i) {
			field[i] = new int[size];
			//field[i] = field[i-1] + size;
		}
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size; ++j)
				field[i][j] = 0;
		if (!even) {
			insert();
		}
		//cout << "full" << endl;	
	}
	Field(Field const &other) : size(other.size), field(nullptr), number(other.number), scale(other.scale) {
		field = new int*[size];
		for (int i = 0; i < size; i++)
			field[i] = new int[size];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				field[i][j] = other.field[i][j];
	}
	Field& operator=(Field const &other) {
		if (&other != this) {
			for (int i = 0; i < size; i++)
				delete[] field[i];
			delete[] field;
		}
		number = other.number;
		size = other.size;
		scale = other.scale;
		field = new int*[size];
		//field[0] = new int[size*size];
		for (size_t i = 0; i < size; ++i) {
			field[i] = new int[size];
			//field[i] = field[i-1] + size;
		}
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				field[i][j] = other.field[i][j];
	}
	~Field() {
		for (int i = 0; i < size; i++)
			delete[] field[i];
		delete[] field;
		field = nullptr;
		size = 0;
		number = 0;
	}
	bool geteven() {
		return even;
	}
	int getnumber() {
		return number;
	}
	int getsize() {
		return size;
	}
	int getscale() {
		return scale;
	}
	int getval(int i, int j) {
		//cout << *field[i,j] * scale << endl;
		return field[i][j];
	}
	void setval(int i, int j, int k) {
		field[i][j] = k;
	}
	void printField() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << field[i][j] << " ";
			}
			cout << endl;
		}
	}
	bool mayInsert(int i, int j, int n) {
		//cout<<"am in mayinsert" << endl;
		if ((i + n) > size || (j + n) > size) {
			return false;
		}
		for (int y = i; y < i + n; y++)
			for (int x = j; x < j + n; x++)
				if (field[y][x] != 0) {
					return false;
				}
		return true;
	}
	void insertSquare(int i, int j, int n) {
		//cout<<"am in insertSquare" << endl;
		for (int y = i; y < i + n; y++) {
			//	cout<<"am in 1st loop" << endl;
			for (int x = j; x < j + n; x++) {
				//		cout<<"am in 2nd loop" << endl;
				field[y][x] = n;
			}
		}
		++number;
	}
	bool IsThereFree(int i, int j) {
		//cout<<"am in aretherefree" << endl;
		for (int y = i; y < size; y++)
			for (int x = 0; x < size; x++)
				if (field[y][x] == 0)
					return true;
		return false;
	}
	int FindFreeStr(int i, int j) {
		//cout<<"am in FindFreeStr" << endl;
		for (int y = i; y < size; y++)
			for (int x = 0; x < size; x++)
				if (field[y][x] == 0) {
					return y;
				}
	}
	int FindFreeCol(int i, int j) {
		//cout<<"am in FindFreeCol" << endl;
		for (int y = i; y < size; y++)
			for (int x = 0; x < size; x++)
				if (field[y][x] == 0) {
					return x;
				}
	}
	void del(int i, int j) {
		int val = field[i][j];
		for (int y = i; y < i + val; y++)
			for (int x = j; x < j + val; x++)
				field[y][x] = 0;
	}
	void printRez() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (field[i][j] != 0) {
					cout << i + 1 << " " << j + 1 << " " << field[i][j] << endl;
					del(i, j);
				}
			}
		}
	}
	void insert() {
		int siz = (size / 2) + 1;
		int si = size / 2;
		//cout << siz << si << endl;
		insertSquare(0, 0, siz);
		insertSquare(0, siz, si);
		insertSquare(siz, 0, si);
		//insertSquare(si, siz, 1);
	}
	void retScale(Field other) {
		int str = 0;
		int col = 0;
		int val = 0;
		this->~Field();
		size = other.getsize() * scale;
		number = other.getnumber();
		scale = other.getscale();
		field = new int*[size];
		for (size_t i = 0; i != size; ++i) {
			field[i] = new int[size];
		}
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size; ++j)
				field[i][j] = 0;
		for (size_t i = 0; i < other.getsize(); ++i) {
			for (size_t j = 0; j < other.getsize(); ++j) {
				str = FindFreeStr(i, j);
				col = FindFreeCol(i, j);
				val = other.getval(str / scale, col / scale);
				insertSquare(str, col, (other.getval(str / scale, col / scale)*scale));
				if (!IsThereFree(str, col)) {
					return;
				}
			}
		}
	}
};

Field bestShape(0);

Field arrangement(Field field, int i, int j) {
	//cout << "in it";
	//cout << field.getnumber() << endl;
	for (int n = 1; n < field.getsize(); n++) {
		if (field.getnumber() > bestNum) {
			return field;
		}
		Field shape = field;
		if (shape.mayInsert(i, j, n)) {
			shape.insertSquare(i, j, n);			//cout << endl;
													//j++;
			if (shape.IsThereFree(i, j)) {
				shape = arrangement(shape, shape.FindFreeStr(i, j), shape.FindFreeCol(i, j));
				//shape.printField();
			}
			else if (bestNum >= shape.getnumber()) {
				bestShape = shape;
				bestNum = shape.getnumber();
			}
		}
	}
	return field;
}

Field ovonarrangement(Field field, int i, int j) {
	//cout << "in it";
	//cout << field.getnumber() << endl;
	for (int n = ((field.getsize() / 2) - 1); n > 0; n--) {
		if (field.getnumber() > bestNum) {
			return field;
		}
		Field shape = field;
		if (shape.mayInsert(i, j, n)) {
			shape.insertSquare(i, j, n);			//cout << endl;
													//j++;
			if (shape.IsThereFree(i, j)) {
				shape = ovonarrangement(shape, shape.FindFreeStr(i, j), shape.FindFreeCol(i, j));
				//shape.printField();
			}
			else if (bestNum >= shape.getnumber()) {
				bestShape = shape;
				bestNum = shape.getnumber();
			}
		}
	}
	return field;
}

int main() {
	//unsigned int start_time =  clock();

	int size = 0;
	cin >> size;
	bestNum = size*size;
	Field A(size);
	if (A.geteven()) {
		A = arrangement(A, 0, 0);

		A.retScale(bestShape);
		//A.printField();
		cout << bestNum << endl;
		A.printRez();
	}
	else {
		A = ovonarrangement(A, A.FindFreeStr(0, 0), A.FindFreeCol(0, 0));
		//bestShape.printField();
		cout << bestNum << endl;
		bestShape.printRez();
	}
	// unsigned int end_time = clock();
	// unsigned int search_time = end_time - start_time;
	// cout << "runtime = " << search_time;
}
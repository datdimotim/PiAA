#include <iostream>

struct Square_state
{
	int x;
	int y;
	int Square_size;
};

class Square
{
private:
	int *mas;
	int size;
	int kol_of_squares;
	Square_state *Square_st;

	void Insert(int x, int y, int size);
	void Insert(int x, int y, int size, Square_state &Square_size);
	bool Check_this_position(int x, int y, int size);
	void Remove_elements(int x, int y, int size);


	void  Backtracking_of_square(int x, int y, int size);
	bool  Backtracking(const int &x0, const int &y0, const int &size, const int &kol_of_squares, int r, int x, int y);

public:
	Square(int size);
	~Square();

	void Realization();
	void Print_squares_positions();
	
};


Square::Square(int size)
{
	mas = new int[(size + 1)*(size + 1)]();
	this->kol_of_squares = 0;
	this->size = size;
}

Square::~Square()
{
	delete mas;
}


void Square::Print_squares_positions()
{
	std::cout << kol_of_squares;
	for (int i = 0; i < kol_of_squares; i++)
		std::cout << std::endl << Square_st[i].x + 1 << " " << Square_st[i].y + 1 << " " << Square_st[i].Square_size;
}


void Square::Insert(int x, int y, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mas[(i + y)*this->size + (j + x)] = size;
	kol_of_squares++;
}


void Square::Insert(int x, int y, int size, Square_state &Square_size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mas[(i + y)*this->size + (j + x)] = size;

	Square_size.x = x;
	Square_size.y = y;
	Square_size.Square_size = size;
	kol_of_squares++;
}

bool Square::Check_this_position(int x, int y, int size)
{
	if ((size > this->size - x)
		||
		(size > this->size - y)) return 0;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (mas[(i + y)*this->size + (j + x)]) return 0;

	return 1;
}


void Square::Remove_elements(int x, int y, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mas[(i + y)*this->size + (j + x)] = 0;

	kol_of_squares--;
}


void Square::Realization()
{
	if (!(size % 2))
	{
		Square_st = new Square_state[4];
		Insert(0, 0, size / 2, Square_st[0]);
		Insert(0, size / 2, size / 2, Square_st[1]);
		Insert(size / 2, 0, size / 2, Square_st[2]);
		Insert(size / 2, size / 2, size / 2, Square_st[3]);

		return;
	}
	if (!(size % 3))
	{
		Square_st = new Square_state[6];
		Insert(0, 0, size * 2 / 3, Square_st[0]);
		Insert(0, size * 2 / 3, size / 3, Square_st[1]);
		Insert(size * 2 / 3, 0, size / 3, Square_st[2]);
		Insert(size / 3, size * 2 / 3, size / 3, Square_st[3]);
		Insert(size * 2 / 3, size / 3, size / 3, Square_st[4]);
		Insert(size * 2 / 3, size * 2 / 3, size / 3, Square_st[5]);

		return;
	}
	if (!(size % 5))
	{
		Square_st = new Square_state[8];
		Insert(0, 0, size * 3 / 5, Square_st[0]);
		Insert(size * 3 / 5, size / 5, size * 2 / 5, Square_st[1]);
		Insert(size / 5, size * 3 / 5, size * 2 / 5, Square_st[2]);
		Insert(size * 3 / 5, size * 3 / 5, size * 2 / 5, Square_st[3]);

		Backtracking(0, 0, size, 8, 4, size * 3 / 5, 0);
		return;
	}


	int m = size / 2 + 1;
	Insert(0, 0, m);
	Insert(0, m, m - 1);
	Insert(m, 0, m - 1);

	Backtracking_of_square(m - 1, m - 1, m);

	Square_st[kol_of_squares - 3].x = 0; Square_st[kol_of_squares - 3].y = 0; Square_st[kol_of_squares - 3].Square_size = m;
	Square_st[kol_of_squares - 2].x = 0; Square_st[kol_of_squares - 2].y = m; Square_st[kol_of_squares - 2].Square_size = m - 1;
	Square_st[kol_of_squares - 1].x = m; Square_st[kol_of_squares - 1].y = 0; Square_st[kol_of_squares - 1].Square_size = m - 1;
}




void Square::Backtracking_of_square(int x, int y, int size)
{

	for (int i = 2; i < size*size; i++)
	{
		Square_st = new Square_state[i + 3];
		if (Backtracking(x, y, size, i, 0, 0, 0)) break;
		delete Square_st;
	}

}


bool Square::Backtracking(const int &x0, const int &y0, const int &size, const int &kol_of_squares, int r, int x, int y)
{
	if (kol_of_squares == r)
	{
		for (int i = 0; i < size; i++)
		{
			if (!(mas[(y0 + i)*this->size + (x0 + size - 1)]
				&&
				mas[(y0 + size - 1)*this->size + (x0 + i)])) return false;
		}

		return true;
	}

	while ((mas[(y0 + y)*this->size + (x0 + x)]) || (x == size))
	{
		if (x >= size)
		{
			if (y == size) return true;
			y++;
			x = 0;
		}
		else x++;
	}


	for (int i = 1; i<size; i++)
	{
		if (Check_this_position(x0 + x, y0 + y, i))
		{
			Insert(x0 + x, y0 + y, i, Square_st[r]); r++;

			if (Backtracking(x0, y0, size, kol_of_squares, r, x + i, y)) return true;

			Remove_elements(x0 + x, y0 + y, i); r--;
		}
	}

	return false;
}



int main()
{
	int Size_of_big_square;
	std::cin >> Size_of_big_square;
	Square Layout(Size_of_big_square);
	Layout.Realization();

	Layout.Print_squares_positions();
	return 0;
}
#include <iostream>
using namespace std;
const char SYMFORFREE = '*';
const int LENGTH = 3;
int GlobalCounter = 0;
void PrintArea(const char arr[][LENGTH]);
void FillArea(char arr[][LENGTH]);
void CheckerFreeArea(char arr[][LENGTH], int row, int col, const char sym, bool& temp, bool& refresh);
bool VerticalChecker(char arr[][LENGTH]);
bool HorizontalChecker(char arr[][LENGTH]);
bool WinChecker(char arr[][LENGTH]);
bool DiagonalChecker(char arr[][LENGTH]);
void GameStart();
void Clear();

int main() {
	setlocale(LC_ALL, "Rus");
	GameStart();
	return 0;
}
void GameStart()
{
	char arr[LENGTH][LENGTH]{};
	FillArea(arr);
	bool flag = true, temp = true, changeSym = false, refresh = false;
	char sym = ' ';
	int move, col = {}, row = {};
	while (flag)
	{
		PrintArea(arr);
		temp = true;
		refresh = true;
		sym = changeSym ? 'O' : 'X';
		cout << "Make your move (1 - 9) " << sym << endl;
		cin >> move;
		if (move <= LENGTH)
		{
			row = 0;
			col = move % 3 == 1 ? 0 : move % 3 == 2 ? 1 : move % 3 == 0 ? 2 : 0;
			CheckerFreeArea(arr, row, col, sym, temp, refresh);
		}
		else if (move <= LENGTH * 2)
		{
			row = 1;
			col = move % 3 == 1 ? 0 : move % 3 == 2 ? 1 : move % 3 == 0 ? 2 : 0;
			CheckerFreeArea(arr, row, col, sym, temp, refresh);
		}
		else if (move <= LENGTH * 3)
		{
			row = 2;
			col = move % 3 == 1 ? 0 : move % 3 == 2 ? 1 : move % 3 == 0 ? 2 : 0;
			CheckerFreeArea(arr, row, col, sym, temp, refresh);
		}
		else
		{
			Clear();
			temp = false;
			refresh = false;
			cout << "Out of range! Try again" << endl;
		}
		if (temp) {
			changeSym = !changeSym;
		}
		if (refresh)
		{
			Clear();
		}
		if (WinChecker(arr) || GlobalCounter > 8)
		{
			flag = false;
			PrintArea(arr);
		}
	}
	if (GlobalCounter >= 8)
	{
		cout << "DRAW!" << endl;
	}
	else
	{
		cout << sym << " Win!" << endl;
	}
}
bool WinChecker(char arr[][LENGTH])
{
	bool flag = false;
	int counter = 0;
	flag = HorizontalChecker(arr) ? !flag : VerticalChecker(arr) ? !flag : DiagonalChecker(arr) ? !flag : flag; // возможно стоит вернуть if
	return flag;
}

bool DiagonalChecker(char arr[][LENGTH])
{
	bool flag = false;
	int counter = 0, temp = 0;
	for (int i = 0; i < LENGTH - 1; i++)
	{
		if (arr[i][temp] != SYMFORFREE && arr[i][temp] == arr[i + 1][temp + 1])
		{
			counter++;
		}
		if (counter >= 2) {
			flag = true;
		}
		temp++;
	}
	counter = 0;
	if (flag == false)
	{
		temp = LENGTH - 1;
		for (int i = 0; i < LENGTH - 1; i++)
		{
			if (arr[i][temp] != SYMFORFREE && arr[i][temp] == arr[i + 1][temp - 1])
			{
				counter++;
			}
			if (counter >= 2) {
				flag = true;
			}
			temp--;
		}
	}
	return flag;
}

bool VerticalChecker(char arr[][LENGTH])
{
	bool flag = false;
	int counter = 0;
	for (int j = 0; j < LENGTH; j++)
	{
		for (int i = 0; i < LENGTH - 1; i++)
		{
			if (arr[i][j] != SYMFORFREE && arr[i][j] == arr[i + 1][j])
			{
				counter++;
			}
		}
		if (counter >= 2) {
			flag = true;
			break;
		}
		counter = 0;
	}
	return flag;
}

bool HorizontalChecker(char arr[][LENGTH])
{
	bool flag = false;
	int counter = 0;
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH - 1; j++)
		{
			if (arr[i][j] != SYMFORFREE && arr[i][j] == arr[i][j + 1])
			{
				counter++;
			}
		}
		if (counter >= 2) {
			flag = true;
			break;
		}
		counter = 0;
	}
	return flag;
}

void CheckerFreeArea(char arr[][LENGTH], int row, int col, const char sym, bool& temp, bool& refresh)
{
	if (arr[row][col] == SYMFORFREE)
	{
		arr[row][col] = sym;
		GlobalCounter++;
	}
	else
	{
		temp = false;
		refresh = false;
		Clear();
		cout << "This cell has already been used!" << endl;
	}
}

void PrintArea(const char arr[][LENGTH])
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (j != LENGTH - 1)
			{
				cout << arr[i][j] << '|';
			}
			else
			{
				cout << arr[i][j];
			}
		}
		cout << endl;
	}
}

void FillArea(char arr[][LENGTH])
{
	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			arr[i][j] = SYMFORFREE;
		}
	}
}

void Clear()
{
	system("cls");
}
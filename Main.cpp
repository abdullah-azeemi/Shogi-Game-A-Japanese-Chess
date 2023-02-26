#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>
#include<conio.h>
#include<mmsystem.h>
using namespace std;
# define Turn 1

void captureCalculator(char x, int turn, int cap_P1[7], int cap_P2[7]);
void saveturn(char** B, char array[][9][9], int dim, int& arraySize, int cap_count1[7], int cap_count2[7], int capsave1[][7], int capsave2[][7], int &save1size, int & save2size);
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct position {
	int ri;
	int ci;

};
void init2(char**& B, int dim, string P_name[2], int turn, isPromoted &P, int cap_P1_count[7], int cap_P2_count[7])
{
	P.B = P.A = P.C = P.F = P.L = P.N = P.P = P.Q = P.R = P.S = P.T = P.U = P.V = P.W = P.X = P.Y = P.Z = P.J= P.D= P.I= P.O = P.H = P.$= false;
	P.b = P.a = P.c = P.f = P.l = P.n = P.p = P.q = P.r = P.s = P.t = P.u = P.v = P.w = P.x = P.y = P.z = P.j= P.d= P.i= P.o = P.h =P.$$= false;

	ifstream rdr("Text.txt");
	rdr >> dim;
	B = new char* [dim];
	for (int ri = 0; ri < dim; ri++)
	{
		B[ri] = new char[dim];
	}
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			rdr >> B[ri][ci];

		}
	}
	int i = 0;
	cout << "\n Enter the " << i + 1 << " Player's Name : ";
	cin >> P_name[i];
	i += 1;
	cout << "\n Enter the " << i + 1 << " Player's Name : ";
	cin >> P_name[i];
	turn = Turn;

	for (int ri = 0; ri < 7; ri++)
	{
		cap_P1_count[ri] = 0;
		cap_P2_count[ri] = 0;
	}
}
void init3(char**& B, int dim, string P_name[2], int turn, isPromoted& P, int cap_P1_count[7], int cap_P2_count[7])
{
	P.B = P.A = P.C = P.F = P.L = P.N = P.P = P.Q = P.R = P.S = P.T = P.U = P.V = P.W = P.X = P.Y = P.Z = P.J = P.D = P.I = P.O = P.H = P.$ = false;
	P.b = P.a = P.c = P.f = P.l = P.n = P.p = P.q = P.r = P.s = P.t = P.u = P.v = P.w = P.x = P.y = P.z = P.j = P.d = P.i = P.o = P.h = P.$$ = false;

	ifstream rdr("Text1.txt");
	dim = 9;
	B = new char* [dim];
	for (int ri = 0; ri < dim; ri++)
	{
		B[ri] = new char[dim];
	}
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			rdr >> B[ri][ci];

		}
	}
	int i = 0;
	cout << "\n Enter the " << i + 1 << " Player's Name : ";
	cin >> P_name[i];
	i += 1;
	cout << "\n Enter the " << i + 1 << " Player's Name : ";
	cin >> P_name[i];
	turn = Turn;

	for (int ri = 0; ri < 7; ri++)
	{
		cap_P1_count[ri] = 0;
		cap_P2_count[ri] = 0;
	}
}
void printMsg(char P_names[2], int turn)
{
	cout << P_names[turn] << "'s Turn : " << endl;
}
bool isValidSourceWhite(int row, int col, int dim, char**& B)
{
	if (B[row][col] >= 'A' && B[row][col] <= 'Z')
	{
		return true;
	}
	return false;
}
bool isValidSourceBlack(int row, int col, int dim, char**& B)
{
	if (B[row][col] >= 'a' && B[row][col] <= 'z')
	{
		return true;
	}
	return false;
}
bool isWhite(char sym)
{
	if (int(sym) >= 65 && int(sym) <= 90)
		return true;
	if (sym == '}' || sym == '$')
		return true;
	return false;
}
bool isBlack(char sym)
{
	if (int(sym) >= 97 && int(sym) <= 122)
		return true;
	if (sym == ']' || sym == '$$')
		return true;
	return false;
}
bool isHorizontal(position Sc, position Dc);
bool isVertical(position Sc, position Dc);
bool isDiagonal(position Sc, position Dc);
bool isDiagMove(position Sc, position Dc);
bool isDiagPathClr1(char**& B, position Sc, position Dc);
bool isDiagPathClr2(char**& B, position Sc, position Dc);
bool isDiagPathClr(char**& B, position Sc, position Dc);
bool ishorizontalPathClear(char** B, position Sc, position Dc);
bool isverticalPathClear(char** B, position Sc, position Dc);
bool isDiagonalPathClearL2R(char** B, position Sc, position Dc);
bool isDiagonalPathClearR2L(char** B, position Sc, position Dc);
bool isValidGoldGeneral(char** B, position Sc, position Dc);
bool isValidRook(char** B, position Sc, position Dc, isPromoted P);
bool isValidLance(char** B, position Sc, position Dc, isPromoted P);
bool isValidBishop(char** B, position Sc, position Dc, isPromoted P);
bool isValidSilverGeneral(char** B, position Sc, position Dc, isPromoted P);
bool isValidKnight(char** B, position Sc, position Dc, isPromoted P);
bool isValidKing(char** B, position Sc, position Dc);
bool isValidPawn(char** B, position Sc, position Dc, isPromoted P);
bool isValidMove(char** B, position Sc, position Dc, isPromoted P)
{
	if (B[Sc.ri][Sc.ci] == 'G' || B[Sc.ri][Sc.ci] == 'g' || B[Sc.ri][Sc.ci] == '}' || B[Sc.ri][Sc.ci] == ']')
	{
		if (isValidGoldGeneral(B, Sc, Dc) == true)
			return true;

		return false;
	}
	if (B[Sc.ri][Sc.ci] == 'L' || B[Sc.ri][Sc.ci] == 'A' || B[Sc.ri][Sc.ci] == 'O')
	{
		return (Sc.ri < Dc.ri) && (isValidLance(B, Sc, Dc, P));
	}
	if (B[Sc.ri][Sc.ci] == 'l' || B[Sc.ri][Sc.ci] == 'a' || B[Sc.ri][Sc.ci] == 'o')
	{
		return (Sc.ri > Dc.ri) && (isValidLance(B, Sc, Dc, P));
	}
	if (B[Sc.ri][Sc.ci] == 'R' || B[Sc.ri][Sc.ci] == 'r' || B[Sc.ri][Sc.ci] == 'I' || B[Sc.ri][Sc.ci] == 'i')
	{
		if (isValidRook(B, Sc, Dc, P) == true)
		{
			return true;
		}
		return false;
	}
	if (B[Sc.ri][Sc.ci] == 'S' || B[Sc.ri][Sc.ci] == 's' || B[Sc.ri][Sc.ci] == 'F' || B[Sc.ri][Sc.ci] == 'f' || B[Sc.ri][Sc.ci] == '$' || B[Sc.ri][Sc.ci] == '$$')
	{
		if (isValidSilverGeneral(B, Sc, Dc, P) == true)
		{
			return true;
		}
		return false;
	}
	if (B[Sc.ri][Sc.ci] == 'N' || B[Sc.ri][Sc.ci] == 'n' || B[Sc.ri][Sc.ci] == 'C' || B[Sc.ri][Sc.ci] == 'c' || B[Sc.ri][Sc.ci] == 'H' || B[Sc.ri][Sc.ci] == 'h')
	{
		if (isValidKnight(B, Sc, Dc, P) == true)
		{
			return true;
		}
		return false;
	}
	if (B[Sc.ri][Sc.ci] == 'K' || B[Sc.ri][Sc.ci] == 'k')
	{
		if (isValidKing(B, Sc, Dc) == true)
		{
			return true;
		}
		return false;
	}
	if (B[Sc.ri][Sc.ci] == 'B' || B[Sc.ri][Sc.ci] == 'b' || B[Sc.ri][Sc.ci] == 'D' || B[Sc.ri][Sc.ci] == 'd')
	{
		if (isValidBishop(B, Sc, Dc, P) == true)
		{
			return true;
		}
		return false;
	}
	if (B[Sc.ri][Sc.ci] == 'P' || B[Sc.ri][Sc.ci] == 'p'|| B[Sc.ri][Sc.ci] == 'Q' || B[Sc.ri][Sc.ci] == 'U' || B[Sc.ri][Sc.ci] == 'V' || B[Sc.ri][Sc.ci] == 'W' || B[Sc.ri][Sc.ci] == 'X' || B[Sc.ri][Sc.ci] == 'Y' || B[Sc.ri][Sc.ci] == 'Z' || B[Sc.ri][Sc.ci] == 'T' || B[Sc.ri][Sc.ci] == 'q' || B[Sc.ri][Sc.ci] == 't' || B[Sc.ri][Sc.ci] == 'u' || B[Sc.ri][Sc.ci] == 'v' || B[Sc.ri][Sc.ci] == 'w' || B[Sc.ri][Sc.ci] == 'x' ||B[Sc.ri][Sc.ci] == 'y' || B[Sc.ri][Sc.ci] == 'z' || B[Sc.ri][Sc.ci] == 'J' || B[Sc.ri][Sc.ci] == 'j')
	{
		if (isValidPawn(B, Sc, Dc, P) == true)
		{
			return true;
		}
		return false;
	}
	return true;

}
void DrawBox(int sr, int sc, int brows, int bcols, int colour, char**& B, int r, int c)
{
	char sym = -37;
	for (int ri = brows - 1; ri >= 0; ri--)
	{
		for (int ci = bcols - 1; ci >= 0; ci--)
		{
			SetClr(colour);
			if (ri == brows / 2 && ci == bcols / 2)
			{
				if (colour == 15)
				{
					SetClr(0);
				}
				if (colour == 0)
				{
					SetClr(8);

				}
				gotoRowCol(sr + ri+20, sc + ri+42);
				SetClr(9);
				if (B[r][c] != '-')
				{
					if (B[r][c] == 'L' || B[r][c] == 'A')
						cout << 'L';
					else if (B[r][c] == 'l' || B[r][c] == 'a')
						cout << 'l';
					else if (B[r][c] == 'N' || B[r][c] == 'C')
						cout << 'N';
					else if (B[r][c] == 'n' || B[r][c] == 'c')
						cout << 'n';
					else if (B[r][c] == 'S' || B[r][c] == 'F')
						cout << 'S';
					else if (B[r][c] == 's' || B[r][c] == 'f')
						cout << 's';
					else if (B[r][c] == 'G')
						cout << 'G';
					else if (B[r][c] == 'K')
						cout << 'K';
					else if (B[r][c] == 'g')
						cout << 'g';
					else if (B[r][c] == 'k')
						cout << 'k';
					else if (B[r][c] == 'B')
						cout << 'B';
					else if (B[r][c] == 'b')
						cout << 'b';
					else if (B[r][c] == 'R')
						cout << 'R';
					else if (B[r][c] == 'r')
						cout << 'r';
					else if (B[r][c] == 'P' || B[r][c] == 'Q' || B[r][c] == 'T' || B[r][c] == 'U' || B[r][c] == 'V' || B[r][c] == 'W' || B[r][c] == 'X' || B[r][c] == 'Y' || B[r][c] == 'Z')
						cout << 'P';
					else if (B[r][c] == 'p' || B[r][c] == 'q' || B[r][c] == 't' || B[r][c] == 'u' || B[r][c] == 'v' || B[r][c] == 'w' || B[r][c] == 'x' || B[r][c] == 'y' || B[r][c] == 'z')
						cout << 'p';
				}

			}

			gotoRowCol(sr + ri + 20, sc + ci + 42);
			if (ri != brows / 2 || ci != bcols / 2)
				cout << sym;
		}
	}
	//cout << B[r][c];
}
void DrawBox3(int sr, int sc, int brows, int bcols, int colour, char**& B, int r, int c)
{

	char sym = -37;
	for (int ri = brows - 1; ri >= 0; ri--)
	{
		for (int ci = bcols - 1; ci >= 0; ci--)
		{
			if (ri == 0 || ci == 0 || ri == brows - 1 || ci == bcols - 1)
			{
				SetClr(6);
			}
			else
			{
				SetClr(colour);
			}
			if (ri == brows / 2 && ci == bcols / 2)
			{
				if (colour == 15)
				{
					SetClr(0);
				}
				if (colour == 0)
				{
					SetClr(8);

				}
				gotoRowCol(sr + ri+20, sc + ri+42);
				SetClr(9);
				if (B[r][c] != '-')
				{
					if (B[r][c] == 'L' || B[r][c] == 'A')
						cout << 'L';
					else if (B[r][c] == 'l' || B[r][c] == 'a')
						cout << 'l';
					else if (B[r][c] == 'N' || B[r][c] == 'C')
						cout << 'N';
					else if (B[r][c] == 'n' || B[r][c] == 'c')
						cout << 'n';
					else if (B[r][c] == 'S' || B[r][c] == 'F')
						cout << 'S';
					else if (B[r][c] == 's' || B[r][c] == 'f')
						cout << 's';
					else if (B[r][c] == 'G')
						cout << 'G';
					else if (B[r][c] == 'K')
						cout << 'K';
					else if (B[r][c] == 'g')
						cout << 'g';
					else if (B[r][c] == 'k')
						cout << 'k';
					else if (B[r][c] == 'B')
						cout << 'B';
					else if (B[r][c] == 'b')
						cout << 'b';
					else if (B[r][c] == 'R')
						cout << 'R';
					else if (B[r][c] == 'r')
						cout << 'r';
					else if (B[r][c] == 'P' || B[r][c] == 'Q' || B[r][c] == 'T' || B[r][c] == 'U' || B[r][c] == 'V' || B[r][c] == 'W' || B[r][c] == 'X' || B[r][c] == 'Y' || B[r][c] == 'Z')
						cout << 'P';
					else if (B[r][c] == 'p' || B[r][c] == 'q' || B[r][c] == 't' || B[r][c] == 'u' || B[r][c] == 'v' || B[r][c] == 'w' || B[r][c] == 'x' || B[r][c] == 'y' || B[r][c] == 'z')
						cout << 'p';
				}
			}
			gotoRowCol(sr + ri+20, sc + ci+42);
			if (ri != brows / 2 || ci != bcols / 2)
				cout << sym;
		}
	}
	SetClr(colour);
	//cout << B[r][c];
}
void DrawBox4(int sr, int sc, int brows, int bcols, int colour, char**& B, int r, int c)
{

	char sym = -37;
	for (int ri = brows - 1; ri >= 0; ri--)
	{
		for (int ci = bcols - 1; ci >= 0; ci--)
		{
			if (ri == 0 || ci == 0 || ri == brows - 1 || ci == bcols - 1)
			{
				SetClr(4);
			}
			else
			{
				SetClr(colour);
			}
			if (ri == brows / 2 && ci == bcols / 2)
			{
				if (colour == 15)
				{
					SetClr(0);
				}
				if (colour == 0)
				{
					SetClr(8);

				}
				gotoRowCol(sr + ri+20, sc + ri+42);
				SetClr(9);
				if (B[r][c] != '-')
				{
					if (B[r][c] == 'L' || B[r][c] == 'A')
						cout << 'L';
					else if (B[r][c] == 'l' || B[r][c] == 'a')
						cout << 'l';
					else if (B[r][c] == 'N' || B[r][c] == 'C')
						cout << 'N';
					else if (B[r][c] == 'n' || B[r][c] == 'c')
						cout << 'n';
					else if (B[r][c] == 'S' || B[r][c] == 'F')
						cout << 'S';
					else if (B[r][c] == 's' || B[r][c] == 'f')
						cout << 's';
					else if (B[r][c] == 'G')
						cout << 'G';
					else if (B[r][c] == 'K')
						cout << 'K';
					else if (B[r][c] == 'g')
						cout << 'g';
					else if (B[r][c] == 'k')
						cout << 'k';
					else if (B[r][c] == 'B')
						cout << 'B';
					else if (B[r][c] == 'b')
						cout << 'b';
					else if (B[r][c] == 'R')
						cout << 'R';
					else if (B[r][c] == 'r')
						cout << 'r';
					else if (B[r][c] == 'P' || B[r][c] == 'Q' || B[r][c] == 'T' || B[r][c] == 'U' || B[r][c] == 'V' || B[r][c] == 'W' || B[r][c] == 'X' || B[r][c] == 'Y' || B[r][c] == 'Z')
						cout << 'P';
					else if (B[r][c] == 'p' || B[r][c] == 'q' || B[r][c] == 't' || B[r][c] == 'u' || B[r][c] == 'v' || B[r][c] == 'w' || B[r][c] == 'x' || B[r][c] == 'y' || B[r][c] == 'z')
						cout << 'p';
				}
			}
			gotoRowCol(sr + ri+20, sc + ci+42);
			if (ri != brows / 2 || ci != bcols / 2)
				cout << sym;
		}
	}
	SetClr(colour);
	//cout << B[r][c];
}
void CheckHighlight(char** B, position Sc, int  turn, int dim, int**& highBoard, isPromoted P)
{
	position Dc;
	highBoard = new int* [dim];
	for (int ri = 0; ri < dim; ri++)
	{
		highBoard[ri] = new int[dim];
		for (int ci = 0; ci < dim; ci++)
		{
			Dc.ri = ri;
			Dc.ci = ci;
			if (isWhite(B[Sc.ri][Sc.ci]) == true)
			{
				highBoard[ri][ci] = (isValidMove(B, Sc, Dc, P) == true) && (isWhite(B[Dc.ri][Dc.ci]) == false);
			}
			if (isBlack(B[Sc.ri][Sc.ci]) == true)
			{
				highBoard[ri][ci] = (isValidMove(B, Sc, Dc, P) == true) && (isBlack(B[Dc.ri][Dc.ci]) == false);
			}
		}
	}
}
void printBoard2(int dim, int rows, int columns, char**& B, int** highboard, position Sc)
{
	//system("cls");
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
			{
				if (ri == Sc.ri && ci == Sc.ci)
				{
					DrawBox3(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
				}
				else if (highboard[ri][ci] == 0 && ((ri != Sc.ri) && (ci != Sc.ci)))
				{
					DrawBox(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
				}
				else if (highboard[ri][ci] == 1)
				{
					DrawBox2(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
				}
			}
			else
			{
				if (ri == Sc.ri && ci == Sc.ci)
				{
					DrawBox3(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
				}
				else if (highboard[ri][ci] == 0 && ((ri != Sc.ri) && (ci != Sc.ci)))
				{
					DrawBox(ri * rows, ci * columns, rows, columns, 0, B, ri, ci);
				}
				else if (highboard[ri][ci] == 1)
				{
					DrawBox2(ri * rows, ci * columns, rows, columns, 0, B, ri, ci);
				}
			}

		}
	}
}
void printBoardCheck(int dim, int rows, int columns, char**& B, position Kc)
{

	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
			{
				if (ri == Kc.ri && ci == Kc.ci)
				{
					DrawBox4(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
				}
				else
				{
					DrawBox(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
				}
			}
			else
			{
				if (ri == Kc.ri && ci == Kc.ci)
				{
					DrawBox4(ri * rows, ci * columns, rows, columns, 0, B, ri, ci);
				}
				else
				{
					DrawBox(ri * rows, ci * columns, rows, columns, 0, B, ri, ci);
				}
			}

		}
	}
}

void findKing(char** B, int dim, int turn, position& Kc);
bool isCheck(char** B, int turn, int dim, isPromoted P);
bool isSelfCheck(char** B, int turn, int dim, isPromoted P)
{
	position Kc, Sc;
	findKing(B, dim, turn, Kc);
	turn = (turn + 1) % 2;
	return(isCheck(B, turn, 9, P));
}
bool isCheckMate(char** B, int dim, int turn, isPromoted P)
{
	position Sc, Dc;

	if (turn == 0)
	{
		for (int sr = 0; sr < dim; sr++)
		{
			for (int sc = 0; sc < dim; sc++)
			{
				for (int dr = 0; dr < dim; dr++)
				{
					for (int dc = 0; dc < dim; dc++)
					{
						Sc.ri = sr;
						Sc.ci = sc;
						Dc.ri = dr;
						Dc.ci = dc;

						if (isWhite(B[Sc.ri][Sc.ci]) && (!isWhite(B[Dc.ri][Dc.ci])) && (isValidMove(B, Sc, Dc,P)) && (!isSelfCheck(B, 9, turn ,P)))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	if (turn == 1)
	{
		for (int sr = 0; sr < dim; sr++)
		{
			for (int sc = 0; sc < dim; sc++)
			{
				for (int dr = 0; dr < dim; dr++)
				{
					for (int dc = 0; dc < dim; dc++)
					{
						Sc.ri = sr;
						Sc.ci = sc;
						Dc.ri = dr;
						Dc.ci = dc;

						if (isBlack(B[Sc.ri][Sc.ci]) && (!isBlack(B[Dc.ri][Dc.ci])) && (isValidMove(B, Sc, Dc, P)) && (!isSelfCheck(B, 9, turn, P)))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	return false;
}
bool ismycheckmate(char** B, int dim, int turn, isPromoted P)
{
	position Sc, Dc;
	if (turn == 0)
	{
		position kc;
		findKing(B, 9, turn, kc);
		for (int ri = 0; ri < 9; ri++)
		{
			for (int ci = 0; ci < 9; ci++)
			{
				Sc.ri = ri; Sc.ci = ci;
				if (isWhite(B[ri][ci]) == true)
				{
					for (int rr = 0; rr < 9; rr++)
					{
						for (int cc = 0; cc < 9; cc++)
						{
							Dc.ri = rr; Dc.ci = cc;
							if (isValidMove(B, Dc, Dc, P) == true)
							{
								if ((Dc.ri == kc.ri) && (Dc.ci == kc.ci))
								{
									return true;
								}

							}
							
						}
					}
				}
			}
		}
		return false;
	}
	if (turn == 1)
	{
		position kc;
		findKing(B, 9, turn, kc);
		for (int ri = 0; ri < 9; ri++)
		{
			for (int ci = 0; ci < 9; ci++)
			{
				Sc.ri = ri; Sc.ci = ci;
				if (isBlack(B[ri][ci]) == true)
				{
					for (int rr = 0; rr < 9; rr++)
					{
						for (int cc = 0; cc < 9; cc++)
						{
							Dc.ri = rr; Dc.ci = cc;
							if (isValidMove(B, Dc, Dc, P) == true)
							{
								if ((Dc.ri == kc.ri) && (Dc.ci == kc.ci))
								{
									return true;
								}

							}

						}
					}
				}
			}
		}
		return false;
	}
	return false;
}


void DrawBoxUndoGraphical(int brows, int bcols);
void checkPromotions(char** B, position Sc, position Dc, int dim, isPromoted& P)
{
	if (isWhite(B[Sc.ri][Sc.ci]) == true)
	{
		if (Dc.ri >= 6 && Dc.ri < dim)
		{
			if (B[Sc.ri][Sc.ci] == 'P')
				P.P = true;
			else if (B[Sc.ri][Sc.ci] == 'B')
				P.B = true;
			else if (B[Sc.ri][Sc.ci] == 'Q')
				P.Q = true;
			else if (B[Sc.ri][Sc.ci] == 'T')
				P.T = true;
			else if (B[Sc.ri][Sc.ci] == 'U')
				P.U = true;
			else if (B[Sc.ri][Sc.ci] == 'V')
				P.V = true;
			else if (B[Sc.ri][Sc.ci] == 'W')
				P.W = true;
			else if (B[Sc.ri][Sc.ci] == 'X')
				P.X = true;
			else if (B[Sc.ri][Sc.ci] == 'Y')
				P.Y = true;
			else if (B[Sc.ri][Sc.ci] == 'Z')
				P.Z = true;
			else if (B[Sc.ri][Sc.ci] == 'C')
				P.C = true;
			else if (B[Sc.ri][Sc.ci] == 'F')
				P.F = true;
			else if (B[Sc.ri][Sc.ci] == 'A')
				P.A = true;
			else if (B[Sc.ri][Sc.ci] == 'R')
				P.R = true;
			else if (B[Sc.ri][Sc.ci] == 'L')
				P.L = true;
			else if (B[Sc.ri][Sc.ci] == 'N')
				P.N = true;
			else if (B[Sc.ri][Sc.ci] == 'S')
				P.S = true;

			/*else if (B[Sc.ri][Sc.ci] == 'J')
				P.J = true;
			else if (B[Sc.ri][Sc.ci] == 'D')
				P.D = true;
			else if (B[Sc.ri][Sc.ci] == 'I')
				P.I = true;
			else if (B[Sc.ri][Sc.ci] == 'O')
				P.O = true;
			else if (B[Sc.ri][Sc.ci] == 'H')
				P.H = true;*/

		}
	}
	if (isBlack(B[Sc.ri][Sc.ci]) == true)
	{
		if (Dc.ri <= 2 && Dc.ri >= 0)
		{
			if (B[Sc.ri][Sc.ci] == 'p')
				P.p = true;
			else if (B[Sc.ri][Sc.ci] == 'b')
				P.b = true;
			else if (B[Sc.ri][Sc.ci] == 'q')
				P.q = true;
			else if (B[Sc.ri][Sc.ci] == 't')
				P.t = true;
			else if (B[Sc.ri][Sc.ci] == 'u')
				P.u = true;
			else if (B[Sc.ri][Sc.ci] == 'v')
				P.v = true;
			else if (B[Sc.ri][Sc.ci] == 'w')
				P.w = true;
			else if (B[Sc.ri][Sc.ci] == 'x')
				P.x = true;
			else if (B[Sc.ri][Sc.ci] == 'y')
				P.y = true;
			else if (B[Sc.ri][Sc.ci] == 'z')
				P.z = true;
			else if (B[Sc.ri][Sc.ci] == 'c')
				P.c = true;
			else if (B[Sc.ri][Sc.ci] == 'f')
				P.f = true;
			else if (B[Sc.ri][Sc.ci] == 'a')
				P.a = true;
			else if (B[Sc.ri][Sc.ci] == 'r')
				P.r = true;
			else if (B[Sc.ri][Sc.ci] == 'l')
				P.l = true;
			else if (B[Sc.ri][Sc.ci] == 'n')
				P.n = true;
			else if (B[Sc.ri][Sc.ci] == 's')
				P.s = true;

			/*else if (B[Sc.ri][Sc.ci] == 'j')
				P.j = true;
			else if (B[Sc.ri][Sc.ci] == 'd')
				P.d = true;
			else if (B[Sc.ri][Sc.ci] == 'i')
				P.i = true;
			else if (B[Sc.ri][Sc.ci] == 'o')
				P.o = true;
			else if (B[Sc.ri][Sc.ci] == 'h')
				P.h = true;*/
		}
	}
}
void Select2(position& Sc, position& Dc, int dim, char**& B, int turn, string P_name[2], char& sym, int size, isPromoted& P, bool &isUndo, int cap_P1[7], int cap_P2[7])
{
	int** highBoard{};
	gotoRowCol(85, 1);
	//gotoRowCol(size * dim, 1);
	cout << "\n" << P_name[turn] << " 's Turn : ";
	isUndo = false;
	if (turn == 0)
	{
	
		do
		{
			int x = 0, y = 0;
			cout << "\n Select your source  : ";
			getRowColbyLeftClick(x, y);
			if (x >= 71 && x < 80 && y >= 106 && y <= 115)
			{
				isUndo = true;
			}
			x -= 20;
			y -= 42;
			Sc.ri = x / size;
			Sc.ci = y / size;
			if (isUndo == true)
			{
				break;
			}
			

		} while ((isWhite(B[Sc.ri][Sc.ci]) == false));
		char s = 0;
		if (isUndo == false)
		{
			sym = B[Sc.ri][Sc.ci];
			CheckHighlight(B, Sc, turn, 9, highBoard, P);
			printBoard2(9, size, size, B, highBoard, Sc);
			do
			{
				if (isUndo == true)
				{
					break;
				}
				int x = 0, y = 0;
				gotoRowCol(57, 1);
				cout << "\n Select your destination  : ";
				getRowColbyLeftClick(x, y);
				x -= 20;
				y -= 42;
				Dc.ri = x / size;
				Dc.ci = y / size;

			} while (isWhite(B[Dc.ri][Dc.ci]) == true);
			if (isBlack(B[Dc.ri][Dc.ci]) == true)
			{
				captureCalculator(B[Dc.ri][Dc.ci], turn, cap_P1, cap_P2);
			}
			checkPromotions(B, Sc, Dc, 9, P);
		}
	}
	if (turn == 1)
	{
		do
		{
			int x2 = 0, y2 = 0;
			cout << "\n Select your source  : ";
			getRowColbyLeftClick(x2, y2);
			if (x2 >= 71 && x2 < 80 && y2 >= 106 && y2 <= 115)
			{
				isUndo = true;
			}
			x2 -= 20;
			y2 -= 42;
			Sc.ri = x2 / size;
			Sc.ci = y2 / size;
			if (isUndo == true)
			{
				break;
			}

		} while ((isBlack(B[Sc.ri][Sc.ci]) == false));
		if (isUndo == false)
		{
			sym = B[Sc.ri][Sc.ci];

			int a = 0, b = 0;
			CheckHighlight(B, Sc, turn, 9, highBoard, P);
			printBoard2(9, size, size, B, highBoard, Sc);
			do
			{
				int x2 = 0, y2 = 0;
				gotoRowCol(57, 1);
				cout << "\n Select your destination  : ";
				getRowColbyLeftClick(x2, y2);
				x2 -= 20;
				y2 -= 42;
				Dc.ri = x2 / size;
				Dc.ci = y2 / size;

			} while ((isBlack(B[Dc.ri][Dc.ci]) == true));
			checkPromotions(B, Sc, Dc, 9, P);
			if (isWhite(B[Dc.ri][Dc.ci]) == true)
			{
				captureCalculator(B[Dc.ri][Dc.ci], turn, cap_P1, cap_P2);
			}
		}
	}
}
void printBoard(int dim, int rows, int columns, char**& B, int cap_P1[7], int cap_P2[7])
{
	system("cls");
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
				DrawBox(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);
			else
				DrawBox(ri * rows, ci * columns, rows, columns, 0, B, ri, ci);

		}
	}
	DrawBoxUndo(10, 10);
	printCapBoardP1(cap_P1);
	printCapBoardP2(cap_P2);
}
void updateBoard(char**& B, position Sc, position Dc, char sym, bool isPlace, char place_sym)
{
	if (isPlace == false)
	{
		sym = B[Sc.ri][Sc.ci];
		B[Sc.ri][Sc.ci] = '-';
		B[Dc.ri][Dc.ci] = sym;
	}
	else if (isPlace == true)
	{
		if (place_sym != '-')
		{
			B[Dc.ri][Dc.ci] = place_sym;
		}
	}
}
void undoBoard(char**& B, char array[100][9][9], int& arraySize, int& turn, int cap_count1[7], int cap_count2[7], int capsave1[][7], int capsave2[][7], int& save1size, int& save2size)
{
	int x = arraySize - 1;
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			B[ri][ci] = array[x][ri][ci];
			array[x][ri][ci] = ' ';
		}
	}
	arraySize -= 1;

	for (int ri = 0; ri < 7; ri++)
	{
		cap_count1[ri] = capsave1[save1size][ri];
		cap_count2[ri] = capsave2[save2size][ri];
	}
	save1size -= 1;
	save2size -= 1;
	turn = (turn + 1) % 2;
}
void saveTextfile(char** B, int dim, string filename)
{
	ofstream writer(filename);
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			writer << B[ri][ci] << " ";
		}
		writer << "\n";
	}
}
bool ISWIN(char** B, int dim)
{
	bool knfound = false, KNfounnd = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (B[i][j] == 'k')
				knfound = true;
			if (B[i][j] == 'K')
				KNfounnd = true;
		}
	}
	if (knfound == false || KNfounnd == false)
	{
		system("cls");
		return true;
	}
	return false;
}
void DrawBoxEmpty(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxPawn(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxKing(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxGoldGeneral(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxSilverGeneral(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxLance(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxBishop(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxRook(int sr, int sc, int brows, int bcols, int colour, int colour2);
void DrawBoxKnight(int sr, int sc, int brows, int bcols, int colour, int colour2);
void my_sleep(float x)
{
	for (int i = 0; i < 1000000 * x; i++);
}
char returnPlacedSym(int x, int turn)
{
	char Place_sym = '-';
	if (turn == 1)
	{
		if (x == 0)
			Place_sym = 'j';
		else if (x == 1)
			Place_sym = 'd';
		else if (x == 2)
			Place_sym = 'i';
		else if (x == 3)
			Place_sym = 'o';
		else if (x == 4)
			Place_sym = 'h';
		else if (x == 5)
			Place_sym = '$';
		else if (x == 6)
			Place_sym = '}';
		
	}
	if (turn == 0)
	{
		if (x == 0)
			Place_sym = 'J';
		else if (x == 1)
			Place_sym = 'D';
		else if (x == 2)
			Place_sym = 'I';
		else if (x == 3)
			Place_sym = 'O';
		else if (x == 4)
			Place_sym = 'H';
		else if (x == 5)
			Place_sym = '$$';
		else if (x == 6)
			Place_sym = ']';
	}
	return Place_sym;
}
void DrawBoxCapAni1(int sr, int sc, int brows, int bcols, int colour, int cap_p1_count[7])
{
	char sym = -37;
	int x = 15, y = 30;
	for (int ri = 0; ri < 7; ri++)
	{
		SetClr(3);
		if (ri == 0)
		{
			     DrawBoxPawn(10 * ri+x, 10+y, 11, 11, 7, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x+8, 19+y);
			cout << cap_p1_count[ri];
		}
		else if (ri == 1)
		{
				DrawBoxBishop(10 * ri+x, 10+y, 11, 11, 8, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 19+y);
			cout << cap_p1_count[ri];
		}
		else if (ri == 2)
		{
			    DrawBoxRook(10 * ri+x, 10+y, 11, 11, 7, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 19+y);
			cout << cap_p1_count[ri];

		}
		else if (ri == 3)
		{
				DrawBoxLance(10 * ri+x, 10+y, 11, 11, 8, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 19+y);
			cout << cap_p1_count[ri];

		}
		else if (ri == 4)
		{
			    DrawBoxKnight(10 * ri+x, 10+y, 11, 11, 7, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 19+y);
			cout << cap_p1_count[ri];

		}
		else if (ri == 5)
		{
				DrawBoxSilverGeneral(10 * ri+x, 10+y, 11, 11, 8, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 19+y);
			cout << cap_p1_count[ri];
		}
		else if (ri == 6)
		{
			    DrawBoxGoldGeneral(10 * ri+x, 10+y, 11, 11, 7, 0);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 19+y);
			cout << cap_p1_count[ri];
		}

	}
}
void DrawBoxCapAni2(int sr, int sc, int brows, int bcols, int colour, int cap_p1_count[7])
{
	char sym = -37;
	int x = 15, y = 130;
	for (int ri = 0; ri < 7; ri++)
	{
		SetClr(3);
		if (ri == 0)
		{
				DrawBoxPawn(10 * ri + x, 80+y, 11, 11, 7, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];
		}
		else if (ri == 1)
		{
				DrawBoxBishop(10 * ri + x, 80+y, 11, 11, 8, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];
		}
		else if (ri == 2)
		{
			if (ri % 2 == 0)
				DrawBoxRook(10 * ri + x, 80+y, 11, 11, 7, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];

		}
		else if (ri == 3)
		{
				DrawBoxLance(10 * ri + x, 80+y, 11, 11, 8, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];

		}
		else if (ri == 4)
		{
				DrawBoxKnight(10 * ri + x, 80+y, 11, 11, 7, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];

		}
		else if (ri == 5)
		{
				DrawBoxSilverGeneral(10 * ri + x, 80+y, 11, 11, 8, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];
		}
		else if (ri == 6)
		{
				DrawBoxGoldGeneral(10 * ri + x, 80+y, 11, 11, 7, 15);
			SetClr(3);
			gotoRowCol(10 * ri + x + 8, 80+y+9);
			cout << cap_p1_count[ri];
		}

	}
}
void DrawBoxG(int sr, int sc, int brows, int bcols, int colour, char**& B, int r, int c)
{
	int x = 6, y = 110;
	char sym = -37;
	for (int ri = brows - 1; ri >= 0; ri--)
	{
		for (int ci = bcols - 1; ci >= 0; ci--)
		{
			if (ri == 0 || ci == 0 || ri == brows - 1 || ci == bcols - 1)
			{
				SetClr(2);
				gotoRowCol(sr + ri , sc + ci );
				  cout << sym;
			}
			
		}
	}
}
void DrawBoxB(int sr, int sc, int brows, int bcols, int colour, char**& B, int r, int c)
{
	int x = 6, y = 110;
	char sym = -37;
	for (int ri = brows - 1; ri >= 0; ri--)
	{
		for (int ci = bcols - 1; ci >= 0; ci--)
		{
			if (ri == 0 || ci == 0 || ri == brows - 1 || ci == bcols - 1)
			{
				SetClr(9);
				gotoRowCol(sr + ri , sc + ci);
				cout << sym;
			}
		}
	}
}
void DrawBoxR(int sr, int sc, int brows, int bcols, int colour)
{
	int x = 6, y = 110;
	char sym = -37;
	for (int ri = brows - 1; ri >= 0; ri--)
	{
		for (int ci = bcols - 1; ci >= 0; ci--)
		{
			if (ri == 0 || ci == 0 || ri == brows - 1 || ci == bcols - 1)
			{
				SetClr(4);
				gotoRowCol(sr + ri, sc + ci);
				cout << sym;
			}
		}
	}
}
void printBoard4(int dim, int rows, int columns, char**& B, int** highboard, position Sc)
{
	int x = 6, y = 80;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
			{
				if (ri == Sc.ri && ci == Sc.ci)
				{
					DrawBoxG(ri * rows + x, ci * columns + y, rows, columns, 15, B, ri, ci);
				}
				else if (highboard[ri][ci] == 0 && ((ri != Sc.ri) && (ci != Sc.ci)))
				{
					//DrawBox(ri * rows, ci * columns, rows, columns, 15, B, ri, ci);;
				}
				else if (highboard[ri][ci] == 1)
				{
					DrawBoxB(ri * rows + x, ci * columns + y, rows, columns, 15, B, ri, ci);
				}
			}
			else
			{
				if (ri == Sc.ri && ci == Sc.ci)
				{
					DrawBoxG(ri * rows + x, ci * columns + y, rows, columns, 15, B, ri, ci);
				}
				else if (highboard[ri][ci] == 0 && ((ri != Sc.ri) && (ci != Sc.ci)))
				{
					//DrawBox(ri * rows, ci * columns, rows, columns, 0, B, ri, ci);;
				}
				else if (highboard[ri][ci] == 1)
				{
					DrawBoxB(ri * rows + x, ci * columns + y, rows, columns, 0, B, ri, ci);
				}
			}

		}
	}
}
void Select3(position& Sc, position& Dc, int dim, char**& B, int turn, string P_name[2], char& sym, int size, isPromoted& P, bool &isUndo,int cap_P1[7], int cap_P2[7], bool &isPlace, char &place_sym)
{
	int** highBoard{};
	int yp = 80; // Adjusting input selection on screen
	gotoRowCol(60,110);
	//gotoRowCol(size * dim, 1);
	cout << "\n" << P_name[turn] << " 's Turn : ";
	if (turn == 0)
	{
		do
		{
			int x = 0, y = 0;
			gotoRowCol(61, 110);
			cout << "\n Select your source  : ";
			getRowColbyLeftClick(x, y);
			if (x >= 91 && x < 100 && y >= 11 && y <= 20)
			{
				isUndo = true;
			}
			if (x >= 15 && x < 210 && y >= 40 && y <= 220)
			{
				int new_x = ((x - 5) / 10)-1;
				if (cap_P2[new_x] != 0)
				{
					cap_P2[new_x] -= 1;
					place_sym = returnPlacedSym(new_x, turn);
					isPlace = true;
				}
			}
			x -= 6;
			y -= yp;
			Sc.ri = x / size;
			Sc.ci = y / size;
			if (isUndo == true)
			{
				break;
			}
			if (isPlace == true)
			{
				break;
			}

		} while ((isWhite(B[Sc.ri][Sc.ci]) == false));
		if (isUndo == false)
		{
			char s = 0;
			sym = B[Sc.ri][Sc.ci];
			CheckHighlight(B, Sc, turn, 9, highBoard, P);
			printBoard4(9, size, size, B, highBoard, Sc);
			PlaySound(TEXT("selectfast"), NULL, SND_SYNC);
			if (isPlace == false)
			{
				do
				{
					int x = 0, y = 0;
					gotoRowCol(62, 110);
					cout << "\n Select your destination  : ";
					getRowColbyLeftClick(x, y);
					
					x -= 6;
					y -= yp;
					Dc.ri = x / size;
					Dc.ci = y / size;


				} while ((isWhite(B[Dc.ri][Dc.ci]) == true) && (isSelfCheck(B,turn,9,P)== false));
			}
			if (isPlace == true)
			{
				do
				{
					int x = 0, y = 0;
					gotoRowCol(62, 110);
					cout << "\n Select your destination  : ";
					getRowColbyLeftClick(x, y);
					x -= 6;
					y -= yp;
					Dc.ri = x / size;
					Dc.ci = y / size;

				} while ((B[Dc.ri][Dc.ci]) != '-');
			}
			if (isBlack(B[Dc.ri][Dc.ci]) == true)
			{
				captureCalculator(B[Dc.ri][Dc.ci], turn, cap_P1, cap_P2);
			}
			checkPromotions(B, Sc, Dc, 9, P);
		}
	}
	if (turn == 1)
	{
		do
		{
			int x2 = 0, y2 = 0;
			gotoRowCol(61, 110);
			cout << "\n Select your source  : ";
			getRowColbyLeftClick(x2, y2);
			if (x2 >= 91 && x2 < 100 && y2 >= 11 && y2 <= 20)
			{
				isUndo = true;
			}
			if (x2 >= 15 && x2 < 85 && y2 >= 40 && y2 <= 50)
			{
				int new_x = ((x2 - 5) / 10)-1;
				if (cap_P1[new_x] != 0)
				{
					cap_P1[new_x] -= 1;
					place_sym = returnPlacedSym(new_x, turn);
					isPlace = true;
				}
			}
			x2 -= 6;
			y2 -= yp;
			Sc.ri = x2 / size;
			Sc.ci = y2 / size;
			if (isUndo == true)
			{
				break;
			}
			if (isPlace == true)
			{
				break;
			}

		} while ((isBlack(B[Sc.ri][Sc.ci]) == false));
		if (isUndo == false)
		{
			sym = B[Sc.ri][Sc.ci];
			CheckHighlight(B, Sc, turn, 9, highBoard, P);
			printBoard4(9, size, size, B, highBoard, Sc);
			PlaySound(TEXT("selectfast"), NULL, SND_SYNC);
			if (isPlace == false)
			{
				do
				{
					int x2 = 0, y2 = 0;
					gotoRowCol(62, 110);
					cout << "\n Select your destination  : ";
					getRowColbyLeftClick(x2, y2);
					x2 -= 6;
					y2 -= yp;
					Dc.ri = x2 / size;
					Dc.ci = y2 / size;

				} while ((isBlack(B[Dc.ri][Dc.ci]) == true) && (isSelfCheck(B, turn, 9, P) == false));
			}
			if (isPlace == true)
			{
				do
				{
					int x2 = 0, y2 = 0;
					gotoRowCol(62, 110);
					cout << "\n Select your destination  : ";
					getRowColbyLeftClick(x2, y2);
					x2 -= 6;
					y2 -= yp;
					Dc.ri = x2 / size;
					Dc.ci = y2 / size;

				} while (((B[Dc.ri][Dc.ci]) != '-'));
			}
			if (isWhite(B[Dc.ri][Dc.ci]) == true)
			{
				captureCalculator(B[Dc.ri][Dc.ci], turn, cap_P1, cap_P2);
			}
			checkPromotions(B, Sc, Dc, 9, P);
		}
	}
}
void printBoardNew(int dim, int rows, int columns, char**& B, int cap_P1[7], int cap_P2[7], isPromoted P, int turn)
{
	//system("cls");
	position Kc;
	int x = 6, y = 80; // for Adjusting placement
	findKing(B, 9, turn, Kc);
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
			{
				if(B[ri][ci] == 'P' || B[ri][ci] == 'Q' || B[ri][ci] == 'T' || B[ri][ci] == 'U' || B[ri][ci] == 'V' || B[ri][ci] == 'W' || B[ri][ci] == 'X' || B[ri][ci] == 'Y' || B[ri][ci] == 'Z' || B[ri][ci] == 'J')
				    DrawBoxPawn(ri * rows+x, ci * columns+y, rows, columns, 7,15);

				else if (B[ri][ci] == 'p' || B[ri][ci] == 'q' || B[ri][ci] == 't' || B[ri][ci] == 'u' || B[ri][ci] == 'v' || B[ri][ci] == 'w' || B[ri][ci] == 'x' || B[ri][ci] == 'y' || B[ri][ci] == 'z' || B[ri][ci] == 'j')
					DrawBoxPawn(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'N' || B[ri][ci] == 'C' || B[ri][ci] == 'H')
					DrawBoxKnight(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'n' || B[ri][ci] == 'c' || B[ri][ci] == 'h')
					DrawBoxKnight(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'S' || B[ri][ci] == 'F' || B[ri][ci] == '$')
					DrawBoxSilverGeneral(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 's' || B[ri][ci] == 'f' || B[ri][ci] == '$$')
					DrawBoxSilverGeneral(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'L' || B[ri][ci] == 'A' || B[ri][ci] == 'O')
					DrawBoxLance(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'l' || B[ri][ci] == 'a' || B[ri][ci] == 'o')
					DrawBoxLance(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'R' || B[ri][ci] == 'I')
					DrawBoxRook(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'r' || B[ri][ci] == 'i')
					DrawBoxRook(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'B' || B[ri][ci] == 'D')
					DrawBoxBishop(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'b' || B[ri][ci] == 'd')
					DrawBoxBishop(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'K')
					DrawBoxKing(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'k')
					DrawBoxKing(ri * rows+x, ci * columns+y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'G' || B[ri][ci] == ']')
					DrawBoxGoldGeneral(ri * rows+x, ci * columns+y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'g' || B[ri][ci] == '}')
					DrawBoxGoldGeneral(ri * rows+x, ci * columns+y, rows, columns, 7, 0);
				else
					DrawBoxEmpty(ri * rows+x, ci * columns+y, rows, columns, 7, 0);
			}
			else
			{
				if (B[ri][ci] == 'P' || B[ri][ci] == 'Q' || B[ri][ci] == 'T' || B[ri][ci] == 'U' || B[ri][ci] == 'V' || B[ri][ci] == 'W' || B[ri][ci] == 'X' || B[ri][ci] == 'Y' || B[ri][ci] == 'Z' || B[ri][ci] == 'J')
					DrawBoxPawn(ri * rows+x, ci * columns+y, rows, columns, 8,15);

				else if (B[ri][ci] == 'p' || B[ri][ci] == 'q' || B[ri][ci] == 't' || B[ri][ci] == 'u' || B[ri][ci] == 'v' || B[ri][ci] == 'w' || B[ri][ci] == 'x' || B[ri][ci] == 'y' || B[ri][ci] == 'z' || B[ri][ci] == 'j')
					DrawBoxPawn(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'N' || B[ri][ci] == 'C' || B[ri][ci] == 'H')
					DrawBoxKnight(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'n' || B[ri][ci] == 'c' || B[ri][ci] == 'h')
					DrawBoxKnight(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'S' || B[ri][ci] == 'F' || B[ri][ci] == '$')
					DrawBoxSilverGeneral(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 's' || B[ri][ci] == 'f' || B[ri][ci] == '$$')
					DrawBoxSilverGeneral(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'L' || B[ri][ci] == 'A' || B[ri][ci] == 'O')
					DrawBoxLance(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'l' || B[ri][ci] == 'a' || B[ri][ci] == 'o')
					DrawBoxLance(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'R' || B[ri][ci] == 'I')
					DrawBoxRook(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'r' || B[ri][ci] == 'i')
					DrawBoxRook(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'B' || B[ri][ci] == 'D')
					DrawBoxBishop(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'b' || B[ri][ci] == 'd')
					DrawBoxBishop(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'K')
					DrawBoxKing(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'k')
					DrawBoxKing(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'G' || B[ri][ci] == ']')
					DrawBoxGoldGeneral(ri * rows+x, ci * columns+y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'g' || B[ri][ci] == '}')
					DrawBoxGoldGeneral(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

				else
					DrawBoxEmpty(ri * rows+x, ci * columns+y, rows, columns, 8, 0);

			}
		}
	}
	if (isCheck(B, turn, 9, P) == true)
	{
		if ((Kc.ri + Kc.ci) % 2 == 0)
		{
			DrawBoxR(Kc.ri * rows + x, Kc.ci * columns + y, rows, columns, 7);
		}
		else
		{
			DrawBoxR(Kc.ri* rows + x, Kc.ci* columns + y, rows, columns, 8);
		}
	}
	DrawBoxUndoGraphical2(10, 10);
	DrawBoxCapAni1(10, 10, 10, 10, 11, cap_P1);
	DrawBoxCapAni2(10, 10, 10, 10, 11, cap_P2);
}
void printBoardRply(int dim, int rows, int columns, char**& B)
{
	int x = 6, y = 80; // for Adjusting placement
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if ((ri + ci) % 2 == 0)
			{
				if (B[ri][ci] == 'P' || B[ri][ci] == 'Q' || B[ri][ci] == 'T' || B[ri][ci] == 'U' || B[ri][ci] == 'V' || B[ri][ci] == 'W' || B[ri][ci] == 'X' || B[ri][ci] == 'Y' || B[ri][ci] == 'Z' || B[ri][ci] == 'J')
					DrawBoxPawn(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'p' || B[ri][ci] == 'q' || B[ri][ci] == 't' || B[ri][ci] == 'u' || B[ri][ci] == 'v' || B[ri][ci] == 'w' || B[ri][ci] == 'x' || B[ri][ci] == 'y' || B[ri][ci] == 'z' || B[ri][ci] == 'j')
					DrawBoxPawn(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'N' || B[ri][ci] == 'C' || B[ri][ci] == 'H')
					DrawBoxKnight(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'n' || B[ri][ci] == 'c' || B[ri][ci] == 'h')
					DrawBoxKnight(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'S' || B[ri][ci] == 'F' || B[ri][ci] == '$')
					DrawBoxSilverGeneral(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 's' || B[ri][ci] == 'f' || B[ri][ci] == '$$')
					DrawBoxSilverGeneral(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'L' || B[ri][ci] == 'A' || B[ri][ci] == 'O')
					DrawBoxLance(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'l' || B[ri][ci] == 'a' || B[ri][ci] == 'o')
					DrawBoxLance(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'R' || B[ri][ci] == 'I')
					DrawBoxRook(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'r' || B[ri][ci] == 'i')
					DrawBoxRook(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'B' || B[ri][ci] == 'D')
					DrawBoxBishop(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'b' || B[ri][ci] == 'd')
					DrawBoxBishop(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'K')
					DrawBoxKing(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'k')
					DrawBoxKing(ri * rows + x, ci * columns + y, rows, columns, 7, 0);

				else if (B[ri][ci] == 'G' || B[ri][ci] == ']')
					DrawBoxGoldGeneral(ri * rows + x, ci * columns + y, rows, columns, 7, 15);

				else if (B[ri][ci] == 'g' || B[ri][ci] == '}')
					DrawBoxGoldGeneral(ri * rows + x, ci * columns + y, rows, columns, 7, 0);
				else
					DrawBoxEmpty(ri * rows + x, ci * columns + y, rows, columns, 7, 0);
			}
			else
			{
				if (B[ri][ci] == 'P' || B[ri][ci] == 'Q' || B[ri][ci] == 'T' || B[ri][ci] == 'U' || B[ri][ci] == 'V' || B[ri][ci] == 'W' || B[ri][ci] == 'X' || B[ri][ci] == 'Y' || B[ri][ci] == 'Z' || B[ri][ci] == 'J')
					DrawBoxPawn(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'p' || B[ri][ci] == 'q' || B[ri][ci] == 't' || B[ri][ci] == 'u' || B[ri][ci] == 'v' || B[ri][ci] == 'w' || B[ri][ci] == 'x' || B[ri][ci] == 'y' || B[ri][ci] == 'z' || B[ri][ci] == 'j')
					DrawBoxPawn(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'N' || B[ri][ci] == 'C' || B[ri][ci] == 'H')
					DrawBoxKnight(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'n' || B[ri][ci] == 'c' || B[ri][ci] == 'h')
					DrawBoxKnight(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'S' || B[ri][ci] == 'F' || B[ri][ci] == '$')
					DrawBoxSilverGeneral(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 's' || B[ri][ci] == 'f' || B[ri][ci] == '$$')
					DrawBoxSilverGeneral(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'L' || B[ri][ci] == 'A' || B[ri][ci] == 'O')
					DrawBoxLance(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'l' || B[ri][ci] == 'a' || B[ri][ci] == 'o')
					DrawBoxLance(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'R' || B[ri][ci] == 'I')
					DrawBoxRook(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'r' || B[ri][ci] == 'i')
					DrawBoxRook(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'B' || B[ri][ci] == 'D')
					DrawBoxBishop(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'b' || B[ri][ci] == 'd')
					DrawBoxBishop(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'K')
					DrawBoxKing(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'k')
					DrawBoxKing(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else if (B[ri][ci] == 'G' || B[ri][ci] == ']')
					DrawBoxGoldGeneral(ri * rows + x, ci * columns + y, rows, columns, 8, 15);

				else if (B[ri][ci] == 'g' || B[ri][ci] == '}')
					DrawBoxGoldGeneral(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

				else
					DrawBoxEmpty(ri * rows + x, ci * columns + y, rows, columns, 8, 0);

			}
		}
	}

	DrawBoxUndoGraphical2(10, 10);
	
}
void Replay1(char** B, int dim, int arraysize, char Array[150][9][9]);
void NewGame(int brows, int bcols);
void LoadGame(int brows, int bcols);
void Replay(int brows, int bcols);
void Exit(int brows, int bcols);
void printIntro(int brows, int bcols);
void getSelection(int x, int y, int & choice)
{
	choice;
	if (x >= 30 && x < 39 && y >= 100 && y <=129)
	{
		choice = 1;
	}
	else if (x >= 42 && x < 52 && y >= 100 && y <=129)
	{
		choice = 2;
	}
	else if (x >= 54 && x < 64 && y >= 100 && y <= 129)
	{
		choice = 3;
	}
}


int main()
{
	PlaySound(TEXT("tune"), NULL, SND_ASYNC);
	printIntro(10, 30);
	gotoRowCol(10, 20);
	SetClr(14);
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tS H O G I ";
	cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\bA game for CFP shaheens";
	int x, y, choice;
	getRowColbyLeftClick(x, y);
	getSelection(x, y,choice);
	if (choice == 1)
	{
		system("cls");
		SetClr(15);
		char array[150][9][9]{};
		// Pattern for Capture : P B R L N S G
		int cap_P1_count[7]{}, cap_P2_count[7]{};
		int cap_P1_save[150][7]{}, cap_P2_save[150][7]{};
		int arraySize = 0, save1size = 0, save2size = 0;
		bool isUndo = false; bool isPlace = false;
		bool isWin = false;
		int turn = 1, dim = 0, size = 11;
		isPromoted P{};
		char** Board;
		position Sc{}, Dc{};
		string P_name[2];
		init2(Board, dim, P_name, turn, P, cap_P1_count, cap_P2_count);
		system("cls");
		char symbo = -37;
		SetClr(3);
		PlaySound(TEXT("begin"), NULL, SND_SYNC);
		printBoardNew(9, size, size, Board, cap_P1_count, cap_P2_count, P, turn);
		while (true)
		{
			isUndo = false;
			isPlace = false;
			char  sym, sym1 = 0, place_sym = '-';
			int sr = 0, sc = 0, er = 0, ec = 0;
			bool check = false;
			do
			{
				Select3(Sc, Dc, dim, Board, turn, P_name, sym1, size, P, isUndo, cap_P1_count, cap_P2_count, isPlace, place_sym);
				if (isUndo == true)
				{
					break;
				}
			} while (isValidMove(Board, Sc, Dc, P) == false);
			if (isUndo == true)
			{
				undoBoard(Board, array, arraySize, turn, cap_P1_count, cap_P2_count, cap_P1_save, cap_P2_save, save1size, save2size);
			}
			else if (isUndo == false)
			{
				saveturn(Board, array, 9, arraySize, cap_P1_count, cap_P2_count, cap_P1_save, cap_P2_save, save1size, save2size);
				updateBoard(Board, Sc, Dc, sym1, isPlace, place_sym);
			}
			PlaySound(TEXT("source"), NULL, SND_SYNC);
			printBoardNew(9, size, size, Board, cap_P1_count, cap_P2_count, P, turn);
			saveTextfile(Board, 9, "Text1.txt");
			if (ISWIN(Board, 9) == true)
			{
				cout << "\n\n Game khatam";
				_getch();
				isWin = true;
				break;
			}
			turn = (turn + 1) % 2;
			if (isWin == true)
			{
				break;
			}
		}
		system("cls");
		int choice;
		cout << "Do you want to replay ? ";
		cin >> choice;
		if (choice == 1)
		{
			Replay1(Board, 9, arraySize, array);
		}

		system("cls");
		cout << "\n\n This game Ends now \n\n Press Enter to Exit";
		_getch();
		return 0;
	}
	if (choice == 2)
	{
		system("cls");
		SetClr(15);
		char array[150][9][9]{};
		// Pattern for Capture : P B R L N S G
		int cap_P1_count[7]{}, cap_P2_count[7]{};
		int cap_P1_save[150][7]{}, cap_P2_save[150][7]{};
		int arraySize = 0, save1size = 0, save2size = 0;
		bool isUndo = false; bool isPlace = false; bool isWin = false;
		int turn = 1, dim = 0, size = 11;
		isPromoted P{};
		char** Board;
		position Sc{}, Dc{};
		string P_name[2];
		init3(Board, dim, P_name, turn, P, cap_P1_count, cap_P2_count);
		system("cls");
		char symbo = -37;
		SetClr(3);
		PlaySound(TEXT("begin"), NULL, SND_SYNC);
		printBoardNew(9, size, size, Board, cap_P1_count, cap_P2_count, P, turn);
		while (true)
		{
			isUndo = false;
			isPlace = false;
			char  sym, sym1 = 0, place_sym = '-';
			int sr = 0, sc = 0, er = 0, ec = 0;
			bool check = false;
			do
			{
				Select3(Sc, Dc, dim, Board, turn, P_name, sym1, size, P, isUndo, cap_P1_count, cap_P2_count, isPlace, place_sym);
				if (isUndo == true)
				{
					break;
				}
			} while (isValidMove(Board, Sc, Dc, P) == false);
			if (isUndo == true)
			{
				undoBoard(Board, array, arraySize, turn, cap_P1_count, cap_P2_count, cap_P1_save, cap_P2_save, save1size, save2size);
			}
			else if (isUndo == false)
			{
				saveturn(Board, array, 9, arraySize, cap_P1_count, cap_P2_count, cap_P1_save, cap_P2_save, save1size, save2size);
				updateBoard(Board, Sc, Dc, sym1, isPlace, place_sym);
			}
			PlaySound(TEXT("source"), NULL, SND_SYNC);
			printBoardNew(9, size, size, Board, cap_P1_count, cap_P2_count, P, turn);
			saveTextfile(Board, 9, "Text1.txt");
			if (ISWIN(Board, 9) == true)
			{
				cout << "\n\n Game khatam";
				_getch();
				isWin = true;
				break;
			}
			turn = (turn + 1) % 2;
			if (isWin == true)
			{
				break;
			}

		}

		system("cls");
		int choice;
		cout << "Do you want to replay ? ";
		cin >> choice;
		if (choice == 1)
		{
			Replay1(Board, 9, arraySize, array);
		}

		system("cls");
		cout << "\n\n This game Ends now \n\n Press Enter to Exit";
		_getch();
		return 0;
	}
	_getch();
	return 0;
}


#include<iostream>
#include<time.h>
using namespace std;

struct Position
{
	int ri, ci;	
};

void Init(int &Dim, int &NOP, int &winCount,int &Turn, string* &PName,char* &PSym,char** &Board)
{
	cout<<"Dim, NOP, winCount: ";
	cin>>Dim>>NOP>>winCount;
	PSym=new char[NOP];
	PName=new string [NOP];
	Board= new char*[Dim];
	for(int ri=0; ri<Dim;ri++)
		{
			Board[ri]=new char[Dim];
			for(int ci=0;ci<Dim;ci++)
				Board[ri][ci]=' ';
					
		}
	cout<<"Enter "<<NOP<<" Names and Symbols: ";
	for(int i=0; i<NOP; i++)
		cin>>PName[i]>>PSym[i];
				
	Turn=(rand())% NOP;		    	
}

void DisplayBoard(char** Board, int Dim)
{
	system("cls");
	for(int ri=0; ri<Dim; ri++)
	{
		cout<<"\t\t\t";
		for(int ci=0;ci<Dim; ci++)
		{
			if(Board[ri][ci]==' ')
				cout<<'-';
			else 
				cout<<Board[ri][ci];
		}
		cout<<endl;
	}
}

void DisplayTurnMsg(string aikplayername)
{
	cout<<aikplayername<<" s turn ";
}

void MakeAMove(Position &Pos)
{
	cin>>Pos.ri>>Pos.ci;
	Pos.ci--;
	Pos.ri--;
}

bool IsValidPosition(char** Board,int Dim,Position Pos)
{
	if(Pos.ri>=0 && Pos.ri<Dim && Pos.ci>=0 && Pos.ci<Dim)
	{
		return Board[Pos.ri][Pos.ci]==' ';
	}
	else 
	return false;
//	return (Pos.ri>=0 && Pos.ri<Dim && Pos.ci>=0 && Pos.ci<Dim) && Board[Pos.ri][Pos.ci]==' ';
}

void UpdateBoard(char** Board,Position Pos,char aikplayerSym)
{
	Board[Pos.ri][Pos.ci]= aikplayerSym;
}

void TurnChange(int &Turn, int NOP)
{
	Turn=(Turn+1) % NOP;
}

bool DoIWinHorizontally(char** Board,int Dim,int ri,int ci,char PSym,int winCount)
{
	if(ci+winCount-1>=Dim)
		return false;
	int Count=0;
	for(int i=0; i<winCount; i++)
		{
		   if(Board[ri][ci+i]==PSym)
		   	Count++;
		}
	return Count==winCount;	
}

bool DoIWinVertically(char** Board,int Dim,int ri,int ci,char PSym,int winCount)
{
	if(ri+winCount-1>=Dim)
		return false;
	int Count=0;
	for(int i=0; i<winCount; i++)
		{
		   if(Board[ri+i][ci]==PSym)
		   	Count++;
		}
	return Count==winCount;	
}

bool DoIWinDiagonallyLeft2Right(char** Board,int Dim,int ri,int ci,char PSym,int winCount)
{
	if(ci+winCount-1>=Dim)
		return false;
	if(ri+winCount-1>=Dim)
		return false;
	int Count=0;
	for(int i=0; i<winCount; i++)
		{
		   if(Board[ri+i][ci+i]==PSym)
		   	Count++;
		}
	return Count==winCount;	
}

bool DoIWinDiagonallyRight2Left(char** Board,int Dim,int ri,int ci,char PSym,int winCount)
{
	if(ri+winCount-1>=Dim)
		return false;
	if(ci-(winCount-1)<0)
		return false;
	int Count=0;
	for(int i=0; i<winCount; i++)
		{
		   if(Board[ri+i][ci-i]==PSym)
		   	Count++;
		}
	return Count==winCount;	
}

bool DoIWinHere(char** Board,int Dim,int ri,int ci,char PSym,int winCount)
{
	return DoIWinHorizontally(Board,Dim,ri,ci,PSym,winCount) ||
		   DoIWinVertically(Board,Dim,ri,ci,PSym,winCount) ||
		   DoIWinDiagonallyLeft2Right(Board,Dim,ri,ci,PSym,winCount) ||
		   DoIWinDiagonallyRight2Left(Board,Dim,ri,ci,PSym,winCount);
}
 
bool IsWin(char** Board, int Dim, char PSym, int winCount)
{
	for(int ri=0;ri<Dim;ri++)
	{
		for(int ci=0;ci<Dim;ci++)
		{
			if(DoIWinHere(Board,Dim,ri,ci,PSym,winCount))
			{
			 return true;	
			}
		}
	}
	return false;
	
}

bool Isdraw(char** Board,int Dim)
{
	for(int ri=0;ri<Dim; ri++)
	{
		for(int ci=0;ci<Dim; ci++)
		{
			if(Board[ri][ci]==' ')
			return false;
		}
	}
	return true;
}

int main()
{
	srand(time(0));
	int Dim, NOP, winCount, Turn;
	string* PName;
	char* PSym;
	char** Board;
	bool GameEnded= false;
	int Winner=-1;
	Position Pos;
	Init(Dim, NOP,winCount,Turn,PName,PSym,Board);
	DisplayBoard(Board,Dim);
	do{	
			do
			{
			DisplayTurnMsg(PName[Turn]);
			MakeAMove(Pos);
			}
			while(IsValidPosition(Board,Dim,Pos)==false);
			UpdateBoard(Board,Pos,PSym[Turn]);
			DisplayBoard(Board,Dim);
			GameEnded=(IsWin(Board,Dim,PSym[Turn],winCount));
			if(GameEnded==true)
			{
				Winner=Turn;
			}
			if(GameEnded==false)
				TurnChange(Turn,NOP);
			if(GameEnded==false)	
				GameEnded=Isdraw(Board,Dim);
		}
while(!GameEnded);

if(Winner==-1)
{
	cout<<"The game is a draw.....!!!!";
}
else
	cout<<PName[Winner]<<" has won the match !!";
return 0;	
}
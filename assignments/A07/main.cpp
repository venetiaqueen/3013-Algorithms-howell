//**************************************************************
// Date:             13 December 2019
// Title:            Program 4 - Monster Hunter
// Semester:         Fall 2019
// Course:           CMPS 3013 
// Assignment:       A07
// Author:           (Faith Howell)
// Email:            (faith-howell@outlook.com)
// Files:            (monstermaze.cpp, TermColor.h)
//**************************************************************
// This program uses A-Star algorithm allowing a set of monsters to find some character and kill him. This game is consists of 5 levels ( but I only did 3)
//***************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<map>
#include<math.h>
#include "TermGame.h"

using namespace std;
namespace term = TermGame;
namespace print = TermPrint;

struct Player
{
  int row;
  int column;
  string g;
  unsigned short foreground;
  unsigned short background;// bg color

  // Default constructor
  Player()
  {
    row = 0;
    column = 0;
    foreground = 8;
    background = 1;
    g = ". ";
  }

  Player(int r, int c, string stn)
  {
    row = r;
    column = c;
    foreground = 8;
    background = 1;
    g = stn;
  }

  Player(int r, int c, string stn, unsigned short f, 
  unsigned short b = 1)
  {
    row = r;
    column = c;
    foreground = f;
    background = b;
    g = stn;
  }

  void SetColor(unsigned short f, unsigned short b = 1)
  {
    foreground = f; // game colors
    background = b; // game colors
  }

  void Print()
  {
    print::print(g, foreground, background);
  }

};

struct Cell
{
  int row;
  int column;
  bool a;
  bool wall;
  string g;

  Cell(int r = 0, int c = 0)
  {
    row = r;
    column = c;
    g = " ";
    wall = false;
    a = false;
  }

  void PrintCell(int x = 1)
  {
    print::print(g, 8, x, false);
  }


  void GetPlayer() {
        g = " ";
    }

    void SetPlayer(string c) {
        g = c;
    }

    void MakeWall() {
        wall = true;
        g = "#";
    }

    bool GetWall()
    {
      return wall;
    }

      void Hit()
    {
      a = true;
      g = '.';
      
    }
};

double Distance(Cell * col, Player player2, int c1)
{
  double x = abs(player2.column - col->column);
  double y = abs(player2.row - col->row);

  return (x + y) + c1;
}

double monsterDist(Cell * col, Player player1)
{
  double x = player1.row - col->row;
  double y = player1.column - col->column;

  return abs(y) + abs(x);
}

class BField{
private:
  int height;
  int width;
  Cell * playercell;
  Cell * monstercell;

public:
  Cell ***field;
  BField(int rows = 16, int columns = 16)//consructor
  {
    height = rows;
    width = columns;

    field = new Cell **[height];

    for (int i = 0; i < height; i++)
    {
      field[i] = new Cell *[width];
    }

    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        field[i][j] = new Cell(i, j);
      }
    }

    Reset();
  }

  void printBField(int x = 1)
  {
    for(int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        field[i][j]->PrintCell(x);
      }
      cout << endl;
    }
  }

void Reset()
{
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {

      field[i][j]->a = false;

      field[i][j]->g = " ";
    }
  }
}

bool LegalMove(int x, int y) {


  if((x < 0 || x >= height) || (y < 0 || y >= width))
  {
    return false;
  }

  if(field[x][y]->a)//hit
  {
    return false;
  }

  if(field[x][y]->wall)
  {
    return false;
  }

  if(field[x][y]->g == "🤺")
  {
    return false;
  }

  return true;
}


bool traverse(Player player1, Player player2, vector<Player> &vect, 
int &c1, bool breadcrumbs = true)
{
  Cell * current;
  Cell * neighbor;
  Player temp;
  vector<Cell *> moves;
  int index = 0;
  bool cmove;

  // Player row and column
  int row = player1.row;
  int column = player1.column;

  current = field[row][column];

  // Keeping track of movements
  if(!current->a && breadcrumbs == true)
  {
    current->a = true;
    current->g = ".";
  }

  moves = find_neighbors(current->row, current->column);

index = choice(moves, player2, c1);

  if (moves.size())
  {
  neighbor = moves[index];

  temp.row = neighbor->row;
  temp.column = neighbor->column;

  vect.push_back(temp);
  c1++;
  return true;
  }

  return false;
}


void Move_m(Player player1, Player player2, vector<Player> &vect, bool breadcrumbs = false)
{
  Cell * current;
  Cell * neighbor;
  Player temp;
  vector<Cell *> moves;// moves monster
  int index = 0;
  bool moves_a;


  int row = player2.row;//row
  int column = player2.column;//column

  current = field[row][column];


  if(!current->a && breadcrumbs == true)
  {
    current->a = true;
    current->g = ".";
  }

  moves = find_neighbors(current->row, current->column);

 index = monster_choice(moves, player1);

  if (moves.size())
  {
  neighbor = moves[index];

  temp.row = neighbor->row;
  temp.column = neighbor->column;

  vect.push_back(temp);
  }

}


//Shows moves
vector<Cell *> find_neighbors(int row, int column)
{
  vector<Cell *> Neighbors;

  // Find moves
  if(LegalMove(row + 1, column) == true)
  {
    Neighbors.push_back(field[row + 1][column]);
  }

  if(LegalMove(row, column + 1) == true)
  {
    Neighbors.push_back(field[row][column + 1]);
  }

  if(LegalMove(row - 1, column) == true)
  {
    Neighbors.push_back(field[row - 1][column]);
  }

  if(LegalMove(row, column - 1) == true)
  {
    Neighbors.push_back(field[row][column - 1]);
  }

  return Neighbors;  
}

int choice(vector<Cell *> moves, Player player2, int c1)
{
  int mini = 99999;
  int d = 0;
  int i = 0;

  for (int j = 0; j < moves.size(); j++)
  {
    d = Distance(moves[j], player2, c1);

    if (d < mini){
      mini = d;
      i = j;
    }
  }

  return i;
}

int monster_choice(vector<Cell *> moves, Player player1)
{
  int max = -99999;
  int d = 0;
  int n = 0;

  for(int j = 0; j < moves.size(); j++)
  {
    d = monsterDist(moves[j], player1);

    if (d > max){
      max = d;
      n = j;
    }
  }

  return n;
}

};
//Levels to monster maze game


void Level_1()
{
    int rows = 20;
    int columns = 20;
    vector<Player> moves;
    bool can_move;

   
    int c1 = 1; // distance of hunter

    BField B1(rows, columns);
    
    // Random locations for player to start
    int ran1 = rand() % (rows - 1);
    int ran2 = rand() % (columns - 1);
    int ran3 = rand() % (rows - 1);
    int ran4 = rand() % (columns - 1);

   
    Player player1(ran1, ran2, "🤺");
    Player player2(ran3, ran4, "🦖");


    B1.field[player1.row][player1.column]->SetPlayer("🤺");
    B1.field[player2.row][player2.column]->SetPlayer("🦖");

    moves.push_back(player1);

    bool found = false;
    
  
    while(!found)
    {
      print::clear();
      B1.field[player1.row][player1.column]->GetPlayer();
      can_move = B1.traverse(player1, player2, moves, c1);

      if(can_move)
      {
        player1 = moves.back();
        B1.field[player1.row][player1.column]->SetPlayer("🤺");
      }

 
      else
      {
   
        moves.pop_back();
        
        player1 = moves.back();
        B1.field[player1.row][player1.column]->SetPlayer("🤺");
      }

      if(player1.row == player2.row && player1.column == player2.column)
      {
        found = true;

        B1.field[player1.row][player1.column]->GetPlayer();
        B1.field[player2.row][player2.column]->GetPlayer();
      }

      B1.printBField();
      cout << "Level 1" << endl;

      term::sleep(200);
    }
}



void Level_2()
{
    int rows = 20;
    int columns = 20;
    vector<Player> moves;
    bool can_move;
    int c1 = 1;

    BField B1(rows, columns);
    
    // Randoms spots where player can start
    int ran1 = rand() % (rows - 1);
    int ran2 = rand() % (columns - 1);
    int ran3 = rand() % (rows - 1);
    int ran4 = rand() % (columns - 1);

    Player player1(ran1, ran2, "🤺");
    Player player2(ran3, ran4, "🦖");

    B1.field[player1.row][player1.column]->SetPlayer("🤺");
    B1.field[player2.row][player2.column]->SetPlayer("🦖");

    moves.push_back(player1);

   
    int count = 0;
    
    
    while(count < 2) // if the moster is caught more than once
    {
      print::clear();
      B1.field[player1.row][player1.column]->GetPlayer();
      can_move = B1.traverse(player1, player2, moves, c1);

      if(can_move)
      {
        player1 = moves.back();
        B1.field[player1.row][player1.column]->SetPlayer("🤺");
      }

      else
      {
        moves.pop_back();
        
        player1 = moves.back();
        B1.field[player1.row][player1.column]->SetPlayer("🤺");
      }

      if(player1.row == player2.row && player1.column == player2.column)
      {
        count++;

        B1.field[player1.row][player1.column]->GetPlayer();
        B1.field[player2.row][player2.column]->GetPlayer();

        // Random locations for player to start
        ran1 = rand() % (rows - 1);
        ran2 = rand() % (columns - 1);
        ran3 = rand() % (rows - 1);
        ran4 = rand() % (columns - 1);

        player1.row = ran1;
        player1.column = ran2;
        player2.row = ran3;
        player2.column = ran4;

        B1.Reset();

        // Set the monster back in the game
        B1.field[player2.row][player2.column]->SetPlayer("🦖");
      }

      B1.printBField(7);
      cout << "Level 2" << endl;
      term::sleep(200);
    }
}


void Level_3()
{
    int rows = 10;
    int columns = 10;
    vector<Player> player_moves;
    vector<Player> mmoves;
    bool can_move;
    int c1 = 1;
    int counter = 0;

    BField B1(rows, columns);
    
    // random locations
    int ran1 = rand() % (rows - 1);
    int ran2 = rand() % (columns - 1);
    int ran3 = rand() % (rows - 1);
    int ran4 = rand() % (columns - 1);

   
    Player player1(ran1, ran2, "🤺");
    Player player2(ran3, ran4, "🦖");

    
    B1.field[player1.row][player1.column]->SetPlayer("🤺");
    B1.field[player2.row][player2.column]->SetPlayer("🦖");

    player_moves.push_back(player1);
    mmoves.push_back(player2);

    bool found = false;
    
    
    while(!found && counter < 100)
    {

      print::clear();
      B1.field[player1.row][player1.column]->GetPlayer();
      B1.field[player2.row][player2.column]->GetPlayer();

      can_move = B1.traverse(player1, player2, player_moves, c1, true);

      B1.Move_m(player1, player2, mmoves);
      player2 = mmoves.back();
      B1.field[player2.row][player2.column]->SetPlayer("🦖");

      if(can_move)
      {
        player1 = player_moves.back();
        B1.field[player1.row][player1.column]->SetPlayer("🤺");
      }


      else
      {
      
        player_moves.pop_back();
        
        player1 = player_moves.back();
        B1.field[player1.row][player1.column]->SetPlayer("🤺");
      }

      if(player1.row == player2.row && player1.column == player2.column)
      {
        found = true;

        B1.field[player1.row][player1.column]->GetPlayer();
        B1.field[player2.row][player2.column]->GetPlayer();
      }

      counter ++;
      B1.printBField(6);
      cout << "Level 3" << endl;
      term::sleep(200);
    }
}

int main()
{

  srand(time(0));

  Level_1();

  Level_2();

  Level_3();

  return 0;
}

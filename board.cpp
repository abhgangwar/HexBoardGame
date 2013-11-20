#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include "graph.h"
#include<string>


using namespace std;
template < class T1, class T2 > void
init_board (graph < T1, T2 > &g, int n)	// Initiates a empty board
{
  int node_cnt = 0;		// counts no of nodes
  for (int i = 0; i < n; i++)	// to initiate topmost row of board
    {
      if (i == 0)
	{
	  g.addnode (node_cnt, node_cnt + 1, 0);	// corner nodes
	  g.addnode (node_cnt, node_cnt + n, 0);
	}
      else if (i == n - 1)	//corner nodes
	{
	  g.addnode (node_cnt, node_cnt - 1, 0);
	  g.addnode (node_cnt, node_cnt + n, 0);
	  g.addnode (node_cnt, node_cnt + n - 1, 0);
	}
      else
	{
	  g.addnode (node_cnt, node_cnt + 1, 0);
	  g.addnode (node_cnt, node_cnt - 1, 0);
	  g.addnode (node_cnt, node_cnt + n, 0);
	  g.addnode (node_cnt, node_cnt + n - 1, 0);
	}
      ++node_cnt;
    }

  for (int i = 1; i < n - 1; i++)	// To initiate further rows except last row of the board
    {
      for (int j = 0; j < n; j++)
	{
	  if (j == 0)		//corner nodes
	    {
	      g.addnode (node_cnt, node_cnt + 1, 0);
	      g.addnode (node_cnt, node_cnt - n, 0);
	      g.addnode (node_cnt, node_cnt - n + 1, 0);
	      g.addnode (node_cnt, node_cnt + n, 0);
	    }
	  else if (j == n - 1)	//corner nodes
	    {
	      g.addnode (node_cnt, node_cnt - 1, 0);
	      g.addnode (node_cnt, node_cnt - n, 0);
	      g.addnode (node_cnt, node_cnt + n, 0);
	      g.addnode (node_cnt, node_cnt + n - 1, 0);
	    }
	  else
	    {
	      g.addnode (node_cnt, node_cnt + 1, 0);
	      g.addnode (node_cnt, node_cnt - 1, 0);
	      g.addnode (node_cnt, node_cnt + n, 0);
	      g.addnode (node_cnt, node_cnt + n - 1, 0);
	      g.addnode (node_cnt, node_cnt - n, 0);
	      g.addnode (node_cnt, node_cnt - n + 1, 0);
	    }
	  ++node_cnt;
	}
    }

  for (int i = 0; i < n; i++)	// To initiate last row of the board
    {
      if (i == 0)		//corner nodes
	{
	  g.addnode (node_cnt, node_cnt + 1, 0);
	  g.addnode (node_cnt, node_cnt - n, 0);
	  g.addnode (node_cnt, node_cnt - n + 1, 0);
	}
      else if (i == n - 1)	//corner nodes
	{
	  g.addnode (node_cnt, node_cnt - 1, 0);
	  g.addnode (node_cnt, node_cnt - n, 0);
	}
      else
	{
	  g.addnode (node_cnt, node_cnt - 1, 0);
	  g.addnode (node_cnt, node_cnt + 1, 0);
	  g.addnode (node_cnt, node_cnt - n, 0);
	  g.addnode (node_cnt, node_cnt - n + 1, 0);
	}
      ++node_cnt;
    }
  g.init_val ();		// fills all nodes with a blank
}

void
print_slash (int n)		// helps in ptinting the board
{
  int flag = 0;
  for (int i = 0; i < 2 * n - 1; i++)
    {
      cout << " ";
      char c;
      if (flag % 2 == 0)
	cout << "\\";
      else
	cout << "/";
      ++flag;
    }
  cout << endl;
}

template < class T1, class T2 > void
disp (graph < T1, T2 > &g, int n)	// Prints the board
{
  int node_cnt = 0;
  int space = 0;
  char c;
  for (int i = 0; i < n; i++)
    {
      for (int k = 0; k < space; k++)
	cout << " ";
      for (int j = 0; j < n; j++)
	{
	  if (g.get_val (node_cnt) == 1)
	    c = 'B';
	  else if (g.get_val (node_cnt) == 2)
	    c = 'R';
	  else
	    c = '.';
	  if (j != n - 1)
	    {
	      cout << c << " - ";
	      ++node_cnt;
	    }
	  else
	    {
	      cout << c;
	      ++node_cnt;
	    }
	}
      cout << endl;
      for (int m = 0; m < space; m++)
	cout << " ";
      if (i != n - 1)
	print_slash (n);
      space += 2;
    }
}

template < class T1, class T2 > bool bfs (graph < T1, T2 > &g, const T1 s, const T1 d, int player)	// To find path connectivity b/w two nodes s and d
{
  queue < T1 > list;
  map < T1, bool > path;
  map < T1, bool > visited;
  vector < T1 > ver = g.get_nodes ();
  for (auto it = ver.begin (); it != ver.end (); it++)
    {
      path[*it] = false;
      visited[*it] = false;
    }
  list.push (s);
  visited[s] = true;
  while (!list.empty ())
    {
      T1 curr_node = list.front ();
      list.pop ();
      vector < T1 > adj_curr = g.adjecent (curr_node);
      for (auto it = adj_curr.begin (); it != adj_curr.end (); it++)
	{
	  if (g.get_val (*it) == player && !visited[*it])
	    {
	      path[*it] = true;
	      if (*it == d)
		return true;
	      list.push (*it);
	      visited[*it] = true;
	    }
	}
    }
  return false;
}

template < class T1, class T2 > bool check_win (graph < T1, T2 > &g, int n, int player)	// If we find a suitable path to opposite edge, the player wins
{
  bool res;
  T1 from, to;			// The 2 nested loops checks for every valid node from and to for path connectivity
  if (player == 1)
    {
      for (int i = 0; i < n; i++)
	{
	  for (int j = 0; j < n; j++)
	    {
	      from = i * n;
	      to = (j * n) + n - 1;
	      res = bfs (g, from, to, player);
	      if (res == true)
		return true;
	    }
	}
    }
  else
    {
      for (int i = 0; i < n; i++)
	{
	  for (int j = 0; j < n; j++)
	    {
	      from = i;
	      to = (n * (n - 1)) + j;
	      res = bfs (g, from, to, player);
	      if (res == true)
		return true;
	    }
	}
    }
  return false;
}

bool
check_move (int node_cnt, int player, int n)	// To make sure that player has played a valid move 
{
  if (player == 1)
    {
      for (int i = 1; i < n - 1; i++)
	if (node_cnt == i || node_cnt == (n * (n - 1) + i))
	  return false;
    }
  else
    {
      for (int i = 1; i < n - 1; i++)
	if (node_cnt == i * n || node_cnt == ((i * n) + n - 1))
	  return false;
    }
  return true;
}


int
main ()
{
  int n;			// To store size of hex board
  graph < int, int >g;
  cout << "size of hex board: ";
  cin >> n;
  init_board (g, n);
  int player = 0;
  int i, j, node_cnt;
  bool res = false;
  cout <<"\t\t\t\t\t\t\tWelcome To Hex Board Game"
  	<<"\nGeneral Rules: "
	<<"\n1. There are 2 players in the game identified by their colours: Blue and Red "
  	<<"\n2. Blue player has to make a connected path between rightmost vertical line to leftmost vertical line."
	<<"\n3. Similarly Red player should make a connected path between topmost and bottommost horizontal line. "
    <<"\n4. Enter the coordinates of a position to play move for that position[rows and column counting starts with 0]"
	<<"\nPress any key to play..."
    << endl;
	cin.ignore();
	cin.ignore();
  while (1)
    {
      disp (g, n);
      cout << "\nEnter " << (player % 2) + 1 << " player's move"
	  <<"\nx: ";
      cin >> i;
      cout << "y: ";
      cin >> j;
      node_cnt = (i * n) + j;
      if (g.get_val (node_cnt) == -1
	  && check_move (node_cnt, (player % 2) + 1, n))
	{
	  g.set_val (node_cnt, (player % 2) + 1);
	  res = check_win (g, n, (player % 2) + 1);
	  if (res == true)
	    {
	      cout << "player: " << (player % 2) + 1 << " won" << endl;
	      exit (0);
	    }
	  ++player;

	}
      else
	cout << "illegal move..try again" << endl;

    }
  return 0;
}

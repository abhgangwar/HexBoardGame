#ifndef _GRAPH
#define _GRAPH

#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include<queue>
#include<limits>
#include<algorithm>

using namespace std;

template < class T1, class T2 > class graph
{
  typedef pair < T1, T2 > dest_cost;	// pair of destination node of edge and its cost
  map < T1, vector < dest_cost > >node;	// stores a source node of edge and its dest_cost pair
  vector < T1 > vertex;		// stores all vertices present in graph
  vector < pair < T1, int >>val;	// to store which player has a perticular node colored [for blue pl. color=1, for red pl. color=2]
public:
  void addnode (T1 from, T1 to, T2 cost);	// adds a edge(from, to) with its cost to graph
  vector < T1 > adjecent (T1 x);	// returns nodes adjecent to x
  vector < T1 > get_nodes ();	// returns all nodes which are present in graph (that is the vector vertex
  void init_val ();		// To give all nodes default value(i.e nodes are blank )
  void set_val (T1, int);	// To set color of a perticular node
  int get_val (T1);		// To get color of a perticuar node
};

template < class T1, class T2 >
  void graph < T1, T2 >::addnode (T1 from, T1 to, T2 cost)
{
  node[from].push_back (make_pair (to, cost));
  int push_from = 1, push_to = 1;
  for (auto it = vertex.begin (); it != vertex.end (); it++)
    {
      if (*it == from)
	push_from = 0;
      if (*it == to)
	push_to = 0;
    }
  if (push_from == 1)
    vertex.push_back (from);
  if (push_to == 1)
    vertex.push_back (to);

}

template < class T1, class T2 > void graph < T1, T2 >::init_val ()
{
  sort (vertex.begin (), vertex.end ());

  for (int it = 0; it < vertex.size (); it++)
    {
      val.push_back (make_pair (vertex[it], -1));	// -1 is to indicate a blank on a node
    }

}

template < class T1, class T2 > void graph < T1, T2 >::set_val (T1 nd, int player = -1)	// -1 is to indicate a blank on a node
{

  for (auto it = val.begin (); it != val.end (); it++)
    {

      if (it->first == nd)
	{
	  it->second = player;
	  break;
	}
    }
}

template < class T1, class T2 > int graph < T1, T2 >::get_val (T1 nd)	// returns the color of a perticular node
{

  for (auto it = val.begin (); it != val.end (); it++)
    {
      if (it->first == nd)
	{

	  return it->second;
	}
    }
  return -1;
}

template < class T1, class T2 >
  vector < T1 > graph < T1, T2 >::adjecent (T1 x)
{
  vector < T1 > adjver;
  for (auto it = node[x].begin (); it != node[x].end (); it++)
    {
      adjver.push_back (it->first);
    }
  return adjver;
}

template < class T1, class T2 > vector < T1 > graph < T1, T2 >::get_nodes ()
{
  return vertex;
}

#endif

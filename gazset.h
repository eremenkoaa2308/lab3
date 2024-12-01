#pragma once
#include "pipe.h"
#include "cs.h"
#include <map>
#include <vector>
using namespace std;
class gazset
{
public:
	map<int, pipe> Pipe;
	map<int, cs> Cs1;
	map<int, cs> Cs2;
	void setpipe(pipe p,int id);
	void setStartCs(cs c,int id);
	void setEndCs(cs c,int id);
	pipe getPipe(int id);
	cs getStartCs(int id);
	cs getEndCs(int id);
	void createCon(pipe p, cs c1, cs c2, int i);
	vector<int> topologicalSort();
};


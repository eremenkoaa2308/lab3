#pragma once
#include "pipe.h"
#include "cs.h"
#include <map>
using namespace std;
class gazset
{
private:
	map<int,pipe> Pipe;
	map<int, cs> Cs1;
	map<int, cs> Cs2;
public:
	void setpipe(pipe p,int id);
	void setStartCs(cs c,int id);
	void setEndCs(cs c,int id);
	pipe getPipe(int id);
	cs getStartCs(int id);
	cs getEndCs(int id);
};


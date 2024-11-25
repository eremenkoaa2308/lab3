#pragma once
#include "pipe.h"
#include "cs.h"
class gazset
{
private:
	pipe Pipe;
	cs Cs1;
	cs Cs2;
public:
	void setpipe(pipe p);
	void setStartCs(cs c);
	void setEndCs(cs c);
	pipe getPipe();
	cs getStartCs();
	cs getEndCs();
};


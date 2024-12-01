#include "gazset.h"

void gazset::setpipe(pipe p,int id)
{
	Pipe[id] = p;
}

void gazset::setStartCs(cs c,int id)
{
	Cs1[id] = c;
}

void gazset::setEndCs(cs c, int id)
{
	Cs2[id] = c;
}

pipe gazset::getPipe(int id)
{
	return Pipe[id];
}

cs gazset::getStartCs(int id)
{
	return Cs1[id];
}

cs gazset::getEndCs(int id)
{
	return Cs2[id];
}

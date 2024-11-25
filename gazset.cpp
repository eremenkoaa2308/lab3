#include "gazset.h"

void gazset::setpipe(pipe p)
{
	Pipe = p;
}

void gazset::setStartCs(cs c)
{
	Cs1 = c;
}

void gazset::setEndCs(cs c)
{
	Cs2 = c;
}

pipe gazset::getPipe()
{
	return Pipe;
}

cs gazset::getStartCs()
{
	return Cs1;
}

cs gazset::getEndCs()
{
	return Cs2;
}

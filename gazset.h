#pragma once
#include "pipe.h"
#include "cs.h"
using namespace std;
class gazset
{
private:
	pipe p;
	int idp;
	cs c1;
	int idc1;
	cs c2;
	int idc2;
public:
	gazset(pipe pe, int i, cs c11, int i1, cs cs22, int i2);
	gazset();
	pipe getPipe() const;
	int getPipeID() const;
	cs getCs1() const;
	cs getCs2() const;
	int getCs1ID() const;
	int getCs2ID() const;
};


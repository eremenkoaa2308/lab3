#include "gazset.h"

gazset::gazset(pipe pe, int i, cs c11, int i1, cs cs22, int i2)
{
	p = pe;
	idp = i;
	c1 = c11;
	idc1 = i1;
	c2 = cs22;
	idc2 = i2;
}

gazset::gazset()
{
	p = pipe();
	c1 = cs();
	c2 = cs();
}

pipe gazset::getPipe() const
{
	return p;
}

int gazset::getPipeID() const
{
	return idp;
}

cs gazset::getCs1() const
{
	return c1;
}

cs gazset::getCs2() const
{
	return c2;
}

int gazset::getCs1ID() const
{
	return idc1;
}

int gazset::getCs2ID() const
{
	return idc2;
}

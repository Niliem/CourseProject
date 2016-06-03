#include "web.hpp"

Web::Web(int sizex, int sizey, std::vector<int> inP)
	: sizeX{ sizex }
	, sizeY{ sizey }
	, limit{100}
{
	weight.resize(sizeX * sizeY, 0);
	mul.resize(sizeX * sizeY, 0);

	input.resize(sizeX * sizeY, 0);
	input = inP;
}

void Web::mul_w()
{
	for (int x = 0; x < sizeX * sizeY; x++)
	{
		mul[x] = input[x] * weight[x];
	}
}

void Web::Sum()
{
	sum = 0;
	for (int x = 0; x < sizeX * sizeY; x++)
	{
		sum += mul[x];
	}
}

bool Web::Rez()
{
	if (sum >= limit)
		return true;
	else return false;
}

void Web::incW(std::vector<int> inP)
{
	for (int x = 0; x < sizeX * sizeY; x++)
	{
		weight[x] += inP[x];
	}
}

void Web::decW(std::vector<int> inP)
{
	for (int x = 0; x < sizeX * sizeY; x++)
	{
		weight[x] -= inP[x];
	}
}

#pragma once

#include <vector>

class Web
{
public:
   	std::vector<int> mul;
	std::vector<int> weight;
	std::vector<int> input;

	int limit;
	int sum;

	int sizeX;
	int sizeY;

	Web(int sizex, int sizey, std::vector<int> inP);

	void mul_w();
	void Sum();
	bool Rez();
	void incW(std::vector<int> inP);
	void decW(std::vector<int> inP);

};

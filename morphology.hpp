#pragma once
#include <vector>
#include <memory>
#include "object.hpp"
#include <map>


class Morphology
{
public:
	static void GenerateObjectList(std::vector<std::vector<int>> map, std::vector<std::shared_ptr<Object>> &objects, int Width, int Height, std::vector<std::vector<int>> &Labels);

private:
	static void Fill(std::vector<std::vector<int>> &img, std::vector<std::vector<int>> &labels, int width, int height, int x, int y, int L, std::multimap<int, Cell> &maps);
	static void Labeling(std::vector<std::vector<int>> &img, std::vector<std::vector<int>> &labels, int width, int height, std::multimap<int, Cell> &maps);
};

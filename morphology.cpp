#include "morphology.hpp"


void Morphology::GenerateObjectList(std::vector<std::vector<int>> map, std::vector<std::shared_ptr<Object>>& objects, int Width, int Height, std::vector<std::vector<int>>& Labels)
{
	std::multimap<int, Cell> Maps;
	Labeling(map, Labels, Width, Height, Maps);

	std::multimap<int, Cell>::iterator k, v;

	for (k = Maps.begin(); k != Maps.end(); k = v)
	{
		Object o;
		auto theKey = k->first;
		auto keyRange = Maps.equal_range(theKey);
		for (v = keyRange.first; v != keyRange.second; ++v)
			o.addCell(Cell(v->second.x, v->second.y));
		o.generateObject();
		objects.push_back(std::make_shared<Object>(o));
	}
}

void Morphology::Fill(std::vector<std::vector<int>>& img, std::vector<std::vector<int>>& labels, int width, int height, int x, int y, int L, std::multimap<int, Cell>& maps)
{
	if ((labels[x][y] == 0) & (img[x][y] == 1))
	{
		maps.insert(std::make_pair(L, Cell(y, x)));
		labels[x][y] = L;
		// 4x
		if (x > 0)
			Fill(img, labels, width, height, x - 1, y, L, maps);
		if (x < height - 1)
			Fill(img, labels, width, height, x + 1, y, L, maps);
		if (y > 0)
			Fill(img, labels, width, height, x, y - 1, L, maps);
		if (y < width - 1)
			Fill(img, labels, width, height, x, y + 1, L, maps);

		// 8x
		if (x > 0 && y > 0)
			Fill(img, labels, width, height, x - 1, y - 1, L, maps);
		if (x < height - 1 && y > 0)
			Fill(img, labels, width, height, x + 1, y - 1, L, maps);
		if (x > 0 && y < width - 1)
			Fill(img, labels, width, height, x - 1, y + 1, L, maps);
		if (x < height - 1 && y < width - 1)
			Fill(img, labels, width, height, x + 1, y + 1, L, maps);
	}
}

void Morphology::Labeling(std::vector<std::vector<int>>& img, std::vector<std::vector<int>>& labels, int width, int height, std::multimap<int, Cell>& maps)
{
	auto L = 1;
	for (auto x = 0; x < height; ++x)
		for (auto y = 0; y < width; ++y)
			Fill(img, labels, width, height, x, y, L++, maps);
}

#pragma once

#include <vector>
#include <string>

#include "cell.hpp"

class Object
{
public:
    Object();

    bool addCell(Cell cell);

    void generateObject();
    void generateImage();

    void resize(int newWidth, int newHeight);

    int count() const;

    int width() const;
    int height() const;
    int x() const;
    int y() const;

    std::string print();
	std::string printImage();

private:
    std::vector<Cell> m_Cells;
    int m_MinX;
    int m_MinY;
    int m_MaxX;
    int m_MaxY;

    int m_Width;
    int m_Height;

    bool m_isGenerated;

    std::vector<std::vector<int>> m_Image;
};


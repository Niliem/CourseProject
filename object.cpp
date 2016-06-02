#include "object.hpp"
#include <string>

Object::Object()
	: m_MinX{ 0 }
	, m_MinY{ 0 }
	, m_MaxX{ 0 }
	, m_MaxY{ 0 }
	, m_Width{ 0 }
	, m_Height{ 0 }
	, m_isGenerated{ false }
{
}

bool Object::addCell(Cell cell)
{
	if (m_isGenerated)
		return false;
	m_Cells.push_back(cell);
	return true;
}

int Object::getCellValue(int x, int y) const
{
	return m_Image[y][x];
}

void Object::generateObject()
{
	m_MinX = m_Cells[0].x;
	m_MaxX = m_Cells[0].x;
	m_MinY = m_Cells[0].y;
	m_MaxY = m_Cells[0].y;
	for (auto& i : m_Cells)
	{
		m_MinX = (i.x < m_MinX) ? i.x : m_MinX;
		m_MaxX = (i.x > m_MaxX) ? i.x : m_MaxX;
		m_MinY = (i.y < m_MinY) ? i.y : m_MinY;
		m_MaxY = (i.y > m_MaxY) ? i.y : m_MaxY;
	}
	m_Width = m_MaxX - m_MinX + 1;
	m_Height = m_MaxY - m_MinY + 1;
	generateImage();
	m_isGenerated = true;
}

void Object::generateImage()
{
	m_Image.resize(m_Height);
	for (auto i = 0; i < m_Height; ++i)
	{
		m_Image[i].resize(m_Width);
		for (auto j = 0; j < m_Width; ++j)
		{
			for (auto& c : m_Cells)
			{
				if ((c.x - m_MinX) == j && (c.y - m_MinY) == i)
				{
					m_Image[i][j] = 1;
					break;
				}
				else
					m_Image[i][j] = 0;
			}
		}
	}
}

void Object::resize(int newWidth, int newHeight)
{
	std::vector<std::vector<int>> tempImage = m_Image;
	m_Image.resize(newHeight);
	for (auto i = 0; i < newHeight; ++i)
	{
		m_Image[i].resize(newWidth, 0);
	}
	auto minHeight = (newHeight < m_Height) ? newHeight : m_Height;
	auto maxHeight = (newHeight > m_Height) ? newHeight : m_Height;
	auto startHeight = static_cast<int>((maxHeight - minHeight) / 2);

	auto minWidth = (newWidth < m_Width) ? newWidth : m_Width;
	auto maxWidth = (newWidth > m_Width) ? newWidth : m_Width;
	auto startWidth = static_cast<int>((maxWidth - minWidth) / 2);

	for (auto i = 0; i < m_Height; ++i)
	{
		for (auto j = 0; j < m_Width; ++j)
		{
			int _i = (i + startHeight < newHeight) ? i + startHeight : newHeight - 1;
			int _j = (j + startWidth < newWidth) ? j + startWidth : newWidth - 1;
			m_Image[_i][_j] = tempImage[i][j];
		}
	}
	m_Height = newHeight;
	m_Width = newWidth;
}

int Object::count() const
{
	return m_Cells.size();
}

int Object::width() const
{
	return m_Width;
}

int Object::height() const
{
	return m_Height;
}

int Object::x() const
{
	return m_MinX;
}

int Object::y() const
{
	return m_MinY;
}

std::string Object::print()
{
	std::string msg;
	for (auto& i : m_Cells)
		msg += std::to_string(i.x) + ":" + std::to_string(i.y) + "\n";
	return msg;
}

std::string Object::printImage()
{
	std::string msg;
	for (auto i = 0; i < m_Height; ++i)
	{
		for (auto j = 0; j < m_Width; j++)
			msg += std::to_string(m_Image[i][j]) + " ";
		msg += "\n";
	}
	msg += "\n";
	return msg;
}

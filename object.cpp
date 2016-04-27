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
	// TODO: Resize m_Cells;
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

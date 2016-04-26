#include "object.hpp"

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
	if (this->m_isGenerated)
		return false;
	this->m_Cells.push_back(cell);
	return true;
}

void Object::generateObject()
{
	this->m_MinX = this->m_Cells[0].x;
	this->m_MaxX = this->m_Cells[0].x;
	this->m_MinY = this->m_Cells[0].y;
	this->m_MaxY = this->m_Cells[0].y;
	for (auto& i : this->m_Cells)
	{
		this->m_MinX = (i.x < this->m_MinX) ? i.x : this->m_MinX;
		this->m_MaxX = (i.x > this->m_MaxX) ? i.x : this->m_MaxX;
		this->m_MinY = (i.y < this->m_MinY) ? i.y : this->m_MinY;
		this->m_MaxY = (i.y > this->m_MaxY) ? i.y : this->m_MaxY;
	}
	this->m_Width = this->m_MaxX - this->m_MinX + 1;
	this->m_Height = this->m_MaxY - this->m_MinY + 1;
	this->generateImage();
	this->m_isGenerated = true;
}

void Object::generateImage()
{
	this->m_Image.resize(this->m_Height);
	for (auto i = 0; i < this->m_Height; ++i)
	{
		this->m_Image[i].resize(this->m_Width);
		for (auto j = 0; j < this->m_Width; ++j)
		{
			for (auto& c : this->m_Cells)
			{
				if ((c.x - this->m_MinX) == j && (c.y - this->m_MinY) == i)
				{
					this->m_Image[i][j] = 1;
					break;
				}
				else
					this->m_Image[i][j] = 0;
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
	return this->m_Cells.size();
}

int Object::width() const
{
	return this->m_Width;
}

int Object::height() const
{
	return this->m_Height;
}

int Object::x() const
{
	return this->m_MinX;
}

int Object::y() const
{
	return this->m_MinY;
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
	for (auto i = 0; i < this->m_Height; ++i)
	{
		for (auto j = 0; j < this->m_Width; j++)
			msg += std::to_string(this->m_Image[i][j]) + " ";
		msg += "\n";
	}
	msg += "\n";
	return msg;
}

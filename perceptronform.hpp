#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>

#include "segmentationform.hpp"

class PerceptronForm
	: public QMainWindow
{
	Q_OBJECT
public:
	explicit PerceptronForm(std::vector<std::shared_ptr<Object>> arrows, QWidget *parent = nullptr);
	std::vector<std::shared_ptr<Object>> mArrowObjects;
};

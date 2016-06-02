#include "perceptronform.hpp"

PerceptronForm::PerceptronForm(std::vector<std::shared_ptr<Object>> arrows, QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowTitle("Perceptron");

	mArrowObjects = arrows;
}

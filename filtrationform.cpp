#include "filtrationform.hpp"

FiltrationForm::FiltrationForm(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Filtration");
}

void FiltrationForm::updateImageLabel(std::shared_ptr<QImage> image, std::shared_ptr<QLabel> label, int minWidth, int minHeight)
{

}

void FiltrationForm::binarization(std::shared_ptr<QImage> image, int treshHold)
{

}

void FiltrationForm::binarization(std::shared_ptr<QImage> image)
{

}

void FiltrationForm::inversion(std::shared_ptr<QImage> image)
{

}


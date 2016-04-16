#include "filtrationform.hpp"

FiltrationForm::FiltrationForm(std::shared_ptr<QImage> image, QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Filtration");

	mCurrentImage = image;

	mImageLabel = new QLabel();
	vLayout = new QVBoxLayout();

	mWindow = new QWidget();

	vLayout->addWidget(mImageLabel);
	mWindow->setLayout(vLayout);
	setCentralWidget(mWindow);

	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void FiltrationForm::closeEvent(QCloseEvent* event)
{
	event->ignore();
	inversion(mCurrentImage);
	emit getImage(mCurrentImage);
	event->accept();
}

void FiltrationForm::updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const
{
	label->setPixmap(QPixmap::fromImage(*image).scaled(300, 300));
}

void FiltrationForm::binarization(std::shared_ptr<QImage> image, int treshHold)
{
	for (auto i = 0; i < image->height(); ++i)
	{
		for (auto j = 0; j < image->width(); ++j)
		{
			if ((QColor(image->pixel(j, i)).red() + QColor(image->pixel(j, i)).green() + QColor(image->pixel(j, i)).blue()) / 3 < treshHold)
			{
				image->setPixel(j, i, qRgb(0, 0, 0));
			}
			else
			{
				image->setPixel(j, i, qRgb(255, 255, 255));
			}
		}
	}
}

void FiltrationForm::binarization(std::shared_ptr<QImage> image)
{
	auto treshHold = 0;
	
	binarization(image, treshHold);
}

void FiltrationForm::inversion(std::shared_ptr<QImage> image)
{
	for (auto i = 0; i < image->height(); ++i)
	{
		for (auto j = 0; j < image->width(); ++j)
		{
			image->setPixel(j, i, QColor(image->pixel(j, i)).red() > 0 ? qRgb(0, 0, 0) : qRgb(255, 255, 255));
		}
	}
}


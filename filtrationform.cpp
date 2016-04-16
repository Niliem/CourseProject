#include "filtrationform.hpp"

FiltrationForm::FiltrationForm(std::shared_ptr<QImage> image, QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowTitle("Filtration");

	mCurrentImage = image;

	mImageLabel = new QLabel();
	mVLayout = new QVBoxLayout();

	mWindow = new QWidget();

	mVLayout->addWidget(mImageLabel);
	mWindow->setLayout(mVLayout);
	setCentralWidget(mWindow);

	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void FiltrationForm::closeEvent(QCloseEvent* event)
{
	event->ignore();
	binarization(mCurrentImage);
	inversion(mCurrentImage);
	emit getImage(mCurrentImage);
	//event->accept();
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
			if ((image->pixelColor(j, i).red() + image->pixelColor(j, i).green() + image->pixelColor(j, i).blue()) / 3 < treshHold)
			{
				image->setPixelColor(j, i, qRgb(0, 0, 0));
			}
			else
			{
				image->setPixelColor(j, i, qRgb(255, 255, 255));
			}
		}
	}
}

void FiltrationForm::binarization(std::shared_ptr<QImage> image)
{
	auto treshHold = 0;
	auto color = 0;
	for (auto i = 0; i < image->height(); ++i)
	{
		for (auto j = 0; j < image->width(); ++j)
		{
			color = (image->pixelColor(j, i).red() + image->pixelColor(j, i).green() + image->pixelColor(j, i).blue()) / 3;
			treshHold += color;
		}
	}
	treshHold /= image->height() * image->width();
	setWindowTitle(std::to_string(treshHold).c_str());
	binarization(image, treshHold);
}

void FiltrationForm::inversion(std::shared_ptr<QImage> image) const
{
	auto r = 0;
	auto g = 0;
	auto b = 0;
	for (auto i = 0; i < image->height(); ++i)
	{
		for (auto j = 0; j < image->width(); ++j)
		{
			r = 255 - image->pixelColor(j, i).red();
			g = 255 - image->pixelColor(j, i).green();
			b = 255 - image->pixelColor(j, i).blue();
			image->setPixelColor(j, i, qRgb(r, g, b));
		}
	}
}


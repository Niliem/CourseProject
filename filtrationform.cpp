#include "filtrationform.hpp"
#include <QIntValidator>

FiltrationForm::FiltrationForm(std::shared_ptr<QImage> image, QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowTitle("Filtration");

	mCurrentImage = image;
	mOriginalImage = std::make_shared<QImage>(*image);

	mImageLabel = new QLabel();
	mVLayout = new QVBoxLayout();

	//Binarization
	mRadioButtonGroupBox = new QGroupBox(tr("Binarization"));
	mBinarizationWithTresHoldRadioButton = new QRadioButton(tr("Binarization with treshold"));
	connect(mBinarizationWithTresHoldRadioButton, SIGNAL(clicked(bool)), this, SLOT(checkRadioButtons()));
	mBinarizationWithOutTresHoldRadioButton = new QRadioButton(tr("Binarization without treshold"));
	connect(mBinarizationWithOutTresHoldRadioButton, SIGNAL(clicked(bool)), this, SLOT(checkRadioButtons()));

	mThesHoldEdit = new QLineEdit("0");
	mThesHoldEdit->setValidator(new QIntValidator(0, 255, this));

	mRadioButtonsVBoxLayout = new QVBoxLayout();
	mFirstRadioButtonsHBoxLayout = new QHBoxLayout();
	mSecondRadioButtonsHBoxLayout = new QHBoxLayout();	
	mControllButtonsHBoxLayout = new QHBoxLayout();

	mBinarizationButton = new QPushButton(tr("Binarization"));
	connect(mBinarizationButton, SIGNAL(pressed()), this, SLOT(binarizationButton()));

	mWindow = new QWidget();

	mBinarizationWithTresHoldRadioButton->setChecked(true);
	mBinarizationWithOutTresHoldRadioButton->setChecked(false);

	mFirstRadioButtonsHBoxLayout->addWidget(mBinarizationWithTresHoldRadioButton);
	mFirstRadioButtonsHBoxLayout->addWidget(mThesHoldEdit);

	mSecondRadioButtonsHBoxLayout->addWidget(mBinarizationWithOutTresHoldRadioButton);


	mRadioButtonsVBoxLayout->addLayout(mFirstRadioButtonsHBoxLayout);
	mRadioButtonsVBoxLayout->addLayout(mSecondRadioButtonsHBoxLayout);
	mRadioButtonsVBoxLayout->addWidget(mBinarizationButton);

	mRadioButtonGroupBox->setLayout(mRadioButtonsVBoxLayout);
	///Binarization

	mInversionButton = new QPushButton(tr("Inversion"));
	connect(mInversionButton, SIGNAL(pressed()), this, SLOT(inversionImage()));

	mOkButton = new QPushButton(tr("Ok"));
	connect(mOkButton, SIGNAL(pressed()), this, SLOT(ok()));

	mCanselButton = new QPushButton(tr("Cancel"));
	connect(mCanselButton, SIGNAL(pressed()), this, SLOT(cancel()));

	mControllButtonsHBoxLayout->addWidget(mOkButton);
	mControllButtonsHBoxLayout->addWidget(mCanselButton);

	mVLayout->addWidget(mImageLabel);
	mVLayout->addWidget(mRadioButtonGroupBox);
	mVLayout->addWidget(mInversionButton);
	mVLayout->addLayout(mControllButtonsHBoxLayout);

	mWindow->setLayout(mVLayout);
	setCentralWidget(mWindow);

	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void FiltrationForm::checkRadioButtons()
{
	if(mBinarizationWithTresHoldRadioButton->isChecked())
	{
		mThesHoldEdit->setVisible(true);
	}
	else if(mBinarizationWithOutTresHoldRadioButton->isChecked())
	{
		mThesHoldEdit->setVisible(false);
	}
	else
	{ }
}

void FiltrationForm::binarizationButton()
{
	if (mBinarizationWithTresHoldRadioButton->isChecked())
	{
		auto thresHold = mThesHoldEdit->text().toInt();
		binarization(mCurrentImage, thresHold);
		updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
	}
	else if (mBinarizationWithOutTresHoldRadioButton->isChecked())
	{
		binarization(mCurrentImage);
		updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
	}
	else
	{
	}
}

void FiltrationForm::cancel()
{
	mCurrentImage = std::make_shared<QImage>(*mOriginalImage);
	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void FiltrationForm::inversionImage()
{
	inversion(mCurrentImage);
	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void FiltrationForm::ok()
{
	emit getImage(mCurrentImage);
	this->close();
}

void FiltrationForm::closeEvent(QCloseEvent* event)
{
	event->ignore();
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


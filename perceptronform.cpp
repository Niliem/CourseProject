#include "perceptronform.hpp"

PerceptronForm::PerceptronForm(std::vector<std::shared_ptr<Object>> arrows, QWidget *parent)
	: QMainWindow(parent)
	, currentImage{-1}
{
	this->setWindowTitle("Perceptron");

	mArrowObjects = arrows;

	std::sort(mArrowObjects.begin(), mArrowObjects.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) {
		return b->x() > a->x();
	});


	mImageLabel = new QLabel();

	mVLayout = new QVBoxLayout();
	mControllButtonsHBoxLayout = new QHBoxLayout();
	mImageHBoxLayout = new QHBoxLayout();

	mWindow = new QWidget();	

	mNextImageButton = new QPushButton(tr("next"));
	connect(mNextImageButton, SIGNAL(pressed()), this, SLOT(nextImageSlot()));

	mImageHBoxLayout->addWidget(mImageLabel);
	mImageHBoxLayout->addWidget(mNextImageButton);

	mOkButton = new QPushButton(tr("Ok"));
	connect(mOkButton, SIGNAL(pressed()), this, SLOT(ok()));

	mCanselButton = new QPushButton(tr("Cancel"));
	connect(mCanselButton, SIGNAL(pressed()), this, SLOT(cancel()));

	mControllButtonsHBoxLayout->addLayout(mImageHBoxLayout);
	mControllButtonsHBoxLayout->addWidget(mOkButton);
	mControllButtonsHBoxLayout->addWidget(mCanselButton);

	mVLayout->addLayout(mControllButtonsHBoxLayout);

	mWindow->setLayout(mVLayout);
	setCentralWidget(mWindow);

	nextImage();
}

void PerceptronForm::updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const
{
	label->setPixmap(QPixmap::fromImage(*image).scaled(image->width(), image->height(), Qt::KeepAspectRatioByExpanding));
}

std::shared_ptr<QImage> PerceptronForm::generateImage(int index)
{
	std::shared_ptr<QImage> tmpImage = std::make_shared<QImage>(mArrowObjects[index]->width(), mArrowObjects[index]->height(), QImage::Format_RGB32);
	for (size_t i = 0; i < mArrowObjects[index]->height(); i++)
	{
		for (size_t j = 0; j < mArrowObjects[index]->width(); j++)
		{
			if (mArrowObjects[index]->getCellValue(i, j) > 0)
			{
				tmpImage->setPixelColor(i, j, qRgb(0, 0, 0));
			}
			else
			{
				tmpImage->setPixelColor(i, j, qRgb(255, 255, 255));
			}
		}
	}
	//tmpImage
	return tmpImage;
}

void PerceptronForm::nextImage()
{
	currentImage++;
	updateImageLabel(generateImage(currentImage), mImageLabel, 0, 0);
	if ((currentImage + 1) >= mArrowObjects.size())
	{
		mNextImageButton->setEnabled(false);
	}
	mNextImageButton->setText(QString(std::to_string(currentImage + 1).c_str()) + "/" + QString(std::to_string(mArrowObjects.size()).c_str()));
}

void PerceptronForm::closeEvent(QCloseEvent* event)
{
	event->ignore();
	event->accept();
}

void PerceptronForm::cancel()
{
	//mCurrentImage = std::make_shared<QImage>(*mOriginalImage);
	//updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void PerceptronForm::ok()
{
	//emit getImage(mCurrentImage);
	this->close();
}

void PerceptronForm::nextImageSlot()
{
	nextImage();
}

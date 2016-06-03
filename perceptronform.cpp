#include "perceptronform.hpp"
#include <fstream>

PerceptronForm::PerceptronForm(std::vector<std::shared_ptr<Object>> arrows, QWidget *parent)
	: QMainWindow(parent)
	, currentImage{-1}
	, size{33}
	, Web1(33, 33, input)
	, Web2(33, 33, input)
{
	this->setWindowTitle("Perceptron");
	
	input.resize(size * size, 0);
	mArrowObjects = arrows;

	std::sort(mArrowObjects.begin(), mArrowObjects.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) {
		return b->x() > a->x();
	});

	
	std::vector<int> weight;
	weight.resize(size * size, 0);

	std::ifstream infile1("C://Projects/GitHub/CourseProject/w1.txt");
	for (int i = 0; i < size*size; ++i)
	{
		int a = 0;
		infile1 >> a;
		weight[i] = a;
	}
	infile1.close();
	Web1.weight = weight;

	weight.clear();
	weight.resize(size * size, 0);

	std::ifstream infile2("C://Projects/GitHub/CourseProject/w2.txt");
	for (int i = 0; i < size*size; ++i)
	{
		int a = 0;
		infile2 >> a;
		weight[i] = a;
	}
	infile2.close();
	Web2.weight = weight;

	mImageLabel = new QLabel();

	mResult1Label = new QLabel();
	mResult2Label = new QLabel();
	mResult3Label = new QLabel();

	mVLayout = new QVBoxLayout();
	mControllButtonsHBoxLayout = new QHBoxLayout();
	mImageHBoxLayout = new QHBoxLayout();

	mWindow = new QWidget();	

	mNextImageButton = new QPushButton(tr("next"));
	connect(mNextImageButton, SIGNAL(pressed()), this, SLOT(nextImageSlot()));

	mImageHBoxLayout->addWidget(mImageLabel);
	mImageHBoxLayout->addWidget(mResult1Label);
	mImageHBoxLayout->addWidget(mResult2Label);
	mImageHBoxLayout->addWidget(mResult3Label);
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
	
	QString filename = std::to_string(index).c_str();
	filename += ".bmp";
	tmpImage->save(filename);
	// Сохранение картинки 
	// с рандомным названием
	// для обучения персептрона

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

	std::vector<std::vector<int>> LI;
	LI.resize(size);
	for (auto i = 0; i < size; ++i)
		LI[i].resize(size);


	for (size_t i = 0; i < mArrowObjects[currentImage]->height(); i++)
	{
		for (size_t j = 0; j < mArrowObjects[currentImage]->width(); j++)
		{
			if (mArrowObjects[currentImage]->getCellValue(i, j) > 0)
			{
				LI[i][j] = 1;
			}
			else
			{
				LI[i][j] = 0;
			}
		}
	}
	input = ArrayToVector(LI);
	Web1.input = input;
	Web2.input = input;
	recognize();
}

void PerceptronForm::recognize()
{
	Web1.mul_w();
	Web1.Sum();
	if (Web1.Rez())
	{
		mResult1Label->setText("true");
	}
	else
	{
		mResult1Label->setText("false");
	}

	Web2.mul_w();
	Web2.Sum();
	if (Web2.Rez())
	{
		mResult2Label->setText("true");
	}
	else
	{
		mResult2Label->setText("false");
	}

	if (Web1.Rez() && Web2.Rez())
	{
		mResult3Label->setText("Left");
	}
	else if (!Web1.Rez() && !Web2.Rez())
	{
		mResult3Label->setText("Right");
	}
	else if (Web1.Rez() && !Web2.Rez())
	{
		mResult3Label->setText("Up");
	}
	else
	{
		mResult3Label->setText("Down");
	}
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
	this->close();
}

void PerceptronForm::nextImageSlot()
{
	nextImage();
}

std::vector<int> PerceptronForm::ArrayToVector(std::vector<std::vector<int>> arr)
{
	int height = size;
	int width = size;
	std::vector<int> vector;
	vector.resize(size*size, 0);
	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			vector[k] = arr[j][i];
			k++;
		}
	}
	return vector;
}

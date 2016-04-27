#include "segmentationform.hpp"

#include <fstream>
#include <QTime>

SegmentationForm::SegmentationForm(std::shared_ptr<QImage> image, QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Filtration");

    mCurrentImage = image;
    mOriginalImage = std::make_shared<QImage>(*image);

    mImageLabel = new QLabel();
    mVLayout = new QVBoxLayout();

    mControllButtonsHBoxLayout = new QHBoxLayout();

    mWindow = new QWidget();

    mSegmentationButton = new QPushButton(tr("Binarization"));
    connect(mSegmentationButton, SIGNAL(pressed()), this, SLOT(segmentationImage()));

    mOkButton = new QPushButton(tr("Ok"));
    connect(mOkButton, SIGNAL(pressed()), this, SLOT(ok()));

    mCanselButton = new QPushButton(tr("Cancel"));
    connect(mCanselButton, SIGNAL(pressed()), this, SLOT(cancel()));

    mControllButtonsHBoxLayout->addWidget(mOkButton);
    mControllButtonsHBoxLayout->addWidget(mCanselButton);

    mVLayout->addWidget(mImageLabel);
    mVLayout->addWidget(mSegmentationButton);
    mVLayout->addLayout(mControllButtonsHBoxLayout);

    mWindow->setLayout(mVLayout);
    setCentralWidget(mWindow);

    updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void SegmentationForm::closeEvent(QCloseEvent* event)
{
    event->ignore();
    event->accept();
}

void SegmentationForm::updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const
{
    label->setPixmap(QPixmap::fromImage(*image).scaled(600, image->height(), Qt::KeepAspectRatioByExpanding));
}

void SegmentationForm::segmentation(std::shared_ptr<QImage> image) const
{
	// Parse image
	auto Height = image->height();
	auto Width = image->width();

	std::vector<std::vector<int>> map(Width);

	for (auto i = 0; i < Height; ++i)
	{
		map[i].resize(Width);
		for (auto j = 0; j < Width; ++j)
		{
			map[i][j] = QColor(image->pixel(j, i)).red() > 123 ? 0 : 1;
		}
	}

	std::ofstream out("result.txt");

	std::vector<std::vector<int>> Labels(Height, std::vector<int>(Width, 0));
	std::vector<std::shared_ptr<Object>> objects;
	Morphology::GenerateObjectList(map, objects, Width, Height, Labels);

	for (auto& i : objects)
	{
		out << " Object: " << i->x() << "->" << i->width() << ":" << i->y() << "->" << i->height() << std::endl;
		out << i->printImage();
	}

	auto startX = 0;
	auto startY = 0;

	auto width = 0;
	auto height = 0;

	auto r = 0;
	auto g = 0;
	auto b = 0;

	out << "End" << std::endl;

	QTime time;

	for(auto& o : objects)
	{
		startX = o->x();
		startY = o->y();

		width = o->width();
		height = o->height();
		
		time = QTime::currentTime();
		qsrand(static_cast<uint>(time.msec()) + startX);
		r = qrand() % ((250 + 1) - 10) + 10;

		qsrand(static_cast<uint>(time.msec()) + startY);
		g = qrand() % ((250 + 1) - 10) + 10;

		qsrand(static_cast<uint>(time.msec()) + (height * width) - 4);
		b = qrand() % ((250 + 1) - 10) + 10;

		for (int i = 0; i < height ; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (o->getCellValue(j, i) > 0)
				{
					mCurrentImage->setPixelColor(j + startX, i + startY, qRgb(r, g, b));
				}				
			}			
		}
	}	
	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
	
	out.close();
}

void SegmentationForm::segmentationImage()
{
    segmentation(mCurrentImage);
    updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void SegmentationForm::cancel()
{
    mCurrentImage = std::make_shared<QImage>(*mOriginalImage);
    updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void SegmentationForm::ok()
{
    emit getImage(mCurrentImage);
    this->close();
}

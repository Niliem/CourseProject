#include "mainwindow.hpp"
#include <QFileDialog>
#include <QMenuBar>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	mCurrentImage = std::make_shared<QImage>();
	mImageLabel = new QLabel();

	vLayout = new QVBoxLayout();

	mWindow = new QWidget();

	vLayout->addWidget(mImageLabel);
	mWindow->setLayout(vLayout);
	setCentralWidget(mWindow);

	createActions();
	createMenu();    
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const
{
	label->setPixmap(QPixmap::fromImage(*image).scaled(600, image->height(), Qt::KeepAspectRatioByExpanding));
}

void MainWindow::setImage(std::shared_ptr<QImage> image)
{
	mCurrentImage = image;
	updateImageLabel(image, mImageLabel, 0, 0);
    if(mFiltrationForm != nullptr)
    {
        disconnect(mFiltrationForm.get(), SIGNAL(getImage(std::shared_ptr<QImage>)), this, SLOT(setImage(std::shared_ptr<QImage>)));
    }    
}

void MainWindow::setArrowObjects(std::vector<std::shared_ptr<Object>> object)
{
	mArrowObjects = object;

	std::sort(mArrowObjects.begin(), mArrowObjects.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) {
		return b->x() > a->x();
	});
	
	std::ofstream out("result.txt");
	for (auto& i : mArrowObjects)
	{
		i->resize(33, 33);

		drawRectangle(i->x(), i->y(), i->width(), i->height());
		out << " Object: " << i->x() << "->" << i->width() << ":" << i->y() << "->" << i->height() << std::endl;
		out << i->printImage();
	}
	
	// clear x min


	// clear x max


	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
	out << "End" << std::endl;
	out.close();

	if (mSegmentationForm != nullptr)
	{
		disconnect(mSegmentationForm.get(), SIGNAL(getArrowObjects(std::vector<std::shared_ptr<Object>>)), this, SLOT(setArrowObjects(std::vector<std::shared_ptr<Object>>)));
	}
}

void MainWindow::drawRectangle(int x, int y, int w, int h)
{
	for (size_t i = 0; i < w; i++)
	{
		mCurrentImage->setPixelColor(x + i, y, qRgb(254, 0, 0));
		mCurrentImage->setPixelColor(x + i, y + h, qRgb(254, 0, 0));
	}

	for (size_t j = 0; j < h; j++)
	{
		mCurrentImage->setPixelColor(x, y + j, qRgb(254, 0, 0));
		mCurrentImage->setPixelColor(x + w, y + j, qRgb(254, 0, 0));
	}
}

void MainWindow::createActions()
{
	mOpenImageAction = new QAction(tr("&Open image..."), this);
	connect(mOpenImageAction, SIGNAL(triggered()), this, SLOT(OpenImage()));

	mOpenFiltrationFormAction = new QAction(tr("&Open filtration form..."), this);
	connect(mOpenFiltrationFormAction, SIGNAL(triggered()), this, SLOT(OpenFiltrationForm()));

	mOpenSegmentationFormAction = new QAction(tr("&Open segmentation form..."), this);
	connect(mOpenSegmentationFormAction, SIGNAL(triggered()), this, SLOT(OpenSegmentationForm()));

	mOpenPerceptronFormAction = new QAction(tr("&Open perceptron form..."), this);
	connect(mOpenPerceptronFormAction, SIGNAL(triggered()), this, SLOT(OpenPerceptronForm()));
}

void MainWindow::createMenu()
{
	mFileMenu = menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mOpenImageAction);
	mFileMenu->addAction(mOpenFiltrationFormAction);
    mFileMenu->addAction(mOpenSegmentationFormAction);
	mFileMenu->addAction(mOpenPerceptronFormAction);
}

void MainWindow::OpenImage()
{
	mCurrentImage->load(QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.jpg)")));
	updateImageLabel(mCurrentImage, mImageLabel, 0, 0);
}

void MainWindow::OpenFiltrationForm()
{
	mFiltrationForm = std::make_shared<FiltrationForm>(mCurrentImage);	
    connect(mFiltrationForm.get(), SIGNAL(getImage(std::shared_ptr<QImage>)), this, SLOT(setImage(std::shared_ptr<QImage>)));
	mFiltrationForm->show();	
}

void MainWindow::OpenSegmentationForm()
{
    mSegmentationForm = std::make_shared<SegmentationForm>(mCurrentImage);
    connect(mSegmentationForm.get(), SIGNAL(getArrowObjects(std::vector<std::shared_ptr<Object>>)), this, SLOT(setArrowObjects(std::vector<std::shared_ptr<Object>>)));
    mSegmentationForm->show();
}

void MainWindow::OpenPerceptronForm()
{
	mPerceptronForm = std::make_shared<PerceptronForm>(mArrowObjects);
	//connect(mSegmentationForm.get(), SIGNAL(getArrowObjects(std::vector<std::shared_ptr<Object>>)), this, SLOT(setArrowObjects(std::vector<std::shared_ptr<Object>>)));
	mPerceptronForm->show();
}

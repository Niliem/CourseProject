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

	std::ofstream out("result.txt");
	for (auto& i : mArrowObjects)
	{
		i->resize(33, 33);
		out << " Object: " << i->x() << "->" << i->width() << ":" << i->y() << "->" << i->height() << std::endl;
		out << i->printImage();
	}
	out << "End" << std::endl;
	out.close();

	if (mSegmentationForm != nullptr)
	{
		disconnect(mSegmentationForm.get(), SIGNAL(getArrowObjects(std::vector<std::shared_ptr<Object>>)), this, SLOT(setArrowObjects(std::vector<std::shared_ptr<Object>>)));
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
}

void MainWindow::createMenu()
{
	mFileMenu = menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mOpenImageAction);
	mFileMenu->addAction(mOpenFiltrationFormAction);
    mFileMenu->addAction(mOpenSegmentationFormAction);
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

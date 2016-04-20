#include "mainwindow.hpp"
#include <QFileDialog>
#include <QMenuBar>

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
	label->setPixmap(QPixmap::fromImage(*image).scaled(300, 300));
}

void MainWindow::setImage(std::shared_ptr<QImage> image)
{
	mCurrentImage = image;
	updateImageLabel(image, mImageLabel, 0, 0);
    if(mFiltrationForm != nullptr)
    {
        disconnect(mFiltrationForm.get(), SIGNAL(getImage(std::shared_ptr<QImage>)), this, SLOT(setImage(std::shared_ptr<QImage>)));
    }
    if(mSegmentationForm != nullptr)
    {
        disconnect(mSegmentationForm.get(), SIGNAL(getImage(std::shared_ptr<QImage>)), this, SLOT(setImage(std::shared_ptr<QImage>)));
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
    connect(mSegmentationForm.get(), SIGNAL(getImage(std::shared_ptr<QImage>)), this, SLOT(setImage(std::shared_ptr<QImage>)));
    mSegmentationForm->show();
}

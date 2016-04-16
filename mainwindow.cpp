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
	disconnect(mFiltrationForm.get(), SIGNAL(getImage), this, SLOT(setImage));
}

void MainWindow::createActions()
{
	mOpenImageAction = new QAction(tr("&Open image..."), this);
	connect(mOpenImageAction, SIGNAL(triggered()), this, SLOT(OpenImage()));

	mOpenFiltrationFormAction = new QAction(tr("&Open filtration form..."), this);
	connect(mOpenFiltrationFormAction, SIGNAL(triggered()), this, SLOT(OpenFiltrationForm()));
}

void MainWindow::createMenu()
{
	mFileMenu = menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mOpenImageAction);
	mFileMenu->addAction(mOpenFiltrationFormAction);
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

#include "segmentationform.hpp"

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
    label->setPixmap(QPixmap::fromImage(*image).scaled(300, 300));
}

void SegmentationForm::segmentation(std::shared_ptr<QImage> image) const
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

#pragma once


#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <memory>

#include "morphology.hpp"

class SegmentationForm
        : public QMainWindow
{
    Q_OBJECT
public:
    explicit SegmentationForm(std::shared_ptr<QImage> image, QWidget *parent = nullptr);
    void closeEvent(QCloseEvent * event) override;

private:
    void updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const;
    void segmentation(std::shared_ptr<QImage> image);

    std::shared_ptr<QImage> mCurrentImage;
    std::shared_ptr<QImage> mOriginalImage;

	std::vector<std::shared_ptr<Object>> mObjects;

    QLabel* mImageLabel;

    QVBoxLayout* mVLayout;
    QWidget* mWindow;

    QPushButton* mSegmentationButton;

    QPushButton* mOkButton;
    QPushButton* mCanselButton;

    QHBoxLayout* mControllButtonsHBoxLayout;

signals:
    void getArrowObjects(std::vector<std::shared_ptr<Object>> object);

public slots:
    void segmentationImage();
    void cancel();
    void ok();
};


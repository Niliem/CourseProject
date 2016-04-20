#ifndef SEGMENTATIONFORM_HPP
#define SEGMENTATIONFORM_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <memory>

class SegmentationForm
        : public QMainWindow
{
    Q_OBJECT
public:
    explicit SegmentationForm(std::shared_ptr<QImage> image, QWidget *parent = nullptr);
    void closeEvent(QCloseEvent * event) override;

private:
    void updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const;
    void segmentation(std::shared_ptr<QImage> image) const;

    std::shared_ptr<QImage> mCurrentImage;
    std::shared_ptr<QImage> mOriginalImage;

    QLabel* mImageLabel;

    QVBoxLayout* mVLayout;
    QWidget* mWindow;

    QPushButton* mSegmentationButton;

    QPushButton* mOkButton;
    QPushButton* mCanselButton;

    QHBoxLayout* mControllButtonsHBoxLayout;

    std::shared_ptr<QMainWindow> mMainWindow;

signals:
    void getImage(std::shared_ptr<QImage> image);

public slots:
    void segmentationImage();
    void cancel();
    void ok();
};

#endif // SEGMENTATIONFORM_HPP

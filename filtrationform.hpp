#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QCloseEvent>
#include <QGroupBox>
#include <QRadioButton>
#include <memory>

class FiltrationForm
    : public QMainWindow
{
    Q_OBJECT
public:
	explicit FiltrationForm(std::shared_ptr<QImage> image, QWidget *parent = nullptr);

	void closeEvent(QCloseEvent * event) override;

private:
    void updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const;
    void binarization(std::shared_ptr<QImage> image, int treshHold);
    void binarization(std::shared_ptr<QImage> image);
	void inversion(std::shared_ptr<QImage> image) const;

    std::shared_ptr<QImage> mCurrentImage;
	std::shared_ptr<QImage> mOriginalImage;
    QLabel* mImageLabel;

	QVBoxLayout* mVLayout;
	QWidget* mWindow;

	QGroupBox* mRadioButtonGroupBox;
	QRadioButton* mBinarizationWithTresHoldRadioButton;
	QRadioButton* mBinarizationWithOutTresHoldRadioButton;
	QVBoxLayout* mRadioButtonsVBoxLayout;
	QHBoxLayout* mFirstRadioButtonsHBoxLayout;
	QHBoxLayout* mSecondRadioButtonsHBoxLayout;
	QSlider* mThesHoldSlider;
	QLabel* mThesHoldLabel;

	QPushButton* mInversionButton;

	QPushButton* mOkButton;
	QPushButton* mCanselButton;

	QHBoxLayout* mControllButtonsHBoxLayout;

    //std::shared_ptr<QMainWindow> mMainWindow;

signals:
	void getImage(std::shared_ptr<QImage> image);

public slots:
	void binarizationWithSlider(int value);
	void checkRadioButtons();
	void updateRadioButtons();
	void cancel();
	void inversionImage();
	void ok();
};


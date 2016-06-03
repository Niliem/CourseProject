#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>

#include "segmentationform.hpp"

class PerceptronForm
	: public QMainWindow
{
	Q_OBJECT
public:
	explicit PerceptronForm(std::vector<std::shared_ptr<Object>> arrows, QWidget *parent = nullptr);
	

	void closeEvent(QCloseEvent * event) override;

private:
	void updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const;
	void nextImage();
	std::shared_ptr<QImage> generateImage(int index);

	std::vector<std::shared_ptr<Object>> mArrowObjects;
	int currentImage;

	QHBoxLayout* mImageHBoxLayout;
	QLabel* mImageLabel;
	QPushButton* mNextImageButton;


	QPushButton* mOkButton;
	QPushButton* mCanselButton;

	QHBoxLayout* mControllButtonsHBoxLayout;

	QVBoxLayout* mVLayout;
	QWidget* mWindow;


public slots:
	void cancel();
	void ok();
	void nextImageSlot();
};

#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <memory>

#include "segmentationform.hpp"
#include "web.hpp"

class PerceptronForm
	: public QMainWindow
{
	Q_OBJECT
public:
	explicit PerceptronForm(std::vector<std::shared_ptr<Object>> arrows, QWidget *parent = nullptr);
	

	void closeEvent(QCloseEvent * event) override;

private:
	void setSizeTableWithImage(int w, int h, QTableWidget *table);
	void resizeTable(QTableWidget *table);
	void fillTable(QTableWidget *table, QString value);
	void fillTable(QTableWidget *table, std::vector<int> array);
	void updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const;
	void nextImage();
	void recognize();
	std::vector<int> ArrayToVector(std::vector<std::vector<int>> arr);

	std::shared_ptr<QImage> generateImage(int index);

	std::vector<std::shared_ptr<Object>> mArrowObjects;
	int currentImage;

	QHBoxLayout* mImageHBoxLayout;
	QLabel* mImageLabel;
	QPushButton* mNextImageButton;

	QTableWidget *mLambda1;
	QTableWidget *mLambda2;
	QTableWidget *mMul1;
	QTableWidget *mMul2;
	QVBoxLayout* mTablesVLayout;


	QPushButton* mOkButton;
	QPushButton* mCanselButton;

	QHBoxLayout* mControllButtonsHBoxLayout;

	QVBoxLayout* mVLayout;
	QWidget* mWindow;

	Web Web1;
	Web Web2;
	std::vector<int> input;

	QLabel* mResult1Label;
	QLabel* mResult2Label;
	QLabel* mResult3Label;

	int size;


public slots:
	void cancel();
	void ok();
	void nextImageSlot();
};

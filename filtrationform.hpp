#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QCloseEvent>
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
    QLabel* mImageLabel;

	QVBoxLayout* mVLayout;
	QWidget* mWindow;

    QPushButton* mBinarizationButton;
    QPushButton* mInversionButton;

    QPushButton* mOkButton;
    QPushButton* mCanselButton;

	std::shared_ptr<QMainWindow> mMainWindow;

signals:
	void getImage(std::shared_ptr<QImage> image);

public slots:
};


#ifndef FILTRATIONFORM_H
#define FILTRATIONFORM_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <memory>

class FiltrationForm
    : public QMainWindow
{
    Q_OBJECT
public:
    explicit FiltrationForm(QWidget *parent = 0);

private:
    void updateImageLabel(std::shared_ptr<QImage> image, std::shared_ptr<QLabel> label, int minWidth, int minHeight);
    void binarization(std::shared_ptr<QImage> image, int treshHold);
    void binarization(std::shared_ptr<QImage> image);
    void inversion(std::shared_ptr<QImage> image);

    std::shared_ptr<QImage> mCurrentImage;
    std::shared_ptr<QLabel> mImageLabel;

    std::shared_ptr<QPushButton> mFiltrationBtutton;

signals:

public slots:
};

#endif // FILTRATIONFORM_H

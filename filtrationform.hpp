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
    void updateImageLabel(QImage *image, QLabel *label, int minWidth, int minHeight);
    void binarization(QImage *image, int treshHold);
    void binarization(QImage *image);
    void inversion(QImage *image);

    QImage *mCurrentImage;
    QLabel *mImageLabel;

    QPushButton *mFiltrationBtutton;

signals:

public slots:
};

#endif // FILTRATIONFORM_H

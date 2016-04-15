#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "filtrationform.hpp"

class MainWindow
    : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::shared_ptr<FiltrationForm> mFiltrationForm;
};

#endif // MAINWINDOW_HPP

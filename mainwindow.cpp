#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mFiltrationForm = std::make_shared<FiltrationForm>();
    mFiltrationForm->show();
}

MainWindow::~MainWindow()
{

}

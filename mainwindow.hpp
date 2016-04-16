#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>

#include "filtrationform.hpp"

class MainWindow
    : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void updateImageLabel(std::shared_ptr<QImage> image, QLabel* label, int minWidth, int minHeight) const;    

private slots:
	void OpenImage();
	void OpenFiltrationForm();
	void setImage(std::shared_ptr<QImage> image);

private:
	void createActions();
	void createMenu();	

    std::shared_ptr<FiltrationForm> mFiltrationForm;

    std::shared_ptr<QImage> mCurrentImage;
    QLabel* mImageLabel;

	QVBoxLayout* vLayout;

    QAction* mOpenImageAction;
	QAction* mOpenFiltrationFormAction;
	QAction* mExitAction;

    QMenu* mFileMenu;

    QWidget* mWindow;
};


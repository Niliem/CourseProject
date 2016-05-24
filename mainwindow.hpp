#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>

#include "filtrationform.hpp"
#include "segmentationform.hpp"

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
	void OpenSegmentationForm();
	void setImage(std::shared_ptr<QImage> image);
	void setArrowObjects(std::vector<std::shared_ptr<Object>> object);

private:
	void createActions();
	void createMenu();	

    std::shared_ptr<FiltrationForm> mFiltrationForm;
    std::shared_ptr<SegmentationForm> mSegmentationForm;

	std::vector<std::shared_ptr<Object>> mArrowObjects;

    std::shared_ptr<QImage> mCurrentImage;
    QLabel* mImageLabel;

	QVBoxLayout* vLayout;

    QAction* mOpenImageAction;
	QAction* mOpenFiltrationFormAction;
	QAction* mOpenSegmentationFormAction;
	QAction* mExitAction;

    QMenu* mFileMenu;

    QWidget* mWindow;
};


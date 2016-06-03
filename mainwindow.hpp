#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>

#include "filtrationform.hpp"
#include "segmentationform.hpp"
#include "perceptronform.hpp"

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
	void OpenPerceptronForm();
	void setImage(std::shared_ptr<QImage> image);
	void setArrowObjects(std::vector<std::shared_ptr<Object>> object);

private:
	void createActions();
	void createMenu();	

	void drawRectangle(int x, int y, int w, int h);

    std::shared_ptr<FiltrationForm> mFiltrationForm;
    std::shared_ptr<SegmentationForm> mSegmentationForm;
	std::shared_ptr<PerceptronForm> mPerceptronForm;

	std::vector<std::shared_ptr<Object>> mArrowObjects;

    std::shared_ptr<QImage> mCurrentImage;
    QLabel* mImageLabel;

	QVBoxLayout* vLayout;

    QAction* mOpenImageAction;
	QAction* mOpenFiltrationFormAction;
	QAction* mOpenSegmentationFormAction;
	QAction* mOpenPerceptronFormAction;
	QAction* mExitAction;

    QMenu* mFileMenu;

    QWidget* mWindow;
};


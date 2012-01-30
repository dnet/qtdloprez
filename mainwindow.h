#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "displaylinkadapter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_actionLoad_PDF_triggered();
	void on_actionNext_slide_triggered();
	void on_actionPrevious_slide_triggered();

private:
    Ui::MainWindow *ui;

protected:
	DisplayLinkAdapter dla;
	QDir cacheDir;
	int curImage;
	void loadImage(const int image);
};

#endif // MAINWINDOW_H

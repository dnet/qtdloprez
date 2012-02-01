#ifndef RESOLUTIONDIALOG_H
#define RESOLUTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ResolutionDialog;
}

class ResolutionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ResolutionDialog(QWidget *parent = 0);
	int width() const;
	int height() const;
	int bpp() const;
	int refresh() const;
	bool useCurrent() const;
	void setParameters(int width, int height, int bpp, int refresh);
    ~ResolutionDialog();
    
private:
    Ui::ResolutionDialog *ui;
};

#endif // RESOLUTIONDIALOG_H

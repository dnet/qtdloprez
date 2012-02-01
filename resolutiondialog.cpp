#include "resolutiondialog.h"
#include "ui_resolutiondialog.h"

ResolutionDialog::ResolutionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolutionDialog) {
    ui->setupUi(this);
}

ResolutionDialog::~ResolutionDialog() {
    delete ui;
}

int ResolutionDialog::width() const {
    return ui->widthBox->value();
}

int ResolutionDialog::height() const {
    return ui->heightBox->value();
}

int ResolutionDialog::bpp() const {
    return ui->bppBox->value();
}

int ResolutionDialog::refresh() const {
    return ui->refreshBox->value();
}

bool ResolutionDialog::useCurrent() const {
    return ui->useCurrent->isChecked();
}

void ResolutionDialog::setParameters(int width, int height, int bpp, int refresh) {
	ui->widthBox->setValue(width);
	ui->heightBox->setValue(height);
	ui->bppBox->setValue(bpp);
	ui->refreshBox->setValue(refresh);
	ui->useCurrent->setText(ui->useCurrent->text().replace(
				"%RES%", QString("%1x%2").arg(width).arg(height)));
}

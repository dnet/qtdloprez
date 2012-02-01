/*
 * resolutiondialog.cpp - QT DisplayLink presenter resolution dialog
 *
 * Copyright (c) 2012 András Veres-Szentkirályi
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

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

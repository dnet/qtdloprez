/*
 * mainwindow.cpp - QT DisplayLink presenter main window
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resolutiondialog.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QProcess>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->statusbar->showMessage(QString("DisplayLink native resolution is ") + resolution());
    const QDesktopWidget dw;
    const QRect screen = dw.screenGeometry();
    const QRect size = geometry();
    move((screen.width() - size.width()) / 2,
         (screen.height() - size.height()) / 2);
}

MainWindow::~MainWindow() {
    delete ui;
}

const QString MainWindow::resolution() const {
    return QString("%1x%2").arg(dla.width()).arg(dla.height());
}

void MainWindow::on_actionLoad_PDF_triggered() {
	ResolutionDialog rd(this);
	rd.setParameters(dla.width(), dla.height(), dla.bpp(), dla.refresh());
	if (!rd.exec()) return;

	if (!rd.useCurrent()) {
		dla.setMode(rd.width(), rd.height(), rd.bpp(), rd.refresh());
	}

	QString fn = QFileDialog::getOpenFileName(this, "Open presentation", "",
			"PDF files (*.pdf)");
	if (!QFile::exists(fn)) return;

	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(fn.toUtf8());
	hash.addData(resolution().toAscii());

	cacheDir = QDir(QDir::temp().absoluteFilePath("qtdloprez") +
			QDir::separator() + hash.result().toHex());

	if (!cacheDir.exists()) {
		QProcess convert;
		QStringList params;

		params << "-density" << "200" << "-sample" << resolution();
		params << fn << cacheDir.absoluteFilePath("converted.png");

		cacheDir.mkpath(".");
		convert.start("convert", params);
		ui->statusbar->showMessage(
				QString("Converting slides to %1...").arg(resolution()));
		while (!convert.waitForFinished(100)) QCoreApplication::processEvents();
		ui->statusbar->clearMessage();
	}

	ui->actionNext_slide->setEnabled(true);
	ui->actionPrevious_slide->setEnabled(true);
	loadImage(0);
}

void MainWindow::loadImage(const int image) {
	const QString imageName = cacheDir.absoluteFilePath(
			QString("converted-%1.png").arg(image));
	if (!QFile::exists(imageName)) return;

	const QImage img(imageName);
	dla.displayImage(img);
	ui->preview->setText("");
	ui->preview->setPixmap(QPixmap::fromImage(img).scaled(ui->preview->size(),
				Qt::KeepAspectRatio, Qt::SmoothTransformation));

	curImage = image;
	ui->statusbar->showMessage(QString("Showing slide %1").arg(image));
}

void MainWindow::on_actionNext_slide_triggered() {
	loadImage(curImage + 1);
}

void MainWindow::on_actionPrevious_slide_triggered() {
	loadImage(curImage - 1);
}

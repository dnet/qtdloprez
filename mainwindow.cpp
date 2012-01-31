#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QProcess>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    resolution(QString("%1x%2").arg(dla.width()).arg(dla.height())) {
    ui->setupUi(this);
    ui->statusbar->showMessage(QString("DisplayLink native resolution is ") + resolution);
    const QDesktopWidget dw;
    const QRect screen = dw.screenGeometry();
    const QRect size = geometry();
    move((screen.width() - size.width()) / 2,
         (screen.height() - size.height()) / 2);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionLoad_PDF_triggered() {
	QString fn = QFileDialog::getOpenFileName(this, "Open presentation", "",
			"PDF files (*.pdf)");
	if (!QFile::exists(fn)) return;

	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(fn.toUtf8());
	hash.addData(resolution.toAscii());

	cacheDir = QDir(QDir::temp().absoluteFilePath("qtdloprez") +
			QDir::separator() + hash.result().toHex());

	if (!cacheDir.exists()) {
		QProcess convert;
		QStringList params;

		params << "-density" << "200" << "-sample" << resolution;
		params << fn << cacheDir.absoluteFilePath("converted.png");

		cacheDir.mkpath(".");
		convert.start("convert", params);
		ui->statusbar->showMessage(
				QString("Converting slides to %1...").arg(resolution));
		while (!convert.waitForFinished(100)) QCoreApplication::processEvents();
		ui->statusbar->clearMessage();
	}

	ui->actionNext_slide->setEnabled(true);
	ui->actionPrevious_slide->setEnabled(true);
	loadImage(0);
}

void MainWindow::loadImage(const int image) {
	QString imageName = cacheDir.absoluteFilePath(
			QString("converted-%1.png").arg(image));
	if (!QFile::exists(imageName)) return;

	QImage img(imageName);
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

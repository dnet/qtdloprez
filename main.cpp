#include <QtGui/QApplication>
#include "mainwindow.h"
#include "displaylinkexception.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	try {
		MainWindow w;
		w.show();

		return a.exec();
	} catch (NoDisplayLinkFound) {
		qDebug("No DisplayLink device was found!");
	} catch (DisplayLinkException dle) {
		qDebug(dle.message());
	}
}

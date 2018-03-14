#include "Paint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	PaintWindow paint;
	paint.show();
	return app.exec();
}

/*
	Copyright (C) 2008 by Wai Khoo

	Entry point of Knight Tour
	Written in Qt 4.4.0
	Multi-threaded
*/
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
        Q_INIT_RESOURCE(application);

        QApplication a (argc, argv);

        MainWindow w;
        w.showMaximized ();

        return a.exec();
}

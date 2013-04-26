/*
qusbmot is the host software to control the usbmot motor controller. 
Copyright (C) 2008 Andreas Goelzer, http://andreas.goelzer.de/usbmot

This file is part of qusbmot.

qusbmot is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

qusbmot is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with qusbmot.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "usbwidgets.h"
#include "usbstuff.h"
#include "mainwidget.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	QString locale = QLocale::system().name();
	QTranslator translator;
	translator.load(QString("qusbmot_") + locale);
	locale.chop(2);
	app.installTranslator(&translator);
	MainWidget mw;
	mw.show();
	return app.exec();
}

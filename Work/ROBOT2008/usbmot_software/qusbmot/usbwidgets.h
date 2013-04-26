#ifndef LEDWIDGET_H
#define LEDWIDGET_H LEDWIDGET_H
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


#include <QObject>
#include <QCheckBox>
#include <QLabel>
#include <QSlider>
#include <QWidget>
#include <QVBoxLayout>
#include <iostream>
#include "usbstuff.h"
#include "usbmotiface.h"

class usbWidget : public QWidget {
	Q_OBJECT
	public:
	int port;
	usb* usbdevice;
	QString name;
	virtual void deserialize(unsigned char* data) = 0;
	virtual void send() = 0;
	usbWidget(usb* nusbdevice, int nport, QString nname, QWidget *parent = 0) : QWidget(parent), port(nport), usbdevice(nusbdevice), name(nname) { }
	void init(){
		unsigned char buffer[8];
		usbdevice->readData(port,buffer,sizeof(buffer));
		deserialize(buffer);
	}
	public slots:
	void stateChanged(){
//		std::cout << "sc called for port " << port << std::endl;
		send();
	}
};

class LEDWidget : public usbWidget {
	Q_OBJECT
	public:
	virtual void deserialize(unsigned char* data){
		if(!*data) LEDVal->setCheckState(Qt::Checked);
		else LEDVal->setCheckState(Qt::Unchecked);
	}
	virtual void send(){
		unsigned char buffer = LEDVal->isChecked() ? 0: 1;
		usbdevice->sendData(port,&buffer,1);
	}
	LEDWidget(usb* nusbdevice, int nport, QString nname, QWidget *parent = 0) : usbWidget(nusbdevice, nport, nname, parent) {
		LEDVal = new QCheckBox(name, this);
		connect(LEDVal, SIGNAL(stateChanged(int)), this, SLOT(stateChanged()));
		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(LEDVal);
		setLayout(layout);
		init();
	}
	private:
	QCheckBox* LEDVal;
};

class MotorWidget : public usbWidget {
	Q_OBJECT
	public:
	virtual void deserialize(unsigned char* data){
		MotorData mot(data);
		MotorVal->setValue(mot.enabled);
		if(mot.forward) Forward->setCheckState(Qt::Checked);
		else Forward->setCheckState(Qt::Unchecked);
		if(mot.backward) Backward->setCheckState(Qt::Checked);
		else Backward->setCheckState(Qt::Unchecked);
	}
	virtual void send(){
		unsigned char buffer[8];
		int len = MotorData::serialize(buffer, MotorVal->value(), Forward->isChecked(), Backward->isChecked());
		usbdevice->sendData(port,buffer,len);
	}
	MotorWidget(usb* nusbdevice, int nport, QString nname, QWidget *parent = 0) : usbWidget(nusbdevice, nport, nname, parent) {
		Forward = new QCheckBox("forward", this);
		Backward = new QCheckBox("backward", this);
		MotorVal = new QSlider(this);
		MotorVal->setMaximum(65535);
		connect(MotorVal, SIGNAL(valueChanged(int)), this, SLOT(stateChanged()));
		connect(Forward, SIGNAL(stateChanged(int)), this, SLOT(stateChanged()));
		connect(Backward, SIGNAL(stateChanged(int)), this, SLOT(stateChanged()));
		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(new QLabel(name, this));
		layout->addWidget(MotorVal);
		layout->addWidget(Forward);
		layout->addWidget(Backward);
		setLayout(layout);
		init();
	}
	private:
	QSlider* MotorVal;
	QCheckBox* Forward;
	QCheckBox* Backward;
};

#endif

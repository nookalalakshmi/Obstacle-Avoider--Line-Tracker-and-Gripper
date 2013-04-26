#ifndef MAINWIDGET_H
#define MAINWIDGET_H MAINWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "usbstuff.h"
#include "usbwidgets.h"

class MainWidget : public QWidget {
	Q_OBJECT
	public:
	MainWidget(QWidget *parent = 0) : QWidget(parent){
		QHBoxLayout *layout = new QHBoxLayout;
		usb* myusb = new usb(this);
		if(myusb->handle){
			connect(myusb,SIGNAL(connectionProblem(int)),this,SLOT(close()));
			layout->addWidget(new LEDWidget(myusb, 0, tr("Red"), this));
			layout->addWidget(new LEDWidget(myusb, 1, tr("Green"), this));
			layout->addWidget(new MotorWidget(myusb, 3, tr("outer"), this));
			layout->addWidget(new MotorWidget(myusb, 4, tr("inner"), this));
		} else {
			QLabel* l= new QLabel(tr("USB device not found"));
			layout->addWidget(l);
		}

		setLayout(layout);
	}
};
#endif

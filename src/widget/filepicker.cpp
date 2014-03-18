#include "filepicker.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QResizeEvent>

constexpr int FilePicker::buttonMaxSize;


FilePicker::FilePicker(QWidget *parent) :
	QWidget(parent)
{
	createWidgets();
	show();
}

void FilePicker::set(QString text)
{
	lineEdit->setText(text);
}

QString FilePicker::value()
{
	return lineEdit->text();
}

void FilePicker::createWidgets()
{

	lineEdit = new QLineEdit(this);
	button = new QPushButton("...", this);

	connect(button, SIGNAL(clicked()), this, SLOT(openDialog()));
}

void FilePicker::resizeEvent(QResizeEvent * event)
{
	QSize size = event->size();
	int buttonSize = qMin(size.height(), buttonMaxSize);
	int lineEditLength = size.width() - buttonSize;
	lineEdit->setGeometry(0, 0, lineEditLength, buttonSize);
	button->setGeometry(lineEditLength, 0, buttonSize, buttonSize);
}

void FilePicker::openDialog()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), lineEdit->text(), tr("Files (*.*)"));

	if(!fileName.isEmpty())
		lineEdit->setText(fileName);
}

#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class FilePicker : public QWidget
{
Q_OBJECT

public:
	explicit FilePicker(QWidget *parent = 0);

	void set(QString);
	QString value();

protected:
	virtual void resizeEvent(QResizeEvent * event);

private slots:
	void openDialog();

private:
	constexpr static int buttonMaxSize = 20;

	QLineEdit * lineEdit;
	QPushButton * button;

	void createWidgets();
};

#endif // FILEPICKER_H

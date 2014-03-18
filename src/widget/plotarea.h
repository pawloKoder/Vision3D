#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QGLWidget>
#include <QVector>
#include <QVector3D>

#include "view/viewdata.h"

class PlotArea : public QGLWidget
{
	Q_OBJECT

public:
	explicit PlotArea(QWidget* = 0);
	~PlotArea();

signals:
	void mouseMove(QPoint);
	void wheelDelta(int);

public slots:
	void setViewData(ViewData);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent *event);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	void clear();
	void computeView();

	ViewData view;
	QVector3D position;
	QVector3D direction;
	QVector3D up;
};

#endif // PLOTAREA_H

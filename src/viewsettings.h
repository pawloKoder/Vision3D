#ifndef VIEWSETTINGS_H
#define VIEWSETTINGS_H

#include <QWidget>
#include "widget/view/viewdata.h"

class ViewSettings : public QObject
{
	Q_OBJECT

	ViewSettings();
	ViewSettings(const ViewSettings &) = delete;
	ViewSettings& operator=(const ViewSettings&) = delete;
	~ViewSettings();

public:
	static ViewSettings & self();

	static ViewData getViewData();

	static bool projection();
	static void toggleProjection();

signals:
	void setViewData(ViewData);

public slots:
	void setRotationX(int);
	void setRotationY(int);
	void setRotationZ(int);

	void mouseMove(QPoint);
	void wheelDelta(int);

	void setZoom(int);

private:
	ViewData data;
};

#endif // VIEWSETTINGS_H

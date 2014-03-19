#include "leftmenu.h"

#include "model.h"
#include "delegates/colorlistdelegate.h"
#include "delegates/proxydelegate.h"
#include "delegates/spinboxdelegate.h"
#include "delegates/pathdelegate.h"
#include "delegates/colorlistdelegate.h"
#include "delegates/doublespinboxdelegate.h"

LeftMenu::LeftMenu(QWidget *parent) :
	QTreeView(parent)
{
	setModel(&Model::self());
	ProxyDelegate * delegate = new ProxyDelegate();
	delegate->registerDelegate(new DoubleSpinBoxDelegate());
	delegate->registerDelegate(new SpinBoxDelegate());
	delegate->registerDelegate(new PathDelegate());
	delegate->registerDelegate(new ColorListDelegate());
	setItemDelegate(delegate);
}

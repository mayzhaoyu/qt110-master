#pragma once

#include <QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QIcon>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QMap>
#include <QPicture>
#include <qstring.h>
#include <QtWidgets/QTextEdit>
#include <QListWidget>
#include <QtWidgets/QListView>
#include <QtWidgets/QTreeView>
#include <QStandardItemModel>
#include "ui_cisDebugWidget.h"
#include "frameWriter.h"
#include "decodeFrame.h"

class cisDebugWidget : public QWidget
{
	Q_OBJECT

public:
	cisDebugWidget(QWidget *parent = Q_NULLPTR, QTcpSocket **psocket=0);
	~cisDebugWidget();

	QGridLayout * layout;
	QHBoxLayout * h_layout;
	QTextEdit * cisTextEdit;
	QTcpSocket **psocket;
	frameWriter frame_writer;



	QPushButton * fix_cap_button;
	QPushButton * fix_save_button;
	QPushButton * fix_apply_button;
	QPushButton * fix_read_button;
	QPushButton * fix_clear_button;
	QPushButton * fix_getimg_button;

	QWidget * wind;
	QListWidget * optList;
	QStringListModel* listModel;
	QStandardItemModel* itemModel;

private:
	Ui::cisDebugWidget ui;
public slots:
	void fix_capButtonClicked();
	void fix_saveButtonClicked();
	void fix_applyButtonClicked();
	void fix_readButtonClicked();
	void fix_clearButtonClicked();
	void fix_getimgButtonClicked();
	void on_clicked_optlist(QModelIndex);
};

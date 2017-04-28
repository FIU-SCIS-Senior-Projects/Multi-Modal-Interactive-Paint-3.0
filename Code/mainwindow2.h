/****************************************************************************
**
** Jim Louro
**
****************************************************************************/

#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QList>
#include <QMainWindow>

class ScribbleArea;


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent *event) override;

	private slots:
	void open();
	void save();
	void penColor();
	//void penWidth();

private:
	void createActions();
	void createMenus();
	bool maybeSave();
	bool saveFile(const QByteArray &fileFormat);
	QWidget *doc;
	ScribbleArea *scribbleArea;

	QMenu *saveAsMenu;
	QMenu *fileMenu;
	QMenu *optionMenu;
	QMenu *helpMenu;

	QAction *openAct;
	QList<QAction *> saveAsActs;
	QAction *exitAct;
	QAction *printAct;
	QAction *clearScreenAct;
	QAction *selectPenColor;
	QAction *aboutAct;
	QAction *aboutQtAct;
};


#endif

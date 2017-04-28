/****************************************************************************
**
** Jim Louro
**
****************************************************************************/

#include <QtWidgets>

#include <functional>
#include <utility>

#include "mainwindow2.h"
#include "multiscribblearea.h"


MainWindow::MainWindow()
{
	scribbleArea = new ScribbleArea;
	setCentralWidget(scribbleArea);

	createActions();
	createMenus();

	setWindowTitle(tr("Paint"));
	resize(500, 500);
	
}



void MainWindow::closeEvent(QCloseEvent *event)

{
	if (maybeSave()) {
		event->accept();
	}
	else {
		event->ignore();
	}
}



void MainWindow::open()

{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"), QDir::currentPath());
		if (!fileName.isEmpty())
			scribbleArea->openImage(fileName);
	}
}



void MainWindow::save()

{
	QAction *action = qobject_cast<QAction *>(sender());
	QByteArray fileFormat = action->data().toByteArray();
	saveFile(fileFormat);
}



//fix this its expecting a doc to run the fucntion to get the new pen color
void MainWindow::penColor()
{
	const QColor newColor = QColorDialog::getColor(scribbleArea->getPenColor());
	if (newColor.isValid()) {		
		scribbleArea->setPenColor(newColor);

	}
}


void MainWindow::createActions()

{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcut(tr("Ctrl+O"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	foreach(QByteArray format, QImageWriter::supportedImageFormats()) {
		QString text = tr("%1...").arg(QString(format).toUpper());

		QAction *action = new QAction(text, this);
		action->setData(format);
		connect(action, SIGNAL(triggered()), this, SLOT(save()));
		saveAsActs.append(action);
	}

	printAct = new QAction(tr("&Print..."), this);
	connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	clearScreenAct = new QAction(tr("&Clear Screen"), this);
	clearScreenAct->setShortcut(tr("Ctrl+L"));
	connect(clearScreenAct, SIGNAL(triggered()),
		scribbleArea, SLOT(clearImage()));

	selectPenColor = new QAction(tr("&Selet Color"), this);
	connect(selectPenColor, SIGNAL(triggered()),
		scribbleArea, SLOT(setPen()));
}



void MainWindow::createMenus()

{
	saveAsMenu = new QMenu(tr("&Save As"), this);
	foreach(QAction *action, saveAsActs)
		saveAsMenu->addAction(action);

	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addMenu(saveAsMenu);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	optionMenu = new QMenu(tr("&Options"), this);
	optionMenu->addAction(clearScreenAct);
	optionMenu->addAction(selectPenColor);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(optionMenu);
    //menuBar()->addMenu(helpMenu);
}



bool MainWindow::maybeSave()

{
	if (scribbleArea->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Scribble"),
			tr("The image has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);
		if (ret == QMessageBox::Save) {
			return saveFile("png");
		}
		else if (ret == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}



bool MainWindow::saveFile(const QByteArray &fileFormat)

{
	QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("%1 Files (*.%2);;All Files (*)")
		.arg(QString::fromLatin1(fileFormat.toUpper()))
		.arg(QString::fromLatin1(fileFormat)));
	if (fileName.isEmpty()) {
		return false;
	}
	else {
		return scribbleArea->saveImage(fileName, fileFormat.constData());
	}
}


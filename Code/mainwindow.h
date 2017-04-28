/* InteractivePaint
 * Daniel Mederos
 * Jim Luoro
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "document.h"
#include <QActionGroup>
#include <QMainWindow>
#include <QUndoStack>

namespace Paint {
class MainWindow : public QMainWindow   //The MainWindow class representing the main application's window
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();

private:
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    QActionGroup brushActionGroup;
    QUndoStack undoStack;
    Document doc;
};

} // namespace Paint

#endif // MAINWINDOW_H

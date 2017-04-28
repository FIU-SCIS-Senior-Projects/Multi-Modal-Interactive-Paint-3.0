/* InteractivePaint
 * Daniel Mederos
 * Jim Luoro
 */

#include "mainwindow.h"
#include "mainwindow2.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QInputDialog>
#include <QString>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
/*
    bool ok;
    QString text = QInputDialog::getText(NULL, "Interactive Paint", "1 for Single   |   2 for Multi", QLineEdit::Normal, QString::null, &ok);
    if ( ok && !text.isEmpty() ) {        
        // user entered something and pressed OK
    } else {
        // user entered nothing or pressed Cancel
    }

    if(text == 1){
    Paint::MainWindow w;
    w.show();
    }

    if(text == 2){
    MainWindow window;
    window.show();
    }
    */

    //Paint::MainWindow w;
   // w.show();

    MainWindow window;
    window.show();

    return app.exec();
}

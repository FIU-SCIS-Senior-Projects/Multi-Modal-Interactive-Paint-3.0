#ifndef GUI_H
#define GUI_H

#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "mainwindow2.h"

class gui: public QMainWindow
{
  Q_OBJECT

  public:
    gui(){}
    ~ gui(){}

    void decorate()
    {

      QPushButton *button = new QPushButton(this);
      QPushButton *button2 = new QPushButton(this);

      button->setText("Single");
      button2->setText("Multi");

      QObject::connect(button, SIGNAL(clicked()),this, SLOT(clickedSlot()));
      QObject::connect(button2, SIGNAL(clicked()),this, SLOT(clickedSlot2()));

      button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
      button2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

      QWidget* centralWidget = new QWidget(this);
      centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

      QHBoxLayout* layout = new QHBoxLayout(centralWidget);

      layout->addWidget(button);
      layout->addWidget(button2);

      setCentralWidget(centralWidget);
      setWindowTitle("Pushbutton Clicked Signal Test");
      show();
    }

   public slots:
     void clickedSlot1()
     {
        //Paint::MainWindow w;
        //w.show();
     }

     void clickedSlot2()
     {
        //MainWindow window;
        //window.show();
     }
};
#endif

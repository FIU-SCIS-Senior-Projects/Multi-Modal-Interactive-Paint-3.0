/****************************************************************************
**
** Jim Louro
**
****************************************************************************/

#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

#include "multiscribblearea.h"
#include "mainwindow2.h"

static const qreal MinimumDiameter = 3.0;
static const qreal MaximumDiameter = 5.0;


ScribbleArea::ScribbleArea(QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_AcceptTouchEvents);
	setAttribute(Qt::WA_StaticContents);
	modified = false;


	
	}
//! [0]
//void ScribbleArea::setPenWidth(int newWidth)
	//{
		//penWidth = newWidth;
	//}

void ScribbleArea::setPenColor(const QColor &newColor)
{
	penColor = newColor;
}

bool ScribbleArea::openImage(const QString &fileName)

{
	QImage loadedImage;
	if (!loadedImage.load(fileName))
		return false;

	QSize newSize = loadedImage.size().expandedTo(size());
	resizeImage(&loadedImage, newSize);
	image = loadedImage;
	modified = false;
	update();
	return true;
}



bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)

{
	QImage visibleImage = image;
	resizeImage(&visibleImage, size());

	if (visibleImage.save(fileName, fileFormat)) {
		modified = false;
		return true;
	}
	else {
		return false;
	}
}


void ScribbleArea::clearImage()

{
	image.fill(qRgb(255, 255, 255));
	modified = true;
	update();
}



void ScribbleArea::paintEvent(QPaintEvent *event)

{
	QPainter painter(this);
	const QRect rect = event->rect();
	painter.drawImage(rect.topLeft(), image, rect);
}



void ScribbleArea::resizeEvent(QResizeEvent *event)

{
	if (width() > image.width() || height() > image.height()) {
		int newWidth = qMax(width() + 128, image.width());
		int newHeight = qMax(height() + 128, image.height());
		resizeImage(&image, QSize(newWidth, newHeight));
		update();
	}
	QWidget::resizeEvent(event);
}



void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)

{
	if (image->size() == newSize)
		return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}



void ScribbleArea::print()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
	QPrinter printer(QPrinter::HighResolution);

	QPrintDialog printDialog(&printer, this);
	
	if (printDialog.exec() == QDialog::Accepted) {
		QPainter painter(&printer);
		QRect rect = painter.viewport();
		QSize size = image.size();
		size.scale(rect.size(), Qt::KeepAspectRatio);
		painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		painter.setWindow(image.rect());
		painter.drawImage(0, 0, image);
	}
#endif // QT_NO_PRINTER
}


bool ScribbleArea::event(QEvent *event)
{
	switch (event->type()) {
	case QEvent::TouchBegin:
	case QEvent::TouchUpdate:
	case QEvent::TouchEnd:
	{
		QTouchEvent *touch = static_cast<QTouchEvent *>(event);
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		foreach(const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
			switch (touchPoint.state()) {
			case Qt::TouchPointStationary:
			case Qt::TouchPointReleased:
				// don't do anything if this touch point hasn't moved or has been released
				continue;
			default:
			{
				QRectF rect = touchPoint.rect();
				if (rect.isEmpty()) {
					qreal diameter = MaximumDiameter;
					if (touch->device()->capabilities() & QTouchDevice::Pressure)
						diameter = MinimumDiameter + (MaximumDiameter - MinimumDiameter) * touchPoint.pressure();
					rect.setSize(QSizeF(diameter, diameter));
				}

				QPainter painter(&image);
				painter.setPen(Qt::NoPen);
				painter.setBrush(penColor);//pencolor.at(touchPoint.id()));
				painter.drawEllipse(rect);
				painter.end();

				modified = true;
				int rad = 2;
				update(rect.toRect().adjusted(-rad, -rad, +rad, +rad));
			}
			break;
			}
		}
		break;
	}
	default:
		return QWidget::event(event);
	}
	return true;
}

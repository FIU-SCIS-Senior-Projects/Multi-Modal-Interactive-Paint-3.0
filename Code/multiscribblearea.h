// Jim Louro

#ifndef MULTISCRIBBLEAREA_H
#define MULTISCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>


class ScribbleArea : public QWidget
{
	Q_OBJECT

public:
	ScribbleArea(QWidget *parent = 0);

	bool openImage(const QString &fileName);
	bool saveImage(const QString &fileName, const char *fileFormat);

	bool isModified() const { return modified; }
	void setPenColor(const QColor &newColor);
	//void setPenWidth(int newWidth);
	QColor getPenColor() const { return penColor; }
	int getPenWidth() const { return penWidth; }

	public slots:
	void clearImage();
	void print();

protected:
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	bool event(QEvent *event) override;

private:
	void resizeImage(QImage *image, const QSize &newSize);
	QWidget *doc;
	bool modified;
	int penWidth;
	QColor penColor;
//	QList<QColor> myPenColors;
	QImage image;
};


#endif

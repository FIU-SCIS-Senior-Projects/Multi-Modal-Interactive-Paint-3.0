/* InteractivePaint
 * Daniel Mederos
 * Jim Luoro
 */

#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <memory>

namespace Paint {
class Document;
class Shape //The Shape base class representing all shapes drawn on the document
{
public:
    Shape(int penWidth, const QColor& penColor);
    virtual ~Shape();
    void draw(QPainter &painter);   //Draw the shape using a painter
    QRect rect() const; //Get the rectangle containing the shape
    void update(const QPoint &toPoint); //Update the shape while "stretching" (drawing) it

protected:
    virtual void doDraw(QPainter &painter) = 0;
    virtual QRect doRect() const = 0;
    virtual void doUpdate(const QPoint &toPoint) = 0;

private:
    int penWidth;
    QColor penColor;
};

std::unique_ptr<Shape> createEllipse(const QPoint &topLeft, int penWidth, const QColor& penColor);
std::unique_ptr<Shape> createEraser(const QPoint &topLeft, int penWidth, const QColor&);
std::unique_ptr<Shape> createFill(Document *doc, const QPoint &topLeft, int penWidth, const QColor&);
std::unique_ptr<Shape> createRectangle(const QPoint &topLeft,  int penWidth, const QColor& penColor);
std::unique_ptr<Shape> createScribble(const QPoint &topLeft, int penWidth, const QColor& penColor);

} // namespace Paint

#endif // SHAPE_H

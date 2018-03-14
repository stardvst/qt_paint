#ifndef CANVAS_H
#define CANVAS_H

#include <QFrame>
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QPixmap>

#include "ObjectsAndStyles.h"

class Canvas : public QFrame
{
	Q_OBJECT

public:
	Canvas(QWidget *parent = nullptr);
	
	// setters
	void setObject(ObjectType type);
	void setVertexCount(int nCount);
	void setPenColor(const QString &sColor);
	void setPenWidth(int nWidth);
	void setPenStyle(Qt::PenStyle style);
	void setBrushColor(const QString &sColor);
	void setBrushStyle(Qt::BrushStyle style);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	// points
	int m_nVertexCount = 10;
	QPoint m_points[10];

	// object, pen & brush
	ObjectType m_eObjectType { ObjectType::LINE };
	QPen m_pen;
	QBrush m_brush;

	//
	QPixmap m_pixmap;
};

#endif

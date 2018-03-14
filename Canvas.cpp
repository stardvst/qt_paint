#include "Canvas.h"

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

#include "Controller.h"

Canvas::Canvas(QWidget *parent /* = nullptr */)
	: QFrame(parent)
{
	setFrameStyle(QFrame::Box | QFrame::Sunken);
	setLineWidth(2);

	m_pixmap = QPixmap(width(), height());
	m_pixmap.fill(Qt::white);
}

void Canvas::paintEvent(QPaintEvent *event)
{
	// scale pixmap to widget's current size
	m_pixmap = m_pixmap.scaled(width(), height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

	QPainter(this).drawPixmap(0, 0, m_pixmap);
	QFrame::paintEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (m_eObjectType != ObjectType::POLYGON)
		m_points[0] = QPoint(event->pos());
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
	QPainter painter(&m_pixmap);
	painter.setPen(m_pen);
	painter.setBrush(m_brush);

	switch (m_eObjectType)
	{
		case ObjectType::LINE:
		{
			auto point2 = QPoint(event->pos());
			painter.drawLine(m_points[0], point2);
			break;
		}
		case ObjectType::RECT:
		{
			auto point1 = m_points[0];
			auto point2 = QPoint(event->pos());
			painter.drawRect(point1.x(), point1.y(),
							 point2.x() - point1.x(),
							 point2.y() - point1.y());
			break;
		}
		case ObjectType::ELLIPSE:
		{
			auto point1 = m_points[0];
			auto point2 = QPoint(event->pos());
			painter.drawEllipse(QPoint(point2.x(), point1.y()),
								point2.x() - point1.x(),
								point2.y() - point1.y());
			break;
		}
		case ObjectType::POLYGON:
		{
			static auto nCurrentVertex = 0;
			
			m_points[nCurrentVertex] = event->pos();
			++nCurrentVertex;

			if (nCurrentVertex == m_nVertexCount)
			{
				painter.drawPolygon(m_points, m_nVertexCount);
				nCurrentVertex = 0;
			}

			break;
		}
	}

	painter.end();

	update();
}

void Canvas::setObject(ObjectType type)
{
	m_eObjectType = type;
}

void Canvas::setVertexCount(int nCount)
{
	m_nVertexCount = nCount;
}

void Canvas::setPenColor(const QString &sColor)
{
	m_pen.setColor(sColor);
}

void Canvas::setPenWidth(int nWidth)
{
	m_pen.setWidth(nWidth);
}

void Canvas::setPenStyle(Qt::PenStyle style)
{
	m_pen.setStyle(style);
}

void Canvas::setBrushColor(const QString &sColor)
{
	m_brush.setColor(sColor);
}

void Canvas::setBrushStyle(Qt::BrushStyle style)
{
	m_brush.setStyle(style);
}
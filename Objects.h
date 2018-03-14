#ifndef OBJECTS_H
#define OBJECTS_H

#include <QFrame>

class QRadioButton;
class RemoveFocusLineEdit;

class Objects : public QFrame
{
	Q_OBJECT

	friend class Controller;

public:
	Objects(QWidget *parent = nullptr);

signals:
	void objectChanged();
	void vertexCountChanged();

private:
	void CreateRadioButtons();

private:
	QRadioButton *m_pLineRadioBtn { nullptr };
	QRadioButton *m_pRectRadioBtn { nullptr };
	QRadioButton *m_pEllipseRadioBtn { nullptr };
	QRadioButton *m_pPolygonRadioBtn { nullptr };
	RemoveFocusLineEdit *m_pVertexLineEdit { nullptr };
};

#endif

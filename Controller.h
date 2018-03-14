#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Canvas;
class Objects;
class Pens;
class Brushes;

enum class ObjectType;

class Controller : public QObject
{
	Q_OBJECT

public:
	Controller(QObject *parent,
			   Canvas *pCanvas,
			   Objects *pObjectOptions,
			   Pens *pPenOptions,
			   Brushes *pBrushOptions);

private slots:
    void onObjectChanged();
    void onVertexCountChanged();
	
	void onPenColorChanged();
	void onPenWidthChanged();
	void onPenStyleChanged();

	void onBrushColorChanged();
	void onBrushStyleChanged();

private:
	Canvas *m_pCanvas { nullptr };
	Objects *m_pObjectOptions { nullptr };
	Pens *m_pPenOptions { nullptr };
	Brushes *m_pBrushOptions { nullptr };
};

#endif

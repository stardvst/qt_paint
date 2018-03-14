#include <QWidget>

#include <memory>

class Controller;
class Canvas;
class Objects;
class Pens;
class Brushes;

enum class ObjectType;
enum class PenStyle;
enum class BrushStyle;

class PaintWindow : public QWidget
{
	Q_OBJECT

public:
	PaintWindow(QWidget *parent = nullptr);

private:
	void CreateWidgets();

private:
	Controller *m_pController;

	Canvas *m_pCanvas;
	Objects *m_pObjectsOptions;
	Pens *m_pPenOptions;
	Brushes *m_pBrushOptions;
};

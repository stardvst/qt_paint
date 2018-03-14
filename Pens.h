#ifndef PENS_H
#define PENS_H

#include <QFrame>

class HexColorLineEdit;
class QSpinBox;
class QComboBox;
enum class PenStyle;

class Pens : public QFrame
{
	Q_OBJECT

	friend class Controller;

public:
	Pens(QWidget *parent = nullptr);

signals:
	void colorChanged() const;
	void widthChanged() const;
	void styleChanged() const;

private:
	void createWidgets();
	void createWidgetLayout();

private:
	HexColorLineEdit *m_pColorLineEdit { nullptr };
	QSpinBox *m_pWidthSpinBox { nullptr };
	QComboBox *m_pStyleComboBox { nullptr };
};

#endif

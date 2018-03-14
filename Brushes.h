#ifndef BRUSHES_H
#define BRUSHES_H

#include <QFrame>
#include <QBrush>

class HexColorLineEdit;
class QComboBox;
enum class BrushStyle;

class Brushes : public QFrame
{
	Q_OBJECT

	friend class Controller;

public:
	Brushes(QWidget *parent = nullptr);

signals:
	void colorChanged() const;
	void styleChanged() const;

private:
	void CreateBrushOptions();

private:
	HexColorLineEdit *m_pColorLineEdit { nullptr };
	QComboBox *m_pStyleComboBox { nullptr };
};

#endif

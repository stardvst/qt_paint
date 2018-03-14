#ifndef REMOVE_FOCUS_LINE_EDIT_H
#define REMOVE_FOCUS_LINE_EDIT_H

#include <QLineEdit>
#include <QRegExpValidator>
#include <QKeyEvent>

class RemoveFocusLineEdit : public QLineEdit
{
public:
	RemoveFocusLineEdit(QWidget *parent = nullptr)
		: QLineEdit(parent)
	{
	}

protected:
	void keyPressEvent(QKeyEvent *event) override
	{
		if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
			clearFocus();
		QLineEdit::keyPressEvent(event);
	}
};

#endif

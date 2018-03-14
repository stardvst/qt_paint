#ifndef HEX_COLOR_LINE_EDIT_H
#define HEX_COLOR_LINE_EDIT_H

#include "RemoveFocusLineEdit.h"

#include <QRegExpValidator>

class HexColorLineEdit : public RemoveFocusLineEdit
{
	Q_OBJECT

public:
	HexColorLineEdit(QWidget *parent = nullptr)
		: RemoveFocusLineEdit(parent)
	{
		QRegExp regexp("^#[\\dA-Fa-f]{0,6}$"); // hex value
		setValidator(new QRegExpValidator(regexp, this));
		setPlaceholderText("Hex code");

		connect(this, &QLineEdit::returnPressed, [this]
		{
			const auto color = text();
			if (color.length() == 7)
			{
				setStyleSheet("border: 1px solid black;");
				emit colorChanged(color);
			}
			else
				setStyleSheet("border: 1px solid red");
		});
	}

signals:
	void colorChanged(const QString &sColor);
};

#endif

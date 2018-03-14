#include "Pens.h"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QEvent>

#include "ObjectsAndStyles.h"
#include "HexColorLineEdit.h"

Pens::Pens(QWidget *parent /* = nullptr */)
	: QFrame(parent)
{
	setFrameStyle(QFrame::StyledPanel);
	setFixedSize(200, 200);

	createWidgets();
	createWidgetLayout();
}

void Pens::createWidgets()
{
	// pen color
	m_pColorLineEdit = new HexColorLineEdit(this);
	m_pColorLineEdit->setText("#ff0000");

	// pen line width
	m_pWidthSpinBox = new QSpinBox(this);
	m_pWidthSpinBox->setRange(1, 16);
	m_pWidthSpinBox->setSuffix(" px");
	m_pWidthSpinBox->setValue(1);

	// pen styles
	m_pStyleComboBox = new QComboBox(this);
	const auto penStyles = QStringList() << "Solid" << "Dashed" << "Dotted" << "Dash-dotted" << "Dash-dot-dotted";
	const auto ids = QList<PenStyle>() << PenStyle::SOLID << PenStyle::DASHED << PenStyle::DOTTED << PenStyle::DASH_DOTTED << PenStyle::DASH_DOT_DOTTED;
	for (auto i = 0; i < penStyles.size(); ++i)
		m_pStyleComboBox->addItem(penStyles[i], static_cast<int>(ids[i]));
	m_pStyleComboBox->setCurrentIndex(0);

	// connections
	connect(m_pColorLineEdit, &HexColorLineEdit::colorChanged, this, &Pens::colorChanged);

	void (QSpinBox::*valueChanged)(int) = &QSpinBox::valueChanged;
	connect(m_pWidthSpinBox, valueChanged, this, &Pens::widthChanged);

	void (QComboBox::*activated)(int) = &QComboBox::activated;
	connect(m_pStyleComboBox, activated, this, &Pens::styleChanged);
}

void Pens::createWidgetLayout()
{
	auto pColorLabel = new QLabel(tr("Color: "), this);
	pColorLabel->setBuddy(m_pColorLineEdit);

	auto pWidthLabel = new QLabel(tr("Width: "), this);
	pWidthLabel->setBuddy(m_pWidthSpinBox);

	auto pStyleLabel = new QLabel(tr("Style: "), this);
	pStyleLabel->setBuddy(m_pColorLineEdit);

	auto pOptionsLayout = new QGridLayout;
	pOptionsLayout->addWidget(pColorLabel, 0, 0);
	pOptionsLayout->addWidget(m_pColorLineEdit, 0, 1);
	pOptionsLayout->addWidget(pWidthLabel, 1, 0);
	pOptionsLayout->addWidget(m_pWidthSpinBox, 1, 1);
	pOptionsLayout->addWidget(pStyleLabel, 2, 0);
	pOptionsLayout->addWidget(m_pStyleComboBox, 2, 1);

	auto pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(new QLabel("Pen Style"));
	pMainLayout->addLayout(pOptionsLayout);
	pMainLayout->addStretch();

	setLayout(pMainLayout);
}
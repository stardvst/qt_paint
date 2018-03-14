#include "Brushes.h"

#include "HexColorLineEdit.h"
#include "ObjectsAndStyles.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

Brushes::Brushes(QWidget *parent /* = nullptr */)
	: QFrame(parent)
{
	setFrameStyle(QFrame::StyledPanel);
	setFixedSize(200, 200);

	CreateBrushOptions();
}

void Brushes::CreateBrushOptions()
{
	// brush color
	m_pColorLineEdit = new HexColorLineEdit(this);
	m_pColorLineEdit->setText("#0000ff");

	// brush styles
	m_pStyleComboBox = new QComboBox(this);
	const auto brushStyles = QStringList() << "Solid" << "Dense" << "Dense1" << "Dense2" << "Dense3" << "Dense4" << "Dense5" << "Dense6" << "Dense7" << "Horizontal" << "Vertical" << "Cross" << "Backward diagonal"
		<< "Forward diagonal" << "Crossing diagonal";
	const auto ids = QList<BrushStyle>() << BrushStyle::SOLID << BrushStyle::DENSE << BrushStyle::DENSE1 <<
		BrushStyle::DENSE2 << BrushStyle::DENSE3 <<	BrushStyle::DENSE4 << BrushStyle::DENSE5 << 
		BrushStyle::DENSE6 << BrushStyle::DENSE7 << BrushStyle::HOR << BrushStyle::VER << 
		BrushStyle::CROSS << BrushStyle::BDIAG << BrushStyle::FDIAG << BrushStyle::DIAG_CROSS;
	for (auto i = 0; i < brushStyles.size(); ++i)
		m_pStyleComboBox->addItem(brushStyles[i], static_cast<int>(ids[i]));
	m_pStyleComboBox->setCurrentIndex(0);

	auto pOptionsLayout = new QGridLayout;
	pOptionsLayout->addWidget(new QLabel("Color: ", this), 0, 0);
	pOptionsLayout->addWidget(m_pColorLineEdit, 0, 1);
	pOptionsLayout->addWidget(new QLabel("Style: ", this), 1, 0);
	pOptionsLayout->addWidget(m_pStyleComboBox, 1, 1);

	auto pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(new QLabel("Brush Style"));
	pMainLayout->addLayout(pOptionsLayout);
	pMainLayout->addStretch();
	setLayout(pMainLayout);

	// connections
	connect(m_pColorLineEdit, &HexColorLineEdit::colorChanged, this, &Brushes::colorChanged);

	void (QComboBox::*activated)(int) = &QComboBox::activated;
	connect(m_pStyleComboBox, activated, this, &Brushes::styleChanged);
}
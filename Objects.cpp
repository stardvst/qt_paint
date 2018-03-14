#include "Objects.h"

#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QRegExpValidator>
#include <QSpacerItem>

#include "ObjectsAndStyles.h"
#include "RemoveFocusLineEdit.h"

Objects::Objects(QWidget *parent /* = nullptr */)
	: QFrame(parent)
{
	CreateRadioButtons();

	setFrameStyle(QFrame::StyledPanel);
	setFixedSize(200, 200);
}

void Objects::CreateRadioButtons()
{
	auto pTitleLabel = new QLabel("Objects", this);

	// create radiobuttons
	m_pLineRadioBtn = new QRadioButton("Line", this);
	m_pLineRadioBtn->setChecked(true);
	m_pRectRadioBtn = new QRadioButton("Rectangle", this);
	m_pEllipseRadioBtn = new QRadioButton("Ellipse", this);
	m_pPolygonRadioBtn = new QRadioButton("Polygon", this);
	
	m_pVertexLineEdit = new RemoveFocusLineEdit(this);
	m_pVertexLineEdit->setPlaceholderText("Vertex count (3-10)");
	m_pVertexLineEdit->setValidator(new QRegExpValidator(QRegExp("^[3-9]|10$"), this));
	m_pVertexLineEdit->setEnabled(m_pPolygonRadioBtn->isChecked());
	connect(m_pVertexLineEdit, &QLineEdit::returnPressed, [this]
	{
		emit vertexCountChanged();
	});

	// setup connections
	connect(m_pLineRadioBtn, &QRadioButton::toggled, this, &Objects::objectChanged);
	connect(m_pRectRadioBtn, &QRadioButton::toggled, this, &Objects::objectChanged);
	connect(m_pEllipseRadioBtn, &QRadioButton::toggled, this, &Objects::objectChanged);
	connect(m_pPolygonRadioBtn, &QRadioButton::toggled, this, &Objects::objectChanged);
	connect(m_pPolygonRadioBtn, &QRadioButton::toggled, [this]
	{
		m_pVertexLineEdit->setEnabled(m_pPolygonRadioBtn->isChecked());
		m_pVertexLineEdit->setFocus(Qt::ActiveWindowFocusReason);		

		/*if (!m_pPolygonRadioBtn->isChecked())
			m_pVertexLineEdit->setPlaceholderText(m_pVertexLineEdit->placeholderText());*/
	});

	// widgets layout
	auto pVertexLayout = new QHBoxLayout;
	pVertexLayout->addSpacerItem(new QSpacerItem(15, 1));
	pVertexLayout->addWidget(m_pVertexLineEdit);

	auto pObjectsLayout = new QVBoxLayout;
	pObjectsLayout->addWidget(pTitleLabel);
	pObjectsLayout->addWidget(m_pLineRadioBtn);
	pObjectsLayout->addWidget(m_pRectRadioBtn);
	pObjectsLayout->addWidget(m_pEllipseRadioBtn);
	pObjectsLayout->addWidget(m_pPolygonRadioBtn);
	pObjectsLayout->addLayout(pVertexLayout);
	pObjectsLayout->addStretch();

	setLayout(pObjectsLayout);
}
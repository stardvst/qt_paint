#include "Paint.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "Canvas.h"
#include "Objects.h"
#include "Pens.h"
#include "Brushes.h"
#include "Controller.h"

PaintWindow::PaintWindow(QWidget *parent /*= nullptr*/)
	: QWidget(parent)
{
	setMinimumSize(1000, 620);

	CreateWidgets();

	m_pController = new Controller(
		this,
		m_pCanvas,
		m_pObjectsOptions,
		m_pPenOptions,
		m_pBrushOptions
	);
}

void PaintWindow::CreateWidgets()
{
	m_pCanvas = new Canvas(this);
	m_pObjectsOptions = new Objects(this);
	m_pPenOptions = new Pens(this);
	m_pBrushOptions = new Brushes(this);

	auto pOptionsLayout = new QVBoxLayout;
	pOptionsLayout->addWidget(m_pObjectsOptions);
	pOptionsLayout->addWidget(m_pPenOptions);
	pOptionsLayout->addWidget(m_pBrushOptions);

	auto pCanvasLabel = new QLabel("Canvas");
	pCanvasLabel->setAlignment(Qt::AlignCenter);
	pCanvasLabel->setStyleSheet("font-size: 20px;");

	auto pCanvasLabelLayout = new QHBoxLayout;
	pCanvasLabelLayout->addWidget(pCanvasLabel);

	auto pCanvasWidgetLayout = new QVBoxLayout;
	pCanvasWidgetLayout->addLayout(pCanvasLabelLayout);
	pCanvasWidgetLayout->addWidget(m_pCanvas);
	pCanvasWidgetLayout->setStretchFactor(m_pCanvas, 1);

	auto pMainLayout = new QHBoxLayout;
	pMainLayout->addLayout(pCanvasWidgetLayout);
	pMainLayout->setStretchFactor(pCanvasWidgetLayout, 1);
	pMainLayout->addLayout(pOptionsLayout);
	pMainLayout->addStretch();

	setLayout(pMainLayout);
}
//
//void PaintWindow::onObjectChanged(ObjectType type)
//{
////	m_pCanvas->setObjectType(type);
//}
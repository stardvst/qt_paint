#include "Controller.h"

#include "Canvas.h"
#include "Objects.h"
#include "Pens.h"
#include "Brushes.h"
#include "HexColorLineEdit.h"

#include <QSpinBox>
#include <QRadioButton>
#include <QComboBox>

Controller::Controller(QObject *parent, Canvas *pCanvas, Objects *pObjectOptions, Pens *pPenOptions, Brushes *pBrushOptions)
	: QObject(parent)
	, m_pCanvas(pCanvas)
	, m_pObjectOptions(pObjectOptions)
	, m_pPenOptions(pPenOptions)
	, m_pBrushOptions(pBrushOptions)
{
	connect(pObjectOptions, &Objects::objectChanged, this, &Controller::onObjectChanged);
	connect(pObjectOptions, &Objects::vertexCountChanged, this, &Controller::onVertexCountChanged);

	connect(pPenOptions, &Pens::colorChanged, this, &Controller::onPenColorChanged);
	connect(pPenOptions, &Pens::widthChanged, this, &Controller::onPenWidthChanged);
	connect(pPenOptions, &Pens::styleChanged, this, &Controller::onPenStyleChanged);

	connect(pBrushOptions, &Brushes::colorChanged, this, &Controller::onBrushColorChanged);
	connect(pBrushOptions, &Brushes::styleChanged, this, &Controller::onBrushStyleChanged);

	// set initial setup
	onObjectChanged();
	onPenColorChanged();
	onPenWidthChanged();
	onPenStyleChanged();
	onBrushColorChanged();
	onBrushStyleChanged();
}

void Controller::onObjectChanged()
{
	if (qobject_cast<Objects *>(sender()) != m_pObjectOptions)
		return;

	if (m_pObjectOptions->m_pLineRadioBtn->isChecked())
		m_pCanvas->setObject(ObjectType::LINE);
	else if (m_pObjectOptions->m_pRectRadioBtn->isChecked())
		m_pCanvas->setObject(ObjectType::RECT);
	else if (m_pObjectOptions->m_pEllipseRadioBtn->isChecked())
		m_pCanvas->setObject(ObjectType::ELLIPSE);
	else
		m_pCanvas->setObject(ObjectType::POLYGON);
}

void Controller::onVertexCountChanged()
{
	m_pCanvas->setVertexCount(m_pObjectOptions->m_pVertexLineEdit->text().toInt());
}

void Controller::onPenColorChanged()
{
	m_pCanvas->setPenColor(m_pPenOptions->m_pColorLineEdit->text());
}

void Controller::onPenWidthChanged()
{
	m_pCanvas->setPenWidth(m_pPenOptions->m_pWidthSpinBox->value());
}

void Controller::onPenStyleChanged()
{
	m_pCanvas->setPenStyle(Qt::PenStyle(
		m_pPenOptions->m_pStyleComboBox->itemData(
			m_pPenOptions->m_pStyleComboBox->currentIndex()).toInt() + 1)); // 0 is NoPen
}

void Controller::onBrushColorChanged()
{
	m_pCanvas->setBrushColor(m_pBrushOptions->m_pColorLineEdit->text());
}

void Controller::onBrushStyleChanged()
{
	m_pCanvas->setBrushStyle(Qt::BrushStyle(
		m_pBrushOptions->m_pStyleComboBox->itemData(
			m_pBrushOptions->m_pStyleComboBox->currentIndex()).toInt() + 1)); // 0 is NoBrush
}
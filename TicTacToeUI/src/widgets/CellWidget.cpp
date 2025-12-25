#include "include/widgets/CellWidget.h"
#include <QFont>

CellWidget::CellWidget(uint8_t row, uint8_t column, QWidget* parent) :
	QPushButton{ parent }, m_row{ row }, m_column{ column }, m_symbol{}
{
	connect(this, &QPushButton::clicked, this, &CellWidget::OnClicked);
	ApplyStyle();
	UpdateDisplay();
}

uint8_t CellWidget::GetRow() const
{
	return m_row;
}

uint8_t CellWidget::GetColumn() const
{
	return m_column;
}

void CellWidget::SetState(std::optional<Symbol> state)
{
	m_symbol = state;
	UpdateDisplay();
}

void CellWidget::Reset()
{
	m_symbol.reset();
	setEnabled(true);
	UpdateDisplay();
}

void CellWidget::OnClicked()
{
	emit CellClicked(m_row, m_column);
}

void CellWidget::UpdateDisplay()
{
	if (!m_symbol.has_value())
	{
		setText("");
		setEnabled(true);
	}
	else
	{
		setText(m_symbol.value() == Symbol::X ? "X" : "O");
		setEnabled(false);
	}
}

void CellWidget::ApplyStyle()
{
	setFixedSize(100, 100);

	QFont font = this->font();
	font.setPointSize(32);
	font.setBold(true);
	setFont(font);

	setStyleSheet(
		"QPushButton {"
		"   background-color: #ffffff;"
		"   border: 2px solid #333333;"
		"   border-radius: 8px;"
		"   color: #333333;"
		"}"
		"QPushButton:hover:enabled {"
		"   background-color: #e8f4f8;"
		"   border: 2px solid #2196F3;"
		"}"
		"QPushButton:pressed:enabled {"
		"   background-color: #bbdefb;"
		"}"
		"QPushButton:disabled {"
		"   background-color: #f5f5f5;"
		"   color: #333333;"
		"}"
	);
}
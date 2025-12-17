#pragma once

#include <QPushButton>
#include <optional>
#include "Game.h"

using namespace tictactoe;

class CellWidget : public QPushButton
{
	Q_OBJECT

public:
	explicit CellWidget(uint8_t row, uint8_t column, QWidget* parent = nullptr);
	~CellWidget() = default;

	uint8_t GetRow() const;
	uint8_t GetColumn() const;

	void SetState(std::optional<Symbol> state);
	void Reset();

signals:
	void CellClicked(uint8_t row, uint8_t column);

private slots:
	void OnClicked();

private:
	uint8_t m_row;
	uint8_t m_column;
	std::optional<Symbol> m_symbol;

	void UpdateDisplay();
	void ApplyStyle();
};
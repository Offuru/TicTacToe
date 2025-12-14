#pragma once

#include <QWidget>
#include <QGridLayout>
#include <array>
#include "CellWidget.h"
#include "GameViewModel.h"

class BoardWidget : public QWidget
{
	Q_OBJECT

public:
	explicit BoardWidget(GameViewModel* viewModel, QWidget* parent = nullptr);
	~BoardWidget() = default;

	void ResetBoard();

private slots:
	void OnCellClicked(uint8_t row, uint8_t column);
	void OnCellChanged(uint8_t row, uint8_t column, std::optional<Symbol> symbol);
	void OnGameStateChanged(GameState newState);
	void OnGameReset();

private:
	GameViewModel* m_viewModel;
	QGridLayout* m_layout;
	std::array<std::array<CellWidget*, 3>, 3> m_cells;

	void CreateCells();
	void ConnectSignals();
	void DisableAllCells();
	void EnableEmptyCells();
};
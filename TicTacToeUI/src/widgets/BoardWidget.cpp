#include "include/widgets/BoardWidget.h"

BoardWidget::BoardWidget(GameViewModel* viewModel, QWidget* parent)
	: QWidget(parent)
	, m_viewModel(viewModel)
	, m_layout(new QGridLayout(this))
{
	m_layout->setSpacing(5);
	m_layout->setContentsMargins(10, 10, 10, 10);

	CreateCells();
	ConnectSignals();

	setLayout(m_layout);
}

void BoardWidget::CreateCells()
{
	for (uint8_t row = 0; row < 3; ++row)
	{
		for (uint8_t col = 0; col < 3; ++col)
		{
			CellWidget* cell = new CellWidget(row, col, this);
			m_cells[row][col] = cell;
			m_layout->addWidget(cell, row, col);

			connect(cell, &CellWidget::CellClicked,
				this, &BoardWidget::OnCellClicked);
		}
	}
}

void BoardWidget::ConnectSignals()
{
	connect(m_viewModel, &GameViewModel::CellChanged,
		this, &BoardWidget::OnCellChanged);

	connect(m_viewModel, &GameViewModel::GameStateChanged,
		this, &BoardWidget::OnGameStateChanged);

	connect(m_viewModel, &GameViewModel::GameReset,
		this, &BoardWidget::OnGameReset);
}

void BoardWidget::ResetBoard()
{
	for (uint8_t row = 0; row < 3; ++row)
	{
		for (uint8_t col = 0; col < 3; ++col)
		{
			m_cells[row][col]->Reset();
		}
	}
}

void BoardWidget::OnCellClicked(uint8_t row, uint8_t column)
{
	m_viewModel->PlayMove(row, column);
}

void BoardWidget::OnCellChanged(uint8_t row, uint8_t column, std::optional<Symbol> symbol)
{
	m_cells[row][column]->SetState(symbol);
}

void BoardWidget::OnGameStateChanged(GameState newState)
{
	if (newState != GameState::WaitingForMove)
	{
		DisableAllCells();
	}
}

void BoardWidget::OnGameReset()
{
	ResetBoard();
}

void BoardWidget::DisableAllCells()
{
	for (uint8_t row = 0; row < 3; ++row)
	{
		for (uint8_t col = 0; col < 3; ++col)
		{
			m_cells[row][col]->setEnabled(false);
		}
	}
}

void BoardWidget::EnableEmptyCells()
{
	for (uint8_t row = 0; row < 3; ++row)
	{
		for (uint8_t col = 0; col < 3; ++col)
		{
			auto state = m_viewModel->GetCellState(row, col);
			m_cells[row][col]->setEnabled(!state.has_value());
		}
	}
}
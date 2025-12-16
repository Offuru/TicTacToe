//module board;
#include "include/Board.h"

#include <sstream>
#include <algorithm>

namespace tictactoe
{
	std::string CellStateToString(std::optional<Symbol> state)
	{
		if (!state.has_value())
			return "_";

		switch (state.value())
		{
		case tictactoe::Symbol::O:
			return "O";
		case tictactoe::Symbol::X:
			return "X";
		default:
			return "_";
		}
	}

	std::ostream& operator<<(std::ostream& os, const Board& board)
	{
		os << board.ToString();

		return os;
	}

	const std::optional<Symbol>& Board::operator[](const Position& pos) const
	{
		return const_cast<std::optional<Symbol>&>(std::as_const(*this)[pos]);
	}

	std::optional<Symbol>& Board::operator[](const Position& pos)
	{
		return m_grid[pos.first][pos.second];
	}

	bool Board::IsFull() const
	{
		return std::all_of(
			m_grid.begin(),
			m_grid.end(),
			[](const auto& row) -> bool
			{
				return std::all_of(
					row.begin(),
					row.end(),
					[](const auto& cell) -> bool
					{
						return cell.has_value();
					}
				);
			}
		);
	}
	std::string Board::ToString() const
	{
		std::ostringstream line{};

		for (const auto& row : m_grid)
		{
			for (const auto& cell : row)
				line << CellStateToString(cell) << " ";
			line << "\n";
		}

		return line.str();
	}
	std::optional<Symbol> Board::CheckWinner() const
	{
		for (uint8_t i = 0; i < 3; ++i)
		{
			if (const auto& rowWinner = CheckRow(i); rowWinner.has_value())
				return rowWinner;
			if (const auto& columnWinner = CheckColumn(i); columnWinner.has_value())
				return columnWinner;
		}

		if (const auto& diagonalWinner = CheckDiagonals(); diagonalWinner.has_value())
			return diagonalWinner;

		return {};
	}

	std::optional<Symbol> Board::CheckRow(uint8_t row) const
	{
		const auto& cell = m_grid[row][0];

		return std::all_of(
			m_grid[row].begin(),
			m_grid[row].end(),
			[&cell](const auto& otherCell) -> bool
			{
				return otherCell == cell;
			}
		) ? cell : std::optional<Symbol>{};
	}

	std::optional<Symbol> Board::CheckColumn(uint8_t column) const
	{
		const auto& cell = m_grid[0][column];
		return std::all_of(
			m_grid.begin(),
			m_grid.end(),
			[&cell, column](const auto& row) -> bool
			{
				return row[column] == cell;
			}
		) ? cell : std::optional<Symbol>{};
	}
	std::optional<Symbol> Board::CheckDiagonals() const
	{
		const auto& centerCell = m_grid[1][1];
		if (centerCell.has_value())
		{
			if (std::all_of(
				m_grid.begin(),
				m_grid.end(),
				[&centerCell, n = 0](const auto& row) mutable -> bool
				{
					return row[n++] == centerCell;
				}
			))
				return centerCell;
			if (std::all_of(
				m_grid.begin(),
				m_grid.end(),
				[&centerCell, n = 2](const auto& row) mutable -> bool
				{
					return row[n--] == centerCell;
				}
			))
				return centerCell;
		}
		return {};
	}
}
export module board;

import std;

namespace tictactoe
{
	using std::uint8_t;
	export using Position = std::pair<uint8_t, uint8_t>;

	export enum class Symbol : uint8_t
	{
		X,
		O,
	};

	export std::string CellStateToString(std::optional<Symbol> state);

	export class Board
	{
	public:
		const std::optional<Symbol>& operator[](const Position& pos) const;
		std::optional<Symbol>& operator[](const Position& pos);

		bool IsFull() const;
		std::string ToString() const;

		std::optional<Symbol> CheckWinner() const;

		friend std::ostream& operator<<(std::ostream& os, const Board& board);
	private:
		std::optional<Symbol> CheckRow(uint8_t row) const;
		std::optional<Symbol> CheckColumn(uint8_t column) const;
		std::optional<Symbol> CheckDiagonals() const;

		std::array<std::array<std::optional<Symbol>, 3>, 3> m_grid;
	};

	export using BoardPtr = std::unique_ptr<Board>;
	export using BoardRef = std::reference_wrapper<Board>;
}
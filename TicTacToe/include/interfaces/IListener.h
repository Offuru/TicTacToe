#pragma once

#include <optional>

#include "../ForwardDeclarations.h"

namespace tictactoe
{
	class IListener
	{
	public:
		virtual ~IListener() = default;

		virtual void OnCellChanged(const Position& pos, std::optional<Symbol> newState) = 0;
		virtual void OnCurrentPlayerChanged(Symbol newPlayer) = 0;
		virtual void OnGameStateChanged(GameState newState) = 0;
		virtual void OnGameReset() = 0;
	};
}
#pragma once
#include <memory>
#include <cstdint>
#include <vector>

namespace tictactoe
{
	class Game;
	class Board;
	class IListener;

	struct GameData;

	enum class Symbol : uint8_t;
	enum class GameState : uint8_t;

	using IListenerWeakPtr = IListener*; 
	using Position = std::pair<uint8_t, uint8_t>;
	using BoardPtr = std::unique_ptr<Board>;
	using BoardRef = std::reference_wrapper<Board>;
	using GameDataRef = std::reference_wrapper<GameData>;
	using GameDataConstRef = std::reference_wrapper<const GameData>;
	using ListenerVector = std::vector<IListenerWeakPtr>;
}
#pragma once

#include <QObject>
#include <QString>
#include "Game.h"

using namespace tictactoe;

class GameViewModel : public QObject
{
	Q_OBJECT

public:
	explicit GameViewModel(QObject* parent = nullptr);
	~GameViewModel() = default;

	QString GetCurrentPlayerString() const;
	Symbol GetCurrentPlayer() const;
	GameState GetGameState() const;
	QString GetGameStateString() const;
	std::optional<Symbol> GetCellState(uint8_t row, uint8_t column) const;
	bool IsGameOver() const;

	bool PlayMove(uint8_t row, uint8_t column);
	void ResetGame();

signals:
	void GameStateChanged(GameState newState);
	void CurrentPlayerChanged(Symbol newPlayer);
	void CellChanged(uint8_t row, uint8_t column, std::optional<Symbol> newState);
	void GameReset();

private:
	std::unique_ptr<Game> m_game;

	void NotifyCellChanged(uint8_t row, uint8_t column);
	void NotifyAllCellsChanged();
};
#pragma once

#include <QObject>
#include <QString>
#include "Game.h"
#include "interfaces/IListener.h"

using namespace tictactoe;

class GameViewModel : public QObject, public IListener
{
	Q_OBJECT

public:
	explicit GameViewModel(QObject* parent = nullptr);
	~GameViewModel();

	QString GetCurrentPlayerString() const;
	Symbol GetCurrentPlayer() const;
	GameState GetGameState() const;
	QString GetGameStateString() const;
	std::optional<Symbol> GetCellState(uint8_t row, uint8_t column) const;
	bool IsGameOver() const;

	bool PlayMove(uint8_t row, uint8_t column);
	void ResetGame();

	void OnCellChanged(const Position& pos, std::optional<Symbol> newState) override;
	void OnCurrentPlayerChanged(Symbol newPlayer) override;
	void OnGameStateChanged(GameState newState) override;
	void OnGameReset() override;

signals:
	void GameStateChanged(GameState newState);
	void CurrentPlayerChanged(Symbol newPlayer);
	void CellChanged(uint8_t row, uint8_t column, std::optional<Symbol> newState);
	void GameReset();

private:
	std::unique_ptr<Game> m_game;
};
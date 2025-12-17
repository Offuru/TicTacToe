//import board;
//import game;
//
//import std;

//#include "include/Game.h"
//
//#include <print>
//#include <iostream>
//
//int main()
//{
//	using namespace tictactoe;
//
//	Game game{};
//
//	while (game.GetData().get().m_state == GameState::WaitingForMove)
//	{
//		system("cls");
//
//		std::println("{}", game.GetData().get().m_board->ToString());
//
//		int row{}, column{};
//
//		std::println("Player {}, enter your move (row and column): ", ((game.GetData().get().currentPlayer == Symbol::X) ? "X" : "O"));
//
//		std::cin >> row >> column;
//
//		while (!game.PlayMove({ row, column }))
//		{
//			std::println("Invalid move. Try again.");
//			std::cin >> row >> column;
//		}
//	}
//
//	system("cls");
//	std::println("Game Over!");
//	std::println("{}", game.GetData().get().m_board->ToString());
//	std::println("Result: {}", (game.GetData().get().m_state == GameState::Draw) ? "Draw" : (game.GetData().get().m_state == GameState::XWins) ? "X wins" : "O wins");
//
//	return 0;
//}
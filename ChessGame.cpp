#include "ChessGame.h"

ChessGame::ChessGame() {
	setTurn(true);
	setWinner(0);
}

void ChessGame::runGame(void) {
	RenderWindow window(VideoMode(1024, 1024), "C++ Chess", Style::Close | Style::Titlebar);

	Board gameboard;
	gameboard.setBoard(window);

	int currentXCoord = 0;
	int currentYCoord = 0;

	setTurn(true); //setting starting turn to white

	
	while (window.isOpen()) {

		gameboard.renderBoard(window);
		gameboard.drawCurrentBoard(window);

		window.display();

		Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::TextEntered:
				if (evnt.text.unicode < 128) {
					printf("%c", evnt.text.unicode);
				}
				gameboard.movePiece(0, 0, 2, 4);
				break;
			case Event::MouseButtonPressed:
				if ((evnt.mouseButton.x >= 0 && evnt.mouseButton.x <= 1024) && (evnt.mouseButton.y >= 0 && evnt.mouseButton.y <= 1024)) {
					currentXCoord = evnt.mouseButton.x / 128;
					currentYCoord = evnt.mouseButton.y / 128;
					Piece* currentPiece = gameboard.getBoardPtr(currentXCoord, currentYCoord);

					//Selecting phase
					if ((getPieceSelected() == nullptr && currentPiece != nullptr)) {
						if (currentPiece->getPlayer() == getTurn()) {
							setPieceSelected(currentPiece);
							std::cout << "Piece Selected" << std::endl;
						}
						else {
							cout << "Wrong Turn!" << endl;
						}

					}
					//Movement phase
					else if (getPieceSelected() != nullptr) {
						Piece* selectedPiece = getPieceSelected();
						if (gameboard.checkMove(selectedPiece->getX(), selectedPiece->getY(), currentXCoord, currentYCoord)) {
							gameboard.movePiece(selectedPiece->getX(), selectedPiece->getY(), currentXCoord, currentYCoord);
							setTurn(!getTurn()); //alternating turn
							if (currentPiece != nullptr) {
								if (currentPiece->getType() == 'k') {
									//game won
									if (selectedPiece->getPlayer()) { //white wins
										setWinner(1);
										cout << "White Wins" << endl;
										//window.close();
										return;
									}
									else { //black wins
										setWinner(2);
										cout << "Black Wins" << endl;
										//window.close();
										return;
									}
								}
							}
							
						}
						else {
							cout << "Invalid Move" << endl;
						}
						setPieceSelected(nullptr);
					}
					else if (getPieceSelected() == currentPiece) {
						setPieceSelected(nullptr);
					}
					
				}
					break;
				}
			}		
	}
}

void ChessGame::setPieceSelected(Piece* newPiece) {
	pieceSelected = newPiece;
}

void ChessGame::setTurn(bool tf) {
	turn = tf;
}

void ChessGame::setWinner(int val) {
	winner = val;
}

Piece* ChessGame::getPieceSelected() {
	return pieceSelected;
}

bool ChessGame::getTurn() {
	return turn;
}

int ChessGame::getWinner() {
	return winner;
}


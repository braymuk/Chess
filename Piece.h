#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using std::cout;
using std::endl;

class Piece : public Sprite{
public:
	Piece();
	Piece(int xCoord, int yCoord, char pieceType, bool player);

	Piece(const Piece& p);
	Piece& operator = (const Piece& p);

	

	
	void setX(int val);
	void setY(int val);
	void setType(char val);
	void setPlayer(bool val);
	void setHasMoved(bool tf);

	int getX(void);
	int getY(void);
	char getType(void);
	bool getPlayer(void);
	bool getHasMoved(void);

	void addTexture(char pieceType, bool player);

	void draw(sf::RenderWindow& window);

private:
	int xCoord;
	int yCoord;
	char pieceType; //p = pawn, h = knight, b = bishop, r = rook, q = queen, k = king
	bool player; //white == true, black == false
	bool hasMoved;
	Texture texture;
};
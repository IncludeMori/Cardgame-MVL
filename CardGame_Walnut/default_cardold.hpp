//
// @Author: Moritz Volkenandt (2017-)
//
//
#pragma once

#include "CardTexture.hpp"
#include <string>
#include "gMouse.hpp"

class Default_Card
{
public:
	Default_Card();
	Default_Card(int Health, int Attack,int Type,std::string path);
	~Default_Card();

	void update();
	void render();

	void loadTexture();
	void move(int x, int y);
	

	bool isEmpty();

	void setActive();
	void setInactive();
	bool isActive();

	std::string getName();
	int getHealth();
	int getAttack();

	void free();

protected:

	CardTexture mCard;

	bool mEmpty;
	bool mActive;

	std::string mName;
	std::string mPath;
	int mType;
	int mHealth;
	int mAttack;

};
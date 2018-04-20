//
// @Author: Moritz Volkenandt (2017-)
//
// Used for: render card-> health, atk, cost
//
#pragma once

#include "HeroHealth.hpp"

enum class Stats_Size {
	STANDARD = 0,
	HOVER = 1
};

class StatsSign : public HeroHealth
{
public:
	StatsSign();
	StatsSign(Stats_Size size, std::shared_ptr<SDL_Texture> texture = nullptr,int width = 0,int height = 0);

	void move(int x, int y);

	void setup(std::shared_ptr<SDL_Texture> texture = nullptr, int width = 0, int height = 0) { setTexture(texture); };

private:
	std::shared_ptr<SDL_Texture> mTexture = nullptr;

	void setTexture(const std::shared_ptr<SDL_Texture> &texture) {
		mTexture = texture;
	};
	SDL_Texture* getTexture() override { return mTexture.get(); };

};
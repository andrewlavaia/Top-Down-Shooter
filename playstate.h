
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include "level.h"
#include "hero.h"
#include "resourceholder.h"
#include "animation.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CPlayState* Instance() {
		return &PlayState;
	}

  bool noKeyPressed;

protected:
	CPlayState()
	{
    fonts.load(Fonts::Calibri, "calibri.ttf");

    textures.load(Textures::Empty, "1x1_empty_texture.png");
    textures.load(Textures::Hitbox, "hitbox_texture.png");
    textures.load(Textures::Hero_Run, "hero_run.png");
    textures.load(Textures::Hero_Grab, "hero_grab.png");
    textures.load(Textures::Hero_Punch, "hero_punch.png");
    textures.load(Textures::Hero_Kick, "hero_kick.png");
    textures.load(Textures::NPC_Texture, "zombie.png");

    animations.load(Animations::Empty, textures.get(Textures::Empty), 1, 1, 1);
    animations.load(Animations::Hero_Run, textures.get(Textures::Hero_Run), 391, 319, 12);
    animations.load(Animations::Hero_Grab, textures.get(Textures::Hero_Grab), 388, 319, 6);
    animations.load(Animations::Hero_Punch, textures.get(Textures::Hero_Punch), 398, 279, 6);
    animations.load(Animations::Hero_Kick, textures.get(Textures::Hero_Kick), 385, 371, 6);
    animations.load(Animations::NPC_Run, textures.get(Textures::NPC_Texture), 49, 50, 8);

    hero = std::make_shared<Hero>(animations);
	  level = std::make_shared<Level>(1, animations);

    HUD_timer.setFont(fonts.get(Fonts::Calibri));
    HUD_timer.setCharacterSize(40);
    HUD_timer.setColor(sf::Color::Black);
    HUD_timer.setPosition(400,20);

    HUD_npc_count.setFont(fonts.get(Fonts::Calibri));
    HUD_npc_count.setCharacterSize(40);
    HUD_npc_count.setColor(sf::Color::Black);
    HUD_npc_count.setPosition(700,20);
  }

private:
	static CPlayState PlayState;

  ResourceHolder<sf::Font, Fonts::ID> fonts;
  ResourceHolder<sf::Texture, Textures::ID> textures;
  ResourceHolder<Animation, Animations::ID> animations;

  std::shared_ptr<Hero> hero;
	std::shared_ptr<Level> level;

	sf::Text HUD_timer;
	sf::Text HUD_npc_count;


};

#endif

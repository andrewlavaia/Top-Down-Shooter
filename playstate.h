
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "timer.h"
#include <math.h> // sqrt
#include "helpers.h" // to_string

#include "animatedsprite.h"
#include "animation.h"
#include "animatedentity.h"

#include "collision.h"
#include "orientation.h"
#include "attack.h"

#include "resourceholder.h"
#include "datatables.h"
#include "hero.h"
#include "npc.h"
#include "collidable.h"
#include "projectile.h"
#include "weapon.h"
#include "mapmanager.h"
#include "level.h"

class CPlayState : public CGameState
{
public:
	void Init(CGameEngine* game);
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

    textures.load(Textures::Empty, "textures/1x1_empty_texture.png");
    textures.load(Textures::Hitbox, "textures/hitbox_texture.png");
    textures.load(Textures::Human_1_SpriteSheet, "textures/human1.png");
    textures.load(Textures::Human_2_SpriteSheet, "textures/human2.png");
    textures.load(Textures::Human_3_SpriteSheet, "textures/human3.png");
    textures.load(Textures::Human_4_SpriteSheet, "textures/human4.png");
    textures.load(Textures::Human_5_SpriteSheet, "textures/human5.png");
    textures.load(Textures::Human_6_SpriteSheet, "textures/human6.png");
    textures.load(Textures::Human_7_SpriteSheet, "textures/human7.png");
    textures.load(Textures::Human_8_SpriteSheet, "textures/human8.png");
    textures.load(Textures::Human_9_SpriteSheet, "textures/human9.png");
    textures.load(Textures::Human_10_SpriteSheet, "textures/human10.png");
    textures.load(Textures::Human_11_SpriteSheet, "textures/human11.png");
    textures.load(Textures::Human_12_SpriteSheet, "textures/human12.png");
    textures.load(Textures::Human_13_SpriteSheet, "textures/human13.png");
    textures.load(Textures::Hero_Idle, "human1-idle.png");
    textures.load(Textures::Hero_Walk, "human1-walk.png");
    textures.load(Textures::Hero_Run, "human1-run.png");
    textures.load(Textures::Hero_Attacked, "human1-attacked.png");
    textures.load(Textures::Hero_Die, "human1-die.png");
    textures.load(Textures::Hero_Dead, "human1-dead.png");
    textures.load(Textures::Hero_Grab, "hero_grab.png");
    textures.load(Textures::Hero_Punch, "hero_punch.png");
    textures.load(Textures::Hero_Kick, "hero_kick.png");
    textures.load(Textures::NPC_Texture, "zombie.png");
    textures.load(Textures::Pistol, "pistol_texture2.png");
    textures.load(Textures::Rifle, "textures/rifle.png");
    textures.load(Textures::Shotgun, "textures/shotgun.png");
    textures.load(Textures::SMG, "textures/smg.png");
    textures.load(Textures::Bullet, "bullet.png");
    textures.load(Textures::Grass, "grass.jpg");
    textures.load(Textures::Dungeon, "dungeon.png");

    animations.load( Animations::Empty, textures.get( Textures::Empty ), 1, 1, 1 );
    animations.load( Animations::Hitbox, textures.get( Textures::Hitbox ), 1, 1, 1 );

    animations.load( Animations::Human_1_Idle, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_1_Walk, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_1_Run, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_1_Grab, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_1_Attacked, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_1_Die, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_1_Dead, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_2_Idle, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_2_Walk, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_2_Run, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_2_Grab, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_2_Attacked, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_2_Die, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_2_Dead, textures.get( Textures::Human_2_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_3_Idle, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_3_Walk, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_3_Run, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_3_Grab, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_3_Attacked, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_3_Die, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_3_Dead, textures.get( Textures::Human_3_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

/*
    animations.load( Animations::Hero_Idle, textures.get( Textures::Human_1_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Hero_Walk, textures.get(Textures::Hero_Walk), 20, 20, 8);
    animations.load(Animations::Hero_Run, textures.get(Textures::Hero_Run), 20, 20, 6);
    animations.load(Animations::Hero_Attacked, textures.get(Textures::Hero_Attacked), 20, 20, 4);
    animations.load(Animations::Hero_Die, textures.get(Textures::Hero_Die), 20, 20, 6);
    animations.load(Animations::Hero_Dead, textures.get(Textures::Hero_Dead), 20, 20, 1);
    animations.load(Animations::Hero_Grab, textures.get(Textures::Hero_Grab), 388, 319, 6);
*/
    animations.load(Animations::Hero_Punch, textures.get(Textures::Hero_Punch), 398, 279, 6);
    animations.load(Animations::Hero_Kick, textures.get(Textures::Hero_Kick), 385, 371, 6);

    //animations.load(Animations::NPC_Run, textures.get(Textures::NPC_Texture), 49, 50, 8);
    animations.load(Animations::Pistol, textures.get(Textures::Pistol), 48, 48, 1);
    animations.load(Animations::Rifle, textures.get(Textures::Rifle), 11, 31, 1);
    animations.load(Animations::Shotgun, textures.get(Textures::Shotgun), 13, 27, 1);
    animations.load(Animations::SMG, textures.get(Textures::SMG), 12, 25, 1);
    animations.load(Animations::Bullet, textures.get(Textures::Bullet), 10, 10, 1);
    animations.load(Animations::Grass, textures.get(Textures::Grass), 1024, 1024, 1);

    hero = std::make_shared<Hero>(Hero::Bob, animations, data);
	  level = std::make_shared<Level>(1, animations, data);

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

  DataTable data;

  std::shared_ptr<Hero> hero;
	std::shared_ptr<Level> level;

	sf::Text HUD_timer;
	sf::Text HUD_npc_count;

};

#endif

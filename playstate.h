
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
#include "hero.h"

#include "collidable.h"
#include "projectile.h"
#include "weapon.h"
#include "npc.h"
#include "datatables.h"
#include "mapmanager.h"
#include "level.h"

#include "charselectstate.h" // needed for CCharSelectState::Instance()->getSelectedHero()

class CPlayState : public CGameState
{
public:
	void Init(CGameEngine* game);
	void Cleanup();

	void Pause(CGameEngine* game);
	void Resume(CGameEngine* game);

	void HandleEvents(CGameEngine* game);
	void Update(CGameEngine* game);
	void Draw(CGameEngine* game, double interpolation);

	static CPlayState* Instance() {
		return &PlayState;
	}

  bool noKeyPressed;

protected:
	CPlayState() :
    game_time(sf::Time::Zero),
    keyboard_delay(sf::Time::Zero)
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
    textures.load(Textures::Sheep_SpriteSheet, "textures/sheep.png");

    textures.load(Textures::Pistol, "pistol_texture2.png");
    textures.load(Textures::Rifle, "textures/rifle.png");
    textures.load(Textures::Shotgun, "textures/shotgun.png");
    textures.load(Textures::SMG, "textures/smg.png");
    textures.load(Textures::RocketLauncher, "textures/rocketlauncher.png");
    textures.load(Textures::Bullet, "bullet.png");
    textures.load(Textures::Spear, "textures/spear.png");
    textures.load(Textures::Spear_Thrust, "textures/spear_thrust.png");

    textures.load(Textures::Dungeon, "dungeon.png");
    textures.load(Textures::Crosshair, "textures/crosshair.png");
    textures.load(Textures::Grass, "textures/grass_texture.png");

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

    animations.load( Animations::Human_4_Idle, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_4_Walk, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_4_Run, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_4_Grab, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_4_Attacked, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_4_Die, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_4_Dead, textures.get( Textures::Human_4_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_5_Idle, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_5_Walk, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_5_Run, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_5_Grab, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_5_Attacked, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_5_Die, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_5_Dead, textures.get( Textures::Human_5_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_6_Idle, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_6_Walk, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_6_Run, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_6_Grab, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_6_Attacked, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_6_Die, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_6_Dead, textures.get( Textures::Human_6_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_7_Idle, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_7_Walk, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_7_Run, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_7_Grab, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_7_Attacked, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_7_Die, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_7_Dead, textures.get( Textures::Human_7_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_8_Idle, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_8_Walk, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_8_Run, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_8_Grab, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_8_Attacked, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_8_Die, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_8_Dead, textures.get( Textures::Human_8_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_9_Idle, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_9_Walk, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_9_Run, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_9_Grab, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_9_Attacked, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_9_Die, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_9_Dead, textures.get( Textures::Human_9_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_10_Idle, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_10_Walk, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_10_Run, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_10_Grab, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_10_Attacked, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_10_Die, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_10_Dead, textures.get( Textures::Human_10_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_11_Idle, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_11_Walk, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_11_Run, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_11_Grab, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_11_Attacked, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_11_Die, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_11_Dead, textures.get( Textures::Human_11_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_12_Idle, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_12_Walk, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_12_Run, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_12_Grab, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_12_Attacked, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_12_Die, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_12_Dead, textures.get( Textures::Human_12_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Human_13_Idle, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {1,1,1,2,2} );
    animations.load( Animations::Human_13_Walk, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {3,4,5,6,7,8,9,10} );
    animations.load( Animations::Human_13_Run, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {17,18,19,21,21,22} );
    animations.load( Animations::Human_13_Grab, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {7,8,8,2} );
    animations.load( Animations::Human_13_Attacked, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {23,23,23,24,2,1} );
    animations.load( Animations::Human_13_Die, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {2,24,23,33,14,35} );
    animations.load( Animations::Human_13_Dead, textures.get( Textures::Human_13_SpriteSheet ), 20, 20, 5, 7, {35} ); // frame 6 rotated and moved down

    animations.load( Animations::Sheep_Idle, textures.get( Textures::Sheep_SpriteSheet ), 50, 40, 4, 1, {4,3,2,1} );
    animations.load( Animations::Sheep_Walk, textures.get( Textures::Sheep_SpriteSheet ), 50, 40, 4, 1, {4,3,2,1} );
    animations.load( Animations::Sheep_Attacked, textures.get( Textures::Sheep_SpriteSheet ), 50, 40, 4, 1, {4,3,2,1} );
    animations.load( Animations::Sheep_Die, textures.get( Textures::Sheep_SpriteSheet ), 50, 40, 4, 1, {4,3,2,1} );
    animations.load( Animations::Sheep_Dead, textures.get( Textures::Sheep_SpriteSheet ), 50, 40, 4, 1, {4,3,2,1} );

    // Weapon animations
    animations.load(Animations::Pistol, textures.get(Textures::Pistol), 24, 24, 1);
    animations.load(Animations::Rifle, textures.get(Textures::Rifle), 11, 31, 1);
    animations.load(Animations::Shotgun, textures.get(Textures::Shotgun), 13, 27, 1);
    animations.load(Animations::SMG, textures.get(Textures::SMG), 12, 25, 1);
    animations.load(Animations::RocketLauncher_Idle, textures.get(Textures::RocketLauncher), 11, 31, 1);
    animations.load(Animations::Bullet, textures.get(Textures::Bullet), 10, 10, 1);

    animations.load(Animations::Spear_Idle, textures.get(Textures::Spear_Thrust), 6, 84, 1);
    animations.load(Animations::Spear_Thrust, textures.get(Textures::Spear_Thrust), 6, 84, 8, 1);

    //!!! add animations for weapon melee attacks (pistol whip, sword slash, etc)


    animations.load(Animations::Grass, textures.get(Textures::Grass), 1024, 1024, 1); // easier to set up as animation with single sprite

    hero = std::make_shared<Hero>(Hero::Bob, animations, data); // constructor is called upon program startup so cannot use
                                                                // CCharState::Instance()->getSelectedHero() here as it will return 0
	  level = std::make_shared<Level>(1, animations, data);

    HUD_background.setSize( sf::Vector2f( 0, 0 ) ); // empty initialization. Set to window size in Playstate::Init()
    //HUD_background.setTexture( );
    HUD_background.setFillColor( sf::Color( 255, 255, 255, 255 ) );

    HUD_weapon.setScale(2, 2);

    HUD_health.setFont(fonts.get(Fonts::Calibri));
    HUD_health.setCharacterSize(40);
    HUD_health.setColor(sf::Color::Black);

    HUD_timer.setFont(fonts.get(Fonts::Calibri));
    HUD_timer.setCharacterSize(40);
    HUD_timer.setColor(sf::Color::Black);

    HUD_ammo_count.setFont(fonts.get(Fonts::Calibri));
    HUD_ammo_count.setCharacterSize(40);
    HUD_ammo_count.setColor(sf::Color::Black);

    HUD_sheep_count.setFont(fonts.get(Fonts::Calibri));
    HUD_sheep_count.setCharacterSize(40);
    HUD_sheep_count.setColor(sf::Color::Black);

    pause_text.setFont(fonts.get(Fonts::Calibri));
    pause_text.setCharacterSize(100);
    pause_text.setColor(sf::Color::Black); //!!! find a better color

    crosshair.setTexture( textures.get( Textures::Crosshair ) );
    crosshair.setOrigin(25,25);

  }

private:
	static CPlayState PlayState;

  ResourceHolder<sf::Font, Fonts::ID> fonts;
  ResourceHolder<sf::Texture, Textures::ID> textures;
  ResourceHolder<Animation, Animations::ID> animations;

  DataTable data;

  std::shared_ptr<Hero> hero;
	std::shared_ptr<Level> level;

	sf::RectangleShape HUD_background;
	AnimatedSprite HUD_weapon;
	sf::Text HUD_health;
	sf::Text HUD_timer;
  sf::Text HUD_ammo_count;
	sf::Text HUD_sheep_count;
	sf::Text pause_text;
	sf::Sprite crosshair;

	sf::Time game_time;

	sf::Time keyboard_delay;
  bool keyboardReady() { return keyboard_delay < sf::Time::Zero; }
  void reduceKeyboardCooldown(sf::Time dt) { keyboard_delay -= dt; }
  void resetKeyboardCooldown() { keyboard_delay = sf::milliseconds(250); }

};

#endif

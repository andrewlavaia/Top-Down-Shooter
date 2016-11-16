/* ----------------
 * ResourceManager
 * ----------------
 * Creates an object that can load and fetch resources
 * Currently holds objects of the following types: sf::Texture, sf::SoundBuffer, sf::Font, sf::Shader, Animation
 * https://github.com/LaurentGomila/SFML-Game-Development-Book/tree/master/02_Resources/Include/Book
 */

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "animation.h"


namespace Textures {
  enum ID {
    Empty,
    Hitbox,
    Human_1_SpriteSheet,
    Human_2_SpriteSheet,
    Human_3_SpriteSheet,
    Human_4_SpriteSheet,
    Human_5_SpriteSheet,
    Human_6_SpriteSheet,
    Human_7_SpriteSheet,
    Human_8_SpriteSheet,
    Human_9_SpriteSheet,
    Human_10_SpriteSheet,
    Human_11_SpriteSheet,
    Human_12_SpriteSheet,
    Human_13_SpriteSheet,
    Sheep_SpriteSheet,
    NPC_Texture,
    Pistol,
    Rifle,
    Shotgun,
    SMG,
    RocketLauncher,
    Bullet,
    Dagger_Metallic,
    ShortSword_Metallic,
    Sword_Metallic,
    LongSword_Metallic,
    SingleAx_Metallic,
    DoubleAx_Metallic,
    Spear,
    Spear_Thrust,
    Spear_Slash,
    Grass,
    Dungeon,
    Crosshair,

 };
}

namespace Fonts {
  enum ID {
    Calibri
  };
}

namespace Animations {
  enum ID {
    Empty,
    Hitbox, //used only to grab hitbox texture so there is no need to pass around all textures to entities
    Human_1_Idle,
    Human_1_Walk,
    Human_1_Run,
    Human_1_Grab,
    Human_1_Attacked,
    Human_1_Die,
    Human_1_Dead,
    Human_2_Idle,
    Human_2_Walk,
    Human_2_Run,
    Human_2_Grab,
    Human_2_Attacked,
    Human_2_Die,
    Human_2_Dead,
    Human_3_Idle,
    Human_3_Walk,
    Human_3_Run,
    Human_3_Grab,
    Human_3_Attacked,
    Human_3_Die,
    Human_3_Dead,
    Human_4_Idle,
    Human_4_Walk,
    Human_4_Run,
    Human_4_Grab,
    Human_4_Attacked,
    Human_4_Die,
    Human_4_Dead,
    Human_5_Idle,
    Human_5_Walk,
    Human_5_Run,
    Human_5_Grab,
    Human_5_Attacked,
    Human_5_Die,
    Human_5_Dead,
    Human_6_Idle,
    Human_6_Walk,
    Human_6_Run,
    Human_6_Grab,
    Human_6_Attacked,
    Human_6_Die,
    Human_6_Dead,
    Human_7_Idle,
    Human_7_Walk,
    Human_7_Run,
    Human_7_Grab,
    Human_7_Attacked,
    Human_7_Die,
    Human_7_Dead,
    Human_8_Idle,
    Human_8_Walk,
    Human_8_Run,
    Human_8_Grab,
    Human_8_Attacked,
    Human_8_Die,
    Human_8_Dead,
    Human_9_Idle,
    Human_9_Walk,
    Human_9_Run,
    Human_9_Grab,
    Human_9_Attacked,
    Human_9_Die,
    Human_9_Dead,
    Human_10_Idle,
    Human_10_Walk,
    Human_10_Run,
    Human_10_Grab,
    Human_10_Attacked,
    Human_10_Die,
    Human_10_Dead,
    Human_11_Idle,
    Human_11_Walk,
    Human_11_Run,
    Human_11_Grab,
    Human_11_Attacked,
    Human_11_Die,
    Human_11_Dead,
    Human_12_Idle,
    Human_12_Walk,
    Human_12_Run,
    Human_12_Grab,
    Human_12_Attacked,
    Human_12_Die,
    Human_12_Dead,
    Human_13_Idle,
    Human_13_Walk,
    Human_13_Run,
    Human_13_Grab,
    Human_13_Attacked,
    Human_13_Die,
    Human_13_Dead,
    Sheep_Idle,
    Sheep_Walk,
    Sheep_Attacked,
    Sheep_Die,
    Sheep_Dead,
    Pistol,
    Rifle,
    Shotgun,
    SMG,
    RocketLauncher_Idle,
    Bullet,
    Dagger_Metallic_Idle,
    ShortSword_Metallic_Idle,
    Sword_Metallic_Idle,
    LongSword_Metallic_Idle,
    SingleAx_Metallic_Idle,
    DoubleAx_Metallic_Idle,
    Spear_Idle,
    Spear_Thrust,
    Spear_Slash,
    Grass,
  };

}

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void						  load(Identifier id, const std::string& filename);

    // For Shaders or anything else with two paramaters
		template <typename Parameter>
		void						  load(Identifier id, const std::string& filename, const Parameter& secondParam);

    // For Animations where all sprites are sequential
		void              load(Identifier id, const sf::Texture& tex, unsigned width, unsigned height, unsigned col_count, unsigned row_count = 1);

		// For Animations where one spritesheet contains all of the sprites for an animation
		void              load( Identifier id,
                            const sf::Texture& spriteSheet,
                            unsigned spriteWidth,
                            unsigned spriteHeight,
                            unsigned colCount,
                            unsigned rowCount,
                            std::vector<unsigned> spriteVec
                          );


		Resource&					get(Identifier id);
		const Resource&		get(Identifier id) const;


	private:
		void						  insertResource(Identifier id, std::unique_ptr<Resource> resource);


	private:
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "resourceholder.inl"

#endif

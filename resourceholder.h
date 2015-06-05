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
    Hero_Idle,
    Hero_Walk,
    Hero_Run,
    Hero_Attacked,
    Hero_Die,
    Hero_Dead,
    Hero_Grab,
    Hero_Punch,
    Hero_Kick,
    NPC_Texture,
    Pistol,
    Bullet,
    Grass,
    Dungeon,
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
    Hero_Idle,
    Hero_Walk,
    Hero_Run,
    Hero_Attacked,
    Hero_Die,
    Hero_Dead,
    Hero_Grab,
    Hero_Punch,
    Hero_Kick,
    NPC_Run,
    Pistol,
    Bullet,
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

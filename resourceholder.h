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
    Hero_Run,
    Hero_Grab,
    Hero_Punch,
    Hero_Kick,
    NPC_Texture,
    Pistol,
    Bullet,
    Grass,
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
    Hero_Run,
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

    // For Animations
		void              load(Identifier id, const sf::Texture& tex, unsigned width, unsigned height, unsigned sprite_count);

		Resource&					get(Identifier id);
		const Resource&		get(Identifier id) const;


	private:
		void						  insertResource(Identifier id, std::unique_ptr<Resource> resource);


	private:
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "resourceholder.inl"

#endif

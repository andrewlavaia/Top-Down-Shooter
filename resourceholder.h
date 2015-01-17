/* ----------------
 * ResourceManager
 * ----------------
 * Creates an object that can load and fetch resources
 * Handles sf::Texture, sf::SoundBuffer, sf::Font, sf::Shader
 * https://github.com/LaurentGomila/SFML-Game-Development-Book/tree/master/02_Resources/Include/Book
 */

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>



namespace Textures {
  enum ID {
    Hero_Run,
    Hero_Grab,
    Hero_Punch,
    Hero_Kick,
    NPC_Texture,
    Hitbox
 };
}

namespace Fonts {
  enum ID {
    Calibri
  };
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void						  load(Identifier id, const std::string& filename);

		template <typename Parameter>
		void						  load(Identifier id, const std::string& filename, const Parameter& secondParam);

		Resource&					get(Identifier id);
		const Resource&		get(Identifier id) const;


	private:
		void						  insertResource(Identifier id, std::unique_ptr<Resource> resource);


	private:
		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "resourceholder.inl"

#endif

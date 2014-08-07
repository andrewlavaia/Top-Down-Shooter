/* MapManager
 * Creates and displays a tile based map from a .txt file
 *
 *   complex .txt file should follow the following format:
 *      path/to/image/location.png
 *      tile_width tile_height
 *      tile map separated by spaces and new lines
 *         0,0 represents first tile in image
 *         1,0 represents next tile in image
 *         x,x representing null tile
 *
 *   simple .txt file should follow the following format:
 *      path/to/image/location.png
 *      tile_width tile_height rows columns
 *
 */

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<vector>
#include<sstream>
#include "tile.h"


class MapManager
{
public:
  MapManager();

  void Load(std::string filelocation);      // loads the map file and populates array of tiles. Requires .txt file location

  int GetTileWidth() { return tile_width; }
  int GetTileHeight() { return tile_height; }

  std::vector<std::vector<Tile>> GetTiles(){ return tiles; }
  std::string filepath_txt;


private:
  void SetSprites();                        // used in MapManager::Load
  void SetTileSize(int width, int height);  // used in MapManager::Load

  const std::string map_type;
  std::string filepath_img;

  int tile_width;                           // stored at map level as all tiles should be the same size
  int tile_height;                          // stored at map level as all tiles should be the same size
  sf::Texture map_texture;

  void LoadComplex();                       // NOT CURRENTLY USED - supports loading individual tiles based on a sprite map
  void SetSpritesComplex();                 // NOT CURRENTLY USED

  std::vector<std::vector<Tile>> tiles;
};


#endif  // MAPMANAGER

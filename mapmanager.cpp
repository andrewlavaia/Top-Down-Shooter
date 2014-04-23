#include "mapmanager.h"

MapManager::MapManager(std::string filelocation) : filepath_txt(filelocation)
{
  MapManager::Load();
  MapManager::SetSprites();
}

void MapManager::Load()
{
  std::ifstream openfile(this->filepath_txt);

  if(openfile.is_open())
  {
    // set location of tile images
    std::string imagelocation;
    openfile >> imagelocation;
    this->map_texture.loadFromFile(imagelocation);
    this->filepath_img = imagelocation;

    // set tile size
    int width, height;
    openfile >> width >> height;
    this->tile_width = width;
    this->tile_height = height;

    std::vector<Tile> tempMap;
    tempMap.clear();
    this->tiles.clear();
    int rows, cols;
    openfile >> rows >> cols;

    for(int i = 0; i < cols; i++)
    {
      for(int j = 0; j < rows; j++)
      {
        tempMap.push_back(Tile(i, j));
      }
      this->tiles.push_back(tempMap);
      tempMap.clear();
    }
  }
}

void MapManager::SetSprites()
{
  for(unsigned i = 0; i < this->tiles.size(); i++)
  {
    for(unsigned j = 0; j < this->tiles[i].size(); j++)
    {
      // Set position of sprite location for all tiles
      this->tiles[i][j].sprite.setPosition(i * this->GetTileWidth(), j * this->GetTileHeight());

      // if tile is mapped to sprite map, assign that texture to sprite
      if(this->tiles[i][j].getX() != -1 && this->tiles[i][j].getY() != -1)
      {
          this->tiles[i][j].sprite.setTexture(this->map_texture);
          this->tiles[i][j].sprite.setTextureRect(sf::IntRect(this->tiles[i][j].getX() * this->GetTileWidth(),
                                                              this->tiles[i][j].getY() * this->GetTileHeight(),
                                                              this->GetTileWidth(),
                                                              this->GetTileHeight()));
      }
    }
  }
}


void MapManager::LoadComplex()
{
  std::ifstream openfile(this->filepath_txt);

  if(openfile.is_open())
  {
    // set location of tile images
    std::string imagelocation;
    openfile >> imagelocation;
    this->map_texture.loadFromFile(imagelocation);
    this->filepath_img = imagelocation;

    // set tile size
    int width, height;
    openfile >> width >> height;
    this->tile_width = width;
    this->tile_height = height;

    std::vector<Tile> tempMap;
    tempMap.clear();
    this->tiles.clear();
    while(!openfile.eof())
    {
      std::string str, value;
      std::getline(openfile, str);
      std::stringstream stream(str);

      while(std::getline(stream, value, ' '))
      {
        if(value.length() > 0)
        {
          std::string xx = value.substr(0, value.find(','));
          std::string yy = value.substr(value.find(',') + 1);

          int x, y;
          unsigned i, j;

          for(i = 0; i < xx.length(); i++)
          {
            if(!isdigit(xx[i]))
                break;
          }

          for(j = 0; j < yy.length(); j++)
          {
            if(!isdigit(yy[j]))
                break;
          }

          x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
          y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

          tempMap.push_back(Tile(x, y));
        }
      }
      this->tiles.push_back(tempMap);
      tempMap.clear();
    }
  }
}

void MapManager::SetSpritesComplex()
{
  for(unsigned i = 0; i < this->tiles.size(); i++)
  {
      for(unsigned j = 0; j < this->tiles[i].size(); j++)
      {
          // Set position of sprite location for all tiles
          this->tiles[i][j].sprite.setPosition(j * this->GetTileWidth(), i * this->GetTileHeight());

          // if tile is mapped to sprite map, assign that texture to sprite
          if(this->tiles[i][j].getX() != -1 && this->tiles[i][j].getY() != -1)
          {
              this->tiles[i][j].sprite.setTexture(this->map_texture);
              this->tiles[i][j].sprite.setTextureRect(sf::IntRect(this->tiles[i][j].getX() * this->GetTileWidth(),
                                                                  this->tiles[i][j].getY() * this->GetTileHeight(),
                                                                  this->GetTileWidth(),
                                                                  this->GetTileHeight()));
          }
      }
  }
}


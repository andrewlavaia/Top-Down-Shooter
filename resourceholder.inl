// Template so definition must be included in header file

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const sf::Texture& texture, unsigned width, unsigned height, unsigned col_count, unsigned row_count)
{
  assert(col_count > 0);
  try
  {
    // Create and load resource
    std::unique_ptr<Resource> resource(new Resource());
    resource->setSpriteSheet(texture);
    for( unsigned j = 0; j < row_count; ++j )
    {
      for( unsigned i = 0; i < col_count; ++i )
      {
        resource->addFrame(sf::IntRect( i * width, j * height, width, height));
      }
    }
    // If loading successful, insert resource to map
    insertResource(id, std::move(resource));
  }
  catch(std::exception& e)
  {
    assert(e.what());
  }

}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load( Identifier id, const sf::Texture& spriteSheet,
                                                 unsigned spriteWidth, unsigned spriteHeight,
                                                 unsigned colCount, unsigned rowCount,
                                                 std::vector<unsigned> spriteVec )
{

  assert( rowCount > 0 && colCount > 0 && spriteVec.size() > 0 );
  for( auto it = spriteVec.begin(); it != spriteVec.end(); ++it )
  {
    assert( *it < rowCount * colCount );
  }
  try
  {
    // Create and load resource
    std::unique_ptr<Resource> resource( new Resource() );
    resource->setSpriteSheet( spriteSheet );

    for( auto it = spriteVec.begin(); it != spriteVec.end(); ++it )
    {
      resource->addFrame( sf::IntRect( ( ( *it - 1 ) % colCount ) * spriteWidth,  // find starting horizontal point
                                       ( ( ( *it - 1 ) / colCount ) % rowCount ) * spriteHeight, // find starting vertical point
                                        spriteWidth,
                                        spriteHeight
                                     )
                        );
    }

    // If loading successful, insert resource to map
    insertResource( id, std::move( resource ) );

  }
  catch( std::exception& e )
  {
    assert( e.what() );
  }

}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	// Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

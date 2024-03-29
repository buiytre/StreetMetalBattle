#pragma once
#include <map>
#include <memory>
#include <cassert>
#include <string>

template<typename Resource, typename Identifier>
class ResourceHolder
{
private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	void insertResource(Identifier id, std::unique_ptr<Resource> resource);

public:
	void load(Identifier id, const std::string& filename);
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	insertResource(id, std::move(resource));
}


template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, int> TextureHolder;
typedef ResourceHolder<sf::Font, int>			FontHolder;
typedef ResourceHolder<sf::Shader, int>			ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, int>	SoundBufferHolder;
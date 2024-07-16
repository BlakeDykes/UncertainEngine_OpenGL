#ifndef TEXTURE_MAP_H
#define TEXTURE_MAP_H

class TextureData;

class TextureMap
{
public:
	TextureMap();
	TextureMap(const TextureMap&) = delete;
	TextureMap& operator=(const TextureMap&) = delete;
	~TextureMap() = default;

	void Set(unsigned int localIndex, unsigned int modelMatIndex);

	bool operator==(const unsigned int modelMatIndex);
	bool operator!=(const unsigned int modelMatIndex);

	unsigned int GetLocalIndex() const;

private:

	unsigned int LocalIndex;
	unsigned int ModelMatIndex;
};

#endif // !BONE_MAP_H


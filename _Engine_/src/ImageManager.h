#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include "ManagerBase.h"
#include "EngineNames.h"

class SpriteSheetData;

namespace Uncertain
{
	class Image;
	class Rect;
	class FontManager;
	class Font;

	class ImageManager : public ManagerBase
	{
	public: 
		ImageManager() = delete;
		ImageManager(const ImageManager&) = delete;
		ImageManager& operator=(const ImageManager&) = delete;

		static void Create(bool initAll, int initialReserved = 20, int deltaGrow = 10);
		static void Destroy();

		static void LoadSpriteSheet(SpriteSheetName ssName);

		//static Image* Add(ImageName name);
		//static void Remove(ImageName name);
		static void Remove(Image& image);
		static Image* Find(SpriteSheetName sname, const char* pImgName);

		static void PrintAll();

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		static ImageManager* instance;

		Image* poCompNode;

		ImageManager(int initialReserved, int deltaGrow);
		virtual ~ImageManager();

		void InitAll();
		static ImageManager* GetInstance();
		void Clear();


	};
}


#endif
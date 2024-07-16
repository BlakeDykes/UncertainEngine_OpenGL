#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "ManagerBase.h"
#include "EngineNames.h"

class SpriteSheetData;

namespace Uncertain
{
	class Font;
	class Rect;

	class FontManager : public ManagerBase
	{
	public:
		FontManager() = delete;
		FontManager(const FontManager&) = delete;
		FontManager& operator=(const FontManager&) = delete;

		static void Create(bool initAll, int initialReserved = 1, int deltaGrow = 2);
		static void Destroy();
		
		static Font* Add(SpriteSheetName sName);
		static void Remove(SpriteSheetName ssName);
		static Font* Find(SpriteSheetName ssName);

		static void PrintAll();

	protected:
		virtual NodeBase* CreateNode() override;

	private:

		static FontManager* instance;
		Font* poCompNode;

		FontManager(int initialReserved, int deltaGrow);
		virtual ~FontManager();


		static FontManager* GetInstance();
		void Clear();
		void InitAll();
	};
}


#endif

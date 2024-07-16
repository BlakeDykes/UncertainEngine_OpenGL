#include "FontManager.h"
#include "Font.h"
#include "Glyph.h"
#include "DLinkManager.h"
#include "Texture.h"
#include "TextureManager.h"
#include "SpriteSheetData.h"
#include "ProtoData_Wrapper.h"
#include "ImageManager.h"

namespace Uncertain
{
	FontManager* FontManager::instance = nullptr;

	FontManager::FontManager(int initialReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager())
	{
		this->poCompNode = new Font();

		this->SetReserve(initialReserved, deltaGrow);
	}

	FontManager::~FontManager()
	{
		delete this->poCompNode;
	}

	void FontManager::Create(bool initAll, int initialReserved, int deltaGrow)
	{
		assert(!instance);

		if (!instance)
		{
			instance = new FontManager(initialReserved, deltaGrow);

			if (initAll)
			{
				instance->InitAll();
			}
		}
	}

	void FontManager::Destroy()
	{
		assert(instance);

		FontManager* inst = FontManager::GetInstance();

		delete inst;

	}
	
	Font* FontManager::Add(SpriteSheetName sName)
	{
		SpriteSheetData sData;
		ProtoData_Wrapper::ReadFromFile(GetFileName(sName), sData);

		if(sData.Type == SpriteSheetData::TYPE::FONT)
		{
			assert(sData.Type == SpriteSheetData::TYPE::FONT);
			assert(sData.ImageCount == 96);

			FontManager* inst = FontManager::GetInstance();

			Font* pFont = (Font*)inst->BaseAdd();
			Glyph* pGlyphs = pFont->GetGlyphList();
			
			TextureManager::Add(sData, sName, pGlyphs);

			pFont->Set(sName);

			return pFont;
		}
		else if (sData.Type == SpriteSheetData::TYPE::SPRITE)
		{
			ImageManager::LoadSpriteSheet(sName);
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	void FontManager::Remove(SpriteSheetName ssName)
	{
		FontManager* inst = FontManager::GetInstance();

		inst->poCompNode->Set(ssName);
		Font* pFont = (Font*)inst->BaseFind(*inst->poCompNode);

		inst->BaseRemove(*pFont);
	}


	Font* FontManager::Find(SpriteSheetName ssName)
	{
		FontManager* inst = FontManager::GetInstance();

		inst->poCompNode->Set(ssName);
		return (Font*)inst->BaseFind(*inst->poCompNode);
	}

	void FontManager::PrintAll()
	{
		FontManager* inst = FontManager::GetInstance();

		Trace::out("\n");
		Trace::out("---------------------------\n");
		Trace::out("------ Active Fonts -------\n");
		Trace::out("---------------------------\n");

		inst->BasePrintAll();
	}

	NodeBase* FontManager::CreateNode()
	{
		return new Font();
	}

	void FontManager::Clear()
	{
		this->BaseClear();
	}

	FontManager* FontManager::GetInstance()
	{
		assert(instance);

		return instance;
	}

	void FontManager::InitAll()
	{
		this->Add(EngineNames::SpriteSheetName::VERDANA_FONT);
	}

}


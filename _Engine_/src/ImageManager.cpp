#include "ImageManager.h"
#include "FontManager.h"
#include "Font.h"
#include "Glyph.h"
#include "Rect.h"
#include "Image.h"
#include "DLinkManager.h"
#include "TextureManager.h"
#include "SpriteSheetData.h"
#include "ProtoData_Wrapper.h"

namespace Uncertain
{
	ImageManager* ImageManager::instance = nullptr;

	ImageManager::ImageManager(int initialReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager()), poCompNode(new Image())
	{
		this->SetReserve(initialReserved, deltaGrow);
	}
	
	ImageManager::~ImageManager()
	{
		delete this->poCompNode;
	}

	void ImageManager::Create(bool initAll, int initialReserved, int deltaGrow)
	{
		assert(instance == nullptr);

		if (instance == nullptr)
		{
			instance = new ImageManager(initialReserved, deltaGrow);
			
			if (initAll)
			{
				instance->InitAll();
			}
		}
	}

	void ImageManager::Destroy()
	{
		ImageManager* inst = ImageManager::GetInstance();

		delete inst;
		instance = nullptr;
	}

	void ImageManager::LoadSpriteSheet(SpriteSheetName ssName)
	{
		ImageManager* inst = ImageManager::GetInstance();

		SpriteSheetData ssData;
		ProtoData_Wrapper::ReadFromFile(GetFileName(ssName), ssData);

		if(ssData.Type == SpriteSheetData::TYPE::SPRITE)
		{
			TextureNode* pTextNode = TextureManager::Add(TextureName::SPRITE_SHEET, *ssData.pText);
			Texture* pText = pTextNode->GetTexture();
			Image* pImage = nullptr;

			for (unsigned int i = 0; i < ssData.ImageCount; i++)
			{
				pImage = (Image*)inst->BaseAdd();
				pImage->Set(ssName, pText, ssData.pImages[i]->ImageName, 
					(float)ssData.pImages[i]->X, 
					(float)ssData.pImages[i]->Y, 
					(float)ssData.pImages[i]->Width, 
					(float)ssData.pImages[i]->Height);
			}
		}
		else if (ssData.Type == SpriteSheetData::TYPE::FONT)
		{
			FontManager::Add(ssName);
		}
		else
		{
			assert(false);
		}
	}

	void ImageManager::Remove(Image& image)
	{
		ImageManager* inst = ImageManager::GetInstance();

		inst->BaseRemove(image);
	}


	Image* ImageManager::Find(SpriteSheetName sname, const char* pImgName)
	{
		ImageManager* inst = ImageManager::GetInstance();

		inst->poCompNode->SName = sname;
		inst->poCompNode->SetName(pImgName);

		return (Image*)inst->BaseFind(*inst->poCompNode);
	}

	void ImageManager::PrintAll()
	{
		ImageManager* inst = ImageManager::GetInstance();

		Trace::out("\n");
		Trace::out("---------------------------\n");
		Trace::out("------ Active Images ------\n");
		Trace::out("---------------------------\n");

		inst->BasePrintAll();
	}

	NodeBase* ImageManager::CreateNode()
	{
		return new Image();
	}

	ImageManager* ImageManager::GetInstance()
	{
		assert(instance);
		return instance;
	}

	void ImageManager::InitAll()
	{
		this->LoadSpriteSheet(EngineNames::SpriteSheetName::UI_GREY);
		this->LoadSpriteSheet(EngineNames::SpriteSheetName::ALIENS);
	}
	
	void ImageManager::Clear()
	{
		this->BaseClear();
	}

}


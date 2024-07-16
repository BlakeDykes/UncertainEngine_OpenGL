#include "EngineNames.h"


const char* EngineNames::Stringify(PlayerName name)
{
	switch (name)
	{
	case EngineNames::PlayerName::PLAYER_1:				return "Player 1";
	case EngineNames::PlayerName::PLAYER_2:				return "Player 2";
	case EngineNames::PlayerName::CONCERT_BAND:			return "Concert band player";

	case EngineNames::PlayerName::UNINITIALIZED:		return "Uninitialized";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(ArmatureName name)
{
	switch (name)
	{
	case EngineNames::ArmatureName::CLAIRE:				return "Claire - ";
	case EngineNames::ArmatureName::CHICKEN_BOT:		return "Chicken Bot - ";
	case EngineNames::ArmatureName::GRANDMA:			return "Grandma - ";
	case EngineNames::ArmatureName::KNIGHT:				return "Knight - ";
	case EngineNames::ArmatureName::MICHELLE:			return "Michelle - ";
	case EngineNames::ArmatureName::MOUSE:				return "Mouse - ";
	case EngineNames::ArmatureName::NINJA:				return "Ninja - ";
	case EngineNames::ArmatureName::ORTIZ:				return "Ortiz - ";
	case EngineNames::ArmatureName::PALADIN:			return "Paladin - ";
	case EngineNames::ArmatureName::PUMPKIN_HULK:		return "Pumpkin Hulk - ";
	case EngineNames::ArmatureName::VANGUARD:			return "Vanguard - ";
	case EngineNames::ArmatureName::ZOMBIE_GIRL:		return "Zombie Girl - ";
	case EngineNames::ArmatureName::UNINITIALIZED:		return "Uninitialized Armature";
	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(ShaderName name)
{
	switch (name)
	{
	case EngineNames::ShaderName::COLOR_LIGHT:				return "Color Light - Shader";
	case EngineNames::ShaderName::COLOR_CONST:				return "Color Constant - Shadert";
	case EngineNames::ShaderName::COLOR_PHONG:				return "Phong Lighting Color - Shader";
	case EngineNames::ShaderName::TEXTURE_SIMPLE:			return "Texture Simple - Shader";
	case EngineNames::ShaderName::TEXTURE_POINT_LIGHT:		return "Texture Point Light - Shader";
	case EngineNames::ShaderName::SKIN_TEXT_POINT_LIGHT:	return "Skinned Texture Point Light- Shader";
	case EngineNames::ShaderName::SPRITE_FLAT:				return "Sprite Flat - Shader";
	case EngineNames::ShaderName::UI_FLAT:					return "UI Flat - Shader";
	case EngineNames::ShaderName::FONT_FLAT:				return "Font Flat - Shader";

	case EngineNames::ShaderName::COMPUTE_BONE_WORLD:		return "Bone World - Compue Shader";
	case EngineNames::ShaderName::COMPUTE_ANIM_MIXER:		return "Anim Mixer - Compue Shader";

	case EngineNames::ShaderName::NULL_SHADER:				return "NULL SHADER";
	case EngineNames::ShaderName::UNINITIALIZED:			return "Uninitialized - Shader";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(TextureName name)
{
	switch (name)
	{
	case EngineNames::TextureName::STONES:					return "Stones - Texture";
	case EngineNames::TextureName::RED_BRICK:				return "Red Brick - Texture";
	case EngineNames::TextureName::DUCKWEED:				return "Duckweed - Texture";
	case EngineNames::TextureName::ROCKS:					return "Rocks - Texture";

	case EngineNames::TextureName::CLAIRE:					return "Claire - Model Textures";
	case EngineNames::TextureName::CHICKENBOT_DIFFUSE:		return "Chicken Bot - Diffuse Texture";
	case EngineNames::TextureName::GRANDMA:					return "Grandma - Model Textures";
	case EngineNames::TextureName::KNIGHT_DIFFUSE:			return "Knight - Diffuse Texture";
	case EngineNames::TextureName::MICHELLE_DIFFUSE:		return "Michelle - Diffuse Texture";
	case EngineNames::TextureName::MOUSE_DIFFUSE:			return "Mouse - Diffuse Texture";
	case EngineNames::TextureName::NINJA_DIFFUSE:			return "Ninja - Diffuse Texture";
	case EngineNames::TextureName::ORTIZ_DIFFUSE:			return "Ortiz - Diffuse Texture";
	case EngineNames::TextureName::PALADIN_DIFFUSE:			return "Paladin - Diffuse Texture";
	case EngineNames::TextureName::PUMPKIN_HULK_DIFFUSE:	return "Pumpkin Hulk - Diffuse Texture";
	case EngineNames::TextureName::R2D2_BASE:				return "R2D2 - Base Color Texture";
	case EngineNames::TextureName::SPACEFRIG_BASE:			return "Space Frig - Base Color Texture";
	case EngineNames::TextureName::VANGUARD:				return "Vanguard - Model Textures";
	case EngineNames::TextureName::WOODEN_CRATE_BASE:		return "Wooden Crate - Base Color Texture";
	case EngineNames::TextureName::ZOMBIE_GIRL:				return "Zombie Girl - Model Textures";

	case EngineNames::TextureName::PROTO:					return "Proto - Texture";
	case EngineNames::TextureName::FONT:					return "Font - Texture";
	case EngineNames::TextureName::SPRITE_SHEET:			return "SpriteSheet - Texture";
	case EngineNames::TextureName::DEFAULT:					return "Default - Texture";

	case EngineNames::TextureName::UNINITIALIZED:			return "Uninitialized - Texture";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(MeshName name)
{
	switch (name)
	{
	case EngineNames::MeshName::CUBE_MESH:		return "Cube - Mesh";
	case EngineNames::MeshName::SPHERE_MESH:	return "Sphere - Mesh";
	case EngineNames::MeshName::PLANE_MESH:		return "Plane - Mesh";
	case EngineNames::MeshName::CONE_MESH:		return "Cone - Mesh";
	case EngineNames::MeshName::TORUS_MESH:		return "Torus - Mesh";
	case EngineNames::MeshName::ICOSPHERE_MESH:	return "Icosphere - Mesh";
	case EngineNames::MeshName::CAMERA_MESH:	return "Camera - Mesh";
	case EngineNames::MeshName::PROTO_MESH:		return "Proto - Mesh";
	case EngineNames::MeshName::SPRITE_MESH:	return "Sprite - Mesh";
	case EngineNames::MeshName::RECT_MESH:		return "Rect - Mesh";
	case EngineNames::MeshName::FONT_MESH:		return "Rect - Mesh";

	case EngineNames::MeshName::NULL_MESH:		return "Null - Mesh";
	case EngineNames::MeshName::UNINITIALIZED:	return "Uninitialized - Mesh";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(ModelName name)
{
	switch (name)
	{
	case EngineNames::ModelName::CLAIRE:			return "Claire - Model";
	case EngineNames::ModelName::CHICKEN_BOT:		return "Chicken Bot - Model";
	case EngineNames::ModelName::GRANDMA:			return "Grandma - Model";
	case EngineNames::ModelName::KNIGHT:			return "Knight - Model";
	case EngineNames::ModelName::MICHELLE:			return "Michelle - Model";
	case EngineNames::ModelName::MOUSE:				return "Mouse - Model";
	case EngineNames::ModelName::NINJA:				return "Ninja - Model";
	case EngineNames::ModelName::ORTIZ:				return "Ortiz - Model";
	case EngineNames::ModelName::PALADIN:			return "Paladin - Model";

	case EngineNames::ModelName::PUMPKIN_HULK:		return "Pumpkin Hulk - Model";
	case EngineNames::ModelName::R2D2:				return "R2D2 - Model";
	case EngineNames::ModelName::SPACE_FRIG:		return "Space Frigate - Model";
	case EngineNames::ModelName::VANGUARD:			return "Vanguard - Model";

	case EngineNames::ModelName::WOODEN_CRATE:		return "Wooden Crate - Model";
	case EngineNames::ModelName::ZOMBIE_GIRL:		return "Zombie Girl - Model";

	case EngineNames::ModelName::UNINITIALIZED:		return "Uninitialized - Model";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(CameraName name)
{
	switch (name)
	{
	case EngineNames::CameraName::MAIN_3D:				return "Main 3D - Camera";
	case EngineNames::CameraName::MAIN_2D:				return "Main 2D - Camera";
	case EngineNames::CameraName::AUX_3D_1:				return "3D Aux 1 - Camera";
	case EngineNames::CameraName::AUX_2D_1:				return "2D Aux 1 - Camera";
	case EngineNames::CameraName::PROTO:				return "Proto - Camera";

	case EngineNames::CameraName::EDIT_NEG_X:			return "Edit Negative X - Camera";
	case EngineNames::CameraName::EDIT_NEG_Y:			return "Edit Negative Y - Camera";
	case EngineNames::CameraName::EDIT_NEG_Z:			return "Edit Negative Z - Camera";


	case EngineNames::CameraName::UNINITIALIZED:		return "Uninitialized - Camera";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(MaterialName name)
{
	switch (name)
	{
	case EngineNames::MaterialName::COLOR_CONST:			return "Constant Color - Material";
	case EngineNames::MaterialName::COLOR_LIGHT:			return "Color with Light - Material";
	case EngineNames::MaterialName::COLOR_PHONG_LIGHT:		return "Color Phong light - Material";
	case EngineNames::MaterialName::TEXT_FLAT:				return "Flat texture - Material";
	case EngineNames::MaterialName::TEXT_POINT_LIGHT:		return "Point Light Texture - Material";
	case EngineNames::MaterialName::SKIN_TEXT_POINT_LIGHT:	return "Skinned Texture Point Light - Material";
	case EngineNames::MaterialName::SPRITE:					return "Sprite - Material";
	case EngineNames::MaterialName::UI:						return "UI - Material";
	case EngineNames::MaterialName::FONT:					return "Font - Material";
	case EngineNames::MaterialName::WIREFRAME:				return "Wireframe - Material";
	case EngineNames::MaterialName::PROTO:					return "Proto - Material";
	case EngineNames::MaterialName::BOUNDING_SPHERE:		return "Bounding Sphere - Material";
	case EngineNames::MaterialName::BOUNDING_RECT:			return "Bounding Rect - Material";
	case EngineNames::MaterialName::NULL_MAT:				return "Null material";
	case EngineNames::MaterialName::UNINITIALIZED:			return "Uninitialized - Material";

	default:
		// name not added to switch
		assert(false);
		return nullptr;
		break;
	}
}

const char* EngineNames::Stringify(UIName name)
{
	switch (name)
	{
	case EngineNames::UIName::PAUSE:			return "Pause - UI";
	case EngineNames::UIName::DEBUG_1:			return "Debug 1 - UI";
	case EngineNames::UIName::DEBUG_2:			return "Debug 2 - UI";
	case EngineNames::UIName::UNINITIALIZED:	return "Uninitialized - UI";
	default:
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::Stringify(SpriteSheetName name)
{
	switch (name)
	{
	case EngineNames::SpriteSheetName::UI_GREY:			return "UI Grey - SpriteSheet";
	case EngineNames::SpriteSheetName::ALIENS:			return "Space Invaders - SpriteSheet";
	case EngineNames::SpriteSheetName::VERDANA_FONT:	return "Verdana - SpriteSheet";
	case EngineNames::SpriteSheetName::UNINITIALIZED:	return "Uninitialized - SpriteSheet";
	default:
		assert(false);
		return nullptr;
	}
}




const char* EngineNames::GetFileName(MeshName name)
{
	switch (name)
	{
	case EngineNames::MeshName::CUBE_MESH:				return "../../Data/Primitives/Cube/Mesh/CubeMesh.azul";
	case EngineNames::MeshName::SPHERE_MESH:			return "../../Data/Primitives/Sphere/Mesh/SphereMesh.azul";
	case EngineNames::MeshName::PLANE_MESH:				return "../../Data/Primitives/Plane/Mesh/PlaneMesh.azul";
	case EngineNames::MeshName::CONE_MESH:				return "../../Data/Primitives/Cone/Mesh/ConeMesh.azul";
	case EngineNames::MeshName::TORUS_MESH:				return "../../Data/Primitives/Torus/Mesh/TorusMesh.azul";
	case EngineNames::MeshName::CAMERA_MESH:			return "../../Data/Primitives/Camera/Mesh/CameraMesh.azul";
	case EngineNames::MeshName::ICOSPHERE_MESH:			return "../../Data/Primitives/Icosphere/Mesh/IcosphereMesh.azul";
	
	case EngineNames::MeshName::FONT_MESH:
	case EngineNames::MeshName::SPRITE_MESH:			
	case EngineNames::MeshName::RECT_MESH:
	case EngineNames::MeshName::NULL_MESH:
	case EngineNames::MeshName::UNINITIALIZED:			
	case EngineNames::MeshName::PROTO_MESH:
		return nullptr;
	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::GetFileName(ArmatureName name)
{
	switch (name)
	{
	case EngineNames::ArmatureName::CLAIRE:				return "model_claire/Armature/arm_model_claire";
	case EngineNames::ArmatureName::CHICKEN_BOT:		return "model_chickenBot/Armature/arm_model_chickenBot";
	case EngineNames::ArmatureName::GRANDMA:			return "model_grandma/Armature/arm_model_grandma";
	case EngineNames::ArmatureName::KNIGHT:				return "model_knight/Armature/arm_model_knight";
	case EngineNames::ArmatureName::MICHELLE:			return "model_michelle/Armature/arm_model_michelle";
	case EngineNames::ArmatureName::MOUSE:				return "model_mouse/Armature/arm_model_mouse";
	case EngineNames::ArmatureName::NINJA:				return "model_ninja/Armature/arm_model_ninja";
	case EngineNames::ArmatureName::ORTIZ:				return "model_ortiz/Armature/arm_model_ortiz";
	case EngineNames::ArmatureName::PALADIN:			return "model_paladin/Armature/arm_model_paladin";
	case EngineNames::ArmatureName::PUMPKIN_HULK:		return "model_pumpkinHulk/Armature/arm_model_pumpkinHulk";
	case EngineNames::ArmatureName::VANGUARD:			return "model_vanguard/Armature/arm_model_vanguard";
	case EngineNames::ArmatureName::ZOMBIE_GIRL:		return "model_zombieGirl/Armature/arm_model_zombieGirl";

	case EngineNames::ArmatureName::UNINITIALIZED:		
	default:
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::GetFileName(ModelName name)
{
	switch (name)
	{
	case EngineNames::ModelName::CLAIRE:			return "model_claire/Model/model_claire";
	case EngineNames::ModelName::CHICKEN_BOT:		return "model_chickenBot/Model/model_chickenBot";
	case EngineNames::ModelName::GRANDMA:			return "model_grandma/Model/model_grandma";
	case EngineNames::ModelName::KNIGHT:			return "model_knight/Model/model_knight";
	case EngineNames::ModelName::MICHELLE:			return "model_michelle/Model/model_michelle";
	case EngineNames::ModelName::MOUSE:				return "model_mouse/Model/model_mouse";
	case EngineNames::ModelName::NINJA:				return "model_ninja/Model/model_ninja";
	case EngineNames::ModelName::ORTIZ:				return "model_ortiz/Model/model_ortiz";
	case EngineNames::ModelName::PALADIN:			return "model_paladin/Model/model_paladin";
	case EngineNames::ModelName::PUMPKIN_HULK:		return "model_pumpkinHulk/Model/model_pumpkinHulk";
	case EngineNames::ModelName::R2D2:				return "model_r2d2/Model/model_r2d2";
	case EngineNames::ModelName::SPACE_FRIG:		return "model_spaceFrigate/Model/model_spaceFrigate";
	case EngineNames::ModelName::VANGUARD:			return "model_vanguard/Model/model_vanguard";
	case EngineNames::ModelName::WOODEN_CRATE:		return "model_woodenCrate/Model/model_woodenCrate";
	case EngineNames::ModelName::ZOMBIE_GIRL:		return "model_zombieGirl/Model/model_zombieGirl";
	
	case EngineNames::ModelName::UNINITIALIZED:
	default:
		// name not added to switch
		assert(false);
		return nullptr;
	}
}

const char* EngineNames::GetFileName(TextureName name)
{
	switch (name)
	{
	case EngineNames::TextureName::STONES:					return "texture_environment/Texture/Stone.tga";
	case EngineNames::TextureName::RED_BRICK:				return "texture_environment/Texture/RedBrick.tga";
	case EngineNames::TextureName::DUCKWEED:				return "texture_environment/Texture/Duckweed.tga";
	case EngineNames::TextureName::ROCKS:					return "texture_environment/Texture/Rocks.tga";

	case EngineNames::TextureName::CLAIRE:					return "model_claire/Texture/t_all_model_claire";
	case EngineNames::TextureName::CHICKENBOT_DIFFUSE:		return "model_chickenBot/Texture/t_ChickenbotDiffuse.png";
	case EngineNames::TextureName::GRANDMA:					return "model_grandma/Texture/t_all_model_grandma";
	case EngineNames::TextureName::KNIGHT_DIFFUSE:			return "model_knight/Texture/t_Knight_diffuse.png";
	case EngineNames::TextureName::MICHELLE_DIFFUSE:		return "model_michelle/Texture/t_Ch03_1001_Diffuse.png";
	case EngineNames::TextureName::MOUSE_DIFFUSE:			return "model_mouse/Texture/t_Ch14_1001_Diffuse.png";
	case EngineNames::TextureName::NINJA_DIFFUSE:			return "model_ninja/Texture/t_Ch24_1001_Diffuse.png";
	case EngineNames::TextureName::ORTIZ_DIFFUSE:			return "model_ortiz/Texture/t_Ch43_1001_Diffuse.png";
	case EngineNames::TextureName::PALADIN_DIFFUSE:			return "model_paladin/Texture/t_Paladin_diffuse.png";
	case EngineNames::TextureName::PUMPKIN_HULK_DIFFUSE:	return "model_pumpkinHulk/Texture/t_pumpkinHulk_diffuse.png";
	case EngineNames::TextureName::R2D2_BASE:				return "model_r2d2/Texture/R2D2_BaseColor.png";
	case EngineNames::TextureName::SPACEFRIG_BASE:			return "model_spaceFrigate/Texture/t_space_frigate.tga";
	case EngineNames::TextureName::VANGUARD:				return "model_vanguard/Texture/t_all_model_vanguard";

	case EngineNames::TextureName::WOODEN_CRATE_BASE:		return "model_woodenCrate/Texture/t_crate_BaseColor";
	case EngineNames::TextureName::ZOMBIE_GIRL:				return "model_zombieGirl/Texture/t_all_model_zombieGirl";

	case EngineNames::TextureName::UNINITIALIZED:			return "_Default/Texture/HotPink.tga";

	case EngineNames::TextureName::DEFAULT:
	case EngineNames::TextureName::PROTO:
	case EngineNames::TextureName::FONT:
	case EngineNames::TextureName::SPRITE_SHEET:
	default:
		// name not added to switch
		assert(false);
		return nullptr;
		break;
	}
}

const char* EngineNames::GetFileName(ShaderName name)
{
	switch (name)
	{
	case EngineNames::ShaderName::COLOR_LIGHT:				return "lightColorRender";
	case EngineNames::ShaderName::COLOR_CONST:				return "colorRender";
	case EngineNames::ShaderName::COLOR_PHONG:				return "phongRender";
	case EngineNames::ShaderName::TEXTURE_SIMPLE:			return "textureRender";
	case EngineNames::ShaderName::TEXTURE_POINT_LIGHT:		return "texturePointlightDiff";
	case EngineNames::ShaderName::SKIN_TEXT_POINT_LIGHT:	return "skinTexturePointLight";
	case EngineNames::ShaderName::SPRITE_FLAT:				return "spriteRender";
	case EngineNames::ShaderName::UI_FLAT:					return "uiRender";
	case EngineNames::ShaderName::FONT_FLAT:				return "fontRender";

	case EngineNames::ShaderName::COMPUTE_BONE_WORLD:		return "computeBoneWorld";
	case EngineNames::ShaderName::COMPUTE_ANIM_MIXER:		return "computeAnimMixer";

	case EngineNames::ShaderName::NULL_SHADER:				return "nullRender";

	case EngineNames::ShaderName::UNINITIALIZED:
	default:
		// name not added to switch
		assert(false);
		return nullptr;
		break;
	}
}

const char* EngineNames::GetFileName(SpriteSheetName name)
{
	switch (name)
	{
	case EngineNames::SpriteSheetName::UI_GREY:			return "spriteSheet_UIgrey/SpriteSheet/greySheet";
	case EngineNames::SpriteSheetName::ALIENS:			return "spriteSheet_aliens/SpriteSheet/aliens";
	case EngineNames::SpriteSheetName::VERDANA_FONT:	return "font_verdana/SpriteSheet/verdana_font";

	case EngineNames::SpriteSheetName::UNINITIALIZED:	
	default:
		assert(false);
		return nullptr;
	}
}



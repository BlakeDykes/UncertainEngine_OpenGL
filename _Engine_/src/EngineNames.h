#ifndef NAMES_H
#define NAMES_H

namespace EngineNames
{
	typedef int MATERIAL_ID;

	enum class DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD
	};

	enum class PlayerName
	{
		PLAYER_1,
		PLAYER_2,

		CONCERT_BAND,


		UNINITIALIZED
	};

	enum class ArmatureName
	{
		CLAIRE,
		CHICKEN_BOT,
		GRANDMA,
		KNIGHT,
		MICHELLE,
		MOUSE,
		NINJA,
		ORTIZ,
		PALADIN,
		PUMPKIN_HULK,
		VANGUARD,
		ZOMBIE_GIRL,

		UNINITIALIZED
	};

	enum class ShaderName
	{
		COLOR_LIGHT,
		COLOR_CONST,
		COLOR_PHONG,
		TEXTURE_SIMPLE,
		TEXTURE_POINT_LIGHT,
		SKIN_TEXT_POINT_LIGHT,
		NULL_SHADER,
		SPRITE_FLAT,
		UI_FLAT,
		FONT_FLAT,

		COMPUTE_BONE_WORLD,
		COMPUTE_ANIM_MIXER,

		UNINITIALIZED,
	};

	enum class TextureName
	{
		STONES,
		RED_BRICK,
		DUCKWEED,
		ROCKS,

		CLAIRE,
		CHICKENBOT_DIFFUSE,
		GRANDMA,
		KNIGHT_DIFFUSE,
		MICHELLE_DIFFUSE,
		MOUSE_DIFFUSE,
		NINJA_DIFFUSE,
		ORTIZ_DIFFUSE,
		PALADIN_DIFFUSE,
		PUMPKIN_HULK_DIFFUSE,
		R2D2_BASE,
		SPACEFRIG_BASE,
		VANGUARD,
		WOODEN_CRATE_BASE,
		ZOMBIE_GIRL,

		PROTO,
		FONT,
		SPRITE_SHEET,
		
		DEFAULT,
		UNINITIALIZED
	};

	enum class MeshName
	{
		CUBE_MESH,
		SPHERE_MESH,
		PLANE_MESH,
		CONE_MESH,
		TORUS_MESH,
		ICOSPHERE_MESH,
		CAMERA_MESH,
		PROTO_MESH,
		SPRITE_MESH,
		RECT_MESH,
		FONT_MESH,
		NULL_MESH,

		UNINITIALIZED
	};

	enum class ModelName
	{
		CLAIRE,
		CHICKEN_BOT,
		GRANDMA,
		KNIGHT,
		MICHELLE,
		MOUSE,
		NINJA,
		ORTIZ,
		PALADIN,
		PUMPKIN_HULK,
		R2D2,
		SPACE_FRIG,
		VANGUARD,
		WOODEN_CRATE,
		ZOMBIE_GIRL,

		UNINITIALIZED
	};

	enum class MaterialName
	{
		COLOR_CONST,
		COLOR_LIGHT,
		COLOR_PHONG_LIGHT,
		TEXT_FLAT,
		TEXT_POINT_LIGHT,
		SKIN_TEXT_POINT_LIGHT,
		SPRITE,
		UI,
		FONT,
		WIREFRAME,
		PROTO,
		BOUNDING_SPHERE,
		BOUNDING_RECT,

		NULL_MAT,
		UNINITIALIZED
	};

	enum class CameraName
	{
		MAIN_3D,
		MAIN_2D,
		AUX_3D_1,
		AUX_2D_1,
		PROTO,

		EDIT_NEG_Z,
		EDIT_NEG_Y,
		EDIT_NEG_X,

		UNINITIALIZED
	};

	enum class SpriteSheetName
	{
		UI_GREY,
		ALIENS,

		// Fonts
		VERDANA_FONT,

		UNINITIALIZED
	};

	enum class UIName
	{
		PAUSE,
		DEBUG_1,
		DEBUG_2,

		UNINITIALIZED
	};

	enum class Axis
	{
		X,
		NEG_X,
		Y,
		NEG_Y,
		Z,
		NEG_Z
	};

	const char* Stringify(PlayerName name);
	const char* Stringify(ArmatureName name);
	const char* Stringify(ShaderName name);
	const char* Stringify(TextureName name);
	const char* Stringify(MeshName name);
	const char* Stringify(ModelName name);
	const char* Stringify(CameraName name);
	const char* Stringify(MaterialName name);
	const char* Stringify(UIName name);
	const char* Stringify(SpriteSheetName name);

	const char* GetFileName(MeshName name);
	const char* GetFileName(ArmatureName name);
	const char* GetFileName(ModelName name);
	const char* GetFileName(TextureName name);
	const char* GetFileName(ShaderName name);
	const char* GetFileName(SpriteSheetName name);
}

// Automatic using on include
using namespace EngineNames;

#endif // !NAMES_H


#include "ModelTextureData.pb.h"
#include "TextureData.pb.h"
#include "VBOData.pb.h"
#include "MeshData.pb.h"
#include "ModelData.pb.h"
#include "AnimData.pb.h"
#include "SpriteSheetData.pb.h"
#include "ArmatureData.pb.h"

class MeshData;
class ModelData;
class TextureData;
class ModelTextureData;
class AnimData;
class SpriteSheetData;
class ArmatureData;

class ProtoData_Wrapper
{
public:

	static const char* DATA_OUTPUT_DIR;
	static const char* DATA_INPUT_DIR;
	static const char* FILE_EXTENSION;

	static bool ReadFromFile(const char* const pFileName, TextureData& textOut);
	static bool ReadFromFile(const char* const pFileName, ModelTextureData& textOut);
	static bool ReadFromFile(const char* const pFileName, MeshData& meshOut);
	static bool ReadFromFile(const char* const pFileName, ModelData& modelOut);
	static bool ReadFromFile(const char* const pFileName, AnimData& animOut);
	static bool ReadFromFile(const char* const pFileName, SpriteSheetData& ssOut);
	static bool ReadFromFile(const char* const pFileName, ArmatureData& armOut);

};
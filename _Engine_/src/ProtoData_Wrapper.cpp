#include "ProtoData_Wrapper.h"
#include "File.h"
#include "MeshData.h"
#include "ModelTextureData.h"
#include "ModelData.h"
#include "TextureData.h"
#include "AnimData.h"
#include "SpriteSheetData.h"
#include "ArmatureData.h"

using namespace Uncertain;

const char* ProtoData_Wrapper::DATA_OUTPUT_DIR = "../../Data/";
const char* ProtoData_Wrapper::DATA_INPUT_DIR = "../../Data/";
const char* ProtoData_Wrapper::FILE_EXTENSION = ".proto.uncertain\0";

bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, TextureData& textOut)
{
	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;
	assert(nameSize <= strlen(DATA_INPUT_DIR) + TextureData::FILE_NAME_SIZE + strlen(FILE_EXTENSION) + 1);

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	TextureData_proto textProto;

	textProto.ParseFromString(strBuff);

	textOut.Deserialize(textProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}

bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, ModelTextureData& textOut)
{
	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;
	assert(nameSize <= strlen(DATA_INPUT_DIR) + TextureData::FILE_NAME_SIZE + strlen(FILE_EXTENSION) + 1);

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	ModelTextureData_proto textProto;

	textProto.ParseFromString(strBuff);

	textOut.Deserialize(textProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}

bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, MeshData& meshOut)
{
	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;
	assert(nameSize <= strlen(DATA_INPUT_DIR) + MeshData::FILE_NAME_SIZE +strlen(FILE_EXTENSION) + 1);

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	MeshData_proto meshProto;

	meshProto.ParseFromString(strBuff);

	meshOut.Deserialize(meshProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}

bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, ModelData& modelOut)
{

	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;
	assert(nameSize <= strlen(DATA_INPUT_DIR) + ModelData::MODEL_NAME_SIZE + strlen(FILE_EXTENSION) + 1);

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	ModelData_proto modelProto;

	modelProto.ParseFromString(strBuff);

	modelOut.Deserialize(modelProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}


bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, AnimData& animOut)
{
	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;
	assert(nameSize <= strlen(DATA_INPUT_DIR) + MeshData::FILE_NAME_SIZE + strlen(FILE_EXTENSION) + 1);

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	AnimData_proto animProto;

	animProto.ParseFromString(strBuff);

	animOut.Deserialize(animProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}

bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, SpriteSheetData& ssOut)
{
	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;
	assert(nameSize <= strlen(DATA_INPUT_DIR) + ModelData::MODEL_NAME_SIZE + strlen(FILE_EXTENSION) + 1);

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	SpriteSheetData_proto ssProto;

	ssProto.ParseFromString(strBuff);

	ssOut.Deserialize(ssProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}

bool ProtoData_Wrapper::ReadFromFile(const char* const pFileName, ArmatureData& armOut)
{
	size_t nameSize = strlen(DATA_INPUT_DIR) + strlen(pFileName) + strlen(FILE_EXTENSION) + 1;

	char* fileNameBuffer = new char[nameSize]();

	File::Handle fh;
	File::Error err;

	strcpy_s(fileNameBuffer, nameSize, DATA_INPUT_DIR);
	strcat_s(fileNameBuffer, nameSize, pFileName);
	strcat_s(fileNameBuffer, nameSize, FILE_EXTENSION);

	err = File::Open(fh, fileNameBuffer, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	DWORD size;
	err = File::GetSize(fh, size);

	char* poBuff = new char[size]();
	assert(poBuff);

	err = File::Read(fh, poBuff, size);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	std::string strBuff(poBuff, size);
	ArmatureData_proto armProto;

	armProto.ParseFromString(strBuff);

	armOut.Deserialize(armProto);

	delete[] poBuff;
	delete[] fileNameBuffer;

	return true;
}


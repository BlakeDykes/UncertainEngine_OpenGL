#ifndef HANDLE_MAN_H
#define HANDLE_MAN_H

#include "Handle.h"

class HandleManager
{

public:

	class HandleTableEntry
	{
	public:
		HandleTableEntry() = default;
		HandleTableEntry(const HandleTableEntry&) = delete;
		HandleTableEntry& operator = (const HandleTableEntry&) = delete;
		~HandleTableEntry() = default;

		std::atomic<unsigned int> id;
		std::mutex mtx;
	};

	HandleManager();
	~HandleManager() = default;
	HandleManager(const HandleManager&) = delete;
	const HandleManager& operator = (const HandleManager&) = delete;

	static Handle::Status ActivateHandle(Handle::ID& id, Handle::Index& index);
	static Handle::Status InvalidateHandle(Handle& handle);
	static Handle::Status ValidateHandle(const Handle& handle);
	static Handle::Status ValidateHandleData(const Handle::HandleData& data);
	static Handle::Status AcquireResource(const Handle& handle);
	static Handle::Status ReleaseResource(const Handle& handle);
	static Handle::ID GetNewID();
	static Handle::ID GetInvalidID();
	static Handle::Index GetInvalidIndex();
	static void PrintTable();

private:
	static const unsigned int MAX_HANDLES = 300;
	static const unsigned int INVALID_INDEX = MAX_HANDLES + 1;
	static unsigned int INVALID_STATE;
	static unsigned int PENDING_STATE;
	static const unsigned int STARTING_ID = 0xAAAA0000;

	static HandleManager* GetInstance();
	bool FindNextAvailable(Handle::Index& index);

	Handle::ID SourceID;
	HandleTableEntry table[MAX_HANDLES];

	std::mutex mtx;

};


#endif
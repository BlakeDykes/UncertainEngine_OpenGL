#include "Handle.h"
#include "HandleManager.h"


using namespace ThreadFramework;



Handle::Handle()
{
	//Status status = HandleManager::ActivateHandle(this->id, this->index);
	//assert(status == Status::SUCCESS);

	//Trace::out("New handle created: 0x%X\n", this->id);
}

Handle::~Handle()
{
	this->InvalidateHandle();
}

void Handle::Wash()
{
	DLink::Wash();
	this->id = HandleManager::GetInvalidID();
}

bool Handle::Compare(NodeBase& pNode)
{
	Handle* pComp = (Handle*)&pNode;

	return this->id == pComp->id;
}

bool Handle::operator==(const Handle& h) const
{
	return this->id == h.id;
}

bool Handle::operator!=(const Handle& h) const
{
	return this->id != h.id;
}

Handle::Status Handle::ActivateHandle()
{
	return HandleManager::ActivateHandle(this->id, this->index);
}

Handle::Status Handle::ValidateHandle() const
{
	return HandleManager::ValidateHandle(*this);
}

Handle::Status Handle::InvalidateHandle()
{
	return HandleManager::InvalidateHandle(*this);
}

Handle::Status Handle::AcquireResource() const
{
	return HandleManager::AcquireResource(*this);
}

Handle::Status Handle::ReleaseResource() const
{
	return HandleManager::ReleaseResource(*this);
}

Handle::Status Handle::HandleData::ValidateData()
{
	return HandleManager::ValidateHandleData(*this);
}


Handle::HandleData::HandleData()
	:id(HandleManager::GetNewID()), index(HandleManager::GetInvalidIndex())
{
}

void Handle::HandleData::Clear()
{
	this->id = HandleManager::GetInvalidID();
	this->index = HandleManager::GetInvalidIndex();
}


// ----------------------------------------------------------------------
// Handle::Lock method implementations ----------------------------------
// ----------------------------------------------------------------------

Handle::Lock::Lock(const Handle& h)
	:handle(h)
{
	this->status = handle.AcquireResource();
}

Handle::Lock::~Lock()
{
	if (this->status == Handle::Status::SUCCESS)
	{
		this->status = this->handle.ReleaseResource();
	}
}

Handle::Lock::operator bool() const
{
	return (this->status == Handle::Status::SUCCESS);
}

Handle::Lock::operator Handle::Status() const
{
	return this->status;
}
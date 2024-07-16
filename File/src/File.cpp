//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "File.h"
#include <limits>

namespace Uncertain
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{
		bool valid = false;

		if (fh != INVALID_HANDLE_VALUE && fh != nullptr)
		{
			DWORD flags;
			valid = GetHandleInformation(fh, &flags);
		}

		return valid;
	}

	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
		File::Error retStatus = File::Error::OPEN_FAIL;

		if (!IsHandleValid(fh))
		{

			fh = CreateFileA(fileName, (DWORD)mode, (FILE_SHARE_READ | FILE_SHARE_WRITE), 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

			if (fh != INVALID_HANDLE_VALUE)
			{
				retStatus = File::Error::SUCCESS;
			}
		}

		return retStatus;
	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		File::Error retStatus = File::Error::CLOSE_FAIL;

		if (IsHandleValid(fh))
		{
			if (CloseHandle(fh))
			{
				fh = INVALID_HANDLE_VALUE;
				retStatus = File::Error::SUCCESS;
			}
		}

		return 	retStatus;
	}

	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{
		File::Error retStatus = File::Error::WRITE_FAIL;

		if (IsHandleValid(fh))
		{
			if (WriteFile(fh, buffer, inSize, 0, 0))
			{
				retStatus = File::Error::SUCCESS;
			}
		}

		return retStatus;
	}

	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{
		File::Error retStatus = File::Error::READ_FAIL;

		if (IsHandleValid(fh))
		{
			if (ReadFile(fh, buffer, inSize, 0, 0))
			{
				retStatus = File::Error::SUCCESS;
			}
		}

		return retStatus;
	}

	File::Error File::MkDir(const char* const dirName) noexcept
	{
		File::Error retStatus = File::Error::PATH_FAIL;
		int ret = CreateDirectoryA(dirName, NULL);

		if ( ret != 0 ) {
			retStatus = File::Error::SUCCESS;
		}
		else
		{
			DWORD err = GetLastError();
			if (err == ERROR_ALREADY_EXISTS)
			{
				retStatus = File::Error::SUCCESS;
			}
		}
		
		return retStatus;
	}


	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		File::Error retStatus = File::Error::SEEK_FAIL;

		if (IsHandleValid(fh))
		{
			DWORD lowOrder = INVALID_SET_FILE_POINTER;

			switch (location)
			{
			case Uncertain::File::Position::BEGIN:

				if (Tell(fh, lowOrder) == File::Error::SUCCESS)
				{
					lowOrder = (lowOrder * -1) + offset;
				}
				break;

			case Uncertain::File::Position::CURRENT:

				lowOrder = (DWORD)offset;
				break;

			case Uncertain::File::Position::END:

				if (Tell(fh, lowOrder) == File::Error::SUCCESS)
				{
					lowOrder = (GetFileSize(fh, 0) - lowOrder) + offset;
				}
				break;

			default:
				assert(false);
				break;
			}

			if (SetFilePointer(fh, (LONG)lowOrder, 0, FILE_CURRENT) != INVALID_SET_FILE_POINTER)
			{
				retStatus = File::Error::SUCCESS;
			}
		}

		return retStatus;;
	}

	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
		File::Error retStatus = File::Error::TELL_FAIL;

		if (IsHandleValid(fh))
		{
			offset = SetFilePointer(fh, 0, 0, FILE_CURRENT);

			if ( offset != INVALID_SET_FILE_POINTER)
			{
				retStatus = File::Error::SUCCESS;
			}
		}

		return retStatus;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		File::Error retStatus = File::Error::FLUSH_FAIL;

		if (IsHandleValid(fh))
		{
			if (FlushFileBuffers(fh))
			{
				retStatus = File::Error::SUCCESS;
			}
		}

		return retStatus;
	}


	File::Error File::GetSize(File::Handle fh, DWORD& sizeOut) noexcept
	{
		File::Error retStatus = File::Error::SEEK_FAIL;

		DWORD currentOffset = SetFilePointer(fh, 0, 0, FILE_CURRENT);
		if (currentOffset != INVALID_SET_FILE_POINTER)
		{
			retStatus = File::Seek(fh, File::Position::END, 0);
			if (retStatus == File::Error::SUCCESS)
			{
				retStatus = File::Tell(fh, sizeOut);
				retStatus = File::Seek(fh, File::Position::BEGIN, (__int32)currentOffset);
			}
		}

		return retStatus;
	}

}

// --- End of File ---

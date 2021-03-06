#ifndef __CRY_HASH_UTIL_H__
#define __CRY_HASH_UTIL_H__

//-----------------------------------------------------------------------------------
// HASH Tools.
// from Frd's code-base courtesy of AW. /FH
typedef uint32 CryHash;

CryHash HashStringSeed( const char* string, const uint32 seed );
CryHash HashString( const char* string );

struct CryHashStringId
{
	CryHashStringId()
		: id (0)
	{

	}

	CryHashStringId(CryHash _id)
		: id (_id)
	{

	}

	CryHashStringId( const char* _name )
	{
		Set(_name);
	}

	CryHashStringId(const CryHashStringId& _otherId)
	{
#if defined(_DEBUG)
		debugName = _otherId.debugName;
#endif
		id = _otherId.id;
	}

	void Set( const char* _name )
	{
		CRY_ASSERT(_name);
#if defined(_DEBUG)
		debugName = _name;
#endif
		id = HashString(_name);
	}

	ILINE bool operator == (const CryHashStringId& rhs) const
	{
		return (id == rhs.id);
	}

	ILINE bool operator != (const CryHashStringId& rhs) const
	{
		return (id != rhs.id);
	}

	ILINE bool operator <= (const CryHashStringId& rhs) const
	{
		return (id <= rhs.id);
	}

	ILINE bool operator < (const CryHashStringId& rhs) const
	{
		return (id < rhs.id);
	}

	ILINE bool operator >= (const CryHashStringId& rhs) const
	{
		return (id >= rhs.id);
	}

	ILINE bool operator > (const CryHashStringId& rhs) const
	{
		return (id > rhs.id);
	}

	void GetMemoryUsage(ICrySizer* pSizer) const
	{
#if defined(_DEBUG)
		pSizer->AddObject(debugName);
#endif
	}

	const char* GetDebugName() const
	{
#if defined(_DEBUG)
		return debugName.c_str();
#else
		return "";
#endif
	}

	//This is useful for look ups in debug, so we don't allocate strings
	static CryHashStringId GetIdForName(const char* _name);

#if defined(_DEBUG)
	string debugName;
#endif
	CryHash id;
};

inline uint64 GuidComponent()
{
	auto least = cry_rand32();
	auto most = cry_rand32();

	return (uint64)most << 32 | least;
}

#endif // __CRY_HASH_UTIL_H__
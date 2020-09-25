#pragma once
#include "Core.h"
#include "Types.h"

namespace StepWay
{
	typedef uint64 UID;
	class LocalUIDGenerator
	{
	public:
		LocalUIDGenerator() {};
		LocalUIDGenerator(LocalUIDGenerator&) = delete;
		LocalUIDGenerator(LocalUIDGenerator&&) = delete;
		
		UID NextID() { return m_current++; };

	private:
		uint64 m_current = 1;
	};

	class GUID
	{
	public:
		static UID NextID() { return m_gen.NextID(); };
	private:
		static LocalUIDGenerator m_gen;
	};
}
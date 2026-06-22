#pragma once

#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

namespace Memory
{
	inline void**& GetVTable(void* instance, uintptr_t offset = 0)
	{
		return *reinterpret_cast<void***>((uintptr_t)instance + offset);
	}

	inline const void** GetVTable(const void* instance, uintptr_t offset = 0)
	{
		return *reinterpret_cast<const void***>((uintptr_t)instance + offset);
	}

	template<typename Fn>
	inline Fn GetVFunc(const void* instance, int index, uintptr_t offset = 0)
	{
		return reinterpret_cast<Fn>(GetVTable(instance, offset)[index]);
	}

	template<typename T>
	inline T* ExtractAddressFromFunc(uint8_t* funcAddress, uint8_t instructionOffset, uint32_t displacement)
	{
		uint8_t* pInstruction = funcAddress + instructionOffset;
		uint32_t displ = *reinterpret_cast<uint32_t*>(pInstruction + displacement);

		return *reinterpret_cast<T**>(pInstruction + 7 + displ);
	}
}

#endif
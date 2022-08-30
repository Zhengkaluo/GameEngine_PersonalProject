#pragma once

#include <string>

#include "KaluoEngine/Core.h"

namespace KaluoEngine {
	
	//will evnetually different type of textures
	//pure abstract class
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		
		virtual void Bind(uint32_t slot= 0) const = 0;
	};

	//still abstract
	class Texture2D : public Texture
	{
	public:
		//create base on path
		static Ref<Texture2D> Create(const std::string& path);
	};
}
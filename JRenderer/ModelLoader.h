#pragma once
#include <sstream>

namespace JRenderer
{
	class ModelLoader_handmade
	{
	private:
		enum HandMadeType {
			Cube,
			Sphere,
		};
	public:
		static bool Load(std::stringstream& ss)
		{
			int type;
			ss >> type;
			return true;
		}
	};

	class ModelLoader
	{
	public:
		static bool Load(std::stringstream& ss)
		{
			return ModelLoader_handmade::Load(ss);
		}
	};
}
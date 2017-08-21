#pragma once
#include <sstream>
#include "BaseModel.h"

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
		static bool Load(std::stringstream& ss, VertexBuffer& vb, IndexBuffer& ib)
		{
			int type;
			ss >> type;
			return true;
		}
	};

	class ModelLoader
	{
	public:
		static bool Load(std::stringstream& ss, VertexBuffer& vb, IndexBuffer& ib)
		{
			return ModelLoader_handmade::Load(ss, vb, ib);
		}
	};
}
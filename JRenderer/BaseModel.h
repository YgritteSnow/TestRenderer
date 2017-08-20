#pragma once
#include <sstream>
#include "JMath.h"

namespace JRenderer
{
	class BaseModel
	{
	public:
		BaseModel() {};
		~BaseModel() {};

		void Render() {};
		bool Load(std::stringstream& ss);

	private:
		WorldPos m_pos;
	};
}
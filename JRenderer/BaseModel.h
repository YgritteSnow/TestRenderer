#pragma once
#include <sstream>
#include "JMath.h"
#include <vector>
#include <Windows.h>

namespace JRenderer
{
	struct VertexBlob
	{
		int* m_stride;
		float* m_data;
		std::string* m_name;
		int m_size;
	};
	typedef std::vector<VertexBlob> VertexBuffer;
	typedef std::vector<DWORD> IndexBuffer;

	class BaseModel
	{
	public:
		BaseModel() {};
		~BaseModel() {};

		void Render();
		bool Load(std::stringstream& ss);

	private:
		WorldPos m_pos;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
	};
}
#include "BaseModel.h"
#include "ModelLoader.h"

namespace JRenderer
{
	bool BaseModel::Load(std::stringstream& ss)
	{
		return ModelLoader::Load(ss);
	}
}
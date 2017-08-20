#pragma once
#include <vector>

namespace JRenderer
{
	class BaseModel;
	class BaseScene
	{
	public:
		BaseScene() {};
		~BaseScene() {};

		void Render();
		void Load(std::string filename);
	protected:
		std::vector<BaseModel*> m_vec_models;
	};

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		static bool Init() { if (!s_instance) { s_instance = new SceneManager(); } return s_instance != nullptr; }
		static void Uninit() { if (s_instance) { delete s_instance; s_instance = nullptr; } }
		static SceneManager* Instance() { return s_instance; }

		void Render();
	private:
		static SceneManager* s_instance;
		std::vector<BaseScene*> m_vec_scenes;
	};
}
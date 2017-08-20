#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "Interface.h"
#include "BaseScene.h"
#include "Device.h"
#include "BaseModel.h"

namespace JRenderer
{
	void Render()
	{
		float color[4] = { 1.0f, 0.f, 0.f, 1.f };
		JDevice::pImmediateContext->ClearRenderTargetView(JDevice::pRenderTargetView, color);
		SceneManager::Instance()->Render();
		JDevice::pSwapChain->Present(0, 0);
	}

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	SceneManager::SceneManager()
	{
		BaseScene* bs = new BaseScene();
		m_vec_scenes.push_back(bs);
	}

	SceneManager::~SceneManager()
	{
		for_each(m_vec_scenes.begin(), m_vec_scenes.end(), [&](auto& x) {
			delete x;
		});
		m_vec_scenes.clear();
	}

	void SceneManager::Render()
	{
		for_each(m_vec_scenes.begin(), m_vec_scenes.end(), [&](auto& x) {
			x->Render();
		});
		JDevice::pSwapChain->Present(0, 0);
	}

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	void BaseScene::Render()
	{
		float color[4] = { 1.0f, 0.f, 0.f, 1.f };
		JDevice::pImmediateContext->ClearRenderTargetView(JDevice::pRenderTargetView, color);
		for_each(m_vec_models.begin(), m_vec_models.end(), [&](auto& x) {
			x->Render();
		});
	}
	
	void BaseScene::Load(std::string filename)
	{
		std::fstream file(filename.c_str(), std::ios::in);
		if (!file.is_open())
		{
			MessageBox(NULL, L"File Load failed", 0, 0);
			return;
		}

		char buffer[256];
		while (!file.eof())
		{
			file.getline(buffer, 100);
			std::stringstream ss = std::stringstream(buffer);
			BaseModel* bm = new BaseModel();
			if (bm->Load(ss))
			{
				m_vec_models.push_back(bm);
			}
			else
			{
				delete bm;
			}
		}
	}

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	SceneManager* SceneManager::s_instance = nullptr;
}
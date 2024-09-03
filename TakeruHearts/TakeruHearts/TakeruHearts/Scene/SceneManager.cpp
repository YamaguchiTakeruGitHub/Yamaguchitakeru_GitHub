#include "SceneManager.h"

SceneManager::SceneManager(std::unique_ptr<SceneBase> initialScene)
	: currentScene(std::move(initialScene))//initialSceneにcurrentSceneの所有権を渡す
	, count(0)
{
	if (currentScene)
	{
		currentScene->Init();
	}
}

SceneManager::~SceneManager()
{

	currentScene.reset();//CurrentSceneのリソースを解放
}

void SceneManager::SetScene(std::unique_ptr<SceneBase> scene)
{
	if (currentScene)
	{
		currentScene->End();
	}
	currentScene = std::move(scene);
	if (currentScene)
	{
		currentScene->Init();
	}
}

void SceneManager::HondleInput()
{
	if (count == 10)
	{
		SetScene(std::make_unique<SceneTitle>());//同じく
	}

	if (CheckHitKey(KEY_INPUT_T) != 0)
	{
		SetScene(std::make_unique<SceneGame>());//新しいインスタンスを生成しunique_ptrに渡す
	}
	if (CheckHitKey(KEY_INPUT_U) != 0)
	{
		SetScene(std::make_unique<SceneTitle>());//同じく
	}
	if (CheckHitKey(KEY_INPUT_R) != 0)
	{
		SetScene(std::make_unique<SceneResult>());//同じく
	}

}

void SceneManager::Init()
{

	if (currentScene)
	{
		currentScene->Init();
	}
}

void SceneManager::Update()
{
	count++;
	if (count == 10)
	{
		count = 10;
	}

	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Draw()
{

	if (currentScene)
	{
		currentScene->Draw();
	}
}

void SceneManager::End()
{

	if (currentScene)
	{
		currentScene->End();
	}
}

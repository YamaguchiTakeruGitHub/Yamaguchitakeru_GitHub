#pragma once

namespace Tag
{
	enum class Scene
	{
		Title,
		Game,
		Result,
#if _DEBUG
		SceneBase,
		SceneManager
#endif
	};

	enum class UI
	{
		UI,
		Button,
		Image
	};

	enum class Map
	{
		TutorialMap
	};

	enum class obj
	{
		Player,
		Enemy,
	};

}
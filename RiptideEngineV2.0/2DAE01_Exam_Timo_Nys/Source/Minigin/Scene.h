#pragma once
#include "SceneManager.h"
#include "GameObject.h"

	class SceneObject;
	class Scene
	{
		
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		std::string GetName() { return mName; };
		const std::vector<std::shared_ptr<GameObject>> GetObjects() const { return mObjects; }

		virtual void Init() = 0;
		virtual void Update(float deltaTime);
		virtual void Render() const;
		virtual void SceneRender()const;
		virtual void SceneUpdate(float deltaTime) = 0;
		
		explicit Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string mName{};
		std::vector <std::shared_ptr<GameObject>> mObjects{};

		static unsigned int idCounter; 
	};


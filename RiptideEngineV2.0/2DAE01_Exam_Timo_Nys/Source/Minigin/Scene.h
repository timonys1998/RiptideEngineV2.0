#pragma once
#include "SceneManager.h"
#include "GameObject.h"

	class SceneObject;
	class Scene
	{
		
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove(const std::shared_ptr<GameObject>& object);

		std::string GetName() { return m_Name; };
		const std::vector<std::shared_ptr<GameObject>> GetObjects() const { return m_spObjects; }


		void Update(float deltaTime);
		
		explicit Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string m_Name{};
		std::vector <std::shared_ptr<GameObject>> m_spObjects{};

		static unsigned int idCounter; 
	};


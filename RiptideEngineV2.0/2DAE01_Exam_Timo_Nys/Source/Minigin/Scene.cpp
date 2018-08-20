#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "algorithm"

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_spObjects.push_back(object);
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	m_spObjects.erase(std::remove(m_spObjects.begin(), m_spObjects.end(), object), m_spObjects.end());
}

void Scene::Update(float deltaTime)
{
	for(auto gameObject : m_spObjects)
	{
		if(gameObject)
			gameObject->Update(deltaTime);
	}
}










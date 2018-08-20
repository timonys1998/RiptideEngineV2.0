#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "BaseComponent.h"
#include "TextureComponent.h"
#include "algorithm"
#include "RenderComponent.h"
#include "InputComponent.h"


GameObject::~GameObject() = default;

std::shared_ptr<GameObject> GameObject::Instantiate(const FLOAT2& position)
{
	std::shared_ptr<GameObject> gameobj = std::make_shared<GameObject>();
	gameobj->AddComponent(std::make_shared<Transform>(position));
	return gameobj;
}



void GameObject::Update(float deltaTime)
{
	for(auto c : m_spComponents)
	{
		c->Update(deltaTime);
	}
	
}


void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	if(typeid(component) == typeid(Transform))
	{
		std::cout << "GameObject::AddComponent >> Cannot add transform component, this is done at initialization of the object \n";
		return;
	}
	else if(typeid(component) == typeid(RenderComponent) && HasComponent<RenderComponent>())
	{
		std::cout << "GameObject::AddComponent >> Cannot add more than 1 render component!\n";
		return;
	}
	
	m_spComponents.push_back(component);
	component->m_wpOwner = shared_from_this();
}



void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{

	m_spComponents.erase(std::remove(m_spComponents.begin(), m_spComponents.end(), component), m_spComponents.end());
}





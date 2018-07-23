#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TextureComponent.h"
#include "algorithm"

GameObject::GameObject()
{
	mComponents.push_back(mTransform);
}

void GameObject::Init()
{
	
}


GameObject::~GameObject() = default;

void GameObject::Update(float deltaTime)
{
	for(auto c : mComponents)
	{
		c->Update(deltaTime);
	}
	for(auto c : mChildren)
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
	for(auto comp : mComponents )
	{
		if(typeid(component) == typeid(comp))
		{
			std::cout << "GameObject::AddComponent >> Cannot add a component already on the gameobject \n";
		}
	}
	mComponents.push_back(component);
	component->mOwner = shared_from_this();
}



void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{

	mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), component), mComponents.end());
}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	mChildren.push_back(child);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), child), mChildren.end());
}



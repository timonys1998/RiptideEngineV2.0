#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : mName(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	mObjects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
		gameObject->ObjectUpdate(deltaTime);
	}
	SceneUpdate(deltaTime);
}

void Scene::Render() const
{
	for (const auto gameObject : GetObjects())
	{
		const std::shared_ptr<RenderComponent> temp = gameObject->GetComponent<RenderComponent>();
		if (temp != nullptr && temp->ShouldRender() && gameObject->GetComponent<RenderComponent>()->GetTextureToRender() != nullptr)
		{
			temp->RenderTexture();
		}
		for(const auto child : gameObject->GetChildren())
		{
			const std::shared_ptr<RenderComponent> temp1 = child->GetComponent<RenderComponent>();
			if (temp1 != nullptr && temp1->ShouldRender() && temp1->GetTextureToRender() != nullptr)
			{
				temp1->RenderTexture();
			}

		}
	}
}

void Scene::SceneRender() const
{
}




#pragma once
#include <memory>

#include "Transform.h"

class BaseComponent;


	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		virtual void Init();
		void Update(float deltaTime);
		virtual void ObjectUpdate(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);
		void AddChild(std::shared_ptr<GameObject> child);
		void RemoveChild(std::shared_ptr<GameObject> child);
		const std::vector<std::shared_ptr<GameObject>> GetChildren() const { return mChildren; }

		explicit GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		
		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			for (const auto comp : mComponents)
			{
				//We dont check for nullptr cause the component should not be in the vector if its nullptr / We only check if its the type
				if (typeid(*comp) == typeid(T))
				{
					std::cout << "Component found \n";
					return std::static_pointer_cast<T>(comp);
				}
			}
			return nullptr;
		}

		template<class T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		

	private:
		std::shared_ptr<Transform> mTransform = std::make_shared<Transform>();
		std::vector<std::shared_ptr<BaseComponent>> mComponents;
		std::vector<std::shared_ptr<GameObject>> mChildren;
	};

#pragma once

class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		virtual void Update(float deltaTime) = 0;

		void SetOwner(std::shared_ptr<GameObject>owner) { mOwner = owner; }
		std::shared_ptr<GameObject> GetOwner()const { return mOwner.lock(); }

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		friend class GameObject;
		std::weak_ptr<GameObject> mOwner;
	};



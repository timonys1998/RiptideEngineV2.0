#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Scene.h"

class UISystem final : public Singleton<UISystem>
{
public:
	void MakeMenu(std::shared_ptr<Scene> menu);//This will create the main menu of our bombergame and can be called in our InitScenes of Game class
	void MakeUI(std::shared_ptr<Scene> game,GameMode mode);//This will create our bomberman UI but will be different depending on gamemode
	void UpdateFPSCounter()const;
	void ChangeBombCapacity(int playerID,int value)const;
	void ChangeHealthValue(int playerID, int value)const;
private:
	std::shared_ptr<GameObject> m_spMainMenu;
	
	std::shared_ptr<GameObject> m_spLivesP1;
	std::shared_ptr<GameObject> m_spLivesP2;
	std::shared_ptr<GameObject> m_spBombsAvailableP1;
	std::shared_ptr<GameObject> m_spBombsAvailableP2;
	std::shared_ptr<GameObject> m_spFpsCounter;
};


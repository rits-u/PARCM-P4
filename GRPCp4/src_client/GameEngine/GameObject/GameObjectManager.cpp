#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::get()
{
    return sharedInstance;
}

void GameObjectManager::initialize()
{
    sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
    if (!GameObjectManager::sharedInstance)
        return;

    delete GameObjectManager::sharedInstance;
}

GameObject* GameObjectManager::findObjectByName(string name)
{
    int index = 0;
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->getName() == name) {
            index = i;
            break;
        }
    }
    return this->gameObjectList[index];
}

std::vector<GameObject*> GameObjectManager::getAllObjects()
{
    return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
    int activeObjs = 0;
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->isEnabled())
            activeObjs++;
    }
    return activeObjs;
}

void GameObjectManager::renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, SwapChainPtr sc)
{
    RenderSystem* renderSystem = GraphicsEngine::get()->getRenderSystem();
    DeviceContextPtr context = renderSystem->getImmediateDeviceContext();

    int index = 0;

    for (Camera* cam : cameras) {
        if (cam->cullingMask & Layer::DEBUG) {
            context->setRasterizerState(renderSystem->getWireframeState());
            context->clearDepth(sc);
        }
        else {
            context->setRasterizerState(renderSystem->getSolidState());
        }

        for (GameObject* obj : this->gameObjectList) {
            if ((cam->cullingMask & obj->getLayer()) != 0 && obj->isEnabled()) {
                if (obj != NULL) {
                    ComponentList components = obj->getComponents();
                    for (int i = 0; i < components.size(); i++) {
                        if (components[i]->type == ComponentType::PHYSICS) {
             /*               Component* p6 = (PhysicsComponent*)components[i];
                            p6->update();*/
                        }
                        else if (components[i]->type == ComponentType::RENDERER) {
                            Renderer* renderer = (Renderer*)components[i];
                            renderer->update(obj->getConstant(), width, height, index);
                            if (cam->isEnabled())
                                renderer->draw(); 
                               
                        }
                    }
                    

                }
            }
        }

        index++;
    }
}

void GameObjectManager::addObject(GameObject* gameObject)
{
    this->gameObjectList.push_back(gameObject);
    this->gameObjectTable[gameObject->getName()] = gameObject;
}

void GameObjectManager::deleteObject(GameObject* gameObject)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i] == gameObject) {
            std::cout << "Deleted " << gameObject->getName() << std::endl;
            if (dynamic_cast<InputListener*>(this->gameObjectList[i]))
                InputSystem::get()->removeListener((InputListener*)this->gameObjectList[i]);
            ComponentList& components = this->gameObjectList[i]->getComponents();
            for (Component* c : components) {
                if (c) {
                    delete c;
                    c = nullptr;
                }
            }
            components.clear();

            delete this->gameObjectList[i];
            this->gameObjectList.erase(this->gameObjectList.begin() + i);
            break;
        }
    }
}

void GameObjectManager::deleteObjectByName(string name)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->getName() == name) {
            delete this->gameObjectList[i];
            this->gameObjectList.erase(this->gameObjectList.begin() + i);
            break;
        }
    }
}

void GameObjectManager::clearSelectedObject()
{
    this->selectedObject = nullptr;
}

void GameObjectManager::setSelectedObject(string name)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i]->getName() == name) {
            this->selectedObject = this->gameObjectList[i];
            break;
        }
    }
}

void GameObjectManager::setSelectedObject(GameObject* gameObject)
{
    for (int i = 0; i < this->gameObjectList.size(); i++) {
        if (this->gameObjectList[i] == gameObject) {
            this->selectedObject = this->gameObjectList[i];
            break;
        }
    }
}

GameObject* GameObjectManager::getSelectedObject()
{
    return this->selectedObject;
}

string GameObjectManager::adjustName(string name)
{
    string adjustedName;
    int count = 0;
    bool rootExists = true;


    for (GameObject* obj : this->gameObjectList) {
        string temp = obj->getName();
        if (temp.find(name) != std::string::npos) {
            count++;
        }
    }

    if (count > 0)
        adjustedName = name + " " + to_string(count);
    else
        adjustedName = name;

    return adjustedName;
}

void GameObjectManager::processDeletions()
{
    for (int i = 0; i < this->pendingDeletion.size(); i++) {
        if (InputListener* listener = dynamic_cast<InputListener*>(this->pendingDeletion[i])) {
            InputSystem::get()->removeListener(listener);
        }
        ComponentList& components = this->pendingDeletion[i]->getComponents();
        for (Component* c : components) {
            delete c;
        }
        components.clear();

        delete this->pendingDeletion[i];
        this->gameObjectList.erase(this->gameObjectList.begin() + i);
        this->pendingDeletion.clear();
    }
}


GameObjectManager::GameObjectManager()
{
    this->selectedObject = nullptr;
    this->gameObjectList.clear();
    this->gameObjectTable.clear();
}

GameObjectManager::~GameObjectManager()
{
   for (int i = 0; i < this->gameObjectList.size(); i++) {
       delete this->gameObjectList[i];
   }

    gameObjectList.clear();
    gameObjectTable.clear();
    selectedObject = nullptr;

    GameObjectManager::sharedInstance = nullptr;
}

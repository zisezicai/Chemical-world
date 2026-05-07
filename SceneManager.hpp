#include <unordered_map>
#include <string>
#include "Scene.hpp"
#include "OutPutManager.hpp"
class SceneManager {
private:
    Scene* currentScene;
	std::unordered_map<std::string, Scene*> scenes;
public:
    SceneManager():currentScene(nullptr){}
    void loadScene(std::string name) {
        OutPutManager::screenReplace("");
        if (scenes.find(name) != scenes.end()) {
            if (currentScene != nullptr) {
                currentScene->free();
            }
            currentScene = scenes[name];
            currentScene->setup();
        }
    }
    bool update(){
        currentScene->update();
        if(currentScene->shouldClose()) return true;
        if(currentScene->NextScene()!="") loadScene(currentScene->NextScene());
        return false;
    }
    ~SceneManager() {
        for (auto& scene : scenes) {
            delete scene.second;
        }
    }
    void addScene(Scene* scene) {
        scenes[scene->Name()] = scene;
        //debugLog("Added Scene\n");
        //debugLog(scene->Name()+"\n");
    }
};
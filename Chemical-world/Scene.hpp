#pragma once
#define SCENE_FLASH_TIME 60
#include <string>
#include <iostream>



class Scene {
protected:
	std::string sceneName;
	int frameCount;
	double frameDelta;
	bool shouldExit;
	std::string nextScene;
public:
	Scene(std::string name):sceneName(name),shouldExit(false),frameCount(0),frameDelta(1/SCENE_FLASH_TIME){}
	void virtual setup() {
		nextScene = "";
		frameCount = 0;
	}
	void virtual update() {
        frameCount++;
	}
	void virtual free(){}
	void virtual gameOver(){}
	~Scene() {
		gameOver();
	}
	void closeApplication() {
		shouldExit = true;
	}
	bool shouldClose() {
		return shouldExit;
	}
	void loadScene(std::string name) {
		nextScene = name;
	}
	std::string NextScene() {
		return nextScene;
	}
	std::string Name() {
		return sceneName;
	}
};













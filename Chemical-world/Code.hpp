#pragma once
#include "StatusManager.hpp"
#include "InputManager.hpp"
#include "OutPutManager.hpp"
#include "SaveManager.hpp"
#include <iostream>
using namespace std;
class GameScene :public Scene {
public:
	static SaveManager player;
	GameScene(string name) :Scene(name) {}
	void update() override {
		Scene::update();
		cout << "Please type 1 to exit.Game is Still in development, so you can only exit for now.\n";
		string input = InputManager::inputText();
		if (input == "1") {
			loadScene("Start");
		}
	}
};
//test
class StartScene : public Scene {
public:
	StartScene(string name) :Scene(name) {}
	//Test
	void setup() override {
		Scene::setup();
	}
	void update() override {
		Scene::update();
		OutPutManager::screenReplace("");
		OutPutManager::screenReplace(std::u8string(u8R"(
			-------------------------------------------------------------------
			|                 chemical world - main menu                      |
			-------------------------------------------------------------------
)"));//string存不了u8，呃呃呃，VS用不了u8R，呃呃呃
		pair<vector<string>, vector<function<void()>>> p = { vector<string>{"New Game", "Load Save", "Set", "Exit"} ,{
		  [this]() {
			loadScene("Register");
		},[this]() {
			vector<string> allSave = SaveManager::getAllSaveNames();
			if (allSave.empty()) {
				OutPutManager::showMessage("No save found!");
				OutPutManager::delay(1000);
				return;
			}
			int index=InputManager::selectList(allSave);
			GameScene::player = SaveManager::load(SaveManager::savePath + allSave[index]);
			loadScene("Game");
		},[this]() {
			loadScene("Set");
		},[this]() {
			closeApplication();
		}} };
		int index = InputManager::selectList(p.first);
		p.second[index]();
	}
};
class RegisterScene:public Scene{
private:
	pair<SaveManager,bool> RegisterPlayer(){//TODO:
		string playerName;
		cout << "Please type your user name in:";
		cin >> playerName;
		return { SaveManager::CreateNewSave(playerName),true };
	}
public:
	RegisterScene(string name) :Scene(name) {}
	void setup() override {
		Scene::setup();
	}
	void update() {
		Scene::update();
		auto [player,finish]=RegisterPlayer();
		if (finish) {
			GameScene::player = player;
			player.save();
			OutPutManager::showMessage("Registration successful!");
			OutPutManager::delay(1000);
			loadScene("Game");
		}
	}
};
class SetScene :public Scene {
private:
	static vector<string> split(string s) {
		vector<string> res{""};
		for (int i = 0;i < s.length();i++) {
			if (s[i] == ' ') res.push_back("");
			else res.back() += s[i];
		}
		return res;
	}
public:
	SetScene(string name):Scene(name){}
	void update() override {
		Scene::update();
		//test
		system("cls");
		SetManager::listAllSet();
		string s=InputManager::getInstruction();
		vector<string> instruction = split(s);
		if (instruction[0] == "exit") {
			loadScene("Start");
			return;
		}
		if (instruction.size() <= 1) {
			cout << "fail\n";
		}
		else {
			if (SetManager::setItem(instruction[0], instruction[1])) {
				cout << "fail\n";
			}
			else {
				OutPutManager::clearScreen();
			}
		}
	}
};
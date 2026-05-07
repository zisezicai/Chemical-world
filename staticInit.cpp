#include "SaveManager.hpp"
#include "Code.hpp"
std::unordered_map<std::string, SaveManager> SaveManager::alreadyLoads;
std::string SaveManager::logPath = "log.txt";
std::string SaveManager::savePath = "saves";
SaveManager GameScene::player;
std::string SetManager::setPath = "set.txt";
std::map<std::string, std::string> SetManager::settings;
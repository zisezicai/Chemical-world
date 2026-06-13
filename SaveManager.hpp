#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <vector>
#include <map>
#include <functional>
#include "OutPutManager.hpp"
//namespace fs = std::filesystem;再三考虑，为了防止宏污染，只能受着了:(
class SaveManager {//TODO:由于游戏设计的东西会变多，所以以后慢慢写
private:
	static std::unordered_map<std::string, SaveManager> alreadyLoads;
	std::string name;
public:
	static std::string savePath;
	static std::string logPath;
	static void sureExistsDirectories(const std::filesystem::path& path) {
		if (!std::filesystem::exists(path)) {
			std::filesystem::create_directories(path);
		}
	}
	static void sureExistsFile(const std::filesystem::path& path) {
		if (!std::filesystem::exists(path)) {
			std::ofstream(path).close();
		}
	}
	void save() const {
		try {
			std::string finalPath = savePath +"\\" + name;
			sureExistsDirectories((std::filesystem::path)savePath);
			std::ofstream file(finalPath);
			file << "name:" << name << std::endl;//先简单的试一下存档，以后慢慢写
			// TODO: Write save data to file
			file.close();
		}
		catch (const std::exception&) {
			std::ofstream file(logPath, std::ios::app);
			file << "error:can't save file" << std::endl;
			file.close();
		}
	}
	static SaveManager load(const std::string& path) {
		std::ifstream file(path);
		SaveManager save;
		save.name = "abaaba";
		if (alreadyLoads.find(save.name) == alreadyLoads.end()) {
			alreadyLoads[save.name] = save;
		}
		file.close();
		return save;//暂时先返回空
	}
	static SaveManager CreateNewSave(std::string name) {
		SaveManager save;
		save.name = name;
		return save;
	}
	static void SaveAll() {//必须及时调用，否则会丢失数据
		for (auto& i : alreadyLoads) {
			i.second.save();
		}
	}
	static std::vector<std::string> getAllSaveNames() {
		std::vector<std::string> names;
		try {
			for (auto& i : std::filesystem::directory_iterator(savePath)) {
				names.push_back(i.path().filename().string());
			}
		}
		catch (const std::exception&) {
			std::ofstream file(logPath, std::ios::app);
			file << "error:can't open save direction" << std::endl;
			file.close();
		}
		return names;
	}
};
class SetManager {
private://这个不能unordered了
	static std::map<std::string, std::string> settings;
public:
	static std::string setPath;
	static void saveSet() {
		std::ofstream file(setPath);

		file.close();
	}
	static void listAllSet() {
		for (auto& i : settings) {
			OutPutManager::showSetItem(i);
		}
	}
	static void loadSet() {
		SaveManager::sureExistsFile((std::filesystem::path)setPath);
	}
	static bool setItem(std::string key, std::string value) {
		if (settings.find(key) == settings.end()) {
			return false;
		}
		settings[key] = value;
		return true;
	}
	static void addItem(std::string key,std::string defaultValue){
		settings.insert({ key, defaultValue });
	}
};
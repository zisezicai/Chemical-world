#pragma once
//等发布了就把这个宏改为空
#define debugLog(s) OutPutManager::showMessage(s);
#include <iostream>
#include <string>
#include <vector>
#include <thread>
class OutPutManager {//提供输出的封装，将游戏逻辑个输出分离，为之后脱离控制台打下基础
public:
    static std::string toString(const std::u8string& u8s) {
        return std::string(u8s.begin(),u8s.end());
    }
    static void clearScreen() {
        system("cls");
    }
    static void showMessage(std::string Message) {
        //未来的想法就是一个圆角透明黑框框显示文本
        std::cout << Message;//先放着，后续版本再说吧
        //或许可以这样
        /*
		#if defined(_WIN32) || defined(_WIN64)//其他平台真不会了，不过以后也不会这么简陋
		    MessageBoxA(NULL, Message.c_str(), "Message", MB_OK | MB_ICONINFORMATION);
		#endif
        */
    }
    static inline void showMessage(std::u8string u8s) {
        showMessage(toString(u8s));
    }
    static void screenReplace(std::string image) {
        clearScreen();
        //未来需要切换图片或者一些炫酷的动画效果，先放着，后续版本再说吧
        std::cout << image;
    }
    static inline void screenReplace(std::u8string u8s){
        screenReplace(toString(u8s));
    }
    //这个为现在版本的开场白
    static void showIcon(std::string icon) {
        clearScreen();
        std::cout << icon;
    }
    static inline void showIcon(std::u8string icon) {
        showIcon(toString(icon));
    }
    static void showList(std::vector<std::string> list) {
        for(std::string s:list)
            std::cout<<s<<std::endl;
    }
    static inline void showList(std::vector<std::u8string> list) {
        for (std::u8string s : list)
            std::cout << toString(s) << std::endl;
    }
    static void showSetItem(std::pair<std::string,std::string> p) {
        std::cout<<p.first<<": "<<p.second<<std::endl;
	}
    static inline void delay(long long ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
	class Voice {//未来的想法是一个语音系统，先放着，后续版本再说吧
    
    };
};
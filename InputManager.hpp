#pragma once
#include <string>
#include <iostream>
#include <vector>
class InputManager {
public:
	static std::string inputText() {
		std::string text;
		std::cin >> text;
		return text;
	}
	static int selectList(std::vector<std::string> list) {//多项选择一个最后返回选项的索引
		for (int i = 0; i < list.size(); i++) {
            std::cout << i + 1 << ": " << list[i] << std::endl;
		}
		select:
        std::cout << "Choice: ";
		std::string select;
		std::cin >> select;
		if (select.size()!=1 || select[0]<'1' || select[0]>'0' + list.size()) {
			std::cout << "Please type again" << std::endl;
			goto select;
		}
        return select[0] - '1';
	}
	static std::string getInstruction() {
		std::string res;
		std::getline(std::cin, res);
		return res;
	}
};
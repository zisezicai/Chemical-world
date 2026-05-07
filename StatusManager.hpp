#pragma once
#include "Scene.hpp"
#include <unordered_map>
#include <functional>
class StatusManager : public Scene{
public:
    struct Status{
        std::function<void()> update;
        struct Transition {
            std::function<bool()> requestCondition;
            std::string next;
        };
        std::vector<Transition> next;
        void addNext(std::function<bool()> requestCondition, std::string next){
            this->next.push_back({requestCondition,next});
        }
    };
private:
    std::string currentStatus;
    std::unordered_map<std::string,Status> status;
public:
    StatusManager(std::string name,std::string startStatus):Scene(name),currentStatus(startStatus){}
    void setup() override {
        Scene::setup();
    }
    void update() override {
        Scene::update();
        if(status.find(currentStatus)!=status.end())
            status[currentStatus].update();
        flushImmediate();
    }
protected:
    void flushImmediate() {
        for (auto& next : status[currentStatus].next) {
            if (next.requestCondition()) {
                currentStatus = next.next;
                break;
            }
        }
    }
    void addStatus(std::string name, Status status){
        this->status.insert({name,status});
    }
    void addTransition(std::string status, std::function<bool()> requestCondition, std::string next){
        this->status[status].addNext(requestCondition,next);
    }
};
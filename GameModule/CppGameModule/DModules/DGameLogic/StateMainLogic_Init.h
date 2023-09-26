#pragma once
#include "FSM.h"
#include "../DModules/DNetwork/Http/HttpManager.h"
#include "StateMainLogic_Run.h"
#include <exception>

class StateMainLogic_Init : public IState
{
public:
    DEFINE_TYPE("state.main.logic.init")
public:
    virtual void OnEnter() override {
        DLOG_INFO("OnEnter");
        Init();
        StateController* controller = GetController();
        controller->SetState(StateMainLogic_Run::GetClassType());
    };
    virtual void OnExit() override {
    }
    virtual void OnUpdate() override {
    }

private:
    void Init()
    {
        DLOG_INFO("Server initalize start\n");
        StartHttpHost();
    }


    void StartHttpHost()
    {
        DLOG_INFO("StartHttpHost\n");
        try {
            DHttp::HttpServer* http_server = new DHttp::HttpServer();
            http_server->host();
            DLOG_INFO("StartHttpHost End\n");
        }
        catch(std::exception const& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    }
};
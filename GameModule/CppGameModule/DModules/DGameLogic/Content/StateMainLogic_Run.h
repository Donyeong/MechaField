#pragma once
#include "FSM.h"

class StateMainLogic_Run : public IState
{
public:
    DEFINE_TYPE("state.main.logic.run")
public:
    virtual void OnEnter() override {
        Init();
        StateController* controller = GetController();
    };
    virtual void OnExit() override {
    }
    virtual void OnUpdate() override {
    }

private:
    void Init()
    {
        DLOG_INFO("Server Init\n");
    }
};
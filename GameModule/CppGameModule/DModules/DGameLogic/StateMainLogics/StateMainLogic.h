#pragma once
#include "../FSM.h"
#include "StateMainLogic_Init.h"
#include "StateMainLogic_Run.h"
#include <iostream>




class StateControllerMainLogic : public StateController
{
public:
    StateControllerMainLogic() : StateController()
    {
        DLOG_INFO("StateMainLogic_Init : CREATE\n");
        
    }

protected:
    virtual void BuildStates() override
    {
        std::cout << "StateMainLogic_Init : BuildStates" << std::endl;
        AddState(new StateMainLogic_Init());
        AddState(new StateMainLogic_Run());
        SetState(StateMainLogic_Init::GetClassType());
        std::cout << "StateMainLogic_Init : BuildStates end" << std::endl;
    }
};
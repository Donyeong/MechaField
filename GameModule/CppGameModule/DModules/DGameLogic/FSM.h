#pragma once
#include "../DModules/DGenericLib/HashMap.h"
#include "../DModules/DGenericLib/String.h"
#include "../DModules/DUtil/Debug.h"

#define DEFINE_TYPE(x) DGeneric::ConstString GetType() const override\
    {\
        return GetClassType();\
    }\
    static DGeneric::ConstString GetClassType()\
    {\
        return #x;\
    }

class StateController;

class IState
{
public:
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void OnUpdate() = 0;
    virtual DGeneric::ConstString GetType() const = 0;
    StateController* GetController()
    {
        return m_controller;
    }
    void SetController(StateController* _controller)
    {
        m_controller = _controller;
    }
private:
    StateController* m_controller;
};

class StateController
{
    typedef DGeneric::String StateKey;
public:
    StateController()
        : m_current_state(nullptr)
        , m_prev_state(nullptr)
    {
    }

    void Init()
    {
        BuildStates();
    }

    void SetState(StateKey _state_key)
    {
        if(nullptr != m_current_state)
        {
            m_current_state->OnExit();
        }
        IState* next_state = GetState(_state_key);
        m_prev_state = m_current_state;
        m_current_state = next_state;
        next_state->OnEnter();
    }

    const IState& GetCurrentState() {
        return *m_current_state;
    }

    const IState& GetPrevState() {
        return *m_prev_state;
    }

    void Update() {
        m_current_state->OnUpdate();
    }

protected:
    void AddState(IState* _state)
    {
        DASSERT(nullptr != _state);
        _state->SetController(this);
        m_map_states.insert_pair(_state->GetType(), _state);
    }
protected:
    DGeneric::HashMap<StateKey ,IState*> m_map_states;
    virtual void BuildStates() = 0;
private:
    IState* GetState(const StateKey& _state_key)
    {
        DASSERT(m_map_states.contain(_state_key));
        return m_map_states[_state_key];
    }
private:
    IState* m_prev_state;
    IState* m_current_state;
};


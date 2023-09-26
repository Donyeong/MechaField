#pragma once
#include "Framework/Component.h"

namespace DLogic {
    class SyncronizeObject :
        public Component
    {

    public:
        int getNetworkObjectId();
        virtual void OnAwake();
        virtual void OnStart();
        virtual void OnUpdate();
    private:
        int network_object_id;

    };
}


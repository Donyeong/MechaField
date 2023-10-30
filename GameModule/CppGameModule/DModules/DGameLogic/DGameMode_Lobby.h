#pragma once
#include "DGameMode.h"
namespace DLogic {
    class DGameMode_Lobby :
        public DGameMode
    {
        OBJECT_POOLING(DGameMode_Lobby)
    public:
    public:
        virtual void OnLoad();
    };
}

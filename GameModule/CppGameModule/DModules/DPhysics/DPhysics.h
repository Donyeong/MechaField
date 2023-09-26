#pragma once
#ifdef DPHYSICS_EXPORTS
#define MYDLL_DECLSPEC __declspec(dllexport)
#else
#define MYDLL_DECLSPEC __declspec(dllimport)
#endif

#include <PxPhysicsAPI.h>
#include <vector>

class MYDLL_DECLSPEC DPhysics
{

public:
    void Init();
    void Update(float _delta_time);
private:
    void BuildEnvironment();
    void BuildGeometry();

    void Simulate(float _delta_time);
    void UpdateLogic(float _delta_time);
private:
    // declare variables
    physx::PxDefaultAllocator      mDefaultAllocatorCallback;
    physx::PxDefaultErrorCallback  mDefaultErrorCallback;
    physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
    physx::PxTolerancesScale       mToleranceScale;

    physx::PxFoundation* mFoundation = NULL;
    physx::PxPhysics* mPhysics = NULL;

    physx::PxScene* mScene = NULL;
    physx::PxMaterial* mMaterial = NULL;

    physx::PxPvd* mPvd = NULL;

    std::vector<physx::PxActor*> vec_actor;
};



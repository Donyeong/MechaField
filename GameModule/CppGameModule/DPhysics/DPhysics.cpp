#include "DPhysics.h"
#include <iostream>
void DPhysics::Init()
{
    std::cout << "Init Physics";
    BuildEnvironment();
    BuildGeometry();
    std::cout << "Complete Init Physics";
}

void DPhysics::Update(float _delta_time)
{
    UpdateLogic(_delta_time);
    Simulate(_delta_time);
}

void DPhysics::BuildEnvironment()
{
    std::cout << "BuildEnvironment";
    // init physx
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
    if (!mFoundation) throw("PxCreateFoundation failed!");
    mPvd = PxCreatePvd(*mFoundation);
    physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
    //mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(),true, mPvd);
    mToleranceScale.length = 100;        // typical length of an object
    mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
    //mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale);

    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = mDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    mScene = mPhysics->createScene(sceneDesc);

    physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
}

void DPhysics::BuildGeometry()
{
    std::cout << "BuildGeometry";
    // create simulation
    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    physx::PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
    mScene->addActor(*groundPlane);

    float halfExtent = .5f;
    physx::PxShape* shape = mPhysics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *mMaterial);
    physx::PxU32 size = 20;
    physx::PxTransform t(physx::PxVec3(0));
    for (physx::PxU32 i = 0; i < size; i++) {
        for (physx::PxU32 j = 0; j < size - i; j++) {
            physx::PxTransform localTm(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2 + 1), 0) * halfExtent);
            physx::PxRigidDynamic* body = mPhysics->createRigidDynamic(t.transform(localTm));
            body->attachShape(*shape);
            physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
            mScene->addActor(*body);
            vec_actor.push_back(body);

            std::cout << "Build BoxObject [" << localTm.p.x << "," << localTm.p.y << "," << localTm.p.z << "]" << std::endl;
        }
    }
    shape->release();
}

void DPhysics::Simulate(float _delta_time)
{
    mScene->simulate(_delta_time);
    mScene->fetchResults(true);
}

void DPhysics::UpdateLogic(float _delta_time)
{
    //for (auto i = vec_actor.begin(); i != vec_actor.end(); i++)
    //{
    //    physx::PxActor* actor = *i;
    //    physx::PxActorType::Enum actor_type = actor->getType();
    //    //physx::PxForceMode::Enum force_mode = physx::PxForceMode::eIMPULSE;
    //    if (actor_type == physx::PxActorType::Enum::eRIGID_DYNAMIC)
    //    {
    //        physx::PxRigidDynamic* d_actor = (physx::PxRigidDynamic*)actor;
    //        d_actor->addForce(physx::PxVec3(rand() % 1000, 1 * rand() % 1000, rand() % 1000));
    //    }

    //    physx::PxRigidDynamicLockFlag::
    //}
}

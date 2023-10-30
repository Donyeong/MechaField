#include "../Framework/GameObject.h"
namespace DLogic
{
	class ActorStat {
	public:
		int hp;
		int max_hp;
	};
	class Actor : public GameObject {
	public:
		Actor() { }
		virtual void OnAwake() {}
		virtual void OnStart() {}
		ActorStat stat;
		Transform transform;
	};	

	class Player : public Actor {
	public:
		Player() : dash_cooldown(0) {

		}
		void OnMove(DGeneric::Vector3 _direction) {
			transform.position += _direction;
		}


		virtual void OnUpdate(float _delta_time) {
			Scene* scene = GetScene();
		}
	public:
		float dash_cooldown;
	};

	class ActorState {
		int state;
	};


	class ActorFSM {
		typedef int ActorStateId;
		DGeneric::HashMap<ActorStateId, ActorState> actor_state_map;
		
	};
}
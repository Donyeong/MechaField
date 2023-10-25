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
		virtual void OnAwake();
		virtual void OnStart();
		virtual void OnUpdate();
		ActorStat stat;
	};	

	class Player : public Actor {
	public:
		float dash_cooldown;
		void OnMove() {

		}


		virtual void OnUpdate() {

		}
	};

	class ActorStat {
		
	};

	class ActorState {
		int state;
	};


	class ActorFSM {
		typedef int ActorStateId;
		DGeneric::HashMap<ActorStateId, ActorState> actor_state_map;
		
	};
}
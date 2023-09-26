#include "../Framework/GameObject.h"
namespace DLogic
{
	class ActorStat;
	class Actor : public GameObject {
	public:
		virtual void OnAwake();
		virtual void OnStart();
		virtual void OnUpdate();
		ActorStat stat;
	};

	class ActorStat {
		
	};
}
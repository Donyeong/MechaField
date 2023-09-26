#include "ICommand.h"
#include "../dl_pch.h"
namespace DLogic
{
	class CommandManager {
	public:

	public:
		CommandManager() : m_command_queue() {
			
		}

		void Update()
		{
			while(!m_command_queue.empty())
			{
				ICommand& c = m_command_queue.Dequeue();
				c.handle();
			}
		}
	private:	
		DGeneric::Queue<ICommand> m_command_queue;
	};
}

  
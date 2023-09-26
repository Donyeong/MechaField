#include "String.h"
#include "Vector3.h"
namespace DGeneric
{
	class Quaternion {
	public:
		Quaternion() = default;
		~Quaternion() = default;
	public:
		union
		{
			struct {
				float x;
				float y;
				float z;
				float w;
			};

			struct {
				Vector3 u;
			};
		};
	};
}
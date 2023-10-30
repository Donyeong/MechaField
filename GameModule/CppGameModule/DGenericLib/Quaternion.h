#include "String.h"
#include "Vector3.h"
namespace DGeneric
{
	class Quaternion {
	public:
		Quaternion() : x(0), y(0), z(0), w(0) {

		}
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
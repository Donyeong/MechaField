using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class DNMath
{
	public static Quaternion VectorToQuaternion(Vector3 _vec)
	{
		return Quaternion.Euler(_vec.x, _vec.y, _vec.z);
	}
}
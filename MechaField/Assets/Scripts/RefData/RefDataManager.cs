using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RefDataManager : Singleton<RefDataManager>
{
	Dictionary<Type, List<RefDataItem>> map_ref_datas;
	List<RefDataItem> GetRefDatas<T>() where T : RefDataItem
	{
		return map_ref_datas[typeof(T)];
	}

} 

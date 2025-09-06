#include "CScene.h"

//Actor에서 URootComponent부터 DFS로 생성
// 
//씬 정보구조
//Actor
//	USceneComponent
//		pos : x, y, z
//		rot : x, y, z
//		scale : x, y, z
//	USceneComponent
//		pos : x, y, z
//		rot : x, y, z
//		scale : x, y, z
//		USceneComponent
//			pos: x, y, z
//			rot : x, y, z
//			scale : x, y, z

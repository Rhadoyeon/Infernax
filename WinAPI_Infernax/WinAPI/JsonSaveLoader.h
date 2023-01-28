#pragma once
#include "SingletonBase.h"

#define DATA_FILE_NAME "SaveData.json"
// 파일입출력으로 사용
// 외부라이브러리를 가져온다.
// ㄴ 1. 파일을 통째로 가져오는 방법(심어주기)
//		ㄴ 심어줄때는 가벼운 용량이어야 한다.
//		ㄴ 못 가져오는 것: 고스트(21GB), DXlibrary
// ㄴ 2. 경로 설정

// 생소하고 어렵기 때문에 쓰지않는다.
// 업계에선 많이 쓰기때문에 되도록 쓰자

#pragma region 제이슨
/*
	제이슨(JSON (JavaScript Object Notation)

	- 제이슨은 객체의 구조와 속성을 텍스트 형식으로 전달하기 위해 고안된 방식이다.
		ㄴ 인터넷에서 자료를 주고 받을 때 그 자료를 표현하는 방법으로 주로 사용이 된다.

	- 자료의 종료에 큰 제한은 없으며 특히 컴퓨터의 프로그램의 변수값을 표현하는데 적합하다.
	- 제이슨의 형식은 자바 스크립트이 구문 형식을 따르지만 프로그래밍 언어나 플랫폼에 독립적이므로
	C, C++, C#, 자바, 자바스트립트, 펄, 파이썬, 루비 등등 많은 언어에서 사용이 되고 있다.

	- XML, HTTP, CSV 등등 보다 "일반적인" 환경에서 더 빠르다.

	- 제이슨 형식에서 사용하는 기호의 의미는 다음과 같다.

	키: 값 -> 객체가 가지는 속성
	{}: 객체
	"": 문자열 데이터
	[]: 배열

*/
#pragma endregion

class JsonSaveLoader : public SingletonBase <JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);
public:

	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);

	Json::Value loadJsonFile(char* fileName);

	JsonSaveLoader() {}
	~JsonSaveLoader() {}
};


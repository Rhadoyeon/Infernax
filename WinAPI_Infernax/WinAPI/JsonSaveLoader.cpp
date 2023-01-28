#include "Stdafx.h"
#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
	// Do Noting
	return E_NOTIMPL;
}

void JsonSaveLoader::release(void)
{
	// Do Noting
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();
	// 고유 식별변호를 알려주기 위한 file, 윈도우에서 보유한 고유 식별 번호
	HANDLE file;
	// BOM(bite of Mark)
	WORD BOM = 0xFEFF;
	DWORD dwBytes = 0;
	DWORD dwRead;

	/*
	// Byte 순서 표시
	▶ BOM (Byte Of(Order) Mark;
	- 컴퓨터는 데이터를 메모리에 저장할 때 바이트 단위로 나눠서 저장을 한다.
	- 하지만 유니코드이 경우 인코딩 방식이나 엔디안 방식에 따라 BOM이 필요한 경우가 있다.

	※ 윈도우가 사용하는 방식은 UTF-16(U+FEFF) -> BOM

	- 바이트가 저장되는 순서에 따라 빅 엔디안, 리틀 엔디안으로 나뉜다.
		빅 엔디안: 1번 변수, 2번 변수 \ 리틀 엔디안: 1, 2, ,3..

	서버에서 많이 쓰이는 방식

		- 빅 엔디안(Big endian) 좌 -> 우
		ㄴ 빅 엔디안 방식은 낮은 주소에 데이터의 높은 바이트부터 저장하는 방식
		ㄴ 메모리에 순차적으로 저장되기 때문에 그대로 읽을 수가 있다.
			ㄴ 사람이 편하다.

		- 리틀 엔디안 (좌 <- 우)
		ㄴ 리틀 엔디안 방식은 낮은 주소에 데이터의 낮은 바이트를 저장하는 방식
		ㄴ 평소 사람이 읽는 방향의 반대로 읽어야 하기 때문에 접근성이 떨어진다.

	- 보통 파일의 제일 앞쪽에 OxFEFF를 바이너리 형식으로 채택해서 (BOM)
	이후에 나올 문자나 문자열을 읽어 들이게 하는 방식때문에 사용한다.	
	*/


	/*
	CreateFile : 파일 입출력 장치를 만들거나 읽어온다.
				사용할 수 있는 Handle을 반환한다.

	인자:
	1. 생성하거나 열 파일의 이름
	2. 파일 접근 타입
	3. 열려진 파일의 공유 여부 (파일이 다른곳에 사용되고 있으면 다른 곳에서도 사용하게 할 것인가 / 0 -> 공유 X)
	4. 자식에게 상속 여부(3번과 4번은 게임에서 고유 값)
	5. 파일 생성 모두 세팅
	ㄴ CREATE_ALWAYS: 새로운 파일 생성 -> 동일한 파일 존재시 덮어쓰기
	6. 파일의 옵션값 설정 (읽기 전용 / 쓰기 전용 등등..)
	ㄴ FILE_ATTRIBUTE_NORMAL: 일반적인 속성을 사용한다.
	7. 파일에 대한 속성값 (새로 만들시)
	
	*/

	file = CreateFile
	(
		fileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL	
	);

	// INVALID_HANDLE_VALUE: 핸들 초기화에 사용한다.
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
	}

	else
	{
		// 인자: CreateFile에서 할당된 핸들, 파일에 쓰고 싶은 스트링 값,
		// 얼마나 읽고 쓸것 인지에 대한 크기
		// 얼마나 읽고 쓸것 인지에 대한 반환값 (주소)
		// WriteFile(file, &BOM, 2, &dwBytes, NULL);
		WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwRead, NULL);

		CloseHandle(file);
	}
}

string JsonSaveLoader::loadString(char* fileName)
{
	TCHAR buf[8192];
	ZeroMemory(buf, sizeof(buf));
	
	HANDLE file;
	DWORD dwBytes;

	// GENERIC_READ: 일반적인 읽기 형태
	// OPEN_ALWAYS: 파일이 존재하면 항상 열겠다. 
	file = CreateFile
	(
		fileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// INVALID_HANDLE_VALUE: 핸들 초기화에 사용한다.
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
		return "";
	}

	else
	{
		ReadFile(file, buf, 8192, &dwBytes, NULL);
		CloseHandle(file);
	}

	return string(buf);
}

void JsonSaveLoader::saveStringWithFileStream(char* fileName, string data)
{
	ofstream outFile(fileName);

	outFile << data << endl;

	outFile.close();
}

string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{
	ifstream fileIn;

	/*
	ios::in 파일을 읽기만 가능한 모드로 개방하겠다.
	ios::out 파일을 쓰기만 가능한 모드로 개방하겠다.
	ios::ate 파일을 개방할 때 파일의 끝으로 파일 포인터를 이동 시킨다.
	ios::app 해당 파일에 맨 끝에서부터 데이터를 추가한다.
	ios::trunc 파일이 있으면 해당 파일의 모든 데이터를 비우고 연다.
	ios::binary 바이너리 모드로 개방(서버)	
	*/

	fileIn.open(fileName, ios::in);

	char data;
	string jsonStr;

	while (fileIn.get(data))
	{
		jsonStr += data;
	}

	fileIn.close();

	return jsonStr;
}

void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);

	saveStringWithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
	string jsonStr = loadStringWithFileStream(fileName);

	if (jsonStr == "")
	{
		MessageBox(_hWnd, "데이터가 없다", "경고", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	// 면접질문, 파싱과 파서의 개념은 알아두어야 한다.
	// 파싱: 특정 문서를 읽어 들여서 이를 다른 프로그램이나 서브 루틴이 사용할 수 있게 내부의 표현 방식으로 변환해 주는 것

	// 파서: 파싱을 하는 프로세서

	bool parsingRet = reader.parse(jsonStr, root);
	// 제이슨 자체에 파싱이라는 것이 있다.

	// 오류가 나면 오류 코드 넣고 구글에 ㄱㄱ
	if (!parsingRet)
	{
		string errMsg = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errMsg.c_str(), "오류", MB_OK);
		PostQuitMessage(0);
	}

	return root;
}

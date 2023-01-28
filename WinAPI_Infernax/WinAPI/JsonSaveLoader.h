#pragma once
#include "SingletonBase.h"

#define DATA_FILE_NAME "SaveData.json"
// ������������� ���
// �ܺζ��̺귯���� �����´�.
// �� 1. ������ ��°�� �������� ���(�ɾ��ֱ�)
//		�� �ɾ��ٶ��� ������ �뷮�̾�� �Ѵ�.
//		�� �� �������� ��: ��Ʈ(21GB), DXlibrary
// �� 2. ��� ����

// �����ϰ� ��Ʊ� ������ �����ʴ´�.
// ���迡�� ���� ���⶧���� �ǵ��� ����

#pragma region ���̽�
/*
	���̽�(JSON (JavaScript Object Notation)

	- ���̽��� ��ü�� ������ �Ӽ��� �ؽ�Ʈ �������� �����ϱ� ���� ��ȵ� ����̴�.
		�� ���ͳݿ��� �ڷḦ �ְ� ���� �� �� �ڷḦ ǥ���ϴ� ������� �ַ� ����� �ȴ�.

	- �ڷ��� ���ῡ ū ������ ������ Ư�� ��ǻ���� ���α׷��� �������� ǥ���ϴµ� �����ϴ�.
	- ���̽��� ������ �ڹ� ��ũ��Ʈ�� ���� ������ �������� ���α׷��� �� �÷����� �������̹Ƿ�
	C, C++, C#, �ڹ�, �ڹٽ�Ʈ��Ʈ, ��, ���̽�, ��� ��� ���� ���� ����� �ǰ� �ִ�.

	- XML, HTTP, CSV ��� ���� "�Ϲ�����" ȯ�濡�� �� ������.

	- ���̽� ���Ŀ��� ����ϴ� ��ȣ�� �ǹ̴� ������ ����.

	Ű: �� -> ��ü�� ������ �Ӽ�
	{}: ��ü
	"": ���ڿ� ������
	[]: �迭

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


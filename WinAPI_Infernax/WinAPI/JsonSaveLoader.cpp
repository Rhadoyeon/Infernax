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
	// ���� �ĺ���ȣ�� �˷��ֱ� ���� file, �����쿡�� ������ ���� �ĺ� ��ȣ
	HANDLE file;
	// BOM(bite of Mark)
	WORD BOM = 0xFEFF;
	DWORD dwBytes = 0;
	DWORD dwRead;

	/*
	// Byte ���� ǥ��
	�� BOM (Byte Of(Order) Mark;
	- ��ǻ�ʹ� �����͸� �޸𸮿� ������ �� ����Ʈ ������ ������ ������ �Ѵ�.
	- ������ �����ڵ��� ��� ���ڵ� ����̳� ����� ��Ŀ� ���� BOM�� �ʿ��� ��찡 �ִ�.

	�� �����찡 ����ϴ� ����� UTF-16(U+FEFF) -> BOM

	- ����Ʈ�� ����Ǵ� ������ ���� �� �����, ��Ʋ ��������� ������.
		�� �����: 1�� ����, 2�� ���� \ ��Ʋ �����: 1, 2, ,3..

	�������� ���� ���̴� ���

		- �� �����(Big endian) �� -> ��
		�� �� ����� ����� ���� �ּҿ� �������� ���� ����Ʈ���� �����ϴ� ���
		�� �޸𸮿� ���������� ����Ǳ� ������ �״�� ���� ���� �ִ�.
			�� ����� ���ϴ�.

		- ��Ʋ ����� (�� <- ��)
		�� ��Ʋ ����� ����� ���� �ּҿ� �������� ���� ����Ʈ�� �����ϴ� ���
		�� ��� ����� �д� ������ �ݴ�� �о�� �ϱ� ������ ���ټ��� ��������.

	- ���� ������ ���� ���ʿ� OxFEFF�� ���̳ʸ� �������� ä���ؼ� (BOM)
	���Ŀ� ���� ���ڳ� ���ڿ��� �о� ���̰� �ϴ� ��Ķ����� ����Ѵ�.	
	*/


	/*
	CreateFile : ���� ����� ��ġ�� ����ų� �о�´�.
				����� �� �ִ� Handle�� ��ȯ�Ѵ�.

	����:
	1. �����ϰų� �� ������ �̸�
	2. ���� ���� Ÿ��
	3. ������ ������ ���� ���� (������ �ٸ����� ���ǰ� ������ �ٸ� �������� ����ϰ� �� ���ΰ� / 0 -> ���� X)
	4. �ڽĿ��� ��� ����(3���� 4���� ���ӿ��� ���� ��)
	5. ���� ���� ��� ����
	�� CREATE_ALWAYS: ���ο� ���� ���� -> ������ ���� ����� �����
	6. ������ �ɼǰ� ���� (�б� ���� / ���� ���� ���..)
	�� FILE_ATTRIBUTE_NORMAL: �Ϲ����� �Ӽ��� ����Ѵ�.
	7. ���Ͽ� ���� �Ӽ��� (���� �����)
	
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

	// INVALID_HANDLE_VALUE: �ڵ� �ʱ�ȭ�� ����Ѵ�.
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
	}

	else
	{
		// ����: CreateFile���� �Ҵ�� �ڵ�, ���Ͽ� ���� ���� ��Ʈ�� ��,
		// �󸶳� �а� ���� ������ ���� ũ��
		// �󸶳� �а� ���� ������ ���� ��ȯ�� (�ּ�)
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

	// GENERIC_READ: �Ϲ����� �б� ����
	// OPEN_ALWAYS: ������ �����ϸ� �׻� ���ڴ�. 
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

	// INVALID_HANDLE_VALUE: �ڵ� �ʱ�ȭ�� ����Ѵ�.
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
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
	ios::in ������ �б⸸ ������ ���� �����ϰڴ�.
	ios::out ������ ���⸸ ������ ���� �����ϰڴ�.
	ios::ate ������ ������ �� ������ ������ ���� �����͸� �̵� ��Ų��.
	ios::app �ش� ���Ͽ� �� ���������� �����͸� �߰��Ѵ�.
	ios::trunc ������ ������ �ش� ������ ��� �����͸� ���� ����.
	ios::binary ���̳ʸ� ���� ����(����)	
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
		MessageBox(_hWnd, "�����Ͱ� ����", "���", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	// ��������, �Ľ̰� �ļ��� ������ �˾Ƶξ�� �Ѵ�.
	// �Ľ�: Ư�� ������ �о� �鿩�� �̸� �ٸ� ���α׷��̳� ���� ��ƾ�� ����� �� �ְ� ������ ǥ�� ������� ��ȯ�� �ִ� ��

	// �ļ�: �Ľ��� �ϴ� ���μ���

	bool parsingRet = reader.parse(jsonStr, root);
	// ���̽� ��ü�� �Ľ��̶�� ���� �ִ�.

	// ������ ���� ���� �ڵ� �ְ� ���ۿ� ����
	if (!parsingRet)
	{
		string errMsg = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errMsg.c_str(), "����", MB_OK);
		PostQuitMessage(0);
	}

	return root;
}

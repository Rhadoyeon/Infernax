#pragma once
//=====================================================
// # Utils (����ȭ �ϰ� �Ͱų� or ������ ����� ��Ƶд�.)
//=====================================================

// ��׸� 1���� ���� ��
// ��Ģ���� �� �������� ���� ����. �ݺ��� ���ƾ� �ϱ� ����.
#define DEG_TO_RAD		0.017453f
#define PI				3.141592654f
#define PI_2			6.283185308f
#define FLOAT_EPSILON	0.0001f
// �Ǽ��� ���������� ��ȯ(��Ȯ���� ��/�ٿ� ĳ�����̶�� ��)
#define FLOAT_TO_INT(f1)		static_cast<int>(f1 + FLOAT_EPSILON)
// �� �Ǽ��� ������ ��
//  �� fabs�� �Ҽ��� ���� ���밪 ��ȯ
#define FLOAT_EQUAL(f1, f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	// �� �� ������ �Ÿ��� ���Ѵ�.
	float getDistance(float startX, float startY, float endX, float endY);

	// start���� end������ ���� �������� ���Ѵ�.
	float getAngle(float startX, float startY, float endX, float endY);
}

#pragma region
/*
	�� ���Ƿ� (Epsilon)

	 - �ε� �Ҽ����� �Ǽ��� ��Ȯ�� ǥ���� �� ���� ������ ������ �ִ�.
	  �� �ֳ��ϸ� ���������� �Ǽ��� �����ѵ� �� �Ǽ��� ������ ��Ʈ�� ǥ���ϱ�
		 ���ؼ��� ��ǻ�Ͱ� ��¿ �� ���� �ٻ�ġ(�ٻ簪)�� ǥ���ؾ� �ϱ� ����.

	 - �̷��� ������ ������ �߻��ϴ� �� �ε��Ҽ��� �ݿø� ����.

	 - �̷��� Ư�������� ���������� �߻��ϴµ� ��Ȯ�� ����� ���ؼ� ����� ���ǵ� ���� ����Ѵ�.

	 - 2D�� ũ�� �ν��� ���ϴ� ��찡 ������, 3D ���� ���� ������� �޶��� �� �ִ�.
*/

/*
	�� ĳ���� ������ ����

	 1. static_cast

	 2. const_cast
	  - const ��� �� ���� �� ���� �뵵. (���� �̸� ���� �� ���� ��)

	 3. dynamic_cast

	 4. reinterpret_cast
	  - ���� ������ �˾Ƶ� ��. �ڼ��� �˰� ���� ����.
*/
#pragma endregion
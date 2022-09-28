#pragma once
#include "../Base/Base.h"

class Field :public Base {
private:
	//�摜�I�u�W�F�N�g(�O�i)
	CImage m_foreground;
	//�摜�I�u�W�F�N�g(���i)
	CImage m_town;
	//�摜�I�u�W�F�N�g(�ŉ��i)
	CImage m_sky;
	//�n�ʂ̍���
	float m_ground_y;
public:
	//
	Field();
	//
	void Draw();

	//
	float GetGroundY() {
		return m_ground_y;
	}
};

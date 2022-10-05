#include "UI.h"
#include "GameData.h"


UI::UI() :Base(eType_UI) {
	m_img.Load("Image/UI.png");
	
}

void UI::Draw() {
	int score = GameData::s_score;
	for (int i = 0; i < 2; i++, score /= 10) {
		int s = score % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(200 - 16 * i, 0);
		m_img.Draw();
	}
	GameData::s_time--;
	int t = GameData::s_time / 60;
	for (int i = 0; i < 4; i++, t /= 10) {
		int s = t % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(200 - 16 * i, 16);
		m_img.Draw();
	}
	//“G‚ª‚¢‚È‚¯‚ê‚Î
	/*if (enemy == nullptr) {
		//ƒQ[ƒ€ƒNƒŠƒA‚Ì•\Ž¦
		m_img.SetRect(0, 64, 0 + 160, 64 + 32);
		m_img.SetSize(160, 32);
		m_img.SetPos(100, 200);
		m_img.Draw();
	}*/
}
#include "pch.h"
#include "AnimationAsset.h"


bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//�ؽ�Ʈ ������ ��� csv���� ����� �о�´�.
	// �Ʒ� �Լ��� csv������ ó���Ѵ�.

	if (FilePath == std::wstring(L"SpiderMan"))
	{
		LoadAnimationFromCSV(0, L"..\\Data\\playerAni.csv");// �׷� �ִϸ��̼��� �ٸ��ٸ� ���⼭ �ݺ����� �����߰ڳ�
	}

	if (FilePath == std::wstring(L"Missile"))
	{
		LoadAnimationFromCSV(0, L"..\\Data\\missileAni.csv");// �׷� �ִϸ��̼��� �ٸ��ٸ� ���⼭ �ݺ����� �����߰ڳ�
	}
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)  //�ε��� ������������.. ���� ��������������
{
	std::wifstream file(fileName); 
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	int AniCount = 0;			// �������� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> AniCount;
	}
	for (int i = 0; i < AniCount; i++)
	{
		int FrameCount = 0;			// �������� ����
		{
			std::getline(file, line);		// ù��° �� �б�
			std::wstringstream wss(line);
			wss >> FrameCount;
		}
		//m_Animations[index].Frames.reserve(FrameCount);
		for (int j = 0; j < FrameCount; j++)
		{
			m_Animations[i].Frames.push_back(FRAME_INFO());
			getline(file, line);			// ���� �б�
			std::wstringstream wss(line);   // ������ �о wstringstream�� ����
			std::wstring token;
			{
				getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
				m_Animations[i].Frames[j].Source.left = (float)_wtoi(token.c_str());
				getline(wss, token, L',');
				m_Animations[i].Frames[j].Source.top = (float)_wtoi(token.c_str());
				getline(wss, token, L',');
				m_Animations[i].Frames[j].Source.right = (float)_wtoi(token.c_str());
				getline(wss, token, L',');
				m_Animations[i].Frames[j].Source.bottom = (float)_wtoi(token.c_str());
				getline(wss, token, L',');
				m_Animations[i].Frames[j].Center.x = (float)_wtoi(token.c_str());
				getline(wss, token, L',');
				m_Animations[i].Frames[j].Center.y = (float)_wtoi(token.c_str());
				getline(wss, token, L',');
				m_Animations[i].Frames[j].Duration = std::wcstod(token.c_str(), nullptr);
			}
		}
	}		
	return true;
}
//��.. �ʿ��Ѹ��Ҹ� ���� ���ؼ�.. �۾��� ��� �ϴ°� ������ ����غ��߰ڴ�.. 
//���� �ʿ��� ���ҽ� �̻���
//���Ѱ� ���̶� �÷��̾�
//���� ���Ѱ����� ���ְ����̿��µ� ����.. ������ ��ֹ��� ����ϴ� ����ε�.. �ʵ� ���ξ����ϱ�..
//ī�޶� �����̸��.. 
//���� 4���� �� �и��ϸ�Ǵµ�.. 
//������ ������ ���ݾ�.. �׷��Ÿ� ���� �� ������ ��Ʈ�� ���ϰ�������..
//��� �ұ�.. 
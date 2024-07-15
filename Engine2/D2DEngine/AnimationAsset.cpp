#include "pch.h"
#include "AnimationAsset.h"


bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//텍스트 파일을 열어서 csv파일 목록을 읽어온다.
	// 아래 함수로 csv파일을 처리한다.

	if (FilePath == std::wstring(L"SpiderMan"))
	{
		LoadAnimationFromCSV(0, L"..\\Data\\playerAni.csv");// 그럼 애니메이션이 다르다면 여기서 반복문을 돌려야겠네
	}

	if (FilePath == std::wstring(L"Missile"))
	{
		LoadAnimationFromCSV(0, L"..\\Data\\missileAni.csv");// 그럼 애니메이션이 다르다면 여기서 반복문을 돌려야겠네
	}
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)  //인덱스 별로하지말고.. 전부 가져오도록하자
{
	std::wifstream file(fileName); 
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	int AniCount = 0;			// 프레임의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> AniCount;
	}
	for (int i = 0; i < AniCount; i++)
	{
		int FrameCount = 0;			// 프레임의 개수
		{
			std::getline(file, line);		// 첫번째 줄 읽기
			std::wstringstream wss(line);
			wss >> FrameCount;
		}
		//m_Animations[index].Frames.reserve(FrameCount);
		for (int j = 0; j < FrameCount; j++)
		{
			m_Animations[i].Frames.push_back(FRAME_INFO());
			getline(file, line);			// 한줄 읽기
			std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
			std::wstring token;
			{
				getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
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
//음.. 필요한리소를 전부 구해서.. 작업을 어떻게 하는게 편할지 계산해봐야겠다.. 
//지금 필요한 리소스 미사일
//구한거 맵이랑 플레이어
//내가 원한게임은 경주게임이였는데 흐음.. 정해진 장애물을 통과하는 방식인데.. 맵도 별로없으니까..
//카메라 움직이면됨.. 
//저거 4개만 더 분리하면되는데.. 
//어차피 내엔진 이잖아.. 그럴거면 나는 저 프레임 렉트로 안하고싶은데..
//어떻게 할까.. 

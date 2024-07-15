// DemoGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoGame.h"
#include "DemoGameApp.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DemoGameApp App;
    App.Initialize(hInstance, nCmdShow);
    App.Run();
    App.Uninitialize(); //빌드가 꼬인거같은데.. 어떻게 해결할수잇을까. 
}

/*
* 원래 데모게임 프로젝트에 있던 리소스폴더를 엔진 프로젝트로 옮겼는데 괜찮은건가?
* 리소스 헤더랑 rc 파일이 뭐하는 놈인지를 모르니.. 
* 옮긴이유는 윈도우 생성을 엔진에서 처리하기위해 리소스 헤더파일이 필요했음
* 그냥 둘다 리소스 헤더파일을 추가하면되나? 흠.. 
*/
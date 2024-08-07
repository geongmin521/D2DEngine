#include "pch.h"
#include "InputSystem.h"


InputSystem* InputSystem::Instance = nullptr;

InputSystem::InputSystem() //미리컴파일된 헤더는 적용됬던걸까?근데 잘쓰면 유용할거같긴한데.
{
	for (int i = 0; i < 256; i++) {
		_isKeyDown[i] = false;
		_isKeyUp[i] = false;
		_isKey[i] = false;
	}
	InitMouse();
}

InputSystem::~InputSystem()
{
	delete[] _isKeyDown;
	delete[] _isKeyUp;
	delete[] _isKey;
}

InputSystem* InputSystem::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new InputSystem;
	}
	return Instance;
}

void InputSystem::DestroyInstance()
{
	delete Instance;
	Instance = nullptr;
}

void InputSystem::InitMouse() //이걸 쓸려면 사이즈랑 핸들이 필요함
{
	_curMouse._x = 0;
	_curMouse._y = 0;
	_curMouse._left = false;
	_curMouse._right = false;
	_curMouse._middle = false;
	
	_prevMouse = _curMouse;
	SetCursorPos(_curMouse._x, _curMouse._y);
}

void InputSystem::UpdateKey()
{
	HWND hWnd = GetFocus();
	if (hWnd != nullptr) {
		for (int i = 0; i < 256; i++) {
			short keyState = GetAsyncKeyState(i);
			if (keyState & 0x8000) { // 키가 눌린 상태
				_isKeyDown[i] = true;
				_isKeyUp[i] = false;
				_isKey[i] = true;
			}
			else if (keyState & 0x0001) { // 키가 떼어진 상태
				_isKeyDown[i] = false;
				_isKeyUp[i] = true;
				_isKey[i] = false;
			}
			else { // 키가 눌리지 않은 상태
				_isKeyDown[i] = false;
				_isKeyUp[i] = false;
				_isKey[i] = false;
			}
		}
	}
}

void InputSystem::UpdateMouse(HWND handle)
{
	_prevMouse = _curMouse;
	
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(handle, &pos);
	
	_curMouse._x = pos.x;
	_curMouse._y = pos.y;
	_curMouse._wheel = 0;
			  
	_curMouse._left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	_curMouse._right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	_curMouse._middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

bool InputSystem::GetMouseButtonDown(int idx)
{
	switch (idx) {
	case 0:
		return (_prevMouse._left == false && _curMouse._left == true);
	case 1:
		return (_prevMouse._middle == false && _curMouse._middle == true);
	case 2:
		return (_prevMouse._right == false && _curMouse._right == true);
	default:
		return false;
	}
}

bool InputSystem::GetMouseButton(int idx)
{
	switch (idx) {
	case 0:
		return (_prevMouse._left == true && _curMouse._left == true);
	case 1:
		return (_prevMouse._middle == true && _curMouse._middle == true);
	case 2:
		return (_prevMouse._right == true && _curMouse._right == true);
	default:
		return false;
	}
}

bool InputSystem::GetMouseButtonUp(int idx)
{
	switch (idx) {
	case 0:
		return (_prevMouse._left == true && _curMouse._left == false);
	case 1:
		return (_prevMouse._middle == true && _curMouse._middle == false);
	case 2:
		return (_prevMouse._right == true && _curMouse._right == false);
	default:
		return false;
	}
}

void InputSystem::ResetInput() {
	for (int i = 0; i < 256; i++) {
		_isKeyDown[i] = false;
		_isKeyUp[i] = false;
		_isKey[i] = false;
	}
}
#include "pch.h"
#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> DataManager::CSVReader(const std::type_info& typeInfo)
{
    //�̰� �����ϱ� ����.. ������ ���°����� ��ġ�� ������.. �̰ɾ�� ó���ϰ� ���������..
    // �׸��� csv������.. ��Ʈ�� �ٸ��� ��� ó���Ǵ��� �ñ���.. �ִϸ��̼ǵ� ���⼭ ó���Ҽ��ְ� �����.. 

    if (typeInfo == typeid(EnemyData)) {
        return EnemyDataRead();
    }
    else if (typeInfo == typeid(TowerData)) {
        return TowerDataRead();
    }
    else if (typeInfo == typeid(WaveData)) {
        return WaveDataRead();
    }
    else {
        assert(false && "Unsupported type in CSVReader");
        return {}; // Unreachable code; returns an empty variant to suppress compiler warnings
    }
}

std::vector<EnemyData> DataManager::EnemyDataRead()
{
	std::wifstream file(L"..\\Data\\EnemyData.csv"); //�б�
	if (!file.is_open()) {
		assert(false && "������ �������� �ʽ��ϴ�.");
	}
	std::wstring line;			// ������ ���ڿ�	
	int DataCount = 0;			
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> DataCount;
	}//���κ��� ��� �ߺ��̶� ������ ��� �����ϱ�
	std::vector<EnemyData> result;
	for (int j = 0; j < DataCount; j++)
	{
		EnemyData data;

		getline(file, line);			// ���� �б�
		std::wstringstream wss(line);   // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			//col->m_Center.x = (float)_wtoi(token.c_str()); //�������� ������ �°� ������� �־��ָ��
			getline(wss, token, L',');
			//col->m_Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			//col->m_Extent.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			//col->m_Extent.y = (float)_wtoi(token.c_str());
		}
		result.push_back(data);  //���� �׳� ������ �ִ°ź���.. �����Ҵ����� �������ִ°� �°���? 
	}
	return result;

}

std::vector<TowerData> DataManager::TowerDataRead()
{
	return std::vector<TowerData>();
}

std::vector<WaveData> DataManager::WaveDataRead()
{
	return std::vector<WaveData>();
}

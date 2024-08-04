#pragma once
#include "DataManager.h"
//#include "SingletonBase.h"


struct VariantVisitor {
    std::vector<TowerData>& operator()( std::vector<TowerData>& towerData) {
        return towerData;
    }

    std::vector<EnemyData>& operator()(std::vector<EnemyData>& enemyData) {
        return enemyData;
    }

    std::vector<WaveData>& operator()(std::vector<WaveData>& waves) {
        return waves;
    }
};

class Factory : public SingletonBase<Factory> 
{
	std::vector<TowerData> towerData; //�����ͷ� ó���ϴ���.. �ƹ�ư �����簡 �Ͼ���ʰ�.. ������ ó���ϱ�.. 
	std::vector<EnemyData> enemyData;
	std::vector<WaveData> waveData;
	void GetData() { 

        std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> data =
            DataManager::GetInstance().get()->CSVReader(typeid(TowerData));

        if (std::holds_alternative<std::vector<EnemyData>>(data)) {
            enemyData = std::get<std::vector<EnemyData>>(data);
        }
        else if (std::holds_alternative<std::vector<TowerData>>(data)) {
            towerData = std::get<std::vector<TowerData>>(data);
        }
        else if (std::holds_alternative<std::vector<WaveData>>(data)) {
            waveData = std::get<std::vector<WaveData>>(data);
        }
    } 

    //template<typename T>
	//T* CreateGameObject() //���忡 �ִ� �Լ� �״�� ������.. 
	//{
	//	bool bIsBase = std::is_base_of<GameObject, T>::value;
	//	assert(bIsBase == true);
	//	T* newObject = new T();
	//	newObject->SetOwner(this); //�̰� ��ԵǴ°��� ����ü.. 
	//	
	//	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	//	{
	//		if ((*it)->renderOrder > newObject->renderOrder)
	//		{
	//			m_GameObjects.insert(it, newObject); 
	//			return newObject; 
	//		}			
	//	}
	//	
	//	m_GameObjects.push_back(newObject); //������ ��Ȳ�� ���ؼ��� �ڿ� �ֱ�
	//
	//	return newObject;
	//}
    //���� ���忡�� ó���ϴ� �ν��Ͻ��� ������ ������ �����ϰ����
    //�ϴ� �Լ��� �����ͼ� �������� ����� �������ƺ���.
};


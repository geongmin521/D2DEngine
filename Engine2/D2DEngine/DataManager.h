#pragma once
#include "SingletonBase.h"

struct EnemyData {
    int id;
    std::string name;
    std::string ShieldType; //��� �׳� Ÿ���ΰŰ���
    int star; //���� //������ ������ �̰͵� �����ϸ�ɵ� �̸��� ���ƾ�������.
    float ATK;
    float attackRange; //���� �ݶ��̴��� ������
    float HP;  //�������� int�� ó���ϰ�;������� ������ ���� ���ҷ���. float�ΰ� ����
    float attackSpeed;
    float speed;
    float detectRange; //������ �ʹ�������..
    //������ �ݶ��̴��� �����������..
    //�浹ü�� �����ǰ� ontriggerstay�϶� �Ÿ����� �ൿ�� �����ϱ�.
    //���������� �Ȱ��� �����Ƽ�� ����? �̰� �� �𸣰ڴ�..
    //�����Ƽ�� ���������� �����Ѵٰ��ϸ�.. ����ü�� Ÿ�ٿ� �������������..
    //�ɷ��� �Ÿ��� �����ͼ� �׾ȿ��ִ� ó���ϱ�? �ᱹ �浹ó���ε�..
    //�ݶ��̴��� �ӽ� �����ϱ�? Ʈ���� �����̷� ����
    //��¥ ���������Ӹ� ����ް� ����°� �����ұ�? 
};

struct TowerData {
    int id;
    std::string name;
    std::string attackType;
    int star; //����
    float ATK;
    float attackRange; //���� �ݶ��̴��� ������
    float HP;  //�������� int�� ó���ϰ�;������� ������ ���� ���ҷ���. float�ΰ� ����
    float attackSpeed;  
    //Ư���ɷ¿� ���� ���̵�� ó������
    //�������� Ư���������� �ѱ��.. 
};

struct WaveData {
    int id;
    int level;
    //float ���ݵ� ���������. �Ƹ� ������ ������ ���ͷ� ó���ҵ�?
};

class DataManager : public SingletonBase<DataManager> //�� �����͸� �о�ͼ� ��û�Ѿ����� ��� �κ� �������.. 
{
private:
    std::vector<EnemyData> EnemyDataRead();
    std::vector<TowerData> TowerDataRead();
    std::vector<WaveData> WaveDataRead();
public:
    DataManager();
    ~DataManager();

    // std::variant�� ����Ͽ� ���� Ÿ���� �ϳ��� ��ȯ Ÿ������ ó��
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> CSVReader(const std::type_info& typeInfo);
    //�ʿ��Ѱ�ü�� �̰� �׳� ȣ���ϱ⸸ �ϸ��
};
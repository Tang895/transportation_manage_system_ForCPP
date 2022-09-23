#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cmath>
#include<Windows.h>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<stack>
#include<fstream>//�ļ�
#include<sstream>
#include"time.h"
#include"graph.h"
#define str string
#define float double
#define ll long long
using namespace std;
//��ȡ����
template<class T>
void Read_city_from_file(Graph<T>& map) {
	ifstream file("cities.txt", ios::in);
	while (!file.eof()) {
		double train_waiting_time_A;
		double train_waiting_time_B;
		double plane_waiting_time_A;
		double plane_waiting_time_B;
		string city_A;
		string city_B;
		file >> city_A >> train_waiting_time_A >> plane_waiting_time_A;
		file >> city_B >> train_waiting_time_B >> plane_waiting_time_B;

		map.add_train_node(city_A, train_waiting_time_A);//���һ���𳵵Ľڵ�
		map.add_plane_node(city_A, plane_waiting_time_A);//���һ���ɻ��Ľڵ�
		map.add_train_node(city_B, train_waiting_time_B);//���һ���𳵵Ľڵ�

		map.add_plane_node(city_B, plane_waiting_time_B);//���һ���ɻ��Ľڵ�
	}
}
//��ȡ��ͼ
template<class T>
void Read_map_from_file(Graph<T>& map) {
	//����𳵵�ͼ
	ifstream train_file("train.txt", ios::in);
	while (!train_file.eof()) {
		string city_A;
		string city_B;
		string code;//����
		double distance;
		double money;
		struct time start;
		struct time end;
		double total_time;
		//�ӳ���A������B�����Σ���ʼʱ�䣨Сʱ������ʼʱ�䣨���ӣ�������ʱ�䣨�죩������ʱ�䣨Сʱ��
		//����ʱ�䣨���ӣ����ܵ�ʱ�䣬hour��min
		train_file >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
			>> end.minute >> total_time >> money;
		map.add_one_train_way(city_A, city_B, code, distance, start, end, total_time, money);
	}
	//����ɻ���ͼ
	ifstream plane_file("flight.txt", ios::in);
	while (!plane_file.eof()) {
		string city_A;
		string city_B;
		string code;//����
		double distance;
		double money;
		struct time start;
		struct time end;
		double total_time;
		//�ӳ���A������B�����Σ���ʼʱ�䣨Сʱ������ʼʱ�䣨���ӣ�������ʱ�䣨�죩������ʱ�䣨Сʱ��
		//����ʱ�䣨���ӣ����ܵ�ʱ��hour��min
		plane_file >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
			>> end.minute >> total_time >> money;
		map.add_one_plane_way(city_A, city_B, code, distance, start, end, total_time, money);
	}
}
//��ѯ������·��
template<class T>
void query_train_fast(Graph<T>& map) {
	string city_A, city_B;
	cout << "����Ҫ��ѯ����������" << endl;
	cin >> city_A >> city_B;
	map.fast_train_road(city_A, city_B);
}
//��ѯ�ɻ������·��
template<class T>
void query_plane_fast(Graph<T>& map) {
	string city_A, city_B;
	cout << "����Ҫ��ѯ����������" << endl;
	cin >> city_A >> city_B;
	map.fast_plane_road(city_A, city_B);
}
//��ѯ�𳵵���ʡǮ����
template<class T>
void query_train_cheap(Graph<T>& map) {
	string city_A, city_B;
	cout << "����Ҫ��ѯ����������" << endl;
	cin >> city_A >> city_B;
	map.cheap_train_road(city_A, city_B);
}
//��ѯ�ɻ�����ʡǮ����
template<class T>
void query_plane_cheap(Graph<T>& map) {
	string city_A, city_B;
	cout << "����Ҫ��ѯ����������" << endl;
	cin >> city_A >> city_B;
	map.cheap_plane_road(city_A, city_B);
}
//���ĳ�������
template<class T>
void edit_city_name(Graph<T>& map) {
	string city_A, city_B;
	cout << "����ɳ������ֺ�������" << endl;
	cin >> city_A >> city_B;
	map.edit_name(city_A, city_B);//�𳵺ͷɻ����и���
}
//���һ���³���,�����г��У��򸲸�
template<class T>
void add_city(Graph<T>& map) {
	string city;
	double train_waiting_time;
	double plane_waiting_time;
	cout << "�������³������֣����еĻ���תʱ�䣬�ɻ���תʱ��" << endl;
	cin >> city >> train_waiting_time >> plane_waiting_time;
	map.add_plane_node(city, plane_waiting_time);
	map.add_train_node(city, train_waiting_time);
}
//�༭���еĻ𳵺ͷɻ���תʱ��
template<class T>
void edit_waiting_time(Graph<T>& map) {
	string city;
	double time1, time2;
	cout << "������е����֣�����𳵺ͷɻ���תʱ��" << endl;
	cin >> city >> time1 >> time2;
	int pos = map.find_train_city_name_pos(city);
	if (pos == -1) {
		cout << "�༭��תʱ��ʱ���������Ƴ��ִ���" << endl;
		return;
	}
	map.edit_waiting_time(city, time1, time2);
}
//���һ������·
template<class T>
void add_train_road(Graph<T>& map) {
	string city_A;
	string city_B;
	string code;//����
	double distance;
	double money;
	struct time start;
	struct time end;
	double total_time;
	cout << "����A->B���֣�code,���룬��ʼʱ�䣨Сʱ������ʼʱ�䣨���ӣ���������Сʱ�������������ӣ�������ʱ��Ʊ��" << endl;
	cin >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
		>> end.minute >> total_time >> money;
	map.delete_train_edge(city_A, city_B);
	map.add_one_train_way(city_A, city_B, code, distance, start, end, total_time, money);

}
//���һ���ɻ���·
template<class T>
void add_plane_road(Graph<T>& map) {
	string city_A;
	string city_B;
	string code;//����
	double distance;
	double money;
	struct time start;
	struct time end;
	double total_time;
	cout << "����A->B���֣�code,���룬��ʼʱ�䣨Сʱ������ʼʱ�䣨���ӣ���������Сʱ�������������ӣ�������ʱ��Ʊ��" << endl;
	cin >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
		>> end.minute >> total_time >> money;
	map.delete_plane_edge(city_A, city_B);
	map.add_one_plane_way(city_A, city_B, code, distance, start, end, total_time, money);
}
template<class T>
void query_city_waiting_time(Graph<T>& map) {
	string city;
	cout << "�����������" << endl;
	cin >> city;
	map.query_city_waiting_time(city);
}
template<class T>
void delete_train_edge(Graph<T>& map) {
	string city_A, city_B;
	cout << "����������������" << endl;
	cin >> city_A >> city_B;
	map.delete_train_edge(city_A, city_B);
}
template<class T>
void delete_plane_edge(Graph<T>& map) {
	string city_A, city_B;
	cout << "����������������" << endl;
	cin >> city_A >> city_B;
	map.delete_plane_edge(city_A, city_B);
}
void work() {
	Graph<int> map;
	//��ȡ���к͵�ͼ
	Read_city_from_file(map);
	Read_map_from_file(map);
	int input = 99;
	while (input != 0) {
		cout << "1:��ѯ�𳵵���쵽��" << endl;
		cout << "2:��ѯ�ɻ�����쵽��" << endl;
		cout << "3:��ѯ�𳵵���ʡǮ����" << endl;
		cout << "4:��ѯ�ɻ�����ʡǮ����" << endl;
		cout << "5:��ѯ��������·" << endl;
		cout << "6:��ѯ�ɻ�������·" << endl;
		cout << "7:�޸ĳ�������" << endl;
		cout << "8:��ӳ���" << endl;
		cout << "9:���һ������·" << endl;
		cout << "10:���һ���ɻ���·" << endl;
		cout << "11:�༭����֮��Ļ���·" << endl;
		cout << "12:�༭����֮��ķɻ���·" << endl;
		cout << "13:�༭���еĻ𳵺ͷɻ�����תʱ��" << endl;
		cout << "14:��ѯ������תʱ��" << endl;
		cout << "15:ɾ��һ����·��" << endl;
		cout << "16:ɾ��һ���ɻ�·��" << endl;
		cout << "0:�˳�" << endl;
		cout << "_>";
		cin >> input;
		switch (input) {
		case 0:return; break;
		case 1:query_train_fast(map); break;
		case 2:query_plane_fast(map); break;
		case 3:query_train_cheap(map); break;
		case 4:query_plane_cheap(map); break;
		case 5:map.show_train(); break;
		case 6:map.show_plane(); break;
		case 7:edit_city_name(map); break;
		case 8:add_city(map); break;
		case 9:add_train_road(map); break;
		case 10:add_plane_road(map); break;
		case 11:add_train_road(map); break;//�����·Ĭ�ϸ��ǣ�����ֱ�ӵ��ú���
		case 12:add_plane_road(map); break;//�����·Ĭ�ϸ��ǣ�����ֱ�ӵ��ú���
		case 13:edit_waiting_time(map); break;
		case 14:query_city_waiting_time(map); break;
		case 15:delete_train_edge(map); break;
		case 16:delete_plane_edge(map); break;
		}
	}
}
int main() {

	cout << "��ͨ��ѯϵͳ" << endl;
	cout << "1:��ʼʹ��" << endl;
	cout << "2:�˳�" << endl;
	int input;
	cout << "_>";
	cin >> input;
	while (input != 2) {
		switch (input) {
		case 1:work();
		case 2:return 0;
		default:cout << "???" << endl;
		}

		cin >> input;
	}
	return 0;
}

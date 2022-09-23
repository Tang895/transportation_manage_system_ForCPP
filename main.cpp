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
#include<fstream>//文件
#include<sstream>
#include"time.h"
#include"graph.h"
#define str string
#define float double
#define ll long long
using namespace std;
//读取城市
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

		map.add_train_node(city_A, train_waiting_time_A);//添加一个火车的节点
		map.add_plane_node(city_A, plane_waiting_time_A);//添加一个飞机的节点
		map.add_train_node(city_B, train_waiting_time_B);//添加一个火车的节点

		map.add_plane_node(city_B, plane_waiting_time_B);//添加一个飞机的节点
	}
}
//读取地图
template<class T>
void Read_map_from_file(Graph<T>& map) {
	//载入火车地图
	ifstream train_file("train.txt", ios::in);
	while (!train_file.eof()) {
		string city_A;
		string city_B;
		string code;//车次
		double distance;
		double money;
		struct time start;
		struct time end;
		double total_time;
		//从城市A到城市B，车次，开始时间（小时），开始时间（分钟），结束时间（天），结束时间（小时）
		//结束时间（分钟），总的时间，hour，min
		train_file >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
			>> end.minute >> total_time >> money;
		map.add_one_train_way(city_A, city_B, code, distance, start, end, total_time, money);
	}
	//载入飞机地图
	ifstream plane_file("flight.txt", ios::in);
	while (!plane_file.eof()) {
		string city_A;
		string city_B;
		string code;//车次
		double distance;
		double money;
		struct time start;
		struct time end;
		double total_time;
		//从城市A到城市B，车次，开始时间（小时），开始时间（分钟），结束时间（天），结束时间（小时）
		//结束时间（分钟），总的时间hour，min
		plane_file >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
			>> end.minute >> total_time >> money;
		map.add_one_plane_way(city_A, city_B, code, distance, start, end, total_time, money);
	}
}
//查询火车最快的路径
template<class T>
void query_train_fast(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入要查询的两个城市" << endl;
	cin >> city_A >> city_B;
	map.fast_train_road(city_A, city_B);
}
//查询飞机的最快路径
template<class T>
void query_plane_fast(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入要查询的两个城市" << endl;
	cin >> city_A >> city_B;
	map.fast_plane_road(city_A, city_B);
}
//查询火车的最省钱方案
template<class T>
void query_train_cheap(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入要查询的两个城市" << endl;
	cin >> city_A >> city_B;
	map.cheap_train_road(city_A, city_B);
}
//查询飞机的最省钱方案
template<class T>
void query_plane_cheap(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入要查询的两个城市" << endl;
	cin >> city_A >> city_B;
	map.cheap_plane_road(city_A, city_B);
}
//更改城市名字
template<class T>
void edit_city_name(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入旧城市名字和新名字" << endl;
	cin >> city_A >> city_B;
	map.edit_name(city_A, city_B);//火车和飞机都有更改
}
//添加一个新城市,若已有城市，则覆盖
template<class T>
void add_city(Graph<T>& map) {
	string city;
	double train_waiting_time;
	double plane_waiting_time;
	cout << "请输入新城市名字，城市的火车中转时间，飞机中转时间" << endl;
	cin >> city >> train_waiting_time >> plane_waiting_time;
	map.add_plane_node(city, plane_waiting_time);
	map.add_train_node(city, train_waiting_time);
}
//编辑城市的火车和飞机中转时间
template<class T>
void edit_waiting_time(Graph<T>& map) {
	string city;
	double time1, time2;
	cout << "输入城市的名字，输入火车和飞机中转时间" << endl;
	cin >> city >> time1 >> time2;
	int pos = map.find_train_city_name_pos(city);
	if (pos == -1) {
		cout << "编辑中转时间时，城市名称出现错误" << endl;
		return;
	}
	map.edit_waiting_time(city, time1, time2);
}
//添加一条火车线路
template<class T>
void add_train_road(Graph<T>& map) {
	string city_A;
	string city_B;
	string code;//车次
	double distance;
	double money;
	struct time start;
	struct time end;
	double total_time;
	cout << "输入A->B名字，code,距离，开始时间（小时），开始时间（分钟），结束（小时），结束（分钟），总用时，票价" << endl;
	cin >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
		>> end.minute >> total_time >> money;
	map.delete_train_edge(city_A, city_B);
	map.add_one_train_way(city_A, city_B, code, distance, start, end, total_time, money);

}
//添加一条飞机线路
template<class T>
void add_plane_road(Graph<T>& map) {
	string city_A;
	string city_B;
	string code;//车次
	double distance;
	double money;
	struct time start;
	struct time end;
	double total_time;
	cout << "输入A->B名字，code,距离，开始时间（小时），开始时间（分钟），结束（小时），结束（分钟），总用时，票价" << endl;
	cin >> city_A >> city_B >> code >> distance >> start.hour >> start.minute >> end.hour\
		>> end.minute >> total_time >> money;
	map.delete_plane_edge(city_A, city_B);
	map.add_one_plane_way(city_A, city_B, code, distance, start, end, total_time, money);
}
template<class T>
void query_city_waiting_time(Graph<T>& map) {
	string city;
	cout << "输入城市名字" << endl;
	cin >> city;
	map.query_city_waiting_time(city);
}
template<class T>
void delete_train_edge(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入两个城市名字" << endl;
	cin >> city_A >> city_B;
	map.delete_train_edge(city_A, city_B);
}
template<class T>
void delete_plane_edge(Graph<T>& map) {
	string city_A, city_B;
	cout << "输入两个城市名字" << endl;
	cin >> city_A >> city_B;
	map.delete_plane_edge(city_A, city_B);
}
void work() {
	Graph<int> map;
	//读取城市和地图
	Read_city_from_file(map);
	Read_map_from_file(map);
	int input = 99;
	while (input != 0) {
		cout << "1:查询火车的最快到达" << endl;
		cout << "2:查询飞机的最快到达" << endl;
		cout << "3:查询火车的最省钱方案" << endl;
		cout << "4:查询飞机的最省钱方案" << endl;
		cout << "5:查询火车所有线路" << endl;
		cout << "6:查询飞机所有线路" << endl;
		cout << "7:修改城市名字" << endl;
		cout << "8:添加城市" << endl;
		cout << "9:添加一条火车线路" << endl;
		cout << "10:添加一条飞机线路" << endl;
		cout << "11:编辑城市之间的火车线路" << endl;
		cout << "12:编辑城市之间的飞机线路" << endl;
		cout << "13:编辑城市的火车和飞机的中转时间" << endl;
		cout << "14:查询城市中转时间" << endl;
		cout << "15:删除一条火车路线" << endl;
		cout << "16:删除一条飞机路线" << endl;
		cout << "0:退出" << endl;
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
		case 11:add_train_road(map); break;//添加线路默认覆盖，所有直接调用函数
		case 12:add_plane_road(map); break;//添加线路默认覆盖，所有直接调用函数
		case 13:edit_waiting_time(map); break;
		case 14:query_city_waiting_time(map); break;
		case 15:delete_train_edge(map); break;
		case 16:delete_plane_edge(map); break;
		}
	}
}
int main() {

	cout << "交通咨询系统" << endl;
	cout << "1:开始使用" << endl;
	cout << "2:退出" << endl;
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

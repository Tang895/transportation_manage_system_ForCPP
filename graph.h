#pragma once
#pragma once
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

#define str string
#define float double
#define ll long long
using namespace std;



//����ͼ
template<class T>
class Graph {
private:
	int train_node_size;//�𳵽ڵ�����
	int plane_node_size;//�ɻ��ڵ�����
	int train_edges;//����·����Σ���
	int plane_edges;//�ɻ���·����Σ���

	struct train_Node {
		string name;//��������
		double waiting_time;//����ת�ȴ�ʱ��
	};
	struct train_Edge {
		double distance;//�𳵵�·��
		string code;
		struct time start_time;//����ʼʱ��
		struct time end_time;//�𳵵���ʱ��
		double total_time;//������ʱ
		double money;//��Ʊ�۸�
	};
	struct plane_Node {
		string name;//��������
		double waiting_time;//�ɻ���ת�ȴ�ʱ��
	};
	struct plane_Edge {
		double distance;//�ɻ���·�̣���λ��m��
		string code;
		struct time start_time;//�ɻ���ʼʱ��
		struct time end_time;//�ɻ�����ʱ��
		double total_time;//�ɻ�����ʱ
		double money;//�ɻ�Ʊ�۸�
	};
	vector<train_Node> train_node;//�𳵳�������
	vector<plane_Node> plane_node;//�ɻ���������
	map<string, vector<train_Node>> train_node_list; //�𳵽ڵ����ƶ��ڽӱ��ӳ��
	map<string, vector<plane_Node>> plane_node_list; //�ɻ��ڵ����ƶ��ڽӱ��ӳ��
	map<string, vector<train_Edge>> train_edge_list;//����·,posһһ��Ӧ�����ڽӱߵ�ӳ��
	map<string, vector<plane_Edge>> plane_edge_list;//�ɻ���·
	set<string> train_node_name_judge;//�洢����ӵ�еĽڵ�����ֵļ���,��������
	set<string> plane_node_name_judge;//�洢����ӵ�еĽڵ�����ֵļ���,��������


public:
	Graph() {
		train_node_size = 0;
		train_edges = 0;
		plane_node_size = 0;
		plane_edges = 0;
	}
	//���ݽڵ��������±꣨�������֣��𳵣�
	int find_train_city_name_pos(string name) {
		for (int i = 0; i < train_node.size(); i++) {
			if (name == train_node[i].name) {
				return i;
			}
		}
		cout << ("δ�ҵ��ڵ�����");
		return -1;
	}
	//���ݽڵ��������±꣨��������,�ɻ���
	int find_plane_city_name_pos(string name) {
		for (int i = 0; i < plane_node.size(); i++) {
			if (name == plane_node[i].name) {
				return i;
			}
		}
		cout << ("δ�ҵ��ڵ�����");
		return -1;
	}
	int get_train_size() {
		return train_node_size;
	}
	int get_plane_size() {
		return plane_node_size;
	}
	//�õ�A->B��·��(��)
	double get_train_distance(string node_A, string node_B) {
		int pos;
		for (int i = 0; i < train_node_list[node_A].size(); i++) {
			if (train_node_list[node_A][i].name == node_B) {
				pos = i;
				return train_edge_list[node_A][pos].distance;
				break;
			}
		}
		return -1;
	}
	//�õ�A->B��·��(�ɻ�)
	int get_plane_distance(string node_A, string node_B) {
		int pos;
		for (int i = 0; i < plane_node_list[node_A].size(); i++) {
			if (plane_node_list[node_A][i].name == node_B) {
				pos = i;
				return plane_edge_list[node_A][pos].distance;
				break;
			}
		}
		return -1;
	}
	//ɾ��һ��·(��),node_A->node_B
	void delete_train_edge(string node_A, string node_B) {
		if (train_node_name_judge.count(node_A) == 0 || train_node_name_judge.count(node_B) == 0) {
			cout << "ɾ��·��ʱ���ڵ����ƴ���" << endl;
			return;
		}
		if (get_train_distance(node_A, node_B) == -1)
			return;
		int pos;
		int n = train_node_list[node_A].size();
		for (int i = 0; i < n; i++) {
			if (train_node_list[node_A][i].name == node_B)
				pos = i;
		}
		train_edge_list[node_A].erase(train_edge_list[node_A].begin() + pos);
		train_node_list[node_A].erase(train_node_list[node_A].begin() + pos);
		train_edges--;
	}
	//ɾ��һ��·(�ɻ�),node_A->node_B
	void delete_plane_edge(string node_A, string node_B) {
		if (plane_node_name_judge.count(node_A) == 0 || plane_node_name_judge.count(node_B) == 0) {
			cout << "ɾ��·��ʱ���ڵ����ƴ���" << endl;
			return;
		}
		if (get_plane_distance(node_A, node_B) == -1)
			return;
		int pos;
		int n = plane_node_list[node_A].size();
		for (int i = 0; i < n; i++) {
			if (plane_node_list[node_A][i].name == node_B)
				pos = i;
		}
		plane_edge_list[node_A].erase(plane_edge_list[node_A].begin() + pos);
		plane_node_list[node_A].erase(plane_node_list[node_A].begin() + pos);
		plane_edges--;
	}
	//�޸ĳ�������
	void edit_name(string city_A, string city_B) { //��A���е����ָ�Ϊcity_B
		//��
		int pos = find_train_city_name_pos(city_A);
		//���޸����з�city_A�ڵ�ĳ���
		for (int i = 0; i < train_node_size; i++) {
			if (i == pos)  //������������޸ĵĳ��еĳ��ȣ���continue
				continue;
			//train_node_list[train_node[i].name];
			for (int j = 0; j < train_node_list[train_node[i].name].size(); j++) {
				if (train_node_list[train_node[i].name][j].name == city_A)
					train_node_list[train_node[i].name][j].name = city_B;
			}
		}
		//city_A�ڵ�
		train_node[pos].name = city_B;
		//���жϳ������Ƶ���������
		train_node_name_judge.erase(city_A);
		train_node_name_judge.insert(city_B);
		train_node_list[city_B] = train_node_list[city_A];
		train_edge_list[city_B] = train_edge_list[city_A];
		train_node_list.erase(city_A);
		train_edge_list.erase(city_A);


		//���ڷɻ��������޸�
		pos = find_plane_city_name_pos(city_A);
		//���޸����з�city_A�ڵ�ĳ���
		for (int i = 0; i < plane_node_size; i++) {
			if (i == pos)  //������������޸ĵĳ��еĳ��ȣ���continue
				continue;
			//plane_node_list[plane_node[i].name];
			for (int j = 0; j < plane_node_list[plane_node[i].name].size(); j++) {
				if (plane_node_list[plane_node[i].name][j].name == city_A)
					plane_node_list[plane_node[i].name][j].name = city_B;
			}
		}
		//city_A�ڵ�
		plane_node[pos].name = city_B;
		//���жϳ������Ƶ���������
		plane_node_name_judge.erase(city_A);
		plane_node_name_judge.insert(city_B);
		plane_node_list[city_B] = plane_node_list[city_A];
		plane_edge_list[city_B] = plane_edge_list[city_A];
		plane_edge_list.erase(city_A);
		plane_node_list.erase(city_A);
	}
	//���һ���ڵ�,���һ������(��)
	void add_train_node(string name, double waiting_time) {
		//����ظ����򸲸�
		train_node_name_judge.insert(name);
		train_node_size += 1;
		train_Node newnode;
		newnode.name = name;
		newnode.waiting_time = waiting_time;
		train_node.push_back(newnode);
	}
	//���һ���ڵ�,���һ������(�ɻ�)
	void add_plane_node(string name, double waiting_time) {
		//����Ѿ����˳��У�Ĭ�ϸ���
		plane_node_name_judge.insert(name);
		plane_node_size += 1;
		plane_Node newnode;
		newnode.name = name;
		newnode.waiting_time = waiting_time;
		plane_node.push_back(newnode);
	}
	//���n���ڵ�
	void add_train_nodes(int n) {
		string name;
		for (int i = 0; i < n; i++) {
			cin >> name;
			add_train_node(name);
		}
	}
	//���n���ڵ�(�ɻ��ڵ�)
	void add_plane_nodes(int n) {
		string name;
		for (int i = 0; i < n; i++) {
			cin >> name;
			add_plane_node(name);
		}
	}
	//���һ����ϵ,���һ����·(��)
	void add_one_train_way(string node_A, string node_B, string code, double cost, struct time start, struct time end\
		, double total_time, double money)
	{
		if (train_node_name_judge.count(node_A) == 0 || train_node_name_judge.count(node_B) == 0) {
			cout << "��ӻ���·ʱ�����нڵ����ƴ���" << endl;
			return;
		}
		train_Edge new_edge;//����·
		int pos_B = find_train_city_name_pos(node_B);
		new_edge.distance = cost;
		new_edge.code = code;
		new_edge.start_time = start;
		new_edge.end_time = end;
		new_edge.total_time = total_time;
		new_edge.money = money;
		train_node_list[node_A].push_back(train_node[pos_B]);
		train_edge_list[node_A].push_back(new_edge);
		train_edges++;
	}
	//���һ����ϵ,���һ����·(�ɻ�)
	void add_one_plane_way(string node_A, string node_B, string code, double cost, struct time start, struct time end\
		, double total_time, double money)
	{
		if (plane_node_name_judge.count(node_A) == 0 || plane_node_name_judge.count(node_B) == 0) {
			cout << "��ӷɻ���·ʱ�����нڵ����ƴ���" << endl;
			return;
		}
		plane_Edge new_edge;//����·
		int pos_B = find_plane_city_name_pos(node_B);
		new_edge.distance = cost;
		new_edge.code = code;
		new_edge.start_time = start;
		new_edge.end_time = end;
		new_edge.total_time = total_time;
		new_edge.money = money;
		plane_node_list[node_A].push_back(plane_node[pos_B]);
		plane_edge_list[node_A].push_back(new_edge);
		plane_edges++;
	}
	//���n����·(��)
	void add_train_way(int edges) {
		cout << "�����ϵ��" << endl;
		for (int i = 0; i < edges; i++) {
			string node_A, node_B;
			int cost;
			cin >> node_A >> node_B >> cost;
			add_one_train_way(node_A, node_B, cost);
		}
	}
	//���n����·(�ɻ�)
	void add_plane_way(int edges) {
		cout << "�����ϵ��" << endl;
		for (int i = 0; i < edges; i++) {
			string node_A, node_B;
			int cost;
			cin >> node_A >> node_B >> cost;
			add_one_plane_way(node_A, node_B, cost);
		}
	}


	void show_train(void) {
		cout << "����·��" << endl;
		for (int i = 0; i < train_node.size(); i++) {
			for (int j = 0; j < train_node_list[train_node[i].name].size(); j++) {
				cout << train_node[i].name << "->";
				cout << train_node_list[train_node[i].name][j].name << "::·��:";
				cout << train_edge_list[train_node[i].name][j].distance;
				cout << " ���Σ�" << train_edge_list[train_node[i].name][j].code;
				cout << " ��ʼʱ�䣺"; train_edge_list[train_node[i].name][j].start_time.show();
				cout << " ����ʱ�䣺"; train_edge_list[train_node[i].name][j].end_time.show();
				cout << " ����ʱ��" << train_edge_list[train_node[i].name][j].total_time;
				cout << " �۸�" << train_edge_list[train_node[i].name][j].money;
				cout << endl;
			}

		}

	}
	void show_plane(void) {
		/*cout << "�ɻ��ڵ�����" << train_node_size << endl;;
		cout << "�ɻ���·��������" << train_edges << endl;*/
		cout << "�ɻ���·��" << endl;
		for (int i = 0; i < plane_node.size(); i++) {
			for (int j = 0; j < plane_node_list[plane_node[i].name].size(); j++) {
				cout << plane_node[i].name << "->";
				cout << plane_node_list[plane_node[i].name][j].name << "::����: ";
				cout << plane_edge_list[plane_node[i].name][j].distance;
				cout << " ������룺" << plane_edge_list[plane_node[i].name][j].code;
				cout << " ��ʼʱ�䣺"; plane_edge_list[plane_node[i].name][j].start_time.show();
				cout << " ����ʱ�䣺"; plane_edge_list[plane_node[i].name][j].end_time.show();
				cout << " ����ʱ��" << plane_edge_list[plane_node[i].name][j].total_time;
				cout << " �۸�" << plane_edge_list[plane_node[i].name][j].money;
				cout << endl;
			}
		}
	}

	//ɾ���ڵ�(��)
	void delete_train_Node(string name) {
		if (train_node_name_judge.count(name) == 0) {
			cout << "ɾ���ڵ�ʱ���ڵ����ƴ���" << endl;
			return;
		}
		train_node_name_judge.erase(name);
		train_node_size -= 1;
		train_edges -= train_edge_list[name].size();//ɾ���ߵ���������ɾ���ڵ�ĳ���vector��size
		train_node_list[name].clear();//ɾ���ڵ�ĳ���
		train_edge_list[name].clear();//ɾ���ڵ�ĳ��ȱ�
		//����ɾ�����
		int pos = -1;//��ɾ���ڵ������
		for (int i = 0; i < train_node.size(); i++) {
			if (train_node[i].name == name) {
				pos = i;//��¼һ��pos,ʹ�ó�������Ч�ʸ���
				continue;
			}
			for (int j = 0; j < train_node_list[train_node[i].name].size(); j++) {
				if (train_node_list[train_node[i].name][j].name == name) {
					train_node_list[train_node[i].name].erase(train_node_list[train_node[i].name].begin() + j);
					train_edge_list[train_node[i].name].erase(train_edge_list[train_node[i].name].begin() + j);
					train_edges--;
				}
			}
		}
		//ɾ������ڵ�
		//int pos=compare_name_node[name];//��ɾ���ڵ������
		//�����δ�ҵ�pos
		if (pos == -1) {
			pos = find_train_city_name_pos(name);
		}
		train_node.erase(train_node.begin() + pos);//ɾ���ڵ�
		train_node_list.erase(name);
		train_edge_list.erase(name);
	}
	//ɾ���ڵ�(�ɻ�)
	void delete_plane_Node(string name) {
		if (plane_node_name_judge.count(name) == 0) {
			cout << "ɾ���ڵ�ʱ���ڵ����ƴ���" << endl;
			return;
		}
		plane_node_name_judge.erase(name);
		plane_node_size -= 1;
		plane_edges -= plane_edge_list[name].size();//ɾ���ߵ���������ɾ���ڵ�ĳ���vector��size
		plane_node_list[name].clear();//ɾ���ڵ�ĳ���
		plane_edge_list[name].clear();//ɾ���ڵ�ĳ��ȱ�
		//����ɾ�����
		int pos = -1;//��ɾ���ڵ������
		for (int i = 0; i < plane_node.size(); i++) {
			if (plane_node[i].name == name) {
				pos = i;//��¼һ��pos,ʹ�ó�������Ч�ʸ���
				continue;
			}
			for (int j = 0; j < plane_node_list[plane_node[i].name].size(); j++) {
				if (plane_node_list[plane_node[i].name][j].name == name) {
					plane_node_list[plane_node[i].name].erase(plane_node_list[plane_node[i].name].begin() + j);
					plane_edge_list[plane_node[i].name].erase(plane_edge_list[plane_node[i].name].begin() + j);
					plane_edges--;
				}
			}
		}
		//ɾ������ڵ�
		//�����δ�ҵ�pos
		if (pos == -1) {
			pos = find_train_city_name_pos(name);
		}
		plane_node.erase(plane_node.begin() + pos);//ɾ���ڵ�
		plane_node_list.erase(name);
		plane_edge_list.erase(name);
	}
	~Graph() {
		train_node_list.clear();
		train_edge_list.clear();
		train_node.clear();
		train_node_name_judge.clear();
		plane_node_list.clear();
		plane_edge_list.clear();
		plane_node.clear();
		plane_node_name_judge.clear();
	}
	//���·��(�Ͽ�����˹�㷨,��),�����ĵ���
	void fast_train_road(string start, string end) {
		//·������point��·����costΪȨֵ
		struct road {
			string point;
			double cost;//������ָ���ѵ�ʱ��
			vector<string> experience;//�м侭���Ľڵ�
		};
		vector<road> selecting;//���Ǻ�ѡ��Ҳ����ѡ·��
		set<string> selected_node;//�Ѿ�ѡ���Ľڵ�,�ù����ȵĽڵ�
		selected_node.insert(start);
		//��ʼ��,��һ����վĬ�ϲ��ȴ�
		for (int i = 0; i < train_node_list[start].size(); i++) {
			road a_road;
			a_road.point = train_node_list[start][i].name;
			a_road.cost = train_edge_list[start][i].total_time;
			//��Ϊ���һ���ڵ㣬�򲻼ӵȴ�ʱ��
			if (train_node_list[start][i].name != end) {
				a_road.cost += train_node_list[start][i].waiting_time;
			}
			selecting.push_back(a_road);
		}
		//����С
		int min_road_pos = 0;//��ǰ��С·����selecting�е��±�,ѡ��Ľ��һ���ǵ�һ���ڵ�ĳ��ȣ���˲������л�·
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//��name�ó���
		vector<string> min_road_experience = selecting[min_road_pos].experience;//��experience�ó���,��Щȫ���ó�������Ϊ�����һ���¾���ɾ��������·��
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//ѭ��������������end��·Ϊ��С
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//ɾ��������·��
			//��ѡ�񵽵Ľڵ���뵽��ѡ���У�
			selected_node.insert(point_name);
			//���º�ѡ�ߣ�����
			for (int i = 0; i < train_node_list[point_name].size(); i++) {
				if (selected_node.count(train_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//�Ȱ�vector���ƹ�����push
				a_road.experience.push_back(point_name);
				a_road.point = train_node_list[point_name][i].name;

				a_road.cost = train_edge_list[point_name][i].total_time + min_cost;
				//��Ϊ���һ���ڵ㣬�򲻼ӵȴ�ʱ��
				if (train_node_list[point_name][i].name != end) {
					a_road.cost += train_node_list[point_name][i].waiting_time;
				}
				//Ѱ����ͬ��point�����Ƚ�cost��С����
				bool judge = 0;//�����ж������ߵ�point��selecting���Ƿ��Ѿ�����
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == train_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + train_edge_list[point_name][i].total_time) {
							selecting.erase(selecting.begin() + j);//ɾ����ߣ�ɾ��ԭ���ı�
							selecting.push_back(a_road);//���ϸո�ѡ�ı�
						}
						//juddge=1 �ҵ���ͬ���ģ����ͬ�������cost��ԭ���Ĵ��ǾͲ����κ���
						judge = 1;
						break;//ֻ�����ҵ�һ����ͬ��������˵ͬ�յ㣬���break��
					}
				}
				//��������forѭ��û���ҵ���ͬ��point����Ĭ��push��selecting��
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//������С��
			min_road_pos = 0;
			min_cost = selecting[0].cost;
			for (int i = 1; i < selecting.size(); i++) {
				if (selecting[i].cost < min_cost) {
					min_road_pos = i;
					min_cost = selecting[i].cost;
				}
			}
			point_name = selecting[min_road_pos].point;
			min_road_experience = selecting[min_road_pos].experience;

		}
		cout << start << "->";
		for (int i = 0; i < selecting[min_road_pos].experience.size(); i++) {
			cout << selecting[min_road_pos].experience[i] << "->";
		}
		cout << end << " �ܵ�ʱ��:" << min_cost << endl;
	}

	//���·��(�Ͽ�����˹�㷨,�ɻ�),�ɻ����ĵ���
	void fast_plane_road(string start, string end) {
		//·������point��·����costΪȨֵ
		struct road {
			//string begin;
			string point;
			double cost;//������ָ���ѵ�ʱ��
			vector<string> experience;//�м侭���Ľڵ�
		};
		vector<road> selecting;//���Ǻ�ѡ��Ҳ����ѡ·��
		set<string> selected_node;//�Ѿ�ѡ���Ľڵ�,�ù����ȵĽڵ�
		selected_node.insert(start);
		//��ʼ��,��һ����վĬ�ϲ��ȴ�
		for (int i = 0; i < plane_node_list[start].size(); i++) {
			road a_road;
			a_road.point = plane_node_list[start][i].name;
			a_road.cost = plane_edge_list[start][i].total_time;
			//��Ϊ���һ���ڵ㣬�򲻼ӵȴ�ʱ��
			if (plane_node_list[start][i].name != end) {
				a_road.cost += plane_node_list[start][i].waiting_time;
			}
			selecting.push_back(a_road);
		}
		//����С
		int min_road_pos = 0;//��ǰ��С·����selecting�е��±�,ѡ��Ľ��һ���ǵ�һ���ڵ�ĳ��ȣ���˲������л�·
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//��name�ó���
		vector<string> min_road_experience = selecting[min_road_pos].experience;//��experience�ó���,��Щȫ���ó�������Ϊ�����һ���¾���ɾ��������·��
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//ѭ��������������end��·Ϊ��С
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//ɾ��������·��
			//��ѡ�񵽵Ľڵ���뵽��ѡ���У�
			selected_node.insert(point_name);
			//���º�ѡ�ߣ�����
			for (int i = 0; i < plane_node_list[point_name].size(); i++) {
				if (selected_node.count(plane_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//�Ȱ�vector���ƹ�����push
				a_road.experience.push_back(point_name);
				a_road.point = plane_node_list[point_name][i].name;
				a_road.cost = plane_edge_list[point_name][i].total_time + min_cost;
				//��Ϊ���һ���ڵ㣬�򲻼ӵȴ�ʱ��
				if (plane_node_list[point_name][i].name != end) {
					a_road.cost += plane_node_list[point_name][i].waiting_time;
				}
				//Ѱ����ͬ��point�����Ƚ�cost��С����
				bool judge = 0;//�����ж������ߵ�point��selecting���Ƿ��Ѿ�����
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == plane_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + plane_edge_list[point_name][i].total_time) {
							selecting.erase(selecting.begin() + j);//ɾ����ߣ�ɾ��ԭ���ı�
							selecting.push_back(a_road);//���ϸո�ѡ�ı�
						}
						//juddge=1 �ҵ���ͬ���ģ����ͬ�������cost��ԭ���Ĵ��ǾͲ����κ���
						judge = 1;
						break;//ֻ�����ҵ�һ����ͬ��������˵ͬ�յ㣬���break��
					}
				}
				//��������forѭ��û���ҵ���ͬ��point����Ĭ��push��selecting��
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//������С��
			min_road_pos = 0;
			min_cost = selecting[0].cost;
			for (int i = 1; i < selecting.size(); i++) {
				if (selecting[i].cost < min_cost) {
					min_road_pos = i;
					min_cost = selecting[i].cost;
				}
			}
			point_name = selecting[min_road_pos].point;
			min_road_experience = selecting[min_road_pos].experience;

		}
		cout << start << "->";
		for (int i = 0; i < selecting[min_road_pos].experience.size(); i++) {
			cout << selecting[min_road_pos].experience[i] << "->";
		}
		cout << end << " �ܵ�ʱ��:" << min_cost << endl;
	}
	//����ʡǮ����
	void cheap_train_road(string start, string end) {
		//·������point��·����costΪȨֵ
		struct road {
			//string begin;
			string point;
			double cost;//������ָ���ѵ�Ǯ
			vector<string> experience;//�м侭���Ľڵ�
		};
		vector<road> selecting;//���Ǻ�ѡ��Ҳ����ѡ·��
		set<string> selected_node;//�Ѿ�ѡ���Ľڵ�,�ù����ȵĽڵ�
		selected_node.insert(start);
		//��ʼ��,��һ����վĬ�ϲ��ȴ�
		for (int i = 0; i < train_node_list[start].size(); i++) {
			road a_road;
			a_road.point = train_node_list[start][i].name;
			a_road.cost = train_edge_list[start][i].money;
			selecting.push_back(a_road);
		}
		//����С
		int min_road_pos = 0;//��ǰ��С·����selecting�е��±�,ѡ��Ľ��һ���ǵ�һ���ڵ�ĳ��ȣ���˲������л�·
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//��name�ó���
		vector<string> min_road_experience = selecting[min_road_pos].experience;//��experience�ó���,��Щȫ���ó�������Ϊ�����һ���¾���ɾ��������·��
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//ѭ��������������end��·Ϊ��С
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//ɾ��������·��
			//��ѡ�񵽵Ľڵ���뵽��ѡ���У�
			selected_node.insert(point_name);
			//���º�ѡ�ߣ�����
			for (int i = 0; i < train_node_list[point_name].size(); i++) {
				if (selected_node.count(train_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//�Ȱ�vector���ƹ�����push
				a_road.experience.push_back(point_name);
				a_road.point = train_node_list[point_name][i].name;

				a_road.cost = train_edge_list[point_name][i].money + min_cost;
				//Ѱ����ͬ��point�����Ƚ�cost��С����
				bool judge = 0;//�����ж������ߵ�point��selecting���Ƿ��Ѿ�����
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == train_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + train_edge_list[point_name][i].money) {
							selecting.erase(selecting.begin() + j);//ɾ����ߣ�ɾ��ԭ���ı�
							selecting.push_back(a_road);//���ϸո�ѡ�ı�
						}
						//juddge=1 �ҵ���ͬ���ģ����ͬ�������cost��ԭ���Ĵ��ǾͲ����κ���
						judge = 1;
						break;//ֻ�����ҵ�һ����ͬ��������˵ͬ�յ㣬���break��
					}
				}
				//��������forѭ��û���ҵ���ͬ��point����Ĭ��push��selecting��
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//������С��
			min_road_pos = 0;
			min_cost = selecting[0].cost;
			for (int i = 1; i < selecting.size(); i++) {
				if (selecting[i].cost < min_cost) {
					min_road_pos = i;
					min_cost = selecting[i].cost;
				}
			}
			point_name = selecting[min_road_pos].point;
			min_road_experience = selecting[min_road_pos].experience;

		}
		cout << start << "->";
		for (int i = 0; i < selecting[min_road_pos].experience.size(); i++) {
			cout << selecting[min_road_pos].experience[i] << "->";
		}
		cout << end << " �ܵĽ�Ǯ:" << min_cost << endl;
	}

	//�ɻ���ʡǮ����
	void cheap_plane_road(string start, string end) {
		//·������point��·����costΪȨֵ
		struct road {
			//string begin;
			string point;
			double cost;//������ָ���ѵ�Ǯ
			vector<string> experience;//�м侭���Ľڵ�
		};
		vector<road> selecting;//���Ǻ�ѡ��Ҳ����ѡ·��
		set<string> selected_node;//�Ѿ�ѡ���Ľڵ�,�ù����ȵĽڵ�
		selected_node.insert(start);
		//��ʼ��,��һ����վĬ�ϲ��ȴ�
		for (int i = 0; i < plane_node_list[start].size(); i++) {
			road a_road;
			a_road.point = plane_node_list[start][i].name;
			a_road.cost = plane_edge_list[start][i].money;
			selecting.push_back(a_road);
		}
		//����С
		int min_road_pos = 0;//��ǰ��С·����selecting�е��±�,ѡ��Ľ��һ���ǵ�һ���ڵ�ĳ��ȣ���˲������л�·
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//��name�ó���
		vector<string> min_road_experience = selecting[min_road_pos].experience;//��experience�ó���,��Щȫ���ó�������Ϊ�����һ���¾���ɾ��������·��
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//ѭ��������������end��·Ϊ��С
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//ɾ��������·��
			//��ѡ�񵽵Ľڵ���뵽��ѡ���У�
			selected_node.insert(point_name);
			//���º�ѡ�ߣ�����
			for (int i = 0; i < plane_node_list[point_name].size(); i++) {
				if (selected_node.count(plane_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//�Ȱ�vector���ƹ�����push
				a_road.experience.push_back(point_name);
				a_road.point = plane_node_list[point_name][i].name;

				a_road.cost = plane_edge_list[point_name][i].money + min_cost;
				//Ѱ����ͬ��point�����Ƚ�cost��С����
				bool judge = 0;//�����ж������ߵ�point��selecting���Ƿ��Ѿ�����
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == plane_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + plane_edge_list[point_name][i].money) {
							selecting.erase(selecting.begin() + j);//ɾ����ߣ�ɾ��ԭ���ı�
							selecting.push_back(a_road);//���ϸո�ѡ�ı�
						}
						//juddge=1 �ҵ���ͬ���ģ����ͬ�������cost��ԭ���Ĵ��ǾͲ����κ���
						judge = 1;
						break;//ֻ�����ҵ�һ����ͬ��������˵ͬ�յ㣬���break��
					}
				}
				//��������forѭ��û���ҵ���ͬ��point����Ĭ��push��selecting��
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//������С��
			min_road_pos = 0;
			min_cost = selecting[0].cost;
			for (int i = 1; i < selecting.size(); i++) {
				if (selecting[i].cost < min_cost) {
					min_road_pos = i;
					min_cost = selecting[i].cost;
				}
			}
			point_name = selecting[min_road_pos].point;
			min_road_experience = selecting[min_road_pos].experience;

		}
		cout << start << "->";
		for (int i = 0; i < selecting[min_road_pos].experience.size(); i++) {
			cout << selecting[min_road_pos].experience[i] << "->";
		}
		cout << end << " �ܵĽ�Ǯ:" << min_cost << endl;
	}
	void query_city_waiting_time(string city) {
		int pos = find_train_city_name_pos(city);
		cout << "����תʱ�䣺" << train_node[pos].waiting_time << endl;
		int pos2 = find_plane_city_name_pos(city);
		cout << "�ɻ���תʱ�䣺" << plane_node[pos].waiting_time << endl;
	}
	void edit_waiting_time(string city, double time1, double time2) {
		int pos = find_train_city_name_pos(city);
		int pos2 = find_plane_city_name_pos(city);
		train_node[pos].waiting_time = time1;
		plane_node[pos2].waiting_time = time2;
	}
};

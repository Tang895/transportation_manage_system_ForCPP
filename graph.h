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
#include<fstream>//文件
#include<sstream>
#include"time.h"

#define str string
#define float double
#define ll long long
using namespace std;



//有向图
template<class T>
class Graph {
private:
	int train_node_size;//火车节点数量
	int plane_node_size;//飞机节点数量
	int train_edges;//火车线路（班次）数
	int plane_edges;//飞机线路（班次）数

	struct train_Node {
		string name;//城市名字
		double waiting_time;//火车中转等待时间
	};
	struct train_Edge {
		double distance;//火车的路程
		string code;
		struct time start_time;//火车起始时间
		struct time end_time;//火车到达时间
		double total_time;//火车总用时
		double money;//火车票价格
	};
	struct plane_Node {
		string name;//城市名字
		double waiting_time;//飞机中转等待时间
	};
	struct plane_Edge {
		double distance;//飞机的路程，单位（m）
		string code;
		struct time start_time;//飞机起始时间
		struct time end_time;//飞机到达时间
		double total_time;//飞机总用时
		double money;//飞机票价格
	};
	vector<train_Node> train_node;//火车城市网络
	vector<plane_Node> plane_node;//飞机城市网络
	map<string, vector<train_Node>> train_node_list; //火车节点名称对邻接表的映射
	map<string, vector<plane_Node>> plane_node_list; //飞机节点名称对邻接表的映射
	map<string, vector<train_Edge>> train_edge_list;//火车线路,pos一一对应，对邻接边的映射
	map<string, vector<plane_Edge>> plane_edge_list;//飞机线路
	set<string> train_node_name_judge;//存储所有拥有的节点的名字的集合,城市名字
	set<string> plane_node_name_judge;//存储所有拥有的节点的名字的集合,城市名字


public:
	Graph() {
		train_node_size = 0;
		train_edges = 0;
		plane_node_size = 0;
		plane_edges = 0;
	}
	//根据节点名字找下标（城市名字，火车）
	int find_train_city_name_pos(string name) {
		for (int i = 0; i < train_node.size(); i++) {
			if (name == train_node[i].name) {
				return i;
			}
		}
		cout << ("未找到节点名称");
		return -1;
	}
	//根据节点名字找下标（城市名字,飞机）
	int find_plane_city_name_pos(string name) {
		for (int i = 0; i < plane_node.size(); i++) {
			if (name == plane_node[i].name) {
				return i;
			}
		}
		cout << ("未找到节点名称");
		return -1;
	}
	int get_train_size() {
		return train_node_size;
	}
	int get_plane_size() {
		return plane_node_size;
	}
	//得到A->B的路程(火车)
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
	//得到A->B的路程(飞机)
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
	//删除一条路(火车),node_A->node_B
	void delete_train_edge(string node_A, string node_B) {
		if (train_node_name_judge.count(node_A) == 0 || train_node_name_judge.count(node_B) == 0) {
			cout << "删除路径时，节点名称错误" << endl;
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
	//删除一条路(飞机),node_A->node_B
	void delete_plane_edge(string node_A, string node_B) {
		if (plane_node_name_judge.count(node_A) == 0 || plane_node_name_judge.count(node_B) == 0) {
			cout << "删除路径时，节点名称错误" << endl;
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
	//修改城市名字
	void edit_name(string city_A, string city_B) { //将A城市的名字改为city_B
		//火车
		int pos = find_train_city_name_pos(city_A);
		//先修改所有非city_A节点的出度
		for (int i = 0; i < train_node_size; i++) {
			if (i == pos)  //如果遍历到待修改的城市的出度，则continue
				continue;
			//train_node_list[train_node[i].name];
			for (int j = 0; j < train_node_list[train_node[i].name].size(); j++) {
				if (train_node_list[train_node[i].name][j].name == city_A)
					train_node_list[train_node[i].name][j].name = city_B;
			}
		}
		//city_A节点
		train_node[pos].name = city_B;
		//将判断城市名称的容器更新
		train_node_name_judge.erase(city_A);
		train_node_name_judge.insert(city_B);
		train_node_list[city_B] = train_node_list[city_A];
		train_edge_list[city_B] = train_edge_list[city_A];
		train_node_list.erase(city_A);
		train_edge_list.erase(city_A);


		//对于飞机的名字修改
		pos = find_plane_city_name_pos(city_A);
		//先修改所有非city_A节点的出度
		for (int i = 0; i < plane_node_size; i++) {
			if (i == pos)  //如果遍历到待修改的城市的出度，则continue
				continue;
			//plane_node_list[plane_node[i].name];
			for (int j = 0; j < plane_node_list[plane_node[i].name].size(); j++) {
				if (plane_node_list[plane_node[i].name][j].name == city_A)
					plane_node_list[plane_node[i].name][j].name = city_B;
			}
		}
		//city_A节点
		plane_node[pos].name = city_B;
		//将判断城市名称的容器更新
		plane_node_name_judge.erase(city_A);
		plane_node_name_judge.insert(city_B);
		plane_node_list[city_B] = plane_node_list[city_A];
		plane_edge_list[city_B] = plane_edge_list[city_A];
		plane_edge_list.erase(city_A);
		plane_node_list.erase(city_A);
	}
	//添加一个节点,添加一个城市(火车)
	void add_train_node(string name, double waiting_time) {
		//如果重复，则覆盖
		train_node_name_judge.insert(name);
		train_node_size += 1;
		train_Node newnode;
		newnode.name = name;
		newnode.waiting_time = waiting_time;
		train_node.push_back(newnode);
	}
	//添加一个节点,添加一个城市(飞机)
	void add_plane_node(string name, double waiting_time) {
		//如果已经有了城市，默认覆盖
		plane_node_name_judge.insert(name);
		plane_node_size += 1;
		plane_Node newnode;
		newnode.name = name;
		newnode.waiting_time = waiting_time;
		plane_node.push_back(newnode);
	}
	//添加n个节点
	void add_train_nodes(int n) {
		string name;
		for (int i = 0; i < n; i++) {
			cin >> name;
			add_train_node(name);
		}
	}
	//添加n个节点(飞机节点)
	void add_plane_nodes(int n) {
		string name;
		for (int i = 0; i < n; i++) {
			cin >> name;
			add_plane_node(name);
		}
	}
	//添加一个关系,添加一条线路(火车)
	void add_one_train_way(string node_A, string node_B, string code, double cost, struct time start, struct time end\
		, double total_time, double money)
	{
		if (train_node_name_judge.count(node_A) == 0 || train_node_name_judge.count(node_B) == 0) {
			cout << "添加火车线路时，城市节点名称错误" << endl;
			return;
		}
		train_Edge new_edge;//新线路
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
	//添加一个关系,添加一条线路(飞机)
	void add_one_plane_way(string node_A, string node_B, string code, double cost, struct time start, struct time end\
		, double total_time, double money)
	{
		if (plane_node_name_judge.count(node_A) == 0 || plane_node_name_judge.count(node_B) == 0) {
			cout << "添加飞机线路时，城市节点名称错误" << endl;
			return;
		}
		plane_Edge new_edge;//新线路
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
	//添加n个线路(火车)
	void add_train_way(int edges) {
		cout << "输入关系：" << endl;
		for (int i = 0; i < edges; i++) {
			string node_A, node_B;
			int cost;
			cin >> node_A >> node_B >> cost;
			add_one_train_way(node_A, node_B, cost);
		}
	}
	//添加n个线路(飞机)
	void add_plane_way(int edges) {
		cout << "输入关系：" << endl;
		for (int i = 0; i < edges; i++) {
			string node_A, node_B;
			int cost;
			cin >> node_A >> node_B >> cost;
			add_one_plane_way(node_A, node_B, cost);
		}
	}


	void show_train(void) {
		cout << "火车线路：" << endl;
		for (int i = 0; i < train_node.size(); i++) {
			for (int j = 0; j < train_node_list[train_node[i].name].size(); j++) {
				cout << train_node[i].name << "->";
				cout << train_node_list[train_node[i].name][j].name << "::路程:";
				cout << train_edge_list[train_node[i].name][j].distance;
				cout << " 车次：" << train_edge_list[train_node[i].name][j].code;
				cout << " 开始时间："; train_edge_list[train_node[i].name][j].start_time.show();
				cout << " 结束时间："; train_edge_list[train_node[i].name][j].end_time.show();
				cout << " 总用时：" << train_edge_list[train_node[i].name][j].total_time;
				cout << " 价格：" << train_edge_list[train_node[i].name][j].money;
				cout << endl;
			}

		}

	}
	void show_plane(void) {
		/*cout << "飞机节点数：" << train_node_size << endl;;
		cout << "飞机线路的数量：" << train_edges << endl;*/
		cout << "飞机线路：" << endl;
		for (int i = 0; i < plane_node.size(); i++) {
			for (int j = 0; j < plane_node_list[plane_node[i].name].size(); j++) {
				cout << plane_node[i].name << "->";
				cout << plane_node_list[plane_node[i].name][j].name << "::距离: ";
				cout << plane_edge_list[plane_node[i].name][j].distance;
				cout << " 航班代码：" << plane_edge_list[plane_node[i].name][j].code;
				cout << " 开始时间："; plane_edge_list[plane_node[i].name][j].start_time.show();
				cout << " 结束时间："; plane_edge_list[plane_node[i].name][j].end_time.show();
				cout << " 总用时：" << plane_edge_list[plane_node[i].name][j].total_time;
				cout << " 价格：" << plane_edge_list[plane_node[i].name][j].money;
				cout << endl;
			}
		}
	}

	//删除节点(火车)
	void delete_train_Node(string name) {
		if (train_node_name_judge.count(name) == 0) {
			cout << "删除节点时，节点名称错误" << endl;
			return;
		}
		train_node_name_judge.erase(name);
		train_node_size -= 1;
		train_edges -= train_edge_list[name].size();//删除边的数量，被删除节点的出度vector的size
		train_node_list[name].clear();//删除节点的出度
		train_edge_list[name].clear();//删除节点的出度边
		//遍历删除入度
		int pos = -1;//待删除节点的坐标
		for (int i = 0; i < train_node.size(); i++) {
			if (train_node[i].name == name) {
				pos = i;//记录一下pos,使得程序运行效率更高
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
		//删除这个节点
		//int pos=compare_name_node[name];//待删除节点的坐标
		//如果仍未找到pos
		if (pos == -1) {
			pos = find_train_city_name_pos(name);
		}
		train_node.erase(train_node.begin() + pos);//删除节点
		train_node_list.erase(name);
		train_edge_list.erase(name);
	}
	//删除节点(飞机)
	void delete_plane_Node(string name) {
		if (plane_node_name_judge.count(name) == 0) {
			cout << "删除节点时，节点名称错误" << endl;
			return;
		}
		plane_node_name_judge.erase(name);
		plane_node_size -= 1;
		plane_edges -= plane_edge_list[name].size();//删除边的数量，被删除节点的出度vector的size
		plane_node_list[name].clear();//删除节点的出度
		plane_edge_list[name].clear();//删除节点的出度边
		//遍历删除入度
		int pos = -1;//待删除节点的坐标
		for (int i = 0; i < plane_node.size(); i++) {
			if (plane_node[i].name == name) {
				pos = i;//记录一下pos,使得程序运行效率更高
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
		//删除这个节点
		//如果仍未找到pos
		if (pos == -1) {
			pos = find_train_city_name_pos(name);
		}
		plane_node.erase(plane_node.begin() + pos);//删除节点
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
	//最短路径(迪克特拉斯算法,火车),火车最快的到达
	void fast_train_road(string start, string end) {
		//路径，到point的路径，cost为权值
		struct road {
			string point;
			double cost;//这里是指花费的时间
			vector<string> experience;//中间经过的节点
		};
		vector<road> selecting;//既是候选，也是已选路径
		set<string> selected_node;//已经选到的节点,拿过出度的节点
		selected_node.insert(start);
		//初始化,第一个车站默认不等待
		for (int i = 0; i < train_node_list[start].size(); i++) {
			road a_road;
			a_road.point = train_node_list[start][i].name;
			a_road.cost = train_edge_list[start][i].total_time;
			//若为最后一个节点，则不加等待时间
			if (train_node_list[start][i].name != end) {
				a_road.cost += train_node_list[start][i].waiting_time;
			}
			selecting.push_back(a_road);
		}
		//找最小
		int min_road_pos = 0;//当前最小路径在selecting中的下标,选择的结果一定是第一个节点的出度，因此不用特判回路
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//把name拿出来
		vector<string> min_road_experience = selecting[min_road_pos].experience;//把experience拿出来,这些全部拿出来，因为待会第一件事就是删除这个最短路径
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//循环截至条件，到end的路为最小
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//删除这个最短路径
			//将选择到的节点加入到已选边中，
			selected_node.insert(point_name);
			//更新候选边，遍历
			for (int i = 0; i < train_node_list[point_name].size(); i++) {
				if (selected_node.count(train_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//先把vector复制过来再push
				a_road.experience.push_back(point_name);
				a_road.point = train_node_list[point_name][i].name;

				a_road.cost = train_edge_list[point_name][i].total_time + min_cost;
				//若为最后一个节点，则不加等待时间
				if (train_node_list[point_name][i].name != end) {
					a_road.cost += train_node_list[point_name][i].waiting_time;
				}
				//寻找相同的point，并比较cost大小更新
				bool judge = 0;//用于判断这条边的point在selecting中是否已经具有
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == train_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + train_edge_list[point_name][i].total_time) {
							selecting.erase(selecting.begin() + j);//删除大边，删除原来的边
							selecting.push_back(a_road);//加上刚刚选的边
						}
						//juddge=1 找到了同名的，如果同名的这个cost比原来的大，那就不做任何事
						judge = 1;
						break;//只可能找到一条边同名，或者说同终点，因此break掉
					}
				}
				//如果上面的for循环没有找到相同的point，则默认push到selecting中
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//更新最小边
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
		cout << end << " 总的时间:" << min_cost << endl;
	}

	//最短路径(迪克特拉斯算法,飞机),飞机最快的到达
	void fast_plane_road(string start, string end) {
		//路径，到point的路径，cost为权值
		struct road {
			//string begin;
			string point;
			double cost;//这里是指花费的时间
			vector<string> experience;//中间经过的节点
		};
		vector<road> selecting;//既是候选，也是已选路径
		set<string> selected_node;//已经选到的节点,拿过出度的节点
		selected_node.insert(start);
		//初始化,第一个车站默认不等待
		for (int i = 0; i < plane_node_list[start].size(); i++) {
			road a_road;
			a_road.point = plane_node_list[start][i].name;
			a_road.cost = plane_edge_list[start][i].total_time;
			//若为最后一个节点，则不加等待时间
			if (plane_node_list[start][i].name != end) {
				a_road.cost += plane_node_list[start][i].waiting_time;
			}
			selecting.push_back(a_road);
		}
		//找最小
		int min_road_pos = 0;//当前最小路径在selecting中的下标,选择的结果一定是第一个节点的出度，因此不用特判回路
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//把name拿出来
		vector<string> min_road_experience = selecting[min_road_pos].experience;//把experience拿出来,这些全部拿出来，因为待会第一件事就是删除这个最短路径
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//循环截至条件，到end的路为最小
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//删除这个最短路径
			//将选择到的节点加入到已选边中，
			selected_node.insert(point_name);
			//更新候选边，遍历
			for (int i = 0; i < plane_node_list[point_name].size(); i++) {
				if (selected_node.count(plane_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//先把vector复制过来再push
				a_road.experience.push_back(point_name);
				a_road.point = plane_node_list[point_name][i].name;
				a_road.cost = plane_edge_list[point_name][i].total_time + min_cost;
				//若为最后一个节点，则不加等待时间
				if (plane_node_list[point_name][i].name != end) {
					a_road.cost += plane_node_list[point_name][i].waiting_time;
				}
				//寻找相同的point，并比较cost大小更新
				bool judge = 0;//用于判断这条边的point在selecting中是否已经具有
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == plane_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + plane_edge_list[point_name][i].total_time) {
							selecting.erase(selecting.begin() + j);//删除大边，删除原来的边
							selecting.push_back(a_road);//加上刚刚选的边
						}
						//juddge=1 找到了同名的，如果同名的这个cost比原来的大，那就不做任何事
						judge = 1;
						break;//只可能找到一条边同名，或者说同终点，因此break掉
					}
				}
				//如果上面的for循环没有找到相同的point，则默认push到selecting中
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//更新最小边
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
		cout << end << " 总的时间:" << min_cost << endl;
	}
	//火车最省钱到达
	void cheap_train_road(string start, string end) {
		//路径，到point的路径，cost为权值
		struct road {
			//string begin;
			string point;
			double cost;//这里是指花费的钱
			vector<string> experience;//中间经过的节点
		};
		vector<road> selecting;//既是候选，也是已选路径
		set<string> selected_node;//已经选到的节点,拿过出度的节点
		selected_node.insert(start);
		//初始化,第一个车站默认不等待
		for (int i = 0; i < train_node_list[start].size(); i++) {
			road a_road;
			a_road.point = train_node_list[start][i].name;
			a_road.cost = train_edge_list[start][i].money;
			selecting.push_back(a_road);
		}
		//找最小
		int min_road_pos = 0;//当前最小路径在selecting中的下标,选择的结果一定是第一个节点的出度，因此不用特判回路
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//把name拿出来
		vector<string> min_road_experience = selecting[min_road_pos].experience;//把experience拿出来,这些全部拿出来，因为待会第一件事就是删除这个最短路径
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//循环截至条件，到end的路为最小
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//删除这个最短路径
			//将选择到的节点加入到已选边中，
			selected_node.insert(point_name);
			//更新候选边，遍历
			for (int i = 0; i < train_node_list[point_name].size(); i++) {
				if (selected_node.count(train_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//先把vector复制过来再push
				a_road.experience.push_back(point_name);
				a_road.point = train_node_list[point_name][i].name;

				a_road.cost = train_edge_list[point_name][i].money + min_cost;
				//寻找相同的point，并比较cost大小更新
				bool judge = 0;//用于判断这条边的point在selecting中是否已经具有
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == train_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + train_edge_list[point_name][i].money) {
							selecting.erase(selecting.begin() + j);//删除大边，删除原来的边
							selecting.push_back(a_road);//加上刚刚选的边
						}
						//juddge=1 找到了同名的，如果同名的这个cost比原来的大，那就不做任何事
						judge = 1;
						break;//只可能找到一条边同名，或者说同终点，因此break掉
					}
				}
				//如果上面的for循环没有找到相同的point，则默认push到selecting中
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//更新最小边
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
		cout << end << " 总的金钱:" << min_cost << endl;
	}

	//飞机最省钱到达
	void cheap_plane_road(string start, string end) {
		//路径，到point的路径，cost为权值
		struct road {
			//string begin;
			string point;
			double cost;//这里是指花费的钱
			vector<string> experience;//中间经过的节点
		};
		vector<road> selecting;//既是候选，也是已选路径
		set<string> selected_node;//已经选到的节点,拿过出度的节点
		selected_node.insert(start);
		//初始化,第一个车站默认不等待
		for (int i = 0; i < plane_node_list[start].size(); i++) {
			road a_road;
			a_road.point = plane_node_list[start][i].name;
			a_road.cost = plane_edge_list[start][i].money;
			selecting.push_back(a_road);
		}
		//找最小
		int min_road_pos = 0;//当前最小路径在selecting中的下标,选择的结果一定是第一个节点的出度，因此不用特判回路
		double min_cost = selecting[0].cost;
		string point_name = selecting[0].point;//把name拿出来
		vector<string> min_road_experience = selecting[min_road_pos].experience;//把experience拿出来,这些全部拿出来，因为待会第一件事就是删除这个最短路径
		for (int i = 1; i < selecting.size(); i++) {
			if (selecting[i].cost < min_cost) {
				min_road_pos = i;
				min_cost = selecting[i].cost;
				min_road_experience = selecting[i].experience;
				point_name = selecting[i].point;
			}
		}
		//循环截至条件，到end的路为最小
		while (selecting[min_road_pos].point != end) {
			selecting.erase(selecting.begin() + min_road_pos);//删除这个最短路径
			//将选择到的节点加入到已选边中，
			selected_node.insert(point_name);
			//更新候选边，遍历
			for (int i = 0; i < plane_node_list[point_name].size(); i++) {
				if (selected_node.count(plane_node_list[point_name][i].name))
					continue;
				road a_road;
				a_road.experience = min_road_experience;//先把vector复制过来再push
				a_road.experience.push_back(point_name);
				a_road.point = plane_node_list[point_name][i].name;

				a_road.cost = plane_edge_list[point_name][i].money + min_cost;
				//寻找相同的point，并比较cost大小更新
				bool judge = 0;//用于判断这条边的point在selecting中是否已经具有
				for (int j = 0; j < selecting.size(); j++) {
					if (selecting[j].point == plane_node_list[point_name][i].name) {
						if (selecting[j].cost > min_cost + plane_edge_list[point_name][i].money) {
							selecting.erase(selecting.begin() + j);//删除大边，删除原来的边
							selecting.push_back(a_road);//加上刚刚选的边
						}
						//juddge=1 找到了同名的，如果同名的这个cost比原来的大，那就不做任何事
						judge = 1;
						break;//只可能找到一条边同名，或者说同终点，因此break掉
					}
				}
				//如果上面的for循环没有找到相同的point，则默认push到selecting中
				if (judge == 0) {
					selecting.push_back(a_road);
				}
			}
			//更新最小边
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
		cout << end << " 总的金钱:" << min_cost << endl;
	}
	void query_city_waiting_time(string city) {
		int pos = find_train_city_name_pos(city);
		cout << "火车中转时间：" << train_node[pos].waiting_time << endl;
		int pos2 = find_plane_city_name_pos(city);
		cout << "飞机中转时间：" << plane_node[pos].waiting_time << endl;
	}
	void edit_waiting_time(string city, double time1, double time2) {
		int pos = find_train_city_name_pos(city);
		int pos2 = find_plane_city_name_pos(city);
		train_node[pos].waiting_time = time1;
		plane_node[pos2].waiting_time = time2;
	}
};

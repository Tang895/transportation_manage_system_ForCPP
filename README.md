# transportation_manage_system_ForCPP
## 交通咨询系统，C++课设，迪杰斯特拉单源最短路径
城市-->cities.txt
火车行程信息-->train.txt
飞机行程信息-->flight.txt
## 数据结构设计
以火车线路为例：`map<string, vector<train_Node>> train_node_list;`
string为城市名字，train_Node为结构体，详情如下：
```C++
struct train_Edge {
		double distance;//火车的路程
		string code;
		struct time start_time;//火车起始时间
		struct time end_time;//火车到达时间
		double total_time;//火车总用时
		double money;//火车票价格
	};
```
todo...

# transportation_manage_system_ForCPP
## 交通咨询系统，C++课设，迪杰斯特拉单源最短路径
城市-->cities.txt
火车行程信息-->train.txt
飞机行程信息-->flight.txt
## 数据结构设计
以火车线路为例：`map<string, vector<train_Node>> train_node_list;`
string为城市名字，train_Node为结构体，详情如下：
```C++
struct train_Node {
		string name;//城市名字
		double waiting_time;//火车中转等待时间
	};
```
todo...

# 图(graph)

### 定义

---

​	图是由顶点的有穷非空集合和顶点之间的集合组成，通常表示为：G(V,E),其中G表示一个图，V是图G中顶点的集合，E是图G中边(edge)的集合

​	tips：

- 线性表中的数据元素被称为元素，树种将数据元素称为结点，而图中的数据元素被称为顶点
- 线性表可以没有数据元素，树也可以没有结点，但是图的定义种强调了顶点集合V是有穷非空的集合，所以图结构种不能没有顶点
- 线性表中，相邻的数据元素具有线性关系，树结构中，相邻两层的结点具有层次关系，而图中，任意两个顶点之间都可能有关系，顶点之间的逻辑关系用边来表示，边集可以是空的

​	一个顶点(vertice)包含的相邻顶点的数量被称为度

### 各种图

---

​	如果图中节点之间的边线是单向的，则被称为有向图

![image-20211114192527930](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211114192527930.png)

如果图中节点之间的边线是双向的，或者没有一个明确的指向，则被称为无向图

![image-20211114192613922](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211114192613922.png)

### 图的实现

---

##### 邻接矩阵

​	使用二维数组表达各个顶点之间的关系

![image-20211114192738970](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211114192738970.png)

##### 邻接表

​	邻接表由图中每个顶点的相邻顶点列表组成，可以使用数组、链表等来表示相邻顶点列表

![image-20211114221313046](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211114221313046.png)

​								<img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211115191958481.png" alt="image-20211115191958481"  /><img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211115192032355.png" alt="image-20211115192032355"  />



### 拓扑排序(topological order)

---

##### 定义

​	对于任何有向图而言，其拓扑排序为其所有结点的一个线性排序（对于同一个有向图而言可能存在多个这样的结点排序）。

​	该排序满足这样的条件：对于图中的任意两个结点u和v，若存在一条有向边从u指向v，则在拓扑排序中u一定出现在v前面

​	当且仅当一个有向图为有向无环图(directed acyclic graph, DAG)时，才能得到对应于该图的拓扑排序，每一个有向无环图都至少存在一种拓扑排序

##### 例

![image-20211115171815072](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211115171815072.png)

该有向无环图的拓扑排序是：[1,2,3,4,5]和[1,2,3,5,4]

### 迪杰斯特拉算法(Dijkstra)

---

​	Dijkstra算法是最短路径算法，同于计算一个节点到其他节点的最短路径，特点是以起始点为中心向外层层扩展(广度优先)，直到扩展到终点为止。

​	就是每次对所有可见点的路径长度进行排序以后选择一条最短的路径，这条路径就是对应顶点到原点的最短路口

##### 算法实现

- 从V0出发，与V0间没有边的顶点与V0的距离设定为无穷大
- 找到距V0距离最近的顶点，更新最短距离表
- 假设上一步找到的顶点是V2，再找到距离V2最近的顶点，设这个点为V5
- 如果V0-V2-V5 < V0-V5，更新表格，表格中V0-V5的最短距离为V0-V2-V5
- 如果V0-V2-V5 > V0-V5，更新表格，表格中V0-V5的最短距离为V0-V5

- 依此类推

### 加权无向图(weighted undirected graph)

---


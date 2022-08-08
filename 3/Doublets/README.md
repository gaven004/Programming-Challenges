解题的思路并不复杂，对于给出的词典，按词长，构建一个图，以词为顶点，为Doublet的词相连

![doublet graph](doublet%20graph.png "doublet graph")

之后找到开始的点，用宽度优先遍历。

BTW，BSF是一个优雅的算法

由于字典的词数有25000+，开始的时候，开的空间比较大，16 * 25000 * 25000，超过内存限制，提交运行报Runtime Error，未能定位错误。改用Java实现一次，AC，但时间要1s多。

回到C的版本，统一空间存储字典，其它改用指针，内存足够，提交获AC。时间0.290s，有些慢。于是改图的实现结构，从连接矩阵，改为链表，时间降到0.070s。

尝试对字典排序，更慢，说明测试数据中的单词对并不多，简单查找已是比较高效。

增加一些小优化，延迟构建单词连接的图，当需要时才构建，测试的时间有提高，其实算法并没有优化，只是说明测试的数据中，单词对并不是每种长度都有。

时间分析，构建图是最用时的一步，其它的环节用时都不多。读入数据有一些，是构建图的1/10以下。Search，意外地用时不多，比前面两个环节都小。
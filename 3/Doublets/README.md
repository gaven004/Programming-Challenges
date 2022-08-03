解题的思路并不复杂，对于给出的词典，按词长，构建一个图，以词为顶点，为Doublet的词相连

![doublet graph](doublet%20graph.png "doublet graph")

之后找到开始的点，用宽度优先遍历。

BTW，BSF是一个优雅的算法

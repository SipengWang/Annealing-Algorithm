# Annealing Algorithm

Reference: [This Blog](https://www.cnblogs.com/cieusy/p/9871095.html)<br>
<br>
By Sipeng Wang<br>

1. 生成途经点地图，邻接矩阵以及初始的随机路径，计算初始路径下的总距离<br>
2. 在路径中随机取两个点，交换位置，求取新的路径下的总长度。如果新的长度比原长度小，则取新的长度；如果新的长度比原先长度大，则按照确信概率取新的长度<br>
3. 更新退火温度，重复步骤2，直至满足条件退出程序<br>

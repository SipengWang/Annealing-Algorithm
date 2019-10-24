#include <QCoreApplication>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define NUMBER 50
#define L 20000
#define T 1e-5
#define ALPHA 0.99

class Map
{
public:
    int map_array[NUMBER][2];
    int path[NUMBER];
    double distance;
    double dist[NUMBER][NUMBER];
};

void ini_map(Map &map)
{
    int i, j;
    vector<int> temp;
    unsigned seed;

    seed = time(0);
    srand(seed);

    //生成随机地图
    for(i = 0; i < NUMBER; i++)
    {
        for(j = 0; j < 2; j++)
        {
            map.map_array[i][j] = rand() % 100 + 1;
        }
    }

    //生成随机路径
    for(i = 0; i < NUMBER; i++)
    {
        temp.push_back(i);
    }


    random_shuffle(temp.begin(), temp.end());

    for(i = 0; i < NUMBER; i++)
        map.path[i] = temp[i];

    //计算距离邻接矩阵
    for(i = 0; i < NUMBER; i++)
    {
        for(j = 0; j <= i; j++)
        {
            if(i == j)
                map.dist[i][i] = 0;
            else
            {
                int x = map.map_array[i][0] - map.map_array[j][0];
                int y = map.map_array[i][1] - map.map_array[j][1];
                map.dist[i][j] = sqrt(x * x + y * y);
            }
        }
    }

    for(i = 0; i < NUMBER; i++)
    {
        for(j = i + 1; j < NUMBER; j++)
            map.dist[i][j] = map.dist[j][i];
    }


    //计算初始距离

    map.distance = 0;
    for(i = 0; i < NUMBER - 1; i++)
    {
        map.distance += map.dist[map.path[i]][map.path[i + 1]];
    }


}

Map Ann_Alg(Map &map)
{
    Map curr = map;
    Map next = map;
    int temp;
    int x, y;
    int i, j;
    double change;
    double t = 1;

    for(i = 0; i < L; i++)
    {
        do{
            x = rand() % NUMBER;
            y = rand() % NUMBER;
        }while (x >= y);

        temp = next.path[x];
        next.path[x] = next.path[y];
        next.path[y] = temp;

        next.distance = 0;
        for(j = 0; j < NUMBER - 1; j++)
        {
            next.distance += next.dist[next.path[j]][next.path[j + 1]];
        }

        change = curr.distance - next.distance;

        if(change < 0)
            curr = next;
        else if(exp(-change / t) >= rand() / (RAND_MAX + 1.0))
            curr = next;
        else
            next = curr;

        t = t * ALPHA;

        if(t < T)
            break;

    }
    return curr;
}


int main(void)
{
    Map map, result;

    ini_map(map);

    result = Ann_Alg(map);

    cout << "Minimum Distance = " << result.distance << endl;
    cout << "Best Path is: " << endl;
    for(int i = 0; i < NUMBER; i++)
    {
        int temp = result.path[i];
        cout << result.map_array[temp][0] << "," << result.map_array[temp][1] << endl;
    }

    return 0;

}

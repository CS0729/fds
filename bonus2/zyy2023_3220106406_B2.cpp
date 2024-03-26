/*Author:Chen Shuo; ID:3220106406; No:02*/
#include<windows.h> 
#include<iostream> 
#include<vector> 
#include<map> 
using namespace std;

int main() {
    int N, M, value; // 定义整型变量N、M和value，分别表示数字序列的长度、每一段的长度和输入的数字
    scanf("%d%d", &N, &M); 

    map<int, int> mapA, mapB; // 定义两个映射容器mapA和mapB，用于存储数字出现的次数

    for (int i = 0; i < M; i++) { // 循环M次，读取M个数字
        scanf("%d", &value); // 从标准输入中读取一个数字
        mapA[value]++; // 将该数字存入mapA中，并增加其出现次数
    }

    vector<int> tmp; // 定义一个整型向量tmp，用于存储每一段的解
    vector<vector<int>> ans; // 定义一个二维整型向量ans，用于存储所有的解

    for (int i = M; i < N; i++) { // 循环N-M次，读取N-M个数字
        scanf("%d", &value); // 从标准输入中读取一个数字
        int head = mapA.begin()->first; // 获取mapA中的最小值作为头部值

        if (mapA.begin()->second == 1) // 如果头部值的出现次数为1
            mapA.erase(mapA.begin()); // 则从mapA中删除该键值对
        else
            mapA[mapA.begin()->first]--; // 否则将头部值的出现次数减1

        tmp.push_back(head); // 将头部值存入tmp中

        if (value >= head)
            mapA[value]++; // 如果当前数字大于等于头部值，则将该数字存入mapA中
        else
            mapB[value]++; // 否则将该数字存入mapB中

        if (mapA.size() == 0) { // 如果mapA中的数字全部处理完毕
            mapA = mapB; // 那就将mapB中的数字存入mapA中
            mapB.clear(); // 然后清空mapB
            ans.push_back(tmp); // 将本轮的解tmp存入ans中
            tmp.clear(); // 最后清空tmp
        }

        if (i == N - 1) { // 如果到了最后一个数字
            while (mapA.size()) { // 循环处理mapA中的数字
                tmp.push_back(mapA.begin()->first); // 将mapA中的数字存入tmp中

                if (mapA.begin()->second == 1) // 如果数字的出现次数为1
                    mapA.erase(mapA.begin()); // 则从mapA中删除该键值对
                else
                    mapA[mapA.begin()->first]--; // 否则将数字的出现次数减1
            }

            if (tmp.size() > 0)
                ans.push_back(tmp); // 将tmp存入ans中

            tmp.clear(); // 清空tmp

            while (mapB.size()) { // 循环处理mapB中的数字
                tmp.push_back(mapB.begin()->first); // 将mapB中的数字存入tmp中

                if (mapB.begin()->second == 1) // 如果数字的出现次数为1
                    mapB.erase(mapB.begin()); // 则从mapB中删除该键值对
                else
                    mapB[mapB.begin()->first]--; // 否则将数字的出现次数减1
            }

            ans.push_back(tmp); // 将tmp存入ans中
        }
    }
//输出
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) { 
            if (j == 0)
                printf("%d", ans[i][j]); 

            else
                printf(" %d", ans[i][j]); 

            if (j == ans[i].size() - 1)
                printf("\n"); 
        }
    }

    return 0; 
}

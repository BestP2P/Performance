#ifndef __DS_PTESTER_H__
#define __DS_PTESTER_H__

#include <iostream>
#include <string>
#include <vector>

namespace DS {

namespace Performance {

typedef std::function<void(const int i)> DSFunc;

struct DSTimeReslut {
    std::string label;
    long wallClock;     // 实际运行时间 ms
    long runTime;       // cpu运行时间 ms
};

struct DSPList {
    std::string label;
    DSFunc F;
};

// 运行单项测试并计时
DSTimeReslut PerformanceTimer(const std::string & label, DSFunc F, int N);
// 运行计时器(并发测试时使用)
DSTimeReslut ParallelsTimer(const std::string & label, DSFunc F, int N);
// 运行测试
void PTesterRun(int N, std::vector<DSPList> & lists);
// 对函数执行n次循环
void ItertorFor(DSFunc F, int N);
// 生成随机数
int GengerRand(int min, int max);
// 获取当前系统时间, 毫秒
long GetMillisecondsTime();

}

}

#endif /* __DS_PTESTER_H__ */

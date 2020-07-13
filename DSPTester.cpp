#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <random>

#include "DSPTester.h"

namespace DS {

namespace Performance {

// 获取进程时间
// 返回wallclock, 即执行时间
// 入参runtime, cpu 总执行时间
clock_t Statistics(clock_t & runtime) {
    struct tms timems;
    clock_t wallclock = times (&timems);
    runtime = timems.tms_utime + timems.tms_stime + timems.tms_cutime + timems.tms_cstime;
    return wallclock;
}

// 取当前时间戳，单位:毫秒
long GetMillisecondsTime() {
    long milliseconds;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return milliseconds;
}

// 运行单项测试并计时
DSTimeReslut PerformanceTimer(const std::string & label, DSFunc F, int N) {
    long tick = sysconf(_SC_CLK_TCK);
    DSTimeReslut ret;
    clock_t runTimeStart, runTimeEnd;
    clock_t usStart, usEnd;
    runTimeStart = Statistics(usStart);
    ItertorFor(F, N);
    runTimeEnd = Statistics(usEnd);
    double sec = (runTimeEnd - runTimeStart) / (double)tick; // 秒数
    double secCpu = (usEnd - usStart) / (double)tick; // 秒数
    long time1 = sec * 1000;
    long time2 = secCpu * 1000;
    double u1 = time1 * 1000 / (double)N;        // 平均每次
    double u2 = time2 * 1000 / (double)N;
    printf("%s [total: %ld(%ld)ms avg: %.3f(%.3f)us]\n", label.c_str(), time2, time1, u2, u1);
    ret.label = label;
    ret.wallClock = time1;
    ret.runTime = time2;
    return ret;
}

// 运行计时器(并发测试时使用)
DSTimeReslut ParallelsTimer(const std::string & label, DSFunc F, int N) {
    DSTimeReslut ret;
    long wallClockStart, wallClockEnd;
    wallClockStart = GetMillisecondsTime();
    ItertorFor(F, N);
    wallClockEnd = GetMillisecondsTime();
    long time1 = wallClockEnd - wallClockStart;
    double u1 = time1 * 1000 / (double)N;        // 平均每次
    printf("%s [total: %ldms avg: %.3fus]\n", label.c_str(), time1, u1);
    ret.label = label;
    ret.wallClock = time1;
    ret.runTime = time1;
    return ret;
}

void ComparePerformance(std::vector<DSTimeReslut> & resultVec, DSTimeReslut base) {
    for (auto item : resultVec) {
        printf("%20s = %9.2fms [%8.2f%%] %9.2fms [%8.2f%%]\n",
               item.label.c_str(), item.runTime + 0.0, item.runTime / (base.runTime + 0.00000001) * 100,
               item.wallClock + 0.0, item.wallClock / (base.wallClock + 0.00000001) * 100);
    }
}

void PTesterRun(int N, std::vector<DSPList> & lists) {
    if (lists.size() == 0) {
        return;
    }
    std::vector<DSTimeReslut> resultVec;
    for (auto item : lists) {
        DSTimeReslut ret = PerformanceTimer(item.label, item.F, N);
        resultVec.push_back(ret);
    }
    printf("========================================================================\n");
    printf("%20s = %9.2fms [%8.2f%%] %9.2fms [%8.2f%%]\n",
           resultVec[0].label.c_str(), (float)resultVec[0].runTime, 100.0, (float)resultVec[0].wallClock, 100.0);
    if (resultVec.size() > 1) {
        DSTimeReslut base = resultVec[0];
        resultVec.erase(resultVec.begin());
        ComparePerformance(resultVec, base);
    }
    printf("========================================================================\n");
}

void ItertorFor(DSFunc F, int N) {
    for (int i = 0; i < N; i++) {
        F(i);
    }
}

int GengerRand(int min, int max) {
    static std::default_random_engine e((unsigned int)time(0));
    int m = min - 1;
    return e() % (max - m) + m;
}

}

}

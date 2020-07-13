/*
* Copyright (c) 2020, zero <2354558781@qq.com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of DSEngine nor the names of its contributors may be used
*     to endorse or promote products derived from this software without
*     specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

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

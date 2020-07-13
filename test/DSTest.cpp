#include "DSPTester.h"

int main(int argc, char * argv[]) {
    auto F1 = [](const int i){ (void)(rand() % 1000000);};
    std::vector<DS::Performance::DSPList> List;
    List = {{"test1", F1}, {"test2", F1}};
    DS::Performance::PTesterRun(1000000, List);
    return 0;
}

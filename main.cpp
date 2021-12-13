#include <fstream>
#include "workflow.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        throw ArgumentException("wrong input parameters count\n");
    }
    Workflow workflow(argv[1]);
    workflow.work();
    return 0;
}

#include "workflow.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        throw ArgumentException("wrong input parameters count\n");
    }
    Workflow workflow;
    workflow.execute(argv[1]);
    return 0;
}

#include "qtest.hpp"

#include "nernode.hpp"
#include "nersyn.hpp"
#include "nerlayer.hpp"

SCENARIO_START
#include "src/nernode.test.cpp"
#include "src/nersyn.test.cpp"
#include "src/nerlayer.test.cpp"
SCENARIO_END

int main(){ return 0; }

#include "scenes.h"
#include "benchmark.h"

// Flip to true (then recompile) to benchmark instead of writing a PPM image.
constexpr bool RUN_BENCHMARK = true;
constexpr int  BENCHMARK_TRIALS = 3;

int main(){
    scene s = make_book1_final(1200, 200);

    if constexpr (RUN_BENCHMARK) {
        run_benchmark(s, BENCHMARK_TRIALS);
    } else {
        s.cam.render(s.world);
    }

    return 0;
}
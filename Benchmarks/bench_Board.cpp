/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Benchmark of the Board class
 */

#include <benchmark/benchmark.h>

#include <MLBoard/Board.hpp>

using namespace ML;

static void BoardCreationDestruction(benchmark::State &state)
{
    for (auto _ : state) {
        Board instance;
        benchmark::DoNotOptimize(instance);
    }
}

BENCHMARK(BoardCreationDestruction);
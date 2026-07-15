#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>

#include "scene.h"

// Renders `s` `num_trials` times in benchmark mode, timing each render and
// appending one CSV row per trial to `csv_path` (the header is written only
// if the file does not already exist). A short summary is printed to stderr.
//
// Recorded per trial: timestamp, git commit, scene name, image width/height,
// samples per pixel, trial number, render time (s), total rays, rays/second.
void run_benchmark(scene& s, int num_trials, const std::string& csv_path = "benchmarks.csv");

#endif

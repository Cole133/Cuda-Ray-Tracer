#ifndef STATS_H
#define STATS_H

#include <atomic>
#include <cstdint>

// Global performance counters for the renderer.

inline std::atomic<uint64_t> g_ray_object_tests{0};

#endif

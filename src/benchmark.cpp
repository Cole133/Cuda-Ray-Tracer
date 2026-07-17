#include "benchmark.h"

#include <chrono>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace {

// Returns time as "YYYY-MM-DD HH:MM:SS"
std::string timestamp() {
    std::time_t t = std::time(nullptr);
    std::tm tm_buf{};
#ifdef _WIN32
    localtime_s(&tm_buf, &t);
#else
    localtime_r(&t, &tm_buf);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_buf);
    return buf;
}

// Returns the current git commit
std::string git_commit() {
#ifdef _WIN32
    FILE* pipe = _popen("git rev-parse --short HEAD 2>NUL", "r");
#else
    FILE* pipe = popen("git rev-parse --short HEAD 2>/dev/null", "r");
#endif
    if (!pipe) return "unknown";

    std::string out;
    char buf[128];
    while (std::fgets(buf, sizeof(buf), pipe)) out += buf;

#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    while (!out.empty() && (out.back() == '\n' || out.back() == '\r' || out.back() == ' '))
        out.pop_back();

    return out.empty() ? "unknown" : out;
}

bool file_exists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

} 

void run_benchmark(scene& s, int num_trials, const std::string& csv_path) {
    // Suppress the PPM image + progress output so only times raytracing work
    s.cam.benchmark_mode = true;

    const std::string ts = timestamp();
    const std::string commit = git_commit();

    const bool needs_header = !file_exists(csv_path);
    std::ofstream csv(csv_path, std::ios::app);
    if (needs_header) {
        csv << "timestamp,git_commit,scene_name,image_width,image_height,"
               "samples_per_pixel,trial_number,render_time_seconds,total_rays,rays_per_second\n";
    }

    std::clog << "Benchmarking scene '" << s.name << "' - "
              << num_trials << " trial(s)\n";

    for (int trial = 1; trial <= num_trials; trial++) {
        const auto start = std::chrono::steady_clock::now();
        s.cam.render(s.world);
        const auto end = std::chrono::steady_clock::now();

        const double seconds = std::chrono::duration<double>(end - start).count();
        const long long total_rays = s.cam.ray_count();
        const double rays_per_sec = seconds > 0.0 ? total_rays / seconds : 0.0;

        const int width = s.cam.image_width;
        const int height = s.cam.image_height_value();
        const int spp = s.cam.samples_per_pixel;

        csv << ts << ',' << commit << ',' << s.name << ','
            << width << ',' << height << ',' << spp << ',' << trial << ','
            << std::fixed << std::setprecision(6) << seconds << ','
            << total_rays << ','
            << std::setprecision(2) << rays_per_sec << '\n';

        std::clog << "  trial " << trial << '/' << num_trials << ": "
                  << std::fixed << std::setprecision(3) << seconds << " s, "
                  << total_rays << " rays, "
                  << std::setprecision(0) << rays_per_sec << " rays/s\n";
    }

    std::clog << "Wrote results to " << csv_path << "\n";
}

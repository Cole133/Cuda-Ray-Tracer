A path tracer in C++ with CUDA acceleration, following Peter Shirley's Ray Tracing in One Weekend series.

Quick recap of the workflow from here on:

  cd "/home/colegardiner/AntiGravity/Cuda Ray Tracing"
  cmake --build build
  ./build/CudaRayTracing > output/render.ppm
  xdg-open output/render.ppm
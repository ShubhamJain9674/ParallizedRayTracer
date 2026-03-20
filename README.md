# Ray Tracing

This project is based on the book *"Ray Tracing in One Weekend"* and focuses on **parallelizing the renderer using OpenMP and CUDA **.

The goal is to speed up image generation by utilizing multi-core CPUs.

---

## Requirements

* C++20 compatible compiler:

  * `g++` (GCC)
  * or Intel (`icpx`)
* CMake (>= 3.16)
* OpenMP support

---

## Setup & Build

### 1. Clone the repository

```bash
git clone <your-repo-url>
cd <repo-name>
```

### 2. Configure the project

Using GCC:

```bash
cmake -B build -S . -DCMAKE_CXX_COMPILER=g++
```

Using Intel compiler:

```bash
cmake -B build -S . -DCMAKE_CXX_COMPILER=icpx
```

### 3. Build

```bash
cmake --build build
```

---

## Run

```bash
./build/RayTracer
```

---

## Notes

* OpenMP is enabled via CMake (`find_package(OpenMP)`).
* Optimization flags can be toggled in `CMakeLists.txt`.
* The renderer outputs an image (e.g., `.ppm`) to stdout or file depending on implementation.

---

## Goal

Parallelize the ray tracing loop (per-pixel or per-scanline) using OpenMP to achieve significant performance improvements over the single-threaded version.

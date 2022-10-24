# No mercy here, use optimization and strip it
nvcc --m64 --std=c++17 -O3 ./baby_nvidia.cu -o ./baby_nvidia
strip ./baby_nvidia

# Show some mercy here, no optimization
# nvcc --m64 --std=c++17 ./baby_nvidia.cu -o ./baby_nvidia

# Genrate ptx file or further usage
nvcc --m64 -ptx --std=c++17 ./baby_nvidia.cu -o ./baby_nvidia.ptx

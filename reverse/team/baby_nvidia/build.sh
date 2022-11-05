# No mercy here, use optimization and strip it
# Genrate ptx file or further usage
nvcc --m64 --std=c++17 -O3 ./baby_nvidia.cu -o ./baby_nvidia
nvcc --m64 -ptx --std=c++17 -O3 ./baby_nvidia.cu -o ./baby_nvidia.ptx
strip ./baby_nvidia

# nvcc --m64 --std=c++17 -O3 ./special_challenge.cu -o ./special_challenge
# strip ./special_challenge

# Show some mercy here, no optimization
nvcc --m64 --std=c++17 ./special_challenge.cu -o ./special_challenge

# Genrate ptx file or further usage
nvcc --m64 -ptx --std=c++17 ./special_challenge.cu -o ./special_challenge.ptx

g++ -static -m32 -mavx2 -Wno-unused-result -O3 -s -std=c++20 ./vm.cpp ./baby_vm.cpp -o ./baby_vm
strip ./baby_vm 
upx --best ./baby_vm

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <cstdio>
#include <cstdlib>  // exit
#include <cstring>  // memcmp
#include <cstdint>  // uint32_t
#include <string>   // std::string
#include <iostream> // std::cout

#define NV_FAILED(status) (status != cudaSuccess)
#define NV_SHOWERR(status) std::cout << "Possible reason: " << cudaGetErrorString(status) << std::endl

#ifdef _MSC_VER
#define NV_INLINE __forceinline
#else
#define NV_INLINE inline
#endif

__global__ void encrypt(uint32_t* v, uint32_t* k) 
{
    v += threadIdx.x * 2;
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i;
    uint32_t delta = 0x9e3779b9;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 18; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    v[0] = v0; v[1] = v1;
}

uint32_t* g_v = nullptr;
uint32_t* g_k = nullptr;

NV_INLINE void deallocMemory()
{
    if (g_k)
        cudaFree(g_k);
    if (g_v)
        cudaFree(g_v);
}
NV_INLINE void myExit(int exitCode)
{
    deallocMemory();
    exit(exitCode);
}
NV_INLINE void initDevice()
{
    cudaError_t status;
    
    int cudaDeviceCount;
    status = cudaGetDeviceCount(&cudaDeviceCount);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to get GPU count!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }

    if (cudaDeviceCount < 1)
    {
        std::cout << "Failed to find an available GPU! This program requires at least one GPU support CUDA!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }

    const int deviceId = cudaDeviceCount - 1;

    status = cudaSetDevice(deviceId);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to select a GPU!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }

    cudaDeviceProp prop;
    status = cudaGetDeviceProperties(&prop, deviceId);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to get GPU property!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }
    std::cout << "Successfully select GPU: " << prop.name << std::endl;
}
NV_INLINE bool checkFormat(std::string& s)
{
    if (s.length() != 32)
        return false;

    if (0 != memcmp("MAYCTF{", s.c_str(), 7))
        return false;

    if (s.back() != '}')
        return false;

    return true;
}
NV_INLINE void initMemory(const char* flag)
{
    cudaError_t status;

    status = cudaMalloc(&g_v, 32);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to malloc memory for g_v!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }
    
    status = cudaMalloc(&g_k, 16);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to malloc memory for g_k!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }

    status = cudaMemcpy(g_v, flag, 32, cudaMemcpyHostToDevice);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to copy data to g_v!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }

    constexpr char key[] = "MAYCTF_REV_CUDA!";
    status = cudaMemcpy(g_k, key, 16, cudaMemcpyHostToDevice);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to copy data to g_k!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }
}
NV_INLINE void executeEncrypt(unsigned char sn[])
{
    cudaError_t status;

    encrypt<<<1, 4>>>(g_v, g_k);
    status = cudaGetLastError();
    if (NV_FAILED(status))
    {
        std::cout << "Failed to verify data!" << std::endl;
        NV_SHOWERR(status);
        myExit(3);
    }

    status = cudaDeviceSynchronize();
    if (NV_FAILED(status))
    {
        std::cout << "Failed to call cudaDeviceSynchronize!" << std::endl;
        NV_SHOWERR(status);
        myExit(3);
    }
    
    status = cudaMemcpy(sn, g_v, 32, cudaMemcpyDeviceToHost);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to copy data back to host!" << std::endl;
        NV_SHOWERR(status);
        myExit(3);
    }
}
NV_INLINE bool checkAnswer(unsigned char sn[])
{
    unsigned char ans[32] =
    {
        0xef, 0x6e, 0xec, 0x60, 0xeb, 0x84, 0x92, 0x00,
        0x42, 0x2f, 0x1a, 0x22, 0x20, 0xb2, 0xb4, 0x83,
        0xa1, 0xe8, 0x61, 0x06, 0xb3, 0x76, 0xaf, 0x8d,
        0xc4, 0x8f, 0x55, 0x8c, 0xc8, 0x71, 0x9b, 0x86,
    };

    return 0 == memcmp(sn, ans, 32);
}

// modified TEA-Encrypt which only has 18 rounds
// key = MAYCTF_REV_CUDA!
// flag = MAYCTF{NviDiA_CuDA_GPU_ProGrAm!}
int main()
{
    std::cout << "Initializing device..." << std::endl;
    initDevice();
    
    std::cout << "Please input your flag:" << std::endl;
    std::string flag;
    std::cin >> flag;
    if (!checkFormat(flag))
    {
        std::cout << "You don't understand Reverse of course!" << std::endl;
        myExit(114514);
    }

    std::cout << "Hold on! I'm verifying your flag...";
    initMemory(flag.c_str());

    unsigned char sn[32] = { 0 };
    executeEncrypt(sn);
    std::cout << " Done.\n" << std::endl;

    if (checkAnswer(sn))
        std::cout << "You are really good at cuda reverse!" << std::endl;
    else
        std::cout << "Seems you cannot fully understand what cuda had done!" << std::endl;

#ifdef _MSC_VER
    system("pause");
#endif

    myExit(0);
}
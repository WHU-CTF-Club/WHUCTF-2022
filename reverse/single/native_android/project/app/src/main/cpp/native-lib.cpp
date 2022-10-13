#include <jni.h>
#include <cstring>

void encrypt(void* V, const void* K)
{
    auto v = reinterpret_cast<unsigned int*>(V);
    auto k = reinterpret_cast<const unsigned int*>(K);
    unsigned int v0 = v[0], v1 = v[1], sum = 0, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++)
    {
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    v[0] = v0; v[1] = v1;
}

// mayctf{S0_This_1S_A_Android_Native_Cpp!}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_native_1android_MainActivity_checkFlagNative(JNIEnv *env, jobject thiz,
                                                              jstring str) {
    const char* ret = "Oops, you need a valid input!";

    if (str) {
        const char* cstr = env->GetStringUTFChars(str, nullptr);
        size_t len = strlen(cstr);
        ret = "Your length is not quite correct!";

        // mayctf{S0_This_1S_A_Android_Native_Cpp!}
        // @Android_Nat1ve!
        if (len == 40) {
            char value[40];
            memcpy(value, cstr, 40);

            unsigned char key[] = {
                    0x40, 0x40, 0x6C, 0x67, 0x76, 0x6A, 0x6F, 0x63,
                    0x57, 0x47, 0x6B, 0x7F, 0x3D, 0x7B, 0x6B, 0x2E
            };
            for (int i = 0; i < 16; ++i)
                key[i] ^= i;

            for (int i = 0; i < 40; i += 8)
                encrypt(value + i, key);

            unsigned char sn[] = {
                    0xf0, 0x2e, 0xd2, 0x73, 0x04, 0xb6, 0x1a, 0xd3,
                    0x59, 0xb2, 0xe3, 0x27, 0xa0, 0xda, 0x90, 0xd6,
                    0xd2, 0x8c, 0x1c, 0x24, 0x00, 0xcb, 0x7e, 0x80,
                    0x70, 0xf7, 0x35, 0xc2, 0x9d, 0x30, 0x3a, 0x3f,
                    0x53, 0xb6, 0xf7, 0xbc, 0x29, 0x53, 0x5d, 0xec,
            };

            if (!memcmp(sn, value, 40))
                ret = "Congratulations!";
            else
                ret = "Wrong flag!";
        }

        env->ReleaseStringUTFChars(str, cstr);
    }

    return env->NewStringUTF(ret);
}
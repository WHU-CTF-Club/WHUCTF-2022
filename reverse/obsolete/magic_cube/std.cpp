int main()
{
    void solve();

    solve();
    return 0;
}

void CopyTmpCubicRowAt(int facing, int row);
void CopyTmpCubicColAt(int facing, int column);
void CopyToCurrentCubicRowAt(int facing, int row);
void CopyToCurrentCubicColAt(int facing, int col);
void SwapColRowTmpBuf();
void Rotate_90Degrees(int facing);
void Rotate_270Degrees(unsigned int facing);
void sub_4014B7();
void sub_4016D2();
void sub_4018ED();
void sub_40190C();
void sub_40192B();
void sub_401B46();
void sub_401D61();
void sub_401D80();
void sub_401D9F();
void sub_401FBA();
void sub_4021D5();
void sub_4021F4();
void sub_402213();
void sub_40242E();
void sub_402649();
void sub_402668();
void sub_402687();
void sub_4028A2();
void sub_402ABD();
void sub_402ADC();
void sub_402AFB();
void sub_402D16();
void sub_402F31();
void sub_402F50();
void sub_402F6F();
void sub_403180();
void sub_403391();
void sub_4033B0();
void sub_4035C1();
void sub_4037D2();
void sub_4037F1();
void sub_403A02();
void sub_403C13();
void sub_403C32();
void sub_403C51();
void sub_403C70();
void sub_403C8F();
void sub_403CAE();
void sub_403CCD();
void sub_403CEC();
void sub_403D0B();
void sub_403D2A();
void sub_403D49();
void sub_403D68();
void sub_403D87();
void sub_403DB0();
void sub_403DD9();
void sub_403E02();
void sub_403E2B();
void sub_403E54();
void Store_CurrentWorkingCubic();
int Check_Color_1();
bool Old_Color1_LessThan_New_Color1();
bool Is_Face_0_Done();
bool Check_Cubic_Face_Side_Line(int face);
bool Is_Base_Done();
void INIT_CUBIC_DATAS();
bool Is_Perfect_Cubic(int x);
void HackCheck(int x);

struct Cubic
{
    int Data[6][3][3];
};

int ColRowTmpBuf[3];
Cubic TmpCubic;
Cubic WorkingCubicInstance;
Cubic CubeOriginals[4];
Cubic WorkingCubicInstance_Store;

#include <iostream>
#include <cstring>

//----- (0000000000401216) ----------------------------------------------------
void CopyTmpCubicRowAt(int facing, int row)
{
    int i; // [rsp+14h] [rbp-4h]

    for (i = 0; i <= 2; ++i)
        ColRowTmpBuf[i] = TmpCubic.Data[facing][row][i];
}

//----- (000000000040128F) ----------------------------------------------------
void CopyTmpCubicColAt(int facing, int column)
{
    int i; // [rsp+14h] [rbp-4h]

    for (i = 0; i <= 2; ++i)
        ColRowTmpBuf[i] = TmpCubic.Data[facing][i][column];
}

//----- (0000000000401308) ----------------------------------------------------
void CopyToCurrentCubicRowAt(int facing, int row)
{
    int i; // [rsp+14h] [rbp-4h]

    for (i = 0; i <= 2; ++i)
        WorkingCubicInstance.Data[facing][row][i] = ColRowTmpBuf[i];
}

//----- (0000000000401380) ----------------------------------------------------
void CopyToCurrentCubicColAt(int facing, int col)
{
    int i; // [rsp+14h] [rbp-4h]

    for (i = 0; i <= 2; ++i)
        WorkingCubicInstance.Data[facing][i][col] = ColRowTmpBuf[i];
}

//----- (00000000004013F8) ----------------------------------------------------
void SwapColRowTmpBuf()
{
    int tmp; // [rsp+0h] [rbp-4h]

    tmp = ColRowTmpBuf[0];
    ColRowTmpBuf[0] = ColRowTmpBuf[2];
    ColRowTmpBuf[2] = tmp;
}
// 40B090: using guessed type int ColRowBufBuffer;

//----- (0000000000401421) ----------------------------------------------------
void Rotate_90Degrees(int facing)
{
    int row; // [rsp+14h] [rbp-4h]

    for (row = 0; row <= 2; ++row)
    {
        CopyTmpCubicRowAt(facing, row);
        CopyToCurrentCubicColAt(facing, 2 - row);
    }
}

//----- (000000000040146C) ----------------------------------------------------
void Rotate_270Degrees(unsigned int facing)
{
    int i; // [rsp+14h] [rbp-4h]

    for (i = 0; i <= 2; ++i)
    {
        CopyTmpCubicColAt(facing, 2 - i);           // 第2-i列放到第i行
        CopyToCurrentCubicRowAt(facing, i);
    }
}

//----- (00000000004014B7) ----------------------------------------------------
void sub_4014B7()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_90Degrees(0);

    // Rotate Bottom 180 degree
    CopyTmpCubicRowAt(3, 2);
    CopyToCurrentCubicRowAt(5, 2);
    CopyTmpCubicRowAt(5, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(2, 2);
    CopyTmpCubicColAt(2, 2);
    CopyToCurrentCubicColAt(4, 2);
    CopyTmpCubicColAt(4, 2);
    SwapColRowTmpBuf();

    CopyToCurrentCubicRowAt(3, 2);
}

//----- (00000000004016D2) ----------------------------------------------------
void sub_4016D2()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_270Degrees(0);
    CopyTmpCubicRowAt(5, 2);
    CopyToCurrentCubicRowAt(3, 2);
    CopyTmpCubicColAt(2, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(5, 2);
    CopyTmpCubicColAt(4, 2);
    CopyToCurrentCubicColAt(2, 2);
    CopyTmpCubicRowAt(3, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(4, 2);
}

//----- (00000000004018ED) ----------------------------------------------------
void sub_4018ED()
{
    sub_4014B7();
    sub_4014B7();
}

//----- (000000000040190C) ----------------------------------------------------
void sub_40190C()
{
    sub_4016D2();
    sub_4016D2();
}

//----- (000000000040192B) ----------------------------------------------------
void sub_40192B()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_90Degrees(1);
    CopyTmpCubicRowAt(3, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(4, 0);
    CopyTmpCubicColAt(4, 0);
    CopyToCurrentCubicColAt(2, 0);
    CopyTmpCubicColAt(2, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(5, 0);
    CopyTmpCubicRowAt(5, 0);
    CopyToCurrentCubicRowAt(3, 0);
}

//----- (0000000000401B46) ----------------------------------------------------
void sub_401B46()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_270Degrees(1u);
    CopyTmpCubicColAt(4, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(3, 0);
    CopyTmpCubicColAt(2, 0);
    CopyToCurrentCubicColAt(4, 0);
    CopyTmpCubicRowAt(5, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(2, 0);
    CopyTmpCubicRowAt(3, 0);
    CopyToCurrentCubicRowAt(5, 0);
}

//----- (0000000000401D61) ----------------------------------------------------
void sub_401D61()
{
    sub_40192B();
    sub_40192B();
}

//----- (0000000000401D80) ----------------------------------------------------
void sub_401D80()
{
    sub_401B46();
    sub_401B46();
}

//----- (0000000000401D9F) ----------------------------------------------------
void sub_401D9F()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_90Degrees(2);
    CopyTmpCubicRowAt(0, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(5, 2);
    CopyTmpCubicColAt(5, 2);
    CopyToCurrentCubicColAt(1, 2);
    CopyTmpCubicColAt(1, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(4, 2);
    CopyTmpCubicRowAt(4, 2);
    CopyToCurrentCubicRowAt(0, 2);
}

//----- (0000000000401FBA) ----------------------------------------------------
void sub_401FBA()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_270Degrees(2u);
    CopyTmpCubicColAt(5, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(0, 2);
    CopyTmpCubicColAt(1, 2);
    CopyToCurrentCubicColAt(5, 2);
    CopyTmpCubicRowAt(4, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(1, 2);
    CopyTmpCubicRowAt(0, 2);
    CopyToCurrentCubicRowAt(4, 2);
}

//----- (00000000004021D5) ----------------------------------------------------
void sub_4021D5()
{
    sub_401D9F();
    sub_401D9F();
}

//----- (00000000004021F4) ----------------------------------------------------
void sub_4021F4()
{
    sub_401FBA();
    sub_401FBA();
}

//----- (0000000000402213) ----------------------------------------------------
void sub_402213()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_90Degrees(3);
    CopyTmpCubicRowAt(0, 0);
    CopyToCurrentCubicRowAt(4, 0);
    CopyTmpCubicRowAt(4, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(1, 0);
    CopyTmpCubicColAt(1, 0);
    CopyToCurrentCubicColAt(5, 0);
    CopyTmpCubicColAt(5, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(0, 0);
}

//----- (000000000040242E) ----------------------------------------------------
void sub_40242E()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_270Degrees(3u);
    CopyTmpCubicRowAt(4, 0);
    CopyToCurrentCubicRowAt(0, 0);
    CopyTmpCubicColAt(1, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(4, 0);
    CopyTmpCubicColAt(5, 0);
    CopyToCurrentCubicColAt(1, 0);
    CopyTmpCubicRowAt(0, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(5, 0);
}

//----- (0000000000402649) ----------------------------------------------------
void sub_402649()
{
    sub_402213();
    sub_402213();
}

//----- (0000000000402668) ----------------------------------------------------
void sub_402668()
{
    sub_40242E();
    sub_40242E();
}

//----- (0000000000402687) ----------------------------------------------------
void sub_402687()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_90Degrees(4);
    CopyTmpCubicColAt(0, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(2, 0);
    CopyTmpCubicRowAt(2, 0);
    CopyToCurrentCubicRowAt(1, 0);
    CopyTmpCubicRowAt(1, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(3, 0);
    CopyTmpCubicColAt(3, 0);
    CopyToCurrentCubicColAt(0, 0);
}

//----- (00000000004028A2) ----------------------------------------------------
void sub_4028A2()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_270Degrees(4u);
    CopyTmpCubicRowAt(2, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(0, 0);
    CopyTmpCubicRowAt(1, 0);
    CopyToCurrentCubicRowAt(2, 0);
    CopyTmpCubicColAt(3, 0);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(1, 0);
    CopyTmpCubicColAt(0, 0);
    CopyToCurrentCubicColAt(3, 0);
}

//----- (0000000000402ABD) ----------------------------------------------------
void sub_402ABD()
{
    sub_402687();
    sub_402687();
}

//----- (0000000000402ADC) ----------------------------------------------------
void sub_402ADC()
{
    sub_4028A2();
    sub_4028A2();
}

//----- (0000000000402AFB) ----------------------------------------------------
void sub_402AFB()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_90Degrees(5);
    CopyTmpCubicColAt(0, 2);
    CopyToCurrentCubicColAt(3, 2);
    CopyTmpCubicColAt(3, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(1, 2);
    CopyTmpCubicRowAt(1, 2);
    CopyToCurrentCubicRowAt(2, 2);
    CopyTmpCubicRowAt(2, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(0, 2);
}

//----- (0000000000402D16) ----------------------------------------------------
void sub_402D16()
{
    TmpCubic = WorkingCubicInstance;
    Rotate_270Degrees(5u);
    CopyTmpCubicColAt(3, 2);
    CopyToCurrentCubicColAt(0, 2);
    CopyTmpCubicRowAt(1, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(3, 2);
    CopyTmpCubicRowAt(2, 2);
    CopyToCurrentCubicRowAt(1, 2);
    CopyTmpCubicColAt(0, 2);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(2, 2);
}

//----- (0000000000402F31) ----------------------------------------------------
void sub_402F31()
{
    sub_402AFB();
    sub_402AFB();
}

//----- (0000000000402F50) ----------------------------------------------------
void sub_402F50()
{
    sub_402D16();
    sub_402D16();
}

//----- (0000000000402F6F) ----------------------------------------------------
void sub_402F6F()
{
    TmpCubic = WorkingCubicInstance;
    CopyTmpCubicColAt(0, 1);
    CopyToCurrentCubicColAt(3, 1);
    CopyTmpCubicColAt(3, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(1, 1);
    CopyTmpCubicRowAt(1, 1);
    CopyToCurrentCubicRowAt(2, 1);
    CopyTmpCubicRowAt(2, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(0, 1);
}

//----- (0000000000403180) ----------------------------------------------------
void sub_403180()
{
    TmpCubic = WorkingCubicInstance;
    CopyTmpCubicColAt(3, 1);
    CopyToCurrentCubicColAt(0, 1);
    CopyTmpCubicRowAt(1, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(3, 1);
    CopyTmpCubicRowAt(2, 1);
    CopyToCurrentCubicRowAt(1, 1);
    CopyTmpCubicColAt(0, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(2, 1);
}

//----- (0000000000403391) ----------------------------------------------------
void sub_403391()
{
    sub_402F6F();
    sub_402F6F();
}

//----- (00000000004033B0) ----------------------------------------------------
void sub_4033B0()
{
    TmpCubic = WorkingCubicInstance;
    CopyTmpCubicRowAt(3, 1);
    CopyToCurrentCubicRowAt(5, 1);
    CopyTmpCubicRowAt(5, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(2, 1);
    CopyTmpCubicColAt(2, 1);
    CopyToCurrentCubicColAt(4, 1);
    CopyTmpCubicColAt(4, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(3, 1);
}

//----- (00000000004035C1) ----------------------------------------------------
void sub_4035C1()
{
    TmpCubic = WorkingCubicInstance;
    CopyTmpCubicRowAt(5, 1);
    CopyToCurrentCubicRowAt(3, 1);
    CopyTmpCubicColAt(2, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(5, 1);
    CopyTmpCubicColAt(4, 1);
    CopyToCurrentCubicColAt(2, 1);
    CopyTmpCubicRowAt(3, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(4, 1);
}

//----- (00000000004037D2) ----------------------------------------------------
void sub_4037D2()
{
    sub_4033B0();
    sub_4033B0();
}

//----- (00000000004037F1) ----------------------------------------------------
void sub_4037F1()
{
    TmpCubic = WorkingCubicInstance;
    CopyTmpCubicRowAt(0, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(5, 1);
    CopyTmpCubicColAt(5, 1);
    CopyToCurrentCubicColAt(1, 1);
    CopyTmpCubicColAt(1, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(4, 1);
    CopyTmpCubicRowAt(4, 1);
    CopyToCurrentCubicRowAt(0, 1);
}

//----- (0000000000403A02) ----------------------------------------------------
void sub_403A02()
{
    TmpCubic = WorkingCubicInstance;
    CopyTmpCubicColAt(5, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicRowAt(0, 1);
    CopyTmpCubicColAt(1, 1);
    CopyToCurrentCubicColAt(5, 1);
    CopyTmpCubicRowAt(4, 1);
    SwapColRowTmpBuf();
    CopyToCurrentCubicColAt(1, 1);
    CopyTmpCubicRowAt(0, 1);
    CopyToCurrentCubicRowAt(4, 1);
}

//----- (0000000000403C13) ----------------------------------------------------
void sub_403C13()
{
    sub_4014B7();
    sub_4033B0();
}

//----- (0000000000403C32) ----------------------------------------------------
void sub_403C32()
{
    sub_4016D2();
    sub_4035C1();
}

//----- (0000000000403C51) ----------------------------------------------------
void sub_403C51()
{
    sub_40192B();
    sub_4035C1();
}

//----- (0000000000403C70) ----------------------------------------------------
void sub_403C70()
{
    sub_401B46();
    sub_4033B0();
}

//----- (0000000000403C8F) ----------------------------------------------------
void sub_403C8F()
{
    sub_401D9F();
    sub_4037F1();
}

//----- (0000000000403CAE) ----------------------------------------------------
void sub_403CAE()
{
    sub_401FBA();
    sub_403A02();
}

//----- (0000000000403CCD) ----------------------------------------------------
void sub_403CCD()
{
    sub_402213();
    sub_403A02();
}

//----- (0000000000403CEC) ----------------------------------------------------
void sub_403CEC()
{
    sub_40242E();
    sub_4037F1();
}

//----- (0000000000403D0B) ----------------------------------------------------
void sub_403D0B()
{
    sub_402687();
    sub_403180();
}

//----- (0000000000403D2A) ----------------------------------------------------
void sub_403D2A()
{
    sub_4028A2();
    sub_402F6F();
}

//----- (0000000000403D49) ----------------------------------------------------
void sub_403D49()
{
    sub_402AFB();
    sub_402F6F();
}

//----- (0000000000403D68) ----------------------------------------------------
void sub_403D68()
{
    sub_402D16();
    sub_403180();
}

//----- (0000000000403D87) ----------------------------------------------------
void sub_403D87()
{
    sub_402AFB();
    sub_4028A2();
    sub_402F6F();
}

//----- (0000000000403DB0) ----------------------------------------------------
void sub_403DB0()
{
    sub_402D16();
    sub_402687();
    sub_403180();
}

//----- (0000000000403DD9) ----------------------------------------------------
void sub_403DD9()
{
    sub_4014B7();
    sub_401B46();
    sub_4033B0();
}

//----- (0000000000403E02) ----------------------------------------------------
void sub_403E02()
{
    sub_4016D2();
    sub_40192B();
    sub_4035C1();
}

//----- (0000000000403E2B) ----------------------------------------------------
void sub_403E2B()
{
    sub_401D9F();
    sub_40242E();
    sub_4037F1();
}

//----- (0000000000403E54) ----------------------------------------------------
void sub_403E54()
{
    sub_401FBA();
    sub_402213();
    sub_403A02();
}

//----- (0000000000403E7D) ----------------------------------------------------
void Store_CurrentWorkingCubic()
{
    WorkingCubicInstance_Store = WorkingCubicInstance;
}

//----- (0000000000404002) ----------------------------------------------------
int Check_Color_1()
{
    int v1; // [rsp+0h] [rbp-4h]

    v1 = 0;
    if (WorkingCubicInstance.Data[2][0][0] == WorkingCubicInstance.Data[2][0][1]
        && WorkingCubicInstance.Data[4][2][0] == WorkingCubicInstance.Data[4][2][1]
        && WorkingCubicInstance.Data[1][0][2] == 1)
    {
        v1 = 1;
    }
    if (WorkingCubicInstance.Data[4][0][0] == WorkingCubicInstance.Data[4][0][1]
        && WorkingCubicInstance.Data[3][0][0] == WorkingCubicInstance.Data[3][1][0]
        && WorkingCubicInstance.Data[1][0][0] == 1)
    {
        ++v1;
    }
    if (WorkingCubicInstance.Data[3][0][2] == WorkingCubicInstance.Data[3][1][2]
        && WorkingCubicInstance.Data[5][0][0] == WorkingCubicInstance.Data[5][1][0]
        && WorkingCubicInstance.Data[1][2][0] == 1)
    {
        ++v1;
    }
    if (WorkingCubicInstance.Data[5][0][2] == WorkingCubicInstance.Data[5][1][2]
        && WorkingCubicInstance.Data[2][2][0] == WorkingCubicInstance.Data[2][2][1]
        && WorkingCubicInstance.Data[1][2][2] == 1)
    {
        ++v1;
    }
    return v1;
}

//----- (00000000004040D2) ----------------------------------------------------
bool Old_Color1_LessThan_New_Color1()
{
    int v1; // [rsp+8h] [rbp-8h]

    TmpCubic = WorkingCubicInstance;
    WorkingCubicInstance = WorkingCubicInstance_Store;
    v1 = Check_Color_1();
    WorkingCubicInstance = TmpCubic;
    return (int)Check_Color_1() > v1;
}

//----- (000000000040457C) ----------------------------------------------------
bool Is_Face_0_Done()
{
    // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (WorkingCubicInstance.Data[0][i][j])
                return 0;
        }
    }
    return 1;
}

//----- (00000000004045E6) ----------------------------------------------------
bool Check_Cubic_Face_Side_Line(int face)
{
    int i; // [rsp+Ch] [rbp-8h]
    int j; // [rsp+10h] [rbp-4h]

    if ((face & 1) != 0)
    {
        for (i = 0; i <= 2; ++i)
        {
            if (face != WorkingCubicInstance.Data[face][2][i])
                return 0;
        }
    }
    else
    {
        for (j = 0; j <= 2; ++j)
        {
            if (face != WorkingCubicInstance.Data[face][j][2])
                return 0;
        }
    }
    return 1;
}

//----- (00000000004046AD) ----------------------------------------------------
bool Is_Base_Done()
{
    int face; // [rsp+Ch] [rbp-4h]

    if (Is_Face_0_Done() != 1)
        return 0;
    for (face = 2; face <= 5; ++face)
    {
        if (Check_Cubic_Face_Side_Line(face) != 1)
            return 0;
    }
    return 1;
}

//----- (00000000004067C2) ----------------------------------------------------
void INIT_CUBIC_DATAS()
{
    int i; // [rsp+0h] [rbp-3A0h]
    int j; // [rsp+4h] [rbp-39Ch]
    int k; // [rsp+8h] [rbp-398h]
    int l; // [rsp+Ch] [rbp-394h]
    int v5[226]; // [rsp+10h] [rbp-390h] BYREF

    memset(v5, 0, sizeof(v5));
    v5[0] = 2;
    v5[3] = 3;
    v5[6] = 2;
    v5[7] = 5;
    v5[8] = 1;
    v5[9] = 1;
    v5[10] = 1;
    v5[11] = 5;
    v5[12] = 1;
    v5[13] = 1;
    v5[14] = 1;
    v5[15] = 1;
    v5[16] = 1;
    v5[17] = 3;
    v5[18] = 2;
    v5[19] = 5;
    v5[21] = 5;
    v5[22] = 5;
    v5[23] = 3;
    v5[24] = 5;
    v5[25] = 2;
    v5[26] = 3;
    v5[27] = 4;
    v5[28] = 4;
    v5[29] = 4;
    v5[30] = 4;
    v5[31] = 4;
    v5[32] = 4;
    v5[34] = 4;
    v5[35] = 4;
    v5[36] = 2;
    v5[37] = 2;
    v5[38] = 4;
    v5[39] = 2;
    v5[40] = 2;
    v5[42] = 1;
    v5[43] = 2;
    v5[44] = 5;
    v5[45] = 3;
    v5[46] = 3;
    v5[48] = 3;
    v5[49] = 3;
    v5[51] = 3;
    v5[52] = 5;
    v5[53] = 5;
    v5[55] = 3;
    v5[57] = 2;
    v5[59] = 4;
    v5[61] = 5;
    v5[63] = 1;
    v5[64] = 1;
    v5[65] = 1;
    v5[66] = 1;
    v5[67] = 1;
    v5[68] = 1;
    v5[69] = 1;
    v5[70] = 1;
    v5[71] = 1;
    v5[72] = 2;
    v5[73] = 2;
    v5[74] = 5;
    v5[75] = 2;
    v5[76] = 2;
    v5[78] = 2;
    v5[79] = 2;
    v5[80] = 4;
    v5[81] = 3;
    v5[82] = 3;
    v5[83] = 3;
    v5[84] = 3;
    v5[85] = 3;
    v5[86] = 3;
    v5[87] = 5;
    v5[89] = 4;
    v5[90] = 4;
    v5[91] = 4;
    v5[92] = 3;
    v5[93] = 4;
    v5[94] = 4;
    v5[96] = 4;
    v5[97] = 4;
    v5[98] = 2;
    v5[99] = 5;
    v5[100] = 5;
    v5[101] = 5;
    v5[102] = 5;
    v5[103] = 5;
    v5[104] = 5;
    v5[105] = 3;
    v5[107] = 2;
    v5[108] = 4;
    v5[110] = 3;
    v5[111] = 3;
    v5[113] = 2;
    v5[116] = 5;
    v5[117] = 1;
    v5[118] = 1;
    v5[119] = 1;
    v5[120] = 1;
    v5[121] = 1;
    v5[122] = 1;
    v5[123] = 1;
    v5[124] = 1;
    v5[126] = 5;
    v5[127] = 5;
    v5[128] = 2;
    v5[129] = 5;
    v5[130] = 5;
    v5[131] = 5;
    v5[132] = 5;
    v5[134] = 1;
    v5[135] = 4;
    v5[136] = 4;
    v5[137] = 4;
    v5[138] = 4;
    v5[139] = 4;
    v5[140] = 4;
    v5[142] = 4;
    v5[143] = 5;
    v5[144] = 2;
    v5[145] = 2;
    v5[146] = 3;
    v5[147] = 2;
    v5[148] = 2;
    v5[149] = 5;
    v5[150] = 2;
    v5[151] = 2;
    v5[152] = 4;
    v5[153] = 3;
    v5[154] = 3;
    v5[155] = 2;
    v5[156] = 3;
    v5[157] = 3;
    v5[158] = 3;
    v5[161] = 3;
    v5[162] = 2;
    v5[164] = 4;
    v5[165] = 2;
    v5[169] = 2;
    v5[170] = 5;
    v5[171] = 2;
    v5[172] = 1;
    v5[173] = 1;
    v5[174] = 1;
    v5[175] = 1;
    v5[176] = 1;
    v5[177] = 1;
    v5[178] = 1;
    v5[179] = 1;
    v5[180] = 3;
    v5[181] = 3;
    v5[182] = 2;
    v5[183] = 3;
    v5[184] = 3;
    v5[186] = 3;
    v5[187] = 4;
    v5[188] = 3;
    v5[189] = 5;
    v5[190] = 2;
    v5[191] = 2;
    v5[193] = 2;
    v5[194] = 2;
    v5[195] = 5;
    v5[196] = 4;
    v5[197] = 3;
    v5[198] = 1;
    v5[199] = 3;
    v5[201] = 5;
    v5[202] = 5;
    v5[203] = 5;
    v5[204] = 5;
    v5[205] = 5;
    v5[206] = 4;
    v5[207] = 4;
    v5[208] = 4;
    v5[209] = 4;
    v5[210] = 4;
    v5[211] = 4;
    v5[212] = 3;
    v5[214] = 5;
    for (i = 0; i <= 3; ++i)
    {
        for (j = 0; j <= 5; ++j)
        {
            for (k = 0; k <= 2; ++k)
            {
                for (l = 0; l <= 2; ++l)
                    CubeOriginals[i].Data[j][k][l] = v5[54 * i + 9 * j + 3 * k + l];
            }
        }
    }
}

//----- (000000000040700F) ----------------------------------------------------
bool Is_Perfect_Cubic(int x)
{
    // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

    for (int facing = 0; facing <= 5; ++facing)
    {
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 2; ++j)
            {
                if (facing != WorkingCubicInstance.Data[facing][i][j])
                    return 0;
            }
        }
    }
    return 1;
}

//----- (000000000040709F) ----------------------------------------------------
void HackCheck(int x)
{
    if (Is_Perfect_Cubic(x))
    {
        if (Is_Perfect_Cubic(x) != 1)
            exit(0);
    }
}

bool Validate_Next_Opt(char a1)
{
    unsigned int v1; // eax
    unsigned int v2; // eax
    unsigned int v3; // eax

    Store_CurrentWorkingCubic();
    if (a1 > 47 && a1 <= 72 || a1 == 110)
    {
        v1 = a1 - 48;
        if (v1 <= 0x3E)
        {
            switch (v1)
            {
            case 0uLL:
                sub_4018ED();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 1uLL:
                sub_403E02();
                sub_4018ED();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 2uLL:
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_401FBA();
                sub_4014B7();
                sub_401D9F();
                break;
            case 3uLL:
                sub_4016D2();
                sub_401FBA();
                sub_4014B7();
                sub_401D9F();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 4uLL:
                sub_403C51();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_403C70();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                break;
            case 5uLL:
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_403C51();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                break;
            case 6uLL:
                sub_403C51();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4018ED();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 7uLL:
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4018ED();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 8uLL:
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                break;
            case 9uLL:
                sub_403E02();
                sub_402D16();
                sub_4018ED();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                break;
            case 0xAuLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_403C51();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                break;
            case 0xBuLL:
                sub_403E02();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_403C70();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                break;
            case 0xCuLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_403C51();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 0xDuLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                break;
            case 0xEuLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 0xFuLL:
                sub_403E02();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 0x10uLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                break;
            case 0x11uLL:
                sub_403E02();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                break;
            case 0x12uLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_403C51();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 0x13uLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                break;
            case 0x14uLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 0x15uLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_403C51();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 0x16uLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4018ED();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 0x17uLL:
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_401FBA();
                sub_4016D2();
                sub_401D9F();
                break;
            case 0x18uLL:
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_4014B7();
                sub_403E02();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                break;
            case 0x19uLL:
            case 0x1AuLL:
            case 0x1BuLL:
            case 0x1CuLL:
            case 0x1DuLL:
            case 0x1EuLL:
            case 0x1FuLL:
            case 0x20uLL:
            case 0x21uLL:
            case 0x22uLL:
            case 0x23uLL:
            case 0x24uLL:
            case 0x25uLL:
            case 0x26uLL:
            case 0x27uLL:
            case 0x28uLL:
            case 0x29uLL:
            case 0x2AuLL:
            case 0x2BuLL:
            case 0x2CuLL:
            case 0x2DuLL:
            case 0x2EuLL:
            case 0x2FuLL:
            case 0x30uLL:
            case 0x31uLL:
            case 0x32uLL:
            case 0x33uLL:
            case 0x34uLL:
            case 0x35uLL:
            case 0x36uLL:
            case 0x37uLL:
            case 0x38uLL:
            case 0x39uLL:
            case 0x3AuLL:
            case 0x3BuLL:
            case 0x3CuLL:
            case 0x3DuLL:
                break;
            case 0x3EuLL:
                sub_403E02();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                break;
            }
        }
        if (!Old_Color1_LessThan_New_Color1())
        {
            return false;
        }
    }
    else if (a1 > 72 && a1 <= 94 || a1 == 100)
    {
        v2 = a1 - 73;
        if (v2 <= 0x1B)
        {
            switch (v2)
            {
            case 0uLL:
            case 1uLL:
                sub_402AFB();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402AFB();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402F31();
                break;
            case 2uLL:
                sub_403391();
                sub_4014B7();
                sub_403391();
                sub_4018ED();
                sub_403391();
                sub_4014B7();
                sub_403391();
                break;
            case 3uLL:
                sub_403391();
                sub_4014B7();
                sub_403391();
                sub_4014B7();
                sub_402F6F();
                sub_4018ED();
                sub_403391();
                sub_4018ED();
                sub_402F6F();
                sub_4018ED();
                break;
            case 4uLL:
                sub_403DB0();
                sub_402F31();
                sub_401D61();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_401D61();
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                sub_403D87();
                break;
            case 5uLL:
                sub_403DB0();
                sub_402AFB();
                sub_4016D2();
                sub_402AFB();
                sub_401D61();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_401D61();
                sub_402F31();
                sub_403D87();
                break;
            case 6uLL:
                sub_402F31();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403DD9();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_403E02();
                sub_402AFB();
                sub_4016D2();
                sub_402F31();
                break;
            case 7uLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402D16();
                sub_401D9F();
                sub_402F31();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_401FBA();
                break;
            case 8uLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_401FBA();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402D16();
                sub_401D9F();
                sub_402F31();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                break;
            case 9uLL:
                sub_403E2B();
                sub_4016D2();
                sub_402AFB();
                sub_401B46();
                sub_402F31();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402F31();
                sub_4014B7();
                sub_40192B();
                sub_402D16();
                break;
            case 0xAuLL:
                sub_401D9F();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_401FBA();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402D16();
                sub_401D9F();
                sub_402AFB();
                sub_401FBA();
                break;
            case 0xBuLL:
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402F50();
                sub_403CEC();
                sub_403D87();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_403E02();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402F31();
                sub_403DB0();
                break;
            case 0xCuLL:
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                sub_403C70();
                sub_402D16();
                sub_401FBA();
                sub_402F31();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                sub_401D9F();
                sub_402AFB();
                sub_401D9F();
                break;
            case 0xDuLL:
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_4018ED();
                sub_402AFB();
                sub_40242E();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402AFB();
                sub_402213();
                sub_402F50();
                sub_4014B7();
                break;
            case 0xEuLL:
                sub_402D16();
                sub_4018ED();
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_401D9F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402D16();
                sub_401FBA();
                sub_402F31();
                sub_4016D2();
                break;
            case 0xFuLL:
                sub_403E2B();
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                sub_403E54();
                sub_402AFB();
                sub_4018ED();
                sub_4028A2();
                sub_4014B7();
                sub_402D16();
                sub_403E2B();
                sub_4014B7();
                sub_402D16();
                sub_403E54();
                sub_402AFB();
                sub_4018ED();
                sub_4028A2();
                sub_4014B7();
                sub_402D16();
                break;
            case 0x10uLL:
                sub_403E2B();
                sub_4016D2();
                sub_402AFB();
                sub_401B46();
                sub_402F31();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403E54();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_403E2B();
                sub_402F31();
                sub_4014B7();
                sub_402D16();
                sub_40192B();
                sub_402D16();
                break;
            case 0x11uLL:
                sub_402F50();
                sub_403C32();
                sub_402AFB();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_403C13();
                sub_402F50();
                sub_403DD9();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 0x12uLL:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_403E02();
                sub_402F50();
                sub_403C32();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                sub_403C13();
                sub_402F31();
                break;
            case 0x13uLL:
                sub_402F50();
                sub_403C13();
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_403C32();
                sub_402F50();
                sub_403E02();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 0x14uLL:
            case 0x15uLL:
                sub_402D16();
                sub_403C70();
                sub_401D9F();
                sub_402F50();
                sub_403C13();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402AFB();
                sub_403C32();
                sub_402F31();
                break;
            case 0x16uLL:
            case 0x17uLL:
            case 0x18uLL:
            case 0x19uLL:
            case 0x1AuLL:
                break;
            case 0x1BuLL:
                sub_402F50();
                sub_4014B7();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402D16();
                break;
            }
        }
        if ((unsigned char)Is_Base_Done() != 1)
        {
            return false;
        }
    }
    else if (a1 > 95 && a1 <= 122)
    {
        v3 = a1 - 96;
        if (v3 <= 0x1A)
        {
            switch (v3)
            {
            case 0u:
                sub_402AFB();
                sub_4016D2();
                sub_4016D2();
                sub_402F50();
                sub_401D9F();
                sub_402AFB();
                sub_401FBA();
                sub_4018ED();
                sub_402D16();
                sub_401D9F();
                sub_402AFB();
                sub_401FBA();
                break;
            case 1u:
                sub_401D9F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_401FBA();
                sub_403C8F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403CAE();
                break;
            case 2u:
                sub_403C8F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403CAE();
                sub_4016D2();
                sub_401D9F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_401FBA();
                break;
            case 3u:
                sub_403C8F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403CAE();
                sub_4014B7();
                sub_401D9F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_401FBA();
                break;
            case 4u:
            case 14u:
                break;
            case 5u:
                sub_403D68();
                sub_4018ED();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4014B7();
                sub_403D49();
                break;
            case 6u:
                sub_403D49();
                sub_40190C();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_403D68();
                break;
            case 7u:
                sub_403D49();
                sub_4014B7();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4018ED();
                sub_403D68();
                break;
            case 8u:
                sub_403D68();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4018ED();
                sub_403D49();
                break;
            case 9u:
                sub_403D68();
                sub_402AFB();
                sub_4014B7();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403D49();
                sub_403D49();
                sub_402F50();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_403D68();
                break;
            case 10u:
                sub_401D9F();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_401FBA();
                break;
            case 11u:
                sub_402AFB();
                sub_4018ED();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 12u:
                sub_403D49();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403D68();
                sub_401D9F();
                sub_402AFB();
                sub_401FBA();
                break;
            case 13u:
                sub_402AFB();
                sub_40190C();
                sub_402F50();
                sub_4016D2();
                sub_402F31();
                sub_4016D2();
                sub_402F50();
                sub_4018ED();
                sub_402AFB();
                break;
            case 15u:
                sub_403C8F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403CAE();
                break;
            case 16u:
                sub_402F31();
                sub_401B46();
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_40192B();
                sub_402AFB();
                sub_40190C();
                sub_402AFB();
                break;
            case 17u:
                sub_401FBA();
                sub_403D49();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403D68();
                sub_401D9F();
                sub_402AFB();
                break;
            case 18u:
                sub_401D9F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_401FBA();
                break;
            case 19u:
                sub_402AFB();
                sub_40190C();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 20u:
                sub_402D16();
                sub_4018ED();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                break;
            case 21u:
                sub_402AFB();
                sub_40242E();
                sub_402F31();
                sub_401D9F();
                sub_402F31();
                sub_402213();
                sub_402F31();
                sub_401FBA();
                sub_402AFB();
                break;
            case 22u:
                sub_402D16();
                sub_401D9F();
                sub_402F31();
                sub_40242E();
                sub_402F31();
                sub_401FBA();
                sub_402F31();
                sub_402213();
                sub_402D16();
                break;
            case 23u:
                sub_40242E();
                sub_4016D2();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_402213();
                break;
            case 24u:
                sub_403D49();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403D68();
                sub_402AFB();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_402D16();
                break;
            case 25u:
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403D49();
                sub_402D16();
                sub_4014B7();
                sub_402AFB();
                sub_4016D2();
                sub_403D68();
                break;
            case 26u:
                sub_403C8F();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_402AFB();
                sub_4014B7();
                sub_402D16();
                sub_4016D2();
                sub_403CAE();
                break;
            }
        }
        if ((unsigned char)Is_Face_0_Done() != 1)
        {
            return false;
        }
    }
    return true;
}

int dfs(int CIdx, int pos = 0)
{
    static char flagbuf[17] = { 0 };

    if (pos == 0)
        WorkingCubicInstance = CubeOriginals[CIdx];

    // Solution is found
    if (Is_Perfect_Cubic(0))
        return pos;

    // Not done yet, search!
    Cubic last_state = WorkingCubicInstance;
    if (pos == 1 && (CIdx == 0 || CIdx == 3))
        sub_403E02();
    for (char ch = 48; ch <= 122; ++ch)
    {
        if (ch == '_') // No need to check '_'
            continue;
        if (Validate_Next_Opt(ch)) 
        {
            // Next step is acceptable
            flagbuf[pos] = ch;

            // Continue search
            int res = dfs(CIdx, pos + 1);

            if (res == -2)
                return -2; // The solution had been printed

            if (res != -1) // A solution had been found, print it and return
            {
                char bufcopy[17];
                memcpy(bufcopy, flagbuf, res);
                bufcopy[res] = 0;
                std::cout << bufcopy;
                return -2;
            }
        }
        // Search next one
        WorkingCubicInstance = WorkingCubicInstance_Store;
    }
    // Restore the last state
    WorkingCubicInstance = last_state;

    // No solution had been found
    return -1;
}

void solve()
{
    INIT_CUBIC_DATAS();
    std::cout << "flag{";
    dfs(0);
    std::cout << "_";
    dfs(1);
    std::cout << "_";
    dfs(2);
    std::cout << "_";
    dfs(3);
    std::cout << "}\n";
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _rep(i, a, b) for (int i = (a); i < (b); ++i)

#define Cube(name) int (name)[6][3][3]


// Base
Cube(curCube);
Cube(tmpCube);
Cube(recordCube);
int color3[3] = {0, 0, 0};

void getRow(int side, int row)
{
	_rep(i, 0, 3) color3[i] = tmpCube[side][row][i];
}

void getCol(int side, int col)
{
	_rep(i, 0, 3) color3[i] = tmpCube[side][i][col];
}

void setRow(int side, int row)
{
	_rep(i, 0, 3) curCube[side][row][i] = color3[i];
}

void setCol(int side, int col)
{
	_rep(i, 0, 3) curCube[side][i][col] = color3[i];
}

void reColor()
{
	int tmp;
	tmp = color3[0];
	color3[0] = color3[2];
	color3[2] = tmp;
}

void side_clock(int side)
{
	_rep(i, 0, 3) {
		getRow(side, i);
		setCol(side, 2 - i);
	}
}

void side_anticlock(int side)
{
	_rep(i, 0, 3) {
		getCol(side, 2 - i);
		setRow(side, i);
	}
}

// Base Operations
// Up
void U_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_clock(0);
	getRow(3, 2); setRow(5, 2);
	getRow(5, 2); reColor(); setCol(2, 2);
	getCol(2, 2); setCol(4, 2);
	getCol(4, 2); reColor(); setRow(3, 2);
}

void U_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_anticlock(0);
	getRow(5, 2); setRow(3, 2);
	getCol(2, 2); reColor(); setRow(5, 2);
	getCol(4, 2); setCol(2, 2);
	getRow(3, 2); reColor(); setCol(4, 2);
}

void U2_clock()
{
	U_clock(); U_clock();
}

void U2_anticlock()
{
	U_anticlock(); U_anticlock();
}

// Down
void D_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_clock(1);
	getRow(3, 0); reColor(); setCol(4, 0);
	getCol(4, 0); setCol(2, 0);
	getCol(2, 0); reColor(); setRow(5, 0);
	getRow(5, 0); setRow(3, 0);
}

void D_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_anticlock(1);
	getCol(4, 0); reColor(); setRow(3, 0);
	getCol(2, 0); setCol(4, 0);
	getRow(5, 0); reColor(); setCol(2, 0);
	getRow(3, 0); setRow(5, 0);
}

void D2_clock()
{
	D_clock(); D_clock();
}

void D2_anticlock()
{
	D_anticlock(); D_anticlock();
}

// Front
void F_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_clock(2);
	getRow(0, 2); reColor(); setCol(5, 2);
	getCol(5, 2); setCol(1, 2);
	getCol(1, 2); reColor(); setRow(4, 2);
	getRow(4, 2); setRow(0, 2);
}

void F_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_anticlock(2);
	getCol(5, 2); reColor(); setRow(0, 2);
	getCol(1, 2); setCol(5, 2);
	getRow(4, 2); reColor(); setCol(1, 2);
	getRow(0, 2); setRow(4, 2);
}

void F2_clock()
{
	F_clock(); F_clock();
}

void F2_anticlock()
{
	F_anticlock(); F_anticlock();
}

// Back
void B_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_clock(3);
	getRow(0, 0); setRow(4, 0);
	getRow(4, 0); reColor(); setCol(1, 0);
	getCol(1, 0); setCol(5, 0);
	getCol(5, 0); reColor(); setRow(0, 0);
}

void B_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_anticlock(3);
	getRow(4, 0); setRow(0, 0);
	getCol(1, 0); reColor(); setRow(4, 0);
	getCol(5, 0); setCol(1, 0);
	getRow(0, 0); reColor(); setCol(5, 0);
}

void B2_clock()
{
	B_clock(); B_clock();
}

void B2_anticlock()
{
	B_anticlock(); B_anticlock();
}

// Left
void L_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_clock(4);
	getCol(0, 0); reColor(); setRow(2, 0);
	getRow(2, 0); setRow(1, 0);
	getRow(1, 0); reColor(); setCol(3, 0);
	getCol(3, 0); setCol(0, 0);
}

void L_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_anticlock(4);
	getRow(2, 0); reColor(); setCol(0, 0);
	getRow(1, 0); setRow(2, 0);
	getCol(3, 0); reColor(); setRow(1, 0);
	getCol(0, 0); setCol(3, 0);
}

void L2_clock()
{
	L_clock(); L_clock();
}

void L2_anticlock()
{
	L_anticlock(); L_anticlock();
}

// Right
void R_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_clock(5);
	getCol(0, 2); setCol(3, 2);
	getCol(3, 2); reColor(); setRow(1, 2);
	getRow(1, 2); setRow(2, 2);
	getRow(2, 2); reColor(); setCol(0, 2);
}

void R_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	side_anticlock(5);
	getCol(3, 2); setCol(0, 2);
	getRow(1, 2); reColor(); setCol(3, 2);
	getRow(2, 2); setRow(1, 2);
	getCol(0, 2); reColor(); setRow(2, 2);
}

void R2_clock()
{
	R_clock(); R_clock();
}

void R2_anticlock()
{
	R_anticlock(); R_anticlock();
}


// M
void M_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	getCol(0, 1); setCol(3, 1);
	getCol(3, 1); reColor(); setRow(1, 1);
	getRow(1, 1); setRow(2, 1);
	getRow(2, 1); reColor(); setCol(0, 1);
}

void M_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	getCol(3, 1); setCol(0, 1);
	getRow(1, 1); reColor(); setCol(3, 1);
	getRow(2, 1); setRow(1, 1);
	getCol(0, 1); reColor(); setRow(2, 1);
}

void M2_clock()
{
	M_anticlock(); M_anticlock();
}

// E
void E_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	getRow(3, 1); setRow(5, 1);
	getRow(5, 1); reColor(); setCol(2, 1);
	getCol(2, 1); setCol(4, 1);
	getCol(4, 1); reColor(); setRow(3, 1);
}

void E_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	getRow(5, 1); setRow(3, 1);
	getCol(2, 1); reColor(); setRow(5, 1);
	getCol(4, 1); setCol(2, 1);
	getRow(3, 1); reColor(); setCol(4, 1);
}

void E2_clock()
{
	E_anticlock(); E_anticlock();
}

// S
void S_clock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	getRow(0, 1); reColor(); setCol(5, 1);
	getCol(5, 1); setCol(1, 1);
	getCol(1, 1); reColor(); setRow(4, 1);
	getRow(4, 1); setRow(0, 1);
}

void S_anticlock()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	getCol(5, 1); reColor(); setRow(0, 1);
	getCol(1, 1); setCol(5, 1);
	getRow(4, 1); reColor(); setCol(1, 1);
	getRow(0, 1); setRow(4, 1);
}


// u
void u_clock()
{
	U_clock(); E_anticlock();
}

void u_anticlock()
{
	U_anticlock(); E_clock();
}

// d
void d_clock()
{
	D_clock(); E_clock();
}

void d_anticlock()
{
	D_anticlock(); E_anticlock();
}

// f
void f_clock()
{
	F_clock(); S_clock();
}

void f_anticlock()
{
	F_anticlock(); S_anticlock();
}

// b
void b_clock()
{
	B_clock(); S_anticlock();
}

void b_anticlock()
{
	B_anticlock(); S_clock();
}

// l
void l_clock()
{
	L_clock(); M_clock();
}

void l_anticlock()
{
	L_anticlock(); M_anticlock();
}

// r
void r_clock()
{
	R_clock(); M_anticlock();
}

void r_anticlock()
{
	R_anticlock(); M_clock();
}


// x
void x_clock()
{
	R_clock(); L_anticlock(); M_anticlock();
}

void x_anticlock()
{
	R_anticlock(); L_clock(); M_clock();
}

// y
void y_clock()
{
	U_clock(); D_anticlock(); E_anticlock();
}

void y_anticlock()
{
	U_anticlock(); D_clock(); E_clock();
}

// z
void z_clock()
{
	F_clock(); B_anticlock(); S_clock();
}

void z_anticlock()
{
	F_anticlock(); B_clock(); S_anticlock();
}


// base operation define
#define U U_clock();
#define U_ U_anticlock();
#define U2 U2_clock();
#define U_2 U2_anticlock();
#define D D_clock();
#define D_ D_anticlock();
#define D2 D2_clock();
#define D_2 D2_anticlock();
#define F F_clock();
#define F_ F_anticlock();
#define F2 F2_clock();
#define F_2 F2_anticlock();
#define B B_clock();
#define B_ B_anticlock();
#define B2 B2_clock();
#define B_2 B2_anticlock();
#define L L_clock();
#define L_ L_anticlock();
#define L2 L2_clock();
#define L_2 L2_anticlock();
#define R R_clock();
#define R_ R_anticlock();
#define R2 R2_clock();
#define R_2 R2_anticlock();

#define M M_clock();
#define M_ M_anticlock();
#define M2 M2_clock();
#define E E_clock();
#define E_ E_anticlock();
#define E2 E2_clock();
#define S S_clock();
#define S_ S_anticlock();

#define u u_clock();
#define u_ u_anticlock();
#define d d_clock();
#define d_ d_anticlock();
#define f f_clock();
#define f_ f_anticlock();
#define b b_clock();
#define b_ b_anticlock();
#define l l_clock();
#define l_ l_anticlock();
#define r r_clock();
#define r_ r_anticlock();
#define r2 r r

#define x x_clock();
#define x_ x_anticlock();
#define y y_clock();
#define y_ y_anticlock();
#define z z_clock();
#define z_ z_anticlock();

// base operation group define
#define RU R U
#define RU_ R U_
#define R_U R_ U
#define R_U_ R_ U_

#define RUR_ R U R_
#define RU_R R U_ R
#define RU_R_ R U_ R_
#define R_UR R_ U R
#define R_UR_ R_ U R_
#define R_U_R R_ U_ R
#define RU_U_ R U_ U_
#define RU_2 R U_2
#define R_U2 R_ U2
#define R2U R2 U
#define R2U_ R2 U_
#define R_2U R_2 U
#define R_2U_ R_2 U_
#define RU_2R R U_2 R
#define RU_R2 R U_ R2
#define R_U_R2 R_ U_ R2
#define RU2R_ R U2 R_
#define RU_2R_ R U_2 R_
#define R_U2R R_ U2 R

#define RURU_ R U R U_
#define RUR_U R U R_ U
#define RUR_U_ R U R_ U_
#define RU_R_U R U_ R_ U
#define RU_R_U_ R U_ R_ U_
#define R_URU R_ U R U
#define R_URU_ R_ U R U_
#define R_U_RU R_ U_ R U
#define R_U_RU_ R_ U_ R U_

#define URU_R_ U R U_ R_
#define U_RUR_ U_ R U R_
#define U_RU_R_ U_ R U_ R_

#define RU2R_U_ R U2 R_ U_
#define RU_2R_U R U_2 R_ U
#define RURU_R_ R U R U_ R_
#define R2UR_ R2 U R_
#define R2UR_U_ R2 U R_ U_
#define R2UR_U_R R2 U R_ U_ R
#define R2U_R_U R2 U_ R_ U

#define UR U R
#define UR_ U R_
#define URU_ U R U_
#define UR_U_ U R_ U_

#define F_UF F_ U F
#define F_U_F F_ U_ F

#define R_F R_ F
#define R_F_ R_ F_
#define R_FRF R_ F R F
#define R_FRF_ R_ F R F_

#define R2F R2 F
#define R2F_ R2 F_
#define R_2F_ R_2 F_
#define R_F_R R_ F_ R
#define R_2FRF_ R_2 F R F_

#define RB_ R B_
#define R2B R2 B
#define R2B_ R2 B_

#define R2D_ R2 D_
#define R_D R_ D

#define Ru_R_2 R u_ R_2
#define R_uR2 R_ u R2
#define R_uR_2 R_ u R_2
#define R_2u_ R_2 u_
#define R_2uR_ R_2 u R_

#define R_U_F R_ U_ F
#define RB_R_U_ R B_ R_ U_
#define RURB R U R B
#define R_URB R_ U R B
#define R_URBR_ R_ U R B R_
#define RUR_F_ R U R_ F_
#define RUR_F_R R U R_ F_ R
#define R_UR_d_ R_ U R_ d_
#define R_FR2U_R_U_ R_ F R2 U_ R_ U_
#define R_F_R2U_ R_ F_ R2 U_
#define RU2L_UR_ R U2 L_ U R_

#define B_U_ B_ U_
#define U_RD_ U_ R D_

#define FRUR_U_F_ F R U R_ U_ F_
#define fRUR_U_f_ f R U R_ U_ f_

#define RU_2R_U_RU_R_ R U_2 R_ U_ R U_ R_
#define R_U2RUR_UR R_ U2 R U R_ U R

#define rU_2R_U_RU_r_ r U_2 R_ U_ R U_ r_
#define r_U2RUR_Ur r_ U2 R U R_ U r

#define RUR_URU2R_ R U R_ U R U2 R_
#define R_U_RU_R_U2R R_ U_ R U_ R_ U2 R

#define r_U2 r_ U2
#define rU_2 r U_2

#define rUr_ r U r_
#define rU_r_ r U_ r_

#define r_RU r_ R U
#define rUR_U r U R_ U
#define rUR_U_ r U R_ U_
#define r_FR r_ F R
#define r_FRF_ r_ F R F_
#define URU_r_ U R U_ r_

#define l_U_l l_ U_ l
#define l_Ul l_ U l

#define L_U_LU L_ U_ L U

#define lU_R_U l U_ R_ U

// F2L
#define F2L11 RUR_
#define F2L12 y_ R_U_R
#define F2L13 y_ U_ R_UR
#define F2L14 U R U_ R_
#define F2L21 U_ RUR_U RUR_
#define F2L22 d R_U2R d_ RUR_
#define F2L23 U_ RU_R_U RUR_
#define F2L24 U y_ R_U_RU_ R_U_R
#define F2L25 U_ RU_2R_ d R_U_R
#define F2L26 d R_URU_ R_U_R
#define F2L31 U_ RU_2R_ U2 RU_R_
#define F2L32 U_RUR_ U2 RU_R_
#define F2L33 d R_U2R U_2 R_UR
#define F2L34 d R_U_R U_2 R_UR
#define F2L41 y_ U_ R_U2R U_ R_UR
#define F2L42 U RU2R_ U RU_R_
#define F2L43 U2 RUR_U RU_R_
#define F2L44 y_ U2 R_U_RU_ R_UR
#define F2L51 U RU_R_ U_ F_UF
#define F2L52 U_ F_UF U RU_R_
#define F2L61 d R_U_R d_ RUR_
#define F2L62 U_ RUR_ d R_U_R
#define F2L63 d R_UR U2 R_UR
#define F2L64 U_RU_R_ U2 RU_R_
#define F2L71 RU_2R_ U_ RUR_
#define F2L72 y_ R_U2R U R_U_R
#define F2L81 RU_R_U d R_U_R
#define F2L82 y_ R_URU_ d_ RUR_
#define F2L91 RU_R_ d R_UR
#define F2L92 RUR_U_ RUR_U_ RUR_
#define F2LA1 RU_R_U RU_R_
#define F2LA2 y_ R_UR U_ R_UR
#define F2LA3 RUR_U_ RUR_
#define F2LA4 y_ R_U_RU R_U_R
#define F2LB1 RUR_ d R_URU_ R_UR
#define F2LB2 RUR_U_ U_ RUR_U_ RUR_
#define F2LC1 RU_R_U RU_2R_ U RU_R_
#define F2LC2 RU_R_U d R_U_RU_ R_UR
#define F2LC3 RU_R_ U_ RUR_ U2 RU_R_
#define F2LC4 RU_R_U_ RU_R_ U F_U_F
#define F2LC5 RU_2R_U RU_2R_U y_ R_U_R


// OLL
#define OLL01 RU_U_ R_2FRF_ U2 R_FRF_	// *2
#define OLL02 FRUR_U_F_ fRUR_U_f_		// 2
#define OLL03 fRUR_U_f_ U_ FRUR_U_F_	// 4
#define OLL04 fRUR_U_f_ U FRUR_U_F_		// 3
#define OLL05 r_U2 RUR_U r				// 8
#define OLL06 rU_2 R_U_RU_ r_			// 7
#define OLL07 r U R_ U R U2 r_			// 6
#define OLL08 r_ U_ R U_ R_ U2 r		// 5
#define OLL09 RUR_U_ R_F R2UR_U_ F_		// 13
#define OLL10 RUR_U R_FRF_ RU_2R_		// 8
#define OLL11 rUR_U R_FRF_ R U2 r_		// *6
#define OLL12 FRUR_U_F_ U FRUR_U_F_		// *7
#define OLL13 F URU_ R_2F_ RURU_R_		// 9
#define OLL14 R_F RUR_F_R y_ RU_R_		// *10
#define OLL15 l_U_l L_U_LU l_Ul			// *8
#define OLL16 rUr_ RUR_U_ rU_r_			// *42
#define OLL17 RUR_U R_FRF_ U2 R_FRF_	// 18
#define OLL18 F RUR_U y_ R_U2 R_FRF_	// 17
#define OLL19 M U RUR_U_ M_ R_FRF_		// *17
#define OLL20 r_RU RUR_U_ r2 R_2 URU_r_	// 20
#define OLL21 RU2R_U_ RUR_U_ RU_R_		// 21
#define OLL22 RU_2 R_2U_ R2U_ R_2 U2 R	// 22
#define OLL23 R2D_ RU_2 R_D RU_2R		// 25
#define OLL24 rUR_U_ r_FRF_				// 25
#define OLL25 F_ rUR_U_ r_FR			// 24
#define OLL26 R U_2 R_ U_ R U_ R_		// 27
#define OLL27 R_ U2 R U R_ U R			// 26
#define OLL28 rUR_U_ r_ R URU_R_		// 57
#define OLL29 rU_2R_U_RU_r_ R_U2RUR_UR	// *45
#define OLL30 r_U2RUR_Ur RU_2R_U_RU_R_	// *45
#define OLL31 R_U_F URU_ R_F_R			// 40
#define OLL32 RU B_U_ R_URBR_			// 39
#define OLL33 RUR_U_ R_FRF_				// 37
#define OLL34 RUR_U_ x D_ R_UR E_		// *37
#define OLL35 RU_2 R_2FRF_ RU_2R_		// *37
#define OLL36 R_U_RU_ R_URU lU_R_U		// *32
#define OLL37 F RU_R_U_ RUR_F_			// 33
#define OLL38 RUR_U RU_R_U_ R_FRF_		// *31
#define OLL39 L F_ L_U_LU F U_ L_		// 32
#define OLL40 R_F RUR_U_ F_ UR			// 31
#define OLL41 RUR_URU2R_ FRUR_U_F_		// 43
#define OLL42 R_U_RU_R_U2R FRUR_U_F_	// 41
#define OLL43 B_ U_ R_URB				// 45
#define OLL44 fRUR_U_f_					// 45
#define OLL45 FRUR_U_F_					// 44
#define OLL46 R_U_ R_FRF_ UR			// *43
#define OLL47 F_ L_U_LU L_U_LU F		// *51
#define OLL48 F RUR_U_ RUR_U_ F_		// 51
#define OLL49 RB_ R2F R2B R2F_ R		// 50
#define OLL50 R_F R2B_ R2F_ R2B R_		// 49
#define OLL51 f RUR_U_ RUR_U_ f_		// 48
#define OLL52 R_U_RU_ R_U y_ R_URB		// 52
#define OLL53 r_ U2 RUR_U_ RUR_U r		// 53
#define OLL54 r U R_URU_ R_URU_ U_ r_	// 54
#define OLL55 R_ F URU_ R_2F_ R2UR_U_R	// *50
#define OLL56 rUr_ URU_R_ URU_R_ rU_r_	// *54
#define OLL57 RUR_U_ r R_ URU_r_		// 28


// PLL
#define PLL11 RU_R U RURU_ R_U_R2		// 12
#define PLL12 R_2U RUR_U_ R_U_ R_UR_	// 11
#define PLL13 M2 U M2 U2 M2 U M2		// 13
#define PLL14 M2 U M2 U M_ U2 M2 U2 M_ U2	// 14
#define PLL15 x_ R2 D2 R_U_R D2 R_UR_ x	// 16
#define PLL16 x_ RU_R D2 R_UR D2 R2 x	// 15
#define PLL17 R2UR_U_ y RUR_U_ RUR_U_ RUR_ y_ RU_R2	// 17
#define PLL21 RUR_U_ R_FR2U_R_U_ RUR_F_	// 21
#define PLL22 RUR_F_ RUR_U_ R_FR2U_R_U_	// 22
#define PLL23 z U_RD_ R2UR_U_ R2U D R_	// 23
#define PLL24 F RU_R_U_ RUR_F_ RUR_U_ R_FRF_	// 24
#define PLL25 U_ R_URU_ R_2 b_ x R_UR y_ RUR_U_ R2 x_	// 25
#define PLL26 R_UR_d_ R_F_ R2U_R_U R_FRF	// 26
#define PLL27 RU_2 R_U2 RB_R_U_ RURB R_2 U	// 27
#define PLL28 R_U2 RU_2 R_F RUR_U_ R_F_R2U_	// 28
#define PLL31 z R_UR_ z_ RU2L_UR_ z UR_ z_ RU2L_UR_	// *31
#define PLL32 z U_RD_ R2UR_U_ z_ RUR_ z R2UR_ D R_	// *32
#define PLL33 R_2u_ RU_R U R_uR_2 y RU_R_	// *
#define PLL34 RUR_ y_ R_2u_ RU_R_U R_uR2	// *
#define PLL35 R_2uR_ UR_U_ Ru_R_2 y_ R_UR	// *
#define PLL36 R_ d_ F R_2uR_ U RU_R u_ R2	// *


void record()
{
	memcpy(recordCube, curCube, sizeof(curCube));
}

int count_F2L()
{
	int cnt = 0;
	if (curCube[2][0][0] == curCube[2][0][1] && curCube[4][2][0] == curCube[4][2][1] && curCube[1][0][2] == 1) ++cnt;
	if (curCube[4][0][0] == curCube[4][0][1] && curCube[3][0][0] == curCube[3][1][0] && curCube[1][0][0] == 1) ++cnt;
	if (curCube[3][0][2] == curCube[3][1][2] && curCube[5][0][0] == curCube[5][1][0] && curCube[1][2][0] == 1) ++cnt;
	if (curCube[5][0][2] == curCube[5][1][2] && curCube[2][2][0] == curCube[2][2][1] && curCube[1][2][2] == 1) ++cnt;
	return cnt;
}

bool check_F2L()
{
	memcpy(tmpCube, curCube, sizeof(curCube));
	memcpy(curCube, recordCube, sizeof(curCube));
	int old = count_F2L();
	memcpy(curCube, tmpCube, sizeof(curCube));
	int now = count_F2L();
	// printf("%d %d\n", old, now);
	if (now <= old)
		return false;
	return true;
}

bool check_OLL()
{
	_rep(i, 0, 3)
		_rep(j, 0, 3)
			if (curCube[0][i][j] != 0) return false;
	return true;
}

bool check_top(int index)
{
	if (index % 2) {
		_rep(i, 0, 3)
			if (curCube[index][2][i] != index) return false;
	} else {
		_rep(i, 0, 3)
			if (curCube[index][i][2] != index) return false;
	}
	return true;
}

bool check_PLL()
{
	if (!check_OLL()) return false;
	_rep(i, 2, 6)
		if (!check_top(i)) return false;
	return true;
}

void solve_cube_operation(char c)
{
	record(); // printf("\n%c ", c);
	if (c >= 48 && c <= 72 || c == 110) { // F2L 26
        switch(c) {
            case 110: F2L12 break;
            case 48: F2L43 break;
            case 49: F2L44 break;
            case 50: F2L51 break;
            case 51: F2L52 break;
            case 52: F2L61 break;
            case 53: F2L62 break;
            case 54: F2L63 break;
            case 55: F2L64 break;
            case 56: F2L71 break;
            case 57: F2L72 break;
            case 58: F2L81 break;
            case 59: F2L82 break;
            case 60: F2L91 break;
            case 61: F2L92 break;
            case 62: F2LA1 break;
            case 63: F2LA2 break;
            case 64: F2LA3 break;
            case 65: F2LA4 break;
            case 66: F2LB1 break;
            case 67: F2LB2 break;
            case 68: F2LC1 break;
            case 69: F2LC2 break;
            case 70: F2LC3 break;
            case 71: F2LC4 break;
            case 72: F2LC5 break;
            default: break;
        }
        if (!check_F2L()) {
        	puts("Not this one.");
        	exit(0);
        }
    } else if (c >= 73 && c <= 94 || c == 100) {	// PLL 20
        switch(c) {
            case 73: PLL11 break;
            case 74: PLL11 break;
            case 100: PLL12 break;
            case 75: PLL13 break;
            case 76: PLL14 break;
            case 77: PLL15 break;
            case 78: PLL16 break;
            case 79: PLL17 break;
            case 80: PLL21 break;
            case 81: PLL22 break;
            case 82: PLL23 break;
            case 83: PLL24 break;
            case 84: PLL25 break;
            case 85: PLL26 break;
            case 86: PLL27 break;
            case 87: PLL28 break;
            case 88: PLL31 break;
            case 89: PLL32 break;
            case 90: PLL33 break;
            case 91: PLL34 break;
            case 92: PLL35 break;
            case 93: PLL36 break;
            case 94: PLL36 break;
        }
        if (!check_PLL()) {
        	puts("Not this one.");
        	exit(0);
        }
    } else if (c >= 96 && c <= 122 && c != 100 && c != 110) {	// OLL 25
        switch(c) {
        	case 96: OLL01 break;
            case 97: OLL02 break;
            case 98: OLL03 break;
            case 99: OLL04 break;
            case 101: OLL05 break;
            case 102: OLL06 break;
            case 103: OLL07 break;
            case 104: OLL08 break;
            case 105: OLL20 break;
            case 106: OLL37 break;
            case 107: OLL21 break;
            case 108: OLL24 break;
            case 109: OLL22 break;
            case 111: OLL44 break;
            case 112: OLL23 break;
            case 113: OLL25 break;
            case 114: OLL45 break;
            case 115: OLL26 break;
            case 116: OLL27 break;
            case 117: OLL49 break;
            case 118: OLL50 break;
            case 119: OLL43 break;
            case 120: OLL28 break;
            case 121: OLL57 break;
            case 122: OLL51 break;
        }
        if (!check_OLL()) {
        	puts("Not this one.");
        	exit(0);
        }
    }
}


// main
Cube(cubes[4]);

void init(void) __attribute__((constructor));

void init(void)
{
	int arr[4 * 6 * 3 * 3 + 10] = {
	    // 0
        2, 0, 0, 3, 0, 0, 2, 5, 1,
        1, 1, 5, 1, 1, 1, 1, 1, 3,
        2, 5, 0, 5, 5, 3, 5, 2, 3,
        4, 4, 4, 4, 4, 4, 0, 4, 4,
        2, 2, 4, 2, 2, 0, 1, 2, 5,
        3, 3, 0, 3, 3, 0, 3, 5, 5,
        // 1
        0, 3, 0, 2, 0, 4, 0, 5, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 5, 2, 2, 0, 2, 2, 4,
        3, 3, 3, 3, 3, 3, 5, 0, 4,
        4, 4, 3, 4, 4, 0, 4, 4, 2,
        5, 5, 5, 5, 5, 5, 3, 0, 2,
        // 2
        4, 0, 3, 3, 0, 2, 0, 0, 5,
        1, 1, 1, 1, 1, 1, 1, 1, 0,
        5, 5, 2, 5, 5, 5, 5, 0, 1,
        4, 4, 4, 4, 4, 4, 0, 4, 5,
        2, 2, 3, 2, 2, 5, 2, 2, 4,
        3, 3, 2, 3, 3, 3, 0, 0, 3,
        // 3
        2, 0, 4, 2, 0, 0, 0, 2, 5,
        2, 1, 1, 1, 1, 1, 1, 1, 1,
        3, 3, 2, 3, 3, 0, 3, 4, 3,
        5, 2, 2, 0, 2, 2, 5, 4, 3,
        1, 3, 0, 5, 5, 5, 5, 5, 4,
        4, 4, 4, 4, 4, 3, 0, 5, 0,
	};

	_rep(i, 0, 4) {
        _rep(j, 0, 6) {
            _rep(k, 0, 3) {
                _rep(h, 0, 3) {
                    cubes[i][j][k][h] = arr[i * 54 + j * 9 + k * 3 + h];
                }
            }
        }
	}
}

bool check_cube()
{
	_rep(i, 0, 6)
        _rep(j, 0, 3)
            _rep(k, 0, 3)
                if (curCube[i][j][k] != i)
                    return false;
    return true;
}

void Nothing(int index)
{
	if (check_cube(index))
		if (!check_cube(index))
			exit(0);
}

int solve_cube(int index, char* operation, int cur_op)
{
    _rep(i, 0, 6)
        _rep(j, 0, 3)
            _rep(k, 0, 3)
                curCube[i][j][k] = cubes[index][i][j][k];

    _rep(i, cur_op, strlen(operation)) {
        if ((i - cur_op == 1) && (index == 0 || index == 3))
            y_
        solve_cube_operation(operation[i]);
        if (!( i & ~i)) {
        	_rep(j, 0, 0x233)
        		Nothing(index);
        }
        if (operation[i] == '_') {
        	_rep(j, 0, 8)
        		Nothing(index);
        	return (i + 1);
    	}
    }
    return strlen(operation);
}

void solve_cubes(char* operation)
{
	int cur_op = 0;
	_rep(i, 0, 4) {
		cur_op = solve_cube(i, operation, cur_op);
    }
}

// test
void print()
{
	_rep(i, 0, 6) {
		_rep(j, 0, 3)
			_rep(k, 0, 3)
				printf("%d%c", curCube[i][j][k], k == 2 ? '\n': ' ');
        printf("====\n");
	}
}

void test()
{
    _rep(i, 0, 6)
        _rep(j, 0, 3)
            _rep(k, 0, 3)
                curCube[i][j][k] = i; // j * 3 + k + 1;

	print();
}

int main()
{
	char flag[0x30];
	char str[0x20];
	char *op[4];

	puts("Rubik's Cube was born in 1974. Please solve these cubes.");
	scanf("%22s", flag);

	if (strncmp(flag, "flag{", 5) || flag[21] != '}') {
		puts("You know nothing, don't you?");
		return 0;
	}

	strncpy(str, flag + 5, 0x10);
	str[0x10] = '\x00';
	solve_cubes(str);
	
	/*
	_rep(i, 0, 4) {
        op[i] = malloc(10);
	}
	op[0] = strtok(str, "_");
	_rep(i, 1, 4) {
		op[i] = strtok(NULL, "_");
	}
    _rep(i, 0, 4) {
        if (op[i] == NULL) {
            puts("You know nothing about reverse, don't you?");
            return 0;
        }
        // printf("%s\n", op[i]);
    }*/
    
    _rep(i, 0, 4)
		if (!check_cube(i)) {
            printf("%d: ", i);
            puts("You need more practice, don't you?");
            // print();
            exit(0);
        }

    puts("You really understand Rubik's Cube or Reverse, congratulation!");

	return 0;
}
// flag{CFoP_iS_noT_H@rd}
// n F2L12
// d PLL12
// F2LB2 F2LC3 OLL44 PLL21
// OLL20 PLL24
// F2L12 OLL44 PLL25
// F2LC5 F2LA3 OLL45 PLL12

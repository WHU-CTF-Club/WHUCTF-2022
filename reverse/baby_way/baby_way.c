#include <stdio.h>
#include <malloc.h>

#define int long long // MORE MEMORIES!

#include "baby_way.h"

// flag{A1g0R1tHm_1S_FvN_64D1DB1C-261A-4D62-882C-16C32461CAB1}

#define NEW(T, C) (T*)malloc(sizeof(T) * (C))
#define DELETE(P) { free(P); P = NULL; }
#define INF 0x7FFFFFFFFFFFFFFFu

// read an integer, signed.
int read();

FILE* stream;
signed main() {
	setbuf(stdout, NULL);
	printf("Hold on, I'll calculate the flag for you.\n");
	stream = fmemopen((void*)the_way_data, the_way_length, "r");

	if (NULL == stream)
		return 1;
	
	register int n = read();
	register int m = read();

	unsigned int** graph = NEW(unsigned int*, n + 5);
	for (register int i = 0; i < n + 5; ++i)
		graph[i] = NEW(int, n + 5);

	for (register int i = 0; i < n + 5; ++i) {
		for (register int j = 0; j < n + 5; ++j)
			graph[i][j] = INF;
	}

	for (register int i = 0; i < m; ++i) {
		register int a, b, c;
		a = read();
		b = read();
		c = read();
		graph[a][b] = c;
	}

	for (register int k = 1; k <= n; ++k) {
		for (register int i = 1; i <= n; ++i) {
			for (register int j = 1; j <= n; ++j) {
				register unsigned int tmp = graph[i][k] + graph[k][j];
				if (tmp < graph[i][j])
					graph[i][j] = tmp;
			}
		}
	}

	printf("Wow. Your flag is: ");

	for (register int i = 0; i < ans_table_length; ++i)
		putchar(graph[1][ans_table_data[i] / 3 ^ 14]);
	putchar('\n');

	for (register int i = 0; i < n + 5; ++i)
		DELETE(graph[i]);
	DELETE(graph);
	
	fclose(stream);

	return 0;
}

inline int read() {
	register int ret = 0;
	register char flag = 1;
	register char ch = fgetc(stream);
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			flag = -1;
			ch = fgetc(stream);
			break;
		}
		ch = fgetc(stream);
	}
	while (ch >= '0' && ch <= '9') {
		ret = ret * 10 + ch - '0';
		ch = fgetc(stream);
	}
	return flag * ret;
}
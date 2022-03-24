#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bad_input() {
	printf("bad input\n");
	exit(0);
	return 0;
}

int check (char *str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		int c = str[i] - '0';
		if ((c < 0) || (c > 9)) return 0;
	}
	for (int i = 0, j = 1; i < len; i++) {
		while (str[i] != str[j] && j < len) {
			j++;
		}
		if (str[i] == str[j]) return 0;
	}
	return 1;
}

void swap (char *a, char *b) {
	char t = *a;
	*a = *b;
	*b = t;
}

void reverse (char *str, int len) {
    for (int i = 0; i < len/2; i++) {
		swap(&str[i], &str[len-i-1]);
    }
}

int next_permutation (char *str) {
	int  len = strlen(str);
	int larger_perm_found = 1;
	int j = len - 2;
	while (j >= 0 && str[j] > str[j+1]) {
		j--;
	}
	if (j < 0) {
		larger_perm_found = 0;
		return larger_perm_found;
	}
	int l = j + 1;
	for (int k = l; k < len; k++) {
		if (str[j] < str[k]) {
			l = k;
		}
	}
	swap(&str[j], &str[l]);
	reverse(str + j + 1, len - j - 1);
	return larger_perm_found;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	char str[100] = "";
	int n;
	int len = strlen(str);
	if (scanf("%99[ 0-9]s", str) != 1) {
                bad_input();
        }
	for (int i = 0; i < len; i++) {
		if (str[i] == ' ') {
			bad_input();
		}
	}
	if (scanf("%i", &n) != 1) {
		bad_input();
	}
	if (n == 0) {
		return 0;
	}
	if (!check(str)) {
		bad_input();
	}
	
	int m = 0;
	while (next_permutation(str) && m < n) {
		printf("%s\n", str);
		m++;
	}
	return 0;
}

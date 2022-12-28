
void lstp() {}

char func() {
	char a = 'a';
	char b[10];
	a += 1;
	for (int i =0;i < 3000;i++) {
		if (i == 302)
			lstp();
		printf("%d\n", i);
	}
	return a;
}

int main() {
	char c;

	c = func();
	printf("%c\n", c);
}

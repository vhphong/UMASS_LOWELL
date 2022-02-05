#include <stdio.h>
void a(void);
void b(void);
int c(int x, int y);

int main()
{
	a();
	b();

	void (*p)(void);
	void (*v[2])(void);
	p = a;
	p();
	v[0] = a;
	v[1] = b;
	v[0]();
	v[1]();
	printf("%p\n", &p);
	printf("%p\n", p);
	printf("%p\n", a);
	printf("%p\n", b);
	return 0;

}

void a(void){
	printf("Func a\n");
}
void b(void)
{
	printf("Func b\n");
}
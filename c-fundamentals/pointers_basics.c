#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
	uint32_t x = 100;
	uint32_t *p = &x;

	printf("x = %u\n", x);
	printf("*p = %u\n", *p);
	printf("p == &x: %d\n", p == &x);

	*p = 200;
	printf("x after *p=200: %u\n", x);

	uint32_t arr[] = {10, 20, 30, 40, 50};
	uint32_t *ap = arr;

	printf("arr[0] via pointer: %u\n", *ap);
	printf("arr[2] via pointer: %u\n", *(ap + 2));
	printf("arr[4] via pointer: %u\n", *(ap + 4));

	/* Exercise 4 — sizeof */
	printf("sizeof uint8_t:  %zu\n", sizeof(uint8_t));
	printf("sizeof uint16_t: %zu\n", sizeof(uint16_t));
	printf("sizeof uint32_t: %zu\n", sizeof(uint32_t));
	printf("sizeof pointer:  %zu\n", sizeof(uint32_t *));

	return 0;
}

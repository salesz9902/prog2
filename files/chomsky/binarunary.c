#include <stdio.h>

int main()
{
    int szam = 0;
    
	printf("Kérlek adj megy egy decimális számot: ");
    scanf("%d", &szam);

	for (int i = 0; i < szam; i++)
    printf((i % 5) ? "|" : " |");
    printf("\n");

	return 0;
}
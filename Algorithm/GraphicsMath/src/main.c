#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GraphicsMath.h"

int main(void)
{
	GraphicsMath_Point M = GraphicsMath_Point_Init(4, 4);
	GraphicsMath_Point O = GraphicsMath_Point_Init(0, 0);

	printf("L'angle est : %f\n", GraphicsMath_Point_Angle(&O, &M));

	return EXIT_SUCCESS;
}
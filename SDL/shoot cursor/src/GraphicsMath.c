#include <stdio.h>
#include <math.h>
#include "GraphicsMath.h"

#define SIZE_ALLOCATION 256

/**************************************************************************/

// Fonction outils 

/*
*	\author Biczo Samuel 
*	@param l'angle en radian 
*	@return l'angle en degrée 
*/
float GraphicsMath_RadToDegree(const float rad)
{
	return (rad * GraphicsMath_PI_TO_DEGREE) / GraphicsMath_PI;
}
/*
*	\author Biczo Samuel 
*	@param l'angle en degrée 
*	@return l'angle en radian
*/
float GraphicsMath_DegreeToRad(const float degree)
{
	return (degree * GraphicsMath_PI) / GraphicsMath_PI_TO_DEGREE;
}
/*
*	\author Biczo Samuel
*	@param le factoriel que l'on veut calculer 
*	@return le factoriel
*/
unsigned int GraphicsMath_Factorial(const unsigned int n)
{
	unsigned int i = 0;
	unsigned int fact = 1;
	for(i = 1; i <= 4; i++)
	{
		fact *= i;
	}
	return fact;
}

/**************************************************************************/

/*
* \author Biczo Samuel 
* @param les coordonées en x et y
* @return un vecteur 2D  
*/
GraphicsMath_Vector2D GraphicsMath_Vector2D_Init(const float x, const float y)
{
	GraphicsMath_Vector2D vector2D = {vector2D.x = x, vector2D.y = y};
	return vector2D;
}

/*
* \author Biczo Samuel 
* @param les coordonnées en x, y et z 
* @return un vecteur 3D 
*/
GraphicsMath_Vector3D GraphicsMath_Vector3D_Init(const float x, const float y, const float z)
{
	GraphicsMath_Vector3D vector3D = {vector3D.x = x, vector3D.y = y, vector3D.z = z};
	return vector3D;
}

/*
* \author Samuel Biczo 
* @param une pointeur de vecteur 3D 
* @return la racine carré de la somme des coordonnées au caré élevé au carré 
*/
float GraphicsMath_Vector2D_Distance(const GraphicsMath_Vector2D* vector2D)
{
	return sqrt((vector2D->x * vector2D->x) + (vector2D->y * vector2D->y));
}

/*
* \author Samuel Biczo
* @param une pointeur de vecteur 3D 
* @return la racine carré de la somme des coordonnées au caré élevé au carré 
*/
float GraphicsMath_Vector3D_Distance(const GraphicsMath_Vector3D* vector3D)
{
	return sqrt((vector3D->x*vector3D->x) + (vector3D->y*vector3D->y) + (vector3D->z*vector3D->z));
}

/*
* \author Samuel Biczo 
* @param un pointeur sur un vecteur 2D et un pointeur sur un vector 2D
* @return un vecteur 2D
*/
GraphicsMath_Vector2D GraphicsMath_Vector2D_Sum(const GraphicsMath_Vector2D* vector2D_A, const GraphicsMath_Vector2D* vector2D_B)
{
	GraphicsMath_Vector2D vector;

	vector.x = vector2D_A->x + vector2D_B->x;
	vector.y = vector2D_A->y + vector2D_B->y;
	return vector;
}
/*
* \author Samuel Biczo 
* @param un pointeur sur un vecteur 3D et un pointeur sur un vector 3D
* @return un vecteur 3D
*/
GraphicsMath_Vector3D GraphicsMath_Vector3D_Sum(const GraphicsMath_Vector3D* vector3D_A, const GraphicsMath_Vector3D* vector3D_B)
{
	GraphicsMath_Vector3D vector;

	vector.x = vector3D_A->x + vector3D_B->x;
	vector.y = vector3D_A->y + vector3D_B->y;
 	vector.z = vector3D_A->z + vector3D_B->z;
	return vector;
}
/*
* \author Samuel Biczo 
* @param un pointeur sur un vecteur 3D et un pointeur sur un vector 3D
* @return un vecteur 3D
*/
GraphicsMath_Vector2D GraphicsMath_Vector2D_Substraction(const GraphicsMath_Vector2D* vector2D_A, const GraphicsMath_Vector2D* vector2D_B)
{
	GraphicsMath_Vector2D vector;

	vector.x = vector2D_A->x - vector2D_B->x;
	vector.y = vector2D_A->y - vector2D_B->y;
	return vector;
}
/*
* \author Samuel Biczo 
* @param un pointeur sur un vecteur 3D et un pointeur sur un vector 3D
* @return un vecteur 3D
*/
GraphicsMath_Vector3D GraphicsMath_Vector3D_Substraction(const GraphicsMath_Vector3D* vector3D_A, const GraphicsMath_Vector3D* vector3D_B)
{
	GraphicsMath_Vector3D vector;

	vector.x = vector3D_A->x - vector3D_B->x;
	vector.y = vector3D_A->y - vector3D_B->y;
	vector.z = vector3D_A->z - vector3D_B->z;
	return vector;
}

/*
* \author Samuel Biczo 
* @param un pointeur sur un vecteur 2D et un pointeur sur un vector 2D
* @return un vecteur 2D
*/
GraphicsMath_Vector2D GraphicsMath_Vector2D_Scalar(const GraphicsMath_Vector2D* vector2D_A, const GraphicsMath_Vector2D* vector2D_B)
{
	GraphicsMath_Vector2D vector;

	vector.x = vector2D_A->x * vector2D_B->x;
	vector.y = vector2D_A->y * vector2D_B->y;
 
	return vector;
}

/*
* \author Samuel Biczo 
* @param un pointeur sur un vecteur 3D et un pointeur sur un vector 3D
* @return un vecteur 3D
*/
GraphicsMath_Vector3D GraphicsMath_Vector3D_Scalar(const GraphicsMath_Vector3D* vector3D_A, const GraphicsMath_Vector3D* vector3D_B)
{
	GraphicsMath_Vector3D vector;

	vector.x = vector3D_A->x * vector3D_B->x;
	vector.y = vector3D_A->y * vector3D_B->y;
	vector.z = vector3D_A->z * vector3D_B->z;

	return vector;
}

/**************************************************************************************************************************************/
/*
* \author Biczo Samuel 
* @param les coordonées le nombre réel et l'imaginaire 
* @return un nombre complexe 
*/
GraphicsMath_Complex GraphicsMath_Complex_Init(const float real, const float imaginary)
{
	GraphicsMath_Complex complex = {complex.a = real, complex.b = imaginary};
	return complex;
}
/*
* \author Biczo Samuel 
* @param un nombre complexe 
* @return le conjuguée du nombre complexe (a+ib) <=> (a-ib) et inveserment 
*/
GraphicsMath_Complex GraphicsMath_Complex_Conjugate(const GraphicsMath_Complex* complex)
{
	GraphicsMath_Complex conjugate;
	conjugate.a = complex->a;
	conjugate.b = -complex->b;
	return conjugate;
}

GraphicsMath_Complex GraphicsMath_Complex_Sum(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B)
{
	GraphicsMath_Complex complex;

	complex.a = complex_A->a + complex_B->a;
	complex.b = complex_A->b + complex_B->b;
	return complex;
}

GraphicsMath_Complex GraphicsMath_Complex_Substraction(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B)
{
	GraphicsMath_Complex complex;

	complex.a = complex_A->a - complex_B->a;
	complex.b = complex_A->b - complex_B->b;

	return complex;
}

GraphicsMath_Complex GraphicsMath_Complex_Product(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B)
{
	GraphicsMath_Complex complex;

	complex.a = (complex_A->a * complex_B->a) + (complex_A->b * complex_B->b * GraphicsMath_ISquare);
	complex.b = (complex_A->a * complex_B->b) + (complex_A->b * complex_B->a);

	return complex;
}

GraphicsMath_Complex GraphicsMath_Complex_Quotient(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B)
{
	GraphicsMath_Complex complex;

	GraphicsMath_Complex conjugate = GraphicsMath_Complex_Conjugate(complex_B);
	GraphicsMath_Complex numerator = GraphicsMath_Complex_Product(complex_A, &conjugate);
	const float denominator = (complex_B->a * complex_B->a) + (complex_B->b * complex_B->b);

 
	complex.a = numerator.a / denominator;
	complex.b = numerator.b /  denominator;

	return complex;
}

float GraphicsMath_Complex_Modulus(const GraphicsMath_Complex* complex)
{
	float modulus_complex = sqrt((complex->a * complex->a) + (complex->b * complex->b));
	return modulus_complex;
}

float GraphicsMath_Complex_Argument(const GraphicsMath_Complex* complex)
{
	float modulus = GraphicsMath_Complex_Modulus(complex);
	float argument = 0.0;
 

 	if(complex->a >= 0 && complex->b >= 0)
 	{
 		argument = acos(complex->a / modulus);
 	}
 	else if(complex->a >= 0 && complex->b < 0)
 	{
 		argument = -acosh(complex->a / modulus);
 	}
 	else if(complex < 0 && complex->b >= 0)
 	{
 		argument = acosh(complex->a / modulus);
 	}
 	else 
 	{
 		argument = -acosh(complex->a / modulus);
 	}
 	return argument;
}
/*
Pour la traduction des mots mathématique anglais vers le francais 
	https://www.lyceedadultes.fr/sitepedagogique/documents/math/autres_documents/cours_traduction_anglais_termes_mathematiques.pdf
*/

#ifndef __GraphicsMath__H__ 
#define __GraphicsMath__H__

#define GraphicsMath_ISquare -1
#define GraphicsMath_PI (22.0/7.0)
#define GraphicsMath_PI_TO_DEGREE 180

/*********************************************/

/*
	Fonction généraliste de conversion, de calcul 
*/

float GraphicsMath_RadToDegree(const float rad);
float GraphicsMath_DegreeToRad(const float degree);

unsigned int GraphicsMath_Factorial(const unsigned int n);

/*************************************/

/*
	Vecteur 2D défini par un le systeme de coordonées (x, y)
	Vecteur 3D défini par un le systeme de coordonnées (x, y, z)
*/

typedef struct GraphicsMath_Vector2D
{
	float x;
	float y;
}GraphicsMath_Vector2D;

typedef struct GraphicsMath_Vector3D 
{
	float x;
	float y;
	float z;
}GraphicsMath_Vector3D;

GraphicsMath_Vector2D GraphicsMath_Vector2D_Init(const float x, const float y);
GraphicsMath_Vector3D GraphicsMath_Vector3D_Init(const float x, const float y, const float z);

float GraphicsMath_Vector2D_Distance(const GraphicsMath_Vector2D* vector2D);
float GraphicsMath_Vector3D_Distance(const GraphicsMath_Vector3D* vector3D);

GraphicsMath_Vector2D GraphicsMath_Vector2D_Sum(const GraphicsMath_Vector2D* vector2D_A, const GraphicsMath_Vector2D* vector2D_B);
GraphicsMath_Vector3D GraphicsMath_Vector3D_Sum(const GraphicsMath_Vector3D* vector3D_A, const GraphicsMath_Vector3D* vector3D_B);

GraphicsMath_Vector2D GraphicsMath_Vector2D_Substraction(const GraphicsMath_Vector2D* vector2D_A, const GraphicsMath_Vector2D* vector2D_B);
GraphicsMath_Vector3D GraphicsMath_Vector3D_Substraction(const GraphicsMath_Vector3D* vector3D_A, const GraphicsMath_Vector3D* vector3D_B);

float GraphicsMath_Vector2D_Scalar(const GraphicsMath_Vector2D* vector2D_A, const GraphicsMath_Vector2D* vector2D_B);
float GraphicsMath_Vector3D_Scalar(const GraphicsMath_Vector3D* vector3D_A, const GraphicsMath_Vector3D* vector3D_B);


/*************************************/

/*
	Nombre complexe défini par un réel et un imaginaire 
*/

 

typedef struct GraphicsMath_Complex 
{
	float a;  // le réel 
	float b; // l'imaginaire 
}GraphicsMath_Complex;

GraphicsMath_Complex GraphicsMath_Complex_Init(const float real, const float imaginary);
GraphicsMath_Complex GraphicsMath_Complex_Conjugate(const GraphicsMath_Complex* complex);
GraphicsMath_Complex GraphicsMath_Complex_Sum(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B);
GraphicsMath_Complex GraphicsMath_Complex_Substraction(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B);
GraphicsMath_Complex GraphicsMath_Complex_Product(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B);
GraphicsMath_Complex GraphicsMath_Complex_Quotient(const GraphicsMath_Complex* complex_A, const GraphicsMath_Complex* complex_B);
float GraphicsMath_Complex_Modulus(const GraphicsMath_Complex* complex);
float GraphicsMath_Complex_Argument(const GraphicsMath_Complex* complex);

/***********************************************************/

typedef struct GraphicsMath_Linear
{
	float a;
	float b;
}GraphicsMath_Linear;

GraphicsMath_Linear GraphicsMath_Linear_Init(const float x, const float y);
float GraphicsMath_Linear_Image(const GraphicsMath_Linear* linear, const float x);
float counterimage_Linear_InverseImage(const GraphicsMath_Linear* linear, const float y);

/***********************************************************/

typedef struct GraphicsMath_Point 
{
	float x;
	float y;
}GraphicsMath_Point;

GraphicsMath_Point GraphicsMath_Point_Init(const float x, const float y);
float GraphicsMath_Point_Angle(const GraphicsMath_Point* reference, const GraphicsMath_Point* point);


#endif
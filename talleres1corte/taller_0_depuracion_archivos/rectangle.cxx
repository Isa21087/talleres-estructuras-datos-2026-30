#include "rectangle.h"
#include <math.h>

float perimeterRect ( Rectangle rect ) {
	
	float perim = 0.0;
	perim = 2.0 * (rect.width + rect.height);
	return perim;
}

float areaRect ( Rectangle rect ) {

	float area = 0.0;
	area = rect.width * rect.height;
	return area;
}

float distOriginRect ( Rectangle rect ) {

    float dist = 0.0;
    dist = sqrt( rect.posX * rect.posX + rect.posY * rect.posY ); // las coordenadas solamente se utilizan para calcular la distancia al origen o sea si pongo 2 y 3 entonces se clacula la distancia desde 0,0 hasta 2,3 
    return dist;
}
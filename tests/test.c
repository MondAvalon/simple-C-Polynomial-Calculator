#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../source/Node.h"

int main() {
    // Test parsePolynomial
    char input1[] = "-3x^2-2x-5";
    Node *poly1 = parsePolynomial(input1);
    printf("Parsed Polynomial 1: ");
    displayPolynomial(poly1, 'm');

    char input2[] = "-4x^3+3x^2-2x+1";
    Node *poly2 = parsePolynomial(input2);
    printf("Parsed Polynomial 2: ");
    displayPolynomial(poly2, 'm');

    // Test addPolynomials
    Node *sum = addPolynomials(poly1, poly2);
    printf("Sum of Polynomials: ");
    displayPolynomial(sum, 'm');

    // Test substractPolynomials
    Node *diff = substractPolynomials(poly1, poly2);
    printf("Difference of Polynomials: ");
    displayPolynomial(diff, 'm');

    // Test derivativePolynomial
    Node *derivative = derivativePolynomial(poly1);
    printf("Derivative of Polynomial 1: ");
    displayPolynomial(derivative, 'm');

    // Test multiplyPolynomials
    Node *product = multiplyPolynomials(poly1, poly2);
    printf("Product of Polynomials: ");
    displayPolynomial(product, 'm');

    // Free allocated memory (assuming you have a function to free the polynomial
    // linked list)
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sum);
    freePolynomial(diff);
    freePolynomial(derivative);
    freePolynomial(product);

    return 0;
}
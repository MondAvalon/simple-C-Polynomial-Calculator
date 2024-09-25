#ifndef CPOLYNOMIALCALCULATOR_NODE_H
#define CPOLYNOMIALCALCULATOR_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define OVERFLOW 1
#define OK 0
#define ERROR -1

typedef int Status;

// 多项式单链表结点
typedef struct Node {
  double coef;
  int exp;
  struct Node *next;
} Node;

typedef struct {
  double coef;
  int exp;
} Token;

Node *createNode(double coef, int exp);

Node *insertNode(Node *head, double coef, int exp);

void displayPolynomialMath(Node *head);

void displayPolynomialSequence(Node *head);

void displayPolynomial(Node *head, char format);

void freePolynomial(Node *head);

Status tokenize(char *input, Token *token);

Node *parsePolynomial(char *input);

Node *addPolynomials(Node *poly1, Node *poly2);

Node *substractPolynomials(Node *poly1, Node *poly2);

Node *derivativePolynomial(Node *poly);

Node *multiplyPolynomials(Node *poly1, Node *poly2);

#endif //CPOLYNOMIALCALCULATOR_NODE_H

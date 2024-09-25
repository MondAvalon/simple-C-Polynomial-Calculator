#include "Node.h"

// 新建一个结点
Node *createNode(double coef, int exp) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 在多项式的链表中按降幂插入一个新的节点
Node *insertNode(Node *head, double coef, int exp) {
    if (coef == 0) return head;
    Node *temp = head;
    while (temp->next && temp->next->exp > exp) temp = temp->next;
    // 如果指数相同则合并系数
    if (temp->next && temp->next->exp == exp) {
        temp->next->coef += coef;
        // 如果系数为0则删除该结点
        if (temp->next->coef == 0) {
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
        }
    } else {// 否则插入新结点
        Node *newNode = createNode(coef, exp);
        newNode->next = temp->next;
        temp->next = newNode;
    }
    return head;
}

// 打印多项式，格式为数学表达式
void displayPolynomialMath(Node *head) {
    if (head->next == NULL) {
        printf("0\n");
        return;
    }
    Node *temp = head->next;
    while (temp) {
        if (temp->exp == 0) {
            printf("%g", temp->coef);
        } else if (temp->exp == 1) {
            if (temp->coef == 1) {
                printf("x");
            } else if (temp->coef == -1) {
                printf("-x");
            } else {
                printf("%gx", temp->coef);
            }
        } else {
            if (temp->coef == 1) {
                printf("x^%d", temp->exp);
            } else if (temp->coef == -1) {
                printf("-x^%d", temp->exp);
            } else {
                printf("%gx^%d", temp->coef, temp->exp);
            }
        }
        if (temp->next && temp->next->coef > 0) printf("+");
        temp = temp->next;
    }
    printf("\n");
}

// 打印多项式，格式为系数指数序列
void displayPolynomialSequence(Node *head) {
    Node *temp = head->next;
    int length = 0;
    while (temp) {
        length++;
        temp = temp->next;
    }
    printf("%d ", length);
    temp = head->next;
    for (int i = 0; i < length; i++) {
        printf("%g %d ", temp->coef, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}

void displayPolynomial(Node *head, char format) {
    if (format == 'm') {
        displayPolynomialMath(head);
    } else if (format == 's') {
        displayPolynomialSequence(head);
    }
}

void freePolynomial(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 从字符串解析多项式，将多项式字符串分割成一项一项的字符串,注意系数和指数有都负数的情况,例如
// 6x^-3-x分割为6x^-3和-x
Status tokenize(char *input, Token *token) {
    static char *this;
    static size_t length;
    if (input != NULL) {
        this = input;
        length = strlen(input);
    }
    int sign = 1;

    if (this[0] == '-') {
        // 处理负号
        sign = -1;
        this++;
    } else if (this[0] == '+') {
        // 处理正号
        sign = 1;
        this++;
    }

    if (this[0] == 'x') {
        // 系数绝对值省略为1
        token->coef = sign;
        this++;
        if (this[0] == '^') token->exp = strtol(this + 1, &this, 10);// 有指数
        else token->exp = 1;// 无指数
    } else {
        // 有系数
        token->coef = sign * strtod(this, &this);
        if (this[0] == 'x') {
            // 含有x
            this++;
            if (this[0] == '^') token->exp = strtol(this + 1, &this, 10);// 有指数
            else token->exp = 1;// 没有指数
        } else
            // 不含x（常数项）
            token->exp = 0;
    }
    if (this[0] == '\0' || this[0] == ' ' || this[0] == '\n')
        return EOF;
    return OK;
}

// 从字符串解析多项式，并记录参数的正负插入链表
Node *parsePolynomial(char *input) {
    Node *poly = createNode(0, 0);  // 创建头节点
    Token token;
    int status = tokenize(input, &token);
    poly = insertNode(poly, token.coef, token.exp);

    while (status != EOF) {
        status = tokenize(NULL, &token);
        poly = insertNode(poly, token.coef, token.exp);
    }
    return poly;
}


//Node *parsePolynomial(char *input) {
//    Node *poly = createNode(0, 0);  // 创建头节点
//    char copy[strlen(input) + 1];
//    char *pInput = input;  // 指向input的指针,用于确定分隔符是+还是-
//    strcpy(copy, input);   // 复制字符串到copy
//    char *token = strtok(copy, "+-");  // 分割字符串copy
//    pInput = input + (token - copy) - 1;
//
//    double coef;   // 系数
//    int exp;       // 指数
//    int sign = 1;  // 符号
//
//    while (token != NULL) {
//        // 判断符号
//        if (token != &copy[0] && (*pInput == '-')) {
//            sign = -1;
//        } else {
//            sign = 1;
//        }
//        char *signX = strchr(token, 'x');
//
//        // 判断字符串是否有指数，有指数则按指数插入，否则按常数插入
//        if (sscanf(token, "%lfx^%d", &coef, &exp) == 2) {
//            poly = insertNode(poly, sign * coef, exp);  // 处理像 "3x^2" 的项
//        } else if (sscanf(token, "x^%d", &exp) == 1) {
//            poly = insertNode(poly, sign, exp);  // 处理像 "x^2" 的项，系数为1
//        } else if (sscanf(token, "%lfx", &coef) == 1 && signX != NULL) {
//            poly = insertNode(poly, sign * coef, 1);  // 处理像 "2x" 的项，指数为 1
//        } else if (strcmp(token, "x") == 0) {
//            poly = insertNode(poly, sign, 1);  // 处理像 "x" 的项，系数为1，指数为1
//        } else if (sscanf(token, "%lf", &coef) == 1) {
//            poly = insertNode(poly, sign * coef, 0);  // 处理常数项，比如 "1"
//        }
//
//        token = strtok(NULL, "+-"); // 继续分割
//        if (token != NULL) pInput = input + (token - copy) - 1;  // 更新pInput的位置
//    }
//    return poly;
//}

//int calculatePolynomial(char *input) {}

// 多项式加法
Node *addPolynomials(Node *poly1, Node *poly2) {
    Node *result = createNode(0, 0);  // 创建头节点
    Node *temp1 = poly1->next;
    Node *temp2 = poly2->next;
    while (temp1 && temp2) {
        if (temp1->exp > temp2->exp) {
            result = insertNode(result, temp1->coef, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            result = insertNode(result, temp2->coef, temp2->exp);
            temp2 = temp2->next;
        } else {
            double sum = temp1->coef + temp2->coef;
            if (sum != 0) result = insertNode(result, sum, temp1->exp);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    while (temp1) {
        result = insertNode(result, temp1->coef, temp1->exp);
        temp1 = temp1->next;
    }
    while (temp2) {
        result = insertNode(result, temp2->coef, temp2->exp);
        temp2 = temp2->next;
    }
    return result;
}

// 多项式减法
Node *substractPolynomials(Node *poly1, Node *poly2) {
    Node *result = createNode(0, 0);  // 创建头节点
    Node *temp1 = poly1->next;
    Node *temp2 = poly2->next;
    while (temp1 && temp2) {
        if (temp1->exp > temp2->exp) {
            result = insertNode(result, temp1->coef, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            result = insertNode(result, -temp2->coef, temp2->exp);
            temp2 = temp2->next;
        } else {
            double diff = temp1->coef - temp2->coef;
            if (diff != 0) result = insertNode(result, diff, temp1->exp);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    while (temp1) {
        result = insertNode(result, temp1->coef, temp1->exp);
        temp1 = temp1->next;
    }
    while (temp2) {
        result = insertNode(result, -temp2->coef, temp2->exp);
        temp2 = temp2->next;
    }
    return result;
}

// 多项式求导
Node *derivativePolynomial(Node *poly) {
    Node *result = createNode(0, 0);  // 创建头节点
    Node *temp = poly->next;
    while (temp) {
        if (temp->exp != 0) {
            result = insertNode(result, temp->coef * temp->exp, temp->exp - 1);
        }
        temp = temp->next;
    }
    return result;
}

// 多项式乘法
Node *multiplyPolynomials(Node *poly1, Node *poly2) {
    Node *result = createNode(0, 0);  // 创建头节点
    Node *temp1 = poly1->next;
    Node *temp2 = poly2->next;
    while (temp1) {
        temp2 = poly2->next;
        while (temp2) {
            double coef = temp1->coef * temp2->coef;
            int exp = temp1->exp + temp2->exp;
            result = insertNode(result, coef, exp);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return result;
}
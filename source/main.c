#include "Node.h"

// 输入四个个参数，第一个参数是输出格式，第二个参数是操作符，第三个参数是第一个多项式，第四个参数是第二个多项式
int main() {
    char output_format, operator;
    char raw_poly_1[100], raw_poly_2[100] = "";

    // 从标准输入中获取数据
    scanf("%c ", &output_format);
    if (output_format != 'm' && output_format != 's') {
        printf("输出格式错误\n");
        return ERROR;
    }
    scanf("%c ", &operator);
    scanf("%s", raw_poly_1);

    // 只有当操作符不是求导时才读取第二个多项式
    if (operator != 'd') {
        scanf("%s", raw_poly_2);
    }

    Node *result = NULL;
    Node *poly1 = parsePolynomial(raw_poly_1);

    // 根据操作符进行不同的操作
    if (operator == 'd') {
        result = derivativePolynomial(poly1);
    } else {
        Node *poly2 = parsePolynomial(raw_poly_2);
        switch (operator) {
            case '+':result = addPolynomials(poly1, poly2);
                break;
            case '-':result = substractPolynomials(poly1, poly2);
                break;
            case '*':result = multiplyPolynomials(poly1, poly2);
                break;
            default:printf("操作符错误\n");
                return 1;
        }
        freePolynomial(poly2);
    }

    if (result != NULL)
        displayPolynomial(result, output_format);
    else
        printf("结果为空\n");
    freePolynomial(poly1);
    freePolynomial(result);
    return 0;
}

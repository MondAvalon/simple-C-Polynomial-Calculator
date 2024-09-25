#include "Node.h"

// �����ĸ�����������һ�������������ʽ���ڶ��������ǲ������������������ǵ�һ������ʽ�����ĸ������ǵڶ�������ʽ
int main() {
    char output_format, operator;
    char raw_poly_1[100], raw_poly_2[100] = "";

    // �ӱ�׼�����л�ȡ����
    scanf("%c ", &output_format);
    if (output_format != 'm' && output_format != 's') {
        printf("�����ʽ����\n");
        return ERROR;
    }
    scanf("%c ", &operator);
    scanf("%s", raw_poly_1);

    // ֻ�е�������������ʱ�Ŷ�ȡ�ڶ�������ʽ
    if (operator != 'd') {
        scanf("%s", raw_poly_2);
    }

    Node *result = NULL;
    Node *poly1 = parsePolynomial(raw_poly_1);

    // ���ݲ��������в�ͬ�Ĳ���
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
            default:printf("����������\n");
                return 1;
        }
        freePolynomial(poly2);
    }

    if (result != NULL)
        displayPolynomial(result, output_format);
    else
        printf("���Ϊ��\n");
    freePolynomial(poly1);
    freePolynomial(result);
    return 0;
}

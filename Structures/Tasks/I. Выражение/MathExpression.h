#include <string>

using namespace std;

class TempConst;
class TempSum;
class TempProduct;

class TempConst : public Expression {
private:
    int res;

public:
    TempConst(int num) : res(num) {}

    int Evaluate() const override { return res; };
    string ToString() const override { return to_string(res); };
};

class TempSum : public Expression {
private:
    int res;
    string text;

public:
    TempSum(ExpressionPtr first, ExpressionPtr second) {
        res = first->Evaluate() + second->Evaluate();
        text = first->ToString() + " + " + second->ToString();
    }

    int Evaluate() const override { return res; }
    string ToString() const override { return text; }
};

class TempProduct : public Expression {
private:
    int res;
    string text;

public:
    TempProduct(ExpressionPtr first, ExpressionPtr second) {
        res = first->Evaluate() * second->Evaluate();
        if (typeid(*first.get()) == typeid(TempSum)) {
            text += "(" + first->ToString() + ") * ";
        } else {
            text += first->ToString() + " * ";
        }
        if (typeid(*second.get()) == typeid(TempSum)) {
            text += "(" + second->ToString() + ")";
        } else {
            text += second->ToString();
        }
    }

    int Evaluate() const override { return res; }
    string ToString() const override { return text; }
};

ExpressionPtr Const(int num) {
    ExpressionPtr temp(new TempConst(num));
    return temp;
}

ExpressionPtr Sum(ExpressionPtr first, ExpressionPtr second) {
    ExpressionPtr temp(new TempSum(first, second));
    return temp;
}

ExpressionPtr Product(ExpressionPtr first, ExpressionPtr second) {
    ExpressionPtr temp(new TempProduct(first, second));
    return temp;
}

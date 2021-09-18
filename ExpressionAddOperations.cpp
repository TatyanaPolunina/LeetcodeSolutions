#include <vector>
#include <string>
#include <strstream>
#include <iostream>
#include <numeric>


using namespace std;

enum class Operation {
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    NO_OPERATION = 'n'
};

const double maxNumber = numeric_limits<int>::max() / 10.0;

struct Expression
{
    string expr_result;
    bool isLastPlus;
    vector<int> multiplies;
    int previous = 0;
};

template <Operation operation>
bool getNextExpression(const Expression& expression, int num, Expression& newExpression) {
    newExpression = Expression();
    newExpression.expr_result = expression.expr_result + static_cast<char>(operation) + to_string(num);
    long long mul = expression.multiplies.size() == 1?expression.multiplies.front():std::accumulate(expression.multiplies.begin(),expression.multiplies.end(), 1, std::multiplies<long long>());
    if (mul != static_cast<int>(mul)) {
        return false;
    }
    long long value = 0;
    if (expression.isLastPlus) {
        value = expression.previous + mul;
    } else {
        value = expression.previous - mul;
    }
    if (value != static_cast<int>(value)) return false;
    newExpression.previous = value;
    newExpression.isLastPlus = operation == Operation::PLUS;
    newExpression.multiplies.push_back(num);
    return true;
}

template<>
bool getNextExpression<Operation::MULTIPLY>(const Expression& expression, int num, Expression& newExpression) {
    newExpression = expression;
    newExpression.expr_result += static_cast<char>(Operation::MULTIPLY) + to_string(num);
    newExpression.multiplies.push_back(num);
    return true;
}

template<>
bool getNextExpression<Operation::NO_OPERATION>(const Expression& expression, int num, Expression& newExpression) {

    if (expression.multiplies.empty() || expression.multiplies.back() == 0 ||          expression.multiplies.back() > maxNumber) {
        return false;
    }
    newExpression = expression;
    newExpression.expr_result += to_string(num);
    newExpression.multiplies.back() = static_cast<int>(static_cast<long long>(newExpression.multiplies.back()) * 10 + num);
    return true;
}

class Solution {

    string numbers;

    void addNextExpression(const Expression& expression, string::iterator number, int target, std::vector<string>& result) {
        if (number == numbers.end()) {
            int exprResult = expression.previous;
            long long val = std::accumulate(expression.multiplies.begin(),expression.multiplies.end(), 1, std::multiplies<long long>());
            if (val != static_cast<int>(val)) {
                return;
            }
            if (expression.isLastPlus) {
                exprResult += static_cast<int>(val);
            } else {
                exprResult -= static_cast<int>(val);
            }
            if (exprResult == target) {
                result.push_back(expression.expr_result);
            }
            return;
        }
        int value = static_cast<int>(*number - '0');
        Expression newExpression;
        if (getNextExpression<Operation::PLUS>(expression, value, newExpression))
             addNextExpression(newExpression, number + 1, target, result);
        if (getNextExpression<Operation::MINUS>(expression, value, newExpression))
            addNextExpression(newExpression, number + 1, target, result);
        if (getNextExpression<Operation::MULTIPLY>(expression, value, newExpression))
            addNextExpression(newExpression, number + 1, target, result);
        if (getNextExpression<Operation::NO_OPERATION>(expression, value, newExpression))
            addNextExpression(newExpression, number + 1, target, result);
        
    }
    
public:
    vector<string> addOperators(string num, int target) {
        if (num.empty() ) {
            return {};
        }
        vector<string> result;
        numbers = move(num);
        Expression initialExpression = {string(1, numbers[0]),true, {numbers[0]  - '0'}, 0};
        addNextExpression(initialExpression, numbers.begin() + 1, target, result);
        return result; 
    }
};

int main()
{
    Solution s;
    std::vector<string> result = s.addOperators("123", 6);
    cout << "test" << endl;
    for (auto& str: result) {
        cout << str << endl;
    }
}
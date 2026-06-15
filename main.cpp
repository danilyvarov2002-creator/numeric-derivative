#include <iostream>
#include <cmath>
#include <functional>
#include <limits>

using namespace std;

using Function = function<double(double)>;

double derivativeForward(const Function& f, double x, double h) {
    return (f(x + h) - f(x)) / h;
}

double derivativeBackward(const Function& f, double x, double h) {
    return (f(x) - f(x - h)) / h;
}

double derivativeCentral(const Function& f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

void printError(double exactValue, double approxValue) {
    double absoluteError = fabs(exactValue - approxValue);
    double relativeError = fabs(absoluteError / exactValue) * 100.0;
    
    cout << "    Abs error: " << absoluteError << endl;
    cout << "    Rel error: " << relativeError << " %" << endl;
}

void demonstrate() {
    cout << "=== Demo: f(x) = x^2 ===" << endl;
    cout << "Exact derivative: f'(x) = 2x" << endl << endl;
    
    auto f = [](double x) { return x * x; };
    
    double x = 2.0;
    double h = 0.001;
    double exactDerivative = 2.0 * x;
    
    cout << "x = " << x << ", h = " << h << endl;
    cout << "Exact value: " << exactDerivative << endl << endl;
    
    double d1 = derivativeForward(f, x, h);
    cout << "Method 1 (forward): " << d1 << endl;
    printError(exactDerivative, d1);
    
    double d2 = derivativeBackward(f, x, h);
    cout << "Method 2 (backward): " << d2 << endl;
    printError(exactDerivative, d2);
    
    double d3 = derivativeCentral(f, x, h);
    cout << "Method 3 (central): " << d3 << endl;
    printError(exactDerivative, d3);
}

void interactiveMode() {
    cout << "\n=== Interactive Mode ===" << endl;
    cout << "Available functions:" << endl;
    cout << "  1. f(x) = x^2        (derivative: 2x)" << endl;
    cout << "  2. f(x) = sin(x)     (derivative: cos(x))" << endl;
    cout << "  3. f(x) = exp(x)     (derivative: exp(x))" << endl;
    cout << "  4. f(x) = ln(x)      (derivative: 1/x, x > 0)" << endl;
    
    int choice;
    cout << "\nSelect function (1-4): ";
    cin >> choice;
    
    Function f;
    function<double(double)> exact;
    
    switch(choice) {
        case 1:
            f = [](double x) { return x * x; };
            exact = [](double x) { return 2.0 * x; };
            cout << "Selected: f(x) = x^2" << endl;
            break;
        case 2:
            f = [](double x) { return sin(x); };
            exact = [](double x) { return cos(x); };
            cout << "Selected: f(x) = sin(x)" << endl;
            break;
        case 3:
            f = [](double x) { return exp(x); };
            exact = [](double x) { return exp(x); };
            cout << "Selected: f(x) = exp(x)" << endl;
            break;
        case 4:
            f = [](double x) { return log(x); };
            exact = [](double x) { return 1.0 / x; };
            cout << "Selected: f(x) = ln(x)" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }
    
    double x, h;
    cout << "Enter x: ";
    cin >> x;
    
    if (choice == 4 && x <= 0) {
        cout << "Error: ln(x) defined only for x > 0!" << endl;
        return;
    }
    
    cout << "Enter step h (e.g., 0.001): ";
    cin >> h;
    
    if (h <= 0) {
        cout << "Error: step h must be positive!" << endl;
        return;
    }
    
    double exactValue = exact(x);
    
    cout << "\nResults:" << endl;
    cout << "Exact value: " << exactValue << endl << endl;
    
    double d1 = derivativeForward(f, x, h);
    cout << "Method 1 (forward): " << d1 << endl;
    printError(exactValue, d1);
    
    double d2 = derivativeBackward(f, x, h);
    cout << "Method 2 (backward): " << d2 << endl;
    printError(exactValue, d2);
    
    double d3 = derivativeCentral(f, x, h);
    cout << "Method 3 (central): " << d3 << endl;
    printError(exactValue, d3);
}

int main() {
    system("chcp 65001 > nul");
    
    cout << "===== Numerical Differentiation =====" << endl;
    cout << "Computing the first derivative of a function at a point" << endl;
    cout << "========================================" << endl << endl;
    
    demonstrate();
    
    char again;
    cout << "\nTry another function? (y/n): ";
    cin >> again;
    
    if (again == 'y' || again == 'Y') {
        interactiveMode();
    }
    
    cout << "\nProgram finished." << endl;
    return 0;
}
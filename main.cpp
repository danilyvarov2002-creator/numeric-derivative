#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

using namespace std;

using Function = function<double(double)>;

double derivativeForward(const Function& f, double x, double h)
{
    return (f(x + h) - f(x)) / h;
}

double derivativeBackward(const Function& f, double x, double h)
{
    return (f(x) - f(x - h)) / h;
}

double derivativeCentral(const Function& f, double x, double h)
{
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

void printResult(const string& methodName,
                 double approxValue,
                 double exactValue)
{
    const double absoluteError = fabs(approxValue - exactValue);

    cout << "\n" << methodName << '\n';
    cout << "Approximate derivative: " << approxValue << '\n';
    cout << "Absolute error: " << absoluteError << '\n';

    if (fabs(exactValue) > 1e-12)
    {
        const double relativeError =
            absoluteError / fabs(exactValue) * 100.0;

        cout << "Relative error: "
             << relativeError << " %\n";
    }
    else
    {
        cout << "Relative error: undefined (exact value = 0)\n";
    }
}

int main()
{
    system("chcp 65001 > nul");

    cout << fixed << setprecision(10);

    Function f;
    Function exactDerivative;

    int choice;

    cout << "Choose function:\n";
    cout << "1. x^2\n";
    cout << "2. sin(x)\n";
    cout << "3. exp(x)\n";
    cout << "4. ln(x)\n";
    cout << "Your choice: ";

    cin >> choice;

    switch (choice)
    {
        case 1:
            f = [](double x) { return x * x; };
            exactDerivative = [](double x) { return 2 * x; };
            break;

        case 2:
            f = [](double x) { return sin(x); };
            exactDerivative = [](double x) { return cos(x); };
            break;

        case 3:
            f = [](double x) { return exp(x); };
            exactDerivative = [](double x) { return exp(x); };
            break;

        case 4:
            f = [](double x) { return log(x); };
            exactDerivative = [](double x) { return 1.0 / x; };
            break;

        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    double x, h;

    cout << "\nEnter x: ";
    cin >> x;

    cout << "Enter h: ";
    cin >> h;

    if (h <= 0)
    {
        cout << "Step h must be positive!\n";
        return 1;
    }

    if (choice == 4 && x <= 0)
    {
        cout << "For ln(x), x must be > 0!\n";
        return 1;
    }

    const double exactValue = exactDerivative(x);

    printResult(
        "Forward difference method",
        derivativeForward(f, x, h),
        exactValue
    );

    printResult(
        "Backward difference method",
        derivativeBackward(f, x, h),
        exactValue
    );

    printResult(
        "Central difference method",
        derivativeCentral(f, x, h),
        exactValue
    );

    cout << "\nExact derivative: "
         << exactValue << '\n';

    return 0;
}
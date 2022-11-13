#include "Calculator.h"
#include <math.h>

Calculator::Calculator() : result(0.0) 
{
}
Calculator::~Calculator()
{
}

void Calculator::Add(const double x, const double y)
{
	result = x + y;
}

void Calculator::Subtract(const double x, const double y)
{
	result = x - y;
}

void Calculator::Multiply(const double x, const double y)
{
	result = x * y;
}

Calculator::Error Calculator::Divide(const double x, const double y)
{
	Calculator::Error error = Calculator::Error::SUCCESS;

	if (y== 0)
	{
		error = Calculator::Error::DIVISION_BY_ZERO;
	}
	else
	{
		result = x / y;
	}

	return error;
}

double Calculator::GetResult()
{
	return result; 
}

double Calculator::GetResult() const
{
	return 0.0;
}

void Calculator::ResetValue(double x)
{
	x = 0;
}

void Calculator::ResetReferencedValue(double &x)
{
	x = 0;
}

Calculator::Error Calculator::Roots(const double a, const  double b, const  double c, double &x0, double &x1)
{
	Calculator::Error error = Calculator::Error::SUCCESS;
	double delta = (b * b) - (a * 4 * c);

	if (a==0.0||b==0.0||c==0.0) {
		error = Calculator::Error::INVALID_PARAMETER;
		return error;
	}
	else if (delta < 0) {
		error = Calculator::Error::NO_ROOTS;
		return error;
	}
	else if (delta == 0) {
		error = Calculator::Error::SINGLE_ROOT;
		x0 = (-b) / (2 * a);
		return error;
	}
	else {
		x0 = (-b - sqrt(delta)) / (2 * a);
		x1 = (-b + sqrt(delta)) / (2 * a);
		return error;
	}
	
}


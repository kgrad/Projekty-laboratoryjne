#pragma once
class Calculator
{
private:
	double result;

public:

	Calculator();

	~Calculator();

	enum Error
	{
		SUCCESS,
		NO_ROOTS,
		SINGLE_ROOT,
		INVALID_PARAMETER,
		DIVISION_BY_ZERO,
	};
	void Add(const double x, const double y);
	void Subtract(const double x, const double y);
	void Multiply(const double x, const double y);
	Error Divide(const double, const double);
	double GetResult();
	double GetResult() const;
	Error Roots(const double, const double, const double, double&, double&);
	void ResetValue(double);
	void ResetReferencedValue(double&);
};


#ifndef BLACK_SCHOLES_HPP
#define BLACK_SCHOLES_HPP

#include <cmath>
#include <iostream>

class BlackScholes 
{
public:
    BlackScholes(double stockPrice, double strikePrice, double timeToExpiration, double riskFreeRate, double volatility)
        : S(stockPrice), K(strikePrice), T(timeToExpiration), r(riskFreeRate), s(volatility) {}

    double calculateCallPrice() const 
    {
        double d1 = (std::log(S / K) + (r + 0.5 * s * s) * T) / (s * std::sqrt(T));
        double d2 = d1 - s * std::sqrt(T);
        return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
    }

    double calculatePutPrice() const 
    {
        double d1 = (std::log(S / K) + (r + 0.5 * s * s) * T) / (s * std::sqrt(T));
        double d2 = d1 - s * std::sqrt(T);
        return K * std::exp(-r * T) * normalCDF(-d2) - S * normalCDF(-d1);
    }

private:
    double S; // Stock price
    double r; // Risk-free interest rate
    double K; // Strike price
    double T; // Time to expiration
    double s; // Volatility

    double normalCDF(double value) const 
    {
        return 0.5 * std::erfc(-value * M_SQRT1_2);
    }
};

#endif 
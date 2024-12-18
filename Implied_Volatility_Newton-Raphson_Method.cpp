#include <iostream>
#include <cmath>

// Black-Scholes Price and its Vega (sensitivity to volatility)
double blackScholesVega(double S, double K, double r, double T, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return S * sqrt(T) * exp(-0.5 * d1 * d1) / sqrt(2 * M_PI);
}

// Newton-Raphson for Implied Volatility
double impliedVolatility(double marketPrice, double S, double K, double r, double T, bool isCall) {
    double sigma = 0.2, tol = 1e-6;
    for (int i = 0; i < 100; ++i) {
        double price = blackScholesPrice(S, K, r, T, sigma, isCall);
        double vega = blackScholesVega(S, K, r, T, sigma);
        double diff = marketPrice - price;
        if (std::abs(diff) < tol) return sigma;
        sigma += diff / vega;
    }
    return sigma;
}
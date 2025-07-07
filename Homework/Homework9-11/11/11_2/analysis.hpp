#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <iostream>
#include <vector>
#include <functional>
#include "black_scholes.hpp"

namespace Derivative 
{

// 事件类模板，用于管理衍生品价格变化的事件
template<typename... Args>
class PriceEvent {
public:
    using Callback = std::function<void(Args...)>;

    void addListener(const Callback& callback) {
        listeners.push_back(callback);
    }

    void trigger(Args... args) const {
        for (const auto& listener : listeners) {
            listener(args...);
        }
    }

private:
    std::vector<Callback> listeners;
};

// 价格分析类，用于分析衍生品与标的资产的关系
class DerivativeAnalysis 
{
public:
    DerivativeAnalysis(double strikePrice, double riskFreeRate, double volatility)
        : K(strikePrice), r(riskFreeRate), s(volatility) {}

    void analyzePrice(double marketPrice, double underlyingPrice, double timeToExpiration) 
    {
        if (timeToExpiration <= 0) {
            std::cerr << "到期时间必须大于零" << std::endl;
            return;
        }

        BlackScholes bs(underlyingPrice, K, timeToExpiration, r, s);
        double theoreticalPrice = bs.calculateCallPrice();

        std::cout << "市场价格: " << marketPrice << std::endl;
        std::cout << "理论价格: " << theoreticalPrice << std::endl;

        if (marketPrice < theoreticalPrice) 
        {
            std::cout << "期权被低估，建议买入期权" << std::endl;
        } 
        else if (marketPrice > theoreticalPrice) 
        {
            std::cout << "期权被高估，建议卖出期权" << std::endl;
        } 
        else 
        {
            std::cout << "期权价格与理论价格相符" << std::endl;
        }
    }

private:
    double K; // 行权价
    double r; // 无风险利率
    double s; // 波动率
};

} 

#endif 
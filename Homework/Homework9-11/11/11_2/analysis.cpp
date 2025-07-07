#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <memory>
#include "black_scholes.hpp"
#include "event.hpp"
#include "analysis.hpp"

// 市场数据类，用于存储市场价格和理论价格
class MarketData 
{
public:
    MarketData(double marketPrice, double theoreticalPrice)
        : marketPrice(marketPrice), theoreticalPrice(theoreticalPrice) {}

    double getMarketPrice() const { return marketPrice; }
    double getTheoreticalPrice() const { return theoreticalPrice; }

private:
    double marketPrice;
    double theoreticalPrice;
};

// 价格分析器类，用于分析市场价格与理论价格的差异
class PriceAnalyzer 
{
public:
    PriceAnalyzer(Event<const MarketData&>& priceEvent)
        : priceEvent(priceEvent) {}

    // 分析价格差异
    void analyzePriceDifference(const MarketData& market) 
    {
        double marketPrice = market.getMarketPrice();
        double theoreticalPrice = market.getTheoreticalPrice();
        std::cout << "Market Price: " << marketPrice << std::endl;
        std::cout << "Theoretical Price: " << theoreticalPrice << std::endl;

        if (marketPrice < theoreticalPrice) 
        {
            std::cout << "Option is undervalued, consider buying." << std::endl;
        } 
        else if (marketPrice > theoreticalPrice) 
        {
            std::cout << "Option is overvalued, consider selling." << std::endl;
        } 
        else 
        {
            std::cout << "Option price matches theoretical price." << std::endl;
        }
    }

    // 绑定事件监听器
    void bind() 
    {
        priceEvent.addListener([this](const MarketData& market) {
            analyzePriceDifference(market);
        });
    }

private:
    Event<const MarketData&>& priceEvent;
};

// 执行分析
void performAnalysis() 
{
    Event<const MarketData&> priceEvent;

    PriceAnalyzer analyzer(priceEvent);
    analyzer.bind();

    // 创建Black-Scholes模型实例
    double S = 10000.0;    // 标的资产价格
    double r = 0.05;       // 无风险利率
    double K = 10000.0;    // 行权价
    double T = 1.0;        // 到期时间
    double s = 0.15;       // 波动率
    
    BlackScholes bs(S, K, T, r, s);
    double theoreticalPrice = bs.calculateCallPrice();

    MarketData market(1000.0, theoreticalPrice); // 示例市场价格和理论价格

    std::cout << "Simulating market price check:" << std::endl;

    // 触发事件
    priceEvent.trigger(market);
}

int main() 
{
    performAnalysis();
    return 0;
}
// Строитель (Builder)

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

class Tariff
{
    const std::vector<double> amount;
    const std::vector<int> discount;

public:
    Tariff(std::vector<double> &&amount, std::vector<int> &&discount)
        : amount(amount), discount(discount) {
        assert(amount.size() == discount.size());
    }

    void apply();
};

class TariffBuilder
{
    std::map<double/*amount*/, int/*discount*/> tariff;

public:
    void add_discount(double subtotal, int discount) {
        if (discount > 40)
            return;

        tariff[subtotal] = discount;
    }

    Tariff build() {
        std::vector<double> amounts;
        std::vector<int> discounts;

        for (const auto &[amount, discount] : tariff) {
            amounts.push_back(amount);
            discounts.push_back(discount);
        }

        return Tariff(std::move(amounts), std::move(discounts));
    }
};

void Tariff::apply() {
    std::cout << "[Tariff]" << std::endl;
    for (size_t i = 0; i < amount.size(); ++i) {
        std::cout << "After " << amount[i] << " RUB apply " << discount[i] << "%"
                  << std::endl;
    }
}

int main(int, char *[]) {
    auto builder = TariffBuilder();
    builder.add_discount(1000, 10);
    builder.add_discount(20000, 20);
    builder.add_discount(10000, 15);
    builder.add_discount(25000, 25);
    builder.add_discount(30000, 50);
    auto tariff = builder.build();

    tariff.apply();

    return 0;
}

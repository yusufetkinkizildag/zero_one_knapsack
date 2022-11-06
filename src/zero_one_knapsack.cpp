#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include <numeric>

namespace utility
{
    constexpr static auto print_dp{[](auto const &dp) noexcept
    {
        for (auto i{0}; i < dp.size(); ++i)
        {
            std::cout << '[';
            for (auto j{0}; j < dp[i].size() - 1; ++j)
            {
                std::cout << std::setw(2) << std::setfill(' ') << dp[i][j] << ", ";
            }
            std::cout << std::setw(2) << std::setfill(' ') << dp[i].back();
            std::cout << "]\n";
        }
    }};

    constexpr static auto print_selected_items{[](auto const &selected_items, auto const &profits, auto const &weights) noexcept
    {
        std::cout << "Selected items (P, W)\n";
        std::cout << '[';
        for (auto i{0}; i < selected_items.size(); ++i)
        {
            if (selected_items[i] == 1)
            {
                std::cout << "(" << profits[i] << ", " << weights[i] << "), ";
            }
        }
        std::cout << "]\n";
    }};
} // namespace utility


namespace recursive
{

    constexpr static auto solve_recursive{[](auto const &profits, auto const &weights, auto const capacity, auto const current_index) noexcept
    {
        if (capacity <= 0 || current_index >= profits.size())
        {
            return 0;
        }
        auto profit1{0};
        if (weights[current_index] <= capacity)
        {
            profit1 = profits[current_index] + solve_recursive(profits, weights, capacity - weights[current_index], current_index + 1);
        }
        auto const profit2{solve_recursive(profits, weights, capacity, current_index + 1)};
        return std::max(profit1, profit2);
    }};

    constexpr static auto solve{[](auto const &profits, auto const &weights, auto const capacity) noexcept
    {
        return solve_recursive(profits, weights, capacity, 0);
    }};

} // namespace recursive

namespace memoization
{

    constexpr static auto solve_recursive{[](auto &dp, auto const &profits, auto const &weights, auto const capacity, auto const current_index) noexcept
    {
        if (capacity <= 0 || current_index >= profits.size())
        {
            return 0;
        }
        if (dp[current_index][capacity] != -1)
        {
            return dp[current_index][capacity];
        }
        auto profit1{0};
        if (weights[current_index] <= capacity)
        {
            profit1 = profits[current_index] + solve_recursive(dp, profits, weights, capacity - weights[current_index], current_index + 1);
        }
        auto const profit2{solve_recursive(dp, profits, weights, capacity, current_index + 1)};
        dp[current_index][capacity] = std::max(profit1, profit2);
        return dp[current_index][capacity];
    }};

    constexpr static auto solve{[](auto const &profits, auto const &weights, auto const capacity) noexcept
    {
        std::vector<std::vector<int>> dp(profits.size(), std::vector<int>(capacity + 1, -1));
        return solve_recursive(dp, profits, weights, capacity, 0);
    }};

} // namespace memoization

namespace dynamic
{

    constexpr static auto get_selected_items{[](auto const &dp, auto const &profits, auto const &weights, auto const capacity) noexcept
    {
        auto const n{weights.size() - 1};
        auto cap{capacity};
        auto total_profit{dp[n][capacity]};
        std::vector<size_t> selected_items(n + 1, 0);
        for(auto i{n}; i > 0; i--)
        {
            if (total_profit != dp[i-1][cap])
            {
                
                selected_items[i] = 1;
                cap -= weights[i];
                total_profit -= profits[i];
            }
        }
        if (total_profit > 0 && weights[0] <= cap)
        {
            selected_items[0] = 1;
        }
        return selected_items;
    }};

    constexpr static auto solve{[](auto const &profits, auto const &weights, auto const capacity) noexcept
    {
        if (capacity <= 0 || profits.empty() || weights.size() != profits.size())
        {
            return 0;
        }
        auto const n{profits.size()};
        std::vector<std::vector<int>> dp(n, std::vector<int>(capacity + 1, 0));
        for (auto c{0}; c <= capacity; ++c)
        {
            if (weights[0] <= c)
            {
                dp[0][c] = profits[0];
            }
        }
        for (auto i{1}; i < n; ++i)
        {
            for (auto c{1}; c <= capacity; ++c)
            {
                auto profit1{0};
                if (weights[i] <= c)
                {
                    profit1 = profits[i] + dp[i - 1][c - weights[i]];
                }
                dp[i][c] = std::max(profit1, dp[i - 1][c]);
            }
        }
        auto const selected_items{get_selected_items(dp, profits, weights, capacity)};
        utility::print_selected_items(selected_items, profits, weights);
        return dp[n - 1][capacity];
    }};

} // namespace dynamic


namespace zero_one_knapsack
{

    class Problem
    {
        private:
            std::vector<size_t> X;
            std::vector<double> P;
            std::vector<double> W;
            std::vector<std::vector<double>> d;
        public:
            Problem(std::vector<double> const &P, std::vector<double> const &W) noexcept : P{P}, W{W} {}
            Problem(std::vector<double> &&P, std::vector<double> const &W) noexcept : P{std::move(P)}, W{W} {}
            Problem(std::vector<double> const &P, std::vector<double> &&W) noexcept : P{P}, W{std::move(W)} {}
            Problem(std::vector<double> &&P, std::vector<double> &&W) noexcept : P{std::move(P)}, W{std::move(W)} {}

            void solve(size_t const capacity) noexcept
            {
                auto const size{this->P.size()};
                d.resize(size);
                for (auto &row : d)
                {
                    row = std::vector<double>(capacity + 1, 0);
                }
                for (auto c{0}; c <= capacity; ++c)
                {
                    if (this->W[0] <= c)
                    {
                        this->d[0][c] = this->P[0];
                    }
                }
                for (auto i{1}; i < size; ++i)
                {
                    for (auto c{1}; c <= capacity; ++c)
                    {
                        auto profit1{0.0};
                        if (this->W[i] <= c)
                        {
                            profit1 = this->P[i] + this->d[i - 1][c - this->W[i]];
                        }
                        this->d[i][c] = std::max(profit1, this->d[i - 1][c]);
                    }
                }
            }

            std::vector<size_t> get_selected_items() noexcept
            {
                auto const n{this->W.size() - 1};
                auto cap{this->d.front().size() - 1};
                auto total_profit{this->d[n][cap]};
                this->X.clear();
                this->X.resize(n + 1, 0);
                for(auto i{n}; i > 0; i--)
                {
                    if (total_profit != this->d[i-1][cap])
                    {
                        this->X[i] = 1;
                        cap -= this->W[i];
                        total_profit -= this->P[i];
                    }
                }
                if (total_profit > 0 && this->W[0] <= cap)
                {
                    this->X[0] = 1;
                }
                return this->X;
            }

            double get_maximum_profit() noexcept
            {
                return std::transform_reduce(std::cbegin(this->X), std::cend(this->X), std::cbegin(this->P), 0.0);
            }

            double get_maximum_weight() noexcept
            {
                return std::transform_reduce(std::cbegin(this->X), std::cend(this->X), std::cbegin(this->W), 0.0);
            }
    };

} // namespace zero_one_knapsack


int main(int argc, char const *argv[])
{
    std::vector<int> profits{1, 6, 10, 16};
    std::vector<int> weights{1, 2, 3, 5};
    std::cout << "recursive" << '\n';
    std::cout << recursive::solve(profits, weights, 6) << '\n';
    std::cout << recursive::solve(profits, weights, 7) << '\n';
    std::cout << "recursive with memoization" << '\n';
    std::cout << memoization::solve(profits, weights, 6) << '\n';
    std::cout << memoization::solve(profits, weights, 7) << '\n';
    std::cout << "dynamic" << '\n';
    std::cout << dynamic::solve(profits, weights, 6) << '\n';
    std::cout << dynamic::solve(profits, weights, 7) << '\n';
    std::cout << "Inside a class" << '\n';
    zero_one_knapsack::Problem problem({1, 6, 10, 16}, {1, 2, 3, 5});
    problem.solve(6);
    auto const selected_items1{problem.get_selected_items()};
    auto const p1{problem.get_maximum_profit()};
    auto const w1{problem.get_maximum_weight()};
    std::cout << p1 << ' ' << w1 << '\n';
    problem.solve(7);
    auto const selected_items2{problem.get_selected_items()};
    auto const p2{problem.get_maximum_profit()};
    auto const w2{problem.get_maximum_weight()};
    std::cout << p2 << ' ' << w2 << '\n';
    return 0;
}

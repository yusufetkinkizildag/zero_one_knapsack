#include <iostream>
#include <vector>

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

int main(int argc, char const *argv[])
{
    std::vector<int> profits{1, 6, 10, 16};
    std::vector<int> weights{1, 2, 3, 5};
    std::cout << "recursive" << std::endl;
    std::cout << recursive::solve(profits, weights, 6) << std::endl;
    std::cout << recursive::solve(profits, weights, 7) << std::endl;
    std::cout << "recursive with memoization" << std::endl;
    std::cout << memoization::solve(profits, weights, 6) << std::endl;
    std::cout << memoization::solve(profits, weights, 7) << std::endl;
    return 0;
}


// using namespace std;

// #include <iostream>
// #include <vector>

// class Knapsack {
// public:
//   int solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity) {
//     // basic checks
//     if (capacity <= 0 || profits.empty() || weights.size() != profits.size()) {
//       return 0;
//     }

//     int n = profits.size();
//     vector<vector<int>> dp(n, vector<int>(capacity + 1));

//     // populate the capacity=0 columns, with '0' capacity we have '0' profit
//     for (int i = 0; i < n; i++) {
//       dp[i][0] = 0;
//     }

//     // if we have only one weight, we will take it if it is not more than the capacity
//     for (int c = 0; c <= capacity; c++) {
//       if (weights[0] <= c) {
//         dp[0][c] = profits[0];
//       }
//     }

//     // process all sub-arrays for all the capacities
//     for (int i = 1; i < n; i++) {
//       for (int c = 1; c <= capacity; c++) {
//         int profit1 = 0, profit2 = 0;
//         // include the item, if it is not more than the capacity
//         if (weights[i] <= c) {
//           profit1 = profits[i] + dp[i - 1][c - weights[i]];
//         }
//         // exclude the item
//         profit2 = dp[i - 1][c];
//         // take maximum
//         dp[i][c] = max(profit1, profit2);
//       }
//     }

//     // maximum profit will be at the bottom-right corner.
//     return dp[n - 1][capacity];
//   }
// };

// int main(int argc, char *argv[]) {
//   Knapsack ks;
//   vector<int> profits = {1, 6, 10, 16};
//   vector<int> weights = {1, 2, 3, 5};
//   int maxProfit = ks.solveKnapsack(profits, weights, 6);
//   cout << "Total knapsack profit ---> " << maxProfit << endl;
//   maxProfit = ks.solveKnapsack(profits, weights, 7);
//   cout << "Total knapsack profit ---> " << maxProfit << endl;
// }

// // print elements

// using namespace std;

// #include <iostream>
// #include <vector>

// class Knapsack {
// public:
//   int solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity) {
//     // base checks
//     if (capacity <= 0 || profits.empty() || weights.size() != profits.size()) {
//       return 0;
//     }

//     int n = profits.size();
//     vector<vector<int>> dp(n, vector<int>(capacity + 1));

//     // populate the capacity=0 columns, with '0' capacity we have '0' profit
//     for (int i = 0; i < n; i++) {
//       dp[i][0] = 0;
//     }

//     // if we have only one weight, we will take it if it is not more than the capacity
//     for (int c = 0; c <= capacity; c++) {
//       if (weights[0] <= c) {
//         dp[0][c] = profits[0];
//       }
//     }

//     // process all sub-arrays for all the capacities
//     for (int i = 1; i < n; i++) {
//       for (int c = 1; c <= capacity; c++) {
//         int profit1 = 0, profit2 = 0;
//         // include the item, if it is not more than the capacity
//         if (weights[i] <= c) {
//           profit1 = profits[i] + dp[i - 1][c - weights[i]];
//         }
//         // exclude the item
//         profit2 = dp[i - 1][c];
//         // take maximum
//         dp[i][c] = max(profit1, profit2);
//       }
//     }

//     printSelectedElements(dp, weights, profits, capacity);
//     // maximum profit will be at the bottom-right corner.
//     return dp[n - 1][capacity];
//   }

// private:
//   void printSelectedElements(vector<vector<int>> &dp, const vector<int> &weights,
//                              const vector<int> &profits, int capacity) {
//     cout << "Selected weights:";
//     int totalProfit = dp[weights.size() - 1][capacity];
//     for (int i = weights.size() - 1; i > 0; i--) {
//       if (totalProfit != dp[i - 1][capacity]) {
//         cout << " " << weights[i];
//         capacity -= weights[i];
//         totalProfit -= profits[i];
//       }
//     }

//     if (totalProfit != 0) {
//       cout << " " << weights[0];
//     }
//     cout << "" << endl;
//   }
// };

// int main(int argc, char *argv[]) {
//   Knapsack ks;
//   vector<int> profits = {1, 6, 10, 16};
//   vector<int> weights = {1, 2, 3, 5};
//   int maxProfit = ks.solveKnapsack(profits, weights, 7);
//   cout << "Total knapsack profit ---> " << maxProfit << endl;
//   maxProfit = ks.solveKnapsack(profits, weights, 6);
//   cout << "Total knapsack profit ---> " << maxProfit << endl;
// }

// using namespace std;

// #include <iostream>
// #include <vector>

// // space optimization
// class Knapsack {
// public:
//   int solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity) {
//     //TODO: Write - Your - Code
//     return -1;
//   }
// };

// using namespace std;

// #include <iostream>
// #include <vector>

// class Knapsack {
// public:
//   int solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity) {
//     return this->knapsackRecursive(profits, weights, capacity, 0);
//   }

// private:
//   int knapsackRecursive(const vector<int> &profits, const vector<int> &weights, int capacity,
//                         int current_index) {
//     // base checks
//     if (capacity <= 0 || current_index >= profits.size()) {
//       return 0;
//     }

//     // recursive call after choosing the element at the current_index
//     // if the weight of the element at current_index exceeds the capacity, we shouldn't process this
//     int profit1 = 0;
//     if (weights[current_index] <= capacity) {
//       profit1 =
//           profits[current_index] +
//           knapsackRecursive(profits, weights, capacity - weights[current_index], current_index + 1);
//     }

//     // recursive call after excluding the element at the current_index
//     int profit2 = knapsackRecursive(profits, weights, capacity, current_index + 1);

//     return max(profit1, profit2);
//   }
// };

// int main(int argc, char *argv[]) {
//   Knapsack ks;
//   vector<int> profits = {1, 6, 10, 16};
//   vector<int> weights = {1, 2, 3, 5};
//   int maxProfit = ks.solveKnapsack(profits, weights, 7);
//   cout << "Total knapsack profit ---> " << maxProfit << endl;
//   maxProfit = ks.solveKnapsack(profits, weights, 6);
//   cout << "Total knapsack profit ---> " << maxProfit << endl;
// }
// //****************************************************************** benim eski cozum
// #include <iostream>

// #define NUMBER_OF_ITEMS 4
// #define KNAPSACK_CAPACITY 5

// void print_array(int *array, int array_length)
// {
//     for (int i = 0; i < array_length; i++)
//     {
//         std::cout << array[i] << " ";
//     }
//     std::cout << std::endl;
// }

// int knapsack_recursive(int weights[], int values[], int number_of_items, int knapsack_capacity)
// {
//     if (knapsack_capacity == 0) //if the capacity of knapsack is 0 then can not include any item
//     {
//         return 0;
//     }

//     if (number_of_items == 0) //if no more items are left then return
//     {
//         return 0;
//     }

//     if (weights[number_of_items - 1] > knapsack_capacity) //if current item weighs more than the capacity of knapsack, it can not be included
//     {
//         return knapsack_recursive(weights, values, number_of_items - 1, knapsack_capacity);
//     }

//     //else select the maximum value of once including the current item and once not including it
//     return std::max(knapsack_recursive(weights, values, number_of_items - 1, knapsack_capacity), values[number_of_items - 1] + knapsack_recursive(weights, values, number_of_items - 1, knapsack_capacity - weights[number_of_items - 1]));
// }

// int knapsack_dynamic(int weights[], int values[], int number_of_items, int knapsack_capacity)
// {
//     int i, j;
//     int knapsack[number_of_items + 1][knapsack_capacity + 1];
//     for (i = 0; i <= number_of_items; i++)
//     {
//         knapsack[i][0] = 0;
//     }
//     for (j = 0; j <= knapsack_capacity; j++)
//     {
//         knapsack[0][j] = 0;
//     }

//     for (i = 1; i <= number_of_items; i++)
//     {
//         for (j = 1; j <= knapsack_capacity; j++)
//         {
//             if (weights[i - 1] <= j)
//             {
//                 knapsack[i][j] = std::max(knapsack[i - 1][j], values[i - 1] + knapsack[i - 1][j - weights[i - 1]]);
//             }
//             else
//             {
//                 knapsack[i][j] = knapsack[i - 1][j];
//             }
//         }
//     }

//     return knapsack[number_of_items][knapsack_capacity];
// }

// int main(int argc, char const *argv[])
// {
//     int weights[NUMBER_OF_ITEMS] = {2, 1, 3, 2};    // item one is 2kg, item two is 1kg, item three is 3kg, item four is 2kg
//     int values[NUMBER_OF_ITEMS] = {12, 10, 20, 15}; // item one is 12$, item two is 10$, item three is 20$, item four is 15$
//     std::cout << knapsack_recursive(weights, values, NUMBER_OF_ITEMS, KNAPSACK_CAPACITY) << "$\n";
//     std::cout << knapsack_dynamic(weights, values, NUMBER_OF_ITEMS, KNAPSACK_CAPACITY) << "$\n";
//     return 0;
// }

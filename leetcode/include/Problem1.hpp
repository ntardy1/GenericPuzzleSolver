////////////////////////////////////////////////////////////////////////////////
// system includes
////////////////////////////////////////////////////////////////////////////////
#include <vector>

/**
 * @class Problem1
 * @brief Computes indices of two values whose sum matches the target.
 */
class Problem1 {
    public:
        Problem1();

        std::vector<int> solve(std::vector<int>& nums, int target);
};
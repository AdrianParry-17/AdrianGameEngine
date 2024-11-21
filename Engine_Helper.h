#ifndef __ENGINE_HELPER_H__
#define __ENGINE_HELPER_H__

#include <string>
#include <vector>

namespace Engine {
    /// @brief The String Helper class, provide basic helper function that related to string.
    class StringHelper final {
    public:
        /// @brief Split the string into multiple part and store the result into the given vector.
        /// @param s The string to split.
        /// @param result The vector to store the result, this will cleared all previous element in the vector.
        /// @param delimiter The delimiter use to split the string, default is a space character (' ').
        /// @param remove_empty_string If this true (default), will remove all empty string after split.
        static void Split(const std::string& s, std::vector<std::string>& result, char delimiter = ' ', bool remove_empty_string = true) {
            result.clear();
            result.push_back("");

            for (char c : s) {
                if (c == delimiter) {
                    if (!remove_empty_string || !result.back().empty())
                        result.push_back("");
                    continue;
                }
                result.back() += c;
            }

            if (result.back().empty() && remove_empty_string)
                result.pop_back();
        }
    };
}

#endif // __ENGINE_HELPER_H__
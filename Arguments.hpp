#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <bits/stdc++.h>

namespace qboost
{
    namespace args
    {
        inline bool argsExist(std::vector<std::string>& t, long long argOffset)
        {
            return !(argOffset >= t.size());
        }

        inline std::vector<std::string> getArgs(const std::string& str)
        {
            std::string processed_str = str;
            if (!processed_str.empty() && processed_str.back() == '\\') {
                processed_str.pop_back();
            }
            boost::escaped_list_separator<char> sep('\\', ' ', '\"');
            boost::tokenizer<boost::escaped_list_separator<char>> tok(processed_str, sep);
            std::vector<std::string> tokens;
            tokens.assign(tok.begin(), tok.end());
            return tokens;
        }

        inline bool firstArgMatch(std::vector<std::string>& args, std::string mtch)
        {
            if (args.empty()) return false;
            return args[0] == mtch;
        }

        inline std::vector<std::string> getRemainingArgs(std::vector<std::string> args)
        {
            std::reverse(args.begin(), args.end());
            args.pop_back();
            std::reverse(args.begin(), args.end());
            return args;
        }

        inline bool argsOverloaded(std::vector<std::string>& t, long long max_param)
        {
            return ((long long)t.size() > max_param);
        }

    }
}


#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_addres = std::vector<std::string>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::ostream &operator<<(std::ostream &out, const ip_addres &addr)
{
    for (auto ip_part = addr.cbegin(); ip_part != addr.cend(); ++ip_part)
    {
        if (ip_part != addr.cbegin())
            out << ".";
        out << *ip_part;
    }
    return out;
}


int main(/*int argc, char const *argv[]*/)
{

    try
    {
        std::vector<ip_addres > ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            ip_addres v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        std::sort(ip_pool.begin(), ip_pool.end(),
            [](const ip_addres &left, const ip_addres &right){
                for (size_t i = 0; i < left.size(); i++) {
                    if (left[i] != right[i])
                        return std::stoi(left[i]) > std::stoi(right[i]);
                }
                return true;
            });

        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            std::cout << *ip << std::endl;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // std::cout << "-------------------------------------" << std::endl;

        std::for_each(ip_pool.begin(), ip_pool.end(),
            [](const ip_addres &addr){
                if (addr[0] == "1")
                    std::cout << addr << std::endl;
            });

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // std::cout << "-------------------------------------" << std::endl;
        
        std::for_each(ip_pool.begin(), ip_pool.end(),
            [](const ip_addres &addr){
                if (addr[0] == "46" && addr[1] == "70")
                    std::cout << addr << std::endl;
            });


        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46

        // std::cout << "-------------------------------------" << std::endl;
        
        std::for_each(ip_pool.begin(), ip_pool.end(),
            [](const ip_addres &addr){
                if (std::any_of(addr.cbegin(), addr.cend(),
                    [](const std::string &part){
                        return part == "46";
                    }))
                    std::cout << addr << std::endl;
            });
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

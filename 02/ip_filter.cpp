#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_addres = std::vector<std::string>;

std::vector<std::string> split(const std::string &str, char separator)
{
    std::vector<std::string> string_list;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(separator);
    while(stop != std::string::npos)
    {
        string_list.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(separator, start);
    }
    string_list.push_back(str.substr(start));

    return string_list;
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


int main()
{
    try
    {
        std::vector<ip_addres> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            ip_addres v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // reverse lexicographically sort
        
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

        // TODO filter by first byte and output

        std::for_each(ip_pool.begin(), ip_pool.end(),
            [](const ip_addres &addr){
                if (addr[0] == "1")
                    std::cout << addr << std::endl;
            });

        // TODO filter by first and second bytes and output
        
        std::for_each(ip_pool.begin(), ip_pool.end(),
            [](const ip_addres &addr){
                if (addr[0] == "46" && addr[1] == "70")
                    std::cout << addr << std::endl;
            });


        // TODO filter by any byte and output
        // ip = filter_any(46)
        
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

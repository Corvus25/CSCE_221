#ifndef PROJECTS_Jeans_H
#define PROJECTS_Jeans_H
#include <iostream>
#include <string>
#include <map>

enum class Jeans_colors {
    navy,
    camo,
    teal,
    khaki
};

enum class Jeans_sizes {
    small,
    medium,
    large
};

class Jeans {
private:
    Jeans_colors c;
    Jeans_sizes s;

public:
    Jeans();
    Jeans(Jeans_colors c, Jeans_sizes s) : c(c), s(s) {}
    Jeans_colors get_color() const;
    Jeans_sizes get_size() const;

    bool operator==(Jeans &jn) {
        bool flag1 = false, flag2 = false;

        if (get_color() == jn.get_color())
            flag1 = true;

        if (get_size() == jn.get_size())
            flag2 = true;

        return flag1 && flag2;
    }

    bool operator==(const Jeans& jn) const;
};

//std::ostream& operator<<(std::ostream& o, const Jeans& jn);

#endif

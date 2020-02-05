#ifndef PROJECTS_STRESS_BALL_H
#define PROJECTS_STRESS_BALL_H
#include <iostream>
#include <string>
#include <map>

enum class Stress_ball_colors {
    red,
    blue,
    yellow,
    green
};

enum class Stress_ball_sizes {
    small,
    medium,
    large
};

class Stress_ball {
private:
    Stress_ball_colors c;
    Stress_ball_sizes s;

public:
    Stress_ball();
    Stress_ball(Stress_ball_colors c, Stress_ball_sizes s) : c(c), s(s) {}
    Stress_ball_colors get_color() const;
    Stress_ball_sizes get_size() const;

    bool operator==(Stress_ball &sb) {
        bool flag1 = false, flag2 = false;

        if (get_color() == sb.get_color())
            flag1 = true;

        if (get_size() == sb.get_size())
            flag2 = true;

        return flag1 && flag2;
    }

    bool operator==(const Stress_ball& sb) const;
};

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb);

#endif

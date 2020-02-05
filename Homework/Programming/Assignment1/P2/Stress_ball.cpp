#include <iostream>
#include <map>
#include <cstdlib>
#include "Stress_ball.h"
using namespace std;

Stress_ball::Stress_ball() {
    c = Stress_ball_colors(rand() % 4);
    s = Stress_ball_sizes(rand() % 3);
}

bool Stress_ball::operator==(const Stress_ball& sb) const {
    if (sb.get_color() != this->get_color()) {
        return false;
    }
    if (sb.get_size() != this->get_size()) {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb) {
    std::map<Stress_ball_colors, std::string> convert_color;
    std::map<Stress_ball_sizes, std::string> convert_size;

    convert_color[Stress_ball_colors::red] = "red";
    convert_color[Stress_ball_colors::blue] = "blue";
    convert_color[Stress_ball_colors::yellow] = "yellow";
    convert_color[Stress_ball_colors::green] = "green";
    convert_size[Stress_ball_sizes::small] = "small";
    convert_size[Stress_ball_sizes::medium] = "medium";
    convert_size[Stress_ball_sizes::large] = "large";

    o << "(" << convert_color[sb.get_color()] << ", " << convert_size[sb.get_size()] << ")";
    return o;
}

Stress_ball_colors Stress_ball::get_color() const {
    return c;
}

Stress_ball_sizes Stress_ball::get_size() const {
    return s;
}
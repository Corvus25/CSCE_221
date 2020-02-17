#include <iostream>
#include <map>
#include <cstdlib>
#include "Jeans.h"
using namespace std;

Jeans::Jeans() {
    c = Jeans_colors(rand() % 4);
    s = Jeans_sizes(rand() % 3);
}

bool Jeans::operator==(const Jeans& jn) const {
    if (jn.get_color() != this->get_color()) {
        return false;
    }
    if (jn.get_size() != this->get_size()) {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& o, const Jeans& jn) {
    std::map<Jeans_colors, std::string> convert_color;
    std::map<Jeans_sizes, std::string> convert_size;

    convert_color[Jeans_colors::navy] = "navy";
    convert_color[Jeans_colors::camo] = "camo";
    convert_color[Jeans_colors::teal] = "teal";
    convert_color[Jeans_colors::khaki] = "khaki";
    convert_size[Jeans_sizes::small] = "small";
    convert_size[Jeans_sizes::medium] = "medium";
    convert_size[Jeans_sizes::large] = "large";

    o << "(" << convert_color[jn.get_color()] << ", " << convert_size[jn.get_size()] << ")";
    return o;
}

Jeans_colors Jeans::get_color() const {
    return c;
}

Jeans_sizes Jeans::get_size() const {
    return s;
}
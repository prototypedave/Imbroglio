#ifndef layout_hpp
#define layout_hpp

#include <vector>
#include <string>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Layout {
public:
    Layout(std::string filename, Vector2d &pos);
    std::vector<std::vector<int>> map;
    uint32_t columns;
    uint32_t rows;
};

#endif /* layout_hpp */

#ifndef GRID_COMPONENT_HPP
#define GRID_COMPONENT_HPP

#include <sigma/graphics/static_mesh.hpp>

struct grid_component {
    int rows;
    int columns;
    float row_spacing;
    float column_spacing;
    std::shared_ptr<sigma::graphics::static_mesh> mesh;

    grid_component(int rows = 0, int columns = 0,
        float row_spacing = 0, float column_spacing = 0,
        std::shared_ptr<sigma::graphics::static_mesh> mesh = nullptr)
        : rows(rows)
        , columns(columns)
        , row_spacing(row_spacing)
        , column_spacing(column_spacing)
    {
    }
};

#endif // GRID_COMPONENT_HPP

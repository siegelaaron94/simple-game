#include "simple_game.hpp"

#include <sigma/graphics/render_queue.hpp>

#include <chrono>
#include <cmath>

simple_game::simple_game(std::shared_ptr<sigma::context> ctx, sigma::graphics::render_queue* queue)
    : queue_(queue)
{
}

void simple_game::update(const sigma::graphics::view_port& viewport, std::chrono::duration<float> dt)
{
    auto transform_view = registry().view<sigma::transform, sigma::graphics::static_mesh_instance>();
    transform_view.each([&](auto e, sigma::transform& tx, sigma::graphics::static_mesh_instance& sm) {
        for (const auto& part : sm.mesh->parts()) {
            auto cmd = queue_->enqueue();
            cmd->group = 0;
            cmd->projection_view = viewport.view_frustum.projection_view();
            cmd->model = tx.matrix;
            cmd->program = part.material()->id();
            cmd->mesh = sm.mesh->id();
            cmd->offset = part.start();
            cmd->count = part.end() - part.start();
            for (const auto [i, buffer] : part.material()->buffers()) {
                cmd->buffer_bindings[i] = buffer->id();
            }
            for (const auto [i, texture] : part.material()->textures()) {
                cmd->input_textures[i] = texture->id();
            }
        }
    });
}
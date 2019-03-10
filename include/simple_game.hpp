#ifndef SIMPLE_GAME_HPP
#define SIMPLE_GAME_HPP

#include <grid_component.hpp>

#include <sigma/context.hpp>
#include <sigma/game.hpp>
#include <sigma/graphics/directional_light.hpp>
#include <sigma/graphics/point_light.hpp>
#include <sigma/graphics/post_process_effect.hpp>
#include <sigma/graphics/renderer.hpp>
#include <sigma/graphics/spot_light.hpp>
#include <sigma/graphics/static_mesh_instance.hpp>
#include <sigma/transform.hpp>

#include <glm/vec3.hpp>

struct simple_level_settings {
    static constexpr const char* GROUP = "level";
};

class simple_game : public sigma::game {
public:
    simple_game(std::shared_ptr<sigma::context> ctx);

    virtual void update(std::chrono::duration<float> dt) override;
};

#endif // SIMPLE_GAME_HPP

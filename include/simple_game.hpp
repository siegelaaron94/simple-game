#ifndef SIMPLE_GAME_HPP
#define SIMPLE_GAME_HPP

#include <grid_component.hpp>

#include <sigma/blueprint.hpp>
#include <sigma/context.hpp>
#include <sigma/game.hpp>
#include <sigma/graphics/directional_light.hpp>
#include <sigma/graphics/point_light.hpp>
#include <sigma/graphics/post_process_effect.hpp>
#include <sigma/graphics/renderer.hpp>
#include <sigma/graphics/spot_light.hpp>
#include <sigma/graphics/static_mesh_instance.hpp>
#include <sigma/transform.hpp>
#include <sigma/world.hpp>

#include <glm/vec3.hpp>

using simple_component_set = sigma::component_set<sigma::transform,
    sigma::graphics::directional_light,
    sigma::graphics::point_light,
    sigma::graphics::spot_light,
    sigma::graphics::static_mesh_instance,
    grid_component>;

using simple_world = sigma::world<simple_component_set>;

using simple_blueprint = sigma::blueprint<simple_component_set>;

struct simple_level_settings {
    static constexpr const char* GROUP = "level";

    BOOST_HANA_DEFINE_STRUCT(simple_level_settings,
        (std::shared_ptr<simple_blueprint>, current_level_blueprint));
};

class simple_game : public sigma::game<simple_world> {
public:
    simple_game(std::shared_ptr<sigma::context> ctx);

    virtual void update(std::chrono::duration<float> dt) override;
};

#endif // SIMPLE_GAME_HPP

#include <simple_game.hpp>

#include <sigma/config.hpp>
#include <sigma/context.hpp>
#include <sigma/graphics/opengl/renderer.hpp>
#include <sigma/graphics/renderer.hpp>
#include <sigma/trackball_controller.hpp>
#include <sigma/util/type_sequence.hpp>
#include <sigma/window.hpp>

#include <SDL2/SDL.h>

#include <filesystem>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    auto cache_path = std::filesystem::current_path() / "data";
    if (!std::filesystem::exists(cache_path))
        cache_path = std::filesystem::current_path() / ".." / "data";

    auto context = std::make_shared<sigma::context>(cache_path);

    sigma::window window { glm::ivec2 { 1920, 1080 } };

    auto game = std::make_shared<simple_game>(context);

    auto renderer = std::make_shared<sigma::opengl::renderer>(window.size(), context);
    sigma::opengl::renderer::world_view_type render_view { game->world() };

    sigma::graphics::view_port viewport {
        window.size(),
        sigma::frustum(0.785398f, (float)window.size().x / (float)window.size().y, 0.1f, 50.0f)
    };
    sigma::trackball_controller controller;
    auto start = std::chrono::high_resolution_clock::now();

    auto elapsed_time_start = start;
    std::size_t count = 0;
    while (window.good()) {

        viewport.view_frustum.set_view(controller.matrix());

        auto end = std::chrono::high_resolution_clock::now();
        auto dt = end - start;
        start = end;

        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - elapsed_time_start);
        count++;
        if (elapsed_time > 1000ms) {
            auto fps = count / (std::chrono::duration_cast<std::chrono::duration<float>>(elapsed_time)).count();
            std::cout << "Frame time: " << (elapsed_time.count() / count) << " ms\n";
            std::cout << "FPS: " << fps << '\n';
            elapsed_time_start = end;
            count = 0;
        }

        if (renderer && game) {
            SDL_GL_MakeCurrent(window.window_, window.gl_context_);
            renderer->render(render_view);
            game->update(std::chrono::duration_cast<std::chrono::duration<float>>(dt));
        }

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_MOUSEWHEEL: {
                controller.zoom(event.wheel.y);
                break;
            }
            case SDL_MOUSEMOTION: {
                controller.update(float(event.motion.x) / window.size().x, float(event.motion.y) / window.size().y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (!controller.is_rotating())
                    controller.beginRotate(float(event.motion.x) / window.size().x, float(event.motion.y) / window.size().y);
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                if (controller.is_rotating())
                    controller.endRotate(float(event.motion.x) / window.size().x, float(event.motion.y) / window.size().y);
                if (controller.isPanning())
                    controller.endPan();
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game = nullptr;
                    renderer = nullptr;
                    window.close();
                } else if (event.key.keysym.sym == SDLK_f) {
                    // renderer->save_frustums = true;
                }
                if (!controller.isPanning())
                    controller.beginPan();
                break;
            }
            case SDL_KEYUP: {
                if (controller.isPanning())
                    controller.endPan();
                break;
            }
            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    game = nullptr;
                    renderer = nullptr;
                    window.close();
                    break;
                }
            case SDL_WINDOWEVENT_RESIZED: {
                break;
            }
            }
            }
        }

        SDL_GL_SwapWindow(window.window_);
    }

    SDL_Quit();

    return 0;
}

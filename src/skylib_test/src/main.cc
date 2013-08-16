#include <skylib_test/test_state.h>
#include <skylib_test/menu_state.h>
#include <skylib_test/level.h>
#include <skylib_test/font.h>
#include <skylib/engine.h>
#include <windows.h>
#include <SDL/SDL.h>

#define FULLSCREEN false
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#if FULLSCREEN
void GetDesktopResolution(int& horizontal, int& vertical) {
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return EXIT_FAILURE;
  }

  int window_width = DEFAULT_WINDOW_WIDTH;
  int window_height = DEFAULT_WINDOW_HEIGHT;
#if FULLSCREEN
  GetDesktopResolution(window_width, window_height);
  const int flags = SDL_OPENGL | SDL_DOUBLEBUF | SDL_FULLSCREEN;
#else
  const int flags = SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE;
#endif

  SDL_Surface *screen = SDL_SetVideoMode(window_width, window_height, 32,
                                         flags);

  if (screen == NULL) {
    return EXIT_FAILURE;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_WM_SetCaption("Marble Game", NULL);
  SDL_ShowCursor(SDL_DISABLE);

  skylib::Engine engine;
  engine.Initialize(window_width, window_height);

  skylib_test::Font font("res/font.json", "res/font.png", &engine);
  if (!font.IsValid()) {
    SDL_Quit();
    return EXIT_FAILURE;
  }

  skylib_test::MenuState *menu_state;
  skylib_test::TestState *test_state = NULL;
  bool playing = false;

  menu_state = new skylib_test::MenuState();
  menu_state->SetEngine(&engine);
  menu_state->Initialize(&font);
  engine.GetStateManager().SetState(menu_state);

  bool running = true;
  bool paused = false;
  SDL_Event event;

  const unsigned int frames_per_second = 60;
  const float frame_space = 1000.0 / frames_per_second;
  float next_time = SDL_GetTicks() + frame_space;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_VIDEORESIZE) {
        engine.UpdateSize(event.resize.w, event.resize.h);
        window_width = event.resize.w;
        window_height = event.resize.h;
      } else if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_p) {
          paused = !paused;
          SDL_WM_GrabInput(paused ? SDL_GRAB_OFF : SDL_GRAB_ON);
          SDL_ShowCursor(paused ? SDL_ENABLE : SDL_DISABLE);
        } else if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }

        if (!paused) {
          if (playing) {
            switch (event.key.keysym.sym) {
              case SDLK_q:
                test_state->Exit();
                break;

              case SDLK_a:
                test_state->SetLeftActive(true);
                break;

              case SDLK_d:
                test_state->SetRightActive(true);
                break;

              case SDLK_w:
                test_state->SetUpActive(true);
                break;

              case SDLK_s:
                test_state->SetDownActive(true);
                break;

              case SDLK_SPACE:
                test_state->Jump();
                break;

              default:
                break;
            }
          } else {
            switch (event.key.keysym.sym) {
              case SDLK_LEFT:
                menu_state->Left();
                break;

              case SDLK_RIGHT:
                menu_state->Right();
                break;

              case SDLK_RETURN:
                menu_state->Enter();
                break;

              default:
                break;
            }
          }
        }
      } else if (event.type == SDL_KEYUP && !paused && playing) {
        switch (event.key.keysym.sym) {
          case SDLK_a:
            test_state->SetLeftActive(false);
            break;

          case SDLK_d:
            test_state->SetRightActive(false);
            break;

          case SDLK_w:
            test_state->SetUpActive(false);
            break;

          case SDLK_s:
            test_state->SetDownActive(false);
            break;

          default:
            break;
        }
      } else if (event.type == SDL_MOUSEMOTION && !paused && playing) {
        test_state->UpdateCamera(event.motion.xrel, event.motion.yrel);
      } else if (event.type == SDL_MOUSEBUTTONDOWN && !paused && playing) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          test_state->Jump();
        }
      }
    }

    if (playing) {
      if (test_state->ShouldExit()) {
        playing = false;
        menu_state = new skylib_test::MenuState();
        menu_state->SetEngine(&engine);
        menu_state->Initialize(&font);
        engine.GetStateManager().SetState(menu_state);
        delete test_state;
      }
    } else {
      if (menu_state->Selected()) {
        playing = true;
        test_state = new skylib_test::TestState();
        test_state->SetEngine(&engine);
        skylib_test::Level level("res/levels/" + menu_state->Filename());
        test_state->Initialize(level, &font);
        engine.GetStateManager().SetState(test_state);
        delete menu_state;
      }
    }

    if (!paused) {
      engine.Update();
    }
    engine.Draw();

    SDL_GL_SwapBuffers();

    int delay_time = next_time - SDL_GetTicks();

    if (delay_time > 0) {
      SDL_Delay(delay_time);
    }

    next_time += frame_space;
  }

  if (playing) {
    delete test_state;
  } else {
    delete menu_state;
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}

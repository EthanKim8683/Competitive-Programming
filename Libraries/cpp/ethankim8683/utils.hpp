#ifndef ETHANKIM8683_UTILS
#define ETHANKIM8683_UTILS 1

#ifdef ETHANKIM8683
#include <raylib.h>

#include <functional>

void viz(const std::function<void()> &draw) {
  static bool init = true;
  if (init) {
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(30);
    init = false;
  }

  InitWindow(400, 400, "");
  BeginDrawing();
  draw();
  EndDrawing();
  while (!WindowShouldClose()) {
    PollInputEvents();
  }
  CloseWindow();
}

#define viz(...) viz(__VA_ARGS__)
#else
#define viz(...)
#endif

#endif  // ETHANKIM8683_UTILS

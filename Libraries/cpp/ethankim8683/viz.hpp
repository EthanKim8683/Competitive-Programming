#ifndef ETHANKIM8683_VIZ
#define ETHANKIM8683_VIZ 1

#ifdef ETHANKIM8683
#include "functional"
#include "raylib.h"

void viz(const std::function<void()> &draw) {
  static bool init = true;
  if (init) {
    SetTargetFPS(30);
    SetTraceLogLevel(LOG_NONE);
    init = false;
  }

  InitWindow(400, 400, "");
  while (!WindowShouldClose()) {
    BeginDrawing();
    draw();
    EndDrawing();
  }
  CloseWindow();
}

#define viz(...) viz(__VA_ARGS__)
#else
#define viz(...)
#endif

#endif  // ETHANKIM8683_VIZ
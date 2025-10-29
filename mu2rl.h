#include "microui.h"
#include "raylib.h"

static int text_width(mu_Font font, const char *text, int len);
static int text_height(mu_Font font);

void mu_handle_input(mu_Context* ctx);
void mu_draw_shapes(mu_Context* ctx);
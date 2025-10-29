#include "microui.h"
#include "raylib.h"
#include "stdlib.h"

static int murl_text_width(mu_Font font, const char *text, int len);
static int murl_text_height(mu_Font font);

void mu_handle_input(mu_Context* ctx);
void mu_draw_shapes(mu_Context* ctx);
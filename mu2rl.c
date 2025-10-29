#include "mu2rl.h"

static int text_width(mu_Font font, const char *text, int len) {
    if (len == -1) { len = strlen(text); }
    return MeasureText(text, 20);
}
  
static int text_height(mu_Font font) {
    return 20;
}


void mu_handle_input(mu_Context* ctx) {

  
  // handle text input

  int key = GetCharPressed();

  char* text = malloc(200);

  text[0] = '\0';

  int pos = 0;

  while ((key >= 32) && (key <= 125))
  {
    text[pos] = (char) key;
    text[pos+1] = '\0';

    pos++;

    key = GetCharPressed();
    
  }        
  
  mu_input_text(ctx, text);

  free(text);

  
  //key input
  if(IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) mu_input_keydown(ctx,MU_KEY_SHIFT);
  if(IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) mu_input_keydown(ctx,MU_KEY_BACKSPACE);


  if(IsKeyReleased(KEY_LEFT_SHIFT) || IsKeyReleased(KEY_RIGHT_SHIFT)) mu_input_keyup(ctx,MU_KEY_SHIFT);
  if(IsKeyReleased(KEY_BACKSPACE)) mu_input_keyup(ctx,MU_KEY_BACKSPACE);



  //mouse input
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mu_input_mousedown(ctx, GetMousePosition().x, GetMousePosition().y, MU_MOUSE_LEFT);
  if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) mu_input_mousedown(ctx, GetMousePosition().x, GetMousePosition().y, MU_MOUSE_MIDDLE);
  if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) mu_input_mousedown(ctx, GetMousePosition().x, GetMousePosition().y, MU_MOUSE_RIGHT);

  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) mu_input_mouseup(ctx, GetMousePosition().x, GetMousePosition().y, MU_MOUSE_LEFT);
  if(IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) mu_input_mouseup(ctx, GetMousePosition().x, GetMousePosition().y, MU_MOUSE_MIDDLE);
  if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) mu_input_mouseup(ctx, GetMousePosition().x, GetMousePosition().y, MU_MOUSE_RIGHT);

  

  //scroll wheel + mouse move
  mu_input_mousemove(ctx, GetMousePosition().x, GetMousePosition().y);
  mu_input_scroll(ctx, GetMouseWheelMoveV().x, GetMouseWheelMoveV().y);

}

void mu_draw_shapes(mu_Context* ctx) {
  mu_Command *cmd = 0;
  while (mu_next_command(ctx, &cmd)) {
      switch (cmd->type) {
        case MU_COMMAND_TEXT: DrawText(cmd->text.str, cmd->text.pos.x, cmd->text.pos.y, 20, (Color){cmd->text.color.r, cmd->text.color.g, cmd->text.color.b, 255}); break;
      case MU_COMMAND_RECT: DrawRectangle(cmd->rect.rect.x, cmd->rect.rect.y, cmd->rect.rect.w, cmd->rect.rect.h, (Color){cmd->rect.color.r, cmd->rect.color.g, cmd->rect.color.b, 255}); break;
      case MU_COMMAND_ICON: {
        //draw check icon (just a big X)
        if(cmd->icon.id == MU_ICON_CHECK) DrawText("X",cmd->icon.rect.x + 2, cmd->icon.rect.y + 2, 20, (Color){cmd->icon.color.r, cmd->icon.color.g, cmd->icon.color.b, 255});
        break;
      };
      case MU_COMMAND_CLIP: BeginScissorMode(cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w, cmd->clip.rect.h); break;
    }
  }
}


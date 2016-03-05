#pragma once

#include "game.h"

class message_buffer {
private:
   bool has_message;
   bool has_params;

   UINT message;
   WPARAM wparam;
   LPARAM lparam;
public:
   message_buffer();

   void set_message(UINT message);
   void set_params(WPARAM wparam, LPARAM lparam);

   bool ready() const;
   void clear();

   UINT get_message() const;
   WPARAM get_wparam() const;
   LPARAM get_lparam() const;
};

class message_flow {
private:
   game_window &from;
   game_window &to;
   message_buffer buf;

public:
   message_flow(game_window &from, game_window &to);

   void clear();
   void message(UINT message);
   void params(WPARAM wparam, LPARAM lparam);
   void post();
};

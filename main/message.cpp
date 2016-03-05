#include "stdafx.h"

message_buffer::message_buffer() : has_message{ false },
                                   has_params{ false }
{
}

void message_buffer::set_message(UINT message)
{
   this->message = message;
   has_message = true;
}

void message_buffer::set_params(WPARAM wparam, LPARAM lparam)
{
   this->wparam = wparam;
   this->lparam = lparam;
   has_params = true;
}

bool message_buffer::ready() const
{
   return has_message && has_params;
}

void message_buffer::clear()
{
   has_message = false;
   has_params = false;
}

UINT message_buffer::get_message() const
{
   return message;
}

WPARAM message_buffer::get_wparam() const
{
   return wparam;
}

LPARAM message_buffer::get_lparam() const
{
   return lparam;
}

message_flow::message_flow(game_window &from, game_window &to) : from{ from },
                                                                 to{ to }
{
}

void message_flow::clear() {
   buf.clear();
}

void message_flow::message(UINT message) {
   buf.set_message(message);
}

void message_flow::params(WPARAM wparam, LPARAM lparam) {
   buf.set_params(wparam, lparam);
}

void message_flow::post() {
   if (buf.ready()) {
      UINT message = buf.get_message();
      WPARAM wParam = buf.get_wparam();
      LPARAM lParam = buf.get_lparam();

      from.translate(to, message, wParam, lParam);
      to.post_message(message, wParam, lParam);
      buf.clear();
   }
}

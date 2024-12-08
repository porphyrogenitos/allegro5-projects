#include "Application.hpp"


Application::Application() {
  init();
}

void Application::init() {
  al_init();
  al_install_keyboard();
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();

  platform = std::make_unique<Platform>();
  canvas_controller = std::make_unique<CanvasController>(platform.get());
  timer = al_create_timer(ALLEGRO_BPS_TO_SECS(10.0));
  event_queue = al_create_event_queue();

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  display = al_create_display(500, 500); //NOTE: Hardcoded

  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_mouse_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));

  bool redraw = false;

  al_start_timer(timer);

  while (true) {
    al_wait_for_event(event_queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      tick();
      redraw = true;
      break;
    case ALLEGRO_EVENT_KEY_DOWN:
      platform->keyboard_manager.key_pressed(event.keyboard.keycode);
      break;

    case ALLEGRO_EVENT_KEY_UP:
      platform->keyboard_manager.key_released(event.keyboard.keycode);
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      platform->mouse_manager.move_mouse(event.mouse.x, event.mouse.y);
      break;
      

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      platform->exit = true;
    }

    if (platform->exit) {
      deinit();
      break;
    }

    if (redraw && al_event_queue_is_empty(event_queue)) {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      draw();
      al_flip_display();
      redraw = false;
    }
  }
}

void Application::deinit() {
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
}

void Application::tick() {
  platform->keyboard_manager.tick();
  canvas_controller->tick();
}

void Application::draw() {
  canvas_controller->draw();
}

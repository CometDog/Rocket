#include "pebble.h"
#include "main.h" // Used for drawing hands
#ifdef PBL_COLOR // Only use this for color screens
  #include "gcolor_definitions.h" // Allows the use of colors such as "GColorMidnightGreen"
#endif

static Window *s_main_window; // Main window
static Layer *s_solid_bg_layer, *s_hands_layer; // Solid background and hand layers
static BitmapLayer *s_background_layer; // Background bitmap layer
static GBitmap *s_background_bitmap; // The bitmap that goes on the above layer
static GPath *s_wings, *s_flames, *s_side_wing, *s_stripe, *s_left_win, *s_right_win, *s_tip, *s_min_plan, *s_hour_plan, *s_minute_arrow, *s_hour_arrow, *s_second_arrow; // Paths for the ship and hands

// Update background when called
static void bg_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite); // Set the fill color
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone); // Fill the screen
}

// Update hands when called
static void hands_update_proc(Layer *layer, GContext *ctx) {
  time_t now = time(NULL); // Get the time
  struct tm *t = localtime(&now); // Get the structure of the time
  
  // Set tick paths
  int32_t hour_angle = ((TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6));
  int32_t minute_angle = (TRIG_MAX_ANGLE * t->tm_min / 60);
  int32_t second_angle = (TRIG_MAX_ANGLE * t->tm_sec / 60);
  
  // Define the paths that the objects will follow
  // Minute
  gpath_rotate_to(s_minute_arrow, minute_angle); 
  gpath_rotate_to(s_min_plan, minute_angle);
   
  // Hour
  gpath_rotate_to(s_hour_arrow, hour_angle);
  gpath_rotate_to(s_hour_plan, hour_angle);
                  
  // Ship
  gpath_rotate_to(s_wings, second_angle); 
  gpath_rotate_to(s_second_arrow, second_angle); 
  gpath_rotate_to(s_side_wing, second_angle); 
  gpath_rotate_to(s_stripe, second_angle); 
  gpath_rotate_to(s_left_win, second_angle); 
  gpath_rotate_to(s_right_win, second_angle); 
  gpath_rotate_to(s_tip, second_angle); 
  gpath_rotate_to(s_flames, second_angle); 

  // Minute hand
  #ifdef PBL_COLOR // For color screens
    graphics_context_set_fill_color(ctx, GColorLightGray); // Set fill color
    graphics_context_set_stroke_color(ctx, GColorDarkGray); // Set outline color
  #else // For black and white screens
    graphics_context_set_fill_color(ctx, GColorWhite); // Set fill color
    graphics_context_set_stroke_color(ctx, GColorBlack); // Set outline color
  #endif
  gpath_draw_outline(ctx, s_minute_arrow); // Draw outline
  gpath_draw_filled(ctx, s_minute_arrow); // Fill the hand with the above color
  
  // Minute planet
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorSunsetOrange); 
  #else 
    graphics_context_set_fill_color(ctx, GColorWhite); 
    graphics_context_set_stroke_color(ctx, GColorBlack); 
    gpath_draw_outline(ctx, s_min_plan); // Draw outline if black and white
  #endif
  gpath_draw_filled(ctx, s_min_plan); 
  
  // Hour hand
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorLightGray); 
    graphics_context_set_stroke_color(ctx, GColorDarkGray); 
  #else 
    graphics_context_set_fill_color(ctx, GColorWhite); 
    graphics_context_set_stroke_color(ctx, GColorBlack); 
  #endif
  gpath_draw_outline(ctx, s_hour_arrow); 
  gpath_draw_filled(ctx, s_hour_arrow); 
  
  // Hour planet
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorBrass); 
  #else 
    graphics_context_set_fill_color(ctx, GColorWhite); 
    graphics_context_set_stroke_color(ctx, GColorBlack); 
    gpath_draw_outline(ctx, s_hour_plan); 
  #endif
  gpath_draw_filled(ctx, s_hour_plan); 
  
  // Ship Wings
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorCeleste); 
  #else 
    graphics_context_set_fill_color(ctx, GColorWhite); 
  #endif
  gpath_draw_filled(ctx, s_wings); 
  
  // Ship
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorRajah); 
  #else 
    graphics_context_set_fill_color(ctx, GColorBlack); 
    graphics_context_set_stroke_color(ctx, GColorWhite); 
    gpath_draw_outline(ctx, s_second_arrow); 
  #endif
  gpath_draw_filled(ctx, s_second_arrow); 
  
  // Ship Side Wing
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorCeleste); // Set fill color
  #else 
    graphics_context_set_fill_color(ctx, GColorWhite); // Set fill color
  #endif
  gpath_draw_filled(ctx, s_side_wing); // Fill the hand with the above color
  
  gpath_draw_filled(ctx, s_stripe); // Ship stripe
  gpath_draw_filled(ctx, s_left_win); // Ship left window
  gpath_draw_filled(ctx, s_right_win); // Ship right window
  gpath_draw_filled(ctx, s_tip); // Ship tip
  
  // Ship flames
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, GColorRed); 
  #else 
    graphics_context_set_fill_color(ctx, GColorWhite); 
  #endif
  gpath_draw_filled(ctx, s_flames); 
}

// Update hands every second when called
static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(window_get_root_layer(s_main_window));
}

// Loads the layers onto the main window
static void window_load(Window *s_main_window) {
  Layer *window_layer = window_get_root_layer(s_main_window); // Creates a main layer for the entire window
  GRect bounds = layer_get_bounds(window_layer); // Sets the bounds of the main layer
  
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND); // Set the background bitmap resource

  s_solid_bg_layer = layer_create(bounds); // Create the simple single color background
  s_background_layer = bitmap_layer_create(bounds); // Create the watch face layer
  s_hands_layer = layer_create(bounds); // Create the hands layer
  
  layer_set_update_proc(s_solid_bg_layer, bg_update_proc); // Call the background update function
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); // Set the bitmap image to the background layer
  layer_set_update_proc(s_hands_layer, hands_update_proc); // Call the hands update function
  
  // Add the layers to their parent layers
  layer_add_child(window_layer, s_solid_bg_layer); 
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer)); 
  layer_add_child(window_layer, s_hands_layer); 
}

// Unload the layers from the main window
static void window_unload(Window *s_main_window) {
  // Destroy layers
  layer_destroy(s_solid_bg_layer); 
  gbitmap_destroy(s_background_bitmap); 
  bitmap_layer_destroy(s_background_layer); 
  layer_destroy(s_hands_layer); 
}

// Initialize the main window
static void init() {
  s_main_window = window_create(); // Create the window on initialization
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load, // Allow the window_load function to handle the window
    .unload = window_unload, // Allow the window_unload function to handle the window
  });
  window_stack_push(s_main_window, true); // Show the window. Animated = true

   // Initialize the path of the object from the main.h file
  s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS); 
  s_hour_arrow = gpath_create(&HOUR_HAND_POINTS); 
  s_second_arrow = gpath_create(&SECOND_HAND_POINTS); 
  s_wings = gpath_create(&WINGS_POINTS); 
  s_flames = gpath_create(&FLAMES_POINTS); 
  s_side_wing = gpath_create(&SIDE_WING_POINTS);
  s_stripe = gpath_create(&STRIPE_POINTS); 
  s_left_win = gpath_create(&LEFT_WIN_POINTS); 
  s_right_win = gpath_create(&RIGHT_WIN_POINTS); 
  s_tip = gpath_create(&TIP_POINTS); 
  s_min_plan = gpath_create(&MIN_PLAN_POINTS); 
  s_hour_plan = gpath_create(&HOUR_PLAN_POINTS); 

  Layer *window_layer = window_get_root_layer(s_main_window); // Create the root layer of the window
  GRect bounds = layer_get_bounds(window_layer); // Set the bounds of that layer
  GPoint center = grect_center_point(&bounds); // Set the center of the layer
  
  // Move the objects to the center
  gpath_move_to(s_minute_arrow, center); 
  gpath_move_to(s_hour_arrow, center); 
  gpath_move_to(s_second_arrow, center); 
  gpath_move_to(s_wings, center); 
  gpath_move_to(s_flames, center); 
  gpath_move_to(s_side_wing, center); 
  gpath_move_to(s_stripe, center); 
  gpath_move_to(s_left_win, center); 
  gpath_move_to(s_right_win, center); 
  gpath_move_to(s_tip, center); 
  gpath_move_to(s_min_plan, center); 
  gpath_move_to(s_hour_plan, center); 

  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick); // Call to the handle_second_tick to update the watch every second
}

// Deinitialize the main window
static void deinit() {
  
  // Destroy the hand paths
  gpath_destroy(s_minute_arrow); 
  gpath_destroy(s_hour_arrow); 
  gpath_destroy(s_second_arrow); 
  gpath_destroy(s_wings);
  gpath_destroy(s_flames);
  gpath_destroy(s_side_wing);
  gpath_destroy(s_stripe);
  gpath_destroy(s_left_win);
  gpath_destroy(s_right_win);
  gpath_destroy(s_tip);
  gpath_destroy(s_min_plan);
  gpath_destroy(s_hour_plan);

  tick_timer_service_unsubscribe(); // Unsubscribe from the tick timer
  
  window_destroy(s_main_window); // Destroy the main window
}

int main() {
  init();
  app_event_loop();
  deinit();
}


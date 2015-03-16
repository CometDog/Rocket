/*
In this file, you map each point of the hand. A good way to do this is to draw the file in something like GIMP or 
Photoshop. Center the newly drawn hand in a 144x168 size file and then figure out the coordinates of the points 
by scrolling your cursor over top each point you want mapped. Then it is as simple as subtracting 72x84 from the 
points you just mapped to get the coordinates here. You can find that easily by saving the coordinates in a .csv 
file, opening it in Excel and using the following formula to get the points:
  =CONCATENATE("{ ", A1 - 72,", ", B1 - 84, " },")
Then you can just copy and paste the coordinates from Excel and you will get something like what follows. It does
not matter where you start or stop as long as you map all the points you map (don't map points twice)
*/

#pragma once

#include "pebble.h"

// Minute hand
static const GPathInfo MINUTE_HAND_POINTS = {
// Number of points that are going to be used
7,
  (GPoint []) {
    { 2, -6 },
    { 5, -50 },
    { 5, -58 },
    { 0, -74 },
    { -5, -58 },
    { -5, -50 },
    { -2, -6 }
  }
};

// Minute Planet
static const GPathInfo MIN_PLAN_POINTS = {
16,
  (GPoint []) {
    { -3, -38 },
    { 3, -38 },
    { 5, -39 },
    { 9, -43 },
    { 10, -45 },
    { 10, -51 },
    { 9, -53 },
    { 5, -57 },
    { 3, -58 },
    { -3, -58 },
    { -5, -57 },
    { -9, -53 },
    { -10, -51 },
    { -10, -45 },
    { -9, -43 },
    { -5, -39 }
  }
};

// Hour hand
static const GPathInfo HOUR_HAND_POINTS = {
// Number of points that are going to be used
7,
  (GPoint []) {
    { 2, -6 },
    { 5, -35 },
    { 5, -43 },
    { 0, -59 },
    { -5, -43 },
    { -5, -35 },
    { -2, -6 }
  }
};

// Hour planet
static const GPathInfo HOUR_PLAN_POINTS = {
16,
  (GPoint []) {
    { -3, -25 },
    { 3, -25 },
    { 5, -26 },
    { 8, -29 },
    { 9, -31 },
    { 9, -37 },
    { 8, -39 },
    { 5, -42 },
    { 3, -43 },
    { -3, -43 },
    { -5, -42 },
    { -8, -39 },
    { -9, -37 },
    { -9, -31 },
    { -8, -29 },
    { -5, -26 }
  }
};

// Second hand
static const GPathInfo SECOND_HAND_POINTS = {
// Number of points that are going to be used.
14,
  (GPoint []) {
    { -2, -65 },
    { 5, -65 },
    { 10, -66 },
    { 14, -67 },
    { 17, -68 },
    { 22, -71 },
    { 22, -72 },
    { 17, -75 },
    { 14, -76 },
    { 10, -77 },
    { 5, -78 },
    { -2, -78 },
    { -14, -74 },
    { -14, -69 }
  }
};

// Wings
static const GPathInfo WINGS_POINTS = {
10,
  (GPoint []) {
    { -19, -82 },
    { -13, -82 },
    { -5, -78 },
    { -5, -65 },
    { -13, -61 },
    { -19, -61 },
    { -19, -63 },
    { -11, -67 },
    { -11, -76 },
    { -19, -80 }
  }
};

// Flames
static const GPathInfo FLAMES_POINTS = {
8,
  (GPoint []) {
    { -14, -74 },
    { -14, -69 }, 
    { -17, -70 },
    { -19, -71 },
    { -22, -71 },
    { -22, -72 },
    { -18, -73 },
    { -16, -74 }
  }
};

// Side Wing
static const GPathInfo SIDE_WING_POINTS = {
6,
  (GPoint []) {
    { -11, -73 },
    { -9, -74 },
    { -4, -74 },
    { -4, -69 },
    { -9, -69 },
    { -11, -70 }
  }
};

// Stripe
static const GPathInfo STRIPE_POINTS = {
4,
  (GPoint []) {
    { -1, -78 },
    { 3, -78 },
    { 3, -65 },
    { -1, -65 }
  }
};

// Left Window
static const GPathInfo LEFT_WIN_POINTS = {
4,
  (GPoint []) {
    { 7, -74 },
    { 10, -74 },
    { 10, -71 },
    { 7, -71 }
  }
};

// Right Window
static const GPathInfo RIGHT_WIN_POINTS = {
4,
  (GPoint []) {
    { 12, -74 },
    { 15, -74 },
    { 15, -71 },
    { 12, -71 }
  }
};

// Tip
static const GPathInfo TIP_POINTS = {
4,  
  (GPoint []) {
    { 18, -74 },
    { 22, -72 },
    { 22, -71 },
    { 18, -69 }
  }
};
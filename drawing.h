// Credit to https://gist.github.com/bert/9bb403b01a3029b988938a7ce8217735

#ifndef __DRAWING_H
#define __DRAWING_H

#include <gtk/gtk.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>

#include "definitions.h"

//local constants
const int FRAME_RATE = 60;
const int WIDTH = 600;
const int HEIGHT = 600;
const char TITLE[] = "Drawing Example";
extern const unsigned NUM_FRAMES;
unsigned frame = 0;
extern unsigned const CALCULATIONS_PER_SECOND;

//local variables
extern unsigned numParticles;
extern Frame *buffer;
pthread_t drawing_thread;
pthread_mutex_t mutex;
cairo_surface_t *surface = NULL;
int surface_width;
int surface_height;
int status = 1;

//Local function prototypes
gboolean invalidate_cb(void*);
gboolean drawing_area_configure_cb(GtkWidget *, GdkEventConfigure *);
void drawing_area_draw_cb(GtkWidget*, cairo_t*, void*);
void* thread_draw();
void start_gtk();
void handle_sigint(int);

#endif

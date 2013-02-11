// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "filesystem_generator_window.h"
#include "cb_filesystem_generator_window.h"

#include "fl_dnd_box.h"

void filesystem_generator_window::cb_bt_cancel_i(Fl_Button* o, void*) {
  ((Fl_Window*)(o->parent()))->hide();
}
void filesystem_generator_window::cb_bt_cancel(Fl_Button* o, void* v) {
  ((filesystem_generator_window*)(o->parent()->user_data()))->cb_bt_cancel_i(o,v);
}

filesystem_generator_window::filesystem_generator_window() {
  { window = new Fl_Double_Window(704, 416, "Create a File System based floppy");
    window->user_data((void*)(this));
    { bt_injectdir = new Fl_Button(610, 20, 90, 25, "Create Disk");
      bt_injectdir->labelsize(12);
      bt_injectdir->callback((Fl_Callback*)filesystem_generator_window_bt_injectdir);
    } // Fl_Button* bt_injectdir
    { bt_cancel = new Fl_Button(610, 381, 90, 25, "Close");
      bt_cancel->labelsize(12);
      bt_cancel->callback((Fl_Callback*)cb_bt_cancel);
    } // Fl_Button* bt_cancel
    { choice_filesystype = new Fl_Choice(5, 20, 600, 25, "File system type :");
      choice_filesystype->down_box(FL_BORDER_BOX);
      choice_filesystype->labelsize(12);
      choice_filesystype->textsize(12);
      choice_filesystype->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Choice* choice_filesystype
    { fs_browser = new Fl_Tree(5, 60, 600, 310, "FS_Tree");
      fs_browser->labeltype(FL_NO_LABEL);
      fs_browser->callback((Fl_Callback*)filesystem_generator_window_browser_fs);
    } // Fl_Tree* fs_browser
    { txtout_freesize = new Fl_Text_Display(5, 380, 600, 29);
    } // Fl_Text_Display* txtout_freesize
    { bt_delete = new Fl_Button(610, 150, 90, 25, "Delete");
      bt_delete->callback((Fl_Callback*)filesystem_generator_window_bt_delete);
    } // Fl_Button* bt_delete
    { bt_get = new Fl_Button(610, 120, 90, 25, "Get Files");
      bt_get->callback((Fl_Callback*)filesystem_generator_window_bt_getfiles);
    } // Fl_Button* bt_get
    { bt_put = new Fl_Button(610, 90, 90, 25, "Put Files");
      bt_put->callback((Fl_Callback*)filesystem_generator_window_bt_putfiles);
    } // Fl_Button* bt_put
    { bt_createdir = new Fl_Button(610, 60, 90, 25, "Create Dir.");
      bt_createdir->callback((Fl_Callback*)filesystem_generator_window_bt_createdir);
    } // Fl_Button* bt_createdir

    Fl_DND_Box *o = new Fl_DND_Box(5, 60, 600, 310, 0);
    o->callback(dnd_fs_cb);

    window->end();
  } // Fl_Double_Window* window
}

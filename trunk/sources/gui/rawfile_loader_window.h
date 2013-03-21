// generated by Fast Light User Interface Designer (fluid) version 1.0300

#ifndef rawfile_loader_window_h
#define rawfile_loader_window_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Check_Button.H>
extern void raw_loader_window_datachanged(Fl_Widget*, void*);
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
extern void raw_loader_window_bt_loadrawfile(Fl_Button*, void*);
extern void raw_loader_window_bt_createemptyfloppy(Fl_Button*, void*);
extern void raw_loader_window_bt_savecfg(Fl_Button*, void*);
extern void raw_loader_window_bt_loadcfg(Fl_Button*, void*);
#include <FL/Fl_Choice.H>

class rawfile_loader_window {
public:
  rawfile_loader_window();
  Fl_Double_Window *window;
  Fl_Check_Button *chk_reversesides;
  Fl_Check_Button *chk_intersidesectornum;
  Fl_Check_Button *chk_side0track_first;
  Fl_Check_Button *chk_autogap3;
  Fl_Value_Input *numin_pregap;
  Fl_Value_Input *numin_formatvalue;
  Fl_Value_Input *numin_interleave;
  Fl_Value_Input *numin_skew;
  Fl_Check_Button *chk_sidebasedskew;
  Fl_Output *strout_totalsector;
  Fl_Output *strout_totalsize;
  Fl_Value_Input *innum_nbtrack;
  Fl_Value_Input *innum_sectoridstart;
  Fl_Value_Input *innum_sectorpertrack;
  Fl_Value_Input *innum_rpm;
  Fl_Value_Input *innum_bitrate;
private:
  inline void cb_Close_i(Fl_Button*, void*);
  static void cb_Close(Fl_Button*, void*);
public:
  Fl_Choice *choice_sectorsize;
  Fl_Choice *choice_tracktype;
  Fl_Value_Input *numin_gap3;
  Fl_Choice *choice_numberofside;
  Fl_Choice *choice_disklayout;
  Fl_Output *hlptxt;
};
#endif

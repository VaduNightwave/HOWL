//
// HOWL - Music-synced animation library
// File: TimelinePanel.h
// ©2018 Gooborg Studios: Vinyl Darkscratch, Light Apacha.
// http://www.gooborg.com
//

#pragma once

#ifdef USE_WXWIDGETS // Entire file requires wxWidgets

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/dcbuffer.h>
#include <wx/vscroll.h>

#include "GooCore/GooCore.h"
#include "Project.h"
#include "Layer.h"

namespace HOWL {
	// Timeline panel
	class EXPORT TimelinePanel: public wxHVScrolledWindow {
		public:
			TimelinePanel(wxPanel *parent, wxWindowID window_id, Project *project, wxWindowID eventTarget);
			~TimelinePanel();
			void setProject(Project *project);
			void setEventTarget(wxWindowID eventTarget);
			void paintEvent(wxPaintEvent &event);
			void paintNow();
			void refreshNow(wxCommandEvent &event);
			void onLeftDown(wxMouseEvent &event);
			void onMouseMove(wxMouseEvent &event);
			void onLeftUp(wxMouseEvent &event);
			void render(wxDC &canvas);
			void nextBeat();
			void nextQuarterBeat();
			void advanceCol(int cols);
			void movePlayhead(int time);
			void zoom(int percent);
			int getPlayhead();

		protected:
			wxCoord OnGetRowHeight(size_t row) const;
			wxCoord OnGetColumnWidth(size_t column) const;
			void render_header(wxDC &canvas);
			void render_header_segment(wxDC &canvas, int col, int xpos);
			void render_selection(wxDC &canvas, Selection sel);
			void render_row(wxDC &canvas, std::string rowname, KeyframeSet *keyframes, wxRect bounding_box);
			void render_playhead(wxDC &canvas);

			int playhead;
			int ticksPerCol;

		private:
			double colsPerBeat();
			int measureFromCol(int col);
			int beatFromCol(int col);
			int divFromCol(int col);
			int tickFromCol(int col);
			int playhead_in_pixels();
			wxPoint offset_in_pixels();
			wxPoint mousepos_to_buttons(wxPoint mousepos);
			wxPoint index_to_screenpos(wxPoint index);

			wxPanel *m_parent;
			wxBoxSizer *sizer;
			int rowsize;
			int colsize;
			int headersize;
			int labelsize;
			std::map<int, KeyframeSet *> visible_layers;
			bool headerclicked = false;
			Project *activeProject = NULL;
			wxWindowID eventTarget = NULL;
		
		wxDECLARE_EVENT_TABLE();
	};
	
	wxDECLARE_EVENT(DISPLAY_REFRESH, wxCommandEvent);
	wxDECLARE_EVENT(PLAYHEAD_MOVED, wxCommandEvent);
	wxDECLARE_EVENT(SELECTION_CHANGED, wxCommandEvent);
}

#endif

//
// HOWL - Music-synced animation library
// File: Selection.cpp
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.
// https://www.nightwave.co
//

#include "Selection.h"

#include <vector>

#include "Layer.h"

using namespace HOWL;

wxDEFINE_EVENT(HOWL::SELECTION_ON, HOWL::SelectionEvent);
wxDEFINE_EVENT(HOWL::SELECTION_OFF, HOWL::SelectionEvent);

// XXX Rename me to SelectionSet!
Selection::Selection() {
	clear();
}

Selection::Selection(Selection *other) {
	clear();
	sel = std::vector<SingleSelection *>(other->sel);
}

void Selection::clear() {
	sel.clear();
}

void Selection::add(KeyframeSet *set, long start, long end) {
	SingleSelection *newsel = new SingleSelection;
	newsel->set = set;
	newsel->start = start;
	newsel->end = end;
	sel.push_back(newsel);
}

void Selection::toggle(KeyframeSet *set, long start, long end) {
	// XXX Implement me!
}

bool Selection::matches(Keyframe *kf) {
	for (SingleSelection *s : sel) {
		if (s->set == NULL || !s->set) continue;
		if (s->set->name == kf->name
			&& s->start <= kf->time
			&& s->end > kf->time) return true;
	}
	
	return false;
}

SelectionEvent::SelectionEvent(wxEventType eventType, wxWindowID winid, SingleSelection selection) : wxEvent(winid, eventType), m_selection(selection) {
	
};

void SelectionEvent::SetSelection(SingleSelection selection) {
	m_selection = selection;
}

SingleSelection SelectionEvent::GetSelection() const {
	return m_selection;
}

wxEvent* SelectionEvent::Clone() const {
	return new SelectionEvent(*this);
}

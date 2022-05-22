///////////////////////////////////////////////////////////////////////////////
// Name:        wx/iconloc.h
// Purpose:     declaration of wxIconLocation class
// Author:      Vadim Zeitlin
// Modified by:
// Created:     21.06.2003
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_ICONLOC_H_
#define _WX_ICONLOC_H_

#include "wx/arrstr.h"

// ----------------------------------------------------------------------------
// wxIconLocation: describes the location of an icon
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_BASE wxIconLocationBase
{
public:
    // ctor takes the name of the file where the icon is
    explicit wxIconLocationBase(const wxString &filename = wxEmptyString,
            const wxArrayString &alternateFilenames = {}) :
            m_filename(filename), m_alternateFilenames(alternateFilenames)
    { }

    // default copy ctor, assignment operator and dtor are ok


    // returns true if this object is valid/initialized
    bool IsOk() const { return !m_filename.empty(); }

    // set/get the icon file name
    void SetFileName(const wxString& filename) { m_filename = filename; }
    const wxString& GetFileName() const { return m_filename; }

    void AddAlternateFileName(const wxString& alternateFilename) { m_alternateFilenames.Add(alternateFilename); }
    const wxArrayString& GetAlternateFileNames() const { return m_alternateFilenames; }

private:
    wxString m_filename;
    wxArrayString m_alternateFilenames;
};

// under Windows the same file may contain several icons so we also store the
// index of the icon
#if defined(__WINDOWS__)

class WXDLLIMPEXP_BASE wxIconLocation : public wxIconLocationBase
{
public:
    // ctor takes the name of the file where the icon is and the icons index in
    // the file
    explicit wxIconLocation(const wxString& file = wxEmptyString, int num = 0);

    // set/get the icon index
    void SetIndex(int num) { m_index = num; }
    int GetIndex() const { return m_index; }

private:
    int m_index;
};

inline
wxIconLocation::wxIconLocation(const wxString& file, int num)
              : wxIconLocationBase(file)
{
    SetIndex(num);
}

#else // !__WINDOWS__

// must be a class because we forward declare it as class
class WXDLLIMPEXP_BASE wxIconLocation : public wxIconLocationBase
{
public:
    explicit wxIconLocation(const wxString &filename = wxEmptyString,
            const wxArrayString &alternateFilenames = {}) :
            wxIconLocationBase(filename, alternateFilenames)
    { }
};

#endif // platform

#endif // _WX_ICONLOC_H_


/////////////////////////////////////////////////////////////////////////////
// Name:        src/gtk/mimetype.cpp
// Purpose:     classes and functions to manage MIME types
// Author:      Hans Mackowiak
// Created:     2016-06-05
// Copyright:   (c) 2016 Hans Mackowiak <hanmac@gmx.de>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#if wxUSE_MIMETYPE

#include "wx/gtk/mimetype.h"

#include "wx/gtk/private/wrapgtk.h"

#include "wx/gtk/private/string.h"
#include "wx/gtk/private/object.h"

#if defined(__UNIX__)
wxArrayString wxGTKMimeTypesManagerImpl::GetIconsFromMimeType(const wxString& mime)
{
    wxArrayString icons = wxArrayString();
#if GTK_CHECK_VERSION(2,14,0)
    if (!wx_is_at_least_gtk2(14))
        return icons;

    wxGtkString type(g_content_type_from_mime_type(mime.utf8_str()));

    wxGtkObject<GIcon> gicon(g_content_type_get_icon(type));
    if ( !gicon )
        return icons;

    GtkIconTheme *theme(gtk_icon_theme_get_default());
    if ( !theme )
        return icons;

    static const gint iconSizes[] = { 512, 96, 64, 48, 32, 24, 22, 16};
    for ( size_t i = 0; i < sizeof(iconSizes)/sizeof(iconSizes[0]); i++ )
    {
        // Notice that we can't use wxGtkObject here because a special function
        // needs to be used for freeing this object prior to GTK+ 3.8.
        GtkIconInfo* const giconinfo = gtk_icon_theme_lookup_by_gicon
                                       (
                                            theme,
                                            gicon,
                                            iconSizes[i],
                                            GTK_ICON_LOOKUP_NO_SVG
                                       );

        if ( giconinfo )
        {
            wxString icon = wxString::FromUTF8(gtk_icon_info_get_filename(giconinfo));
            if ( icons.Index(icon) == wxNOT_FOUND)
                icons.Add(icon);

            wxGCC_WARNING_SUPPRESS(deprecated-declarations)
            gtk_icon_info_free(giconinfo);
            wxGCC_WARNING_RESTORE()
        }
    }
#endif // GTK_CHECK_VERSION(2,14,0)
    return icons;
}
#endif // defined(__UNIX__)

wxMimeTypesManagerImpl *wxGTKMimeTypesManagerFactory::CreateMimeTypesManagerImpl()
{
    return new wxGTKMimeTypesManagerImpl();
}

#endif // wxUSE_MIMETYPE

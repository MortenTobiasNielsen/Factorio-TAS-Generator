#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "GUI_Base.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

/// <summary>
/// Class to handle changing shortcuts. Shortcuts are found in the 3rd menu point
/// </summary>
class ShortcutChanger : public Shortcut_changer
{
public:
	ShortcutChanger(wxWindow* parent,
        wxWindowID id = wxID_ANY, 
        const wxString& title = wxT("Change shortcuts"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP | wxBORDER_DEFAULT) : Shortcut_changer(parent, id, title, pos, size, style) {}
    ~ShortcutChanger() {}

    /// <summary>
    /// Builds the dialog box using the shortcut menu and settings file
    /// </summary>
    /// <param name="menu_shortcuts">Pointer to the shortcut menu, used to strip both their label and keybinding</param>
    void Build(wxMenu* menu_shortcuts);

    //entry string for settings json
    static inline const std::string shortcuts = "shortcuts";

    //filename for settings json
    static inline const std::string filename = "generator-settings.json";

    /// <summary>
    /// Gets the fully qualified named of settings json file
    /// </summary>
    /// <returns>The file name as a std::string</returns>
    static inline const std::string GetFile()
    {
        return (std::filesystem::current_path() / filename).string();
    }

    /// <summary>
    /// Used after building the GUI to update shortcuts from the settings file
    /// </summary>
    /// <param name="menu_shortcuts">The shortcut menu where the keybinds should be updated</param>
    static inline void UpdateShortcutsFromFile(wxMenu* menu_shortcuts)
    {
        using std::fstream;
        fstream file(GetFile(), fstream::in);
        try
        {
            json data = json::parse(file);
            for (auto [key, value] : data["shortcuts"].items())
            { 
                for (auto& a : menu_shortcuts->GetMenuItems())
                {
                    if (a->GetItemLabel().StartsWith(key))
                    {
                        a->SetItemLabel(key + wxT('\t') + std::string(value));
                    }
                }
            }
        }
        catch (...) { } // ignore all errors
    }

protected:
    wxMenu* menu;
    std::map<std::string, wxTextCtrl*> mapCtrl = {};
    json state;

    //Copies the settings json into the state json
    void extract(json savedata);
    //Create state json from the shortcut menu
    json DefaultShortcuts();

    //Event handler for closing the dialog, where the json state gets saved in settings file
    void OnCloseShortcutChanger(wxCloseEvent& event);

    void OnInitDialogShortcutChanger(wxInitDialogEvent& event);
    
    //Event handler for clicking reset. Resetting the input fields to the state json. 
    void OnButtonClickSCReset(wxCommandEvent& event);
    //Event handler for clicking the save button. Saving the values of the input fields to the state json and updates shortcut keybinds.
    void OnButtonClickSCSave(wxCommandEvent& event);
};

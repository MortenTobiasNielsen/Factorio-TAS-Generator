///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI_Base.h"

///////////////////////////////////////////////////////////////////////////

GUI_Base::GUI_Base( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_menubar1 = new wxMenuBar( 0 );
	menu_file = new wxMenu();
	wxMenuItem* menu_file_new;
	menu_file_new = new wxMenuItem( menu_file, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("CTRL+N"), wxEmptyString, wxITEM_NORMAL );
	menu_file->Append( menu_file_new );

	wxMenuItem* menu_file_open;
	menu_file_open = new wxMenuItem( menu_file, wxID_ANY, wxString( wxT("Open") ) + wxT('\t') + wxT("CTRL+O"), wxEmptyString, wxITEM_NORMAL );
	menu_file->Append( menu_file_open );

	wxMenuItem* menu_file_save;
	menu_file_save = new wxMenuItem( menu_file, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	menu_file->Append( menu_file_save );

	wxMenuItem* menu_file_save_as;
	menu_file_save_as = new wxMenuItem( menu_file, wxID_ANY, wxString( wxT("Save As") ) + wxT('\t') + wxT("CTRL+SHIFT+S"), wxEmptyString, wxITEM_NORMAL );
	menu_file->Append( menu_file_save_as );

	wxMenuItem* menu_file_exit;
	menu_file_exit = new wxMenuItem( menu_file, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	menu_file->Append( menu_file_exit );

	m_menubar1->Append( menu_file, wxT("File") );

	menu_script = new wxMenu();
	wxMenuItem* menu_script_choose_location;
	menu_script_choose_location = new wxMenuItem( menu_script, wxID_ANY, wxString( wxT("Choose Location") ) , wxEmptyString, wxITEM_NORMAL );
	menu_script->Append( menu_script_choose_location );

	wxMenuItem* menu_script_generate_script;
	menu_script_generate_script = new wxMenuItem( menu_script, wxID_ANY, wxString( wxT("Generate Script") ) + wxT('\t') + wxT("Alt+G"), wxEmptyString, wxITEM_NORMAL );
	menu_script->Append( menu_script_generate_script );

	wxMenuItem* menu_script_only_generate_steps;
	menu_script_only_generate_steps = new wxMenuItem( menu_script, wxID_ANY, wxString( wxT("Only Generate Steps File") ) , wxEmptyString, wxITEM_CHECK );
	menu_script->Append( menu_script_only_generate_steps );

	m_menubar1->Append( menu_script, wxT("Script") );

	menu_shortcuts = new wxMenu();
	wxMenuItem* shortcut_craft;
	shortcut_craft = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Craft") ) + wxT('\t') + wxT("Ctrl+1"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_craft );

	wxMenuItem* shortcut_walk;
	shortcut_walk = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Walk") ) + wxT('\t') + wxT("Ctrl+2"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_walk );

	wxMenuItem* shortcut_game_speed;
	shortcut_game_speed = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Game Speed") ) + wxT('\t') + wxT("Ctrl+3"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_game_speed );

	wxMenuItem* shortcut_rotate;
	shortcut_rotate = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Rotate") ) + wxT('\t') + wxT("Ctrl+4"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_rotate );

	wxMenuItem* shortcut_recipe;
	shortcut_recipe = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Recipe") ) + wxT('\t') + wxT("Ctrl+5"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_recipe );

	wxMenuItem* shortcut_stop;
	shortcut_stop = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Stop") ) + wxT('\t') + wxT("Ctrl+6"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_stop );

	wxMenuItem* shortcut_mine;
	shortcut_mine = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Mine") ) + wxT('\t') + wxT("Alt+1"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_mine );

	wxMenuItem* shortcut_build;
	shortcut_build = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Build") ) + wxT('\t') + wxT("Alt+2"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_build );

	wxMenuItem* shortcut_tech;
	shortcut_tech = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Tech") ) + wxT('\t') + wxT("Alt+3"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_tech );

	wxMenuItem* shortcut_take;
	shortcut_take = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Take") ) + wxT('\t') + wxT("Alt+4"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_take );

	wxMenuItem* shortcut_put;
	shortcut_put = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Put") ) + wxT('\t') + wxT("Alt+5"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_put );

	wxMenuItem* shortcut_idle;
	shortcut_idle = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Idle") ) + wxT('\t') + wxT("Alt+6"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_idle );

	wxMenuItem* shortcut_priority;
	shortcut_priority = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Priority") ) + wxT('\t') + wxT("Shift+1"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_priority );

	wxMenuItem* shortcut_limit;
	shortcut_limit = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Limit") ) + wxT('\t') + wxT("Shift+2"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_limit );

	wxMenuItem* shortcut_filter;
	shortcut_filter = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Filter") ) + wxT('\t') + wxT("Shift+3"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_filter );

	wxMenuItem* shortcut_pick_up;
	shortcut_pick_up = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Pick Up") ) + wxT('\t') + wxT("Shift+4"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_pick_up );

	wxMenuItem* shortcut_drop;
	shortcut_drop = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Drop") ) + wxT('\t') + wxT("Shift+5"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_drop );

	wxMenuItem* shortcut_launch;
	shortcut_launch = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Launch") ) + wxT('\t') + wxT("Shift+6"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_launch );

	wxMenuItem* shortcut_Save;
	shortcut_Save = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("Alt+Q"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_Save );

	wxMenuItem* shortcut_Start;
	shortcut_Start = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Start") ) + wxT('\t') + wxT("Alt+E"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_Start );

	wxMenuItem* shortcut_pause;
	shortcut_pause = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Pause") ) + wxT('\t') + wxT("Alt+R"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_pause );

	wxMenuItem* shortcut_add_step;
	shortcut_add_step = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Add Step") ) + wxT('\t') + wxT("Alt+A"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_add_step );

	wxMenuItem* shortcut_change_step;
	shortcut_change_step = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Change Step") ) + wxT('\t') + wxT("Alt+C"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_change_step );

	wxMenuItem* shortcut_delete_step;
	shortcut_delete_step = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Delete Step") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_delete_step );

	wxMenuItem* shortcut_move_up;
	shortcut_move_up = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Move Up") ) + wxT('\t') + wxT("Alt+W"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_move_up );

	wxMenuItem* shortcut_move_down;
	shortcut_move_down = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Move Down") ) + wxT('\t') + wxT("Alt+S"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_move_down );

	m_menubar1->Append( menu_shortcuts, wxT("Shortcuts") );

	menu_goals = new wxMenu();
	wxMenuItem* goal_steelaxe;
	goal_steelaxe = new wxMenuItem( menu_goals, wxID_ANY, wxString( wxT("Steel Axe") ) , wxEmptyString, wxITEM_RADIO );
	menu_goals->Append( goal_steelaxe );
	goal_steelaxe->Check( true );

	wxMenuItem* goal_GOTLAP;
	goal_GOTLAP = new wxMenuItem( menu_goals, wxID_ANY, wxString( wxT("Getting On Track Like A Pro") ) , wxEmptyString, wxITEM_RADIO );
	menu_goals->Append( goal_GOTLAP );

	wxMenuItem* goal_any_percent;
	goal_any_percent = new wxMenuItem( menu_goals, wxID_ANY, wxString( wxT("Any %") ) , wxEmptyString, wxITEM_RADIO );
	menu_goals->Append( goal_any_percent );

	wxMenuItem* goal_debug;
	goal_debug = new wxMenuItem( menu_goals, wxID_ANY, wxString( wxT("Debug") ) , wxEmptyString, wxITEM_RADIO );
	menu_goals->Append( goal_debug );

	m_menubar1->Append( menu_goals, wxT("Goal") );

	menu_auto_close = new wxMenu();
	wxMenuItem* auto_close_generate_script;
	auto_close_generate_script = new wxMenuItem( menu_auto_close, wxID_ANY, wxString( wxT("Generate Script") ) , wxEmptyString, wxITEM_CHECK );
	menu_auto_close->Append( auto_close_generate_script );
	auto_close_generate_script->Check( true );

	wxMenuItem* auto_close_open;
	auto_close_open = new wxMenuItem( menu_auto_close, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_CHECK );
	menu_auto_close->Append( auto_close_open );

	wxMenuItem* auto_close_save;
	auto_close_save = new wxMenuItem( menu_auto_close, wxID_ANY, wxString( wxT("Save") ) , wxEmptyString, wxITEM_CHECK );
	menu_auto_close->Append( auto_close_save );
	auto_close_save->Check( true );

	wxMenuItem* auto_close_save_as;
	auto_close_save_as = new wxMenuItem( menu_auto_close, wxID_ANY, wxString( wxT("Save As") ) , wxEmptyString, wxITEM_CHECK );
	menu_auto_close->Append( auto_close_save_as );

	m_menubar1->Append( menu_auto_close, wxT("Auto-close") );

	this->SetMenuBar( m_menubar1 );

	m_panel21 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel21, wxAuiPaneInfo() .Name( wxT("StepDetailPanel") ).Top() .Caption( wxT("Step detail") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 1010,155 ) ).BottomDockable( false ).LeftDockable( false ).RightDockable( false ).Row( 1 ).BestSize( wxSize( 650,140 ) ).MinSize( wxSize( 650,120 ) ).Layer( 1 ) );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	wxBoxSizer* bSizer1181;
	bSizer1181 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerX;
	bSizerX = new wxBoxSizer( wxHORIZONTAL );

	bSizerX->SetMinSize( wxSize( 10,10 ) );
	label_x_cord = new wxStaticText( m_panel21, wxID_ANY, wxT("X-Cord:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_x_cord->Wrap( -1 );
	bSizerX->Add( label_x_cord, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	spin_x = new wxSpinCtrlDouble( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT|wxSP_ARROW_KEYS, -1e+06, 1e+06, 0.000000, 1 );
	spin_x->SetDigits( 1 );
	spin_x->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	bSizerX->Add( spin_x, 0, wxALL, 5 );


	bSizer1181->Add( bSizerX, 1, 0, 5 );

	wxBoxSizer* bSizerY;
	bSizerY = new wxBoxSizer( wxHORIZONTAL );

	label_y_cord = new wxStaticText( m_panel21, wxID_ANY, wxT("Y-Cord:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_y_cord->Wrap( -1 );
	bSizerY->Add( label_y_cord, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spin_y = new wxSpinCtrlDouble( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT|wxSP_ARROW_KEYS, -1e+06, 1e+06, 0, 1 );
	spin_y->SetDigits( 1 );
	bSizerY->Add( spin_y, 0, wxALL, 5 );


	bSizer1181->Add( bSizerY, 1, 0, 5 );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	label_amount = new wxStaticText( m_panel21, wxID_ANY, wxT("Amount:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_amount->Wrap( -1 );
	bSizer36->Add( label_amount, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	spin_amount = new wxSpinCtrl( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_RIGHT|wxSP_ARROW_KEYS, 0, 1000000, 1 );
	bSizer36->Add( spin_amount, 0, wxALL, 5 );


	bSizer1181->Add( bSizer36, 1, 0, 5 );

	wxBoxSizer* bSizer361;
	bSizer361 = new wxBoxSizer( wxHORIZONTAL );

	label_comment = new wxStaticText( m_panel21, wxID_ANY, wxT("Comment:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_comment->Wrap( -1 );
	bSizer361->Add( label_comment, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txt_comment = new wxTextCtrl( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	bSizer361->Add( txt_comment, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1181->Add( bSizer361, 1, wxEXPAND, 5 );


	fgSizer2->Add( bSizer1181, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1191;
	bSizer1191 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	label_item = new wxStaticText( m_panel21, wxID_ANY, wxT("Item:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_item->Wrap( -1 );
	bSizer35->Add( label_item, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_item = new wxComboBox( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_item->SetMinSize( wxSize( 150,-1 ) );

	bSizer35->Add( cmb_item, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1191->Add( bSizer35, 1, 0, 5 );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );

	label_from_into = new wxStaticText( m_panel21, wxID_ANY, wxT("From:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_from_into->Wrap( -1 );
	bSizer31->Add( label_from_into, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_from_into = new wxComboBox( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_from_into->SetSelection( 0 );
	cmb_from_into->SetMinSize( wxSize( 150,-1 ) );

	bSizer31->Add( cmb_from_into, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer1191->Add( bSizer31, 1, 0, 5 );

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxHORIZONTAL );

	label_input = new wxStaticText( m_panel21, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_input->Wrap( -1 );
	bSizer47->Add( label_input, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString radio_inputChoices[] = { wxT("Left"), wxT("None"), wxT("Right") };
	int radio_inputNChoices = sizeof( radio_inputChoices ) / sizeof( wxString );
	radio_input = new wxRadioBox( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, radio_inputNChoices, radio_inputChoices, 3, wxRA_SPECIFY_COLS );
	radio_input->SetSelection( 1 );
	radio_input->SetFont( wxFont( 6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	radio_input->SetMinSize( wxSize( 150,-1 ) );

	bSizer47->Add( radio_input, 0, wxLEFT|wxRIGHT, 5 );


	bSizer1191->Add( bSizer47, 1, 0, 5 );

	wxBoxSizer* bSizer471;
	bSizer471 = new wxBoxSizer( wxHORIZONTAL );

	label_output = new wxStaticText( m_panel21, wxID_ANY, wxT("Output:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_output->Wrap( -1 );
	bSizer471->Add( label_output, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString radio_outputChoices[] = { wxT("Left"), wxT("None"), wxT("Right") };
	int radio_outputNChoices = sizeof( radio_outputChoices ) / sizeof( wxString );
	radio_output = new wxRadioBox( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, radio_outputNChoices, radio_outputChoices, 3, wxRA_SPECIFY_COLS );
	radio_output->SetSelection( 1 );
	radio_output->SetFont( wxFont( 6, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	radio_output->SetMinSize( wxSize( 150,-1 ) );

	bSizer471->Add( radio_output, 0, wxLEFT|wxRIGHT, 5 );


	bSizer1191->Add( bSizer471, 1, wxEXPAND, 5 );


	fgSizer2->Add( bSizer1191, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );

	label_building_orientation = new wxStaticText( m_panel21, wxID_ANY, wxT("Building orientation:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_building_orientation->Wrap( -1 );
	bSizer58->Add( label_building_orientation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_building_orientation = new wxComboBox( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0, NULL, 0 );
	cmb_building_orientation->SetToolTip( wxT("The orientation of the building. Inserters are reversed.") );

	bSizer58->Add( cmb_building_orientation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer120->Add( bSizer58, 1, 0, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );

	label_direction_to_build = new wxStaticText( m_panel21, wxID_ANY, wxT("Build direction:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_direction_to_build->Wrap( -1 );
	bSizer59->Add( label_direction_to_build, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_direction_to_build = new wxComboBox( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0, NULL, 0 );
	cmb_direction_to_build->SetToolTip( wxT("The direction to place the next building") );

	bSizer59->Add( cmb_direction_to_build, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer120->Add( bSizer59, 1, 0, 5 );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	label_building_size = new wxStaticText( m_panel21, wxID_ANY, wxT("Building size:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_building_size->Wrap( -1 );
	bSizer51->Add( label_building_size, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	spin_building_size = new wxSpinCtrl( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxSP_ARROW_KEYS, 1, 10, 1 );
	spin_building_size->SetToolTip( wxT("Number of tiles the building is wide. Used for placing multiple buildings in a row.") );
	spin_building_size->SetMinSize( wxSize( 80,-1 ) );

	bSizer51->Add( spin_building_size, 0, wxALL, 5 );


	bSizer120->Add( bSizer51, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxHORIZONTAL );

	label_amount_of_buildings = new wxStaticText( m_panel21, wxID_ANY, wxT("Amount of Buildings:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_amount_of_buildings->Wrap( -1 );
	bSizer52->Add( label_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	spin_building_amount = new wxSpinCtrl( m_panel21, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxSP_ARROW_KEYS, 1, 250, 1 );
	spin_building_amount->SetToolTip( wxT("The number of buildings to place in a row") );
	spin_building_amount->SetMinSize( wxSize( 80,-1 ) );

	bSizer52->Add( spin_building_amount, 0, wxALL, 5 );


	bSizer120->Add( bSizer52, 1, wxEXPAND, 5 );


	fgSizer2->Add( bSizer120, 1, wxEXPAND, 5 );


	bSizer19->Add( fgSizer2, 1, wxEXPAND, 5 );


	m_panel21->SetSizer( bSizer19 );
	m_panel21->Layout();
	bSizer19->Fit( m_panel21 );
	type_panel = new TypePanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	m_mgr.AddPane( type_panel, wxAuiPaneInfo() .Name( wxT("StepTypePanel") ).Top() .Caption( wxT("Step type") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 700,150 ) ).BottomDockable( false ).LeftDockable( false ).RightDockable( false ).Row( 1 ).BestSize( wxSize( 620,140 ) ).MinSize( wxSize( 620,120 ) ).Layer( 1 ) );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 3, 7, 15, 15 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );

	rbtn_take = new wxRadioButton( type_panel, wxID_ANY, wxT("Take"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer42->Add( rbtn_take, 0, wxALL, 5 );


	fgSizer3->Add( bSizer42, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	rbtn_put = new wxRadioButton( type_panel, wxID_ANY, wxT("Put"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( rbtn_put, 0, wxALL, 5 );


	fgSizer3->Add( bSizer11, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	rbtn_game_speed = new wxRadioButton( type_panel, wxID_ANY, wxT("Game Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( rbtn_game_speed, 0, wxALL, 5 );


	fgSizer3->Add( bSizer17, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );

	rbtn_craft = new wxRadioButton( type_panel, wxID_ANY, wxT("Craft"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( rbtn_craft, 0, wxALL, 5 );


	fgSizer3->Add( bSizer39, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	rbtn_walk = new wxRadioButton( type_panel, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( rbtn_walk, 0, wxALL, 5 );


	fgSizer3->Add( bSizer15, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	rbtn_mine = new wxRadioButton( type_panel, wxID_ANY, wxT("Mine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( rbtn_mine, 0, wxALL, 5 );


	fgSizer3->Add( bSizer12, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	rbtn_start = new wxRadioButton( type_panel, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( rbtn_start, 0, wxALL, 5 );


	fgSizer3->Add( bSizer121, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	rbtn_build = new wxRadioButton( type_panel, wxID_ANY, wxT("Build"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( rbtn_build, 0, wxALL, 5 );


	fgSizer3->Add( bSizer16, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );

	rbtn_recipe = new wxRadioButton( type_panel, wxID_ANY, wxT("Recipe"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer64->Add( rbtn_recipe, 0, wxALL, 5 );


	fgSizer3->Add( bSizer64, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxVERTICAL );

	rbtn_tech = new wxRadioButton( type_panel, wxID_ANY, wxT("Tech"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer63->Add( rbtn_tech, 0, wxALL, 5 );


	fgSizer3->Add( bSizer63, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );

	rbtn_limit = new wxRadioButton( type_panel, wxID_ANY, wxT("Limit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( rbtn_limit, 0, wxALL, 5 );


	fgSizer3->Add( bSizer40, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer431;
	bSizer431 = new wxBoxSizer( wxVERTICAL );

	rbtn_idle = new wxRadioButton( type_panel, wxID_ANY, wxT("Idle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer431->Add( rbtn_idle, 0, wxALL, 5 );


	fgSizer3->Add( bSizer431, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );

	rbtn_filter = new wxRadioButton( type_panel, wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( rbtn_filter, 0, wxALL, 5 );


	fgSizer3->Add( bSizer65, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );

	rbtn_pause = new wxRadioButton( type_panel, wxID_ANY, wxT("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer141->Add( rbtn_pause, 0, wxALL, 5 );


	fgSizer3->Add( bSizer141, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	rbtn_priority = new wxRadioButton( type_panel, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( rbtn_priority, 0, wxALL, 5 );


	fgSizer3->Add( bSizer9, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	rbtn_rotate = new wxRadioButton( type_panel, wxID_ANY, wxT("Rotate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( rbtn_rotate, 0, wxALL, 5 );


	fgSizer3->Add( bSizer13, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );

	rbtn_pick_up = new wxRadioButton( type_panel, wxID_ANY, wxT("Pick Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( rbtn_pick_up, 0, wxALL, 5 );


	fgSizer3->Add( bSizer41, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer441;
	bSizer441 = new wxBoxSizer( wxVERTICAL );

	rbtn_drop = new wxRadioButton( type_panel, wxID_ANY, wxT("Drop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer441->Add( rbtn_drop, 0, wxALL, 5 );


	fgSizer3->Add( bSizer441, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	rbtn_launch = new wxRadioButton( type_panel, wxID_ANY, wxT("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( rbtn_launch, 0, wxALL, 5 );


	fgSizer3->Add( bSizer14, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1411;
	bSizer1411 = new wxBoxSizer( wxVERTICAL );

	rbtn_save = new wxRadioButton( type_panel, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1411->Add( rbtn_save, 0, wxALL, 5 );


	fgSizer3->Add( bSizer1411, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	rbtn_stop = new wxRadioButton( type_panel, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( rbtn_stop, 0, wxALL, 5 );


	fgSizer3->Add( bSizer8, 1, wxEXPAND, 5 );


	bSizer18->Add( fgSizer3, 1, wxEXPAND|wxLEFT|wxRIGHT, 15 );


	type_panel->SetSizer( bSizer18 );
	type_panel->Layout();
	bSizer18->Fit( type_panel );
	m_panel23 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_panel23, wxAuiPaneInfo() .Name( wxT("AutoPutPanel") ).Top() .Caption( wxT("Auto put") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 300,150 ) ).BottomDockable( false ).LeftDockable( false ).RightDockable( false ).Row( 1 ).BestSize( wxSize( 200,140 ) ).MinSize( wxSize( 100,120 ) ).MaxSize( wxSize( 300,180 ) ).Layer( 1 ) );

	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 4, 1, 5, 15 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	check_furnace = new wxCheckBox( m_panel23, wxID_ANY, wxT("Furnace"), wxDefaultPosition, wxDefaultSize, 0 );
	check_furnace->SetValue(true);
	check_furnace->SetToolTip( wxT("Adds a step to put coal into stone and steel furnaces") );

	fgSizer4->Add( check_furnace, 0, wxALL, 5 );

	check_burner = new wxCheckBox( m_panel23, wxID_ANY, wxT("Burner"), wxDefaultPosition, wxDefaultSize, 0 );
	check_burner->SetValue(true);
	check_burner->SetToolTip( wxT("Adds a step to put coal into Burner Mining Drills, Burner Inserters and Boilers") );

	fgSizer4->Add( check_burner, 0, wxALL, 5 );

	check_lab = new wxCheckBox( m_panel23, wxID_ANY, wxT("Lab"), wxDefaultPosition, wxDefaultSize, 0 );
	check_lab->SetValue(true);
	check_lab->SetToolTip( wxT("Adds a step to put automation science into the Lab") );

	fgSizer4->Add( check_lab, 0, wxALL, 5 );

	check_recipe = new wxCheckBox( m_panel23, wxID_ANY, wxT("Recipe"), wxDefaultPosition, wxDefaultSize, 0 );
	check_recipe->SetValue(true);
	check_recipe->SetToolTip( wxT("Add steps to put the items needed to craft that recipe") );

	fgSizer4->Add( check_recipe, 0, wxALL, 5 );


	bSizer116->Add( fgSizer4, 1, wxLEFT|wxRIGHT, 5 );


	m_panel23->SetSizer( bSizer116 );
	m_panel23->Layout();
	bSizer116->Fit( m_panel23 );
	m_auinotebook1 = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_TAB_EXTERNAL_MOVE|wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TOP|wxAUI_NB_WINDOWLIST_BUTTON|wxBORDER_RAISED );
	m_mgr.AddPane( m_auinotebook1, wxAuiPaneInfo() .Name( wxT("DataBook") ).Center() .Caption( wxT("Book") ).CaptionVisible( false ).CloseButton( false ).MaximizeButton( true ).MinimizeButton( true ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).Row( 2 ).MinSize( wxSize( 500,500 ) ).Layer( 2 ).CentrePane() );

	group_panel = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer561;
	bSizer561 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxVERTICAL );

	bSizer118->SetMinSize( wxSize( 710,-1 ) );
	wxBoxSizer* bSizer1261;
	bSizer1261 = new wxBoxSizer( wxHORIZONTAL );

	label_choose_group = new wxStaticText( group_panel, wxID_ANY, wxT("Choose Group:"), wxDefaultPosition, wxSize( 95,-1 ), wxALIGN_LEFT );
	label_choose_group->Wrap( -1 );
	bSizer1261->Add( label_choose_group, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_choose_group = new wxComboBox( group_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_choose_group->SetMinSize( wxSize( 150,-1 ) );

	bSizer1261->Add( cmb_choose_group, 0, wxALIGN_CENTER|wxALL, 5 );

	btn_new_group = new wxButton( group_panel, wxID_ANY, wxT("New Group"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer1261->Add( btn_new_group, 0, wxALL, 5 );

	btn_group_delete = new wxButton( group_panel, wxID_ANY, wxT("Delete Group"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer1261->Add( btn_group_delete, 0, wxALL, 5 );


	bSizer118->Add( bSizer1261, 1, wxALIGN_LEFT, 5 );

	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxHORIZONTAL );

	btn_group_change_step = new wxButton( group_panel, wxID_ANY, wxT("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_group_change_step, 0, wxALL, 5 );

	btn_group_delete_step = new wxButton( group_panel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_group_delete_step, 0, wxALL, 5 );

	btn_group_move_up = new wxButton( group_panel, wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_group_move_up, 0, wxALL, 5 );

	btn_gorup_move_down = new wxButton( group_panel, wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_gorup_move_down, 0, wxALL, 5 );


	bSizer118->Add( bSizer100, 1, wxALIGN_LEFT, 5 );


	bSizer114->Add( bSizer118, 1, wxEXPAND, 5 );

	m_staticline5 = new wxStaticLine( group_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer114->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxVERTICAL );

	btn_group_add_to_steps_list = new wxButton( group_panel, wxID_ANY, wxT("Add to steps list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer119->Add( btn_group_add_to_steps_list, 0, wxALL, 5 );

	btn_group_add_from_steps_list = new wxButton( group_panel, wxID_ANY, wxT("Add from steps list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer119->Add( btn_group_add_from_steps_list, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer114->Add( bSizer119, 0, 0, 5 );


	bSizer561->Add( bSizer114, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );

	grid_group = new wxGrid( group_panel, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );

	// Grid
	grid_group->CreateGrid( 0, 10 );
	grid_group->EnableEditing( false );
	grid_group->EnableGridLines( true );
	grid_group->EnableDragGridSize( false );
	grid_group->SetMargins( 0, 0 );

	// Columns
	grid_group->SetColSize( 0, 75 );
	grid_group->SetColSize( 1, 59 );
	grid_group->SetColSize( 2, 59 );
	grid_group->SetColSize( 3, 50 );
	grid_group->SetColSize( 4, 150 );
	grid_group->SetColSize( 5, 70 );
	grid_group->SetColSize( 6, 70 );
	grid_group->SetColSize( 7, 50 );
	grid_group->SetColSize( 8, 60 );
	grid_group->SetColSize( 9, 140 );
	grid_group->EnableDragColMove( false );
	grid_group->EnableDragColSize( true );
	grid_group->SetColLabelValue( 0, wxT("Step") );
	grid_group->SetColLabelValue( 1, wxT("X-cord") );
	grid_group->SetColLabelValue( 2, wxT("Y-cord") );
	grid_group->SetColLabelValue( 3, wxT("Amount") );
	grid_group->SetColLabelValue( 4, wxT("Item") );
	grid_group->SetColLabelValue( 5, wxT("Orientation") );
	grid_group->SetColLabelValue( 6, wxT("Direction") );
	grid_group->SetColLabelValue( 7, wxT("Size") );
	grid_group->SetColLabelValue( 8, wxT("Buildings") );
	grid_group->SetColLabelValue( 9, wxT("Comment") );
	grid_group->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_group->EnableDragRowSize( false );
	grid_group->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	grid_group->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_group->SetMinSize( wxSize( 860,1500 ) );

	bSizer50->Add( grid_group, 1, wxALL|wxEXPAND, 5 );


	bSizer561->Add( bSizer50, 1, wxEXPAND, 5 );


	group_panel->SetSizer( bSizer561 );
	group_panel->Layout();
	bSizer561->Fit( group_panel );
	m_auinotebook1->AddPage( group_panel, wxT("Groups"), false, wxNullBitmap );
	template_panel = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5612;
	bSizer5612 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer103;
	bSizer103 = new wxBoxSizer( wxVERTICAL );

	bSizer103->SetMinSize( wxSize( 612,-1 ) );
	wxBoxSizer* bSizer126;
	bSizer126 = new wxBoxSizer( wxHORIZONTAL );

	label_choose_template = new wxStaticText( template_panel, wxID_ANY, wxT("Choose Template:"), wxDefaultPosition, wxSize( 95,-1 ), 0 );
	label_choose_template->Wrap( -1 );
	bSizer126->Add( label_choose_template, 0, wxALIGN_CENTER|wxALL, 5 );

	cmb_choose_template = new wxComboBox( template_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	cmb_choose_template->SetMinSize( wxSize( 150,-1 ) );

	bSizer126->Add( cmb_choose_template, 0, wxALIGN_CENTER|wxALL, 5 );

	btn_template_new = new wxButton( template_panel, wxID_ANY, wxT("New Template"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer126->Add( btn_template_new, 0, wxALL, 5 );

	btn_template_delete = new wxButton( template_panel, wxID_ANY, wxT("Delete Template"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer126->Add( btn_template_delete, 0, wxALL, 5 );


	bSizer103->Add( bSizer126, 1, wxALIGN_LEFT, 5 );

	wxBoxSizer* bSizer1002;
	bSizer1002 = new wxBoxSizer( wxHORIZONTAL );

	btn_template_change_step = new wxButton( template_panel, wxID_ANY, wxT("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_change_step, 0, wxALL, 5 );

	btn_template_delete_step = new wxButton( template_panel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_delete_step, 0, wxALL, 5 );

	btn_template_move_up_step = new wxButton( template_panel, wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_move_up_step, 0, wxALL, 5 );

	btn_template_move_down_step = new wxButton( template_panel, wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_move_down_step, 0, wxALL, 5 );


	bSizer103->Add( bSizer1002, 1, wxALIGN_LEFT, 5 );


	bSizer102->Add( bSizer103, 1, 0, 5 );

	m_staticline51 = new wxStaticLine( template_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer102->Add( m_staticline51, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer1041;
	bSizer1041 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1051;
	bSizer1051 = new wxBoxSizer( wxHORIZONTAL );

	btn_template_add_to_steps_list = new wxButton( template_panel, wxID_ANY, wxT("Add to steps list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer1051->Add( btn_template_add_to_steps_list, 0, wxALL, 5 );


	bSizer1041->Add( bSizer1051, 1, 0, 5 );

	wxBoxSizer* bSizer1061;
	bSizer1061 = new wxBoxSizer( wxHORIZONTAL );

	btn_template_add_from_steps_list = new wxButton( template_panel, wxID_ANY, wxT("Add from steps list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer1061->Add( btn_template_add_from_steps_list, 0, wxALL, 5 );


	bSizer1041->Add( bSizer1061, 1, 0, 5 );


	bSizer102->Add( bSizer1041, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1042;
	bSizer1042 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1052;
	bSizer1052 = new wxBoxSizer( wxHORIZONTAL );

	label_template_amount_offset = new wxStaticText( template_panel, wxID_ANY, wxT("Amount-Offset:"), wxDefaultPosition, wxSize( 85,-1 ), 0 );
	label_template_amount_offset->Wrap( -1 );
	bSizer1052->Add( label_template_amount_offset, 0, wxALIGN_CENTER, 5 );

	spin_amount_offset = new wxSpinCtrl( template_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer1052->Add( spin_amount_offset, 0, wxALL, 5 );


	bSizer1042->Add( bSizer1052, 1, 0, 5 );

	wxBoxSizer* bSizer1062;
	bSizer1062 = new wxBoxSizer( wxHORIZONTAL );

	label_template_amount_multiplier = new wxStaticText( template_panel, wxID_ANY, wxT("Amount-Multi:"), wxDefaultPosition, wxSize( 85,-1 ), 0 );
	label_template_amount_multiplier->Wrap( -1 );
	bSizer1062->Add( label_template_amount_multiplier, 0, wxALIGN_CENTER, 5 );

	spin_amount_multiplier = new wxSpinCtrl( template_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer1062->Add( spin_amount_multiplier, 0, wxALL, 5 );


	bSizer1042->Add( bSizer1062, 1, 0, 5 );


	bSizer102->Add( bSizer1042, 0, 0, 5 );

	wxBoxSizer* bSizer104;
	bSizer104 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxHORIZONTAL );

	label_template_x_offset = new wxStaticText( template_panel, wxID_ANY, wxT("X-Offset:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	label_template_x_offset->Wrap( -1 );
	bSizer105->Add( label_template_x_offset, 0, wxALIGN_CENTER, 5 );

	spin_x_offset = new wxSpinCtrl( template_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer105->Add( spin_x_offset, 0, wxALL, 5 );


	bSizer104->Add( bSizer105, 1, 0, 5 );

	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxHORIZONTAL );

	label_template_y_offset = new wxStaticText( template_panel, wxID_ANY, wxT("Y-Offset:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	label_template_y_offset->Wrap( -1 );
	bSizer106->Add( label_template_y_offset, 0, wxALIGN_CENTER, 5 );

	spin_y_offset = new wxSpinCtrl( template_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, -10000, 10000, 0 );
	bSizer106->Add( spin_y_offset, 0, wxALL, 5 );


	bSizer104->Add( bSizer106, 1, 0, 5 );


	bSizer102->Add( bSizer104, 0, 0, 5 );


	bSizer5612->Add( bSizer102, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer502;
	bSizer502 = new wxBoxSizer( wxVERTICAL );

	grid_template = new wxGrid( template_panel, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );

	// Grid
	grid_template->CreateGrid( 0, 10 );
	grid_template->EnableEditing( false );
	grid_template->EnableGridLines( true );
	grid_template->EnableDragGridSize( false );
	grid_template->SetMargins( 0, 0 );

	// Columns
	grid_template->SetColSize( 0, 75 );
	grid_template->SetColSize( 1, 59 );
	grid_template->SetColSize( 2, 59 );
	grid_template->SetColSize( 3, 50 );
	grid_template->SetColSize( 4, 150 );
	grid_template->SetColSize( 5, 70 );
	grid_template->SetColSize( 6, 70 );
	grid_template->SetColSize( 7, 50 );
	grid_template->SetColSize( 8, 60 );
	grid_template->SetColSize( 9, 140 );
	grid_template->EnableDragColMove( false );
	grid_template->EnableDragColSize( true );
	grid_template->SetColLabelValue( 0, wxT("Step") );
	grid_template->SetColLabelValue( 1, wxT("X-cord") );
	grid_template->SetColLabelValue( 2, wxT("Y-cord") );
	grid_template->SetColLabelValue( 3, wxT("Amount") );
	grid_template->SetColLabelValue( 4, wxT("Item") );
	grid_template->SetColLabelValue( 5, wxT("Orientation") );
	grid_template->SetColLabelValue( 6, wxT("Direction") );
	grid_template->SetColLabelValue( 7, wxT("Size") );
	grid_template->SetColLabelValue( 8, wxT("Buildings") );
	grid_template->SetColLabelValue( 9, wxT("Comment") );
	grid_template->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_template->EnableDragRowSize( false );
	grid_template->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	grid_template->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_template->SetMinSize( wxSize( 860,2500 ) );

	bSizer502->Add( grid_template, 0, wxALL|wxEXPAND, 5 );


	bSizer5612->Add( bSizer502, 1, wxEXPAND, 5 );


	template_panel->SetSizer( bSizer5612 );
	template_panel->Layout();
	bSizer5612->Fit( template_panel );
	m_auinotebook1->AddPage( template_panel, wxT("Templates"), false, wxNullBitmap );
	step_panel = new wxPanel( m_auinotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5611;
	bSizer5611 = new wxBoxSizer( wxVERTICAL );


	bSizer5611->Add( 0, 33, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1001;
	bSizer1001 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxHORIZONTAL );

	step_search_ctrl = new wxSearchCtrl( step_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	step_search_ctrl->ShowSearchButton( true );
	#endif
	step_search_ctrl->ShowCancelButton( true );
	bSizer113->Add( step_search_ctrl, 0, wxALL, 5 );

	btn_add_step = new wxButton( step_panel, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( btn_add_step, 0, wxALIGN_CENTER|wxALL, 5 );

	btn_change_step = new wxButton( step_panel, wxID_ANY, wxT("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( btn_change_step, 0, wxALL, 5 );

	btn_delete_step = new wxButton( step_panel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( btn_delete_step, 0, wxALL, 5 );

	btn_move_up = new wxButton( step_panel, wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxDefaultSize, 0 );
	btn_move_up->SetToolTip( wxT("Right-click to move 5 but be patient") );

	bSizer113->Add( btn_move_up, 0, wxALL, 5 );

	btn_move_down = new wxButton( step_panel, wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxDefaultSize, 0 );
	btn_move_down->SetToolTip( wxT("Right-click to move 5 but be patient") );

	bSizer113->Add( btn_move_down, 0, wxALL, 5 );


	bSizer1001->Add( bSizer113, 1, wxEXPAND, 5 );


	bSizer5611->Add( bSizer1001, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer501;
	bSizer501 = new wxBoxSizer( wxVERTICAL );

	grid_steps = new wxGrid( step_panel, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );

	// Grid
	grid_steps->CreateGrid( 0, 10 );
	grid_steps->EnableEditing( false );
	grid_steps->EnableGridLines( true );
	grid_steps->EnableDragGridSize( false );
	grid_steps->SetMargins( 0, 0 );

	// Columns
	grid_steps->SetColSize( 0, 75 );
	grid_steps->SetColSize( 1, 59 );
	grid_steps->SetColSize( 2, 59 );
	grid_steps->SetColSize( 3, 58 );
	grid_steps->SetColSize( 4, 150 );
	grid_steps->SetColSize( 5, 70 );
	grid_steps->SetColSize( 6, 70 );
	grid_steps->SetColSize( 7, 50 );
	grid_steps->SetColSize( 8, 60 );
	grid_steps->SetColSize( 9, 140 );
	grid_steps->EnableDragColMove( false );
	grid_steps->EnableDragColSize( true );
	grid_steps->SetColLabelValue( 0, wxT("Step") );
	grid_steps->SetColLabelValue( 1, wxT("X-cord") );
	grid_steps->SetColLabelValue( 2, wxT("Y-cord") );
	grid_steps->SetColLabelValue( 3, wxT("Amount") );
	grid_steps->SetColLabelValue( 4, wxT("Item") );
	grid_steps->SetColLabelValue( 5, wxT("Orientation") );
	grid_steps->SetColLabelValue( 6, wxT("Direction") );
	grid_steps->SetColLabelValue( 7, wxT("Size") );
	grid_steps->SetColLabelValue( 8, wxT("Buildings") );
	grid_steps->SetColLabelValue( 9, wxT("Comment") );
	grid_steps->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_steps->EnableDragRowSize( false );
	grid_steps->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance
	grid_steps->SetLabelTextColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );

	// Cell Defaults
	grid_steps->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_steps->SetMinSize( wxSize( 860,2500 ) );

	bSizer501->Add( grid_steps, 0, wxALL|wxEXPAND, 5 );


	bSizer5611->Add( bSizer501, 1, wxEXPAND, 5 );


	step_panel->SetSizer( bSizer5611 );
	step_panel->Layout();
	bSizer5611->Fit( step_panel );
	m_auinotebook1->AddPage( step_panel, wxT("Steps"), true, wxNullBitmap );


	m_mgr.Update();
	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUI_Base::OnApplicationClose ) );
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuNew ), this, menu_file_new->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuOpen ), this, menu_file_open->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuSave ), this, menu_file_save->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuSaveAs ), this, menu_file_save_as->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuExit ), this, menu_file_exit->GetId());
	menu_script->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnChooseLocation ), this, menu_script_choose_location->GetId());
	menu_script->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnGenerateScript ), this, menu_script_generate_script->GetId());
	menu_script->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnOnlyGenerateSteps ), this, menu_script_only_generate_steps->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnCraftMenuSelected ), this, shortcut_craft->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnWalkMenuSelected ), this, shortcut_walk->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnGameSpeedMenuSelected ), this, shortcut_game_speed->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnRotateMenuSelected ), this, shortcut_rotate->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnRecipeMenuChosen ), this, shortcut_recipe->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnStopMenuSelected ), this, shortcut_stop->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMineMenuSelected ), this, shortcut_mine->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnBuildMenuSelected ), this, shortcut_build->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnTechMenuSelected ), this, shortcut_tech->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnTakeMenuSelected ), this, shortcut_take->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnPutMenuSelected ), this, shortcut_put->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnIdleMenuSelected ), this, shortcut_idle->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnPriorityMenuSelected ), this, shortcut_priority->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnLimitMenuSelected ), this, shortcut_limit->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnFilterMenuSelected ), this, shortcut_filter->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnPickUpMenuSelected ), this, shortcut_pick_up->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnDropMenuSelected ), this, shortcut_drop->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnLaunchMenuSelected ), this, shortcut_launch->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnSaveMenuSelected ), this, shortcut_Save->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnStartMenuSelected ), this, shortcut_Start->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnPauseMenuSelected ), this, shortcut_pause->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnAddMenuSelected ), this, shortcut_add_step->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnChangeMenuSelected ), this, shortcut_change_step->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnDeleteMenuSelected ), this, shortcut_delete_step->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMoveUpMenuSelected ), this, shortcut_move_up->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMoveDownMenuSelected ), this, shortcut_move_down->GetId());
	menu_goals->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuSteelAxeClicked ), this, goal_steelaxe->GetId());
	menu_goals->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuGOTLAPClicked ), this, goal_GOTLAP->GetId());
	menu_goals->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuAnyPercentClicked ), this, goal_any_percent->GetId());
	menu_goals->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuDebugClicked ), this, goal_debug->GetId());
	menu_auto_close->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuAutoCloseGenerateScriptClicked ), this, auto_close_generate_script->GetId());
	menu_auto_close->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuAutoCloseOpenClicked ), this, auto_close_open->GetId());
	menu_auto_close->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuAutoCloseSaveClicked ), this, auto_close_save->GetId());
	menu_auto_close->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnMenuAutoCloseSaveAsClicked ), this, auto_close_save_as->GetId());
	rbtn_take->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnTakeChosen ), NULL, this );
	rbtn_put->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPutChosen ), NULL, this );
	rbtn_game_speed->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnGameSpeedChosen ), NULL, this );
	rbtn_craft->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnCraftChosen ), NULL, this );
	rbtn_walk->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnWalkChosen ), NULL, this );
	rbtn_mine->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnMineChosen ), NULL, this );
	rbtn_start->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnStartChosen ), NULL, this );
	rbtn_build->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnBuildChosen ), NULL, this );
	rbtn_recipe->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnRecipeChosen ), NULL, this );
	rbtn_tech->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnTechChosen ), NULL, this );
	rbtn_limit->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnLimitChosen ), NULL, this );
	rbtn_idle->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnIdleChosen ), NULL, this );
	rbtn_filter->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnfilterChosen ), NULL, this );
	rbtn_pause->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPauseChosen ), NULL, this );
	rbtn_priority->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPriorityChosen ), NULL, this );
	rbtn_rotate->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnRotateChosen ), NULL, this );
	rbtn_pick_up->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPickUpChosen ), NULL, this );
	rbtn_drop->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnDropChosen ), NULL, this );
	rbtn_launch->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnLaunchChosen ), NULL, this );
	rbtn_save->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnSaveChosen ), NULL, this );
	rbtn_stop->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnStopChosen ), NULL, this );
	cmb_choose_group->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUI_Base::OnGroupChosen ), NULL, this );
	btn_new_group->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnNewGroupClicked ), NULL, this );
	btn_group_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteGroupClicked ), NULL, this );
	btn_group_change_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupChangeClicked ), NULL, this );
	btn_group_delete_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupDeleteClicked ), NULL, this );
	btn_group_move_up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveUpClicked ), NULL, this );
	btn_gorup_move_down->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveDownClicked ), NULL, this );
	btn_group_add_to_steps_list->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddToStepsListClicked ), NULL, this );
	btn_group_add_from_steps_list->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddFromStepsListClicked ), NULL, this );
	grid_group->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnGroupGridDoubleLeftClick ), NULL, this );
	cmb_choose_template->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUI_Base::OnTemplateChosen ), NULL, this );
	btn_template_new->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnNewTemplateClicked ), NULL, this );
	btn_template_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteTemplateClicked ), NULL, this );
	btn_template_change_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateChangeStepClicked ), NULL, this );
	btn_template_delete_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateDeleteStepClicked ), NULL, this );
	btn_template_move_up_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveUpClicked ), NULL, this );
	btn_template_move_down_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveDownClicked ), NULL, this );
	btn_template_add_to_steps_list->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddToStepsListClicked ), NULL, this );
	btn_template_add_from_steps_list->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddFromStepsListClicked ), NULL, this );
	grid_template->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnTemplateGridDoubleLeftClick ), NULL, this );
	step_search_ctrl->Connect( wxEVT_COMMAND_SEARCHCTRL_CANCEL_BTN, wxCommandEventHandler( GUI_Base::StepSeachOnCancelButton ), NULL, this );
	step_search_ctrl->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( GUI_Base::StepSeachOnSearchButton ), NULL, this );
	step_search_ctrl->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUI_Base::StepSeachOnText ), NULL, this );
	step_search_ctrl->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUI_Base::StepSeachOnTextEnter ), NULL, this );
	btn_add_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnAddStepClicked ), NULL, this );
	btn_change_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnChangeStepClicked ), NULL, this );
	btn_delete_step->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteStepClicked ), NULL, this );
	btn_move_up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveUpClicked ), NULL, this );
	btn_move_up->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUI_Base::OnMoveUpFiveClicked ), NULL, this );
	btn_move_down->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveDownClicked ), NULL, this );
	btn_move_down->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUI_Base::OnMoveDownFiveClicked ), NULL, this );
	grid_steps->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnStepsGridDoubleLeftClick ), NULL, this );
}

GUI_Base::~GUI_Base()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUI_Base::OnApplicationClose ) );
	rbtn_take->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnTakeChosen ), NULL, this );
	rbtn_put->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPutChosen ), NULL, this );
	rbtn_game_speed->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnGameSpeedChosen ), NULL, this );
	rbtn_craft->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnCraftChosen ), NULL, this );
	rbtn_walk->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnWalkChosen ), NULL, this );
	rbtn_mine->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnMineChosen ), NULL, this );
	rbtn_start->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnStartChosen ), NULL, this );
	rbtn_build->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnBuildChosen ), NULL, this );
	rbtn_recipe->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnRecipeChosen ), NULL, this );
	rbtn_tech->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnTechChosen ), NULL, this );
	rbtn_limit->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnLimitChosen ), NULL, this );
	rbtn_idle->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnIdleChosen ), NULL, this );
	rbtn_filter->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnfilterChosen ), NULL, this );
	rbtn_pause->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPauseChosen ), NULL, this );
	rbtn_priority->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPriorityChosen ), NULL, this );
	rbtn_rotate->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnRotateChosen ), NULL, this );
	rbtn_pick_up->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnPickUpChosen ), NULL, this );
	rbtn_drop->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnDropChosen ), NULL, this );
	rbtn_launch->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnLaunchChosen ), NULL, this );
	rbtn_save->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnSaveChosen ), NULL, this );
	rbtn_stop->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( GUI_Base::OnStopChosen ), NULL, this );
	cmb_choose_group->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUI_Base::OnGroupChosen ), NULL, this );
	btn_new_group->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnNewGroupClicked ), NULL, this );
	btn_group_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteGroupClicked ), NULL, this );
	btn_group_change_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupChangeClicked ), NULL, this );
	btn_group_delete_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupDeleteClicked ), NULL, this );
	btn_group_move_up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveUpClicked ), NULL, this );
	btn_gorup_move_down->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveDownClicked ), NULL, this );
	btn_group_add_to_steps_list->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddToStepsListClicked ), NULL, this );
	btn_group_add_from_steps_list->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddFromStepsListClicked ), NULL, this );
	grid_group->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnGroupGridDoubleLeftClick ), NULL, this );
	cmb_choose_template->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUI_Base::OnTemplateChosen ), NULL, this );
	btn_template_new->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnNewTemplateClicked ), NULL, this );
	btn_template_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteTemplateClicked ), NULL, this );
	btn_template_change_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateChangeStepClicked ), NULL, this );
	btn_template_delete_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateDeleteStepClicked ), NULL, this );
	btn_template_move_up_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveUpClicked ), NULL, this );
	btn_template_move_down_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveDownClicked ), NULL, this );
	btn_template_add_to_steps_list->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddToStepsListClicked ), NULL, this );
	btn_template_add_from_steps_list->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddFromStepsListClicked ), NULL, this );
	grid_template->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnTemplateGridDoubleLeftClick ), NULL, this );
	step_search_ctrl->Disconnect( wxEVT_COMMAND_SEARCHCTRL_CANCEL_BTN, wxCommandEventHandler( GUI_Base::StepSeachOnCancelButton ), NULL, this );
	step_search_ctrl->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( GUI_Base::StepSeachOnSearchButton ), NULL, this );
	step_search_ctrl->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUI_Base::StepSeachOnText ), NULL, this );
	step_search_ctrl->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUI_Base::StepSeachOnTextEnter ), NULL, this );
	btn_add_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnAddStepClicked ), NULL, this );
	btn_change_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnChangeStepClicked ), NULL, this );
	btn_delete_step->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteStepClicked ), NULL, this );
	btn_move_up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveUpClicked ), NULL, this );
	btn_move_up->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUI_Base::OnMoveUpFiveClicked ), NULL, this );
	btn_move_down->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveDownClicked ), NULL, this );
	btn_move_down->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUI_Base::OnMoveDownFiveClicked ), NULL, this );
	grid_steps->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnStepsGridDoubleLeftClick ), NULL, this );

	m_mgr.UnInit();

}

BaseForDialogProgress::BaseForDialogProgress( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxVERTICAL );

	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxVERTICAL );

	txt_dialog_text = new wxStaticText( m_panel7, wxID_ANY, wxT("Generating script"), wxDefaultPosition, wxDefaultSize, 0 );
	txt_dialog_text->Wrap( -1 );
	bSizer113->Add( txt_dialog_text, 0, wxALIGN_CENTER|wxALL, 5 );

	progress_bar = new wxGauge( m_panel7, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	progress_bar->SetValue( 0 );
	bSizer113->Add( progress_bar, 0, wxALL, 5 );


	bSizer112->Add( bSizer113, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxHORIZONTAL );

	btn_dialog_progress_done = new wxButton( m_panel7, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0 );
	btn_dialog_progress_done->Enable( false );

	bSizer114->Add( btn_dialog_progress_done, 1, wxALIGN_CENTER|wxALL, 5 );


	bSizer112->Add( bSizer114, 1, wxEXPAND, 5 );


	m_panel7->SetSizer( bSizer112 );
	m_panel7->Layout();
	bSizer112->Fit( m_panel7 );
	bSizer111->Add( m_panel7, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer111 );
	this->Layout();
	bSizer111->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	btn_dialog_progress_done->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseForDialogProgress::GenerateScriptOnClick ), NULL, this );
}

BaseForDialogProgress::~BaseForDialogProgress()
{
	// Disconnect Events
	btn_dialog_progress_done->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseForDialogProgress::GenerateScriptOnClick ), NULL, this );

}

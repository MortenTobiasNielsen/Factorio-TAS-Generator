///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

GUI_Base::GUI_Base( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

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

	m_menubar1->Append( menu_file, wxT("FIle") );

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
	wxMenuItem* menu_shortcuts_change_shortcuts;
	menu_shortcuts_change_shortcuts = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Change Shortcuts") ) , wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( menu_shortcuts_change_shortcuts );

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

	wxMenuItem* shortcut_add_task;
	shortcut_add_task = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Add Task") ) + wxT('\t') + wxT("Alt+A"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_add_task );

	wxMenuItem* shortcut_change_task;
	shortcut_change_task = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Change Task") ) + wxT('\t') + wxT("Alt+C"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_change_task );

	wxMenuItem* shortcut_delete_task;
	shortcut_delete_task = new wxMenuItem( menu_shortcuts, wxID_ANY, wxString( wxT("Delete Task") ) + wxT('\t') + wxT("Del"), wxEmptyString, wxITEM_NORMAL );
	menu_shortcuts->Append( shortcut_delete_task );

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

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer841;
	bSizer841 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );

	bSizer23->SetMinSize( wxSize( 10,10 ) );
	label_x_cord = new wxStaticText( m_panel1, wxID_ANY, wxT("X-Cord:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_x_cord->Wrap( -1 );
	bSizer23->Add( label_x_cord, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	spin_x_cord = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxSP_ARROW_KEYS, -1e+06, 1e+06, 0.000000, 0.1 );
	spin_x_cord->SetDigits( 1 );
	bSizer23->Add( spin_x_cord, 0, wxALL, 5 );


	bSizer30->Add( bSizer23, 1, 0, 5 );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	label_y_cord = new wxStaticText( m_panel1, wxID_ANY, wxT("Y-Cord:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_y_cord->Wrap( -1 );
	bSizer28->Add( label_y_cord, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spin_y_cord = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxSP_ARROW_KEYS, -1e+06, 1e+06, 0.000000, 0.1 );
	spin_y_cord->SetDigits( 1 );
	bSizer28->Add( spin_y_cord, 0, wxALL, 5 );


	bSizer30->Add( bSizer28, 1, 0, 5 );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	label_units = new wxStaticText( m_panel1, wxID_ANY, wxT("Units:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_units->Wrap( -1 );
	bSizer36->Add( label_units, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txt_units = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	bSizer36->Add( txt_units, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer30->Add( bSizer36, 1, 0, 5 );

	wxBoxSizer* bSizer361;
	bSizer361 = new wxBoxSizer( wxHORIZONTAL );

	label_comment = new wxStaticText( m_panel1, wxID_ANY, wxT("Comment:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_comment->Wrap( -1 );
	bSizer361->Add( label_comment, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txt_comment = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	bSizer361->Add( txt_comment, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer30->Add( bSizer361, 1, wxEXPAND, 5 );


	bSizer37->Add( bSizer30, 0, 0, 5 );


	bSizer19->Add( bSizer37, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	label_item = new wxStaticText( m_panel1, wxID_ANY, wxT("Item:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_item->Wrap( -1 );
	bSizer35->Add( label_item, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_item = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_item->SetMinSize( wxSize( 150,-1 ) );

	bSizer35->Add( cmb_item, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer24->Add( bSizer35, 1, 0, 5 );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );

	label_from_into = new wxStaticText( m_panel1, wxID_ANY, wxT("From/Into:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_from_into->Wrap( -1 );
	bSizer31->Add( label_from_into, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_from_into = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_from_into->SetSelection( 0 );
	cmb_from_into->SetMinSize( wxSize( 150,-1 ) );

	bSizer31->Add( cmb_from_into, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer24->Add( bSizer31, 1, 0, 5 );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );

	label_tech = new wxStaticText( m_panel1, wxID_ANY, wxT("Tech:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_tech->Wrap( -1 );
	bSizer34->Add( label_tech, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_tech = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_tech->SetSelection( 0 );
	cmb_tech->SetMinSize( wxSize( 150,-1 ) );

	bSizer34->Add( cmb_tech, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer24->Add( bSizer34, 1, 0, 5 );

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer( wxHORIZONTAL );

	label_input = new wxStaticText( m_panel1, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_input->Wrap( -1 );
	bSizer47->Add( label_input, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_input = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_input->SetSelection( 0 );
	cmb_input->SetMinSize( wxSize( 150,-1 ) );

	bSizer47->Add( cmb_input, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer24->Add( bSizer47, 1, 0, 5 );

	wxBoxSizer* bSizer471;
	bSizer471 = new wxBoxSizer( wxHORIZONTAL );

	label_output = new wxStaticText( m_panel1, wxID_ANY, wxT("Output:"), wxDefaultPosition, wxSize( 60,-1 ), wxALIGN_RIGHT );
	label_output->Wrap( -1 );
	bSizer471->Add( label_output, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_output = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_output->SetSelection( 0 );
	cmb_output->SetMinSize( wxSize( 150,-1 ) );

	bSizer471->Add( cmb_output, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer24->Add( bSizer471, 1, wxEXPAND, 5 );


	bSizer20->Add( bSizer24, 1, wxEXPAND, 5 );


	bSizer19->Add( bSizer20, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );

	label_building_orientation = new wxStaticText( m_panel1, wxID_ANY, wxT("Building Orientation:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_building_orientation->Wrap( -1 );
	bSizer58->Add( label_building_orientation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_building_orientation = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0, NULL, 0 );
	bSizer58->Add( cmb_building_orientation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer57->Add( bSizer58, 1, 0, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );

	label_direction_to_build = new wxStaticText( m_panel1, wxID_ANY, wxT("Direction:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_direction_to_build->Wrap( -1 );
	bSizer59->Add( label_direction_to_build, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	cmb_direction_to_build = new wxComboBox( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0, NULL, 0 );
	bSizer59->Add( cmb_direction_to_build, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer57->Add( bSizer59, 1, 0, 5 );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	label_building_size = new wxStaticText( m_panel1, wxID_ANY, wxT("Building Size:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_building_size->Wrap( -1 );
	bSizer51->Add( label_building_size, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txt_building_size = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer51->Add( txt_building_size, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer57->Add( bSizer51, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxHORIZONTAL );

	label_amount_of_buildings = new wxStaticText( m_panel1, wxID_ANY, wxT("Amount of Buildings:"), wxDefaultPosition, wxSize( 115,-1 ), wxALIGN_RIGHT );
	label_amount_of_buildings->Wrap( -1 );
	bSizer52->Add( label_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txt_amount_of_buildings = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer52->Add( txt_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer57->Add( bSizer52, 1, wxEXPAND, 5 );


	bSizer19->Add( bSizer57, 0, 0, 5 );


	bSizer19->Add( 50, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	label_tasks = new wxStaticText( m_panel1, wxID_ANY, wxT("Tasks"), wxDefaultPosition, wxDefaultSize, 0 );
	label_tasks->Wrap( -1 );
	bSizer18->Add( label_tasks, 0, wxALIGN_CENTER|wxALL, 5 );

	m_staticline3 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer18->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );

	rbtn_take = new wxRadioButton( m_panel1, wxID_ANY, wxT("Take"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer42->Add( rbtn_take, 0, wxALL, 5 );


	bSizer6->Add( bSizer42, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	rbtn_put = new wxRadioButton( m_panel1, wxID_ANY, wxT("Put"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( rbtn_put, 0, wxALL, 5 );


	bSizer6->Add( bSizer11, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	rbtn_game_speed = new wxRadioButton( m_panel1, wxID_ANY, wxT("Game Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( rbtn_game_speed, 0, wxALL, 5 );


	bSizer6->Add( bSizer17, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );

	rbtn_craft = new wxRadioButton( m_panel1, wxID_ANY, wxT("Craft"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( rbtn_craft, 0, wxALL, 5 );


	bSizer6->Add( bSizer39, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	rbtn_walk = new wxRadioButton( m_panel1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( rbtn_walk, 0, wxALL, 5 );


	bSizer6->Add( bSizer15, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	rbtn_mine = new wxRadioButton( m_panel1, wxID_ANY, wxT("Mine"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( rbtn_mine, 0, wxALL, 5 );


	bSizer6->Add( bSizer12, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	rbtn_start = new wxRadioButton( m_panel1, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( rbtn_start, 0, wxALL, 5 );


	bSizer6->Add( bSizer121, 1, wxEXPAND, 5 );


	bSizer18->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	rbtn_build = new wxRadioButton( m_panel1, wxID_ANY, wxT("Build"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( rbtn_build, 0, wxALL, 5 );


	bSizer7->Add( bSizer16, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer( wxVERTICAL );

	rbtn_recipe = new wxRadioButton( m_panel1, wxID_ANY, wxT("Recipe"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer64->Add( rbtn_recipe, 0, wxALL, 5 );


	bSizer7->Add( bSizer64, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer( wxVERTICAL );

	rbtn_tech = new wxRadioButton( m_panel1, wxID_ANY, wxT("Tech"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer63->Add( rbtn_tech, 0, wxALL, 5 );


	bSizer7->Add( bSizer63, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );

	rbtn_limit = new wxRadioButton( m_panel1, wxID_ANY, wxT("Limit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( rbtn_limit, 0, wxALL, 5 );


	bSizer7->Add( bSizer40, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer431;
	bSizer431 = new wxBoxSizer( wxVERTICAL );

	rbtn_idle = new wxRadioButton( m_panel1, wxID_ANY, wxT("Idle"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer431->Add( rbtn_idle, 0, wxALL, 5 );


	bSizer7->Add( bSizer431, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxVERTICAL );

	rbtn_filter = new wxRadioButton( m_panel1, wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( rbtn_filter, 0, wxALL, 5 );


	bSizer7->Add( bSizer65, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );

	rbtn_pause = new wxRadioButton( m_panel1, wxID_ANY, wxT("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer141->Add( rbtn_pause, 0, wxALL, 5 );


	bSizer7->Add( bSizer141, 1, wxEXPAND, 5 );


	bSizer18->Add( bSizer7, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	rbtn_priority = new wxRadioButton( m_panel1, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( rbtn_priority, 0, wxALL, 5 );


	bSizer5->Add( bSizer9, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	rbtn_rotate = new wxRadioButton( m_panel1, wxID_ANY, wxT("Rotate"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( rbtn_rotate, 0, wxALL, 5 );


	bSizer5->Add( bSizer13, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );

	rbtn_pick_up = new wxRadioButton( m_panel1, wxID_ANY, wxT("Pick Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( rbtn_pick_up, 0, wxALL, 5 );


	bSizer5->Add( bSizer41, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer441;
	bSizer441 = new wxBoxSizer( wxVERTICAL );

	rbtn_drop = new wxRadioButton( m_panel1, wxID_ANY, wxT("Drop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer441->Add( rbtn_drop, 0, wxALL, 5 );


	bSizer5->Add( bSizer441, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	rbtn_launch = new wxRadioButton( m_panel1, wxID_ANY, wxT("Launch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( rbtn_launch, 0, wxALL, 5 );


	bSizer5->Add( bSizer14, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1411;
	bSizer1411 = new wxBoxSizer( wxVERTICAL );

	rbtn_save = new wxRadioButton( m_panel1, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1411->Add( rbtn_save, 0, wxALL, 5 );


	bSizer5->Add( bSizer1411, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	rbtn_stop = new wxRadioButton( m_panel1, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( rbtn_stop, 0, wxALL, 5 );


	bSizer5->Add( bSizer8, 1, wxEXPAND, 5 );


	bSizer18->Add( bSizer5, 1, wxEXPAND, 5 );

	m_staticline4 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer18->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );


	bSizer19->Add( bSizer18, 1, wxEXPAND, 5 );


	bSizer19->Add( 50, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxVERTICAL );

	label_atuo_put = new wxStaticText( m_panel1, wxID_ANY, wxT("Auto-put"), wxDefaultPosition, wxDefaultSize, 0 );
	label_atuo_put->Wrap( -1 );
	bSizer116->Add( label_atuo_put, 0, wxALIGN_CENTER|wxALL, 5 );

	m_staticline31 = new wxStaticLine( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer116->Add( m_staticline31, 0, wxEXPAND | wxALL, 5 );

	check_furnace = new wxCheckBox( m_panel1, wxID_ANY, wxT("Furnace"), wxDefaultPosition, wxDefaultSize, 0 );
	check_furnace->SetValue(true);
	check_furnace->SetToolTip( wxT("Adds a task to put coal into stone and steel furnaces") );

	bSizer116->Add( check_furnace, 0, wxALL, 5 );

	check_burner = new wxCheckBox( m_panel1, wxID_ANY, wxT("Burner"), wxDefaultPosition, wxDefaultSize, 0 );
	check_burner->SetValue(true);
	check_burner->SetToolTip( wxT("Adds a task to put coal into Burner Mining Drills, Burner Inserters and Boilers") );

	bSizer116->Add( check_burner, 0, wxALL, 5 );

	check_lab = new wxCheckBox( m_panel1, wxID_ANY, wxT("Lab"), wxDefaultPosition, wxDefaultSize, 0 );
	check_lab->SetValue(true);
	check_lab->SetToolTip( wxT("Adds a task to put automation science into the Lab") );

	bSizer116->Add( check_lab, 0, wxALL, 5 );

	check_recipe = new wxCheckBox( m_panel1, wxID_ANY, wxT("Recipe"), wxDefaultPosition, wxDefaultSize, 0 );
	check_recipe->SetValue(true);
	check_recipe->SetToolTip( wxT("Add tasks to put the items needed to craft that recipe") );

	bSizer116->Add( check_recipe, 0, wxALL, 5 );


	bSizer19->Add( bSizer116, 1, wxEXPAND, 5 );


	bSizer19->Add( 10000, 0, 1, wxEXPAND, 5 );


	bSizer841->Add( bSizer19, 1, 0, 5 );


	bSizer84->Add( bSizer841, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer84 );
	m_panel1->Layout();
	bSizer84->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );

	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxVERTICAL );

	bSizer44->SetMinSize( wxSize( 550,-1 ) );
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer561;
	bSizer561 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer118;
	bSizer118 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1261;
	bSizer1261 = new wxBoxSizer( wxHORIZONTAL );

	label_choose_group = new wxStaticText( m_panel3, wxID_ANY, wxT("Choose Group:"), wxDefaultPosition, wxSize( 95,-1 ), wxALIGN_RIGHT );
	label_choose_group->Wrap( -1 );
	bSizer1261->Add( label_choose_group, 0, wxALIGN_CENTER|wxALL, 5 );

	cmb_choose_group = new wxComboBox( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT );
	cmb_choose_group->SetMinSize( wxSize( 150,-1 ) );

	bSizer1261->Add( cmb_choose_group, 0, wxALIGN_CENTER|wxALL, 5 );

	btn_new_group = new wxButton( m_panel3, wxID_ANY, wxT("New Group"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer1261->Add( btn_new_group, 0, wxALL, 5 );

	btn_group_delete = new wxButton( m_panel3, wxID_ANY, wxT("Delete Group"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer1261->Add( btn_group_delete, 0, wxALL, 5 );


	bSizer118->Add( bSizer1261, 1, wxALIGN_LEFT, 5 );

	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxHORIZONTAL );

	btn_group_change_task = new wxButton( m_panel3, wxID_ANY, wxT("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_group_change_task, 0, wxALL, 5 );

	btn_group_delete_task = new wxButton( m_panel3, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_group_delete_task, 0, wxALL, 5 );

	btn_group_move_up = new wxButton( m_panel3, wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_group_move_up, 0, wxALL, 5 );

	btn_gorup_move_down = new wxButton( m_panel3, wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( btn_gorup_move_down, 0, wxALL, 5 );


	bSizer118->Add( bSizer100, 1, wxALIGN_LEFT, 5 );


	bSizer114->Add( bSizer118, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxVERTICAL );

	btn_group_add_to_tasks_list = new wxButton( m_panel3, wxID_ANY, wxT("Add to tasks list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer119->Add( btn_group_add_to_tasks_list, 0, wxALL, 5 );

	btn_group_add_from_tasks_list = new wxButton( m_panel3, wxID_ANY, wxT("Add from tasks list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer119->Add( btn_group_add_from_tasks_list, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer114->Add( bSizer119, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1191;
	bSizer1191 = new wxBoxSizer( wxVERTICAL );


	bSizer1191->Add( 2, 0, 1, wxEXPAND, 5 );


	bSizer114->Add( bSizer1191, 0, wxEXPAND, 5 );


	bSizer561->Add( bSizer114, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );

	grid_group = new wxGrid( m_panel3, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );

	// Grid
	grid_group->CreateGrid( 0, 10 );
	grid_group->EnableEditing( false );
	grid_group->EnableGridLines( true );
	grid_group->EnableDragGridSize( false );
	grid_group->SetMargins( 0, 0 );

	// Columns
	grid_group->SetColSize( 0, 75 );
	grid_group->SetColSize( 1, 50 );
	grid_group->SetColSize( 2, 50 );
	grid_group->SetColSize( 3, 50 );
	grid_group->SetColSize( 4, 150 );
	grid_group->SetColSize( 5, 70 );
	grid_group->SetColSize( 6, 70 );
	grid_group->SetColSize( 7, 50 );
	grid_group->SetColSize( 8, 50 );
	grid_group->SetColSize( 9, 150 );
	grid_group->EnableDragColMove( false );
	grid_group->EnableDragColSize( false );
	grid_group->SetColLabelValue( 0, wxT("Task") );
	grid_group->SetColLabelValue( 1, wxT("X-cord") );
	grid_group->SetColLabelValue( 2, wxT("Y-cord") );
	grid_group->SetColLabelValue( 3, wxT("Units") );
	grid_group->SetColLabelValue( 4, wxT("Item") );
	grid_group->SetColLabelValue( 5, wxT("Orientation") );
	grid_group->SetColLabelValue( 6, wxT("Direction") );
	grid_group->SetColLabelValue( 7, wxT("Size") );
	grid_group->SetColLabelValue( 8, wxT("Amount") );
	grid_group->SetColLabelValue( 9, wxT("Comment") );
	grid_group->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_group->EnableDragRowSize( false );
	grid_group->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	grid_group->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_group->SetMinSize( wxSize( 870,2500 ) );

	bSizer50->Add( grid_group, 0, wxALL, 5 );


	bSizer561->Add( bSizer50, 1, wxEXPAND, 5 );


	m_panel3->SetSizer( bSizer561 );
	m_panel3->Layout();
	bSizer561->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, wxT("Group"), true );
	m_panel6 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5612;
	bSizer5612 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer103;
	bSizer103 = new wxBoxSizer( wxVERTICAL );

	bSizer103->SetMinSize( wxSize( 612,-1 ) );
	wxBoxSizer* bSizer126;
	bSizer126 = new wxBoxSizer( wxHORIZONTAL );

	label_choose_template = new wxStaticText( m_panel6, wxID_ANY, wxT("Choose Template:"), wxDefaultPosition, wxSize( 95,-1 ), 0 );
	label_choose_template->Wrap( -1 );
	bSizer126->Add( label_choose_template, 0, wxALIGN_CENTER|wxALL, 5 );

	cmb_choose_template = new wxComboBox( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	cmb_choose_template->SetMinSize( wxSize( 150,-1 ) );

	bSizer126->Add( cmb_choose_template, 0, wxALIGN_CENTER|wxALL, 5 );

	btn_template_new = new wxButton( m_panel6, wxID_ANY, wxT("New Template"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer126->Add( btn_template_new, 0, wxALL, 5 );

	btn_template_delete = new wxButton( m_panel6, wxID_ANY, wxT("Delete Template"), wxDefaultPosition, wxSize( 105,-1 ), 0 );
	bSizer126->Add( btn_template_delete, 0, wxALL, 5 );


	bSizer103->Add( bSizer126, 1, wxALIGN_LEFT, 5 );

	wxBoxSizer* bSizer1002;
	bSizer1002 = new wxBoxSizer( wxHORIZONTAL );

	btn_template_change_task = new wxButton( m_panel6, wxID_ANY, wxT("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_change_task, 0, wxALL, 5 );

	btn_template_delete_task = new wxButton( m_panel6, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_delete_task, 0, wxALL, 5 );

	btn_template_move_up_task = new wxButton( m_panel6, wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_move_up_task, 0, wxALL, 5 );

	btn_template_move_down_task = new wxButton( m_panel6, wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1002->Add( btn_template_move_down_task, 0, wxALL, 5 );


	bSizer103->Add( bSizer1002, 1, wxALIGN_LEFT, 5 );


	bSizer102->Add( bSizer103, 1, 0, 5 );

	wxBoxSizer* bSizer1041;
	bSizer1041 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer1051;
	bSizer1051 = new wxBoxSizer( wxHORIZONTAL );

	btn_template_add_to_tasks_list1 = new wxButton( m_panel6, wxID_ANY, wxT("Add to tasks list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer1051->Add( btn_template_add_to_tasks_list1, 0, wxALL, 5 );


	bSizer1041->Add( bSizer1051, 1, 0, 5 );

	wxBoxSizer* bSizer1061;
	bSizer1061 = new wxBoxSizer( wxHORIZONTAL );

	btn_template_add_from_tasks_list1 = new wxButton( m_panel6, wxID_ANY, wxT("Add from tasks list"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	bSizer1061->Add( btn_template_add_from_tasks_list1, 0, wxALL, 5 );


	bSizer1041->Add( bSizer1061, 1, 0, 5 );


	bSizer102->Add( bSizer1041, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer104;
	bSizer104 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxHORIZONTAL );

	label_template_x_offset = new wxStaticText( m_panel6, wxID_ANY, wxT("X-Offset:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	label_template_x_offset->Wrap( -1 );
	bSizer105->Add( label_template_x_offset, 0, wxALIGN_CENTER, 5 );

	txt_template_x_offset = new wxTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer105->Add( txt_template_x_offset, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer104->Add( bSizer105, 1, 0, 5 );

	wxBoxSizer* bSizer106;
	bSizer106 = new wxBoxSizer( wxHORIZONTAL );

	label_template_y_offset = new wxStaticText( m_panel6, wxID_ANY, wxT("Y-Offset:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	label_template_y_offset->Wrap( -1 );
	bSizer106->Add( label_template_y_offset, 0, wxALIGN_CENTER, 5 );

	txt_template_y_offset = new wxTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer106->Add( txt_template_y_offset, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer104->Add( bSizer106, 1, 0, 5 );


	bSizer102->Add( bSizer104, 0, 0, 5 );


	bSizer5612->Add( bSizer102, 1, 0, 5 );

	wxBoxSizer* bSizer502;
	bSizer502 = new wxBoxSizer( wxVERTICAL );

	grid_template = new wxGrid( m_panel6, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );

	// Grid
	grid_template->CreateGrid( 0, 10 );
	grid_template->EnableEditing( false );
	grid_template->EnableGridLines( true );
	grid_template->EnableDragGridSize( false );
	grid_template->SetMargins( 0, 0 );

	// Columns
	grid_template->SetColSize( 0, 75 );
	grid_template->SetColSize( 1, 50 );
	grid_template->SetColSize( 2, 50 );
	grid_template->SetColSize( 3, 50 );
	grid_template->SetColSize( 4, 150 );
	grid_template->SetColSize( 5, 70 );
	grid_template->SetColSize( 6, 70 );
	grid_template->SetColSize( 7, 50 );
	grid_template->SetColSize( 8, 50 );
	grid_template->SetColSize( 9, 150 );
	grid_template->EnableDragColMove( false );
	grid_template->EnableDragColSize( false );
	grid_template->SetColLabelValue( 0, wxT("Task") );
	grid_template->SetColLabelValue( 1, wxT("X-cord") );
	grid_template->SetColLabelValue( 2, wxT("Y-cord") );
	grid_template->SetColLabelValue( 3, wxT("Units") );
	grid_template->SetColLabelValue( 4, wxT("Item") );
	grid_template->SetColLabelValue( 5, wxT("Orientation") );
	grid_template->SetColLabelValue( 6, wxT("Direction") );
	grid_template->SetColLabelValue( 7, wxT("Size") );
	grid_template->SetColLabelValue( 8, wxT("Amount") );
	grid_template->SetColLabelValue( 9, wxT("Comment") );
	grid_template->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_template->EnableDragRowSize( false );
	grid_template->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	grid_template->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_template->SetMinSize( wxSize( 870,2500 ) );

	bSizer502->Add( grid_template, 0, wxALL, 5 );


	bSizer5612->Add( bSizer502, 1, wxEXPAND, 5 );


	m_panel6->SetSizer( bSizer5612 );
	m_panel6->Layout();
	bSizer5612->Fit( m_panel6 );
	m_notebook1->AddPage( m_panel6, wxT("Template"), false );
	m_panel61 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer56111;
	bSizer56111 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer100121;
	bSizer100121 = new wxBoxSizer( wxHORIZONTAL );


	bSizer100121->Add( 0, 36, 1, wxEXPAND, 5 );


	bSizer56111->Add( bSizer100121, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1001211;
	bSizer1001211 = new wxBoxSizer( wxHORIZONTAL );


	bSizer1001211->Add( 0, 36, 1, wxEXPAND, 5 );


	bSizer56111->Add( bSizer1001211, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5011;
	bSizer5011 = new wxBoxSizer( wxVERTICAL );

	grid_buildings = new wxGrid( m_panel61, wxID_ANY, wxDefaultPosition, wxSize( 825,-1 ), 0 );

	// Grid
	grid_buildings->CreateGrid( 0, 9 );
	grid_buildings->EnableEditing( false );
	grid_buildings->EnableGridLines( true );
	grid_buildings->EnableDragGridSize( false );
	grid_buildings->SetMargins( 0, 0 );

	// Columns
	grid_buildings->SetColSize( 0, 50 );
	grid_buildings->SetColSize( 1, 50 );
	grid_buildings->SetColSize( 2, 150 );
	grid_buildings->SetColSize( 3, 70 );
	grid_buildings->SetColSize( 4, 50 );
	grid_buildings->SetColSize( 5, 150 );
	grid_buildings->SetColSize( 6, 50 );
	grid_buildings->SetColSize( 7, 50 );
	grid_buildings->SetColSize( 8, 150 );
	grid_buildings->EnableDragColMove( false );
	grid_buildings->EnableDragColSize( false );
	grid_buildings->SetColLabelValue( 0, wxT("X-cord") );
	grid_buildings->SetColLabelValue( 1, wxT("Y-cord") );
	grid_buildings->SetColLabelValue( 2, wxT("Building") );
	grid_buildings->SetColLabelValue( 3, wxT("Orientation") );
	grid_buildings->SetColLabelValue( 4, wxT("Limit") );
	grid_buildings->SetColLabelValue( 5, wxT("Recipe") );
	grid_buildings->SetColLabelValue( 6, wxT("Prio In") );
	grid_buildings->SetColLabelValue( 7, wxT("Prio Out") );
	grid_buildings->SetColLabelValue( 8, wxT("Filter") );
	grid_buildings->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_buildings->EnableDragRowSize( false );
	grid_buildings->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	grid_buildings->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_buildings->SetMinSize( wxSize( 870,2500 ) );

	bSizer5011->Add( grid_buildings, 0, wxALL, 5 );


	bSizer56111->Add( bSizer5011, 1, 0, 5 );


	m_panel61->SetSizer( bSizer56111 );
	m_panel61->Layout();
	bSizer56111->Fit( m_panel61 );
	m_notebook1->AddPage( m_panel61, wxT("Buildings"), false );

	bSizer44->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );


	bSizer43->Add( bSizer44, 1, wxEXPAND, 5 );


	bSizer43->Add( 25, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer442;
	bSizer442 = new wxBoxSizer( wxVERTICAL );

	bSizer442->SetMinSize( wxSize( 550,-1 ) );
	m_notebook11 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel31 = new wxPanel( m_notebook11, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5611;
	bSizer5611 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer10012;
	bSizer10012 = new wxBoxSizer( wxHORIZONTAL );


	bSizer10012->Add( 0, 36, 1, wxEXPAND, 5 );


	bSizer5611->Add( bSizer10012, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer1001;
	bSizer1001 = new wxBoxSizer( wxHORIZONTAL );


	bSizer1001->Add( 125, 0, 1, wxEXPAND, 5 );

	btn_add_task11 = new wxButton( m_panel31, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1001->Add( btn_add_task11, 0, wxALIGN_CENTER|wxALL, 5 );

	btn_change_task11 = new wxButton( m_panel31, wxID_ANY, wxT("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1001->Add( btn_change_task11, 0, wxALL, 5 );

	btn_delete_task11 = new wxButton( m_panel31, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1001->Add( btn_delete_task11, 0, wxALL, 5 );

	btn_move_up11 = new wxButton( m_panel31, wxID_ANY, wxT("Move Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1001->Add( btn_move_up11, 0, wxALL, 5 );

	btn_move_down11 = new wxButton( m_panel31, wxID_ANY, wxT("Move Down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1001->Add( btn_move_down11, 0, wxALL, 5 );


	bSizer5611->Add( bSizer1001, 0, 0, 5 );

	wxBoxSizer* bSizer501;
	bSizer501 = new wxBoxSizer( wxVERTICAL );

	grid_tasks = new wxGrid( m_panel31, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );

	// Grid
	grid_tasks->CreateGrid( 0, 10 );
	grid_tasks->EnableEditing( false );
	grid_tasks->EnableGridLines( true );
	grid_tasks->EnableDragGridSize( false );
	grid_tasks->SetMargins( 0, 0 );

	// Columns
	grid_tasks->SetColSize( 0, 75 );
	grid_tasks->SetColSize( 1, 50 );
	grid_tasks->SetColSize( 2, 50 );
	grid_tasks->SetColSize( 3, 50 );
	grid_tasks->SetColSize( 4, 150 );
	grid_tasks->SetColSize( 5, 70 );
	grid_tasks->SetColSize( 6, 70 );
	grid_tasks->SetColSize( 7, 50 );
	grid_tasks->SetColSize( 8, 50 );
	grid_tasks->SetColSize( 9, 150 );
	grid_tasks->EnableDragColMove( false );
	grid_tasks->EnableDragColSize( false );
	grid_tasks->SetColLabelValue( 0, wxT("Task") );
	grid_tasks->SetColLabelValue( 1, wxT("X-cord") );
	grid_tasks->SetColLabelValue( 2, wxT("Y-cord") );
	grid_tasks->SetColLabelValue( 3, wxT("Units") );
	grid_tasks->SetColLabelValue( 4, wxT("Item") );
	grid_tasks->SetColLabelValue( 5, wxT("Orientation") );
	grid_tasks->SetColLabelValue( 6, wxT("Direction") );
	grid_tasks->SetColLabelValue( 7, wxT("Size") );
	grid_tasks->SetColLabelValue( 8, wxT("Amount") );
	grid_tasks->SetColLabelValue( 9, wxT("Comment") );
	grid_tasks->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	grid_tasks->EnableDragRowSize( false );
	grid_tasks->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	grid_tasks->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grid_tasks->SetMinSize( wxSize( 870,2500 ) );

	bSizer501->Add( grid_tasks, 0, wxALL, 5 );


	bSizer5611->Add( bSizer501, 1, wxEXPAND, 5 );


	m_panel31->SetSizer( bSizer5611 );
	m_panel31->Layout();
	bSizer5611->Fit( m_panel31 );
	m_notebook11->AddPage( m_panel31, wxT("Tasks"), false );

	bSizer442->Add( m_notebook11, 1, wxEXPAND | wxALL, 5 );


	bSizer43->Add( bSizer442, 1, wxEXPAND, 5 );


	bSizer43->Add( 10000, 0, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer43, 1, wxEXPAND, 5 );


	bSizer1->Add( 0, 10000, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

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
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnChangeShortcuts ), this, menu_shortcuts_change_shortcuts->GetId());
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
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnAddMenuSelected ), this, shortcut_add_task->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnChangeMenuSelected ), this, shortcut_change_task->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI_Base::OnDeleteMenuSelected ), this, shortcut_delete_task->GetId());
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
	btn_group_change_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupChangeClicked ), NULL, this );
	btn_group_delete_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupDeleteClicked ), NULL, this );
	btn_group_move_up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveUpClicked ), NULL, this );
	btn_gorup_move_down->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveDownClicked ), NULL, this );
	btn_group_add_to_tasks_list->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddToTasksListClicked ), NULL, this );
	btn_group_add_from_tasks_list->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddFromTasksListClicked ), NULL, this );
	grid_group->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnGroupGridDoubleLeftClick ), NULL, this );
	cmb_choose_template->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUI_Base::OnTemplateChosen ), NULL, this );
	btn_template_new->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnNewTemplateClicked ), NULL, this );
	btn_template_delete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteTemplateClicked ), NULL, this );
	btn_template_change_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateChangeTaskClicked ), NULL, this );
	btn_template_delete_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateDeleteTaskClicked ), NULL, this );
	btn_template_move_up_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveUpClicked ), NULL, this );
	btn_template_move_down_task->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveDownClicked ), NULL, this );
	btn_template_add_to_tasks_list1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddToTasksListClicked ), NULL, this );
	btn_template_add_from_tasks_list1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddFromTasksListClicked ), NULL, this );
	grid_template->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnTemplateGridDoubleLeftClick ), NULL, this );
	grid_buildings->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnBuildingsGridLeftDoubleClick ), NULL, this );
	btn_add_task11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnAddTaskClicked ), NULL, this );
	btn_change_task11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnChangeTaskClicked ), NULL, this );
	btn_delete_task11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteTaskClicked ), NULL, this );
	btn_move_up11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveUpClicked ), NULL, this );
	btn_move_down11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveDownClicked ), NULL, this );
	grid_tasks->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnTasksGridDoubleLeftClick ), NULL, this );
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
	btn_group_change_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupChangeClicked ), NULL, this );
	btn_group_delete_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupDeleteClicked ), NULL, this );
	btn_group_move_up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveUpClicked ), NULL, this );
	btn_gorup_move_down->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupMoveDownClicked ), NULL, this );
	btn_group_add_to_tasks_list->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddToTasksListClicked ), NULL, this );
	btn_group_add_from_tasks_list->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnGroupAddFromTasksListClicked ), NULL, this );
	grid_group->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnGroupGridDoubleLeftClick ), NULL, this );
	cmb_choose_template->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( GUI_Base::OnTemplateChosen ), NULL, this );
	btn_template_new->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnNewTemplateClicked ), NULL, this );
	btn_template_delete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteTemplateClicked ), NULL, this );
	btn_template_change_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateChangeTaskClicked ), NULL, this );
	btn_template_delete_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateDeleteTaskClicked ), NULL, this );
	btn_template_move_up_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveUpClicked ), NULL, this );
	btn_template_move_down_task->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateMoveDownClicked ), NULL, this );
	btn_template_add_to_tasks_list1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddToTasksListClicked ), NULL, this );
	btn_template_add_from_tasks_list1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnTemplateAddFromTasksListClicked ), NULL, this );
	grid_template->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnTemplateGridDoubleLeftClick ), NULL, this );
	grid_buildings->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnBuildingsGridLeftDoubleClick ), NULL, this );
	btn_add_task11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnAddTaskClicked ), NULL, this );
	btn_change_task11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnChangeTaskClicked ), NULL, this );
	btn_delete_task11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnDeleteTaskClicked ), NULL, this );
	btn_move_up11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveUpClicked ), NULL, this );
	btn_move_down11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI_Base::OnMoveDownClicked ), NULL, this );
	grid_tasks->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( GUI_Base::OnTasksGridDoubleLeftClick ), NULL, this );

}

Shortcuts_Menu::Shortcuts_Menu( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 570,400 ), wxDefaultSize );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer( wxHORIZONTAL );

	bSizer98->SetMinSize( wxSize( -1,325 ) );
	m_scrolledWindow3 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxVSCROLL );
	m_scrolledWindow3->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer519;
	bSizer519 = new wxBoxSizer( wxVERTICAL );

	bSizer519->SetMinSize( wxSize( -1,300 ) );
	wxBoxSizer* bSizer5181;
	bSizer5181 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk->Wrap( -1 );
	bSizer5181->Add( label_shortcut_walk, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181->Add( m_textCtrl681, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer5181, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51811;
	bSizer51811 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk1 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk1->Wrap( -1 );
	bSizer51811->Add( label_shortcut_walk1, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6811 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51811->Add( m_textCtrl6811, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51811, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51812;
	bSizer51812 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk2 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk2->Wrap( -1 );
	bSizer51812->Add( label_shortcut_walk2, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6812 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51812->Add( m_textCtrl6812, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51812, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51813;
	bSizer51813 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk3 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk3->Wrap( -1 );
	bSizer51813->Add( label_shortcut_walk3, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6813 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51813->Add( m_textCtrl6813, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51813, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51814;
	bSizer51814 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk4 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk4->Wrap( -1 );
	bSizer51814->Add( label_shortcut_walk4, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6814 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51814->Add( m_textCtrl6814, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51814, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51815;
	bSizer51815 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk5 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk5->Wrap( -1 );
	bSizer51815->Add( label_shortcut_walk5, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6815 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51815->Add( m_textCtrl6815, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51815, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51816;
	bSizer51816 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk6 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk6->Wrap( -1 );
	bSizer51816->Add( label_shortcut_walk6, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6816 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51816->Add( m_textCtrl6816, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51816, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51817;
	bSizer51817 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk7 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk7->Wrap( -1 );
	bSizer51817->Add( label_shortcut_walk7, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6817 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51817->Add( m_textCtrl6817, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51817, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51818;
	bSizer51818 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk8 = new wxStaticText( m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk8->Wrap( -1 );
	bSizer51818->Add( label_shortcut_walk8, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6818 = new wxTextCtrl( m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51818->Add( m_textCtrl6818, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer519->Add( bSizer51818, 1, wxEXPAND, 5 );


	m_scrolledWindow3->SetSizer( bSizer519 );
	m_scrolledWindow3->Layout();
	bSizer519->Fit( m_scrolledWindow3 );
	bSizer98->Add( m_scrolledWindow3, 1, wxEXPAND | wxALL, 5 );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	m_scrolledWindow1->SetMinSize( wxSize( -1,50 ) );

	wxBoxSizer* bSizer5191;
	bSizer5191 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer51819;
	bSizer51819 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk9 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk9->Wrap( -1 );
	bSizer51819->Add( label_shortcut_walk9, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl6819 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer51819->Add( m_textCtrl6819, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer51819, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518111;
	bSizer518111 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk11 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk11->Wrap( -1 );
	bSizer518111->Add( label_shortcut_walk11, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68111 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518111->Add( m_textCtrl68111, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518111, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518121;
	bSizer518121 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk21 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk21->Wrap( -1 );
	bSizer518121->Add( label_shortcut_walk21, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68121 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518121->Add( m_textCtrl68121, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518121, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518131;
	bSizer518131 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk31 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk31->Wrap( -1 );
	bSizer518131->Add( label_shortcut_walk31, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68131 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518131->Add( m_textCtrl68131, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518131, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518141;
	bSizer518141 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk41 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk41->Wrap( -1 );
	bSizer518141->Add( label_shortcut_walk41, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68141 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518141->Add( m_textCtrl68141, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518141, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518151;
	bSizer518151 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk51 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk51->Wrap( -1 );
	bSizer518151->Add( label_shortcut_walk51, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68151 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518151->Add( m_textCtrl68151, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518151, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518161;
	bSizer518161 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk61 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk61->Wrap( -1 );
	bSizer518161->Add( label_shortcut_walk61, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68161 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518161->Add( m_textCtrl68161, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518161, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518171;
	bSizer518171 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk71 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk71->Wrap( -1 );
	bSizer518171->Add( label_shortcut_walk71, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68171 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518171->Add( m_textCtrl68171, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518171, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer518181;
	bSizer518181 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk81 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk81->Wrap( -1 );
	bSizer518181->Add( label_shortcut_walk81, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68181 = new wxTextCtrl( m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518181->Add( m_textCtrl68181, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5191->Add( bSizer518181, 1, wxEXPAND, 5 );


	m_scrolledWindow1->SetSizer( bSizer5191 );
	m_scrolledWindow1->Layout();
	bSizer5191->Fit( m_scrolledWindow1 );
	bSizer98->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );

	m_scrolledWindow11 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow11->SetScrollRate( 5, 5 );
	m_scrolledWindow11->SetMinSize( wxSize( -1,50 ) );

	wxBoxSizer* bSizer51911;
	bSizer51911 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer518191;
	bSizer518191 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk91 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk91->Wrap( -1 );
	bSizer518191->Add( label_shortcut_walk91, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl68191 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer518191->Add( m_textCtrl68191, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer518191, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181111;
	bSizer5181111 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk111 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk111->Wrap( -1 );
	bSizer5181111->Add( label_shortcut_walk111, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681111 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181111->Add( m_textCtrl681111, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181111, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181211;
	bSizer5181211 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk211 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk211->Wrap( -1 );
	bSizer5181211->Add( label_shortcut_walk211, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681211 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181211->Add( m_textCtrl681211, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181211, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181311;
	bSizer5181311 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk311 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk311->Wrap( -1 );
	bSizer5181311->Add( label_shortcut_walk311, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681311 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181311->Add( m_textCtrl681311, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181311, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181411;
	bSizer5181411 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk411 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk411->Wrap( -1 );
	bSizer5181411->Add( label_shortcut_walk411, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681411 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181411->Add( m_textCtrl681411, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181411, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181511;
	bSizer5181511 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk511 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk511->Wrap( -1 );
	bSizer5181511->Add( label_shortcut_walk511, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681511 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181511->Add( m_textCtrl681511, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181511, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181611;
	bSizer5181611 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk611 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk611->Wrap( -1 );
	bSizer5181611->Add( label_shortcut_walk611, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681611 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181611->Add( m_textCtrl681611, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181611, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181711;
	bSizer5181711 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk711 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk711->Wrap( -1 );
	bSizer5181711->Add( label_shortcut_walk711, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681711 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181711->Add( m_textCtrl681711, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181711, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5181811;
	bSizer5181811 = new wxBoxSizer( wxHORIZONTAL );

	label_shortcut_walk811 = new wxStaticText( m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0 );
	label_shortcut_walk811->Wrap( -1 );
	bSizer5181811->Add( label_shortcut_walk811, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl681811 = new wxTextCtrl( m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5181811->Add( m_textCtrl681811, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer51911->Add( bSizer5181811, 1, wxEXPAND, 5 );


	m_scrolledWindow11->SetSizer( bSizer51911 );
	m_scrolledWindow11->Layout();
	bSizer51911->Fit( m_scrolledWindow11 );
	bSizer98->Add( m_scrolledWindow11, 1, wxEXPAND | wxALL, 5 );


	bSizer50->Add( bSizer98, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxHORIZONTAL );

	bSizer76->SetMinSize( wxSize( -1,50 ) );
	m_button3 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( m_button3, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( m_button4, 0, wxALL, 5 );


	bSizer50->Add( bSizer76, 1, wxALIGN_CENTER, 5 );


	this->SetSizer( bSizer50 );
	this->Layout();

	this->Centre( wxBOTH );
}

Shortcuts_Menu::~Shortcuts_Menu()
{
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

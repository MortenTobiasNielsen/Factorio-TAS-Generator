#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "ScriptProgressBar.h"

class OpenTas
{
public:
	void Open();

private:
	std::vector<std::string> seglist;
	std::string segment;
	std::string goal;

	int total_lines = 0;
	int lines_processed = 0;

	bool extract_total_steps(std::ifstream& file);
	bool extract_goal(std::ifstream& file);
	bool extract_steps(std::ifstream& file);
	bool extract_groups(std::ifstream& file);
	bool extract_templates(std::ifstream& file);
	bool extract_save_location(std::ifstream& file);
	bool extract_script_location(std::ifstream& file);
	bool extract_auto_close(std::ifstream& file);
	bool extract_auto_put(std::ifstream& file);

	void update_segment(std::ifstream& file);
	void malformed_saved_file_message();
};


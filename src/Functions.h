#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <wx/wx.h>

bool compare_task_strings(const wxString& str1, const std::string& str2);

std::string extract_define(std::string building, std::string from_into);

bool check_input(std::string& item, const std::vector<std::string>& all_items);

void string_capitalized(std::string &string);

void find_coordinates(std::string& x_cord, std::string& y_cord, std::string& direction, std::string& building_size);

bool is_number(const std::string& s);
#include "SearchUtil.h"

tuple<wxString, wxString> Search::ExtractColon(const wxString& s)
{
	size_t t = s.find_first_of(':');
	if (t > s.size())
	{
		return {"any", s};
	}

	return {s.substr(0, t), s.substr(t + 1, s.Length())};
}

tuple<vector<int>, wxString> Search::HandleColon(const wxString& s)
{
	auto [column, text] = ExtractColon(s);
	vector<int> c; //casd
	if (column == "any")
	{
		c.reserve(5);
		double text_todouble_throwaway = 0;
		
		if (text.ToDouble(&text_todouble_throwaway))
		{
			c.push_back(1);
			c.push_back(2);
			c.push_back(3);
			c.push_back(7);
			c.push_back(8);
		}
		else
		{
			c.push_back(0);
			c.push_back(4);
			c.push_back(5);
			c.push_back(6);
			c.push_back(9);
		}
	}
	else
	{
		for (int i = 0; i < column.Length(); i++) column[i] = std::tolower(column[i]); // convert custom column to lower case
		vector<wxString> columns = StepColumns;
		for (int i = 0; i < 10; i++)
		{
			if (columns[i].starts_with(column))
			{
				c.push_back(i);
				break;
			}
		}
		//TODO: handle if no column is found
	}

	return {c, text};
}

vector<tuple<vector<int>, wxString>> Search::HandleSearchString(wxCommandEvent& event)
{
	vector<tuple<vector<int>, wxString>> searchterms = {};
	auto str = event.GetString();
	
	auto list = Split(str.ToStdString(), ';');
	for (wxString item : list)
	{
		auto a = HandleColon(item);
		searchterms.push_back(a);
	}
	return searchterms;
}

bool Search::TrySelectCurrent(wxGrid* grid, vector<tuple<vector<int>, wxString>> searchTerms)
{
	auto rows = grid->GetSelectedRows();
	for (auto id : rows)
	{
		int a = 0;
		for (auto [columns, term] : searchTerms)
		{
			for (auto c : columns)
			{ //any column contains term
				if (grid->GetCellValue(id, c).starts_with(term))
				{
					a++;
					break;
				}
			}//maybe add fast exit if no column contains term
		}

		if (a == searchTerms.size()) // if found row
		{
			grid->SelectRow(id);
			grid->ScrollLines(id - rows[0]);
			return true;
		}
	}

	return false;
}

bool Search::TrySelectNext(wxCommandEvent& event, wxGrid* grid, vector<tuple<vector<int>, wxString>> searchTerms)
{
	auto rows = grid->GetNumberRows();
	if (event.GetString().size() < 1 || rows < 1)
	{ // no text or no rows => end search
		return false;
	}

	int start;
	auto sel = grid->GetSelectedRows();
	if (sel.empty())
	{
		start = 0; //no select => start at beginning
	}
	else
	{
		start = grid->GetSelectedRows().back() + 1; // select => start at end of selection
	}

	for (int i = start; i < rows; i++)
	{

		int a = 0, c;
		for (auto [columns, term] : searchTerms)
		{
			for (c = 0; c < columns.size(); c++)
			{ //any column contains term
				if (grid->GetCellValue(i, columns[c]).starts_with(term))
				{
					a++;
					break;
				}
			}//maybe add fast exit if no column contains term
		}

		if (a == searchTerms.size()) // if found row
		{
			grid->SelectRow(i);
			grid->GoToCell(i, 0);
			return true;
		}
	}

	return false;
}

void Search::FindCurrentOrNext(wxCommandEvent& event, wxGrid* grid)
{
	vector<tuple<vector<int>, wxString>> searchTerms = HandleSearchString(event);
	if (TrySelectCurrent(grid, searchTerms))
	{
		return;
	}
	else
	{
		TrySelectNext(event, grid, searchTerms);
	}
}

void Search::FindNext(wxCommandEvent& event, wxGrid* grid)
{
	vector<tuple<vector<int>, wxString>> searchTerms = HandleSearchString(event);
	TrySelectNext(event, grid, searchTerms);
}
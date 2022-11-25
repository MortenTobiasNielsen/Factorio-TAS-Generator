#pragma once
#include <wx/string.h>

#include <string>
#include <vector>
#include <tuple>

/// <summary>
/// Contains methods to search through a grid for row matching a search string
/// </summary>
namespace search
{
	using std::vector;
	using std::tuple;
	using std::stringstream;

	/// <summary>
	/// Returns true if any char in str contains any char of chars
	/// </summary>
	/// <param name="str">String to search in</param>
	/// <param name="chars">list of chars to search for</param>
	/// <returns></returns>
	static bool stringContainsAny(const wxString& str, const string& chars)
	{
		for (int i = 0; i < str.size(); i++)
			for (int j = 0; j < chars.size(); j++)
				if (str[i] == str[j])
					return true;
		return false;
	}

	/// <summary>
	/// Splits a string
	/// </summary>
	/// <param name="s">String to split</param>
	/// <param name="delim">Delimiter to split on</param>
	/// <returns>Vector of strings</returns>
	static vector<wxString> split(const string& s, char delim)
	{
		vector<wxString> result;
		stringstream ss(s);
		string item;

		while (getline(ss, item, delim))
		{
			result.push_back(item);
		}

		return result;
	}

	namespace internal
	{

		/// <summary>
		/// Internal - Splits a string into column : text, if no colon is found uses column=any
		/// </summary>
		/// <param name="s">string</param>
		/// <returns>tuple(column,text)</returns>
		static tuple<wxString, wxString> extractColon(const wxString& s)
		{
			size_t t = s.find_first_of(':');
			if (t > s.size()) return {"any", s};
			return {s.substr(0, t),
				s.substr(t + 1, s.Length())};
		}

		//column header for task grids
		static inline const vector<wxString> taskcolumns = {"task", "x-cord", "y-cord", "units", "item", "orientation", "direction", "size", "amount", "comment"};
		//column header for building grid
		static inline const vector<wxString> buildingcolumns = {"x-cord", "y-cord", "building", "orientation", "limit", "recipe", "prio in", "prio out", "filter"};

		/// <summary>
		/// Internal - Converts a search text into a list of columns
		/// </summary>
		/// <param name="s">search text</param>
		/// <param name="isTaskGrid">if the grid is a task grid</param>
		/// <returns>tuple(list of columns, text)</returns>
		static tuple<vector<int>, wxString> handleColon(const wxString& s, bool isTaskGrid)
		{
			auto [column, text] = extractColon(s);
			vector<int> c; //casd
			if (column == "any")
			{
				c.reserve(5);
				double throwaway = 0;
				if (isTaskGrid)
				{
					if (text.ToDouble(&throwaway))
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
					if (text.ToDouble(&throwaway))
					{
						c.push_back(0);
						c.push_back(1);
						c.push_back(4);
					}
					else
					{
						c.push_back(2);
						c.push_back(3);
						c.push_back(5);
						c.push_back(6);
						c.push_back(7);
						c.push_back(8);
					}
				}
			}
			else
			{
				for (int i = 0; i < column.Length(); i++) column[i] = std::tolower(column[i]); // convert custom column to lower case
				vector<wxString> columns = isTaskGrid ? taskcolumns : buildingcolumns;
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

		/// <summary>
		/// Internal - Converts a search text into a list of search terms
		/// </summary>
		/// <param name="event">That triggered the search and contain the search text</param>
		/// <param name="isTaskGrid">if the current grid is a task grid</param>
		/// <returns>list of searchterm tuple(columns, text) </returns>
		static vector<tuple<vector<int>, wxString>> handleSearchString(wxCommandEvent& event, bool isTaskGrid = true)
		{
			vector<tuple<vector<int>, wxString>> searchterms = {};
			auto str = event.GetString();
			/*if (str.length() < 4 ||  // 3 or fewer chars, special char rules does not apply
				stringContainsAny(str, ";:~%^")) //or if there are no special chars
			{
				return searchterms;
			}*/
			auto list = split(str.ToStdString(), ';');
			for (wxString item : list)
			{
				auto a = handleColon(item, isTaskGrid);
				searchterms.push_back(a);
			}
			return searchterms;
		}

		//internal storage of current search terms
		vector<tuple<vector<int>, wxString>> searchTerms;

		/// <summary>
		/// Internal - tries to select one of the selected rows when searching. 
		/// Set searchTerms before entering this function
		/// </summary>
		/// <param name="grid">grid to search</param>
		/// <returns>True if any selected row matches the search</returns>
		static bool trySelectCurrent(wxGrid* grid)
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

		/// <summary>
		/// Internal - Tries to select the next element that matches the search criteria. 
		/// Set searchTerms before entering this function
		/// </summary>
		/// <param name="event">Event containing the search string</param>
		/// <param name="grid">Grid to search in</param>
		/// <returns>True if a row is found</returns>
		static bool trySelectNext(wxCommandEvent& event, wxGrid* grid)
		{
			auto rows = grid->GetNumberRows();
			if (event.GetString().size() < 1 || rows < 1)
			{ // no text or no rows => end search
				return false;
			}

			int start;
			auto sel = grid->GetSelectedRows();
			if (sel.empty()) start = 0; //no select => start at beginning
			else start = grid->GetSelectedRows().back() + 1; // select => start at end of selection

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

	}
	/// <summary>
	/// External - select either a selected row that matches or the next one
	/// </summary>
	/// <param name="event">Search trigger event - contains search string</param>
	/// <param name="grid">Grid to search in</param>
	/// <param name="isTaskGrid">If the grid is a task grid - used to determine columns</param>
	static void findCurrentOrNext(wxCommandEvent& event, wxGrid* grid, bool isTaskGrid = true)
	{
		internal::searchTerms = internal::handleSearchString(event, isTaskGrid);
		if (internal::trySelectCurrent(grid))
		{
			return;
		}
		else
		{
			internal::trySelectNext(event, grid);
		}
	}

	/// <summary>
	/// External - select the next row that matches
	/// </summary>
	/// <param name="event">Search trigger event - contains search string</param>
	/// <param name="grid">Grid to search in</param>
	/// <param name="isTaskGrid">If the grid is a task grid - used to determine columns</param>
	static void findNext(wxCommandEvent& event, wxGrid* grid, bool isTaskGrid = true)
	{
		internal::searchTerms = internal::handleSearchString(event, isTaskGrid);
		internal::trySelectNext(event, grid);
	}
}

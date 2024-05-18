#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <regex>


class CFGManager
{
public:
	// Constructors and destructor	
	CFGManager(const std::string& file_path);
	CFGManager();
	~CFGManager();


	const bool is_key_exists(const std::string& key);
	const bool is_empty();
	const size_t size();


	void openconfig(const std::string& file_path = "");
	void save(const std::string& file_path = "");
	void set_file_path(const std::string& file_path);
	const std::string& get_file_path();

	std::string& operator [] (const std::string& key);
	std::pair <const std::string, std::string>& operator [] (const size_t& index);


	void rename_key(const std::string& key, const std::string& new_name);
	void add_key(const std::string& key, const std::string& value = "");
	void remove_key(const std::string& key);
	void clear();



private:
	std::unordered_map <std::string, std::string> structure;
	std::string file_path;
	std::fstream filestream;

	bool file_was_opened = false;
};


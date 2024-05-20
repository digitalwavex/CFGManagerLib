#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <regex>





class CFGManager
{
public:
	class exception : public std::exception
	{
	public:
		exception(const std::string& function_name, const std::string& error);
		
		const char* what() const noexcept override;

	private:
		std::string message;
	};	
	
	
	// Constructors and destructor	
	CFGManager(const std::string& file_path);
	CFGManager();


	const bool is_key_exists(const std::string& key);
	const bool is_empty();
	const size_t size();


	void open();
	void save();
	void set_file_path(const std::string& file_path);
	const char* get_file_path();


	void rename_key(const std::string& key, const std::string& new_name);
	void add_key(const std::string& key, const std::string& value = "");
	void remove_key(const std::string& key);
	void clear();


	std::unordered_map <std::string, std::string>& get_container();


private:
	std::unordered_map <std::string, std::string> structure;
	std::string file_path;
	std::fstream filestream;

	bool file_was_opened = false;
};


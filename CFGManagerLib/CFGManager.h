#pragma once

#include <string>
#include <map>
#include <fstream>
#include <regex>





class CFGManager
{
public:
	// Inner exception class
	class exception : public std::exception
	{
	public:
		exception(const std::string& function_name, const std::string& error, const unsigned int& error_code) noexcept;
		
		const char* what() const noexcept override;

		const unsigned int& get_error_code() const noexcept;

		enum exceptions
		{
			FILE_PATH_IS_NOT_SPECIFIED,
			FILESTREAM_CANT_BE_OPENED_FOR_WRITING,
			FILESTREAM_CANT_BE_OPENED_FOR_READING
		};

	private:
		std::string message;
		unsigned int error_code;
	};	



	
	
	// Constructors and destructor	
	CFGManager(const std::string& file_path);
	CFGManager();


	bool is_key_exists(const std::string& key);
	bool is_empty();
	size_t size();


	void open();
	void save();
	void set_file_path(const std::string& file_path);
	const char* get_file_path();


	void rename_key(const std::string& key, const std::string& new_name);
	void add_key(const std::string& key, const std::string& value = "");
	void remove_key(const std::string& key);
	void clear();


	std::map <std::string, std::string>& get_container();


private:
	std::map <std::string, std::string> structure;
	std::string file_path;
	std::fstream filestream;
};


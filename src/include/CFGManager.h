#pragma once


#include <string>
#include <unordered_map>
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
		std::string _message;
		unsigned int _error_code;
	};


	
	
	// Constructors
	CFGManager(const std::string& file_path) noexcept;
	CFGManager() noexcept;
	CFGManager(const CFGManager& other) noexcept;


	bool is_key_exists(const std::string& key) const noexcept;
	bool is_empty() const noexcept;
	size_t size() const noexcept;


	void open();
	void save();
	void set_file_path(const std::string& file_path) noexcept;
	std::string get_file_path() const noexcept;


	void rename_key(const std::string& key, const std::string& new_name) noexcept;
	void add_key(const std::string& key, const std::string& value) noexcept;
	void remove_key(const std::string& key) noexcept;
	void clear() noexcept;


	std::unordered_map <std::string, std::string>& get_container() noexcept;
	const std::unordered_map <std::string, std::string>& get_container() const noexcept;


	void operator = (const CFGManager& other) noexcept;

private:
	std::unordered_map <std::string, std::string> _data;
	std::string _file_path;
	std::fstream _filestream;
};

bool operator == (const CFGManager& first, const CFGManager& second) noexcept;
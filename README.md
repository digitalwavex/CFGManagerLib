## CFGManager - statically linked library for managing configuration files 
The library is written in C++ and use the format [key]:[value] to manage configuration files. Library has the following functionality and nothing extra:

 - Reading and writing files
 - Adding, deleting, renaming keys etc



## How to use the library?
First, you need to either install the library on the system, or copy the folder with the downloaded or compiled library to the folder with your project. Also, do not forget to tell the compiler where to look for the static library file (in the **lib** folder, header files in the **include** folder). In general, the purpose of the methods is clear from their names, but let's look at a few examples:

    CFGManager cfg("some config file.txt");     // This saves the file path specified in the constructor  
    cfg.open();                                 // This will open the file along the path passed to the constructor
    std::cout << cfg["Key 1"];                  // This will display the value of Key 1 (operator [] can throw exception!)

You can use **get_container()** method to get full control over the data container, which is the unordered_map. This way you can iterate over the keys.


You can also add values

    cfg.add_key("Key name", "Value");  
    
    // This will add a key:value pair
    // If no value is specified, the empty value is used

Finally you can save the file (the **save** method overwrites the file or creates a new one):

    cfg.save();

If you want to set the path to a new file or view the current path, use the **set_file_path** and **get_file_path** methods respectively. The **save** and **open** methods use the path specified either in the class constructor or via **set_file_path**.

It is also possible to rename the key:

    cfg.rename_key("It was an old name", "this will become a new name");
The library also has an overloaded copy constructor, an assignment operator (copies the file path and data, like a copy constructor), and a comparison operator (compares by data).


## Possible exceptions
Some functions may throw an exception if something goes wrong. The exception class is CFGManager::exception, which inherits from std::exception. Inside this class there is an additional method get_error_code(), which returns the error code. The what() method returns a description of the exception and in which method it was thrown. Inside CFGManager::exception there is an exception enum which contains the following possible exceptions (you can compare the error code with the exception code):


    FILE_PATH_IS_NOT_SPECIFIED            - Forgot to specify the path to the file 
    FILESTREAM_CANT_BE_OPENED_FOR_WRITING - Does not have write permissions 
    FILESTREAM_CANT_BE_OPENED_FOR_READING - The file does not exist or there is no read permission
    KEY_NOT_FOUND                         - Attempting to access a non-existent key



These exceptions can be thrown by the following methods:

    open()      - FILE_PATH_IS_NOT_SPECIFIED or FILESTREAM_CANT_BE_OPENED_FOR_READING
    save()      - FILE_PATH_IS_NOT_SPECIFIED or FILESTREAM_CANT_BE_OPENED_FOR_WRITING
    operator [] - KEY_NOT_FOUND (If the key was found, this will return a reference to it)



## How to build the library?
You need to install the following:

 - С++ compiler (I use g++ with C++ 23 standart)
 - Cmake (3.27.4 minimum required)
 - Make
 - GTest (If you want to build tests)

Go to the project root folder (where the CMakeLists.txt file is located) then write in terminal (you can also open the folder in Visual Studio Code and build the project):

    mkdir build
    cd build

If you want to build tests:

    cmake .. -DBUILD_TESTS=ON
If not:

    cmake ..
  Then:
	  

    cmake --build .
The built library will be located in the folder ****build/CFGManager****


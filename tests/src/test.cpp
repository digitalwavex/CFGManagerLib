#include <gtest/gtest.h>
#include "../../build/CFGManager/include/CFGManager.h"
#include "cmake_defined_data_directory.h"




std::string data_directory          = TESTS_DATA_DIRECTORY;
std::string _10_elements_file       = data_directory + "10_elements.txt";
std::string _10_elements_named_file = data_directory + "10_elements_named.txt";
std::string _file_to_writing        = data_directory + "file_to_writing.txt";




TEST(CopyingConstructor, copying_empty_config)
{
    CFGManager cfg;
    CFGManager cfg2 = cfg;

    EXPECT_EQ(cfg.size(), cfg2.size());
    EXPECT_TRUE(cfg.get_container() == cfg2.get_container());
}


TEST(CopyingConstructor, copying_config)
{
    CFGManager cfg;
    cfg.add_key("Key 1", "Value 1");

    CFGManager cfg2 = cfg;

    EXPECT_EQ(cfg.size(), cfg2.size());
    EXPECT_TRUE(cfg.get_container() == cfg2.get_container());
}





TEST(AssignmentOperator, assign_empty)
{
    CFGManager cfg;
    CFGManager cfg2;

    cfg2 = cfg;

    EXPECT_TRUE(cfg.get_container() == cfg2.get_container() && cfg.get_file_path() == cfg2.get_file_path());
}


TEST(AssignmentOperator, assign_not_empty)
{
    CFGManager cfg;
    cfg.add_key("Key 1", "Value 1");
    CFGManager cfg2;

    cfg2 = cfg;

    EXPECT_TRUE(cfg.get_container() == cfg2.get_container() && cfg.get_file_path() == cfg2.get_file_path());
}




TEST(ComparasionOperator, compare_equal)
{
    CFGManager cfg;
    cfg.add_key("key 1", "value 1");

    CFGManager cfg2;
    cfg2.add_key("key 1", "value 1");


    EXPECT_TRUE(cfg == cfg2);
}


TEST(ComparasionOperator, compare_not_equal)
{
    CFGManager cfg;
    cfg.add_key("key 1", "value 1");

    CFGManager cfg2;
    cfg2.add_key("key 1", "value 1");
    cfg2.add_key("key 2", "value 2");


    EXPECT_FALSE(cfg == cfg2);
}




TEST(TestingCountOfElements, Testing_5_elements)
{
   CFGManager cfg;
   cfg.add_key("Key 1", "Value 1");
   cfg.add_key("Key 2", "Value 2");
   cfg.add_key("Key 3", "Value 3");
   cfg.add_key("Key 4", "Value 4");
   cfg.add_key("Key 5", "Value 5");

   EXPECT_EQ(cfg.size(), 5);
}


TEST(TestingCountOfElements, Testing_0_elements)
{
   CFGManager cfg;

   EXPECT_EQ(cfg.size(), 0);
}





TEST(TestingEmpty, config_is_empty)
{
    CFGManager cfg;
    EXPECT_TRUE(cfg.is_empty());
}


TEST(TestingEmpty, config_is_not_empty)
{
    CFGManager cfg;
    cfg.add_key("key", "value");
    EXPECT_FALSE(cfg.is_empty());
}





TEST(TestingClear, clear_empty_config)
{
    CFGManager cfg;
    cfg.clear();

    EXPECT_EQ(cfg.size(), 0);
}


TEST(TestingClear, clear_not_empty_config)
{
    CFGManager cfg;
    cfg.add_key("key 1", "value 1");
    cfg.clear();

    EXPECT_EQ(cfg.size(), 0);
}





TEST(TestingAdding, adding_different_keys)
{
    CFGManager cfg;
    cfg.add_key("key 1", "value 1");
    cfg.add_key("key 2", "value 2");
    EXPECT_EQ(cfg.size(), 2);
}


TEST(TestingAdding, adding_same_keys)
{
    CFGManager cfg;
    cfg.add_key("key 1", "value 1");
    cfg.add_key("key 1", "value 2");
    EXPECT_EQ(cfg.size(), 1);
}





TEST(TestingFilePath, get_file_path)
{
    CFGManager cfg(_10_elements_file);

    EXPECT_STREQ(cfg.get_file_path().c_str(), _10_elements_file.c_str());
}


TEST(TestingFilePath, set_file_path)
{
    CFGManager cfg;
    cfg.set_file_path("some/file/path/data.cfg");

    EXPECT_STREQ(cfg.get_file_path().c_str(), "some/file/path/data.cfg");
}





TEST(TestingRemovingKey, remove_key_from_empty_config)
{
    CFGManager cfg;
    cfg.remove_key("Some key");

    EXPECT_EQ(cfg.size(), 0);
}


TEST(TestingRemovingKey, remove_key_from_not_config)
{
    CFGManager cfg;
    cfg.add_key("Key 1", "Value 1");

    cfg.remove_key("Some key");

    EXPECT_EQ(cfg.size(), 1);
}


TEST(TestingRemovingKey, remove_exists_key)
{
    CFGManager cfg;
    cfg.add_key("Some key", "Value 1");
    
    cfg.remove_key("Some key");

    EXPECT_EQ(cfg.size(), 0);
}





TEST(TestingReading, size_10_elements)
{
    CFGManager cfg(_10_elements_file); //  "/usr/10_elements.txt"
    cfg.open();

    EXPECT_EQ(cfg.size(), 10);
}


TEST(TestingReading, elements_correspondence)
{
    CFGManager cfg(_10_elements_file);
    cfg.open();
    
    for (auto pair : cfg.get_container())
    {
        EXPECT_STREQ(pair.first.c_str(), pair.second.c_str());
    }    
}


TEST(TestingReading, all_key_exists)
{
    CFGManager cfg(_10_elements_file);
    cfg.open();

    for (size_t i = 0; i < cfg.size(); ++i)
    {
       EXPECT_TRUE(cfg.is_key_exists(std::to_string(i)));
    }
}


TEST(TestingReading, key_name_changing)
{
    CFGManager cfg(_10_elements_named_file);
    cfg.open();
    
    cfg.rename_key("KEY 5", "KEY 100");

    EXPECT_FALSE(cfg.is_key_exists("KEY 5"));
    EXPECT_TRUE(cfg.is_key_exists("KEY 100"));
    EXPECT_EQ(cfg.size(), 10);
}


TEST(TestingReading, expect_exception_when_not_set_path)
{
    CFGManager cfg;
    
    try
    {
        cfg.open();

        FAIL();
    }
    catch(const CFGManager::exception& e)
    {
        EXPECT_EQ(e.get_error_code(), e.FILE_PATH_IS_NOT_SPECIFIED);
    } 
}


TEST(TestingReading, wrong_path)
{
    CFGManager cfg("wrong path");
    
    try
    {
        cfg.open();

        FAIL();
    }
    catch(const CFGManager::exception& e)
    {
        EXPECT_EQ(e.get_error_code(), e.FILESTREAM_CANT_BE_OPENED_FOR_READING);
    }    
}





TEST(TestingWriting, is_100_writed_elements_exists)
{
    CFGManager cfg(_file_to_writing);
    
    for (size_t i = 0; i < 100; i++)
    {
        cfg.add_key(std::to_string(i), std::to_string(i));
    }

    cfg.save();
    cfg.open();

    EXPECT_EQ(cfg.size(), 100);

    for (size_t i = 0; i < cfg.size(); i++)
    {
        EXPECT_TRUE(cfg.is_key_exists(std::to_string(i)));
    }
    
}


TEST(TestingWriting, expect_exception_when_not_set_path)
{
    CFGManager cfg;
    
    try
    {
        cfg.save();

        FAIL();
    }
    catch(const CFGManager::exception& e)
    {
        EXPECT_EQ(e.get_error_code(), e.FILE_PATH_IS_NOT_SPECIFIED);
    }    
}






int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
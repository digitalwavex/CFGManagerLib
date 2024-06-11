#include <gtest/gtest.h>
#include "../../build/CFGManager/include/CFGManager.h"
#include "cmake_defined_data_directory.h"



std::string data_directory          = TESTS_DATA_DIRECTORY;
std::string _10_elements_file       = data_directory + "10_elements.txt";
std::string _10_elements_named_file = data_directory + "10_elements_named.txt";
std::string _file_to_writing        = data_directory + "file_to_writing.txt";



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





TEST(TestingReading, Testing_10_elements)
{
    CFGManager cfg(_10_elements_file); //  "/usr/10_elements.txt"

    EXPECT_EQ(cfg.size(), 10);
}


TEST(TestingReading, Testing_correspondence)
{
    CFGManager cfg(_10_elements_file);

    
    for (auto pair : cfg.get_container())
    {
        EXPECT_STREQ(pair.first.c_str(), pair.second.c_str());
    }    
}


TEST(TestingReading, Testing_key_exists)
{
    CFGManager cfg(_10_elements_named_file);

    EXPECT_TRUE(cfg.is_key_exists("KEY 5"));  
}


TEST(TestingReading, Testing_key_name_changing)
{
    CFGManager cfg(_10_elements_named_file);
    
    cfg.rename_key("KEY 5", "KEY 100");

    EXPECT_FALSE(cfg.is_key_exists("KEY 5"));
    EXPECT_TRUE(cfg.is_key_exists("KEY 100"));
    EXPECT_EQ(cfg.size(), 10);
}


TEST(TestingReading, Testing_correct_order)
{
    CFGManager cfg(_10_elements_file);
    
    size_t i = 0;
    for(auto pair : cfg.get_container())
    {
        EXPECT_EQ(std::stoi(pair.first.c_str()), i);
        ++i;
    }
}





TEST(TestingWriting, Testing_writing_100_elements)
{
    CFGManager cfg(_file_to_writing);
    
    for (size_t i = 0; i < 100; i++)
    {
        cfg.add_key(std::to_string(i), std::to_string(i));
    }

    cfg.save();
    cfg.open();

    EXPECT_EQ(cfg.size(), 100);    
}


TEST(TestingWriting, Testing_writing_100_elements_in_correct_order)
{
    CFGManager cfg(_file_to_writing);
    
    for (size_t i = 0; i < 100; i++)
    {
        cfg.add_key(std::to_string(i), std::to_string(i));
    }

    cfg.save();
    cfg.open();

    size_t i = 0;
    for(auto pair : cfg.get_container())
    {
        EXPECT_EQ(std::stoi(pair.first.c_str()), i);
        ++i;
    } 
}





int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
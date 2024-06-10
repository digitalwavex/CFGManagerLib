#include <gtest/gtest.h>
#include "../../build/CFGManager/include/CFGManager.h"
#include "cmake_defined_data_directory.h"



std::string data_directory          = TESTS_DATA_DIRECTORY;
std::string _10_elements_file       = data_directory + "10_elements.txt";
std::string _10_elements_named_file = data_directory + "10_elements_named.txt";




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
    cfg.open();

    EXPECT_EQ(cfg.size(), 10);
}


TEST(TestingReading, Testing_correspondence)
{
    CFGManager cfg(_10_elements_file);
    cfg.open();

    
    for (auto pair : cfg.get_container())
    {
        EXPECT_STREQ(pair.first.c_str(), pair.second.c_str());
    }    
}


TEST(TestingReading, Testing_key_exists)
{
    CFGManager cfg(_10_elements_named_file);
    cfg.open();

    EXPECT_TRUE(cfg.is_key_exists("KEY 10"));  
}


TEST(TestingReading, Testing_key_name_changing)
{
    CFGManager cfg(_10_elements_named_file);
    cfg.open();
    
    cfg.rename_key("KEY 5", "KEY 100");

    EXPECT_FALSE(cfg.is_key_exists("KEY 5"));
    EXPECT_TRUE(cfg.is_key_exists("KEY 100"));
    EXPECT_EQ(cfg.size(), 9);
}





int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
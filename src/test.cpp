#include <vector>
#include "Command.h"
#include "TestCommand.h"
#include "Parser.h"
#include "gtest/gtest.h"

using namespace std;

TEST(CommandTestSet, EchoCommandTest){
	char one[] = "echo"; char two[] = "hello"; 
	vector<char*> test_val; test_val.push_back(one); test_val.push_back(two);// test_val.push_back(NULL);
	Command* c = new Command(test_val);
	EXPECT_EQ(c->execute(), 0);
}

TEST(CommandTestSet, LsCommandTest){
	char one[] = "ls";
	vector<char*> test_val;
	test_val.push_back(one);
	Command* c = new Command(test_val);
	EXPECT_EQ(c->execute(), 0);
}

TEST(CommandTestSet, ExitCommandTest){
	char one[] = "exit";
	vector<char*> v;
	v.push_back(one);
	Command* c = new Command(v);
	c->execute();
}

TEST(ParserTestSet, SingleCommandTest){
	char strarr[] = "echo hello";
	vector<char> str;
	for(int i = 0; i < 11; i++){
		str.push_back(strarr[i]);
	}
	Parser* p = new Parser(str);
	vector<char*> test_vals;
	test_vals = p->parse();
	EXPECT_EQ(strcmp(test_vals.at(0), "echo"), 0);
	EXPECT_EQ(strcmp(test_vals.at(1), "hello"), 0);
}

TEST(ParseTestSet, MultipleCommandTest){
	char str[] = "echo a || asdsf && echo b || echo c";
	vector<char> v;
	for(int i = 0; i < 36; i++){
		v.push_back(str[i]);
	}
	Parser* p = new Parser(v);
	vector<char*> test_vals = p->parse();
	EXPECT_EQ(strcmp(test_vals.at(0), "echo"), 0);
	EXPECT_EQ(strcmp(test_vals.at(1), "a"), 0);
	EXPECT_EQ(strcmp(test_vals.at(2), "||"), 0);
	EXPECT_EQ(strcmp(test_vals.at(3), "asdsf"), 0);
	EXPECT_EQ(strcmp(test_vals.at(4), "&&"), 0);
	EXPECT_EQ(strcmp(test_vals.at(5), "echo"), 0);
	EXPECT_EQ(strcmp(test_vals.at(6), "b"), 0);
	EXPECT_EQ(strcmp(test_vals.at(7), "||"), 0);
	EXPECT_EQ(strcmp(test_vals.at(8), "echo"), 0);
	EXPECT_EQ(strcmp(test_vals.at(9), "c"), 0);
}

TEST(TestCommandSet, DashETest){
	vector<char*> v;
	char str[] = "test"; char str1[] = "-e"; char str2[] = "tests/";
	v.push_back(str); v.push_back(str1); v.push_back(str2);
	TestCommand* t = new TestCommand(v);
	EXPECT_EQ(t->execute(), 0);

	v.clear(); v.push_back(str); v.push_back(str2);
	t = new TestCommand(v);
	EXPECT_EQ(t->execute(), 0);

	char str3[] = "src/Parser.h";
	v.clear(); v.push_back(str); v.push_back(str1); v.push_back(str3);
	t = new TestCommand(v);
	EXPECT_EQ(t->execute(), 0);
}

TEST(TestCommandSet, DashFTest){
	vector<char*> v;
	char str[] = "test"; char str1[] = "-f"; char str2[] = "CMakeLists.txt"; char str3[] = "src/UserInterface.cpp"; char str4[] = "tests/";
	v.push_back(str); v.push_back(str1); v.push_back(str2);
	TestCommand* t = new TestCommand(v);
	EXPECT_EQ(t->execute(), 0);
	v.clear(); v.push_back(str); v.push_back(str1); v.push_back(str3);
	t = new TestCommand(v);
	EXPECT_EQ(t->execute(), 0);
	v.clear(); v.push_back(str); v.push_back(str1); v.push_back(str4);
	t = new TestCommand(v);
	EXPECT_EQ(t->execute(), -1);
}

TEST(TestCommandSet, DashDTest){
	vector<char*> v;
        char str[] = "test"; char str1[] = "-d"; char str2[] = "src/"; char str3[] = "src/UserInterface.cpp"; char str4[] = "tests/";
        v.push_back(str); v.push_back(str1); v.push_back(str2);
        TestCommand* t = new TestCommand(v);
        EXPECT_EQ(t->execute(), 0);
        v.clear(); v.push_back(str); v.push_back(str1); v.push_back(str3);
        t = new TestCommand(v);
        EXPECT_EQ(t->execute(), -1);
        v.clear(); v.push_back(str); v.push_back(str1); v.push_back(str4);
        t = new TestCommand(v);
        EXPECT_EQ(t->execute(), 0);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

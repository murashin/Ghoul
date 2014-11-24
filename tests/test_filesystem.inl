/*****************************************************************************************
*                                                                                       *
* GHOUL                                                                                 *
* General Helpful Open Utility Library                                                  *
*                                                                                       *
* Copyright (c) 2012-2014                                                               *
*                                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
* software and associated documentation files (the "Software"), to deal in the Software *
* without restriction, including without limitation the rights to use, copy, modify,    *
* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to the following   *
* conditions:                                                                           *
*                                                                                       *
* The above copyright notice and this permission notice shall be included in all copies *
* or substantial portions of the Software.                                              *
*                                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
****************************************************************************************/

#include "gtest/gtest.h"
#include <ghoul/filesystem/filesystem>
#include <iostream>
#include <fstream>

TEST(FileSystemTest, HasTestDirectory) {
	//EXPECT_EQ(FileSys.directoryExists("${TEST_DIR}"), true);
}

TEST(FileSystemTest, CreateRemoveDirectory) {
	const std::string tmp = absPath("${TEST_DIR}/tmp");
	const std::string tmpRecursive1 = absPath("${TEST_DIR}/tmp/tmp2");
	const std::string tmpRecursive2 = absPath("${TEST_DIR}/tmp/tmp2/tmp3");

	EXPECT_EQ(FileSys.createDirectory(tmp), true);
	EXPECT_EQ(FileSys.createDirectory(tmpRecursive2), false);
	EXPECT_EQ(FileSys.createDirectory(tmpRecursive2, true), true);

#ifdef WIN32
	EXPECT_EQ(FileSys.deleteDirectory(tmp), false);
#endif
	EXPECT_EQ(FileSys.deleteDirectory(tmpRecursive2), true);
	EXPECT_EQ(FileSys.deleteDirectory(tmpRecursive1), true);
	EXPECT_EQ(FileSys.deleteDirectory(tmp), true);
}

TEST(FileSystemTest, Path) {
	using ghoul::filesystem::File;

	std::string path = "${TEST_DIR}/tmpfil.txt";
	std::string abspath = absPath(path);

	File* f1 = new File(path);
	File* f2 = new File(path, true);
	File* f3 = new File(abspath, true);

	EXPECT_NE(f1->path(), f2->path());
	EXPECT_NE(f2->path(), f3->path());
	EXPECT_EQ(f1->path(), f3->path());

	delete f3;
	delete f2;
	delete f1;
}

TEST(FileSystemTest, OnChangeCallback) {
	using ghoul::filesystem::File;

	const char* cpath = "${TEST_DIR}/tmpfil.txt";
	std::string path = absPath(cpath);
	std::ofstream f;
	f.open(path);
	f << "tmp";
	f.close();
	bool b = false;
	auto c = [&b](const File& f) {
		b = true;
	};

	File* f1 = new File(path, false, c);
	File* f2 = new File(path, false, c);

	// Check that the file exists
	EXPECT_EQ(FileSys.fileExists(cpath, false), true);
	EXPECT_EQ(FileSys.fileExists(path), true);
	EXPECT_EQ(FileSys.fileExists(*f1), true);

	f2->setCallback(nullptr);

	// Check that b still is false so no callback has been fired
	EXPECT_EQ(b, false);

	// overwrite the file
	f.open(path);
	f << "tmp";
	f.close();
	FileSys.triggerFilesystemEvents();

	// Sleep the main thread to make sure the filesystem have time to respond
	const int seconds = 4;
#ifdef WIN32
	int count = 0;
	while (b == false && count < 100 * seconds) {
		Sleep(10);
		++count;
	}
#else
	int count = 0;
	while (b == false && count < 10000 * seconds) {
		usleep(100);
		FileSys.triggerFilesystemEvents();
		++count;
	}
#endif
	EXPECT_EQ(b, true);

	delete f2;
	delete f1;

	// Check that we can delete the file
	EXPECT_EQ(FileSys.deleteFile(path), true);
}
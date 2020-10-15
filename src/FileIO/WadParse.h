#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace LCU {
    namespace FileIO {
		// 32 byte file header
		struct FileHeader {
			uint64_t dirPath = 0; // 8
			uint32_t offset = 0; // 4
			uint32_t compressedFileSize = 0; // 4
			uint32_t fileSize = 0; // 4
			char type = 0; // 1
			char duplicate = 0; // 1
			uint16_t unk = 0; // 2
			uint64_t sha256 = 0; // 8
		};

		// File information
		struct WADFile {
			int majorVersion;
			int minorVersion;
			std::vector<FileHeader> headers;

			uint64_t checksum;
			int fileCount;
			char ecdsa[256];
			std::string plugin;
			std::string file;
		};


    }
};

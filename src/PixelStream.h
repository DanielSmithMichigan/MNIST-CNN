#pragma once
#include <fstream>

using namespace std;

class PixelStream {
	private:
	protected:
	public:
		PixelStream();
		~PixelStream();
		virtual uint8_t get();
};